/********************************************************************
*
* SOC FIREWALL PROPERTIES. header file
*
* Copyright (C) 2015-2023 Texas Instruments Incorporated.
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
#ifndef CSLR_SOC_FW_H_
#define CSLR_SOC_FW_H_

#include <drivers/hw_include/cslr.h>
#include <drivers/hw_include/tistdtypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
* Auto-generated CSL definitions for SoC Firewalls:
*/

#define CSL_FW_SECURITY                                                                            (0U)
#define CSL_FW_CHANNEL                                                                             (1U)
#define CSL_FW_MST                                                                                 (2U)

/* Standard Security Master Firewall Definitions */

/* Standard Security Slave Firewall Definitions */

/* Properties of firewall at slave: DDR32SS0_SDRAM_FW0 */
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_ID                                                           (0U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_MMR_BASE                                                     (0x00000045000000U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_NUM_REGIONS                                                  (8U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_SDRAM_START                                                  (0x00000080000000U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_SDRAM_END                                                    (0x000000ffffffffU)

/* Properties of firewall at slave: DDR32SS0_SDRAM_FW1 */
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_ID                                                           (1U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_MMR_BASE                                                     (0x00000045000400U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_SDRAM_START                                                  (0x00000080000000U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_SDRAM_END                                                    (0x000000ffffffffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_ROM_TABLE_0_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_ROM_TABLE_0_0_START                                 (0x00000700000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_ROM_TABLE_0_0_END                                   (0x00000700000fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV0_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_RESV0_0_START                                             (0x00000700001000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_RESV0_0_END                                               (0x00000700001fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CFGAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_CFGAP0_START                                          (0x00000700002000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_CFGAP0_END                                            (0x000007000020ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_APBAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_APBAP0_START                                          (0x00000700002100U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_APBAP0_END                                            (0x000007000021ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_AXIAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_AXIAP0_START                                          (0x00000700002200U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_AXIAP0_END                                            (0x000007000022ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_PWRAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_PWRAP0_START                                          (0x00000700002300U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_PWRAP0_END                                            (0x000007000023ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_PVIEW_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_PVIEW0_START                                          (0x00000700002400U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_PVIEW0_END                                            (0x000007000024ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_JTAGAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_ID                                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_MMR_BASE                                             (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_NUM_REGIONS                                          (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_JTAGAP0_START                                        (0x00000700002500U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_JTAGAP0_END                                          (0x000007000025ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_SECAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_SECAP0_START                                          (0x00000700002600U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_SECAP0_END                                            (0x000007000026ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX0_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_CORTEX0_CFG0_START                                  (0x00000700002700U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_CORTEX0_CFG0_END                                    (0x000007000027ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX1_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_CORTEX1_CFG0_START                                  (0x00000700002800U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_CORTEX1_CFG0_END                                    (0x000007000028ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX2_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_CORTEX2_CFG0_START                                  (0x00000700002900U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_CORTEX2_CFG0_END                                    (0x000007000029ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX3_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_CORTEX3_CFG0_START                                  (0x00000700002a00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_CORTEX3_CFG0_END                                    (0x00000700002affU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX4_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_CORTEX4_CFG0_START                                  (0x00000700002b00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_CORTEX4_CFG0_END                                    (0x00000700002bffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX5_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_CORTEX5_CFG0_START                                  (0x00000700002c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_CORTEX5_CFG0_END                                    (0x00000700002cffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX6_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_CORTEX6_CFG0_START                                  (0x00000700002d00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_CORTEX6_CFG0_END                                    (0x00000700002dffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX7_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_CORTEX7_CFG0_START                                  (0x00000700002e00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_CORTEX7_CFG0_END                                    (0x00000700002effU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX8_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_CORTEX8_CFG0_START                                  (0x00000700002f00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_CORTEX8_CFG0_END                                    (0x00000700002fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV1_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_RESV1_0_START                                             (0x00000700003000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_RESV1_0_END                                               (0x00000700003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV2_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_RESV2_0_START                                             (0x00000700004000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_RESV2_0_END                                               (0x00000702003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_ROM_TABLE_1_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_ROM_TABLE_1_0_START                                 (0x00000720000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_ROM_TABLE_1_0_END                                   (0x00000720000fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CSCTI_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_CSCTI0_START                                          (0x00000720001000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_CSCTI0_END                                            (0x00000720001fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_DRM_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_DRM0_START                                              (0x00000720002000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_DRM0_END                                                (0x00000720002fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV3_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_RESV3_0_START                                             (0x00000720003000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_RESV3_0_END                                               (0x00000720003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CSTPIU_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_ID                                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_MMR_BASE                                             (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_NUM_REGIONS                                          (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_CSTPIU0_START                                        (0x00000720004000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_CSTPIU0_END                                          (0x00000720004fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CTF_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_CTF0_START                                              (0x00000720005000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_CTF0_END                                                (0x00000720005fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV4_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_RESV4_0_START                                             (0x00000720006000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_RESV4_0_END                                               (0x00000721005fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_EXT_APB_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_EXT_APB0_START                                          (0x00000730000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_EXT_APB0_END                                            (0x0000073fffffffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_ROM_TABLE_0_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_ROM_TABLE_0_1_START                                 (0x00000740000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_ROM_TABLE_0_1_END                                   (0x00000740000fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV0_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_RESV0_1_START                                             (0x00000740001000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_RESV0_1_END                                               (0x00000740001fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CFGAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_CFGAP1_START                                          (0x00000740002000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_CFGAP1_END                                            (0x000007400020ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_APBAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_APBAP1_START                                          (0x00000740002100U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_APBAP1_END                                            (0x000007400021ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_AXIAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_AXIAP1_START                                          (0x00000740002200U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_AXIAP1_END                                            (0x000007400022ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_PWRAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_PWRAP1_START                                          (0x00000740002300U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_PWRAP1_END                                            (0x000007400023ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_PVIEW_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_PVIEW1_START                                          (0x00000740002400U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_PVIEW1_END                                            (0x000007400024ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_JTAGAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_ID                                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_MMR_BASE                                             (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_NUM_REGIONS                                          (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_JTAGAP1_START                                        (0x00000740002500U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_JTAGAP1_END                                          (0x000007400025ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_SECAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_SECAP1_START                                          (0x00000740002600U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_SECAP1_END                                            (0x000007400026ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX0_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_CORTEX0_CFG1_START                                  (0x00000740002700U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_CORTEX0_CFG1_END                                    (0x000007400027ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX1_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_CORTEX1_CFG1_START                                  (0x00000740002800U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_CORTEX1_CFG1_END                                    (0x000007400028ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX2_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_CORTEX2_CFG1_START                                  (0x00000740002900U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_CORTEX2_CFG1_END                                    (0x000007400029ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX3_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_CORTEX3_CFG1_START                                  (0x00000740002a00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_CORTEX3_CFG1_END                                    (0x00000740002affU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX4_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_CORTEX4_CFG1_START                                  (0x00000740002b00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_CORTEX4_CFG1_END                                    (0x00000740002bffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX5_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_CORTEX5_CFG1_START                                  (0x00000740002c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_CORTEX5_CFG1_END                                    (0x00000740002cffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX6_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_CORTEX6_CFG1_START                                  (0x00000740002d00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_CORTEX6_CFG1_END                                    (0x00000740002dffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX7_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_CORTEX7_CFG1_START                                  (0x00000740002e00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_CORTEX7_CFG1_END                                    (0x00000740002effU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX8_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_CORTEX8_CFG1_START                                  (0x00000740002f00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_CORTEX8_CFG1_END                                    (0x00000740002fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV1_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_RESV1_1_START                                             (0x00000740003000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_RESV1_1_END                                               (0x00000740003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV2_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_RESV2_1_START                                             (0x00000740004000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_RESV2_1_END                                               (0x00000742003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_ROM_TABLE_1_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_ROM_TABLE_1_1_START                                 (0x00000760000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_ROM_TABLE_1_1_END                                   (0x00000760000fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CSCTI_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_CSCTI1_START                                          (0x00000760001000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_CSCTI1_END                                            (0x00000760001fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_DRM_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_DRM1_START                                              (0x00000760002000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_DRM1_END                                                (0x00000760002fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV3_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_RESV3_1_START                                             (0x00000760003000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_RESV3_1_END                                               (0x00000760003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CSTPIU_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_ID                                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_MMR_BASE                                             (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_NUM_REGIONS                                          (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_CSTPIU1_START                                        (0x00000760004000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_CSTPIU1_END                                          (0x00000760004fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CTF_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_CTF1_START                                              (0x00000760005000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_CTF1_END                                                (0x00000760005fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV4_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_RESV4_1_START                                             (0x00000760006000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_RESV4_1_END                                               (0x00000761005fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_EXT_APB_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_EXT_APB1_START                                          (0x00000770000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_EXT_APB1_END                                            (0x0000077fffffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_UMC_CFG */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_ID                                                  (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_MMR_BASE                                            (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_UMC_START                                           (0x0000007c000000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_UMC_END                                             (0x0000007c01ffffU)

/* Properties of firewall at slave: C7X256V0_CLEC_C7XV_CLEC_CFG */
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_ID                                                  (4U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_MMR_BASE                                            (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_CLEC_START                                          (0x0000007c200000U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_CLEC_END                                            (0x0000007c2fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_ID                                              (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_MMR_BASE                                        (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_NUM_REGIONS                                     (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_DRU_START                                       (0x0000007c400000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_DRU_END                                         (0x0000007c403fffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_ID                                          (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_MMR_BASE                                    (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_NUM_REGIONS                                 (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_DRU_SET_START                               (0x0000007c404000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_DRU_SET_END                                 (0x0000007c407fffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_ID                                        (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_MMR_BASE                                  (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_DRU_QUEUE_START                           (0x0000007c408000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_DRU_QUEUE_END                             (0x0000007c40ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_ID                                        (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_MMR_BASE                                  (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_DRU_CHNRT_START                           (0x0000007c440000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_DRU_CHNRT_END                             (0x0000007c45ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_ID                                         (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_MMR_BASE                                   (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_NUM_REGIONS                                (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_DRU_CHRT_START                             (0x0000007c460000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_DRU_CHRT_END                               (0x0000007c47ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_ID                               (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_MMR_BASE                         (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_NUM_REGIONS                      (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_DRU_CHATOMIC_DEBUG_START         (0x0000007c480000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_DRU_CHATOMIC_DEBUG_END           (0x0000007c49ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_ID                                       (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_MMR_BASE                                 (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_NUM_REGIONS                              (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_DRU_CHCORE_START                         (0x0000007c4a0000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_DRU_CHCORE_END                           (0x0000007c4bffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_ID                                        (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_MMR_BASE                                  (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_DRU_CAUSE_START                           (0x0000007c4e0000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_DRU_CAUSE_END                             (0x0000007c4fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_UMC_MEM_MAIN */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_ID                                             (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_MMR_BASE                                       (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_NUM_REGIONS                                    (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_UMC_MEM_MAIN_START                             (0x0000007e000000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_UMC_MEM_MAIN_END                               (0x0000007e0fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_UMC_MEM_AUX */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_ID                                              (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_MMR_BASE                                        (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_NUM_REGIONS                                     (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_UMC_MEM_AUX_START                               (0x0000007f000000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_UMC_MEM_AUX_END                                 (0x0000007f03ffffU)

/* Properties of firewall at slave: VPAC0_MEM_SLV_DATA */
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_ID                                                           (5U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_MMR_BASE                                                     (0x00000045001400U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_NUM_REGIONS                                                  (8U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_MEM_SLV_DATA_START                                           (0x00000071000000U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_MEM_SLV_DATA_END                                             (0x0000007107ffffU)

/* Properties of firewall at slave: GPMC0_CFG */
#define CSL_STD_FW_GPMC0_CFG_ID                                                                    (6U)
#define CSL_STD_FW_GPMC0_CFG_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_GPMC0_CFG_MMR_BASE                                                              (0x00000045001800U)
#define CSL_STD_FW_GPMC0_CFG_NUM_REGIONS                                                           (8U)
#define CSL_STD_FW_GPMC0_CFG_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_GPMC0_CFG_CFG_START                                                             (0x0000003b000000U)
#define CSL_STD_FW_GPMC0_CFG_CFG_END                                                               (0x0000003b0003ffU)

/* Properties of firewall at slave: GPMC0_DATA */
#define CSL_STD_FW_GPMC0_DATA_ID                                                                   (6U)
#define CSL_STD_FW_GPMC0_DATA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_GPMC0_DATA_MMR_BASE                                                             (0x00000045001800U)
#define CSL_STD_FW_GPMC0_DATA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_GPMC0_DATA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_GPMC0_DATA_DATA_START                                                           (0x00000050000000U)
#define CSL_STD_FW_GPMC0_DATA_DATA_END                                                             (0x00000057ffffffU)

/* Properties of firewall at slave: FSS0_FSAS_0_DAT_REG1 */
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_ID                                                         (7U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_MMR_BASE                                                   (0x00000045001c00U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_DAT_REG1_START                                             (0x00000060000000U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_DAT_REG1_END                                               (0x00000067ffffffU)

/* Properties of firewall at slave: FSS0_FSAS_0_DAT_REG0 */
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_ID                                                         (7U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_MMR_BASE                                                   (0x00000045001c00U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_DAT_REG0_START                                             (0x00000400000000U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_DAT_REG0_END                                               (0x000004ffffffffU)

/* Properties of firewall at slave: FSS0_FSAS_0_DAT_REG3 */
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_ID                                                         (7U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_MMR_BASE                                                   (0x00000045001c00U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_DAT_REG3_START                                             (0x00000500000000U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_DAT_REG3_END                                               (0x000005ffffffffU)

/* Properties of firewall at slave: DMASS0_ECC_AGGR_0_ECCAGGR_REGS */
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_ID                                               (9U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_START                                    (0x0000003f005000U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_END                                      (0x0000003f0053ffU)

/* Properties of firewall at slave: DMASS1_ECC_AGGR_0_ECCAGGR_REGS */
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_ID                                               (9U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_START                                    (0x0000003f006000U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_END                                      (0x0000003f0063ffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_INTR */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_ID                                                (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_INTAGGR_INTR_START                                (0x00000048000000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_INTAGGR_INTR_END                                  (0x000000480fffffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_IMAP */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_ID                                                (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_INTAGGR_IMAP_START                                (0x00000048100000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_INTAGGR_IMAP_END                                  (0x00000048103fffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_CFG */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_INTAGGR_CFG_START                                  (0x00000048110000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_INTAGGR_CFG_END                                    (0x0000004811001fU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_L2G */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_INTAGGR_L2G_START                                  (0x00000048120000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_INTAGGR_L2G_END                                    (0x000000481203ffU)

/* Properties of firewall at slave: DMASS0_PSILCFG_0_PSILCFG_PROXY */
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_ID                                               (9U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_PSILCFG_PROXY_START                              (0x00000048130000U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_PSILCFG_PROXY_END                                (0x000000481301ffU)

/* Properties of firewall at slave: DMASS0_PSILSS_0_PSILSS_MMRS */
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_PSILSS_MMRS_START                                   (0x00000048140000U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_PSILSS_MMRS_END                                     (0x00000048140fffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_UNMAP */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_ID                                               (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_INTAGGR_UNMAP_START                              (0x00000048180000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_INTAGGR_UNMAP_END                                (0x0000004819ffffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_MCAST */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_ID                                               (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_INTAGGR_MCAST_START                              (0x00000048210000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_INTAGGR_MCAST_END                                (0x00000048210fffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_GCNTCFG */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_ID                                             (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_MMR_BASE                                       (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_NUM_REGIONS                                    (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_INTAGGR_GCNTCFG_START                          (0x00000048220000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_INTAGGR_GCNTCFG_END                            (0x00000048221fffU)

/* Properties of firewall at slave: DMASS0_PSILSS_0_ETLSW_MMRS */
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_ID                                                   (9U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_ETLSW_MMRS_START                                     (0x00000048230000U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_ETLSW_MMRS_END                                       (0x00000048230fffU)

/* Properties of firewall at slave: DMASS0_RINGACC_0_RINGACC_GCFG */
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_ID                                                (9U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_RINGACC_GCFG_START                                (0x00000048240000U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_RINGACC_GCFG_END                                  (0x000000482403ffU)

/* Properties of firewall at slave: DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS */
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_ID                                            (9U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_MMR_BASE                                      (0x00000045002400U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_NUM_REGIONS                                   (32U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_SEC_PROXY_MMRS_START                          (0x00000048250000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_SEC_PROXY_MMRS_END                            (0x000000482500ffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_BCHAN */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_ID                                                   (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_BCDMA_BCHAN_START                                    (0x00000048420000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_BCDMA_BCHAN_END                                      (0x00000048421fffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RFLOW */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_PKTDMA_RFLOW_START                                 (0x00000048430000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_PKTDMA_RFLOW_END                                   (0x00000048430fffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_TCHAN */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_PKTDMA_TCHAN_START                                 (0x000000484a0000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_PKTDMA_TCHAN_END                                   (0x000000484a1fffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_TCHAN */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_ID                                                   (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_BCDMA_TCHAN_START                                    (0x000000484a4000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_BCDMA_TCHAN_END                                      (0x000000484a5fffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RCHAN */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_PKTDMA_RCHAN_START                                 (0x000000484c0000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_PKTDMA_RCHAN_END                                   (0x000000484c1fffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_RCHAN */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_ID                                                   (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_START                                    (0x000000484c2000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_END                                      (0x000000484c3fffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_GCFG */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_PKTDMA_GCFG_START                                   (0x000000485c0000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_PKTDMA_GCFG_END                                     (0x000000485c00ffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_GCFG */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_ID                                                    (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_MMR_BASE                                              (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_NUM_REGIONS                                           (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_BCDMA_GCFG_START                                      (0x000000485c0100U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_BCDMA_GCFG_END                                        (0x000000485c01ffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RING */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_PKTDMA_RING_START                                   (0x000000485e0000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_PKTDMA_RING_END                                     (0x000000485effffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_RING */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_ID                                                    (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_MMR_BASE                                              (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_NUM_REGIONS                                           (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_BCDMA_RING_START                                      (0x00000048600000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_BCDMA_RING_END                                        (0x00000048607fffU)

/* Properties of firewall at slave: DMASS0_RINGACC_0_RINGACC_RT */
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_RINGACC_RT_START                                    (0x00000049000000U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_RINGACC_RT_END                                      (0x000000493fffffU)

/* Properties of firewall at slave: DMASS0_RINGACC_0_RINGACC_CFG */
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_RINGACC_CFG_START                                  (0x00000049800000U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_RINGACC_CFG_END                                    (0x0000004983ffffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_GCNTRTI */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_ID                                             (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_MMR_BASE                                       (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_NUM_REGIONS                                    (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_INTAGGR_GCNTRTI_START                          (0x0000004a000000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_INTAGGR_GCNTRTI_END                            (0x0000004a0fffffU)

/* Properties of firewall at slave: DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG */
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_ID                                            (9U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_MMR_BASE                                      (0x00000045002400U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_NUM_REGIONS                                   (32U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_SEC_PROXY_SCFG_START                          (0x0000004a400000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_SEC_PROXY_SCFG_END                            (0x0000004a47ffffU)

/* Properties of firewall at slave: DMASS0_SEC_PROXY_0_SEC_PROXY_RT */
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_ID                                              (9U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_MMR_BASE                                        (0x00000045002400U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_NUM_REGIONS                                     (32U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_SEC_PROXY_RT_START                              (0x0000004a600000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_SEC_PROXY_RT_END                                (0x0000004a67ffffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RCHANRT */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_ID                                               (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_PKTDMA_RCHANRT_START                             (0x0000004a800000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_PKTDMA_RCHANRT_END                               (0x0000004a81ffffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_RCHANRT */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_START                                (0x0000004a820000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_END                                  (0x0000004a83ffffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_TCHANRT */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_ID                                               (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_PKTDMA_TCHANRT_START                             (0x0000004aa00000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_PKTDMA_TCHANRT_END                               (0x0000004aa1ffffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_TCHANRT */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_BCDMA_TCHANRT_START                                (0x0000004aa40000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_BCDMA_TCHANRT_END                                  (0x0000004aa5ffffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RINGRT */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_ID                                                (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_PKTDMA_RINGRT_START                               (0x0000004b800000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_PKTDMA_RINGRT_END                                 (0x0000004b9fffffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_RINGRT */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_BCDMA_RINGRT_START                                  (0x0000004bc00000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_BCDMA_RINGRT_END                                    (0x0000004bcfffffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_BCHANRT */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_BCDMA_BCHANRT_START                                (0x0000004c000000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_BCDMA_BCHANRT_END                                  (0x0000004c01ffffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_GCNTRTI */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_ID                                             (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_MMR_BASE                                       (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_NUM_REGIONS                                    (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_INTAGGR_GCNTRTI_START                          (0x0000004e000000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_INTAGGR_GCNTRTI_END                            (0x0000004e01ffffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_UNMAP */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_ID                                               (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_INTAGGR_UNMAP_START                              (0x0000004e040000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_INTAGGR_UNMAP_END                                (0x0000004e04ffffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_MCAST */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_ID                                               (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_INTAGGR_MCAST_START                              (0x0000004e080000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_INTAGGR_MCAST_END                                (0x0000004e0803ffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_GCNTCFG */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_ID                                             (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_MMR_BASE                                       (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_NUM_REGIONS                                    (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_INTAGGR_GCNTCFG_START                          (0x0000004e090000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_INTAGGR_GCNTCFG_END                            (0x0000004e0903ffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_INTR */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_ID                                                (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_INTAGGR_INTR_START                                (0x0000004e0a0000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_INTAGGR_INTR_END                                  (0x0000004e0a7fffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_IMAP */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_ID                                                (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_INTAGGR_IMAP_START                                (0x0000004e0b0000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_INTAGGR_IMAP_END                                  (0x0000004e0b03ffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_CFG */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_ID                                                 (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_INTAGGR_CFG_START                                  (0x0000004e0c0000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_INTAGGR_CFG_END                                    (0x0000004e0c001fU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_RINGRT */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_ID                                                  (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_BCDMA_RINGRT_START                                  (0x0000004e100000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_BCDMA_RINGRT_END                                    (0x0000004e10ffffU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_RCHANRT */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_ID                                                 (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_START                                (0x0000004e180000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_END                                  (0x0000004e187fffU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_RCHAN */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_ID                                                   (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_START                                    (0x0000004e200000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_END                                      (0x0000004e2007ffU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_RING */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_ID                                                    (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_MMR_BASE                                              (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_NUM_REGIONS                                           (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_BCDMA_RING_START                                      (0x0000004e210000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_BCDMA_RING_END                                        (0x0000004e2107ffU)

/* Properties of firewall at slave: DMASS1_PSILSS_0_PSILSS_MMRS */
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_ID                                                  (9U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_PSILSS_MMRS_START                                   (0x0000004e220000U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_PSILSS_MMRS_END                                     (0x0000004e220fffU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_GCFG */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_ID                                                    (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_MMR_BASE                                              (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_NUM_REGIONS                                           (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_BCDMA_GCFG_START                                      (0x0000004e230000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_BCDMA_GCFG_END                                        (0x0000004e2300ffU)

/* Properties of firewall at slave: DMASS1_PSILCFG_0_PSILCFG_PROXY */
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_ID                                               (9U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_PSILCFG_PROXY_START                              (0x0000004e260000U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_PSILCFG_PROXY_END                                (0x0000004e2601ffU)

/* Properties of firewall at slave: CBASS_DBG0_ERR_REGS */
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_ID                                                          (10U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_MMR_BASE                                                    (0x00000045002800U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_ERR_START                                                   (0x00000000200000U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_ERR_END                                                     (0x000000002003ffU)

/* Properties of firewall at slave: COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS */
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_ID                       (10U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_TYPE                     (CSL_FW_SECURITY)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_MMR_BASE                 (0x00000045002800U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_NUM_REGIONS              (16U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_NUM_PRIV_IDS_PER_REGION  (3U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_PBIST_START              (0x00000000330000U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_PBIST_END                (0x000000003303ffU)

/* Properties of firewall at slave: PBIST3_MEM */
#define CSL_STD_FW_PBIST3_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST3_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST3_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST3_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST3_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST3_MEM_START                                                                (0x00000000340000U)
#define CSL_STD_FW_PBIST3_MEM_END                                                                  (0x000000003403ffU)

/* Properties of firewall at slave: VPAC0_MEM */
#define CSL_STD_FW_VPAC0_MEM_ID                                                                    (10U)
#define CSL_STD_FW_VPAC0_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_MEM_MMR_BASE                                                              (0x00000045002800U)
#define CSL_STD_FW_VPAC0_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_VPAC0_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_VPAC0_MEM_MEM_START                                                             (0x00000000350000U)
#define CSL_STD_FW_VPAC0_MEM_MEM_END                                                               (0x000000003503ffU)

/* Properties of firewall at slave: C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST */
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_ID                                   (10U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_MMR_BASE                             (0x00000045002800U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_NUM_REGIONS                          (16U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_PBIST_START                          (0x00000000360000U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_PBIST_END                            (0x000000003603ffU)

/* Properties of firewall at slave: USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE */
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_ID                          (10U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_TYPE                        (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_MMR_BASE                    (0x00000045002800U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_REGIONS                 (16U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_PRIV_IDS_PER_REGION     (3U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_START (0x00000000703000U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_END (0x000000007031ffU)

/* Properties of firewall at slave: USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE */
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_ID                          (10U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_TYPE                        (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_MMR_BASE                    (0x00000045002800U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_REGIONS                 (16U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_PRIV_IDS_PER_REGION     (3U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_START (0x0000000070c000U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_END (0x0000000070c1ffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_COREPAC_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_ID                                                 (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_MMR_BASE                                           (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_SS_ECC_AGGR_START                                  (0x00000000718000U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_SS_ECC_AGGR_END                                    (0x000000007183ffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_CORE0_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_ID                                                   (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_CORE0_ECC_AGGR_START                                 (0x00000000718400U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_CORE0_ECC_AGGR_END                                   (0x000000007187ffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_CORE1_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_ID                                                   (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_CORE1_ECC_AGGR_START                                 (0x00000000718800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_CORE1_ECC_AGGR_END                                   (0x00000000718bffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_CORE2_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_ID                                                   (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_CORE2_ECC_AGGR_START                                 (0x00000000718c00U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_CORE2_ECC_AGGR_END                                   (0x00000000718fffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_CORE3_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_ID                                                   (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_CORE3_ECC_AGGR_START                                 (0x00000000719000U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_CORE3_ECC_AGGR_END                                   (0x000000007193ffU)

/* Properties of firewall at slave: C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS */
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_ID                                         (10U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_MMR_BASE                                   (0x00000045002800U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_ECC_AGGR_START                             (0x0000000071a000U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_ECC_AGGR_END                               (0x0000000071a3ffU)

/* Properties of firewall at slave: TIMER0_CFG */
#define CSL_STD_FW_TIMER0_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER0_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER0_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER0_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER0_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER0_CFG_CFG_START                                                            (0x00000002400000U)
#define CSL_STD_FW_TIMER0_CFG_CFG_END                                                              (0x000000024003ffU)

/* Properties of firewall at slave: TIMER1_CFG */
#define CSL_STD_FW_TIMER1_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER1_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER1_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER1_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER1_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER1_CFG_CFG_START                                                            (0x00000002410000U)
#define CSL_STD_FW_TIMER1_CFG_CFG_END                                                              (0x000000024103ffU)

/* Properties of firewall at slave: TIMER2_CFG */
#define CSL_STD_FW_TIMER2_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER2_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER2_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER2_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER2_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER2_CFG_CFG_START                                                            (0x00000002420000U)
#define CSL_STD_FW_TIMER2_CFG_CFG_END                                                              (0x000000024203ffU)

/* Properties of firewall at slave: TIMER3_CFG */
#define CSL_STD_FW_TIMER3_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER3_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER3_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER3_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER3_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER3_CFG_CFG_START                                                            (0x00000002430000U)
#define CSL_STD_FW_TIMER3_CFG_CFG_END                                                              (0x000000024303ffU)

/* Properties of firewall at slave: TIMER4_CFG */
#define CSL_STD_FW_TIMER4_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER4_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER4_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER4_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER4_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER4_CFG_CFG_START                                                            (0x00000002440000U)
#define CSL_STD_FW_TIMER4_CFG_CFG_END                                                              (0x000000024403ffU)

/* Properties of firewall at slave: TIMER5_CFG */
#define CSL_STD_FW_TIMER5_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER5_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER5_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER5_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER5_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER5_CFG_CFG_START                                                            (0x00000002450000U)
#define CSL_STD_FW_TIMER5_CFG_CFG_END                                                              (0x000000024503ffU)

/* Properties of firewall at slave: TIMER6_CFG */
#define CSL_STD_FW_TIMER6_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER6_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER6_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER6_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER6_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER6_CFG_CFG_START                                                            (0x00000002460000U)
#define CSL_STD_FW_TIMER6_CFG_CFG_END                                                              (0x000000024603ffU)

/* Properties of firewall at slave: TIMER7_CFG */
#define CSL_STD_FW_TIMER7_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER7_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER7_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER7_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER7_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER7_CFG_CFG_START                                                            (0x00000002470000U)
#define CSL_STD_FW_TIMER7_CFG_CFG_END                                                              (0x000000024703ffU)

/* Properties of firewall at slave: RTI0_CFG */
#define CSL_STD_FW_RTI0_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI0_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI0_CFG_CFG_START                                                              (0x0000000e000000U)
#define CSL_STD_FW_RTI0_CFG_CFG_END                                                                (0x0000000e0000ffU)

/* Properties of firewall at slave: RTI1_CFG */
#define CSL_STD_FW_RTI1_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI1_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI1_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI1_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI1_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI1_CFG_CFG_START                                                              (0x0000000e010000U)
#define CSL_STD_FW_RTI1_CFG_CFG_END                                                                (0x0000000e0100ffU)

/* Properties of firewall at slave: RTI2_CFG */
#define CSL_STD_FW_RTI2_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI2_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI2_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI2_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI2_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI2_CFG_CFG_START                                                              (0x0000000e020000U)
#define CSL_STD_FW_RTI2_CFG_CFG_END                                                                (0x0000000e0200ffU)

/* Properties of firewall at slave: RTI3_CFG */
#define CSL_STD_FW_RTI3_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI3_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI3_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI3_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI3_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI3_CFG_CFG_START                                                              (0x0000000e030000U)
#define CSL_STD_FW_RTI3_CFG_CFG_END                                                                (0x0000000e0300ffU)

/* Properties of firewall at slave: RTI4_CFG */
#define CSL_STD_FW_RTI4_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI4_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI4_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI4_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI4_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI4_CFG_CFG_START                                                              (0x0000000e040000U)
#define CSL_STD_FW_RTI4_CFG_CFG_END                                                                (0x0000000e0400ffU)

/* Properties of firewall at slave: DDR32SS0_REGS_SS_CFG_SSCFG */
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_ID                                                   (10U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_REGS_SS_CFG_SSCFG_START                              (0x0000000f300000U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_REGS_SS_CFG_SSCFG_END                                (0x0000000f3001ffU)

/* Properties of firewall at slave: DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG */
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_ID                                          (10U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_MMR_BASE                                    (0x00000045002800U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_NUM_REGIONS                                 (16U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_CTLPHY_WRAP_CTL_CFG_CTLCFG_START            (0x0000000f308000U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_CTLPHY_WRAP_CTL_CFG_CTLCFG_END              (0x0000000f30ffffU)

/* Properties of firewall at slave: USB0_MMR_MMRVBP_USB2SS_CFG */
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_ID                                                   (10U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_MMR_MMRVBP_USB2SS_CFG_START                          (0x0000000f900000U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_MMR_MMRVBP_USB2SS_CFG_END                            (0x0000000f9007ffU)

/* Properties of firewall at slave: USB0_PHY2 */
#define CSL_STD_FW_USB0_PHY2_ID                                                                    (10U)
#define CSL_STD_FW_USB0_PHY2_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_PHY2_MMR_BASE                                                              (0x00000045002800U)
#define CSL_STD_FW_USB0_PHY2_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_USB0_PHY2_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_USB0_PHY2_PHY2_START                                                            (0x0000000f908000U)
#define CSL_STD_FW_USB0_PHY2_PHY2_END                                                              (0x0000000f9083ffU)

/* Properties of firewall at slave: USB1_MMR_MMRVBP_USB2SS_CFG */
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_ID                                                   (10U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_MMR_MMRVBP_USB2SS_CFG_START                          (0x0000000f910000U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_MMR_MMRVBP_USB2SS_CFG_END                            (0x0000000f9107ffU)

/* Properties of firewall at slave: USB1_PHY2 */
#define CSL_STD_FW_USB1_PHY2_ID                                                                    (10U)
#define CSL_STD_FW_USB1_PHY2_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_PHY2_MMR_BASE                                                              (0x00000045002800U)
#define CSL_STD_FW_USB1_PHY2_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_USB1_PHY2_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_USB1_PHY2_PHY2_START                                                            (0x0000000f918000U)
#define CSL_STD_FW_USB1_PHY2_PHY2_END                                                              (0x0000000f9183ffU)

/* Properties of firewall at slave: USB0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_ID                                                       (10U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_MMR_BASE                                                 (0x00000045002800U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_NUM_REGIONS                                              (16U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_ECC_AGGR_START                                           (0x0000000f980000U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_ECC_AGGR_END                                             (0x0000000f9803ffU)

/* Properties of firewall at slave: USB1_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_ID                                                       (10U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_MMR_BASE                                                 (0x00000045002800U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_NUM_REGIONS                                              (16U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_ECC_AGGR_START                                           (0x0000000f990000U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_ECC_AGGR_END                                             (0x0000000f9903ffU)

/* Properties of firewall at slave: JPGENC0_CORE_REGS */
#define CSL_STD_FW_JPGENC0_CORE_REGS_ID                                                            (10U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_TYPE                                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_JPGENC0_CORE_REGS_MMR_BASE                                                      (0x00000045002800U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_NUM_REGIONS                                                   (16U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_NUM_PRIV_IDS_PER_REGION                                       (3U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_CORE_START                                                    (0x0000000fd20000U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_CORE_END                                                      (0x0000000fd200ffU)

/* Properties of firewall at slave: JPGENC0_CORE_MMU_REGS */
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_ID                                                        (10U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_MMR_BASE                                                  (0x00000045002800U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_CORE_MMU_START                                            (0x0000000fd20200U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_CORE_MMU_END                                              (0x0000000fd203ffU)

/* Properties of firewall at slave: ELM0_MEM */
#define CSL_STD_FW_ELM0_MEM_ID                                                                     (10U)
#define CSL_STD_FW_ELM0_MEM_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_ELM0_MEM_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_ELM0_MEM_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_ELM0_MEM_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_ELM0_MEM_START                                                                  (0x00000025010000U)
#define CSL_STD_FW_ELM0_MEM_END                                                                    (0x00000025010fffU)

/* Properties of firewall at slave: DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS */
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_ID                                 (10U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_MMR_BASE                           (0x00000045002800U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_NUM_REGIONS                        (16U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_START (0x00000030110000U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_END (0x00000030110fffU)

/* Properties of firewall at slave: DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS */
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_ID                                           (10U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_MMR_BASE                                     (0x00000045002800U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_NUM_REGIONS                                  (16U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_MMR_SLV_K3_DPHY_WRAP_START                   (0x00000030111000U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_MMR_SLV_K3_DPHY_WRAP_END                     (0x000000301110ffU)

/* Properties of firewall at slave: CODEC0_VPU_REGS */
#define CSL_STD_FW_CODEC0_VPU_REGS_ID                                                              (10U)
#define CSL_STD_FW_CODEC0_VPU_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_CODEC0_VPU_REGS_MMR_BASE                                                        (0x00000045002800U)
#define CSL_STD_FW_CODEC0_VPU_REGS_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_CODEC0_VPU_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_CODEC0_VPU_REGS_VPU_START                                                       (0x00000030210000U)
#define CSL_STD_FW_CODEC0_VPU_REGS_VPU_END                                                         (0x0000003021ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_CFG_MMR */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_ID                                                  (10U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_MMR_BASE                                            (0x00000045002800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_NUM_REGIONS                                         (16U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_START                                               (0x00000030240000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_END                                                 (0x0000003024ffffU)

/* Properties of firewall at slave: VPAC_RSWS_BW_LIMITER7_REGS */
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_ID                                                   (10U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_REGS_START                                           (0x00000030400000U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_REGS_END                                             (0x00000030400fffU)

/* Properties of firewall at slave: CODEC_WS_BW_LIMITER3_REGS */
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_ID                                                    (10U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_MMR_BASE                                              (0x00000045002800U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_REGS_START                                            (0x00000030401000U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_REGS_END                                              (0x00000030401fffU)

/* Properties of firewall at slave: A53_WS_BW_LIMITER1_REGS */
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_ID                                                      (10U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_MMR_BASE                                                (0x00000045002800U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_NUM_REGIONS                                             (16U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_REGS_START                                              (0x00000030402000U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_REGS_END                                                (0x00000030402fffU)

/* Properties of firewall at slave: A53_RS_BW_LIMITER0_REGS */
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_ID                                                      (10U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_MMR_BASE                                                (0x00000045002800U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_NUM_REGIONS                                             (16U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_REGS_START                                              (0x00000030403000U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_REGS_END                                                (0x00000030403fffU)

/* Properties of firewall at slave: JPGENC_RS_BW_LIMITER4_REGS */
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_ID                                                   (10U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_REGS_START                                           (0x00000030404000U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_REGS_END                                             (0x00000030404fffU)

/* Properties of firewall at slave: JPGENC_WS_BW_LIMITER5_REGS */
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_ID                                                   (10U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_REGS_START                                           (0x00000030405000U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_REGS_END                                             (0x00000030405fffU)

/* Properties of firewall at slave: C7XV_RSWS_BS_LIMITER6_REGS */
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_ID                                                   (10U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_REGS_START                                           (0x00000030406000U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_REGS_END                                             (0x00000030406fffU)

/* Properties of firewall at slave: VPAC_RSWS_BW_LIMITER8_REGS */
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_ID                                                   (10U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_REGS_START                                           (0x00000030407000U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_REGS_END                                             (0x00000030407fffU)

/* Properties of firewall at slave: CODEC_RS_BW_LIMITER2_REGS */
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_ID                                                    (10U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_MMR_BASE                                              (0x00000045002800U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_REGS_START                                            (0x00000030408000U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_REGS_END                                              (0x00000030408fffU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_ID                               (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_START (0x00000031000000U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_END (0x0000003100001fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_ID                              (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_START (0x00000031000020U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_END (0x0000003100005fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_ID                              (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_START (0x00000031000420U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_END (0x0000003100043fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_ID                           (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_TYPE                         (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_MMR_BASE                     (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_NUM_REGIONS                  (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_NUM_PRIV_IDS_PER_REGION      (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_START (0x00000031000440U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_END (0x0000003100045fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_ID                              (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_START (0x00000031000460U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_END (0x0000003100049fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_ID                                (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_TYPE                              (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_MMR_BASE                          (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_NUM_REGIONS                       (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_NUM_PRIV_IDS_PER_REGION           (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_START (0x00000031000560U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_END (0x0000003100075fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_ID                            (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_TYPE                          (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_MMR_BASE                      (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_NUM_REGIONS                   (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_NUM_PRIV_IDS_PER_REGION       (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_START (0x00000031000960U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_END (0x0000003100096fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2 */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_ID                        (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_START (0x00000031000970U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_END (0x0000003100097fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3 */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_ID                        (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_START (0x00000031000980U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_END (0x0000003100099fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_ID                               (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_START (0x0000003100c100U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_END (0x0000003100c8ffU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_ID                               (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_START (0x0000003100c700U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_END (0x0000003100ceffU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_ID                              (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_START (0x0000003100d000U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_END (0x0000003100d07fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_ID                             (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_MMR_BASE                       (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_NUM_REGIONS                    (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_START (0x0000003100d800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_END (0x0000003100d9ffU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0 */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_ID                        (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_START (0x00000031040000U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_END (0x0000003104ffffU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_ID                               (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_START (0x00000031100000U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_END (0x0000003110001fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_ID                              (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_START (0x00000031100020U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_END (0x0000003110005fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_ID                              (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_START (0x00000031100420U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_END (0x0000003110043fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_ID                           (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_TYPE                         (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_MMR_BASE                     (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_NUM_REGIONS                  (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_NUM_PRIV_IDS_PER_REGION      (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_START (0x00000031100440U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_END (0x0000003110045fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_ID                              (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_START (0x00000031100460U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_END (0x0000003110049fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_ID                                (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_TYPE                              (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_MMR_BASE                          (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_NUM_REGIONS                       (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_NUM_PRIV_IDS_PER_REGION           (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_START (0x00000031100560U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_END (0x0000003110075fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_ID                            (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_TYPE                          (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_MMR_BASE                      (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_NUM_REGIONS                   (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_NUM_PRIV_IDS_PER_REGION       (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_START (0x00000031100960U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_END (0x0000003110096fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2 */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_ID                        (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_START (0x00000031100970U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_END (0x0000003110097fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3 */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_ID                        (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_START (0x00000031100980U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_END (0x0000003110099fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_ID                               (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_START (0x0000003110c100U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_END (0x0000003110c8ffU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_ID                               (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_START (0x0000003110c700U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_END (0x0000003110ceffU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_ID                              (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_START (0x0000003110d000U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_END (0x0000003110d07fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_ID                             (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_MMR_BASE                       (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_NUM_REGIONS                    (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_START (0x0000003110d800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_END (0x0000003110d9ffU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0 */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_ID                        (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_START (0x00000031140000U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_END (0x0000003114ffffU)

/* Properties of firewall at slave: PBIST0_MEM */
#define CSL_STD_FW_PBIST0_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST0_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST0_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST0_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST0_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST0_MEM_START                                                                (0x0000003f110000U)
#define CSL_STD_FW_PBIST0_MEM_END                                                                  (0x0000003f1103ffU)

/* Properties of firewall at slave: CBASS_MCASP0_ERR_REGS */
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_ID                                                        (11U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_MMR_BASE                                                  (0x00000045002c00U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_ERR_START                                                 (0x00000000240000U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_ERR_END                                                   (0x000000002403ffU)

/* Properties of firewall at slave: CPSW0_CPSW_NUSS_VBUSP_ECC */
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_ID                                                    (11U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_MMR_BASE                                              (0x00000045002c00U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_ECC_START                                             (0x00000000704000U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_ECC_END                                               (0x000000007043ffU)

/* Properties of firewall at slave: MMCSD0_ECC_AGGR_RXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_START                             (0x00000000706000U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_END                               (0x000000007063ffU)

/* Properties of firewall at slave: MMCSD0_ECC_AGGR_TXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_START                             (0x00000000707000U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_END                               (0x000000007073ffU)

/* Properties of firewall at slave: MMCSD1_ECC_AGGR_RXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_START                             (0x00000000708000U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_END                               (0x000000007083ffU)

/* Properties of firewall at slave: MMCSD1_ECC_AGGR_TXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_START                             (0x00000000709000U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_END                               (0x000000007093ffU)

/* Properties of firewall at slave: MMCSD2_ECC_AGGR_TXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_START                             (0x0000000070a000U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_END                               (0x0000000070a3ffU)

/* Properties of firewall at slave: MMCSD2_ECC_AGGR_RXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_START                             (0x0000000070b000U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_END                               (0x0000000070b3ffU)

/* Properties of firewall at slave: CSI_RX_IF0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_ID                                                 (11U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_ECC_AGGR_CFG_START                                 (0x0000000070e000U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_ECC_AGGR_CFG_END                                   (0x0000000070e3ffU)

/* Properties of firewall at slave: MSRAM_64K0_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_ID                                                 (11U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                                (0x00000000710000U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                                  (0x000000007103ffU)

/* Properties of firewall at slave: FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_ID                 (11U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_TYPE               (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE           (0x00000045002c00U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS        (16U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI0_ECC_AGGR_START (0x00000000716000U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI0_ECC_AGGR_END (0x000000007163ffU)

/* Properties of firewall at slave: GICSS0_GIC_TRANSLATER_REGS */
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_ID                                                   (11U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_MMR_BASE                                             (0x00000045002c00U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_GIC_TRANSLATER_START                                 (0x00000001000000U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_GIC_TRANSLATER_END                                   (0x000000013fffffU)

/* Properties of firewall at slave: GICSS0_GIC_REGS */
#define CSL_STD_FW_GICSS0_GIC_REGS_ID                                                              (11U)
#define CSL_STD_FW_GICSS0_GIC_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_GICSS0_GIC_REGS_MMR_BASE                                                        (0x00000045002c00U)
#define CSL_STD_FW_GICSS0_GIC_REGS_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_GICSS0_GIC_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_GICSS0_GIC_REGS_GIC_START                                                       (0x00000001800000U)
#define CSL_STD_FW_GICSS0_GIC_REGS_GIC_END                                                         (0x000000018fffffU)

/* Properties of firewall at slave: CPSW0_CPSW_NUSS_VBUSP */
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ID                                                        (11U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_MMR_BASE                                                  (0x00000045002c00U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUSS_START                                                (0x00000008000000U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUSS_END                                                  (0x000000081fffffU)

/* Properties of firewall at slave: MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG */
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_ID                                              (11U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_MMR_BASE                                        (0x00000045002c00U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_REGIONS                                     (16U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_START                                   (0x0000000fa00000U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_END                                     (0x0000000fa00fffU)

/* Properties of firewall at slave: MMCSD1_REGS_SS_CFG_SSCFG */
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_ID                                                     (11U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_MMR_BASE                                               (0x00000045002c00U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_SS_CFG_START                                           (0x0000000fa08000U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_SS_CFG_END                                             (0x0000000fa083ffU)

/* Properties of firewall at slave: MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG */
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_ID                                              (11U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_MMR_BASE                                        (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_REGIONS                                     (16U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_START                                   (0x0000000fa10000U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_END                                     (0x0000000fa10fffU)

/* Properties of firewall at slave: MMCSD0_REGS_SS_CFG_SSCFG */
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_ID                                                     (11U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_MMR_BASE                                               (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_SS_CFG_START                                           (0x0000000fa18000U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_SS_CFG_END                                             (0x0000000fa183ffU)

/* Properties of firewall at slave: MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG */
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_ID                                              (11U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_MMR_BASE                                        (0x00000045002c00U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_REGIONS                                     (16U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_START                                   (0x0000000fa20000U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_END                                     (0x0000000fa20fffU)

/* Properties of firewall at slave: MMCSD2_REGS_SS_CFG_SSCFG */
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_ID                                                     (11U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_MMR_BASE                                               (0x00000045002c00U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_SS_CFG_START                                           (0x0000000fa28000U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_SS_CFG_END                                             (0x0000000fa283ffU)

/* Properties of firewall at slave: FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS */
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_ID                                         (11U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_MMR_BASE                                   (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_CFG_START                                  (0x0000000fc00000U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_CFG_END                                    (0x0000000fc000ffU)

/* Properties of firewall at slave: FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS */
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_ID                                   (11U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_MMR_BASE                             (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_NUM_REGIONS                          (16U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_FSAS_CFG_START                       (0x0000000fc10000U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_FSAS_CFG_END                         (0x0000000fc100ffU)

/* Properties of firewall at slave: FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS */
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_ID                                (11U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_TYPE                              (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_MMR_BASE                          (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_NUM_REGIONS                       (16U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_NUM_PRIV_IDS_PER_REGION           (3U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_OTFA_CFG_START                    (0x0000000fc20000U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_OTFA_CFG_END                      (0x0000000fc20fffU)

/* Properties of firewall at slave: FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS */
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_ID (11U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_MMR_BASE (0x00000045002c00U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_REGIONS (16U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI0_CTRL_START (0x0000000fc40000U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI0_CTRL_END (0x0000000fc400ffU)

/* Properties of firewall at slave: FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS */
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_ID                             (11U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_MMR_BASE                       (0x00000045002c00U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_REGIONS                    (16U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI0_SS_CFG_START             (0x0000000fc44000U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI0_SS_CFG_END               (0x0000000fc441ffU)

/* Properties of firewall at slave: CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG */
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_ID                                         (11U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_MMR_BASE                                   (0x00000045002c00U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_NUM_REGIONS                                (16U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_CP_INTD_CFG_INTD_CFG_START                 (0x00000030100000U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_CP_INTD_CFG_INTD_CFG_END                   (0x00000030100fffU)

/* Properties of firewall at slave: CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS */
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_ID                               (11U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_MMR_BASE                         (0x00000045002c00U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_NUM_REGIONS                      (16U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_START (0x00000030101000U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_END (0x00000030101fffU)

/* Properties of firewall at slave: CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS */
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_ID                                   (11U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_MMR_BASE                             (0x00000045002c00U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_NUM_REGIONS                          (16U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_RX_SHIM_VBUSP_MMR_CSI2RXIF_START     (0x00000030102000U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_RX_SHIM_VBUSP_MMR_CSI2RXIF_END       (0x00000030102fffU)

/* Properties of firewall at slave: DSS0_COMMON */
#define CSL_STD_FW_DSS0_COMMON_ID                                                                  (11U)
#define CSL_STD_FW_DSS0_COMMON_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_COMMON_MMR_BASE                                                            (0x00000045002c00U)
#define CSL_STD_FW_DSS0_COMMON_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_DSS0_COMMON_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_DSS0_COMMON_COMMON_START                                                        (0x00000030200000U)
#define CSL_STD_FW_DSS0_COMMON_COMMON_END                                                          (0x00000030200fffU)

/* Properties of firewall at slave: DSS0_COMMON1 */
#define CSL_STD_FW_DSS0_COMMON1_ID                                                                 (11U)
#define CSL_STD_FW_DSS0_COMMON1_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_COMMON1_MMR_BASE                                                           (0x00000045002c00U)
#define CSL_STD_FW_DSS0_COMMON1_NUM_REGIONS                                                        (16U)
#define CSL_STD_FW_DSS0_COMMON1_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_DSS0_COMMON1_COMMON1_START                                                      (0x00000030201000U)
#define CSL_STD_FW_DSS0_COMMON1_COMMON1_END                                                        (0x00000030201fffU)

/* Properties of firewall at slave: DSS0_VIDL1 */
#define CSL_STD_FW_DSS0_VIDL1_ID                                                                   (11U)
#define CSL_STD_FW_DSS0_VIDL1_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_VIDL1_MMR_BASE                                                             (0x00000045002c00U)
#define CSL_STD_FW_DSS0_VIDL1_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_DSS0_VIDL1_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_DSS0_VIDL1_VIDL1_START                                                          (0x00000030202000U)
#define CSL_STD_FW_DSS0_VIDL1_VIDL1_END                                                            (0x00000030202fffU)

/* Properties of firewall at slave: DSS0_VID */
#define CSL_STD_FW_DSS0_VID_ID                                                                     (11U)
#define CSL_STD_FW_DSS0_VID_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_VID_MMR_BASE                                                               (0x00000045002c00U)
#define CSL_STD_FW_DSS0_VID_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DSS0_VID_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DSS0_VID_VID_START                                                              (0x00000030206000U)
#define CSL_STD_FW_DSS0_VID_VID_END                                                                (0x00000030206fffU)

/* Properties of firewall at slave: DSS0_OVR1 */
#define CSL_STD_FW_DSS0_OVR1_ID                                                                    (11U)
#define CSL_STD_FW_DSS0_OVR1_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_OVR1_MMR_BASE                                                              (0x00000045002c00U)
#define CSL_STD_FW_DSS0_OVR1_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_DSS0_OVR1_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_DSS0_OVR1_OVR1_START                                                            (0x00000030207000U)
#define CSL_STD_FW_DSS0_OVR1_OVR1_END                                                              (0x00000030207fffU)

/* Properties of firewall at slave: DSS0_OVR2 */
#define CSL_STD_FW_DSS0_OVR2_ID                                                                    (11U)
#define CSL_STD_FW_DSS0_OVR2_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_OVR2_MMR_BASE                                                              (0x00000045002c00U)
#define CSL_STD_FW_DSS0_OVR2_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_DSS0_OVR2_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_DSS0_OVR2_OVR2_START                                                            (0x00000030208000U)
#define CSL_STD_FW_DSS0_OVR2_OVR2_END                                                              (0x00000030208fffU)

/* Properties of firewall at slave: DSS0_VP1 */
#define CSL_STD_FW_DSS0_VP1_ID                                                                     (11U)
#define CSL_STD_FW_DSS0_VP1_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_VP1_MMR_BASE                                                               (0x00000045002c00U)
#define CSL_STD_FW_DSS0_VP1_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DSS0_VP1_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DSS0_VP1_VP1_START                                                              (0x0000003020a000U)
#define CSL_STD_FW_DSS0_VP1_VP1_END                                                                (0x0000003020afffU)

/* Properties of firewall at slave: DSS0_VP2 */
#define CSL_STD_FW_DSS0_VP2_ID                                                                     (11U)
#define CSL_STD_FW_DSS0_VP2_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_VP2_MMR_BASE                                                               (0x00000045002c00U)
#define CSL_STD_FW_DSS0_VP2_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DSS0_VP2_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DSS0_VP2_VP2_START                                                              (0x0000003020b000U)
#define CSL_STD_FW_DSS0_VP2_VP2_END                                                                (0x0000003020bfffU)

/* Properties of firewall at slave: CBASS0_ERR_REGS */
#define CSL_STD_FW_CBASS0_ERR_REGS_ID                                                              (11U)
#define CSL_STD_FW_CBASS0_ERR_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS0_ERR_REGS_MMR_BASE                                                        (0x00000045002c00U)
#define CSL_STD_FW_CBASS0_ERR_REGS_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_CBASS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_CBASS0_ERR_REGS_ERR_START                                                       (0x0000003a000000U)
#define CSL_STD_FW_CBASS0_ERR_REGS_ERR_END                                                         (0x0000003a0003ffU)

/* Properties of firewall at slave: GICSS0_REGS */
#define CSL_STD_FW_GICSS0_REGS_ID                                                                  (11U)
#define CSL_STD_FW_GICSS0_REGS_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_GICSS0_REGS_MMR_BASE                                                            (0x00000045002c00U)
#define CSL_STD_FW_GICSS0_REGS_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_GICSS0_REGS_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_GICSS0_REGS_REGS_START                                                          (0x0000003f004000U)
#define CSL_STD_FW_GICSS0_REGS_REGS_END                                                            (0x0000003f0043ffU)

/* Properties of firewall at slave: MCRC64_0_MCRC64_REGS */
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_ID                                                         (13U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_MMR_BASE                                                   (0x00000045003400U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_REGS_START                                                 (0x00000030300000U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_REGS_END                                                   (0x00000030300fffU)

/* Properties of firewall at slave: MSRAM_64K0_RAM */
#define CSL_STD_FW_MSRAM_64K0_RAM_ID                                                               (15U)
#define CSL_STD_FW_MSRAM_64K0_RAM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_64K0_RAM_MMR_BASE                                                         (0x00000045003c00U)
#define CSL_STD_FW_MSRAM_64K0_RAM_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_MSRAM_64K0_RAM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MSRAM_64K0_RAM_RAM_START                                                        (0x00000043c40000U)
#define CSL_STD_FW_MSRAM_64K0_RAM_RAM_END                                                          (0x00000043c4ffffU)

/* Properties of firewall at slave: WKUP_R5FSS0_CORE0_ICACHE0 */
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_ID                                                    (32U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_MMR_BASE                                              (0x00000045008000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_START                                    (0x00000074000000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_END                                      (0x000000747fffffU)

/* Properties of firewall at slave: WKUP_R5FSS0_CORE0_DCACHE0 */
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_ID                                                    (32U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_MMR_BASE                                              (0x00000045008000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_START                                    (0x00000074800000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_END                                      (0x00000074ffffffU)

/* Properties of firewall at slave: WKUP_R5FSS0_CORE0_ATCM0 */
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_ID                                                      (32U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_MMR_BASE                                                (0x00000045008000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_CORE0_ATCM_START                                        (0x00000078000000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_CORE0_ATCM_END                                          (0x00000078007fffU)

/* Properties of firewall at slave: WKUP_R5FSS0_CORE0_BTCM0 */
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_ID                                                      (32U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_MMR_BASE                                                (0x00000045008000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_CORE0_BTCM_START                                        (0x00000078100000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_CORE0_BTCM_END                                          (0x00000078107fffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG0 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_GTC_CFG0_START                                               (0x00000000a80000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_GTC_CFG0_END                                                 (0x00000000a803ffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG1 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_GTC_CFG1_START                                               (0x00000000a90000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_GTC_CFG1_END                                                 (0x00000000a93fffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG2 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_GTC_CFG2_START                                               (0x00000000aa0000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_GTC_CFG2_END                                                 (0x00000000aa3fffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG3 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_GTC_CFG3_START                                               (0x00000000ab0000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_GTC_CFG3_END                                                 (0x00000000ab3fffU)

/* Properties of firewall at slave: WKUP_VTM0_MMR_VBUSP_CFG1 */
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_ID                                                     (34U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_MMR_BASE                                               (0x00000045008800U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_MMR_VBUSP_CFG1_START                                   (0x00000000b00000U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_MMR_VBUSP_CFG1_END                                     (0x00000000b003ffU)

/* Properties of firewall at slave: WKUP_VTM0_MMR_VBUSP_CFG2 */
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_ID                                                     (34U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_MMR_BASE                                               (0x00000045008800U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_MMR_VBUSP_CFG2_START                                   (0x00000000b01000U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_MMR_VBUSP_CFG2_END                                     (0x00000000b013ffU)

/* Properties of firewall at slave: WKUP_VTM0_ECCAGGR_CFG_REGS */
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_ID                                                  (34U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_MMR_BASE                                            (0x00000045008800U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_NUM_REGIONS                                         (16U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_START                                   (0x00000000b02000U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_END                                     (0x00000000b023ffU)

/* Properties of firewall at slave: WKUP_RTI0_CFG */
#define CSL_STD_FW_WKUP_RTI0_CFG_ID                                                                (34U)
#define CSL_STD_FW_WKUP_RTI0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_RTI0_CFG_MMR_BASE                                                          (0x00000045008800U)
#define CSL_STD_FW_WKUP_RTI0_CFG_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_WKUP_RTI0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_RTI0_CFG_CFG_START                                                         (0x0000002b000000U)
#define CSL_STD_FW_WKUP_RTI0_CFG_CFG_END                                                           (0x0000002b0000ffU)

/* Properties of firewall at slave: WKUP_RTCSS0_RTC_REGS */
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_ID                                                         (34U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_MMR_BASE                                                   (0x00000045008800U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_NUM_REGIONS                                                (16U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_RTC_START                                                  (0x0000002b1f0000U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_RTC_END                                                    (0x0000002b1f007fU)

/* Properties of firewall at slave: WKUP_I2C0_CFG */
#define CSL_STD_FW_WKUP_I2C0_CFG_ID                                                                (34U)
#define CSL_STD_FW_WKUP_I2C0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_I2C0_CFG_MMR_BASE                                                          (0x00000045008800U)
#define CSL_STD_FW_WKUP_I2C0_CFG_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_WKUP_I2C0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_I2C0_CFG_CFG_START                                                         (0x0000002b200000U)
#define CSL_STD_FW_WKUP_I2C0_CFG_CFG_END                                                           (0x0000002b2000ffU)

/* Properties of firewall at slave: WKUP_UART0_MEM */
#define CSL_STD_FW_WKUP_UART0_MEM_ID                                                               (34U)
#define CSL_STD_FW_WKUP_UART0_MEM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_UART0_MEM_MMR_BASE                                                         (0x00000045008800U)
#define CSL_STD_FW_WKUP_UART0_MEM_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_WKUP_UART0_MEM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_WKUP_UART0_MEM_START                                                            (0x0000002b300000U)
#define CSL_STD_FW_WKUP_UART0_MEM_END                                                              (0x0000002b3001ffU)

/* Properties of firewall at slave: WKUP_CBASS0_ERR_REGS */
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_ID                                                         (34U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_MMR_BASE                                                   (0x00000045008800U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_NUM_REGIONS                                                (16U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_ERR_START                                                  (0x0000002b400000U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_ERR_END                                                    (0x0000002b4003ffU)

/* Properties of firewall at slave: WKUP_PBIST0_MEM */
#define CSL_STD_FW_WKUP_PBIST0_MEM_ID                                                              (34U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PBIST0_MEM_MMR_BASE                                                        (0x00000045008800U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_START                                                           (0x0000002b500000U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_END                                                             (0x0000002b5003ffU)

/* Properties of firewall at slave: WKUP_PBIST1_MEM */
#define CSL_STD_FW_WKUP_PBIST1_MEM_ID                                                              (34U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PBIST1_MEM_MMR_BASE                                                        (0x00000045008800U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_START                                                           (0x0000002b510000U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_END                                                             (0x0000002b5103ffU)

/* Properties of firewall at slave: WKUP_ECC_AGGR0_REGS */
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_ID                                                          (34U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_MMR_BASE                                                    (0x00000045008800U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_ECC_AGGR_START                                              (0x0000002b600000U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_ECC_AGGR_END                                                (0x0000002b6003ffU)

/* Properties of firewall at slave: WKUP_ECC_AGGR1_REGS */
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_ID                                                          (34U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_MMR_BASE                                                    (0x00000045008800U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_ECC_AGGR_START                                              (0x0000002b601000U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_ECC_AGGR_END                                                (0x0000002b6013ffU)

/* Properties of firewall at slave: WKUP_PSRAMECC_8K0_REGS */
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_ID                                                       (34U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_MMR_BASE                                                 (0x00000045008800U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_NUM_REGIONS                                              (16U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_REGS_START                                               (0x0000002b608000U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_REGS_END                                                 (0x0000002b6083ffU)

/* Properties of firewall at slave: WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS */
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_ID                                      (34U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_MMR_BASE                                (0x00000045008800U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_REGIONS                             (16U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_START               (0x0000003c018000U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_END                 (0x0000003c0180ffU)

/* Properties of firewall at slave: WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_ID                                   (34U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_MMR_BASE                             (0x00000045008800U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_NUM_REGIONS                          (16U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_START                 (0x0000003f00d000U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_END                   (0x0000003f00d3ffU)

/* Properties of firewall at slave: WKUP_PSRAMECC_8K0_RAM */
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_ID                                                        (34U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_MMR_BASE                                                  (0x00000045008800U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_RAM_START                                                 (0x00000041880000U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_RAM_END                                                   (0x00000041887fffU)

/* Properties of firewall at slave: WKUP_CTRL_MMR0_CFG0 */
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_ID                                                          (34U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_MMR_BASE                                                    (0x00000045008800U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_CFG0_START                                                  (0x00000043000000U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_CFG0_END                                                    (0x0000004301ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_ID                             (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_MMR_BASE                       (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_NUM_REGIONS                    (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_START (0x0000002b604000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_END (0x0000002b6043ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_ID      (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_TYPE    (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_START (0x0000002b605000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_END (0x0000002b6053ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_ID       (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_TYPE     (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_START (0x0000002b607000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_END (0x0000002b6073ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_ID                    (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_TYPE                  (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_MMR_BASE              (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_NUM_REGIONS           (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_START (0x0000002c000000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_END (0x0000002c0003ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_ID                         (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_TYPE                       (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_MMR_BASE                   (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_NUM_REGIONS                (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_NUM_PRIV_IDS_PER_REGION    (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_START (0x0000002c002000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_END (0x0000002c003fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_ID                          (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_TYPE                        (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_MMR_BASE                    (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_NUM_REGIONS                 (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_NUM_PRIV_IDS_PER_REGION     (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_IVPAC_TOP_0_CFG_SLV_CP_INTD_CFG_INTD_CFG_START (0x0000002c004000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_IVPAC_TOP_0_CFG_SLV_CP_INTD_CFG_INTD_CFG_END (0x0000002c004fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_ID                                   (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_MMR_BASE                             (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_NUM_REGIONS                          (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_START (0x0000002c010000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_END  (0x0000002c01ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_ID               (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_TYPE             (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_MMR_BASE         (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_NUM_REGIONS      (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_START (0x0000002c020000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_END (0x0000002c0203ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_ID     (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_TYPE   (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_START (0x0000002c020400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_END (0x0000002c0205ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_START (0x0000002c020800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_END (0x0000002c020fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_START (0x0000002c021000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_END (0x0000002c0217ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_START (0x0000002c022000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_END (0x0000002c023fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_ID   (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_START (0x0000002c028000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_END (0x0000002c02ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_START (0x0000002c030000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_END (0x0000002c037fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_ID                    (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_TYPE                  (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_MMR_BASE              (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_NUM_REGIONS           (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_START (0x0000002c0c0000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_END (0x0000002c0c07ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_ID                (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_TYPE              (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_MMR_BASE          (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_NUM_REGIONS       (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_START (0x0000002c0c0800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_END (0x0000002c0c09ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_ID       (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_TYPE     (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_START (0x0000002c100000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_END (0x0000002c1001ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_ID   (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_START (0x0000002c100400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_END (0x0000002c1005ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_START (0x0000002c103800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_END (0x0000002c103fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_START (0x0000002c104000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_END (0x0000002c107fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_START (0x0000002c108000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_END (0x0000002c10ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_START (0x0000002c110000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_END (0x0000002c1107ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_START (0x0000002c110800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_END (0x0000002c110fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_START (0x0000002c111000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_END (0x0000002c1117ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_START (0x0000002c111800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_END (0x0000002c111fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_START (0x0000002c112000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_END (0x0000002c1127ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_START (0x0000002c112800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_END (0x0000002c112fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_START (0x0000002c113000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_END (0x0000002c1137ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_START (0x0000002c113800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_END (0x0000002c113fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_START (0x0000002c118000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_END (0x0000002c1187ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_START (0x0000002c120000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_END (0x0000002c1203ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_START (0x0000002c120400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_END (0x0000002c1204ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_START (0x0000002c120800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_END (0x0000002c120fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_START (0x0000002c121000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_END (0x0000002c1217ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_START (0x0000002c121800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_END (0x0000002c121fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_START (0x0000002c122000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_END (0x0000002c1227ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_START (0x0000002c122800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_END (0x0000002c122fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_START (0x0000002c123000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_END (0x0000002c1233ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_START (0x0000002c124000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_END (0x0000002c125fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_START (0x0000002c128000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_END (0x0000002c12ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_START (0x0000002c130000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_END (0x0000002c131fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_START (0x0000002c132000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_END (0x0000002c133fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_START (0x0000002c136000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_END (0x0000002c137fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_VBUSP_NSF4VCORE_START (0x0000002c140000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_VBUSP_NSF4VCORE_END (0x0000002c1407ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_START (0x0000002c140800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_END (0x0000002c1409ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_START (0x0000002c141000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_END (0x0000002c1417ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMRRAM_VBUSP_MMR_RAM_START (0x0000002c144000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMRRAM_VBUSP_MMR_RAM_END (0x0000002c147fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_START (0x0000002c150000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_END (0x0000002c157fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_START (0x0000002c158000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_END (0x0000002c15bfffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMRCFG_CAC_START (0x0000002c180000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMRCFG_CAC_END (0x0000002c1803ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_START (0x0000002c182000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_END (0x0000002c183fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_START (0x0000002c184000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_END (0x0000002c187fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMRCFG_PCID_START (0x0000002c188000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMRCFG_PCID_END (0x0000002c1883ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_START (0x0000002c188800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_END (0x0000002c188fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_CFG_LINE_MEM_START (0x0000002c18c000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_CFG_LINE_MEM_END (0x0000002c18ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_ID              (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_TYPE            (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_MMR_BASE        (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_NUM_REGIONS     (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_START (0x0000002c200000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_END (0x0000002c203fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_ID          (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_TYPE        (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_MMR_BASE    (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_SET_START (0x0000002c204000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_SET_END (0x0000002c207fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_ID        (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_TYPE      (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_MMR_BASE  (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_QUEUE_START (0x0000002c208000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_QUEUE_END (0x0000002c20ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_ID        (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_TYPE      (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_MMR_BASE  (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHNRT_START (0x0000002c240000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHNRT_END (0x0000002c25ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_ID         (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_TYPE       (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_MMR_BASE   (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHRT_START (0x0000002c260000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHRT_END (0x0000002c27ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHATOMIC_DEBUG_START (0x0000002c280000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHATOMIC_DEBUG_END (0x0000002c29ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_ID       (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_TYPE     (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHCORE_START (0x0000002c2a0000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHCORE_END (0x0000002c2bffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_ID        (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_TYPE      (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_MMR_BASE  (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CAUSE_START (0x0000002c2e0000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CAUSE_END (0x0000002c2fffffU)

/* Properties of firewall at slave: CBASS_FW0_ERR_REGS */
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_ID                                                           (66U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_MMR_BASE                                                     (0x00000045010800U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_NUM_REGIONS                                                  (4U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_ERR_START                                                    (0x00000000220000U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_ERR_END                                                      (0x000000002203ffU)

/* Properties of firewall at slave: CBASS_IPCSS0_ERR_REGS */
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_ID                                                        (66U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_MMR_BASE                                                  (0x00000045010800U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_ERR_START                                                 (0x00000000230000U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_ERR_END                                                   (0x000000002303ffU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_ECC_REGS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_ID                                                     (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_MMR_BASE                                               (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_NUM_REGIONS                                            (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_ECC_AGGR_START                                         (0x00000000712000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_ECC_AGGR_END                                           (0x000000007123ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_0_REGS0 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_REGS0_START                                    (0x00000029000000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_REGS0_END                                      (0x000000290001ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_1_REGS1 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_REGS1_START                                    (0x00000029010000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_REGS1_END                                      (0x000000290101ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_2_REGS2 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_REGS2_START                                    (0x00000029020000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_REGS2_END                                      (0x000000290201ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_3_REGS3 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_REGS3_START                                    (0x00000029030000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_REGS3_END                                      (0x000000290301ffU)

/* Properties of firewall at slave: SPINLOCK0_REGS */
#define CSL_STD_FW_SPINLOCK0_REGS_ID                                                               (66U)
#define CSL_STD_FW_SPINLOCK0_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_SPINLOCK0_REGS_MMR_BASE                                                         (0x00000045010800U)
#define CSL_STD_FW_SPINLOCK0_REGS_NUM_REGIONS                                                      (4U)
#define CSL_STD_FW_SPINLOCK0_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_SPINLOCK0_REGS_START                                                            (0x0000002a000000U)
#define CSL_STD_FW_SPINLOCK0_REGS_END                                                              (0x0000002a007fffU)

/* Properties of firewall at slave: ECC_AGGR1_REGS */
#define CSL_STD_FW_ECC_AGGR1_REGS_ID                                                               (66U)
#define CSL_STD_FW_ECC_AGGR1_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_ECC_AGGR1_REGS_MMR_BASE                                                         (0x00000045010800U)
#define CSL_STD_FW_ECC_AGGR1_REGS_NUM_REGIONS                                                      (4U)
#define CSL_STD_FW_ECC_AGGR1_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_ECC_AGGR1_REGS_ECC_AGGR_START                                                   (0x0000003f00e000U)
#define CSL_STD_FW_ECC_AGGR1_REGS_ECC_AGGR_END                                                     (0x0000003f00e3ffU)

/* Properties of firewall at slave: ECC_AGGR0_REGS */
#define CSL_STD_FW_ECC_AGGR0_REGS_ID                                                               (66U)
#define CSL_STD_FW_ECC_AGGR0_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_ECC_AGGR0_REGS_MMR_BASE                                                         (0x00000045010800U)
#define CSL_STD_FW_ECC_AGGR0_REGS_NUM_REGIONS                                                      (4U)
#define CSL_STD_FW_ECC_AGGR0_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_ECC_AGGR0_REGS_ECC_AGGR_START                                                   (0x0000003f00f000U)
#define CSL_STD_FW_ECC_AGGR0_REGS_ECC_AGGR_END                                                     (0x0000003f00f3ffU)

/* Properties of firewall at slave: CBASS_CENTRAL2_ERR_REGS */
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_ID                                                      (66U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_MMR_BASE                                                (0x00000045010800U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_ERR_START                                               (0x0000003f012000U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_ERR_END                                                 (0x0000003f0123ffU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_MMRS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_ID                                                         (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_MMR_BASE                                                   (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_NUM_REGIONS                                                (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_REGS_START                                                 (0x00000040900000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_REGS_END                                                   (0x00000040900fffU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_MMRA_REGS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_ID                                                    (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_MMR_BASE                                              (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_MMRA_START                                            (0x00000040901000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_MMRA_END                                              (0x000000409011ffU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_ID                               (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_MMR_BASE                         (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_NUM_REGIONS                      (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_EIP_76_START                     (0x00000040910000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_EIP_76_END                       (0x0000004091007fU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_EIP_29T2_REGS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_ID                                                (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_MMR_BASE                                          (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_NUM_REGIONS                                       (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_EIP_29T2_START                                    (0x00000040920000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_EIP_29T2_END                                      (0x0000004092ffffU)

/* Properties of firewall at slave: DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA */
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_ID                                 (160U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_MMR_BASE                           (0x00000045028000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_NUM_REGIONS                        (8U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_SEC_PROXY_SRC_TARGET_DATA_START    (0x0000004d000000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_SEC_PROXY_SRC_TARGET_DATA_END      (0x0000004d07ffffU)

/* Properties of firewall at slave: SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA */
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_ID                                (161U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_TYPE                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_MMR_BASE                          (0x00000045028400U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_NUM_REGIONS                       (8U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_NUM_PRIV_IDS_PER_REGION           (3U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_SEC_PROXY_SRC_TARGET_DATA_START   (0x00000043600000U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_SEC_PROXY_SRC_TARGET_DATA_END     (0x0000004360ffffU)

/* Properties of firewall at slave: SMS0_ROM_0_IROM_SLV_ROM */
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_ID                                                      (512U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_MMR_BASE                                                (0x00000045080000U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_NUM_REGIONS                                             (2U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_NUM_PRIV_IDS_PER_REGION                                 (1U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_IROM_SLV_ROM_START                                      (0x00000000000000U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_IROM_SLV_ROM_END                                        (0x0000000003ffffU)

/* Properties of firewall at slave: SMS0_TIFS_SRAM_0_TIFS_SRAM0 */
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_ID                                                  (513U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_MMR_BASE                                            (0x00000045080400U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_TIFS_SRAM0_START                                    (0x00000044040000U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_TIFS_SRAM0_END                                      (0x0000004405ffffU)

/* Properties of firewall at slave: SMS0_TIFS_SRAM_1_TIFS_SRAM1_0 */
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_ID                                                (514U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_MMR_BASE                                          (0x00000045080800U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_NUM_REGIONS                                       (8U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_TIFS_SRAM1_0_START                                (0x00000044060000U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_TIFS_SRAM1_0_END                                  (0x00000044067fffU)

/* Properties of firewall at slave: SMS0_TIFS_SRAM_1_TIFS_SRAM1_1 */
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_ID                                                (514U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_MMR_BASE                                          (0x00000045080800U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_NUM_REGIONS                                       (8U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_TIFS_SRAM1_1_START                                (0x00000044068000U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_TIFS_SRAM1_1_END                                  (0x0000004406bfffU)

/* Properties of firewall at slave: SMS0_PWRCTRL_0_TIFS_PWR_MMR */
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_ID                                                  (528U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_MMR_BASE                                            (0x00000045084000U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_NUM_REGIONS                                         (1U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_PWR_START                                           (0x00000044130000U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_PWR_END                                             (0x000000441307ffU)

/* Properties of firewall at slave: SMS0_DMTIMER_0_TIFS_DMTIMER0 */
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_ID                                                 (536U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_MMR_BASE                                           (0x00000045086000U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_DMTIMER0_START                                     (0x00000044133000U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_DMTIMER0_END                                       (0x000000441333ffU)

/* Properties of firewall at slave: SMS0_DMTIMER_1_TIFS_DMTIMER1 */
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_ID                                                 (537U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_MMR_BASE                                           (0x00000045086400U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_DMTIMER1_START                                     (0x00000044134000U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_DMTIMER1_END                                       (0x000000441343ffU)

/* Properties of firewall at slave: SMS0_RTI_0_TIFS_RTI_MMR */
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_ID                                                      (544U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_MMR_BASE                                                (0x00000045088000U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_NUM_REGIONS                                             (1U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_RTI_START                                               (0x00000044135100U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_RTI_END                                                 (0x000000441351ffU)

/* Properties of firewall at slave: SMS0_WDTCTRL_0_TIFS_WDT_RTI */
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_ID                                                  (545U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_MMR_BASE                                            (0x00000045088400U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_NUM_REGIONS                                         (1U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_WDT_RTI_START                                       (0x00000044135000U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_WDT_RTI_END                                         (0x000000441350ffU)

/* Properties of firewall at slave: SMS0_RAT_0_TIFS_RAT_MMRS */
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_ID                                                     (552U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_MMR_BASE                                               (0x0000004508a000U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_NUM_REGIONS                                            (1U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_RAT_START                                              (0x00000044200000U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_RAT_END                                                (0x00000044200fffU)

/* Properties of firewall at slave: SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS */
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_ID                                           (562U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_MMR_BASE                                     (0x0000004508c800U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_NUM_REGIONS                                  (2U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_ECC_AGGR_START                               (0x00000043700000U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_ECC_AGGR_END                                 (0x000000437003ffU)

/* Properties of firewall at slave: SMS0_SECCTRL_0_TIFS_SEC_MMR */
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_ID                                                  (576U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_MMR_BASE                                            (0x00000045090000U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_NUM_REGIONS                                         (1U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_SEC_START                                           (0x00000044230000U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_SEC_END                                             (0x00000044230fffU)

/* Properties of firewall at slave: SMS0_DBG_AUTH_0_TIFS_DBGAUTH */
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_ID                                                 (578U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_MMR_BASE                                           (0x00000045090800U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_TIFS_DBGAUTH_START                                 (0x00000044232000U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_TIFS_DBGAUTH_END                                   (0x000000442320ffU)

/* Properties of firewall at slave: SMS0_SEC_MGR_0_TIFS_SECMGR */
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_ID                                                   (582U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_MMR_BASE                                             (0x00000045091800U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_NUM_REGIONS                                          (2U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_SECMGR_START                                         (0x00000044234000U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_SECMGR_END                                           (0x00000044237fffU)

/* Properties of firewall at slave: SMS0_DMTIMER_2_TIFS_DMTIMER2 */
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_ID                                                 (592U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_MMR_BASE                                           (0x00000045094000U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_DMTIMER2_START                                     (0x00000044238000U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_DMTIMER2_END                                       (0x000000442383ffU)

/* Properties of firewall at slave: SMS0_DMTIMER_3_TIFS_DMTIMER3 */
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_ID                                                 (593U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_MMR_BASE                                           (0x00000045094400U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_DMTIMER3_START                                     (0x00000044239000U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_DMTIMER3_END                                       (0x000000442393ffU)

/* Properties of firewall at slave: SMS0_AESEIP38T_0_TIFS_AES38T */
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_ID                                                 (602U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_MMR_BASE                                           (0x00000045096800U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_NUM_REGIONS                                        (2U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_AES_START                                          (0x0000004423c000U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_AES_END                                            (0x0000004423dfffU)

/* Properties of firewall at slave: SA3_SS0_DMSS_ECCAGGR_0_ECCAGGR_CFG_REGS */
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_ID                                     (638U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_TYPE                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_MMR_BASE                               (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_NUM_REGIONS                            (24U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                (3U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_START                      (0x00000043702000U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_END                        (0x000000437023ffU)

/* Properties of firewall at slave: SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY */
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_PSILCFG_CFG_PROXY_START                     (0x00000044801000U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_PSILCFG_CFG_PROXY_END                       (0x000000448011ffU)

/* Properties of firewall at slave: SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS */
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_ID                                             (638U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_MMR_BASE                                       (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_NUM_REGIONS                                    (24U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_PSILSS_CFG_MMRS_START                          (0x00000044802000U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_PSILSS_CFG_MMRS_END                            (0x00000044802fffU)

/* Properties of firewall at slave: SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS */
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_ID                                 (638U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_MMR_BASE                           (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_NUM_REGIONS                        (24U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_IPCSS_SEC_PROXY_CFG_MMRS_START     (0x00000044804000U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_IPCSS_SEC_PROXY_CFG_MMRS_END       (0x000000448040ffU)

/* Properties of firewall at slave: SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG */
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_ID                                     (638U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_TYPE                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_MMR_BASE                               (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_NUM_REGIONS                            (24U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_NUM_PRIV_IDS_PER_REGION                (3U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_IPCSS_RINGACC_CFG_GCFG_START           (0x00000044805000U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_IPCSS_RINGACC_CFG_GCFG_END             (0x000000448053ffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_ID                                            (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_MMR_BASE                                      (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_NUM_REGIONS                                   (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_INTAGGR_CFG_START                             (0x00000044808000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_INTAGGR_CFG_END                               (0x0000004480801fU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_ID                                           (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_MMR_BASE                                     (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_NUM_REGIONS                                  (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_INTAGGR_CFG_IMAP_START                       (0x00000044809000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_INTAGGR_CFG_IMAP_END                         (0x000000448093ffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_INTAGGR_CFG_MCAST_START                     (0x0000004480a000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_INTAGGR_CFG_MCAST_END                       (0x0000004480a3ffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_ID                                        (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_MMR_BASE                                  (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_NUM_REGIONS                               (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_INTAGGR_CFG_GCNTCFG_START                 (0x0000004480b000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_INTAGGR_CFG_GCNTCFG_END                   (0x0000004480b3ffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_ID                                           (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_MMR_BASE                                     (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_NUM_REGIONS                                  (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_INTAGGR_CFG_INTR_START                       (0x00000044810000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_INTAGGR_CFG_INTR_END                         (0x00000044817fffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_ID                                        (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_MMR_BASE                                  (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_NUM_REGIONS                               (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_INTAGGR_CFG_GCNTRTI_START                 (0x00000044820000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_INTAGGR_CFG_GCNTRTI_END                   (0x0000004483ffffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_INTAGGR_CFG_UNMAP_START                     (0x00000044840000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_INTAGGR_CFG_UNMAP_END                       (0x0000004484ffffU)

/* Properties of firewall at slave: SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG */
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_ID                                 (638U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_MMR_BASE                           (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_NUM_REGIONS                        (24U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_IPCSS_SEC_PROXY_CFG_SCFG_START     (0x00000044860000U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_IPCSS_SEC_PROXY_CFG_SCFG_END       (0x0000004487ffffU)

/* Properties of firewall at slave: SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT */
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_ID                                   (638U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_MMR_BASE                             (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_NUM_REGIONS                          (24U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_IPCSS_SEC_PROXY_CFG_RT_START         (0x00000044880000U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_IPCSS_SEC_PROXY_CFG_RT_END           (0x0000004489ffffU)

/* Properties of firewall at slave: SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG */
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_ID                                      (638U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_MMR_BASE                                (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_NUM_REGIONS                             (24U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_IPCSS_RINGACC_CFG_START                 (0x000000448c0000U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_IPCSS_RINGACC_CFG_END                   (0x000000448fffffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_ID                                             (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_MMR_BASE                                       (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_NUM_REGIONS                                    (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_PKTDMA_CFG_GCFG_START                          (0x00000044910000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_PKTDMA_CFG_GCFG_END                            (0x000000449100ffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_ID                                            (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_MMR_BASE                                      (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_NUM_REGIONS                                   (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_PKTDMA_CFG_RFLOW_START                        (0x00000044911000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_PKTDMA_CFG_RFLOW_END                          (0x000000449113ffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_ID                                            (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_MMR_BASE                                      (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_NUM_REGIONS                                   (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_PKTDMA_CFG_RCHAN_START                        (0x00000044912000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_PKTDMA_CFG_RCHAN_END                          (0x000000449123ffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_ID                                            (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_MMR_BASE                                      (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_NUM_REGIONS                                   (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_PKTDMA_CFG_TCHAN_START                        (0x00000044913000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_PKTDMA_CFG_TCHAN_END                          (0x000000449131ffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_PKTDMA_CFG_RCHANRT_START                    (0x00000044914000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_PKTDMA_CFG_RCHANRT_END                      (0x00000044917fffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_PKTDMA_CFG_TCHANRT_START                    (0x00000044918000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_PKTDMA_CFG_TCHANRT_END                      (0x00000044919fffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_ID                                             (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_MMR_BASE                                       (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_NUM_REGIONS                                    (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_PKTDMA_CFG_RING_START                          (0x0000004491a000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_PKTDMA_CFG_RING_END                            (0x0000004491bfffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_ID                                           (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_MMR_BASE                                     (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_NUM_REGIONS                                  (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_PKTDMA_CFG_RINGRT_START                      (0x00000044940000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_PKTDMA_CFG_RINGRT_END                        (0x0000004497ffffU)

/* Properties of firewall at slave: SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT */
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_ID                                       (638U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_MMR_BASE                                 (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_NUM_REGIONS                              (24U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_IPCSS_RINGACC_CFG_RT_START               (0x00000044c00000U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_IPCSS_RINGACC_CFG_RT_END                 (0x00000044ffffffU)

/* Properties of firewall at slave: SMS0_FWMGR_0_TIFS_FW_VBUS_CFG */
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_ID                                                (639U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_MMR_BASE                                          (0x0000004509fc00U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_NUM_REGIONS                                       (8U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_FW_START                                          (0x00000045000000U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_FW_END                                            (0x00000045ffffffU)

/* Properties of firewall at slave: SMS0_HSM_SRAM_0_HSM_SRAM0_0 */
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_ID                                                  (641U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_MMR_BASE                                            (0x000000450a0400U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_HSM_SRAM0_0_START                                   (0x00000043c00000U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_HSM_SRAM0_0_END                                     (0x00000043c1ffffU)

/* Properties of firewall at slave: SMS0_HSM_SRAM_0_HSM_SRAM0_1 */
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_ID                                                  (641U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_MMR_BASE                                            (0x000000450a0400U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_HSM_SRAM0_1_START                                   (0x00000043c20000U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_HSM_SRAM0_1_END                                     (0x00000043c2ffffU)

/* Properties of firewall at slave: SMS0_HSM_SRAM_1_HSM_SRAM1 */
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_ID                                                    (642U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_MMR_BASE                                              (0x000000450a0800U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_NUM_REGIONS                                           (8U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_HSM_SRAM1_START                                       (0x00000043c30000U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_HSM_SRAM1_END                                         (0x00000043c3ffffU)

/* Properties of firewall at slave: SMS0_RTI_1_HSM_CTRL_MMR */
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_ID                                                      (672U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_MMR_BASE                                                (0x000000450a8000U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_NUM_REGIONS                                             (1U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_HSM_CTRL_MMR_START                                      (0x00000043936000U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_HSM_CTRL_MMR_END                                        (0x00000043936fffU)

/* Properties of firewall at slave: SMS0_WDTCTRL_1_HSM_WDT_RTI */
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_ID                                                   (673U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_MMR_BASE                                             (0x000000450a8400U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_NUM_REGIONS                                          (1U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_HSM_WDT_RTI_START                                    (0x00000043935000U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_HSM_WDT_RTI_END                                      (0x000000439350ffU)

/* Properties of firewall at slave: SMS0_RAT_1_HSM_RAT_MMRS */
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_ID                                                      (680U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_MMR_BASE                                                (0x000000450aa000U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_NUM_REGIONS                                             (1U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_HSM_RAT_MMRS_START                                      (0x00000043a00000U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_HSM_RAT_MMRS_END                                        (0x00000043a00fffU)

/* Properties of firewall at slave: SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS */
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_ID                                             (690U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_MMR_BASE                                       (0x000000450ac800U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_NUM_REGIONS                                    (2U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_HSM_ECC_START                                  (0x00000043701000U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_HSM_ECC_END                                    (0x000000437013ffU)

/* Infrastructure Slave Firewall Definitions */

/* Properties of firewall at slave: PDMA0_REGS */
#define CSL_STD_FW_PDMA0_REGS_ID                                                                   (8U)
#define CSL_STD_FW_PDMA0_REGS_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PDMA0_REGS_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_PDMA0_REGS_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PDMA0_REGS_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PDMA0_REGS_START                                                                (0x00000000c00000U)
#define CSL_STD_FW_PDMA0_REGS_END                                                                  (0x00000000c003ffU)

/* Properties of firewall at slave: PDMA1_REGS */
#define CSL_STD_FW_PDMA1_REGS_ID                                                                   (8U)
#define CSL_STD_FW_PDMA1_REGS_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PDMA1_REGS_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_PDMA1_REGS_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PDMA1_REGS_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PDMA1_REGS_START                                                                (0x00000000c01000U)
#define CSL_STD_FW_PDMA1_REGS_END                                                                  (0x00000000c013ffU)

/* Properties of firewall at slave: UART0_MEM */
#define CSL_STD_FW_UART0_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART0_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART0_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART0_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART0_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART0_MEM_START                                                                 (0x00000002800000U)
#define CSL_STD_FW_UART0_MEM_END                                                                   (0x000000028001ffU)

/* Properties of firewall at slave: UART1_MEM */
#define CSL_STD_FW_UART1_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART1_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART1_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART1_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART1_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART1_MEM_START                                                                 (0x00000002810000U)
#define CSL_STD_FW_UART1_MEM_END                                                                   (0x000000028101ffU)

/* Properties of firewall at slave: UART2_MEM */
#define CSL_STD_FW_UART2_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART2_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART2_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART2_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART2_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART2_MEM_START                                                                 (0x00000002820000U)
#define CSL_STD_FW_UART2_MEM_END                                                                   (0x000000028201ffU)

/* Properties of firewall at slave: UART3_MEM */
#define CSL_STD_FW_UART3_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART3_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART3_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART3_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART3_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART3_MEM_START                                                                 (0x00000002830000U)
#define CSL_STD_FW_UART3_MEM_END                                                                   (0x000000028301ffU)

/* Properties of firewall at slave: UART4_MEM */
#define CSL_STD_FW_UART4_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART4_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART4_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART4_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART4_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART4_MEM_START                                                                 (0x00000002840000U)
#define CSL_STD_FW_UART4_MEM_END                                                                   (0x000000028401ffU)

/* Properties of firewall at slave: UART5_MEM */
#define CSL_STD_FW_UART5_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART5_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART5_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART5_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART5_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART5_MEM_START                                                                 (0x00000002850000U)
#define CSL_STD_FW_UART5_MEM_END                                                                   (0x000000028501ffU)

/* Properties of firewall at slave: UART6_MEM */
#define CSL_STD_FW_UART6_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART6_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART6_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART6_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART6_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART6_MEM_START                                                                 (0x00000002860000U)
#define CSL_STD_FW_UART6_MEM_END                                                                   (0x000000028601ffU)

/* Properties of firewall at slave: I2C0_CFG */
#define CSL_STD_FW_I2C0_CFG_ID                                                                     (8U)
#define CSL_STD_FW_I2C0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C0_CFG_MMR_BASE                                                               (0x00000045002000U)
#define CSL_STD_FW_I2C0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_I2C0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C0_CFG_CFG_START                                                              (0x00000020000000U)
#define CSL_STD_FW_I2C0_CFG_CFG_END                                                                (0x000000200000ffU)

/* Properties of firewall at slave: I2C1_CFG */
#define CSL_STD_FW_I2C1_CFG_ID                                                                     (8U)
#define CSL_STD_FW_I2C1_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C1_CFG_MMR_BASE                                                               (0x00000045002000U)
#define CSL_STD_FW_I2C1_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_I2C1_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C1_CFG_CFG_START                                                              (0x00000020010000U)
#define CSL_STD_FW_I2C1_CFG_CFG_END                                                                (0x000000200100ffU)

/* Properties of firewall at slave: I2C2_CFG */
#define CSL_STD_FW_I2C2_CFG_ID                                                                     (8U)
#define CSL_STD_FW_I2C2_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C2_CFG_MMR_BASE                                                               (0x00000045002000U)
#define CSL_STD_FW_I2C2_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_I2C2_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C2_CFG_CFG_START                                                              (0x00000020020000U)
#define CSL_STD_FW_I2C2_CFG_CFG_END                                                                (0x000000200200ffU)

/* Properties of firewall at slave: I2C3_CFG */
#define CSL_STD_FW_I2C3_CFG_ID                                                                     (8U)
#define CSL_STD_FW_I2C3_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C3_CFG_MMR_BASE                                                               (0x00000045002000U)
#define CSL_STD_FW_I2C3_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_I2C3_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C3_CFG_CFG_START                                                              (0x00000020030000U)
#define CSL_STD_FW_I2C3_CFG_CFG_END                                                                (0x000000200300ffU)

/* Properties of firewall at slave: MCSPI0_CFG */
#define CSL_STD_FW_MCSPI0_CFG_ID                                                                   (8U)
#define CSL_STD_FW_MCSPI0_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI0_CFG_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_MCSPI0_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_MCSPI0_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI0_CFG_CFG_START                                                            (0x00000020100000U)
#define CSL_STD_FW_MCSPI0_CFG_CFG_END                                                              (0x000000201003ffU)

/* Properties of firewall at slave: MCSPI1_CFG */
#define CSL_STD_FW_MCSPI1_CFG_ID                                                                   (8U)
#define CSL_STD_FW_MCSPI1_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI1_CFG_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_MCSPI1_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_MCSPI1_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI1_CFG_CFG_START                                                            (0x00000020110000U)
#define CSL_STD_FW_MCSPI1_CFG_CFG_END                                                              (0x000000201103ffU)

/* Properties of firewall at slave: MCSPI2_CFG */
#define CSL_STD_FW_MCSPI2_CFG_ID                                                                   (8U)
#define CSL_STD_FW_MCSPI2_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI2_CFG_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_MCSPI2_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_MCSPI2_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI2_CFG_CFG_START                                                            (0x00000020120000U)
#define CSL_STD_FW_MCSPI2_CFG_CFG_END                                                              (0x000000201203ffU)

/* Properties of firewall at slave: CBASS_MISC_PERI0_ERR_REGS */
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_ID                                                    (8U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_MMR_BASE                                              (0x00000045002000U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_ERR_START                                             (0x000000201f0000U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_ERR_END                                               (0x000000201f03ffU)

/* Properties of firewall at slave: MCAN0_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_ID                                                 (8U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                           (0x00000045002000U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_START                                           (0x00000020700000U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_END                                             (0x000000207000ffU)

/* Properties of firewall at slave: MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                       (8U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                                 (0x00000045002000U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                              (16U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                                (0x00000020701000U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                                  (0x000000207011ffU)

/* Properties of firewall at slave: MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                             (8U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                       (0x00000045002000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                    (16U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                               (0x00000020708000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                                 (0x0000002070ffffU)

/* Properties of firewall at slave: ECAP0_CTL_STS */
#define CSL_STD_FW_ECAP0_CTL_STS_ID                                                                (8U)
#define CSL_STD_FW_ECAP0_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP0_CTL_STS_MMR_BASE                                                          (0x00000045002000U)
#define CSL_STD_FW_ECAP0_CTL_STS_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_ECAP0_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP0_CTL_STS_CTL_STS_START                                                     (0x00000023100000U)
#define CSL_STD_FW_ECAP0_CTL_STS_CTL_STS_END                                                       (0x000000231000ffU)

/* Properties of firewall at slave: ECAP1_CTL_STS */
#define CSL_STD_FW_ECAP1_CTL_STS_ID                                                                (8U)
#define CSL_STD_FW_ECAP1_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP1_CTL_STS_MMR_BASE                                                          (0x00000045002000U)
#define CSL_STD_FW_ECAP1_CTL_STS_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_ECAP1_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP1_CTL_STS_CTL_STS_START                                                     (0x00000023110000U)
#define CSL_STD_FW_ECAP1_CTL_STS_CTL_STS_END                                                       (0x000000231100ffU)

/* Properties of firewall at slave: ECAP2_CTL_STS */
#define CSL_STD_FW_ECAP2_CTL_STS_ID                                                                (8U)
#define CSL_STD_FW_ECAP2_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP2_CTL_STS_MMR_BASE                                                          (0x00000045002000U)
#define CSL_STD_FW_ECAP2_CTL_STS_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_ECAP2_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP2_CTL_STS_CTL_STS_START                                                     (0x00000023120000U)
#define CSL_STD_FW_ECAP2_CTL_STS_CTL_STS_END                                                       (0x000000231200ffU)

/* Properties of firewall at slave: EQEP0_REG */
#define CSL_STD_FW_EQEP0_REG_ID                                                                    (8U)
#define CSL_STD_FW_EQEP0_REG_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_EQEP0_REG_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_EQEP0_REG_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_EQEP0_REG_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_EQEP0_REG_REG_START                                                             (0x00000023200000U)
#define CSL_STD_FW_EQEP0_REG_REG_END                                                               (0x000000232000ffU)

/* Properties of firewall at slave: EQEP1_REG */
#define CSL_STD_FW_EQEP1_REG_ID                                                                    (8U)
#define CSL_STD_FW_EQEP1_REG_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_EQEP1_REG_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_EQEP1_REG_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_EQEP1_REG_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_EQEP1_REG_REG_START                                                             (0x00000023210000U)
#define CSL_STD_FW_EQEP1_REG_REG_END                                                               (0x000000232100ffU)

/* Properties of firewall at slave: EQEP2_REG */
#define CSL_STD_FW_EQEP2_REG_ID                                                                    (8U)
#define CSL_STD_FW_EQEP2_REG_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_EQEP2_REG_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_EQEP2_REG_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_EQEP2_REG_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_EQEP2_REG_REG_START                                                             (0x00000023220000U)
#define CSL_STD_FW_EQEP2_REG_REG_END                                                               (0x000000232200ffU)

/* Properties of firewall at slave: MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                          (8U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                    (0x00000045002000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                                 (16U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                              (0x00000024018000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                                (0x000000240183ffU)

/* Properties of firewall at slave: MCASP0_CFG */
#define CSL_STD_FW_MCASP0_CFG_ID                                                                   (14U)
#define CSL_STD_FW_MCASP0_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP0_CFG_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP0_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP0_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP0_CFG_CFG_START                                                            (0x00000002b00000U)
#define CSL_STD_FW_MCASP0_CFG_CFG_END                                                              (0x00000002b01fffU)

/* Properties of firewall at slave: MCASP0_DMA */
#define CSL_STD_FW_MCASP0_DMA_ID                                                                   (14U)
#define CSL_STD_FW_MCASP0_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP0_DMA_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP0_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP0_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP0_DMA_DMA_START                                                            (0x00000002b08000U)
#define CSL_STD_FW_MCASP0_DMA_DMA_END                                                              (0x00000002b083ffU)

/* Properties of firewall at slave: MCASP1_CFG */
#define CSL_STD_FW_MCASP1_CFG_ID                                                                   (14U)
#define CSL_STD_FW_MCASP1_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP1_CFG_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP1_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP1_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP1_CFG_CFG_START                                                            (0x00000002b10000U)
#define CSL_STD_FW_MCASP1_CFG_CFG_END                                                              (0x00000002b11fffU)

/* Properties of firewall at slave: MCASP1_DMA */
#define CSL_STD_FW_MCASP1_DMA_ID                                                                   (14U)
#define CSL_STD_FW_MCASP1_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP1_DMA_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP1_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP1_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP1_DMA_DMA_START                                                            (0x00000002b18000U)
#define CSL_STD_FW_MCASP1_DMA_DMA_END                                                              (0x00000002b183ffU)

/* Properties of firewall at slave: MCASP2_CFG */
#define CSL_STD_FW_MCASP2_CFG_ID                                                                   (14U)
#define CSL_STD_FW_MCASP2_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP2_CFG_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP2_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP2_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP2_CFG_CFG_START                                                            (0x00000002b20000U)
#define CSL_STD_FW_MCASP2_CFG_CFG_END                                                              (0x00000002b21fffU)

/* Properties of firewall at slave: MCASP2_DMA */
#define CSL_STD_FW_MCASP2_DMA_ID                                                                   (14U)
#define CSL_STD_FW_MCASP2_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP2_DMA_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP2_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP2_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP2_DMA_DMA_START                                                            (0x00000002b28000U)
#define CSL_STD_FW_MCASP2_DMA_DMA_END                                                              (0x00000002b283ffU)

/* Properties of firewall at slave: EPWM0_EPWM_REGS */
#define CSL_STD_FW_EPWM0_EPWM_REGS_ID                                                              (14U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_EPWM0_EPWM_REGS_MMR_BASE                                                        (0x00000045003800U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_NUM_REGIONS                                                     (8U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_EPWM_START                                                      (0x00000023000000U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_EPWM_END                                                        (0x000000230000ffU)

/* Properties of firewall at slave: EPWM1_EPWM_REGS */
#define CSL_STD_FW_EPWM1_EPWM_REGS_ID                                                              (14U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_EPWM1_EPWM_REGS_MMR_BASE                                                        (0x00000045003800U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_NUM_REGIONS                                                     (8U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_EPWM_START                                                      (0x00000023010000U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_EPWM_END                                                        (0x000000230100ffU)

/* Properties of firewall at slave: EPWM2_EPWM_REGS */
#define CSL_STD_FW_EPWM2_EPWM_REGS_ID                                                              (14U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_EPWM2_EPWM_REGS_MMR_BASE                                                        (0x00000045003800U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_NUM_REGIONS                                                     (8U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_EPWM_START                                                      (0x00000023020000U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_EPWM_END                                                        (0x000000230200ffU)

/* Properties of firewall at slave: PSRAMECC0_RAM */
#define CSL_STD_FW_PSRAMECC0_RAM_ID                                                                (33U)
#define CSL_STD_FW_PSRAMECC0_RAM_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_PSRAMECC0_RAM_MMR_BASE                                                          (0x00000045008400U)
#define CSL_STD_FW_PSRAMECC0_RAM_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_PSRAMECC0_RAM_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_PSRAMECC0_RAM_RAM_START                                                         (0x00000000000000U)
#define CSL_STD_FW_PSRAMECC0_RAM_RAM_END                                                           (0x000000000003ffU)

/* Properties of firewall at slave: PADCFG_CTRL0_CFG0 */
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_ID                                                            (33U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_TYPE                                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_MMR_BASE                                                      (0x00000045008400U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_NUM_REGIONS                                                   (16U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_NUM_PRIV_IDS_PER_REGION                                       (3U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_CFG0_START                                                    (0x000000000f0000U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_CFG0_END                                                      (0x000000000f7fffU)

/* Properties of firewall at slave: CTRL_MMR0_CFG0 */
#define CSL_STD_FW_CTRL_MMR0_CFG0_ID                                                               (33U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_CTRL_MMR0_CFG0_MMR_BASE                                                         (0x00000045008400U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_CFG0_START                                                       (0x00000000100000U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_CFG0_END                                                         (0x0000000011ffffU)

/* Properties of firewall at slave: CBASS_INFRA1_ERR_REGS */
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_ID                                                        (33U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_MMR_BASE                                                  (0x00000045008400U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_ERR_START                                                 (0x00000000210000U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_ERR_END                                                   (0x000000002103ffU)

/* Properties of firewall at slave: EFUSE0_MEM */
#define CSL_STD_FW_EFUSE0_MEM_ID                                                                   (33U)
#define CSL_STD_FW_EFUSE0_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_EFUSE0_MEM_MMR_BASE                                                             (0x00000045008400U)
#define CSL_STD_FW_EFUSE0_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_EFUSE0_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_EFUSE0_MEM_START                                                                (0x00000000300000U)
#define CSL_STD_FW_EFUSE0_MEM_END                                                                  (0x000000003000ffU)

/* Properties of firewall at slave: PSC0_VBUS */
#define CSL_STD_FW_PSC0_VBUS_ID                                                                    (33U)
#define CSL_STD_FW_PSC0_VBUS_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_PSC0_VBUS_MMR_BASE                                                              (0x00000045008400U)
#define CSL_STD_FW_PSC0_VBUS_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_PSC0_VBUS_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_PSC0_VBUS_START                                                                 (0x00000000400000U)
#define CSL_STD_FW_PSC0_VBUS_END                                                                   (0x00000000400fffU)

/* Properties of firewall at slave: PLLCTRL0_MEM */
#define CSL_STD_FW_PLLCTRL0_MEM_ID                                                                 (33U)
#define CSL_STD_FW_PLLCTRL0_MEM_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_PLLCTRL0_MEM_MMR_BASE                                                           (0x00000045008400U)
#define CSL_STD_FW_PLLCTRL0_MEM_NUM_REGIONS                                                        (16U)
#define CSL_STD_FW_PLLCTRL0_MEM_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_PLLCTRL0_MEM_START                                                              (0x00000000410000U)
#define CSL_STD_FW_PLLCTRL0_MEM_END                                                                (0x000000004101ffU)

/* Properties of firewall at slave: ESM0_CFG */
#define CSL_STD_FW_ESM0_CFG_ID                                                                     (33U)
#define CSL_STD_FW_ESM0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_ESM0_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_ESM0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_ESM0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_ESM0_CFG_CFG_START                                                              (0x00000000420000U)
#define CSL_STD_FW_ESM0_CFG_CFG_END                                                                (0x00000000420fffU)

/* Properties of firewall at slave: DFTSS0_MEM */
#define CSL_STD_FW_DFTSS0_MEM_ID                                                                   (33U)
#define CSL_STD_FW_DFTSS0_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DFTSS0_MEM_MMR_BASE                                                             (0x00000045008400U)
#define CSL_STD_FW_DFTSS0_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_DFTSS0_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_DFTSS0_MEM_START                                                                (0x00000000500000U)
#define CSL_STD_FW_DFTSS0_MEM_END                                                                  (0x000000005003ffU)

/* Properties of firewall at slave: DDPA0_DDPA */
#define CSL_STD_FW_DDPA0_DDPA_ID                                                                   (33U)
#define CSL_STD_FW_DDPA0_DDPA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DDPA0_DDPA_MMR_BASE                                                             (0x00000045008400U)
#define CSL_STD_FW_DDPA0_DDPA_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_DDPA0_DDPA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_DDPA0_DDPA_START                                                                (0x00000000580000U)
#define CSL_STD_FW_DDPA0_DDPA_END                                                                  (0x000000005803ffU)

/* Properties of firewall at slave: GPIO0_MEM */
#define CSL_STD_FW_GPIO0_MEM_ID                                                                    (33U)
#define CSL_STD_FW_GPIO0_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_GPIO0_MEM_MMR_BASE                                                              (0x00000045008400U)
#define CSL_STD_FW_GPIO0_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_GPIO0_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_GPIO0_MEM_START                                                                 (0x00000000600000U)
#define CSL_STD_FW_GPIO0_MEM_END                                                                   (0x000000006000ffU)

/* Properties of firewall at slave: GPIO1_MEM */
#define CSL_STD_FW_GPIO1_MEM_ID                                                                    (33U)
#define CSL_STD_FW_GPIO1_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_GPIO1_MEM_MMR_BASE                                                              (0x00000045008400U)
#define CSL_STD_FW_GPIO1_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_GPIO1_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_GPIO1_MEM_START                                                                 (0x00000000601000U)
#define CSL_STD_FW_GPIO1_MEM_END                                                                   (0x000000006010ffU)

/* Properties of firewall at slave: PLL0_CFG */
#define CSL_STD_FW_PLL0_CFG_ID                                                                     (33U)
#define CSL_STD_FW_PLL0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_PLL0_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_PLL0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_PLL0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_PLL0_CFG_CFG_START                                                              (0x00000000680000U)
#define CSL_STD_FW_PLL0_CFG_CFG_END                                                                (0x0000000069ffffU)

/* Properties of firewall at slave: PSRAMECC0_REGS */
#define CSL_STD_FW_PSRAMECC0_REGS_ID                                                               (33U)
#define CSL_STD_FW_PSRAMECC0_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_PSRAMECC0_REGS_MMR_BASE                                                         (0x00000045008400U)
#define CSL_STD_FW_PSRAMECC0_REGS_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_PSRAMECC0_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_PSRAMECC0_REGS_ECC_AGGR_START                                                   (0x00000000700000U)
#define CSL_STD_FW_PSRAMECC0_REGS_ECC_AGGR_END                                                     (0x000000007003ffU)

/* Properties of firewall at slave: PSC0_ECC_AGGR_0_REGS */
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_ID                                                         (33U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_MMR_BASE                                                   (0x00000045008400U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_NUM_REGIONS                                                (16U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_REGS_START                                                 (0x00000000700400U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_REGS_END                                                   (0x000000007007ffU)

/* Properties of firewall at slave: PSRAMECC1_REGS */
#define CSL_STD_FW_PSRAMECC1_REGS_ID                                                               (33U)
#define CSL_STD_FW_PSRAMECC1_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_PSRAMECC1_REGS_MMR_BASE                                                         (0x00000045008400U)
#define CSL_STD_FW_PSRAMECC1_REGS_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_PSRAMECC1_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_PSRAMECC1_REGS_ECC_AGGR_START                                                   (0x00000000701000U)
#define CSL_STD_FW_PSRAMECC1_REGS_ECC_AGGR_END                                                     (0x000000007013ffU)

/* Properties of firewall at slave: DCC0_CFG */
#define CSL_STD_FW_DCC0_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC0_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC0_CFG_START                                                                  (0x00000000800000U)
#define CSL_STD_FW_DCC0_CFG_END                                                                    (0x0000000080003fU)

/* Properties of firewall at slave: DCC1_CFG */
#define CSL_STD_FW_DCC1_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC1_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC1_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC1_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC1_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC1_CFG_START                                                                  (0x00000000804000U)
#define CSL_STD_FW_DCC1_CFG_END                                                                    (0x0000000080403fU)

/* Properties of firewall at slave: DCC2_CFG */
#define CSL_STD_FW_DCC2_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC2_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC2_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC2_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC2_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC2_CFG_START                                                                  (0x00000000808000U)
#define CSL_STD_FW_DCC2_CFG_END                                                                    (0x0000000080803fU)

/* Properties of firewall at slave: DCC3_CFG */
#define CSL_STD_FW_DCC3_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC3_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC3_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC3_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC3_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC3_CFG_START                                                                  (0x0000000080c000U)
#define CSL_STD_FW_DCC3_CFG_END                                                                    (0x0000000080c03fU)

/* Properties of firewall at slave: DCC4_CFG */
#define CSL_STD_FW_DCC4_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC4_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC4_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC4_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC4_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC4_CFG_START                                                                  (0x00000000810000U)
#define CSL_STD_FW_DCC4_CFG_END                                                                    (0x0000000081003fU)

/* Properties of firewall at slave: DCC5_CFG */
#define CSL_STD_FW_DCC5_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC5_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC5_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC5_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC5_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC5_CFG_START                                                                  (0x00000000814000U)
#define CSL_STD_FW_DCC5_CFG_END                                                                    (0x0000000081403fU)

/* Properties of firewall at slave: DCC6_CFG */
#define CSL_STD_FW_DCC6_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC6_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC6_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC6_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC6_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC6_CFG_START                                                                  (0x00000000818000U)
#define CSL_STD_FW_DCC6_CFG_END                                                                    (0x0000000081803fU)

/* Properties of firewall at slave: PSRAMECC1_RAM */
#define CSL_STD_FW_PSRAMECC1_RAM_ID                                                                (33U)
#define CSL_STD_FW_PSRAMECC1_RAM_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_PSRAMECC1_RAM_MMR_BASE                                                          (0x00000045008400U)
#define CSL_STD_FW_PSRAMECC1_RAM_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_PSRAMECC1_RAM_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_PSRAMECC1_RAM_RAM_START                                                         (0x00000000900000U)
#define CSL_STD_FW_PSRAMECC1_RAM_RAM_END                                                           (0x000000009003ffU)

/* Properties of firewall at slave: MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_ID                                      (33U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_MMR_BASE                                (0x00000045008400U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                             (16U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START                   (0x00000000a00000U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                     (0x00000000a007ffU)

/* Properties of firewall at slave: CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_ID                                         (33U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_MMR_BASE                                   (0x00000045008400U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                                (16U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START                      (0x00000000a30000U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                        (0x00000000a307ffU)

/* Properties of firewall at slave: TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_ID                                       (33U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_MMR_BASE                                 (0x00000045008400U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                              (16U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START                    (0x00000000a40000U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                      (0x00000000a403ffU)

/* Properties of firewall at slave: WKUP_PSC0_VBUS */
#define CSL_STD_FW_WKUP_PSC0_VBUS_ID                                                               (35U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSC0_VBUS_MMR_BASE                                                         (0x00000045008c00U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_START                                                            (0x00000004000000U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_END                                                              (0x00000004000fffU)

/* Properties of firewall at slave: MCU_PLLCTRL0_MEM */
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_ID                                                             (35U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_TYPE                                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_MMR_BASE                                                       (0x00000045008c00U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_NUM_REGIONS                                                    (16U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_NUM_PRIV_IDS_PER_REGION                                        (3U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_START                                                          (0x00000004020000U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_END                                                            (0x000000040201ffU)

/* Properties of firewall at slave: WKUP_ECC_AGGR2_REGS */
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_ID                                                          (35U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_MMR_BASE                                                    (0x00000045008c00U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_ECC_AGGR_START                                              (0x00000004030000U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_ECC_AGGR_END                                                (0x000000040303ffU)

/* Properties of firewall at slave: WKUP_PLL0_CFG */
#define CSL_STD_FW_WKUP_PLL0_CFG_ID                                                                (35U)
#define CSL_STD_FW_WKUP_PLL0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PLL0_CFG_MMR_BASE                                                          (0x00000045008c00U)
#define CSL_STD_FW_WKUP_PLL0_CFG_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_WKUP_PLL0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_PLL0_CFG_CFG_START                                                         (0x00000004040000U)
#define CSL_STD_FW_WKUP_PLL0_CFG_CFG_END                                                           (0x00000004040fffU)

/* Properties of firewall at slave: WKUP_PADCFG_CTRL0_CFG0 */
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_ID                                                       (35U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_MMR_BASE                                                 (0x00000045008c00U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_NUM_REGIONS                                              (16U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_CFG0_START                                               (0x00000004080000U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_CFG0_END                                                 (0x00000004087fffU)

/* Properties of firewall at slave: WKUP_ESM0_CFG */
#define CSL_STD_FW_WKUP_ESM0_CFG_ID                                                                (35U)
#define CSL_STD_FW_WKUP_ESM0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ESM0_CFG_MMR_BASE                                                          (0x00000045008c00U)
#define CSL_STD_FW_WKUP_ESM0_CFG_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_WKUP_ESM0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_ESM0_CFG_CFG_START                                                         (0x00000004100000U)
#define CSL_STD_FW_WKUP_ESM0_CFG_CFG_END                                                           (0x00000004100fffU)

/* Properties of firewall at slave: MCU_GPIO0_MEM */
#define CSL_STD_FW_MCU_GPIO0_MEM_ID                                                                (35U)
#define CSL_STD_FW_MCU_GPIO0_MEM_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_GPIO0_MEM_MMR_BASE                                                          (0x00000045008c00U)
#define CSL_STD_FW_MCU_GPIO0_MEM_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_MCU_GPIO0_MEM_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_MCU_GPIO0_MEM_START                                                             (0x00000004201000U)
#define CSL_STD_FW_MCU_GPIO0_MEM_END                                                               (0x000000042010ffU)

/* Properties of firewall at slave: WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_ID                                  (35U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_TYPE                                (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_MMR_BASE                            (0x00000045008c00U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                         (16U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION             (3U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START               (0x00000004210000U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                 (0x000000042101ffU)

/* Properties of firewall at slave: MCU_CTRL_MMR0_CFG0 */
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_ID                                                           (35U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_MMR_BASE                                                     (0x00000045008c00U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_CFG0_START                                                   (0x00000004500000U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_CFG0_END                                                     (0x0000000451ffffU)

/* Properties of firewall at slave: WKUP_CBASS_SAFE1_ERR_REGS */
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_ID                                                    (35U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_MMR_BASE                                              (0x00000045008c00U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_ERR_START                                             (0x00000004600000U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_ERR_END                                               (0x000000046003ffU)

/* Properties of firewall at slave: MCU_TIMEOUT0_CFG */
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_ID                                                             (36U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_TYPE                                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_MMR_BASE                                                       (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_NUM_REGIONS                                                    (8U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_NUM_PRIV_IDS_PER_REGION                                        (3U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_CFG_START                                                      (0x00000004301000U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_CFG_END                                                        (0x000000043013ffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_ID                                         (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_MMR_BASE                                   (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_NUM_REGIONS                                (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_START                  (0x00000004400000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_END                    (0x000000044000ffU)

/* Properties of firewall at slave: MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                      (36U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                             (8U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                          (0x00000004701000U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                            (0x000000047013ffU)

/* Properties of firewall at slave: MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                      (36U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                             (8U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                          (0x00000004702000U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                            (0x000000047023ffU)

/* Properties of firewall at slave: MCU_ECC_AGGR0_REGS */
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_ID                                                           (36U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_MMR_BASE                                                     (0x00000045009000U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_NUM_REGIONS                                                  (8U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_ECC_AGGR_START                                               (0x00000004703000U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_ECC_AGGR_END                                                 (0x000000047033ffU)

/* Properties of firewall at slave: MCU_ECC_AGGR1_REGS */
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_ID                                                           (36U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_MMR_BASE                                                     (0x00000045009000U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_NUM_REGIONS                                                  (8U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_ECC_AGGR_START                                               (0x00000004704000U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_ECC_AGGR_END                                                 (0x000000047043ffU)

/* Properties of firewall at slave: MCU_MSRAM_256K0_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_ID                                            (36U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_MMR_BASE                                      (0x00000045009000U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_NUM_REGIONS                                   (8U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                           (0x00000004705000U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                             (0x000000047053ffU)

/* Properties of firewall at slave: MCU_MSRAM_256K1_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_ID                                            (36U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_MMR_BASE                                      (0x00000045009000U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_NUM_REGIONS                                   (8U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                           (0x00000004706000U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                             (0x000000047063ffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_ID                                      (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_MMR_BASE                                (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_NUM_REGIONS                             (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_START                    (0x00000004707000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_END                      (0x000000047073ffU)

/* Properties of firewall at slave: MCU_CBASS0_ERR_REGS */
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_ID                                                          (36U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_MMR_BASE                                                    (0x00000045009000U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_NUM_REGIONS                                                 (8U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_ERR_START                                                   (0x00000004720000U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_ERR_END                                                     (0x000000047203ffU)

/* Properties of firewall at slave: MCU_TIMER0_CFG */
#define CSL_STD_FW_MCU_TIMER0_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_TIMER0_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMER0_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMER0_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_TIMER0_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_TIMER0_CFG_CFG_START                                                        (0x00000004800000U)
#define CSL_STD_FW_MCU_TIMER0_CFG_CFG_END                                                          (0x000000048003ffU)

/* Properties of firewall at slave: MCU_TIMER1_CFG */
#define CSL_STD_FW_MCU_TIMER1_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_TIMER1_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMER1_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMER1_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_TIMER1_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_TIMER1_CFG_CFG_START                                                        (0x00000004810000U)
#define CSL_STD_FW_MCU_TIMER1_CFG_CFG_END                                                          (0x000000048103ffU)

/* Properties of firewall at slave: MCU_TIMER2_CFG */
#define CSL_STD_FW_MCU_TIMER2_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_TIMER2_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMER2_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMER2_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_TIMER2_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_TIMER2_CFG_CFG_START                                                        (0x00000004820000U)
#define CSL_STD_FW_MCU_TIMER2_CFG_CFG_END                                                          (0x000000048203ffU)

/* Properties of firewall at slave: MCU_TIMER3_CFG */
#define CSL_STD_FW_MCU_TIMER3_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_TIMER3_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMER3_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMER3_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_TIMER3_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_TIMER3_CFG_CFG_START                                                        (0x00000004830000U)
#define CSL_STD_FW_MCU_TIMER3_CFG_CFG_END                                                          (0x000000048303ffU)

/* Properties of firewall at slave: MCU_RTI0_CFG */
#define CSL_STD_FW_MCU_RTI0_CFG_ID                                                                 (36U)
#define CSL_STD_FW_MCU_RTI0_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_RTI0_CFG_MMR_BASE                                                           (0x00000045009000U)
#define CSL_STD_FW_MCU_RTI0_CFG_NUM_REGIONS                                                        (8U)
#define CSL_STD_FW_MCU_RTI0_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_RTI0_CFG_CFG_START                                                          (0x00000004880000U)
#define CSL_STD_FW_MCU_RTI0_CFG_CFG_END                                                            (0x000000048800ffU)

/* Properties of firewall at slave: MCU_I2C0_CFG */
#define CSL_STD_FW_MCU_I2C0_CFG_ID                                                                 (36U)
#define CSL_STD_FW_MCU_I2C0_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_I2C0_CFG_MMR_BASE                                                           (0x00000045009000U)
#define CSL_STD_FW_MCU_I2C0_CFG_NUM_REGIONS                                                        (8U)
#define CSL_STD_FW_MCU_I2C0_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_I2C0_CFG_CFG_START                                                          (0x00000004900000U)
#define CSL_STD_FW_MCU_I2C0_CFG_CFG_END                                                            (0x000000049000ffU)

/* Properties of firewall at slave: MCU_UART0_MEM */
#define CSL_STD_FW_MCU_UART0_MEM_ID                                                                (36U)
#define CSL_STD_FW_MCU_UART0_MEM_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_UART0_MEM_MMR_BASE                                                          (0x00000045009000U)
#define CSL_STD_FW_MCU_UART0_MEM_NUM_REGIONS                                                       (8U)
#define CSL_STD_FW_MCU_UART0_MEM_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_MCU_UART0_MEM_START                                                             (0x00000004a00000U)
#define CSL_STD_FW_MCU_UART0_MEM_END                                                               (0x00000004a001ffU)

/* Properties of firewall at slave: MCU_MCSPI0_CFG */
#define CSL_STD_FW_MCU_MCSPI0_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCSPI0_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_CFG_START                                                        (0x00000004b00000U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_CFG_END                                                          (0x00000004b003ffU)

/* Properties of firewall at slave: MCU_MCSPI1_CFG */
#define CSL_STD_FW_MCU_MCSPI1_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCSPI1_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_CFG_START                                                        (0x00000004b10000U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_CFG_END                                                          (0x00000004b103ffU)

/* Properties of firewall at slave: MCU_DCC0_CFG */
#define CSL_STD_FW_MCU_DCC0_CFG_ID                                                                 (36U)
#define CSL_STD_FW_MCU_DCC0_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_DCC0_CFG_MMR_BASE                                                           (0x00000045009000U)
#define CSL_STD_FW_MCU_DCC0_CFG_NUM_REGIONS                                                        (8U)
#define CSL_STD_FW_MCU_DCC0_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_DCC0_CFG_START                                                              (0x00000004c00000U)
#define CSL_STD_FW_MCU_DCC0_CFG_END                                                                (0x00000004c0003fU)

/* Properties of firewall at slave: MCU_DCC1_CFG */
#define CSL_STD_FW_MCU_DCC1_CFG_ID                                                                 (36U)
#define CSL_STD_FW_MCU_DCC1_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_DCC1_CFG_MMR_BASE                                                           (0x00000045009000U)
#define CSL_STD_FW_MCU_DCC1_CFG_NUM_REGIONS                                                        (8U)
#define CSL_STD_FW_MCU_DCC1_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_DCC1_CFG_START                                                              (0x00000004c10000U)
#define CSL_STD_FW_MCU_DCC1_CFG_END                                                                (0x00000004c1003fU)

/* Properties of firewall at slave: MCU_MCRC64_0_MCRC64_REGS */
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_ID                                                     (36U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_MMR_BASE                                               (0x00000045009000U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_NUM_REGIONS                                            (8U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_REGS_START                                             (0x00000004d00000U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_REGS_END                                               (0x00000004d00fffU)

/* Properties of firewall at slave: MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                         (36U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                   (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                (8U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                           (0x00000004e00000U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                             (0x00000004e07fffU)

/* Properties of firewall at slave: MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                   (36U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                             (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                          (8U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                            (0x00000004e08000U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                              (0x00000004e081ffU)

/* Properties of firewall at slave: MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_ID                                             (36U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                       (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                    (8U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_START                                       (0x00000004e09000U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_END                                         (0x00000004e090ffU)

/* Properties of firewall at slave: MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                         (36U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                   (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                (8U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                           (0x00000004e10000U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                             (0x00000004e17fffU)

/* Properties of firewall at slave: MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                   (36U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                             (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                          (8U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                            (0x00000004e18000U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                              (0x00000004e181ffU)

/* Properties of firewall at slave: MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_ID                                             (36U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                       (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                    (8U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_SS_START                                       (0x00000004e19000U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_SS_END                                         (0x00000004e190ffU)

/* Properties of firewall at slave: MCU_PBIST0_MEM */
#define CSL_STD_FW_MCU_PBIST0_MEM_ID                                                               (36U)
#define CSL_STD_FW_MCU_PBIST0_MEM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_PBIST0_MEM_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_PBIST0_MEM_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_PBIST0_MEM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_PBIST0_MEM_START                                                            (0x00000004f00000U)
#define CSL_STD_FW_MCU_PBIST0_MEM_END                                                              (0x00000004f003ffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_ICACHE0 */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_ID                                                     (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_MMR_BASE                                               (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_NUM_REGIONS                                            (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_START                                     (0x00000073000000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_END                                       (0x000000737fffffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_DCACHE0 */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_ID                                                     (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_MMR_BASE                                               (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_NUM_REGIONS                                            (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_START                                     (0x00000073800000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_END                                       (0x00000073ffffffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_ATCM0 */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_ID                                                       (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_MMR_BASE                                                 (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_NUM_REGIONS                                              (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_CORE0_ATCM_START                                         (0x00000079000000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_CORE0_ATCM_END                                           (0x00000079007fffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_BTCM0 */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_ID                                                       (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_MMR_BASE                                                 (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_NUM_REGIONS                                              (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_CORE0_BTCM_START                                         (0x00000079020000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_CORE0_BTCM_END                                           (0x00000079027fffU)

/* Properties of firewall at slave: MCU_MSRAM_256K0_RAM */
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_ID                                                          (36U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_MMR_BASE                                                    (0x00000045009000U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_NUM_REGIONS                                                 (8U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_RAM_START                                                   (0x00000079100000U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_RAM_END                                                     (0x0000007913ffffU)

/* Properties of firewall at slave: MCU_MSRAM_256K1_RAM */
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_ID                                                          (36U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_MMR_BASE                                                    (0x00000045009000U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_NUM_REGIONS                                                 (8U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_RAM_START                                                   (0x00000079140000U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_RAM_END                                                     (0x0000007917ffffU)

/* Channelized Firewall Definitions */

/* Properties of channelized firewall at: PSC0_VBUS */
#define CSL_CH_FW_PSC0_VBUS_ID                                                                     (128U)
#define CSL_CH_FW_PSC0_VBUS_TYPE                                                                   (CSL_FW_CHANNEL)
#define CSL_CH_FW_PSC0_VBUS_MMR_BASE                                                               (0x00000045020000U)
#define CSL_CH_FW_PSC0_VBUS_NUM_REGIONS                                                            (5U)
#define CSL_CH_FW_PSC0_VBUS_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_START                                                       (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_END                                                         (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_OFFSET_FIRST_RES                                            (0x0000000000000000U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_NUM_CHANNELS                                                (1U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_CHANNEL_SIZE                                                (4U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_START                                                             (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_END                                                               (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_OFFSET_FIRST_RES                                                  (0x0000000000000020U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_NUM_CHANNELS                                                      (1U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_CHANNEL_SIZE                                                      (4U)
#define CSL_CH_FW_PSC0_VBUS_HSM_START                                                              (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_HSM_END                                                                (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_HSM_OFFSET_FIRST_RES                                                   (0x0000000000000040U)
#define CSL_CH_FW_PSC0_VBUS_HSM_NUM_CHANNELS                                                       (1U)
#define CSL_CH_FW_PSC0_VBUS_HSM_CHANNEL_SIZE                                                       (4U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_START                                                            (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_END                                                              (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_OFFSET_FIRST_RES                                                 (0x0000000000000060U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_NUM_CHANNELS                                                     (1U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_CHANNEL_SIZE                                                     (4U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_START                                                          (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_END                                                            (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_OFFSET_FIRST_RES                                               (0x0000000000000080U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_NUM_CHANNELS                                                   (1U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_CHANNEL_SIZE                                                   (4U)

#ifdef __cplusplus
}
#endif
#endif /* CSLR_SOC_FW_H_ */
/********************************************************************
*
* SOC FIREWALL PROPERTIES. header file
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated.
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
#ifndef CSLR_SOC_FW_H_
#define CSLR_SOC_FW_H_

#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
* Auto-generated CSL definitions for SoC Firewalls:
*/

#define CSL_FW_SECURITY                                                                            (0U)
#define CSL_FW_CHANNEL                                                                             (1U)
#define CSL_FW_MST                                                                                 (2U)

/* Standard Security Master Firewall Definitions */

/* Standard Security Slave Firewall Definitions */

/* Properties of firewall at slave: DDR32SS0_SDRAM_FW0 */
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_ID                                                           (0U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_MMR_BASE                                                     (0x00000045000000U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_NUM_REGIONS                                                  (8U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_SDRAM_START                                                  (0x00000080000000U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW0_SDRAM_END                                                    (0x000000ffffffffU)

/* Properties of firewall at slave: DDR32SS0_SDRAM_FW1 */
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_ID                                                           (1U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_MMR_BASE                                                     (0x00000045000400U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_SDRAM_START                                                  (0x00000080000000U)
#define CSL_STD_FW_DDR32SS0_SDRAM_FW1_SDRAM_END                                                    (0x000000ffffffffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_ROM_TABLE_0_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_ROM_TABLE_0_0_START                                 (0x00000700000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_0_ROM_TABLE_0_0_END                                   (0x00000700000fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV0_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_RESV0_0_START                                             (0x00000700001000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_0_RESV0_0_END                                               (0x00000700001fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CFGAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_CFGAP0_START                                          (0x00000700002000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_0_CFGAP0_END                                            (0x000007000020ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_APBAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_APBAP0_START                                          (0x00000700002100U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_0_APBAP0_END                                            (0x000007000021ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_AXIAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_AXIAP0_START                                          (0x00000700002200U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_0_AXIAP0_END                                            (0x000007000022ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_PWRAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_PWRAP0_START                                          (0x00000700002300U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_0_PWRAP0_END                                            (0x000007000023ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_PVIEW_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_PVIEW0_START                                          (0x00000700002400U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_0_PVIEW0_END                                            (0x000007000024ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_JTAGAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_ID                                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_MMR_BASE                                             (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_NUM_REGIONS                                          (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_JTAGAP0_START                                        (0x00000700002500U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_0_JTAGAP0_END                                          (0x000007000025ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_SECAP_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_SECAP0_START                                          (0x00000700002600U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_0_SECAP0_END                                            (0x000007000026ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX0_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_CORTEX0_CFG0_START                                  (0x00000700002700U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_0_CORTEX0_CFG0_END                                    (0x000007000027ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX1_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_CORTEX1_CFG0_START                                  (0x00000700002800U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_0_CORTEX1_CFG0_END                                    (0x000007000028ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX2_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_CORTEX2_CFG0_START                                  (0x00000700002900U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_0_CORTEX2_CFG0_END                                    (0x000007000029ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX3_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_CORTEX3_CFG0_START                                  (0x00000700002a00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_0_CORTEX3_CFG0_END                                    (0x00000700002affU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX4_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_CORTEX4_CFG0_START                                  (0x00000700002b00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_0_CORTEX4_CFG0_END                                    (0x00000700002bffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX5_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_CORTEX5_CFG0_START                                  (0x00000700002c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_0_CORTEX5_CFG0_END                                    (0x00000700002cffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX6_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_CORTEX6_CFG0_START                                  (0x00000700002d00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_0_CORTEX6_CFG0_END                                    (0x00000700002dffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX7_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_CORTEX7_CFG0_START                                  (0x00000700002e00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_0_CORTEX7_CFG0_END                                    (0x00000700002effU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX8_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_CORTEX8_CFG0_START                                  (0x00000700002f00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_0_CORTEX8_CFG0_END                                    (0x00000700002fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV1_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_RESV1_0_START                                             (0x00000700003000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_0_RESV1_0_END                                               (0x00000700003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV2_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_RESV2_0_START                                             (0x00000700004000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_0_RESV2_0_END                                               (0x00000702003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_ROM_TABLE_1_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_ROM_TABLE_1_0_START                                 (0x00000720000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_0_ROM_TABLE_1_0_END                                   (0x00000720000fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CSCTI_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_CSCTI0_START                                          (0x00000720001000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_0_CSCTI0_END                                            (0x00000720001fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_DRM_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_DRM0_START                                              (0x00000720002000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_0_DRM0_END                                                (0x00000720002fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV3_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_RESV3_0_START                                             (0x00000720003000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_0_RESV3_0_END                                               (0x00000720003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CSTPIU_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_ID                                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_MMR_BASE                                             (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_NUM_REGIONS                                          (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_CSTPIU0_START                                        (0x00000720004000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_0_CSTPIU0_END                                          (0x00000720004fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CTF_CFG_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_CTF0_START                                              (0x00000720005000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_0_CTF0_END                                                (0x00000720005fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV4_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_RESV4_0_START                                             (0x00000720006000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_0_RESV4_0_END                                               (0x00000721005fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_EXT_APB_0 */
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_EXT_APB0_START                                          (0x00000730000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_0_EXT_APB0_END                                            (0x0000073fffffffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_ROM_TABLE_0_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_ROM_TABLE_0_1_START                                 (0x00000740000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_0_1_ROM_TABLE_0_1_END                                   (0x00000740000fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV0_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_RESV0_1_START                                             (0x00000740001000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV0_1_RESV0_1_END                                               (0x00000740001fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CFGAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_CFGAP1_START                                          (0x00000740002000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CFGAP_CFG_1_CFGAP1_END                                            (0x000007400020ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_APBAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_APBAP1_START                                          (0x00000740002100U)
#define CSL_STD_FW_DEBUGSS_WRAP0_APBAP_CFG_1_APBAP1_END                                            (0x000007400021ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_AXIAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_AXIAP1_START                                          (0x00000740002200U)
#define CSL_STD_FW_DEBUGSS_WRAP0_AXIAP_CFG_1_AXIAP1_END                                            (0x000007400022ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_PWRAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_PWRAP1_START                                          (0x00000740002300U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PWRAP_CFG_1_PWRAP1_END                                            (0x000007400023ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_PVIEW_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_PVIEW1_START                                          (0x00000740002400U)
#define CSL_STD_FW_DEBUGSS_WRAP0_PVIEW_CFG_1_PVIEW1_END                                            (0x000007400024ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_JTAGAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_ID                                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_MMR_BASE                                             (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_NUM_REGIONS                                          (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_JTAGAP1_START                                        (0x00000740002500U)
#define CSL_STD_FW_DEBUGSS_WRAP0_JTAGAP_CFG_1_JTAGAP1_END                                          (0x000007400025ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_SECAP_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_SECAP1_START                                          (0x00000740002600U)
#define CSL_STD_FW_DEBUGSS_WRAP0_SECAP_CFG_1_SECAP1_END                                            (0x000007400026ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX0_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_CORTEX0_CFG1_START                                  (0x00000740002700U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX0_CFG_1_CORTEX0_CFG1_END                                    (0x000007400027ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX1_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_CORTEX1_CFG1_START                                  (0x00000740002800U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX1_CFG_1_CORTEX1_CFG1_END                                    (0x000007400028ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX2_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_CORTEX2_CFG1_START                                  (0x00000740002900U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX2_CFG_1_CORTEX2_CFG1_END                                    (0x000007400029ffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX3_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_CORTEX3_CFG1_START                                  (0x00000740002a00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX3_CFG_1_CORTEX3_CFG1_END                                    (0x00000740002affU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX4_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_CORTEX4_CFG1_START                                  (0x00000740002b00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX4_CFG_1_CORTEX4_CFG1_END                                    (0x00000740002bffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX5_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_CORTEX5_CFG1_START                                  (0x00000740002c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX5_CFG_1_CORTEX5_CFG1_END                                    (0x00000740002cffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX6_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_CORTEX6_CFG1_START                                  (0x00000740002d00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX6_CFG_1_CORTEX6_CFG1_END                                    (0x00000740002dffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX7_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_CORTEX7_CFG1_START                                  (0x00000740002e00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX7_CFG_1_CORTEX7_CFG1_END                                    (0x00000740002effU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CORTEX8_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_CORTEX8_CFG1_START                                  (0x00000740002f00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CORTEX8_CFG_1_CORTEX8_CFG1_END                                    (0x00000740002fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV1_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_RESV1_1_START                                             (0x00000740003000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV1_1_RESV1_1_END                                               (0x00000740003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV2_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_RESV2_1_START                                             (0x00000740004000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV2_1_RESV2_1_END                                               (0x00000742003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_ROM_TABLE_1_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_ID                                                  (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_MMR_BASE                                            (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_NUM_REGIONS                                         (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_ROM_TABLE_1_1_START                                 (0x00000760000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_ROM_TABLE_1_1_ROM_TABLE_1_1_END                                   (0x00000760000fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CSCTI_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_ID                                                    (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_MMR_BASE                                              (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_CSCTI1_START                                          (0x00000760001000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSCTI_CFG_1_CSCTI1_END                                            (0x00000760001fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_DRM_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_DRM1_START                                              (0x00000760002000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_DRM_CFG_1_DRM1_END                                                (0x00000760002fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV3_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_RESV3_1_START                                             (0x00000760003000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV3_1_RESV3_1_END                                               (0x00000760003fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CSTPIU_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_ID                                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_MMR_BASE                                             (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_NUM_REGIONS                                          (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_CSTPIU1_START                                        (0x00000760004000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CSTPIU_CFG_1_CSTPIU1_END                                          (0x00000760004fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_CTF_CFG_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_CTF1_START                                              (0x00000760005000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_CTF_CFG_1_CTF1_END                                                (0x00000760005fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_RESV4_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_ID                                                        (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_MMR_BASE                                                  (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_RESV4_1_START                                             (0x00000760006000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_RESV4_1_RESV4_1_END                                               (0x00000761005fffU)

/* Properties of firewall at slave: DEBUGSS_WRAP0_EXT_APB_1 */
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_ID                                                      (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_MMR_BASE                                                (0x00000045000c00U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_EXT_APB1_START                                          (0x00000770000000U)
#define CSL_STD_FW_DEBUGSS_WRAP0_EXT_APB_1_EXT_APB1_END                                            (0x0000077fffffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_UMC_CFG */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_ID                                                  (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_MMR_BASE                                            (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_UMC_START                                           (0x0000007c000000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_UMC_END                                             (0x0000007c01ffffU)

/* Properties of firewall at slave: C7X256V0_CLEC_C7XV_CLEC_CFG */
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_ID                                                  (4U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_MMR_BASE                                            (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_CLEC_START                                          (0x0000007c200000U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_CLEC_END                                            (0x0000007c2fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_ID                                              (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_MMR_BASE                                        (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_NUM_REGIONS                                     (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_DRU_START                                       (0x0000007c400000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_DRU_END                                         (0x0000007c403fffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_ID                                          (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_MMR_BASE                                    (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_NUM_REGIONS                                 (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_DRU_SET_START                               (0x0000007c404000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_DRU_SET_END                                 (0x0000007c407fffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_ID                                        (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_MMR_BASE                                  (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_DRU_QUEUE_START                           (0x0000007c408000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_DRU_QUEUE_END                             (0x0000007c40ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_ID                                        (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_MMR_BASE                                  (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_DRU_CHNRT_START                           (0x0000007c440000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_DRU_CHNRT_END                             (0x0000007c45ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_ID                                         (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_MMR_BASE                                   (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_NUM_REGIONS                                (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_DRU_CHRT_START                             (0x0000007c460000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_DRU_CHRT_END                               (0x0000007c47ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_ID                               (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_MMR_BASE                         (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_NUM_REGIONS                      (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_DRU_CHATOMIC_DEBUG_START         (0x0000007c480000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_DRU_CHATOMIC_DEBUG_END           (0x0000007c49ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_ID                                       (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_MMR_BASE                                 (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_NUM_REGIONS                              (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_DRU_CHCORE_START                         (0x0000007c4a0000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_DRU_CHCORE_END                           (0x0000007c4bffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_ID                                        (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_MMR_BASE                                  (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_DRU_CAUSE_START                           (0x0000007c4e0000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_DRU_CAUSE_END                             (0x0000007c4fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_UMC_MEM_MAIN */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_ID                                             (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_MMR_BASE                                       (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_NUM_REGIONS                                    (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_UMC_MEM_MAIN_START                             (0x0000007e000000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_UMC_MEM_MAIN_END                               (0x0000007e0fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_UMC_MEM_AUX */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_ID                                              (4U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_MMR_BASE                                        (0x00000045001000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_NUM_REGIONS                                     (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_UMC_MEM_AUX_START                               (0x0000007f000000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_UMC_MEM_AUX_END                                 (0x0000007f03ffffU)

/* Properties of firewall at slave: VPAC0_MEM_SLV_DATA */
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_ID                                                           (5U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_MMR_BASE                                                     (0x00000045001400U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_NUM_REGIONS                                                  (8U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_MEM_SLV_DATA_START                                           (0x00000071000000U)
#define CSL_STD_FW_VPAC0_MEM_SLV_DATA_MEM_SLV_DATA_END                                             (0x0000007107ffffU)

/* Properties of firewall at slave: GPMC0_CFG */
#define CSL_STD_FW_GPMC0_CFG_ID                                                                    (6U)
#define CSL_STD_FW_GPMC0_CFG_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_GPMC0_CFG_MMR_BASE                                                              (0x00000045001800U)
#define CSL_STD_FW_GPMC0_CFG_NUM_REGIONS                                                           (8U)
#define CSL_STD_FW_GPMC0_CFG_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_GPMC0_CFG_CFG_START                                                             (0x0000003b000000U)
#define CSL_STD_FW_GPMC0_CFG_CFG_END                                                               (0x0000003b0003ffU)

/* Properties of firewall at slave: GPMC0_DATA */
#define CSL_STD_FW_GPMC0_DATA_ID                                                                   (6U)
#define CSL_STD_FW_GPMC0_DATA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_GPMC0_DATA_MMR_BASE                                                             (0x00000045001800U)
#define CSL_STD_FW_GPMC0_DATA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_GPMC0_DATA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_GPMC0_DATA_DATA_START                                                           (0x00000050000000U)
#define CSL_STD_FW_GPMC0_DATA_DATA_END                                                             (0x00000057ffffffU)

/* Properties of firewall at slave: FSS0_FSAS_0_DAT_REG1 */
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_ID                                                         (7U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_MMR_BASE                                                   (0x00000045001c00U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_DAT_REG1_START                                             (0x00000060000000U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG1_DAT_REG1_END                                               (0x00000067ffffffU)

/* Properties of firewall at slave: FSS0_FSAS_0_DAT_REG0 */
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_ID                                                         (7U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_MMR_BASE                                                   (0x00000045001c00U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_DAT_REG0_START                                             (0x00000400000000U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG0_DAT_REG0_END                                               (0x000004ffffffffU)

/* Properties of firewall at slave: FSS0_FSAS_0_DAT_REG3 */
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_ID                                                         (7U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_MMR_BASE                                                   (0x00000045001c00U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_DAT_REG3_START                                             (0x00000500000000U)
#define CSL_STD_FW_FSS0_FSAS_0_DAT_REG3_DAT_REG3_END                                               (0x000005ffffffffU)

/* Properties of firewall at slave: DMASS0_ECC_AGGR_0_ECCAGGR_REGS */
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_ID                                               (9U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_START                                    (0x0000003f005000U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_END                                      (0x0000003f0053ffU)

/* Properties of firewall at slave: DMASS1_ECC_AGGR_0_ECCAGGR_REGS */
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_ID                                               (9U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_START                                    (0x0000003f006000U)
#define CSL_STD_FW_DMASS1_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_END                                      (0x0000003f0063ffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_INTR */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_ID                                                (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_INTAGGR_INTR_START                                (0x00000048000000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_INTR_INTAGGR_INTR_END                                  (0x000000480fffffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_IMAP */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_ID                                                (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_INTAGGR_IMAP_START                                (0x00000048100000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_IMAP_INTAGGR_IMAP_END                                  (0x00000048103fffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_CFG */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_INTAGGR_CFG_START                                  (0x00000048110000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_CFG_INTAGGR_CFG_END                                    (0x0000004811001fU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_L2G */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_INTAGGR_L2G_START                                  (0x00000048120000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_L2G_INTAGGR_L2G_END                                    (0x000000481203ffU)

/* Properties of firewall at slave: DMASS0_PSILCFG_0_PSILCFG_PROXY */
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_ID                                               (9U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_PSILCFG_PROXY_START                              (0x00000048130000U)
#define CSL_STD_FW_DMASS0_PSILCFG_0_PSILCFG_PROXY_PSILCFG_PROXY_END                                (0x000000481301ffU)

/* Properties of firewall at slave: DMASS0_PSILSS_0_PSILSS_MMRS */
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_PSILSS_MMRS_START                                   (0x00000048140000U)
#define CSL_STD_FW_DMASS0_PSILSS_0_PSILSS_MMRS_PSILSS_MMRS_END                                     (0x00000048140fffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_UNMAP */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_ID                                               (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_INTAGGR_UNMAP_START                              (0x00000048180000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_UNMAP_INTAGGR_UNMAP_END                                (0x0000004819ffffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_MCAST */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_ID                                               (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_INTAGGR_MCAST_START                              (0x00000048210000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_MCAST_INTAGGR_MCAST_END                                (0x00000048210fffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_GCNTCFG */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_ID                                             (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_MMR_BASE                                       (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_NUM_REGIONS                                    (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_INTAGGR_GCNTCFG_START                          (0x00000048220000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTCFG_INTAGGR_GCNTCFG_END                            (0x00000048221fffU)

/* Properties of firewall at slave: DMASS0_PSILSS_0_ETLSW_MMRS */
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_ID                                                   (9U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_ETLSW_MMRS_START                                     (0x00000048230000U)
#define CSL_STD_FW_DMASS0_PSILSS_0_ETLSW_MMRS_ETLSW_MMRS_END                                       (0x00000048230fffU)

/* Properties of firewall at slave: DMASS0_RINGACC_0_RINGACC_GCFG */
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_ID                                                (9U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_RINGACC_GCFG_START                                (0x00000048240000U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_GCFG_RINGACC_GCFG_END                                  (0x000000482403ffU)

/* Properties of firewall at slave: DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS */
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_ID                                            (9U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_MMR_BASE                                      (0x00000045002400U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_NUM_REGIONS                                   (32U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_SEC_PROXY_MMRS_START                          (0x00000048250000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_MMRS_SEC_PROXY_MMRS_END                            (0x000000482500ffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_BCHAN */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_ID                                                   (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_BCDMA_BCHAN_START                                    (0x00000048420000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHAN_BCDMA_BCHAN_END                                      (0x00000048421fffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RFLOW */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_PKTDMA_RFLOW_START                                 (0x00000048430000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RFLOW_PKTDMA_RFLOW_END                                   (0x00000048430fffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_TCHAN */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_PKTDMA_TCHAN_START                                 (0x000000484a0000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_PKTDMA_TCHAN_END                                   (0x000000484a1fffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_TCHAN */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_ID                                                   (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_BCDMA_TCHAN_START                                    (0x000000484a4000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_BCDMA_TCHAN_END                                      (0x000000484a5fffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RCHAN */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_PKTDMA_RCHAN_START                                 (0x000000484c0000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHAN_PKTDMA_RCHAN_END                                   (0x000000484c1fffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_RCHAN */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_ID                                                   (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_START                                    (0x000000484c2000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_END                                      (0x000000484c3fffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_GCFG */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_PKTDMA_GCFG_START                                   (0x000000485c0000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_GCFG_PKTDMA_GCFG_END                                     (0x000000485c00ffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_GCFG */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_ID                                                    (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_MMR_BASE                                              (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_NUM_REGIONS                                           (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_BCDMA_GCFG_START                                      (0x000000485c0100U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_GCFG_BCDMA_GCFG_END                                        (0x000000485c01ffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RING */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_PKTDMA_RING_START                                   (0x000000485e0000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RING_PKTDMA_RING_END                                     (0x000000485effffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_RING */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_ID                                                    (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_MMR_BASE                                              (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_NUM_REGIONS                                           (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_BCDMA_RING_START                                      (0x00000048600000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RING_BCDMA_RING_END                                        (0x00000048607fffU)

/* Properties of firewall at slave: DMASS0_RINGACC_0_RINGACC_RT */
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_RINGACC_RT_START                                    (0x00000049000000U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_RT_RINGACC_RT_END                                      (0x000000493fffffU)

/* Properties of firewall at slave: DMASS0_RINGACC_0_RINGACC_CFG */
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_RINGACC_CFG_START                                  (0x00000049800000U)
#define CSL_STD_FW_DMASS0_RINGACC_0_RINGACC_CFG_RINGACC_CFG_END                                    (0x0000004983ffffU)

/* Properties of firewall at slave: DMASS0_INTAGGR_0_INTAGGR_GCNTRTI */
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_ID                                             (9U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_MMR_BASE                                       (0x00000045002400U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_NUM_REGIONS                                    (32U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_INTAGGR_GCNTRTI_START                          (0x0000004a000000U)
#define CSL_STD_FW_DMASS0_INTAGGR_0_INTAGGR_GCNTRTI_INTAGGR_GCNTRTI_END                            (0x0000004a0fffffU)

/* Properties of firewall at slave: DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG */
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_ID                                            (9U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_MMR_BASE                                      (0x00000045002400U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_NUM_REGIONS                                   (32U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_SEC_PROXY_SCFG_START                          (0x0000004a400000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SCFG_SEC_PROXY_SCFG_END                            (0x0000004a47ffffU)

/* Properties of firewall at slave: DMASS0_SEC_PROXY_0_SEC_PROXY_RT */
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_ID                                              (9U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_MMR_BASE                                        (0x00000045002400U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_NUM_REGIONS                                     (32U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_SEC_PROXY_RT_START                              (0x0000004a600000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_RT_SEC_PROXY_RT_END                                (0x0000004a67ffffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RCHANRT */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_ID                                               (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_PKTDMA_RCHANRT_START                             (0x0000004a800000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RCHANRT_PKTDMA_RCHANRT_END                               (0x0000004a81ffffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_RCHANRT */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_START                                (0x0000004a820000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_END                                  (0x0000004a83ffffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_TCHANRT */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_ID                                               (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_PKTDMA_TCHANRT_START                             (0x0000004aa00000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_PKTDMA_TCHANRT_END                               (0x0000004aa1ffffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_TCHANRT */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_BCDMA_TCHANRT_START                                (0x0000004aa40000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_BCDMA_TCHANRT_END                                  (0x0000004aa5ffffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_RINGRT */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_ID                                                (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_PKTDMA_RINGRT_START                               (0x0000004b800000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_RINGRT_PKTDMA_RINGRT_END                                 (0x0000004b9fffffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_RINGRT */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_ID                                                  (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_BCDMA_RINGRT_START                                  (0x0000004bc00000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RINGRT_BCDMA_RINGRT_END                                    (0x0000004bcfffffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_BCHANRT */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_BCDMA_BCHANRT_START                                (0x0000004c000000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_BCDMA_BCHANRT_END                                  (0x0000004c01ffffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_GCNTRTI */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_ID                                             (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_MMR_BASE                                       (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_NUM_REGIONS                                    (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_INTAGGR_GCNTRTI_START                          (0x0000004e000000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTRTI_INTAGGR_GCNTRTI_END                            (0x0000004e01ffffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_UNMAP */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_ID                                               (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_INTAGGR_UNMAP_START                              (0x0000004e040000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_UNMAP_INTAGGR_UNMAP_END                                (0x0000004e04ffffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_MCAST */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_ID                                               (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_INTAGGR_MCAST_START                              (0x0000004e080000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_MCAST_INTAGGR_MCAST_END                                (0x0000004e0803ffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_GCNTCFG */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_ID                                             (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_MMR_BASE                                       (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_NUM_REGIONS                                    (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_INTAGGR_GCNTCFG_START                          (0x0000004e090000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_GCNTCFG_INTAGGR_GCNTCFG_END                            (0x0000004e0903ffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_INTR */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_ID                                                (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_INTAGGR_INTR_START                                (0x0000004e0a0000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_INTR_INTAGGR_INTR_END                                  (0x0000004e0a7fffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_IMAP */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_ID                                                (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_MMR_BASE                                          (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_NUM_REGIONS                                       (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_INTAGGR_IMAP_START                                (0x0000004e0b0000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_IMAP_INTAGGR_IMAP_END                                  (0x0000004e0b03ffU)

/* Properties of firewall at slave: DMASS1_INTAGGR_0_INTAGGR_CFG */
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_ID                                                 (9U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_INTAGGR_CFG_START                                  (0x0000004e0c0000U)
#define CSL_STD_FW_DMASS1_INTAGGR_0_INTAGGR_CFG_INTAGGR_CFG_END                                    (0x0000004e0c001fU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_RINGRT */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_ID                                                  (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_BCDMA_RINGRT_START                                  (0x0000004e100000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RINGRT_BCDMA_RINGRT_END                                    (0x0000004e10ffffU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_RCHANRT */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_ID                                                 (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_START                                (0x0000004e180000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_END                                  (0x0000004e187fffU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_RCHAN */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_ID                                                   (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_START                                    (0x0000004e200000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_END                                      (0x0000004e2007ffU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_RING */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_ID                                                    (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_MMR_BASE                                              (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_NUM_REGIONS                                           (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_BCDMA_RING_START                                      (0x0000004e210000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_RING_BCDMA_RING_END                                        (0x0000004e2107ffU)

/* Properties of firewall at slave: DMASS1_PSILSS_0_PSILSS_MMRS */
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_ID                                                  (9U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_MMR_BASE                                            (0x00000045002400U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_NUM_REGIONS                                         (32U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_PSILSS_MMRS_START                                   (0x0000004e220000U)
#define CSL_STD_FW_DMASS1_PSILSS_0_PSILSS_MMRS_PSILSS_MMRS_END                                     (0x0000004e220fffU)

/* Properties of firewall at slave: DMASS1_BCDMA_0_BCDMA_GCFG */
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_ID                                                    (9U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_MMR_BASE                                              (0x00000045002400U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_NUM_REGIONS                                           (32U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_BCDMA_GCFG_START                                      (0x0000004e230000U)
#define CSL_STD_FW_DMASS1_BCDMA_0_BCDMA_GCFG_BCDMA_GCFG_END                                        (0x0000004e2300ffU)

/* Properties of firewall at slave: DMASS1_PSILCFG_0_PSILCFG_PROXY */
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_ID                                               (9U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_PSILCFG_PROXY_START                              (0x0000004e260000U)
#define CSL_STD_FW_DMASS1_PSILCFG_0_PSILCFG_PROXY_PSILCFG_PROXY_END                                (0x0000004e2601ffU)

/* Properties of firewall at slave: CBASS_DBG0_ERR_REGS */
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_ID                                                          (10U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_MMR_BASE                                                    (0x00000045002800U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_ERR_START                                                   (0x00000000200000U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_ERR_END                                                     (0x000000002003ffU)

/* Properties of firewall at slave: COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS */
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_ID                       (10U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_TYPE                     (CSL_FW_SECURITY)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_MMR_BASE                 (0x00000045002800U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_NUM_REGIONS              (16U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_NUM_PRIV_IDS_PER_REGION  (3U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_PBIST_START              (0x00000000330000U)
#define CSL_STD_FW_COMPUTE_CLUSTER0_PBIST_0_K3_PBIST_4C28P_4BIT_WRAP_REGS_PBIST_END                (0x000000003303ffU)

/* Properties of firewall at slave: PBIST3_MEM */
#define CSL_STD_FW_PBIST3_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST3_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST3_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST3_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST3_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST3_MEM_START                                                                (0x00000000340000U)
#define CSL_STD_FW_PBIST3_MEM_END                                                                  (0x000000003403ffU)

/* Properties of firewall at slave: VPAC0_MEM */
#define CSL_STD_FW_VPAC0_MEM_ID                                                                    (10U)
#define CSL_STD_FW_VPAC0_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_MEM_MMR_BASE                                                              (0x00000045002800U)
#define CSL_STD_FW_VPAC0_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_VPAC0_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_VPAC0_MEM_MEM_START                                                             (0x00000000350000U)
#define CSL_STD_FW_VPAC0_MEM_MEM_END                                                               (0x000000003503ffU)

/* Properties of firewall at slave: C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST */
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_ID                                   (10U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_MMR_BASE                             (0x00000045002800U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_NUM_REGIONS                          (16U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_PBIST_START                          (0x00000000360000U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_PBIST_END                            (0x000000003603ffU)

/* Properties of firewall at slave: USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE */
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_ID                          (10U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_TYPE                        (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_MMR_BASE                    (0x00000045002800U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_REGIONS                 (16U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_PRIV_IDS_PER_REGION     (3U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_START (0x00000000703000U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_END (0x000000007031ffU)

/* Properties of firewall at slave: USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE */
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_ID                          (10U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_TYPE                        (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_MMR_BASE                    (0x00000045002800U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_REGIONS                 (16U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_PRIV_IDS_PER_REGION     (3U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_START (0x0000000070c000U)
#define CSL_STD_FW_USB1_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_END (0x0000000070c1ffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_COREPAC_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_ID                                                 (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_MMR_BASE                                           (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_SS_ECC_AGGR_START                                  (0x00000000718000U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_COREPAC_REGS_SS_ECC_AGGR_END                                    (0x000000007183ffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_CORE0_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_ID                                                   (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_CORE0_ECC_AGGR_START                                 (0x00000000718400U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE0_REGS_CORE0_ECC_AGGR_END                                   (0x000000007187ffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_CORE1_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_ID                                                   (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_CORE1_ECC_AGGR_START                                 (0x00000000718800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE1_REGS_CORE1_ECC_AGGR_END                                   (0x00000000718bffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_CORE2_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_ID                                                   (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_CORE2_ECC_AGGR_START                                 (0x00000000718c00U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE2_REGS_CORE2_ECC_AGGR_END                                   (0x00000000718fffU)

/* Properties of firewall at slave: A53SS0_ECC_AGGR_CORE3_REGS */
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_ID                                                   (10U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_CORE3_ECC_AGGR_START                                 (0x00000000719000U)
#define CSL_STD_FW_A53SS0_ECC_AGGR_CORE3_REGS_CORE3_ECC_AGGR_END                                   (0x000000007193ffU)

/* Properties of firewall at slave: C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS */
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_ID                                         (10U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_MMR_BASE                                   (0x00000045002800U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_ECC_AGGR_START                             (0x0000000071a000U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_ECC_AGGR_END                               (0x0000000071a3ffU)

/* Properties of firewall at slave: TIMER0_CFG */
#define CSL_STD_FW_TIMER0_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER0_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER0_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER0_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER0_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER0_CFG_CFG_START                                                            (0x00000002400000U)
#define CSL_STD_FW_TIMER0_CFG_CFG_END                                                              (0x000000024003ffU)

/* Properties of firewall at slave: TIMER1_CFG */
#define CSL_STD_FW_TIMER1_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER1_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER1_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER1_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER1_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER1_CFG_CFG_START                                                            (0x00000002410000U)
#define CSL_STD_FW_TIMER1_CFG_CFG_END                                                              (0x000000024103ffU)

/* Properties of firewall at slave: TIMER2_CFG */
#define CSL_STD_FW_TIMER2_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER2_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER2_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER2_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER2_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER2_CFG_CFG_START                                                            (0x00000002420000U)
#define CSL_STD_FW_TIMER2_CFG_CFG_END                                                              (0x000000024203ffU)

/* Properties of firewall at slave: TIMER3_CFG */
#define CSL_STD_FW_TIMER3_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER3_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER3_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER3_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER3_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER3_CFG_CFG_START                                                            (0x00000002430000U)
#define CSL_STD_FW_TIMER3_CFG_CFG_END                                                              (0x000000024303ffU)

/* Properties of firewall at slave: TIMER4_CFG */
#define CSL_STD_FW_TIMER4_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER4_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER4_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER4_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER4_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER4_CFG_CFG_START                                                            (0x00000002440000U)
#define CSL_STD_FW_TIMER4_CFG_CFG_END                                                              (0x000000024403ffU)

/* Properties of firewall at slave: TIMER5_CFG */
#define CSL_STD_FW_TIMER5_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER5_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER5_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER5_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER5_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER5_CFG_CFG_START                                                            (0x00000002450000U)
#define CSL_STD_FW_TIMER5_CFG_CFG_END                                                              (0x000000024503ffU)

/* Properties of firewall at slave: TIMER6_CFG */
#define CSL_STD_FW_TIMER6_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER6_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER6_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER6_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER6_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER6_CFG_CFG_START                                                            (0x00000002460000U)
#define CSL_STD_FW_TIMER6_CFG_CFG_END                                                              (0x000000024603ffU)

/* Properties of firewall at slave: TIMER7_CFG */
#define CSL_STD_FW_TIMER7_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER7_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER7_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER7_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER7_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER7_CFG_CFG_START                                                            (0x00000002470000U)
#define CSL_STD_FW_TIMER7_CFG_CFG_END                                                              (0x000000024703ffU)

/* Properties of firewall at slave: RTI0_CFG */
#define CSL_STD_FW_RTI0_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI0_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI0_CFG_CFG_START                                                              (0x0000000e000000U)
#define CSL_STD_FW_RTI0_CFG_CFG_END                                                                (0x0000000e0000ffU)

/* Properties of firewall at slave: RTI1_CFG */
#define CSL_STD_FW_RTI1_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI1_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI1_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI1_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI1_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI1_CFG_CFG_START                                                              (0x0000000e010000U)
#define CSL_STD_FW_RTI1_CFG_CFG_END                                                                (0x0000000e0100ffU)

/* Properties of firewall at slave: RTI2_CFG */
#define CSL_STD_FW_RTI2_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI2_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI2_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI2_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI2_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI2_CFG_CFG_START                                                              (0x0000000e020000U)
#define CSL_STD_FW_RTI2_CFG_CFG_END                                                                (0x0000000e0200ffU)

/* Properties of firewall at slave: RTI3_CFG */
#define CSL_STD_FW_RTI3_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI3_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI3_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI3_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI3_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI3_CFG_CFG_START                                                              (0x0000000e030000U)
#define CSL_STD_FW_RTI3_CFG_CFG_END                                                                (0x0000000e0300ffU)

/* Properties of firewall at slave: RTI4_CFG */
#define CSL_STD_FW_RTI4_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI4_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI4_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI4_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI4_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI4_CFG_CFG_START                                                              (0x0000000e040000U)
#define CSL_STD_FW_RTI4_CFG_CFG_END                                                                (0x0000000e0400ffU)

/* Properties of firewall at slave: DDR32SS0_REGS_SS_CFG_SSCFG */
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_ID                                                   (10U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_REGS_SS_CFG_SSCFG_START                              (0x0000000f300000U)
#define CSL_STD_FW_DDR32SS0_REGS_SS_CFG_SSCFG_REGS_SS_CFG_SSCFG_END                                (0x0000000f3001ffU)

/* Properties of firewall at slave: DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG */
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_ID                                          (10U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_MMR_BASE                                    (0x00000045002800U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_NUM_REGIONS                                 (16U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_CTLPHY_WRAP_CTL_CFG_CTLCFG_START            (0x0000000f308000U)
#define CSL_STD_FW_DDR32SS0_CTLPHY_WRAP_CTL_CFG_CTLCFG_CTLPHY_WRAP_CTL_CFG_CTLCFG_END              (0x0000000f30ffffU)

/* Properties of firewall at slave: USB0_MMR_MMRVBP_USB2SS_CFG */
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_ID                                                   (10U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_MMR_MMRVBP_USB2SS_CFG_START                          (0x0000000f900000U)
#define CSL_STD_FW_USB0_MMR_MMRVBP_USB2SS_CFG_MMR_MMRVBP_USB2SS_CFG_END                            (0x0000000f9007ffU)

/* Properties of firewall at slave: USB0_PHY2 */
#define CSL_STD_FW_USB0_PHY2_ID                                                                    (10U)
#define CSL_STD_FW_USB0_PHY2_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_PHY2_MMR_BASE                                                              (0x00000045002800U)
#define CSL_STD_FW_USB0_PHY2_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_USB0_PHY2_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_USB0_PHY2_PHY2_START                                                            (0x0000000f908000U)
#define CSL_STD_FW_USB0_PHY2_PHY2_END                                                              (0x0000000f9083ffU)

/* Properties of firewall at slave: USB1_MMR_MMRVBP_USB2SS_CFG */
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_ID                                                   (10U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_MMR_MMRVBP_USB2SS_CFG_START                          (0x0000000f910000U)
#define CSL_STD_FW_USB1_MMR_MMRVBP_USB2SS_CFG_MMR_MMRVBP_USB2SS_CFG_END                            (0x0000000f9107ffU)

/* Properties of firewall at slave: USB1_PHY2 */
#define CSL_STD_FW_USB1_PHY2_ID                                                                    (10U)
#define CSL_STD_FW_USB1_PHY2_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_PHY2_MMR_BASE                                                              (0x00000045002800U)
#define CSL_STD_FW_USB1_PHY2_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_USB1_PHY2_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_USB1_PHY2_PHY2_START                                                            (0x0000000f918000U)
#define CSL_STD_FW_USB1_PHY2_PHY2_END                                                              (0x0000000f9183ffU)

/* Properties of firewall at slave: USB0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_ID                                                       (10U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_MMR_BASE                                                 (0x00000045002800U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_NUM_REGIONS                                              (16U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_ECC_AGGR_START                                           (0x0000000f980000U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_ECC_AGGR_END                                             (0x0000000f9803ffU)

/* Properties of firewall at slave: USB1_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_ID                                                       (10U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_MMR_BASE                                                 (0x00000045002800U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_NUM_REGIONS                                              (16U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_ECC_AGGR_START                                           (0x0000000f990000U)
#define CSL_STD_FW_USB1_ECC_AGGR_CFG_REGS_ECC_AGGR_END                                             (0x0000000f9903ffU)

/* Properties of firewall at slave: JPGENC0_CORE_REGS */
#define CSL_STD_FW_JPGENC0_CORE_REGS_ID                                                            (10U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_TYPE                                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_JPGENC0_CORE_REGS_MMR_BASE                                                      (0x00000045002800U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_NUM_REGIONS                                                   (16U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_NUM_PRIV_IDS_PER_REGION                                       (3U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_CORE_START                                                    (0x0000000fd20000U)
#define CSL_STD_FW_JPGENC0_CORE_REGS_CORE_END                                                      (0x0000000fd200ffU)

/* Properties of firewall at slave: JPGENC0_CORE_MMU_REGS */
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_ID                                                        (10U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_MMR_BASE                                                  (0x00000045002800U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_CORE_MMU_START                                            (0x0000000fd20200U)
#define CSL_STD_FW_JPGENC0_CORE_MMU_REGS_CORE_MMU_END                                              (0x0000000fd203ffU)

/* Properties of firewall at slave: ELM0_MEM */
#define CSL_STD_FW_ELM0_MEM_ID                                                                     (10U)
#define CSL_STD_FW_ELM0_MEM_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_ELM0_MEM_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_ELM0_MEM_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_ELM0_MEM_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_ELM0_MEM_START                                                                  (0x00000025010000U)
#define CSL_STD_FW_ELM0_MEM_END                                                                    (0x00000025010fffU)

/* Properties of firewall at slave: DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS */
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_ID                                 (10U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_MMR_BASE                           (0x00000045002800U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_NUM_REGIONS                        (16U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_START (0x00000030110000U)
#define CSL_STD_FW_DPHY_RX0_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_REGS_VBUS2APB_WRAP_VBUSP_K3_DPHY_RX_END (0x00000030110fffU)

/* Properties of firewall at slave: DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS */
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_ID                                           (10U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_MMR_BASE                                     (0x00000045002800U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_NUM_REGIONS                                  (16U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_MMR_SLV_K3_DPHY_WRAP_START                   (0x00000030111000U)
#define CSL_STD_FW_DPHY_RX0_MMR_SLV_K3_DPHY_WRAP_REGS_MMR_SLV_K3_DPHY_WRAP_END                     (0x000000301110ffU)

/* Properties of firewall at slave: CODEC0_VPU_REGS */
#define CSL_STD_FW_CODEC0_VPU_REGS_ID                                                              (10U)
#define CSL_STD_FW_CODEC0_VPU_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_CODEC0_VPU_REGS_MMR_BASE                                                        (0x00000045002800U)
#define CSL_STD_FW_CODEC0_VPU_REGS_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_CODEC0_VPU_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_CODEC0_VPU_REGS_VPU_START                                                       (0x00000030210000U)
#define CSL_STD_FW_CODEC0_VPU_REGS_VPU_END                                                         (0x0000003021ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_CFG_MMR */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_ID                                                  (10U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_MMR_BASE                                            (0x00000045002800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_NUM_REGIONS                                         (16U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_START                                               (0x00000030240000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_END                                                 (0x0000003024ffffU)

/* Properties of firewall at slave: VPAC_RSWS_BW_LIMITER7_REGS */
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_ID                                                   (10U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_REGS_START                                           (0x00000030400000U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER7_REGS_REGS_END                                             (0x00000030400fffU)

/* Properties of firewall at slave: CODEC_WS_BW_LIMITER3_REGS */
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_ID                                                    (10U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_MMR_BASE                                              (0x00000045002800U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_REGS_START                                            (0x00000030401000U)
#define CSL_STD_FW_CODEC_WS_BW_LIMITER3_REGS_REGS_END                                              (0x00000030401fffU)

/* Properties of firewall at slave: A53_WS_BW_LIMITER1_REGS */
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_ID                                                      (10U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_MMR_BASE                                                (0x00000045002800U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_NUM_REGIONS                                             (16U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_REGS_START                                              (0x00000030402000U)
#define CSL_STD_FW_A53_WS_BW_LIMITER1_REGS_REGS_END                                                (0x00000030402fffU)

/* Properties of firewall at slave: A53_RS_BW_LIMITER0_REGS */
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_ID                                                      (10U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_MMR_BASE                                                (0x00000045002800U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_NUM_REGIONS                                             (16U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_REGS_START                                              (0x00000030403000U)
#define CSL_STD_FW_A53_RS_BW_LIMITER0_REGS_REGS_END                                                (0x00000030403fffU)

/* Properties of firewall at slave: JPGENC_RS_BW_LIMITER4_REGS */
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_ID                                                   (10U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_REGS_START                                           (0x00000030404000U)
#define CSL_STD_FW_JPGENC_RS_BW_LIMITER4_REGS_REGS_END                                             (0x00000030404fffU)

/* Properties of firewall at slave: JPGENC_WS_BW_LIMITER5_REGS */
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_ID                                                   (10U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_REGS_START                                           (0x00000030405000U)
#define CSL_STD_FW_JPGENC_WS_BW_LIMITER5_REGS_REGS_END                                             (0x00000030405fffU)

/* Properties of firewall at slave: C7XV_RSWS_BS_LIMITER6_REGS */
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_ID                                                   (10U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_REGS_START                                           (0x00000030406000U)
#define CSL_STD_FW_C7XV_RSWS_BS_LIMITER6_REGS_REGS_END                                             (0x00000030406fffU)

/* Properties of firewall at slave: VPAC_RSWS_BW_LIMITER8_REGS */
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_ID                                                   (10U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_REGS_START                                           (0x00000030407000U)
#define CSL_STD_FW_VPAC_RSWS_BW_LIMITER8_REGS_REGS_END                                             (0x00000030407fffU)

/* Properties of firewall at slave: CODEC_RS_BW_LIMITER2_REGS */
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_ID                                                    (10U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_MMR_BASE                                              (0x00000045002800U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_REGS_START                                            (0x00000030408000U)
#define CSL_STD_FW_CODEC_RS_BW_LIMITER2_REGS_REGS_END                                              (0x00000030408fffU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_ID                               (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_START (0x00000031000000U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_END (0x0000003100001fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_ID                              (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_START (0x00000031000020U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_END (0x0000003100005fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_ID                              (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_START (0x00000031000420U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_END (0x0000003100043fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_ID                           (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_TYPE                         (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_MMR_BASE                     (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_NUM_REGIONS                  (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_NUM_PRIV_IDS_PER_REGION      (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_START (0x00000031000440U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_END (0x0000003100045fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_ID                              (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_START (0x00000031000460U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_END (0x0000003100049fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_ID                                (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_TYPE                              (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_MMR_BASE                          (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_NUM_REGIONS                       (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_NUM_PRIV_IDS_PER_REGION           (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_START (0x00000031000560U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_END (0x0000003100075fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_ID                            (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_TYPE                          (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_MMR_BASE                      (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_NUM_REGIONS                   (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_NUM_PRIV_IDS_PER_REGION       (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_START (0x00000031000960U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_END (0x0000003100096fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2 */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_ID                        (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_START (0x00000031000970U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_END (0x0000003100097fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3 */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_ID                        (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_START (0x00000031000980U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_END (0x0000003100099fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_ID                               (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_START (0x0000003100c100U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_END (0x0000003100c8ffU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_ID                               (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_START (0x0000003100c700U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_END (0x0000003100ceffU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_ID                              (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_START (0x0000003100d000U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_END (0x0000003100d07fU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_ID                             (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_MMR_BASE                       (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_NUM_REGIONS                    (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_START (0x0000003100d800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_END (0x0000003100d9ffU)

/* Properties of firewall at slave: USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0 */
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_ID                        (10U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_START (0x00000031040000U)
#define CSL_STD_FW_USB0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_END (0x0000003104ffffU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_ID                               (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_START (0x00000031100000U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_CAP_END (0x0000003110001fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_ID                              (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_START (0x00000031100020U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_OPER_END (0x0000003110005fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_ID                              (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_START (0x00000031100420U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_PORT_END (0x0000003110043fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_ID                           (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_TYPE                         (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_MMR_BASE                     (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_NUM_REGIONS                  (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_NUM_PRIV_IDS_PER_REGION      (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_START (0x00000031100440U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_RUNTIME_END (0x0000003110045fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_ID                              (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_START (0x00000031100460U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_INTR_END (0x0000003110049fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_ID                                (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_TYPE                              (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_MMR_BASE                          (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_NUM_REGIONS                       (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_NUM_PRIV_IDS_PER_REGION           (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_START (0x00000031100560U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DB_END (0x0000003110075fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_ID                            (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_TYPE                          (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_MMR_BASE                      (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_NUM_REGIONS                   (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_NUM_PRIV_IDS_PER_REGION       (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_START (0x00000031100960U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_EXTCAP_END (0x0000003110096fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2 */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_ID                        (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_START (0x00000031100970U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP2_END (0x0000003110097fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3 */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_ID                        (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_START (0x00000031100980U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_SUPPRTCAP3_END (0x0000003110099fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_ID                               (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_START (0x0000003110c100U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_GBL_END (0x0000003110c8ffU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_ID                               (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_MMR_BASE                         (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_NUM_REGIONS                      (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_START (0x0000003110c700U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEV_END (0x0000003110ceffU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_ID                              (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_TYPE                            (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_MMR_BASE                        (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_NUM_REGIONS                     (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_NUM_PRIV_IDS_PER_REGION         (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_START (0x0000003110d000U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_LINK_END (0x0000003110d07fU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_ID                             (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_MMR_BASE                       (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_NUM_REGIONS                    (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_START (0x0000003110d800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_END (0x0000003110d9ffU)

/* Properties of firewall at slave: USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0 */
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_ID                        (10U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_MMR_BASE                  (0x00000045002800U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_NUM_REGIONS               (16U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_START (0x00000031140000U)
#define CSL_STD_FW_USB1_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_VBP2AHB_WRAP_CONTROLLER_VBP_USB3_CORE_DEBUG_RAM0_END (0x0000003114ffffU)

/* Properties of firewall at slave: PBIST0_MEM */
#define CSL_STD_FW_PBIST0_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST0_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST0_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST0_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST0_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST0_MEM_START                                                                (0x0000003f110000U)
#define CSL_STD_FW_PBIST0_MEM_END                                                                  (0x0000003f1103ffU)

/* Properties of firewall at slave: CBASS_MCASP0_ERR_REGS */
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_ID                                                        (11U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_MMR_BASE                                                  (0x00000045002c00U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_ERR_START                                                 (0x00000000240000U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_ERR_END                                                   (0x000000002403ffU)

/* Properties of firewall at slave: CPSW0_CPSW_NUSS_VBUSP_ECC */
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_ID                                                    (11U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_MMR_BASE                                              (0x00000045002c00U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_ECC_START                                             (0x00000000704000U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_ECC_END                                               (0x000000007043ffU)

/* Properties of firewall at slave: MMCSD0_ECC_AGGR_RXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_START                             (0x00000000706000U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_END                               (0x000000007063ffU)

/* Properties of firewall at slave: MMCSD0_ECC_AGGR_TXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_START                             (0x00000000707000U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_END                               (0x000000007073ffU)

/* Properties of firewall at slave: MMCSD1_ECC_AGGR_RXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_START                             (0x00000000708000U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_END                               (0x000000007083ffU)

/* Properties of firewall at slave: MMCSD1_ECC_AGGR_TXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_START                             (0x00000000709000U)
#define CSL_STD_FW_MMCSD1_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_END                               (0x000000007093ffU)

/* Properties of firewall at slave: MMCSD2_ECC_AGGR_TXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_START                             (0x0000000070a000U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_END                               (0x0000000070a3ffU)

/* Properties of firewall at slave: MMCSD2_ECC_AGGR_RXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_START                             (0x0000000070b000U)
#define CSL_STD_FW_MMCSD2_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_END                               (0x0000000070b3ffU)

/* Properties of firewall at slave: CSI_RX_IF0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_ID                                                 (11U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_ECC_AGGR_CFG_START                                 (0x0000000070e000U)
#define CSL_STD_FW_CSI_RX_IF0_ECC_AGGR_CFG_REGS_ECC_AGGR_CFG_END                                   (0x0000000070e3ffU)

/* Properties of firewall at slave: MSRAM_64K0_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_ID                                                 (11U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                                (0x00000000710000U)
#define CSL_STD_FW_MSRAM_64K0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                                  (0x000000007103ffU)

/* Properties of firewall at slave: FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_ID                 (11U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_TYPE               (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE           (0x00000045002c00U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS        (16U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI0_ECC_AGGR_START (0x00000000716000U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI0_ECC_AGGR_END (0x000000007163ffU)

/* Properties of firewall at slave: GICSS0_GIC_TRANSLATER_REGS */
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_ID                                                   (11U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_MMR_BASE                                             (0x00000045002c00U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_GIC_TRANSLATER_START                                 (0x00000001000000U)
#define CSL_STD_FW_GICSS0_GIC_TRANSLATER_REGS_GIC_TRANSLATER_END                                   (0x000000013fffffU)

/* Properties of firewall at slave: GICSS0_GIC_REGS */
#define CSL_STD_FW_GICSS0_GIC_REGS_ID                                                              (11U)
#define CSL_STD_FW_GICSS0_GIC_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_GICSS0_GIC_REGS_MMR_BASE                                                        (0x00000045002c00U)
#define CSL_STD_FW_GICSS0_GIC_REGS_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_GICSS0_GIC_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_GICSS0_GIC_REGS_GIC_START                                                       (0x00000001800000U)
#define CSL_STD_FW_GICSS0_GIC_REGS_GIC_END                                                         (0x000000018fffffU)

/* Properties of firewall at slave: CPSW0_CPSW_NUSS_VBUSP */
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ID                                                        (11U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_MMR_BASE                                                  (0x00000045002c00U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUSS_START                                                (0x00000008000000U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUSS_END                                                  (0x000000081fffffU)

/* Properties of firewall at slave: MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG */
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_ID                                              (11U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_MMR_BASE                                        (0x00000045002c00U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_REGIONS                                     (16U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_START                                   (0x0000000fa00000U)
#define CSL_STD_FW_MMCSD1_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_END                                     (0x0000000fa00fffU)

/* Properties of firewall at slave: MMCSD1_REGS_SS_CFG_SSCFG */
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_ID                                                     (11U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_MMR_BASE                                               (0x00000045002c00U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_SS_CFG_START                                           (0x0000000fa08000U)
#define CSL_STD_FW_MMCSD1_REGS_SS_CFG_SSCFG_SS_CFG_END                                             (0x0000000fa083ffU)

/* Properties of firewall at slave: MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG */
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_ID                                              (11U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_MMR_BASE                                        (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_REGIONS                                     (16U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_START                                   (0x0000000fa10000U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_END                                     (0x0000000fa10fffU)

/* Properties of firewall at slave: MMCSD0_REGS_SS_CFG_SSCFG */
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_ID                                                     (11U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_MMR_BASE                                               (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_SS_CFG_START                                           (0x0000000fa18000U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_SS_CFG_END                                             (0x0000000fa183ffU)

/* Properties of firewall at slave: MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG */
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_ID                                              (11U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_MMR_BASE                                        (0x00000045002c00U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_REGIONS                                     (16U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_START                                   (0x0000000fa20000U)
#define CSL_STD_FW_MMCSD2_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_END                                     (0x0000000fa20fffU)

/* Properties of firewall at slave: MMCSD2_REGS_SS_CFG_SSCFG */
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_ID                                                     (11U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_MMR_BASE                                               (0x00000045002c00U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_SS_CFG_START                                           (0x0000000fa28000U)
#define CSL_STD_FW_MMCSD2_REGS_SS_CFG_SSCFG_SS_CFG_END                                             (0x0000000fa283ffU)

/* Properties of firewall at slave: FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS */
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_ID                                         (11U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_MMR_BASE                                   (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_CFG_START                                  (0x0000000fc00000U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_CFG_END                                    (0x0000000fc000ffU)

/* Properties of firewall at slave: FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS */
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_ID                                   (11U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_MMR_BASE                             (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_NUM_REGIONS                          (16U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_FSAS_CFG_START                       (0x0000000fc10000U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_FSAS_CFG_END                         (0x0000000fc100ffU)

/* Properties of firewall at slave: FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS */
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_ID                                (11U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_TYPE                              (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_MMR_BASE                          (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_NUM_REGIONS                       (16U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_NUM_PRIV_IDS_PER_REGION           (3U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_OTFA_CFG_START                    (0x0000000fc20000U)
#define CSL_STD_FW_FSS0_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_OTFA_CFG_END                      (0x0000000fc20fffU)

/* Properties of firewall at slave: FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS */
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_ID (11U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_MMR_BASE (0x00000045002c00U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_REGIONS (16U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI0_CTRL_START (0x0000000fc40000U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI0_CTRL_END (0x0000000fc400ffU)

/* Properties of firewall at slave: FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS */
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_ID                             (11U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_MMR_BASE                       (0x00000045002c00U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_REGIONS                    (16U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI0_SS_CFG_START             (0x0000000fc44000U)
#define CSL_STD_FW_FSS0_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI0_SS_CFG_END               (0x0000000fc441ffU)

/* Properties of firewall at slave: CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG */
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_ID                                         (11U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_MMR_BASE                                   (0x00000045002c00U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_NUM_REGIONS                                (16U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_CP_INTD_CFG_INTD_CFG_START                 (0x00000030100000U)
#define CSL_STD_FW_CSI_RX_IF0_CP_INTD_INTD_CFG_INTD_CFG_CP_INTD_CFG_INTD_CFG_END                   (0x00000030100fffU)

/* Properties of firewall at slave: CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS */
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_ID                               (11U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_MMR_BASE                         (0x00000045002c00U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_NUM_REGIONS                      (16U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_START (0x00000030101000U)
#define CSL_STD_FW_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_REGS_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_END (0x00000030101fffU)

/* Properties of firewall at slave: CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS */
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_ID                                   (11U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_MMR_BASE                             (0x00000045002c00U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_NUM_REGIONS                          (16U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_RX_SHIM_VBUSP_MMR_CSI2RXIF_START     (0x00000030102000U)
#define CSL_STD_FW_CSI_RX_IF0_RX_SHIM_VBUSP_MMR_CSI2RXIF_REGS_RX_SHIM_VBUSP_MMR_CSI2RXIF_END       (0x00000030102fffU)

/* Properties of firewall at slave: DSS0_COMMON */
#define CSL_STD_FW_DSS0_COMMON_ID                                                                  (11U)
#define CSL_STD_FW_DSS0_COMMON_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_COMMON_MMR_BASE                                                            (0x00000045002c00U)
#define CSL_STD_FW_DSS0_COMMON_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_DSS0_COMMON_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_DSS0_COMMON_COMMON_START                                                        (0x00000030200000U)
#define CSL_STD_FW_DSS0_COMMON_COMMON_END                                                          (0x00000030200fffU)

/* Properties of firewall at slave: DSS0_COMMON1 */
#define CSL_STD_FW_DSS0_COMMON1_ID                                                                 (11U)
#define CSL_STD_FW_DSS0_COMMON1_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_COMMON1_MMR_BASE                                                           (0x00000045002c00U)
#define CSL_STD_FW_DSS0_COMMON1_NUM_REGIONS                                                        (16U)
#define CSL_STD_FW_DSS0_COMMON1_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_DSS0_COMMON1_COMMON1_START                                                      (0x00000030201000U)
#define CSL_STD_FW_DSS0_COMMON1_COMMON1_END                                                        (0x00000030201fffU)

/* Properties of firewall at slave: DSS0_VIDL1 */
#define CSL_STD_FW_DSS0_VIDL1_ID                                                                   (11U)
#define CSL_STD_FW_DSS0_VIDL1_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_VIDL1_MMR_BASE                                                             (0x00000045002c00U)
#define CSL_STD_FW_DSS0_VIDL1_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_DSS0_VIDL1_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_DSS0_VIDL1_VIDL1_START                                                          (0x00000030202000U)
#define CSL_STD_FW_DSS0_VIDL1_VIDL1_END                                                            (0x00000030202fffU)

/* Properties of firewall at slave: DSS0_VID */
#define CSL_STD_FW_DSS0_VID_ID                                                                     (11U)
#define CSL_STD_FW_DSS0_VID_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_VID_MMR_BASE                                                               (0x00000045002c00U)
#define CSL_STD_FW_DSS0_VID_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DSS0_VID_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DSS0_VID_VID_START                                                              (0x00000030206000U)
#define CSL_STD_FW_DSS0_VID_VID_END                                                                (0x00000030206fffU)

/* Properties of firewall at slave: DSS0_OVR1 */
#define CSL_STD_FW_DSS0_OVR1_ID                                                                    (11U)
#define CSL_STD_FW_DSS0_OVR1_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_OVR1_MMR_BASE                                                              (0x00000045002c00U)
#define CSL_STD_FW_DSS0_OVR1_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_DSS0_OVR1_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_DSS0_OVR1_OVR1_START                                                            (0x00000030207000U)
#define CSL_STD_FW_DSS0_OVR1_OVR1_END                                                              (0x00000030207fffU)

/* Properties of firewall at slave: DSS0_OVR2 */
#define CSL_STD_FW_DSS0_OVR2_ID                                                                    (11U)
#define CSL_STD_FW_DSS0_OVR2_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_OVR2_MMR_BASE                                                              (0x00000045002c00U)
#define CSL_STD_FW_DSS0_OVR2_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_DSS0_OVR2_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_DSS0_OVR2_OVR2_START                                                            (0x00000030208000U)
#define CSL_STD_FW_DSS0_OVR2_OVR2_END                                                              (0x00000030208fffU)

/* Properties of firewall at slave: DSS0_VP1 */
#define CSL_STD_FW_DSS0_VP1_ID                                                                     (11U)
#define CSL_STD_FW_DSS0_VP1_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_VP1_MMR_BASE                                                               (0x00000045002c00U)
#define CSL_STD_FW_DSS0_VP1_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DSS0_VP1_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DSS0_VP1_VP1_START                                                              (0x0000003020a000U)
#define CSL_STD_FW_DSS0_VP1_VP1_END                                                                (0x0000003020afffU)

/* Properties of firewall at slave: DSS0_VP2 */
#define CSL_STD_FW_DSS0_VP2_ID                                                                     (11U)
#define CSL_STD_FW_DSS0_VP2_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DSS0_VP2_MMR_BASE                                                               (0x00000045002c00U)
#define CSL_STD_FW_DSS0_VP2_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DSS0_VP2_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DSS0_VP2_VP2_START                                                              (0x0000003020b000U)
#define CSL_STD_FW_DSS0_VP2_VP2_END                                                                (0x0000003020bfffU)

/* Properties of firewall at slave: CBASS0_ERR_REGS */
#define CSL_STD_FW_CBASS0_ERR_REGS_ID                                                              (11U)
#define CSL_STD_FW_CBASS0_ERR_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS0_ERR_REGS_MMR_BASE                                                        (0x00000045002c00U)
#define CSL_STD_FW_CBASS0_ERR_REGS_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_CBASS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_CBASS0_ERR_REGS_ERR_START                                                       (0x0000003a000000U)
#define CSL_STD_FW_CBASS0_ERR_REGS_ERR_END                                                         (0x0000003a0003ffU)

/* Properties of firewall at slave: GICSS0_REGS */
#define CSL_STD_FW_GICSS0_REGS_ID                                                                  (11U)
#define CSL_STD_FW_GICSS0_REGS_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_GICSS0_REGS_MMR_BASE                                                            (0x00000045002c00U)
#define CSL_STD_FW_GICSS0_REGS_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_GICSS0_REGS_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_GICSS0_REGS_REGS_START                                                          (0x0000003f004000U)
#define CSL_STD_FW_GICSS0_REGS_REGS_END                                                            (0x0000003f0043ffU)

/* Properties of firewall at slave: MCRC64_0_MCRC64_REGS */
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_ID                                                         (13U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_MMR_BASE                                                   (0x00000045003400U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_REGS_START                                                 (0x00000030300000U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_REGS_END                                                   (0x00000030300fffU)

/* Properties of firewall at slave: MSRAM_64K0_RAM */
#define CSL_STD_FW_MSRAM_64K0_RAM_ID                                                               (15U)
#define CSL_STD_FW_MSRAM_64K0_RAM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_64K0_RAM_MMR_BASE                                                         (0x00000045003c00U)
#define CSL_STD_FW_MSRAM_64K0_RAM_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_MSRAM_64K0_RAM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MSRAM_64K0_RAM_RAM_START                                                        (0x00000043c40000U)
#define CSL_STD_FW_MSRAM_64K0_RAM_RAM_END                                                          (0x00000043c4ffffU)

/* Properties of firewall at slave: WKUP_R5FSS0_CORE0_ICACHE0 */
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_ID                                                    (32U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_MMR_BASE                                              (0x00000045008000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_START                                    (0x00000074000000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_END                                      (0x000000747fffffU)

/* Properties of firewall at slave: WKUP_R5FSS0_CORE0_DCACHE0 */
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_ID                                                    (32U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_MMR_BASE                                              (0x00000045008000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_START                                    (0x00000074800000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_END                                      (0x00000074ffffffU)

/* Properties of firewall at slave: WKUP_R5FSS0_CORE0_ATCM0 */
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_ID                                                      (32U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_MMR_BASE                                                (0x00000045008000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_CORE0_ATCM_START                                        (0x00000078000000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_ATCM0_CORE0_ATCM_END                                          (0x00000078007fffU)

/* Properties of firewall at slave: WKUP_R5FSS0_CORE0_BTCM0 */
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_ID                                                      (32U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_MMR_BASE                                                (0x00000045008000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_CORE0_BTCM_START                                        (0x00000078100000U)
#define CSL_STD_FW_WKUP_R5FSS0_CORE0_BTCM0_CORE0_BTCM_END                                          (0x00000078107fffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG0 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_GTC_CFG0_START                                               (0x00000000a80000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_GTC_CFG0_END                                                 (0x00000000a803ffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG1 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_GTC_CFG1_START                                               (0x00000000a90000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_GTC_CFG1_END                                                 (0x00000000a93fffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG2 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_GTC_CFG2_START                                               (0x00000000aa0000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_GTC_CFG2_END                                                 (0x00000000aa3fffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG3 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_GTC_CFG3_START                                               (0x00000000ab0000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_GTC_CFG3_END                                                 (0x00000000ab3fffU)

/* Properties of firewall at slave: WKUP_VTM0_MMR_VBUSP_CFG1 */
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_ID                                                     (34U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_MMR_BASE                                               (0x00000045008800U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_MMR_VBUSP_CFG1_START                                   (0x00000000b00000U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_MMR_VBUSP_CFG1_END                                     (0x00000000b003ffU)

/* Properties of firewall at slave: WKUP_VTM0_MMR_VBUSP_CFG2 */
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_ID                                                     (34U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_MMR_BASE                                               (0x00000045008800U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_MMR_VBUSP_CFG2_START                                   (0x00000000b01000U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_MMR_VBUSP_CFG2_END                                     (0x00000000b013ffU)

/* Properties of firewall at slave: WKUP_VTM0_ECCAGGR_CFG_REGS */
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_ID                                                  (34U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_MMR_BASE                                            (0x00000045008800U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_NUM_REGIONS                                         (16U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_START                                   (0x00000000b02000U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_END                                     (0x00000000b023ffU)

/* Properties of firewall at slave: WKUP_RTI0_CFG */
#define CSL_STD_FW_WKUP_RTI0_CFG_ID                                                                (34U)
#define CSL_STD_FW_WKUP_RTI0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_RTI0_CFG_MMR_BASE                                                          (0x00000045008800U)
#define CSL_STD_FW_WKUP_RTI0_CFG_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_WKUP_RTI0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_RTI0_CFG_CFG_START                                                         (0x0000002b000000U)
#define CSL_STD_FW_WKUP_RTI0_CFG_CFG_END                                                           (0x0000002b0000ffU)

/* Properties of firewall at slave: WKUP_RTCSS0_RTC_REGS */
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_ID                                                         (34U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_MMR_BASE                                                   (0x00000045008800U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_NUM_REGIONS                                                (16U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_RTC_START                                                  (0x0000002b1f0000U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_RTC_END                                                    (0x0000002b1f007fU)

/* Properties of firewall at slave: WKUP_I2C0_CFG */
#define CSL_STD_FW_WKUP_I2C0_CFG_ID                                                                (34U)
#define CSL_STD_FW_WKUP_I2C0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_I2C0_CFG_MMR_BASE                                                          (0x00000045008800U)
#define CSL_STD_FW_WKUP_I2C0_CFG_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_WKUP_I2C0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_I2C0_CFG_CFG_START                                                         (0x0000002b200000U)
#define CSL_STD_FW_WKUP_I2C0_CFG_CFG_END                                                           (0x0000002b2000ffU)

/* Properties of firewall at slave: WKUP_UART0_MEM */
#define CSL_STD_FW_WKUP_UART0_MEM_ID                                                               (34U)
#define CSL_STD_FW_WKUP_UART0_MEM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_UART0_MEM_MMR_BASE                                                         (0x00000045008800U)
#define CSL_STD_FW_WKUP_UART0_MEM_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_WKUP_UART0_MEM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_WKUP_UART0_MEM_START                                                            (0x0000002b300000U)
#define CSL_STD_FW_WKUP_UART0_MEM_END                                                              (0x0000002b3001ffU)

/* Properties of firewall at slave: WKUP_CBASS0_ERR_REGS */
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_ID                                                         (34U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_MMR_BASE                                                   (0x00000045008800U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_NUM_REGIONS                                                (16U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_ERR_START                                                  (0x0000002b400000U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_ERR_END                                                    (0x0000002b4003ffU)

/* Properties of firewall at slave: WKUP_PBIST0_MEM */
#define CSL_STD_FW_WKUP_PBIST0_MEM_ID                                                              (34U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PBIST0_MEM_MMR_BASE                                                        (0x00000045008800U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_START                                                           (0x0000002b500000U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_END                                                             (0x0000002b5003ffU)

/* Properties of firewall at slave: WKUP_PBIST1_MEM */
#define CSL_STD_FW_WKUP_PBIST1_MEM_ID                                                              (34U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PBIST1_MEM_MMR_BASE                                                        (0x00000045008800U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_START                                                           (0x0000002b510000U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_END                                                             (0x0000002b5103ffU)

/* Properties of firewall at slave: WKUP_ECC_AGGR0_REGS */
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_ID                                                          (34U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_MMR_BASE                                                    (0x00000045008800U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_ECC_AGGR_START                                              (0x0000002b600000U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_ECC_AGGR_END                                                (0x0000002b6003ffU)

/* Properties of firewall at slave: WKUP_ECC_AGGR1_REGS */
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_ID                                                          (34U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_MMR_BASE                                                    (0x00000045008800U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_ECC_AGGR_START                                              (0x0000002b601000U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_ECC_AGGR_END                                                (0x0000002b6013ffU)

/* Properties of firewall at slave: WKUP_PSRAMECC_8K0_REGS */
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_ID                                                       (34U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_MMR_BASE                                                 (0x00000045008800U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_NUM_REGIONS                                              (16U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_REGS_START                                               (0x0000002b608000U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_REGS_END                                                 (0x0000002b6083ffU)

/* Properties of firewall at slave: WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS */
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_ID                                      (34U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_MMR_BASE                                (0x00000045008800U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_REGIONS                             (16U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_START               (0x0000003c018000U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_END                 (0x0000003c0180ffU)

/* Properties of firewall at slave: WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_ID                                   (34U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_MMR_BASE                             (0x00000045008800U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_NUM_REGIONS                          (16U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_START                 (0x0000003f00d000U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_END                   (0x0000003f00d3ffU)

/* Properties of firewall at slave: WKUP_PSRAMECC_8K0_RAM */
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_ID                                                        (34U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_MMR_BASE                                                  (0x00000045008800U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_RAM_START                                                 (0x00000041880000U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_RAM_END                                                   (0x00000041887fffU)

/* Properties of firewall at slave: WKUP_CTRL_MMR0_CFG0 */
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_ID                                                          (34U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_MMR_BASE                                                    (0x00000045008800U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_CFG0_START                                                  (0x00000043000000U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_CFG0_END                                                    (0x0000004301ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_ID                             (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_MMR_BASE                       (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_NUM_REGIONS                    (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_START (0x0000002b604000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_KSDW_ECC_AGGR_CFG_END (0x0000002b6043ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_ID      (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_TYPE    (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_START (0x0000002b605000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_KSDW_ECC_AGGR_CFG_END (0x0000002b6053ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_ID       (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_TYPE     (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_START (0x0000002b607000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_KSDW_ECC_AGGR_CFG_END (0x0000002b6073ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_ID                    (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_TYPE                  (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_MMR_BASE              (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_NUM_REGIONS           (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_START (0x0000002c000000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_END (0x0000002c0003ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_ID                         (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_TYPE                       (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_MMR_BASE                   (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_NUM_REGIONS                (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_NUM_PRIV_IDS_PER_REGION    (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_START (0x0000002c002000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_IVPAC_TOP_0_CFG_SLV_CTSET2_WRAP_CFG_CTSET2_CFG_END (0x0000002c003fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_ID                          (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_TYPE                        (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_MMR_BASE                    (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_NUM_REGIONS                 (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_NUM_PRIV_IDS_PER_REGION     (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_IVPAC_TOP_0_CFG_SLV_CP_INTD_CFG_INTD_CFG_START (0x0000002c004000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_CP_INTD_INTD_CFG_INTD_CFG_IVPAC_TOP_0_CFG_SLV_CP_INTD_CFG_INTD_CFG_END (0x0000002c004fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_ID                                   (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_MMR_BASE                             (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_NUM_REGIONS                          (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_START (0x0000002c010000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_REGS_IVPAC_TOP_0_CFG_SLV_HTS_S_VBUSP_END  (0x0000002c01ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_ID               (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_TYPE             (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_MMR_BASE         (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_NUM_REGIONS      (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_START (0x0000002c020000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MMR_VBUSP_END (0x0000002c0203ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_ID     (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_TYPE   (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_START (0x0000002c020400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_VPAC_LDC_LSE_CFG_VP_END (0x0000002c0205ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_START (0x0000002c020800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALY_LUTCFG_DUALY_LUT_END (0x0000002c020fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_START (0x0000002c021000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_PIXWRINTF_DUALC_LUTCFG_DUALC_LUT_END (0x0000002c0217ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_START (0x0000002c022000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_MESH_VBUSPI_MESH_MEM_END (0x0000002c023fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_ID   (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_START (0x0000002c028000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_Y_VBUSPI_Y_MEM_END (0x0000002c02ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_START (0x0000002c030000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_LDC0_S_VBUSP_MEMCFG_LOOP_CBCR_VBUSPI_CBCR_MEM_END (0x0000002c037fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_ID                    (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_TYPE                  (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_MMR_BASE              (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_NUM_REGIONS           (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_START (0x0000002c0c0000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_CFG_VP_END (0x0000002c0c07ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_ID                (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_TYPE              (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_MMR_BASE          (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_NUM_REGIONS       (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_START (0x0000002c0c0800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_MSC_CFG_VP_LSE_CFG_VP_END (0x0000002c0c09ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_ID       (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_TYPE     (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_START (0x0000002c100000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_END (0x0000002c1001ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_ID   (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_START (0x0000002c100400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VPAC_VISS_LSE_CFG_VP_END (0x0000002c1005ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_START (0x0000002c103800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_CFG_GLBCE_END (0x0000002c103fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_START (0x0000002c104000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_K3_GLBCE_TOP_STATMEM_CFG_GLBCE_STATMEM_END (0x0000002c107fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_START (0x0000002c108000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_END (0x0000002c10ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_START (0x0000002c110000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_END (0x0000002c1107ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_START (0x0000002c110800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC1_END (0x0000002c110fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_START (0x0000002c111000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC2_END (0x0000002c1117ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_START (0x0000002c111800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_CONTRASTC3_END (0x0000002c111fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_START (0x0000002c112000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_Y8R8_END (0x0000002c1127ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_START (0x0000002c112800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_C8G8_END (0x0000002c112fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8 */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_START (0x0000002c113000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_S8B8_END (0x0000002c1137ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_START (0x0000002c113800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_HIST_END (0x0000002c113fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_START (0x0000002c118000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_FCC_VBUSP_FLEXCC_LINE_END (0x0000002c1187ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_START (0x0000002c120000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_MMR_S_VBUSP_RAWFE_CFG_END (0x0000002c1203ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_START (0x0000002c120400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_CFG_RAWFE_H3A_CFG_END (0x0000002c1204ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_START (0x0000002c120800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT3_RAM_RAWFE_PWL_LUT3_RAM_END (0x0000002c120fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_START (0x0000002c121000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT2_RAM_RAWFE_PWL_LUT2_RAM_END (0x0000002c1217ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_START (0x0000002c121800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LUT1_RAM_RAWFE_PWL_LUT1_RAM_END (0x0000002c121fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_START (0x0000002c122000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_WDR_LUT_RAM_RAWFE_WDR_LUT_RAM_END (0x0000002c1227ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_START (0x0000002c122800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_LUT_RAM_RAWFE_H3A_LUT_RAM_END (0x0000002c122fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_START (0x0000002c123000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_RAM_RAWFE_DPC_LUT_RAM_END (0x0000002c1233ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_START (0x0000002c124000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_LRAM_RAWFE_DPC_LRAM_END (0x0000002c125fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_START (0x0000002c128000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_LSC_RAM_RAWFE_LSC_LUT_RAM_END (0x0000002c12ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_START (0x0000002c130000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_ARAM_RAWFE_H3A_ARAM_END (0x0000002c131fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_START (0x0000002c132000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_H3A_WRAP_LRAM_RAWFE_H3A_LRAM_END (0x0000002c133fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_START (0x0000002c136000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_RAWFE_CFG_DPC_STATRAM_RAWFE_DPC_STATRAM_END (0x0000002c137fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_VBUSP_NSF4VCORE_START (0x0000002c140000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_MMR_VBUSP_NSF4VCORE_REG_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MMR_VBUSP_NSF4VCORE_END (0x0000002c1407ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_START (0x0000002c140800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTDATA_VBUSP_RAWHIST_END (0x0000002c1409ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_START (0x0000002c141000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_RAWHIST_HISTLUT_VBUSP_RAWHIST_LUT_END (0x0000002c1417ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMRRAM_VBUSP_MMR_RAM_START (0x0000002c144000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMR_MMRRAM_VBUSP_MMR_RAM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_NSF4V_CFG_MEM_MMRRAM_VBUSP_MMR_RAM_END (0x0000002c147fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_START (0x0000002c150000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_EE_VBUSP_FLEXEE_END (0x0000002c157fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_START (0x0000002c158000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_FCP_CFA_VBUSP_FLEXCFA_DLUTS_END (0x0000002c15bfffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMRCFG_CAC_START (0x0000002c180000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMR_MMRCFG_CAC_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_MMRCFG_CAC_END (0x0000002c1803ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_START (0x0000002c182000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_CORE_LUT_CFG_LUT_MEM_END (0x0000002c183fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_START (0x0000002c184000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_CAC_S_VBUSP_LINEMEM_CFG_LINE_MEM_END (0x0000002c187fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMRCFG_PCID_START (0x0000002c188000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMR_MMRCFG_PCID_REGS_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_MMRCFG_PCID_END (0x0000002c1883ffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_START (0x0000002c188800U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_IR_REMAPLUT_LUT_CFG_IRREMAP_LUT_END (0x0000002c188fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_CFG_LINE_MEM_START (0x0000002c18c000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_LINEMEM_CFG_LINE_MEM_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_VISS_PCID_S_VBUSP_CFG_LINEMEM_CFG_LINE_MEM_END (0x0000002c18ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_ID              (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_TYPE            (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_MMR_BASE        (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_NUM_REGIONS     (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_START (0x0000002c200000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_END (0x0000002c203fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_ID          (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_TYPE        (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_MMR_BASE    (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_SET_START (0x0000002c204000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_SET_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_SET_END (0x0000002c207fffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_ID        (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_TYPE      (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_MMR_BASE  (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_QUEUE_START (0x0000002c208000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_QUEUE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_QUEUE_END (0x0000002c20ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_ID        (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_TYPE      (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_MMR_BASE  (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHNRT_START (0x0000002c240000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHNRT_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHNRT_END (0x0000002c25ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_ID         (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_TYPE       (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_MMR_BASE   (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHRT_START (0x0000002c260000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHRT_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHRT_END (0x0000002c27ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_ID (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHATOMIC_DEBUG_START (0x0000002c280000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHATOMIC_DEBUG_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHATOMIC_DEBUG_END (0x0000002c29ffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_ID       (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_TYPE     (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_MMR_BASE (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHCORE_START (0x0000002c2a0000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CHCORE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CHCORE_END (0x0000002c2bffffU)

/* Properties of firewall at slave: VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE */
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_ID        (37U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_TYPE      (CSL_FW_SECURITY)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_MMR_BASE  (0x00000045009400U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_NUM_REGIONS (4U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CAUSE_START (0x0000002c2e0000U)
#define CSL_STD_FW_VPAC0_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_DRU_CAUSE_IVPAC_TOP_0_CFG_SLV_DRU_UTC_VPAC0_DRU_MMR_CFG_DRU_DRU_CAUSE_END (0x0000002c2fffffU)

/* Properties of firewall at slave: CBASS_FW0_ERR_REGS */
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_ID                                                           (66U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_MMR_BASE                                                     (0x00000045010800U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_NUM_REGIONS                                                  (4U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_ERR_START                                                    (0x00000000220000U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_ERR_END                                                      (0x000000002203ffU)

/* Properties of firewall at slave: CBASS_IPCSS0_ERR_REGS */
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_ID                                                        (66U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_MMR_BASE                                                  (0x00000045010800U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_NUM_REGIONS                                               (4U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_ERR_START                                                 (0x00000000230000U)
#define CSL_STD_FW_CBASS_IPCSS0_ERR_REGS_ERR_END                                                   (0x000000002303ffU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_ECC_REGS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_ID                                                     (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_MMR_BASE                                               (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_NUM_REGIONS                                            (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_ECC_AGGR_START                                         (0x00000000712000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_ECC_REGS_ECC_AGGR_END                                           (0x000000007123ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_0_REGS0 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_REGS0_START                                    (0x00000029000000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_0_REGS0_REGS0_END                                      (0x000000290001ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_1_REGS1 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_REGS1_START                                    (0x00000029010000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_1_REGS1_REGS1_END                                      (0x000000290101ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_2_REGS2 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_REGS2_START                                    (0x00000029020000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_2_REGS2_REGS2_END                                      (0x000000290201ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_3_REGS3 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_REGS3_START                                    (0x00000029030000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_3_REGS3_REGS3_END                                      (0x000000290301ffU)

/* Properties of firewall at slave: SPINLOCK0_REGS */
#define CSL_STD_FW_SPINLOCK0_REGS_ID                                                               (66U)
#define CSL_STD_FW_SPINLOCK0_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_SPINLOCK0_REGS_MMR_BASE                                                         (0x00000045010800U)
#define CSL_STD_FW_SPINLOCK0_REGS_NUM_REGIONS                                                      (4U)
#define CSL_STD_FW_SPINLOCK0_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_SPINLOCK0_REGS_START                                                            (0x0000002a000000U)
#define CSL_STD_FW_SPINLOCK0_REGS_END                                                              (0x0000002a007fffU)

/* Properties of firewall at slave: ECC_AGGR1_REGS */
#define CSL_STD_FW_ECC_AGGR1_REGS_ID                                                               (66U)
#define CSL_STD_FW_ECC_AGGR1_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_ECC_AGGR1_REGS_MMR_BASE                                                         (0x00000045010800U)
#define CSL_STD_FW_ECC_AGGR1_REGS_NUM_REGIONS                                                      (4U)
#define CSL_STD_FW_ECC_AGGR1_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_ECC_AGGR1_REGS_ECC_AGGR_START                                                   (0x0000003f00e000U)
#define CSL_STD_FW_ECC_AGGR1_REGS_ECC_AGGR_END                                                     (0x0000003f00e3ffU)

/* Properties of firewall at slave: ECC_AGGR0_REGS */
#define CSL_STD_FW_ECC_AGGR0_REGS_ID                                                               (66U)
#define CSL_STD_FW_ECC_AGGR0_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_ECC_AGGR0_REGS_MMR_BASE                                                         (0x00000045010800U)
#define CSL_STD_FW_ECC_AGGR0_REGS_NUM_REGIONS                                                      (4U)
#define CSL_STD_FW_ECC_AGGR0_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_ECC_AGGR0_REGS_ECC_AGGR_START                                                   (0x0000003f00f000U)
#define CSL_STD_FW_ECC_AGGR0_REGS_ECC_AGGR_END                                                     (0x0000003f00f3ffU)

/* Properties of firewall at slave: CBASS_CENTRAL2_ERR_REGS */
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_ID                                                      (66U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_MMR_BASE                                                (0x00000045010800U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_NUM_REGIONS                                             (4U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_ERR_START                                               (0x0000003f012000U)
#define CSL_STD_FW_CBASS_CENTRAL2_ERR_REGS_ERR_END                                                 (0x0000003f0123ffU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_MMRS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_ID                                                         (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_MMR_BASE                                                   (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_NUM_REGIONS                                                (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_REGS_START                                                 (0x00000040900000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRS_REGS_END                                                   (0x00000040900fffU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_MMRA_REGS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_ID                                                    (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_MMR_BASE                                              (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_NUM_REGIONS                                           (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_MMRA_START                                            (0x00000040901000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_MMRA_REGS_MMRA_END                                              (0x000000409011ffU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_ID                               (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_MMR_BASE                         (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_NUM_REGIONS                      (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_EIP_76_START                     (0x00000040910000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_76D_8_BCDF_EIP76_REGISTERS_EIP_76_END                       (0x0000004091007fU)

/* Properties of firewall at slave: SA3_SS0_SA_UL_0_EIP_29T2_REGS */
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_ID                                                (66U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_MMR_BASE                                          (0x00000045010800U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_NUM_REGIONS                                       (4U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_EIP_29T2_START                                    (0x00000040920000U)
#define CSL_STD_FW_SA3_SS0_SA_UL_0_EIP_29T2_REGS_EIP_29T2_END                                      (0x0000004092ffffU)

/* Properties of firewall at slave: DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA */
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_ID                                 (160U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_MMR_BASE                           (0x00000045028000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_NUM_REGIONS                        (8U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_SEC_PROXY_SRC_TARGET_DATA_START    (0x0000004d000000U)
#define CSL_STD_FW_DMASS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_SEC_PROXY_SRC_TARGET_DATA_END      (0x0000004d07ffffU)

/* Properties of firewall at slave: SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA */
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_ID                                (161U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_TYPE                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_MMR_BASE                          (0x00000045028400U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_NUM_REGIONS                       (8U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_NUM_PRIV_IDS_PER_REGION           (3U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_SEC_PROXY_SRC_TARGET_DATA_START   (0x00000043600000U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_SEC_PROXY_SRC_TARGET_DATA_SEC_PROXY_SRC_TARGET_DATA_END     (0x0000004360ffffU)

/* Properties of firewall at slave: SMS0_ROM_0_IROM_SLV_ROM */
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_ID                                                      (512U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_MMR_BASE                                                (0x00000045080000U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_NUM_REGIONS                                             (2U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_NUM_PRIV_IDS_PER_REGION                                 (1U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_IROM_SLV_ROM_START                                      (0x00000000000000U)
#define CSL_STD_FW_SMS0_ROM_0_IROM_SLV_ROM_IROM_SLV_ROM_END                                        (0x0000000003ffffU)

/* Properties of firewall at slave: SMS0_TIFS_SRAM_0_TIFS_SRAM0 */
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_ID                                                  (513U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_MMR_BASE                                            (0x00000045080400U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_TIFS_SRAM0_START                                    (0x00000044040000U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_0_TIFS_SRAM0_TIFS_SRAM0_END                                      (0x0000004405ffffU)

/* Properties of firewall at slave: SMS0_TIFS_SRAM_1_TIFS_SRAM1_0 */
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_ID                                                (514U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_MMR_BASE                                          (0x00000045080800U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_NUM_REGIONS                                       (8U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_TIFS_SRAM1_0_START                                (0x00000044060000U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_0_TIFS_SRAM1_0_END                                  (0x00000044067fffU)

/* Properties of firewall at slave: SMS0_TIFS_SRAM_1_TIFS_SRAM1_1 */
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_ID                                                (514U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_MMR_BASE                                          (0x00000045080800U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_NUM_REGIONS                                       (8U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_TIFS_SRAM1_1_START                                (0x00000044068000U)
#define CSL_STD_FW_SMS0_TIFS_SRAM_1_TIFS_SRAM1_1_TIFS_SRAM1_1_END                                  (0x0000004406bfffU)

/* Properties of firewall at slave: SMS0_PWRCTRL_0_TIFS_PWR_MMR */
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_ID                                                  (528U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_MMR_BASE                                            (0x00000045084000U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_NUM_REGIONS                                         (1U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_PWR_START                                           (0x00000044130000U)
#define CSL_STD_FW_SMS0_PWRCTRL_0_TIFS_PWR_MMR_PWR_END                                             (0x000000441307ffU)

/* Properties of firewall at slave: SMS0_DMTIMER_0_TIFS_DMTIMER0 */
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_ID                                                 (536U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_MMR_BASE                                           (0x00000045086000U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_DMTIMER0_START                                     (0x00000044133000U)
#define CSL_STD_FW_SMS0_DMTIMER_0_TIFS_DMTIMER0_DMTIMER0_END                                       (0x000000441333ffU)

/* Properties of firewall at slave: SMS0_DMTIMER_1_TIFS_DMTIMER1 */
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_ID                                                 (537U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_MMR_BASE                                           (0x00000045086400U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_DMTIMER1_START                                     (0x00000044134000U)
#define CSL_STD_FW_SMS0_DMTIMER_1_TIFS_DMTIMER1_DMTIMER1_END                                       (0x000000441343ffU)

/* Properties of firewall at slave: SMS0_RTI_0_TIFS_RTI_MMR */
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_ID                                                      (544U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_MMR_BASE                                                (0x00000045088000U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_NUM_REGIONS                                             (1U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_RTI_START                                               (0x00000044135100U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_RTI_MMR_RTI_END                                                 (0x000000441351ffU)

/* Properties of firewall at slave: SMS0_WDTCTRL_0_TIFS_WDT_RTI */
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_ID                                                  (545U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_MMR_BASE                                            (0x00000045088400U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_NUM_REGIONS                                         (1U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_WDT_RTI_START                                       (0x00000044135000U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_WDT_RTI_WDT_RTI_END                                         (0x000000441350ffU)

/* Properties of firewall at slave: SMS0_RAT_0_TIFS_RAT_MMRS */
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_ID                                                     (552U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_MMR_BASE                                               (0x0000004508a000U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_NUM_REGIONS                                            (1U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_RAT_START                                              (0x00000044200000U)
#define CSL_STD_FW_SMS0_RAT_0_TIFS_RAT_MMRS_RAT_END                                                (0x00000044200fffU)

/* Properties of firewall at slave: SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS */
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_ID                                           (562U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_MMR_BASE                                     (0x0000004508c800U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_NUM_REGIONS                                  (2U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_ECC_AGGR_START                               (0x00000043700000U)
#define CSL_STD_FW_SMS0_TIFS_ECC_AGGR_0_TIFS_ECC_REGS_ECC_AGGR_END                                 (0x000000437003ffU)

/* Properties of firewall at slave: SMS0_SECCTRL_0_TIFS_SEC_MMR */
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_ID                                                  (576U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_MMR_BASE                                            (0x00000045090000U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_NUM_REGIONS                                         (1U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_SEC_START                                           (0x00000044230000U)
#define CSL_STD_FW_SMS0_SECCTRL_0_TIFS_SEC_MMR_SEC_END                                             (0x00000044230fffU)

/* Properties of firewall at slave: SMS0_DBG_AUTH_0_TIFS_DBGAUTH */
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_ID                                                 (578U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_MMR_BASE                                           (0x00000045090800U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_TIFS_DBGAUTH_START                                 (0x00000044232000U)
#define CSL_STD_FW_SMS0_DBG_AUTH_0_TIFS_DBGAUTH_TIFS_DBGAUTH_END                                   (0x000000442320ffU)

/* Properties of firewall at slave: SMS0_SEC_MGR_0_TIFS_SECMGR */
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_ID                                                   (582U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_MMR_BASE                                             (0x00000045091800U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_NUM_REGIONS                                          (2U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_SECMGR_START                                         (0x00000044234000U)
#define CSL_STD_FW_SMS0_SEC_MGR_0_TIFS_SECMGR_SECMGR_END                                           (0x00000044237fffU)

/* Properties of firewall at slave: SMS0_DMTIMER_2_TIFS_DMTIMER2 */
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_ID                                                 (592U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_MMR_BASE                                           (0x00000045094000U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_DMTIMER2_START                                     (0x00000044238000U)
#define CSL_STD_FW_SMS0_DMTIMER_2_TIFS_DMTIMER2_DMTIMER2_END                                       (0x000000442383ffU)

/* Properties of firewall at slave: SMS0_DMTIMER_3_TIFS_DMTIMER3 */
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_ID                                                 (593U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_MMR_BASE                                           (0x00000045094400U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_DMTIMER3_START                                     (0x00000044239000U)
#define CSL_STD_FW_SMS0_DMTIMER_3_TIFS_DMTIMER3_DMTIMER3_END                                       (0x000000442393ffU)

/* Properties of firewall at slave: SMS0_AESEIP38T_0_TIFS_AES38T */
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_ID                                                 (602U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_MMR_BASE                                           (0x00000045096800U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_NUM_REGIONS                                        (2U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_AES_START                                          (0x0000004423c000U)
#define CSL_STD_FW_SMS0_AESEIP38T_0_TIFS_AES38T_AES_END                                            (0x0000004423dfffU)

/* Properties of firewall at slave: SA3_SS0_DMSS_ECCAGGR_0_ECCAGGR_CFG_REGS */
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_ID                                     (638U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_TYPE                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_MMR_BASE                               (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_NUM_REGIONS                            (24U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                (3U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_START                      (0x00000043702000U)
#define CSL_STD_FW_SA3_SS0_DMSS_ECCAGGR_0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_END                        (0x000000437023ffU)

/* Properties of firewall at slave: SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY */
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_PSILCFG_CFG_PROXY_START                     (0x00000044801000U)
#define CSL_STD_FW_SA3_SS0_PSILCFG_0_PSILCFG_CFG_PROXY_PSILCFG_CFG_PROXY_END                       (0x000000448011ffU)

/* Properties of firewall at slave: SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS */
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_ID                                             (638U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_MMR_BASE                                       (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_NUM_REGIONS                                    (24U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_PSILSS_CFG_MMRS_START                          (0x00000044802000U)
#define CSL_STD_FW_SA3_SS0_PSILSS_0_PSILSS_CFG_MMRS_PSILSS_CFG_MMRS_END                            (0x00000044802fffU)

/* Properties of firewall at slave: SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS */
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_ID                                 (638U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_MMR_BASE                           (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_NUM_REGIONS                        (24U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_IPCSS_SEC_PROXY_CFG_MMRS_START     (0x00000044804000U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_MMRS_IPCSS_SEC_PROXY_CFG_MMRS_END       (0x000000448040ffU)

/* Properties of firewall at slave: SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG */
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_ID                                     (638U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_TYPE                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_MMR_BASE                               (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_NUM_REGIONS                            (24U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_NUM_PRIV_IDS_PER_REGION                (3U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_IPCSS_RINGACC_CFG_GCFG_START           (0x00000044805000U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_GCFG_IPCSS_RINGACC_CFG_GCFG_END             (0x000000448053ffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_ID                                            (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_MMR_BASE                                      (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_NUM_REGIONS                                   (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_INTAGGR_CFG_START                             (0x00000044808000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_CFG_INTAGGR_CFG_END                               (0x0000004480801fU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_ID                                           (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_MMR_BASE                                     (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_NUM_REGIONS                                  (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_INTAGGR_CFG_IMAP_START                       (0x00000044809000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_IMAP_INTAGGR_CFG_IMAP_END                         (0x000000448093ffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_INTAGGR_CFG_MCAST_START                     (0x0000004480a000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_MCAST_INTAGGR_CFG_MCAST_END                       (0x0000004480a3ffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_ID                                        (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_MMR_BASE                                  (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_NUM_REGIONS                               (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_INTAGGR_CFG_GCNTCFG_START                 (0x0000004480b000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTCFG_INTAGGR_CFG_GCNTCFG_END                   (0x0000004480b3ffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_ID                                           (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_MMR_BASE                                     (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_NUM_REGIONS                                  (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_INTAGGR_CFG_INTR_START                       (0x00000044810000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_INTR_INTAGGR_CFG_INTR_END                         (0x00000044817fffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_ID                                        (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_MMR_BASE                                  (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_NUM_REGIONS                               (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_INTAGGR_CFG_GCNTRTI_START                 (0x00000044820000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_GCNTRTI_INTAGGR_CFG_GCNTRTI_END                   (0x0000004483ffffU)

/* Properties of firewall at slave: SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP */
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_INTAGGR_CFG_UNMAP_START                     (0x00000044840000U)
#define CSL_STD_FW_SA3_SS0_INTAGGR_0_INTAGGR_CFG_UNMAP_INTAGGR_CFG_UNMAP_END                       (0x0000004484ffffU)

/* Properties of firewall at slave: SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG */
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_ID                                 (638U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_MMR_BASE                           (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_NUM_REGIONS                        (24U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_IPCSS_SEC_PROXY_CFG_SCFG_START     (0x00000044860000U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_SCFG_IPCSS_SEC_PROXY_CFG_SCFG_END       (0x0000004487ffffU)

/* Properties of firewall at slave: SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT */
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_ID                                   (638U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_MMR_BASE                             (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_NUM_REGIONS                          (24U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_IPCSS_SEC_PROXY_CFG_RT_START         (0x00000044880000U)
#define CSL_STD_FW_SA3_SS0_SEC_PROXY_0_IPCSS_SEC_PROXY_CFG_RT_IPCSS_SEC_PROXY_CFG_RT_END           (0x0000004489ffffU)

/* Properties of firewall at slave: SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG */
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_ID                                      (638U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_MMR_BASE                                (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_NUM_REGIONS                             (24U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_IPCSS_RINGACC_CFG_START                 (0x000000448c0000U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_CFG_IPCSS_RINGACC_CFG_END                   (0x000000448fffffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_ID                                             (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_MMR_BASE                                       (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_NUM_REGIONS                                    (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_PKTDMA_CFG_GCFG_START                          (0x00000044910000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_GCFG_PKTDMA_CFG_GCFG_END                            (0x000000449100ffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_ID                                            (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_MMR_BASE                                      (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_NUM_REGIONS                                   (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_PKTDMA_CFG_RFLOW_START                        (0x00000044911000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RFLOW_PKTDMA_CFG_RFLOW_END                          (0x000000449113ffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_ID                                            (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_MMR_BASE                                      (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_NUM_REGIONS                                   (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_PKTDMA_CFG_RCHAN_START                        (0x00000044912000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHAN_PKTDMA_CFG_RCHAN_END                          (0x000000449123ffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_ID                                            (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_MMR_BASE                                      (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_NUM_REGIONS                                   (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_PKTDMA_CFG_TCHAN_START                        (0x00000044913000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHAN_PKTDMA_CFG_TCHAN_END                          (0x000000449131ffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_PKTDMA_CFG_RCHANRT_START                    (0x00000044914000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RCHANRT_PKTDMA_CFG_RCHANRT_END                      (0x00000044917fffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_ID                                          (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_MMR_BASE                                    (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_NUM_REGIONS                                 (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_PKTDMA_CFG_TCHANRT_START                    (0x00000044918000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_TCHANRT_PKTDMA_CFG_TCHANRT_END                      (0x00000044919fffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_ID                                             (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_MMR_BASE                                       (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_NUM_REGIONS                                    (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_PKTDMA_CFG_RING_START                          (0x0000004491a000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RING_PKTDMA_CFG_RING_END                            (0x0000004491bfffU)

/* Properties of firewall at slave: SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT */
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_ID                                           (638U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_MMR_BASE                                     (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_NUM_REGIONS                                  (24U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_PKTDMA_CFG_RINGRT_START                      (0x00000044940000U)
#define CSL_STD_FW_SA3_SS0_PKTDMA_0_PKTDMA_CFG_RINGRT_PKTDMA_CFG_RINGRT_END                        (0x0000004497ffffU)

/* Properties of firewall at slave: SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT */
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_ID                                       (638U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_MMR_BASE                                 (0x0000004509f800U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_NUM_REGIONS                              (24U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_IPCSS_RINGACC_CFG_RT_START               (0x00000044c00000U)
#define CSL_STD_FW_SA3_SS0_RINGACC_0_IPCSS_RINGACC_CFG_RT_IPCSS_RINGACC_CFG_RT_END                 (0x00000044ffffffU)

/* Properties of firewall at slave: SMS0_FWMGR_0_TIFS_FW_VBUS_CFG */
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_ID                                                (639U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_MMR_BASE                                          (0x0000004509fc00U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_NUM_REGIONS                                       (8U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_FW_START                                          (0x00000045000000U)
#define CSL_STD_FW_SMS0_FWMGR_0_TIFS_FW_VBUS_CFG_FW_END                                            (0x00000045ffffffU)

/* Properties of firewall at slave: SMS0_HSM_SRAM_0_HSM_SRAM0_0 */
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_ID                                                  (641U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_MMR_BASE                                            (0x000000450a0400U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_HSM_SRAM0_0_START                                   (0x00000043c00000U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_0_HSM_SRAM0_0_END                                     (0x00000043c1ffffU)

/* Properties of firewall at slave: SMS0_HSM_SRAM_0_HSM_SRAM0_1 */
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_ID                                                  (641U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_MMR_BASE                                            (0x000000450a0400U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_HSM_SRAM0_1_START                                   (0x00000043c20000U)
#define CSL_STD_FW_SMS0_HSM_SRAM_0_HSM_SRAM0_1_HSM_SRAM0_1_END                                     (0x00000043c2ffffU)

/* Properties of firewall at slave: SMS0_HSM_SRAM_1_HSM_SRAM1 */
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_ID                                                    (642U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_MMR_BASE                                              (0x000000450a0800U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_NUM_REGIONS                                           (8U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_HSM_SRAM1_START                                       (0x00000043c30000U)
#define CSL_STD_FW_SMS0_HSM_SRAM_1_HSM_SRAM1_HSM_SRAM1_END                                         (0x00000043c3ffffU)

/* Properties of firewall at slave: SMS0_RTI_1_HSM_CTRL_MMR */
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_ID                                                      (672U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_MMR_BASE                                                (0x000000450a8000U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_NUM_REGIONS                                             (1U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_HSM_CTRL_MMR_START                                      (0x00000043936000U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_CTRL_MMR_HSM_CTRL_MMR_END                                        (0x00000043936fffU)

/* Properties of firewall at slave: SMS0_WDTCTRL_1_HSM_WDT_RTI */
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_ID                                                   (673U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_MMR_BASE                                             (0x000000450a8400U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_NUM_REGIONS                                          (1U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_HSM_WDT_RTI_START                                    (0x00000043935000U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_WDT_RTI_HSM_WDT_RTI_END                                      (0x000000439350ffU)

/* Properties of firewall at slave: SMS0_RAT_1_HSM_RAT_MMRS */
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_ID                                                      (680U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_MMR_BASE                                                (0x000000450aa000U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_NUM_REGIONS                                             (1U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_HSM_RAT_MMRS_START                                      (0x00000043a00000U)
#define CSL_STD_FW_SMS0_RAT_1_HSM_RAT_MMRS_HSM_RAT_MMRS_END                                        (0x00000043a00fffU)

/* Properties of firewall at slave: SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS */
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_ID                                             (690U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_MMR_BASE                                       (0x000000450ac800U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_NUM_REGIONS                                    (2U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_HSM_ECC_START                                  (0x00000043701000U)
#define CSL_STD_FW_SMS0_HSM_ECC_AGGR_0_HSM_ECC_REGS_HSM_ECC_END                                    (0x000000437013ffU)

/* Infrastructure Slave Firewall Definitions */

/* Properties of firewall at slave: PDMA0_REGS */
#define CSL_STD_FW_PDMA0_REGS_ID                                                                   (8U)
#define CSL_STD_FW_PDMA0_REGS_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PDMA0_REGS_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_PDMA0_REGS_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PDMA0_REGS_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PDMA0_REGS_START                                                                (0x00000000c00000U)
#define CSL_STD_FW_PDMA0_REGS_END                                                                  (0x00000000c003ffU)

/* Properties of firewall at slave: PDMA1_REGS */
#define CSL_STD_FW_PDMA1_REGS_ID                                                                   (8U)
#define CSL_STD_FW_PDMA1_REGS_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PDMA1_REGS_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_PDMA1_REGS_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PDMA1_REGS_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PDMA1_REGS_START                                                                (0x00000000c01000U)
#define CSL_STD_FW_PDMA1_REGS_END                                                                  (0x00000000c013ffU)

/* Properties of firewall at slave: UART0_MEM */
#define CSL_STD_FW_UART0_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART0_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART0_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART0_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART0_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART0_MEM_START                                                                 (0x00000002800000U)
#define CSL_STD_FW_UART0_MEM_END                                                                   (0x000000028001ffU)

/* Properties of firewall at slave: UART1_MEM */
#define CSL_STD_FW_UART1_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART1_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART1_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART1_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART1_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART1_MEM_START                                                                 (0x00000002810000U)
#define CSL_STD_FW_UART1_MEM_END                                                                   (0x000000028101ffU)

/* Properties of firewall at slave: UART2_MEM */
#define CSL_STD_FW_UART2_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART2_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART2_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART2_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART2_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART2_MEM_START                                                                 (0x00000002820000U)
#define CSL_STD_FW_UART2_MEM_END                                                                   (0x000000028201ffU)

/* Properties of firewall at slave: UART3_MEM */
#define CSL_STD_FW_UART3_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART3_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART3_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART3_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART3_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART3_MEM_START                                                                 (0x00000002830000U)
#define CSL_STD_FW_UART3_MEM_END                                                                   (0x000000028301ffU)

/* Properties of firewall at slave: UART4_MEM */
#define CSL_STD_FW_UART4_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART4_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART4_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART4_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART4_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART4_MEM_START                                                                 (0x00000002840000U)
#define CSL_STD_FW_UART4_MEM_END                                                                   (0x000000028401ffU)

/* Properties of firewall at slave: UART5_MEM */
#define CSL_STD_FW_UART5_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART5_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART5_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART5_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART5_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART5_MEM_START                                                                 (0x00000002850000U)
#define CSL_STD_FW_UART5_MEM_END                                                                   (0x000000028501ffU)

/* Properties of firewall at slave: UART6_MEM */
#define CSL_STD_FW_UART6_MEM_ID                                                                    (8U)
#define CSL_STD_FW_UART6_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART6_MEM_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_UART6_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_UART6_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART6_MEM_START                                                                 (0x00000002860000U)
#define CSL_STD_FW_UART6_MEM_END                                                                   (0x000000028601ffU)

/* Properties of firewall at slave: I2C0_CFG */
#define CSL_STD_FW_I2C0_CFG_ID                                                                     (8U)
#define CSL_STD_FW_I2C0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C0_CFG_MMR_BASE                                                               (0x00000045002000U)
#define CSL_STD_FW_I2C0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_I2C0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C0_CFG_CFG_START                                                              (0x00000020000000U)
#define CSL_STD_FW_I2C0_CFG_CFG_END                                                                (0x000000200000ffU)

/* Properties of firewall at slave: I2C1_CFG */
#define CSL_STD_FW_I2C1_CFG_ID                                                                     (8U)
#define CSL_STD_FW_I2C1_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C1_CFG_MMR_BASE                                                               (0x00000045002000U)
#define CSL_STD_FW_I2C1_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_I2C1_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C1_CFG_CFG_START                                                              (0x00000020010000U)
#define CSL_STD_FW_I2C1_CFG_CFG_END                                                                (0x000000200100ffU)

/* Properties of firewall at slave: I2C2_CFG */
#define CSL_STD_FW_I2C2_CFG_ID                                                                     (8U)
#define CSL_STD_FW_I2C2_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C2_CFG_MMR_BASE                                                               (0x00000045002000U)
#define CSL_STD_FW_I2C2_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_I2C2_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C2_CFG_CFG_START                                                              (0x00000020020000U)
#define CSL_STD_FW_I2C2_CFG_CFG_END                                                                (0x000000200200ffU)

/* Properties of firewall at slave: I2C3_CFG */
#define CSL_STD_FW_I2C3_CFG_ID                                                                     (8U)
#define CSL_STD_FW_I2C3_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C3_CFG_MMR_BASE                                                               (0x00000045002000U)
#define CSL_STD_FW_I2C3_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_I2C3_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C3_CFG_CFG_START                                                              (0x00000020030000U)
#define CSL_STD_FW_I2C3_CFG_CFG_END                                                                (0x000000200300ffU)

/* Properties of firewall at slave: MCSPI0_CFG */
#define CSL_STD_FW_MCSPI0_CFG_ID                                                                   (8U)
#define CSL_STD_FW_MCSPI0_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI0_CFG_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_MCSPI0_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_MCSPI0_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI0_CFG_CFG_START                                                            (0x00000020100000U)
#define CSL_STD_FW_MCSPI0_CFG_CFG_END                                                              (0x000000201003ffU)

/* Properties of firewall at slave: MCSPI1_CFG */
#define CSL_STD_FW_MCSPI1_CFG_ID                                                                   (8U)
#define CSL_STD_FW_MCSPI1_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI1_CFG_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_MCSPI1_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_MCSPI1_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI1_CFG_CFG_START                                                            (0x00000020110000U)
#define CSL_STD_FW_MCSPI1_CFG_CFG_END                                                              (0x000000201103ffU)

/* Properties of firewall at slave: MCSPI2_CFG */
#define CSL_STD_FW_MCSPI2_CFG_ID                                                                   (8U)
#define CSL_STD_FW_MCSPI2_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI2_CFG_MMR_BASE                                                             (0x00000045002000U)
#define CSL_STD_FW_MCSPI2_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_MCSPI2_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI2_CFG_CFG_START                                                            (0x00000020120000U)
#define CSL_STD_FW_MCSPI2_CFG_CFG_END                                                              (0x000000201203ffU)

/* Properties of firewall at slave: CBASS_MISC_PERI0_ERR_REGS */
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_ID                                                    (8U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_MMR_BASE                                              (0x00000045002000U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_ERR_START                                             (0x000000201f0000U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_ERR_END                                               (0x000000201f03ffU)

/* Properties of firewall at slave: MCAN0_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_ID                                                 (8U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                           (0x00000045002000U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_START                                           (0x00000020700000U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_END                                             (0x000000207000ffU)

/* Properties of firewall at slave: MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                       (8U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                                 (0x00000045002000U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                              (16U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                                (0x00000020701000U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                                  (0x000000207011ffU)

/* Properties of firewall at slave: MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                             (8U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                       (0x00000045002000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                    (16U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                               (0x00000020708000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                                 (0x0000002070ffffU)

/* Properties of firewall at slave: ECAP0_CTL_STS */
#define CSL_STD_FW_ECAP0_CTL_STS_ID                                                                (8U)
#define CSL_STD_FW_ECAP0_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP0_CTL_STS_MMR_BASE                                                          (0x00000045002000U)
#define CSL_STD_FW_ECAP0_CTL_STS_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_ECAP0_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP0_CTL_STS_CTL_STS_START                                                     (0x00000023100000U)
#define CSL_STD_FW_ECAP0_CTL_STS_CTL_STS_END                                                       (0x000000231000ffU)

/* Properties of firewall at slave: ECAP1_CTL_STS */
#define CSL_STD_FW_ECAP1_CTL_STS_ID                                                                (8U)
#define CSL_STD_FW_ECAP1_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP1_CTL_STS_MMR_BASE                                                          (0x00000045002000U)
#define CSL_STD_FW_ECAP1_CTL_STS_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_ECAP1_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP1_CTL_STS_CTL_STS_START                                                     (0x00000023110000U)
#define CSL_STD_FW_ECAP1_CTL_STS_CTL_STS_END                                                       (0x000000231100ffU)

/* Properties of firewall at slave: ECAP2_CTL_STS */
#define CSL_STD_FW_ECAP2_CTL_STS_ID                                                                (8U)
#define CSL_STD_FW_ECAP2_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP2_CTL_STS_MMR_BASE                                                          (0x00000045002000U)
#define CSL_STD_FW_ECAP2_CTL_STS_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_ECAP2_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP2_CTL_STS_CTL_STS_START                                                     (0x00000023120000U)
#define CSL_STD_FW_ECAP2_CTL_STS_CTL_STS_END                                                       (0x000000231200ffU)

/* Properties of firewall at slave: EQEP0_REG */
#define CSL_STD_FW_EQEP0_REG_ID                                                                    (8U)
#define CSL_STD_FW_EQEP0_REG_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_EQEP0_REG_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_EQEP0_REG_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_EQEP0_REG_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_EQEP0_REG_REG_START                                                             (0x00000023200000U)
#define CSL_STD_FW_EQEP0_REG_REG_END                                                               (0x000000232000ffU)

/* Properties of firewall at slave: EQEP1_REG */
#define CSL_STD_FW_EQEP1_REG_ID                                                                    (8U)
#define CSL_STD_FW_EQEP1_REG_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_EQEP1_REG_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_EQEP1_REG_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_EQEP1_REG_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_EQEP1_REG_REG_START                                                             (0x00000023210000U)
#define CSL_STD_FW_EQEP1_REG_REG_END                                                               (0x000000232100ffU)

/* Properties of firewall at slave: EQEP2_REG */
#define CSL_STD_FW_EQEP2_REG_ID                                                                    (8U)
#define CSL_STD_FW_EQEP2_REG_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_EQEP2_REG_MMR_BASE                                                              (0x00000045002000U)
#define CSL_STD_FW_EQEP2_REG_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_EQEP2_REG_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_EQEP2_REG_REG_START                                                             (0x00000023220000U)
#define CSL_STD_FW_EQEP2_REG_REG_END                                                               (0x000000232200ffU)

/* Properties of firewall at slave: MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                          (8U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                    (0x00000045002000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                                 (16U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                              (0x00000024018000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                                (0x000000240183ffU)

/* Properties of firewall at slave: MCASP0_CFG */
#define CSL_STD_FW_MCASP0_CFG_ID                                                                   (14U)
#define CSL_STD_FW_MCASP0_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP0_CFG_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP0_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP0_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP0_CFG_CFG_START                                                            (0x00000002b00000U)
#define CSL_STD_FW_MCASP0_CFG_CFG_END                                                              (0x00000002b01fffU)

/* Properties of firewall at slave: MCASP0_DMA */
#define CSL_STD_FW_MCASP0_DMA_ID                                                                   (14U)
#define CSL_STD_FW_MCASP0_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP0_DMA_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP0_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP0_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP0_DMA_DMA_START                                                            (0x00000002b08000U)
#define CSL_STD_FW_MCASP0_DMA_DMA_END                                                              (0x00000002b083ffU)

/* Properties of firewall at slave: MCASP1_CFG */
#define CSL_STD_FW_MCASP1_CFG_ID                                                                   (14U)
#define CSL_STD_FW_MCASP1_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP1_CFG_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP1_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP1_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP1_CFG_CFG_START                                                            (0x00000002b10000U)
#define CSL_STD_FW_MCASP1_CFG_CFG_END                                                              (0x00000002b11fffU)

/* Properties of firewall at slave: MCASP1_DMA */
#define CSL_STD_FW_MCASP1_DMA_ID                                                                   (14U)
#define CSL_STD_FW_MCASP1_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP1_DMA_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP1_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP1_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP1_DMA_DMA_START                                                            (0x00000002b18000U)
#define CSL_STD_FW_MCASP1_DMA_DMA_END                                                              (0x00000002b183ffU)

/* Properties of firewall at slave: MCASP2_CFG */
#define CSL_STD_FW_MCASP2_CFG_ID                                                                   (14U)
#define CSL_STD_FW_MCASP2_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP2_CFG_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP2_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP2_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP2_CFG_CFG_START                                                            (0x00000002b20000U)
#define CSL_STD_FW_MCASP2_CFG_CFG_END                                                              (0x00000002b21fffU)

/* Properties of firewall at slave: MCASP2_DMA */
#define CSL_STD_FW_MCASP2_DMA_ID                                                                   (14U)
#define CSL_STD_FW_MCASP2_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP2_DMA_MMR_BASE                                                             (0x00000045003800U)
#define CSL_STD_FW_MCASP2_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP2_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP2_DMA_DMA_START                                                            (0x00000002b28000U)
#define CSL_STD_FW_MCASP2_DMA_DMA_END                                                              (0x00000002b283ffU)

/* Properties of firewall at slave: EPWM0_EPWM_REGS */
#define CSL_STD_FW_EPWM0_EPWM_REGS_ID                                                              (14U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_EPWM0_EPWM_REGS_MMR_BASE                                                        (0x00000045003800U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_NUM_REGIONS                                                     (8U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_EPWM_START                                                      (0x00000023000000U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_EPWM_END                                                        (0x000000230000ffU)

/* Properties of firewall at slave: EPWM1_EPWM_REGS */
#define CSL_STD_FW_EPWM1_EPWM_REGS_ID                                                              (14U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_EPWM1_EPWM_REGS_MMR_BASE                                                        (0x00000045003800U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_NUM_REGIONS                                                     (8U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_EPWM_START                                                      (0x00000023010000U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_EPWM_END                                                        (0x000000230100ffU)

/* Properties of firewall at slave: EPWM2_EPWM_REGS */
#define CSL_STD_FW_EPWM2_EPWM_REGS_ID                                                              (14U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_EPWM2_EPWM_REGS_MMR_BASE                                                        (0x00000045003800U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_NUM_REGIONS                                                     (8U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_EPWM_START                                                      (0x00000023020000U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_EPWM_END                                                        (0x000000230200ffU)

/* Properties of firewall at slave: PSRAMECC0_RAM */
#define CSL_STD_FW_PSRAMECC0_RAM_ID                                                                (33U)
#define CSL_STD_FW_PSRAMECC0_RAM_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_PSRAMECC0_RAM_MMR_BASE                                                          (0x00000045008400U)
#define CSL_STD_FW_PSRAMECC0_RAM_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_PSRAMECC0_RAM_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_PSRAMECC0_RAM_RAM_START                                                         (0x00000000000000U)
#define CSL_STD_FW_PSRAMECC0_RAM_RAM_END                                                           (0x000000000003ffU)

/* Properties of firewall at slave: PADCFG_CTRL0_CFG0 */
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_ID                                                            (33U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_TYPE                                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_MMR_BASE                                                      (0x00000045008400U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_NUM_REGIONS                                                   (16U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_NUM_PRIV_IDS_PER_REGION                                       (3U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_CFG0_START                                                    (0x000000000f0000U)
#define CSL_STD_FW_PADCFG_CTRL0_CFG0_CFG0_END                                                      (0x000000000f7fffU)

/* Properties of firewall at slave: CTRL_MMR0_CFG0 */
#define CSL_STD_FW_CTRL_MMR0_CFG0_ID                                                               (33U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_CTRL_MMR0_CFG0_MMR_BASE                                                         (0x00000045008400U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_CFG0_START                                                       (0x00000000100000U)
#define CSL_STD_FW_CTRL_MMR0_CFG0_CFG0_END                                                         (0x0000000011ffffU)

/* Properties of firewall at slave: CBASS_INFRA1_ERR_REGS */
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_ID                                                        (33U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_MMR_BASE                                                  (0x00000045008400U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_ERR_START                                                 (0x00000000210000U)
#define CSL_STD_FW_CBASS_INFRA1_ERR_REGS_ERR_END                                                   (0x000000002103ffU)

/* Properties of firewall at slave: EFUSE0_MEM */
#define CSL_STD_FW_EFUSE0_MEM_ID                                                                   (33U)
#define CSL_STD_FW_EFUSE0_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_EFUSE0_MEM_MMR_BASE                                                             (0x00000045008400U)
#define CSL_STD_FW_EFUSE0_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_EFUSE0_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_EFUSE0_MEM_START                                                                (0x00000000300000U)
#define CSL_STD_FW_EFUSE0_MEM_END                                                                  (0x000000003000ffU)

/* Properties of firewall at slave: PSC0_VBUS */
#define CSL_STD_FW_PSC0_VBUS_ID                                                                    (33U)
#define CSL_STD_FW_PSC0_VBUS_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_PSC0_VBUS_MMR_BASE                                                              (0x00000045008400U)
#define CSL_STD_FW_PSC0_VBUS_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_PSC0_VBUS_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_PSC0_VBUS_START                                                                 (0x00000000400000U)
#define CSL_STD_FW_PSC0_VBUS_END                                                                   (0x00000000400fffU)

/* Properties of firewall at slave: PLLCTRL0_MEM */
#define CSL_STD_FW_PLLCTRL0_MEM_ID                                                                 (33U)
#define CSL_STD_FW_PLLCTRL0_MEM_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_PLLCTRL0_MEM_MMR_BASE                                                           (0x00000045008400U)
#define CSL_STD_FW_PLLCTRL0_MEM_NUM_REGIONS                                                        (16U)
#define CSL_STD_FW_PLLCTRL0_MEM_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_PLLCTRL0_MEM_START                                                              (0x00000000410000U)
#define CSL_STD_FW_PLLCTRL0_MEM_END                                                                (0x000000004101ffU)

/* Properties of firewall at slave: ESM0_CFG */
#define CSL_STD_FW_ESM0_CFG_ID                                                                     (33U)
#define CSL_STD_FW_ESM0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_ESM0_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_ESM0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_ESM0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_ESM0_CFG_CFG_START                                                              (0x00000000420000U)
#define CSL_STD_FW_ESM0_CFG_CFG_END                                                                (0x00000000420fffU)

/* Properties of firewall at slave: DFTSS0_MEM */
#define CSL_STD_FW_DFTSS0_MEM_ID                                                                   (33U)
#define CSL_STD_FW_DFTSS0_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DFTSS0_MEM_MMR_BASE                                                             (0x00000045008400U)
#define CSL_STD_FW_DFTSS0_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_DFTSS0_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_DFTSS0_MEM_START                                                                (0x00000000500000U)
#define CSL_STD_FW_DFTSS0_MEM_END                                                                  (0x000000005003ffU)

/* Properties of firewall at slave: DDPA0_DDPA */
#define CSL_STD_FW_DDPA0_DDPA_ID                                                                   (33U)
#define CSL_STD_FW_DDPA0_DDPA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DDPA0_DDPA_MMR_BASE                                                             (0x00000045008400U)
#define CSL_STD_FW_DDPA0_DDPA_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_DDPA0_DDPA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_DDPA0_DDPA_START                                                                (0x00000000580000U)
#define CSL_STD_FW_DDPA0_DDPA_END                                                                  (0x000000005803ffU)

/* Properties of firewall at slave: GPIO0_MEM */
#define CSL_STD_FW_GPIO0_MEM_ID                                                                    (33U)
#define CSL_STD_FW_GPIO0_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_GPIO0_MEM_MMR_BASE                                                              (0x00000045008400U)
#define CSL_STD_FW_GPIO0_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_GPIO0_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_GPIO0_MEM_START                                                                 (0x00000000600000U)
#define CSL_STD_FW_GPIO0_MEM_END                                                                   (0x000000006000ffU)

/* Properties of firewall at slave: GPIO1_MEM */
#define CSL_STD_FW_GPIO1_MEM_ID                                                                    (33U)
#define CSL_STD_FW_GPIO1_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_GPIO1_MEM_MMR_BASE                                                              (0x00000045008400U)
#define CSL_STD_FW_GPIO1_MEM_NUM_REGIONS                                                           (16U)
#define CSL_STD_FW_GPIO1_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_GPIO1_MEM_START                                                                 (0x00000000601000U)
#define CSL_STD_FW_GPIO1_MEM_END                                                                   (0x000000006010ffU)

/* Properties of firewall at slave: PLL0_CFG */
#define CSL_STD_FW_PLL0_CFG_ID                                                                     (33U)
#define CSL_STD_FW_PLL0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_PLL0_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_PLL0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_PLL0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_PLL0_CFG_CFG_START                                                              (0x00000000680000U)
#define CSL_STD_FW_PLL0_CFG_CFG_END                                                                (0x0000000069ffffU)

/* Properties of firewall at slave: PSRAMECC0_REGS */
#define CSL_STD_FW_PSRAMECC0_REGS_ID                                                               (33U)
#define CSL_STD_FW_PSRAMECC0_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_PSRAMECC0_REGS_MMR_BASE                                                         (0x00000045008400U)
#define CSL_STD_FW_PSRAMECC0_REGS_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_PSRAMECC0_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_PSRAMECC0_REGS_ECC_AGGR_START                                                   (0x00000000700000U)
#define CSL_STD_FW_PSRAMECC0_REGS_ECC_AGGR_END                                                     (0x000000007003ffU)

/* Properties of firewall at slave: PSC0_ECC_AGGR_0_REGS */
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_ID                                                         (33U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_MMR_BASE                                                   (0x00000045008400U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_NUM_REGIONS                                                (16U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_REGS_START                                                 (0x00000000700400U)
#define CSL_STD_FW_PSC0_ECC_AGGR_0_REGS_REGS_END                                                   (0x000000007007ffU)

/* Properties of firewall at slave: PSRAMECC1_REGS */
#define CSL_STD_FW_PSRAMECC1_REGS_ID                                                               (33U)
#define CSL_STD_FW_PSRAMECC1_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_PSRAMECC1_REGS_MMR_BASE                                                         (0x00000045008400U)
#define CSL_STD_FW_PSRAMECC1_REGS_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_PSRAMECC1_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_PSRAMECC1_REGS_ECC_AGGR_START                                                   (0x00000000701000U)
#define CSL_STD_FW_PSRAMECC1_REGS_ECC_AGGR_END                                                     (0x000000007013ffU)

/* Properties of firewall at slave: DCC0_CFG */
#define CSL_STD_FW_DCC0_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC0_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC0_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC0_CFG_START                                                                  (0x00000000800000U)
#define CSL_STD_FW_DCC0_CFG_END                                                                    (0x0000000080003fU)

/* Properties of firewall at slave: DCC1_CFG */
#define CSL_STD_FW_DCC1_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC1_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC1_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC1_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC1_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC1_CFG_START                                                                  (0x00000000804000U)
#define CSL_STD_FW_DCC1_CFG_END                                                                    (0x0000000080403fU)

/* Properties of firewall at slave: DCC2_CFG */
#define CSL_STD_FW_DCC2_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC2_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC2_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC2_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC2_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC2_CFG_START                                                                  (0x00000000808000U)
#define CSL_STD_FW_DCC2_CFG_END                                                                    (0x0000000080803fU)

/* Properties of firewall at slave: DCC3_CFG */
#define CSL_STD_FW_DCC3_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC3_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC3_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC3_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC3_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC3_CFG_START                                                                  (0x0000000080c000U)
#define CSL_STD_FW_DCC3_CFG_END                                                                    (0x0000000080c03fU)

/* Properties of firewall at slave: DCC4_CFG */
#define CSL_STD_FW_DCC4_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC4_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC4_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC4_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC4_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC4_CFG_START                                                                  (0x00000000810000U)
#define CSL_STD_FW_DCC4_CFG_END                                                                    (0x0000000081003fU)

/* Properties of firewall at slave: DCC5_CFG */
#define CSL_STD_FW_DCC5_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC5_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC5_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC5_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC5_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC5_CFG_START                                                                  (0x00000000814000U)
#define CSL_STD_FW_DCC5_CFG_END                                                                    (0x0000000081403fU)

/* Properties of firewall at slave: DCC6_CFG */
#define CSL_STD_FW_DCC6_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC6_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC6_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC6_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC6_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC6_CFG_START                                                                  (0x00000000818000U)
#define CSL_STD_FW_DCC6_CFG_END                                                                    (0x0000000081803fU)

/* Properties of firewall at slave: PSRAMECC1_RAM */
#define CSL_STD_FW_PSRAMECC1_RAM_ID                                                                (33U)
#define CSL_STD_FW_PSRAMECC1_RAM_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_PSRAMECC1_RAM_MMR_BASE                                                          (0x00000045008400U)
#define CSL_STD_FW_PSRAMECC1_RAM_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_PSRAMECC1_RAM_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_PSRAMECC1_RAM_RAM_START                                                         (0x00000000900000U)
#define CSL_STD_FW_PSRAMECC1_RAM_RAM_END                                                           (0x000000009003ffU)

/* Properties of firewall at slave: MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_ID                                      (33U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_MMR_BASE                                (0x00000045008400U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                             (16U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START                   (0x00000000a00000U)
#define CSL_STD_FW_MAIN_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                     (0x00000000a007ffU)

/* Properties of firewall at slave: CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_ID                                         (33U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_MMR_BASE                                   (0x00000045008400U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                                (16U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START                      (0x00000000a30000U)
#define CSL_STD_FW_CMP_EVENT_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                        (0x00000000a307ffU)

/* Properties of firewall at slave: TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_ID                                       (33U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_MMR_BASE                                 (0x00000045008400U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                              (16U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START                    (0x00000000a40000U)
#define CSL_STD_FW_TIMESYNC_EVENT_ROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                      (0x00000000a403ffU)

/* Properties of firewall at slave: WKUP_PSC0_VBUS */
#define CSL_STD_FW_WKUP_PSC0_VBUS_ID                                                               (35U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSC0_VBUS_MMR_BASE                                                         (0x00000045008c00U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_START                                                            (0x00000004000000U)
#define CSL_STD_FW_WKUP_PSC0_VBUS_END                                                              (0x00000004000fffU)

/* Properties of firewall at slave: MCU_PLLCTRL0_MEM */
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_ID                                                             (35U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_TYPE                                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_MMR_BASE                                                       (0x00000045008c00U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_NUM_REGIONS                                                    (16U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_NUM_PRIV_IDS_PER_REGION                                        (3U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_START                                                          (0x00000004020000U)
#define CSL_STD_FW_MCU_PLLCTRL0_MEM_END                                                            (0x000000040201ffU)

/* Properties of firewall at slave: WKUP_ECC_AGGR2_REGS */
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_ID                                                          (35U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_MMR_BASE                                                    (0x00000045008c00U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_ECC_AGGR_START                                              (0x00000004030000U)
#define CSL_STD_FW_WKUP_ECC_AGGR2_REGS_ECC_AGGR_END                                                (0x000000040303ffU)

/* Properties of firewall at slave: WKUP_PLL0_CFG */
#define CSL_STD_FW_WKUP_PLL0_CFG_ID                                                                (35U)
#define CSL_STD_FW_WKUP_PLL0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PLL0_CFG_MMR_BASE                                                          (0x00000045008c00U)
#define CSL_STD_FW_WKUP_PLL0_CFG_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_WKUP_PLL0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_PLL0_CFG_CFG_START                                                         (0x00000004040000U)
#define CSL_STD_FW_WKUP_PLL0_CFG_CFG_END                                                           (0x00000004040fffU)

/* Properties of firewall at slave: WKUP_PADCFG_CTRL0_CFG0 */
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_ID                                                       (35U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_MMR_BASE                                                 (0x00000045008c00U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_NUM_REGIONS                                              (16U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_CFG0_START                                               (0x00000004080000U)
#define CSL_STD_FW_WKUP_PADCFG_CTRL0_CFG0_CFG0_END                                                 (0x00000004087fffU)

/* Properties of firewall at slave: WKUP_ESM0_CFG */
#define CSL_STD_FW_WKUP_ESM0_CFG_ID                                                                (35U)
#define CSL_STD_FW_WKUP_ESM0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ESM0_CFG_MMR_BASE                                                          (0x00000045008c00U)
#define CSL_STD_FW_WKUP_ESM0_CFG_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_WKUP_ESM0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_ESM0_CFG_CFG_START                                                         (0x00000004100000U)
#define CSL_STD_FW_WKUP_ESM0_CFG_CFG_END                                                           (0x00000004100fffU)

/* Properties of firewall at slave: MCU_GPIO0_MEM */
#define CSL_STD_FW_MCU_GPIO0_MEM_ID                                                                (35U)
#define CSL_STD_FW_MCU_GPIO0_MEM_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_GPIO0_MEM_MMR_BASE                                                          (0x00000045008c00U)
#define CSL_STD_FW_MCU_GPIO0_MEM_NUM_REGIONS                                                       (16U)
#define CSL_STD_FW_MCU_GPIO0_MEM_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_MCU_GPIO0_MEM_START                                                             (0x00000004201000U)
#define CSL_STD_FW_MCU_GPIO0_MEM_END                                                               (0x000000042010ffU)

/* Properties of firewall at slave: WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_ID                                  (35U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_TYPE                                (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_MMR_BASE                            (0x00000045008c00U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                         (16U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION             (3U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START               (0x00000004210000U)
#define CSL_STD_FW_WKUP_MCU_GPIOMUX_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                 (0x000000042101ffU)

/* Properties of firewall at slave: MCU_CTRL_MMR0_CFG0 */
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_ID                                                           (35U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_MMR_BASE                                                     (0x00000045008c00U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_NUM_REGIONS                                                  (16U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_CFG0_START                                                   (0x00000004500000U)
#define CSL_STD_FW_MCU_CTRL_MMR0_CFG0_CFG0_END                                                     (0x0000000451ffffU)

/* Properties of firewall at slave: WKUP_CBASS_SAFE1_ERR_REGS */
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_ID                                                    (35U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_MMR_BASE                                              (0x00000045008c00U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_ERR_START                                             (0x00000004600000U)
#define CSL_STD_FW_WKUP_CBASS_SAFE1_ERR_REGS_ERR_END                                               (0x000000046003ffU)

/* Properties of firewall at slave: MCU_TIMEOUT0_CFG */
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_ID                                                             (36U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_TYPE                                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_MMR_BASE                                                       (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_NUM_REGIONS                                                    (8U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_NUM_PRIV_IDS_PER_REGION                                        (3U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_CFG_START                                                      (0x00000004301000U)
#define CSL_STD_FW_MCU_TIMEOUT0_CFG_CFG_END                                                        (0x000000043013ffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_ID                                         (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_MMR_BASE                                   (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_NUM_REGIONS                                (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_START                  (0x00000004400000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_END                    (0x000000044000ffU)

/* Properties of firewall at slave: MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                      (36U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                             (8U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                          (0x00000004701000U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                            (0x000000047013ffU)

/* Properties of firewall at slave: MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                      (36U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                             (8U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                          (0x00000004702000U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                            (0x000000047023ffU)

/* Properties of firewall at slave: MCU_ECC_AGGR0_REGS */
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_ID                                                           (36U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_MMR_BASE                                                     (0x00000045009000U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_NUM_REGIONS                                                  (8U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_ECC_AGGR_START                                               (0x00000004703000U)
#define CSL_STD_FW_MCU_ECC_AGGR0_REGS_ECC_AGGR_END                                                 (0x000000047033ffU)

/* Properties of firewall at slave: MCU_ECC_AGGR1_REGS */
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_ID                                                           (36U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_MMR_BASE                                                     (0x00000045009000U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_NUM_REGIONS                                                  (8U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_ECC_AGGR_START                                               (0x00000004704000U)
#define CSL_STD_FW_MCU_ECC_AGGR1_REGS_ECC_AGGR_END                                                 (0x000000047043ffU)

/* Properties of firewall at slave: MCU_MSRAM_256K0_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_ID                                            (36U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_MMR_BASE                                      (0x00000045009000U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_NUM_REGIONS                                   (8U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                           (0x00000004705000U)
#define CSL_STD_FW_MCU_MSRAM_256K0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                             (0x000000047053ffU)

/* Properties of firewall at slave: MCU_MSRAM_256K1_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_ID                                            (36U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_TYPE                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_MMR_BASE                                      (0x00000045009000U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_NUM_REGIONS                                   (8U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                       (3U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                           (0x00000004706000U)
#define CSL_STD_FW_MCU_MSRAM_256K1_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                             (0x000000047063ffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_ID                                      (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_MMR_BASE                                (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_NUM_REGIONS                             (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_START                    (0x00000004707000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_END                      (0x000000047073ffU)

/* Properties of firewall at slave: MCU_CBASS0_ERR_REGS */
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_ID                                                          (36U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_MMR_BASE                                                    (0x00000045009000U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_NUM_REGIONS                                                 (8U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_ERR_START                                                   (0x00000004720000U)
#define CSL_STD_FW_MCU_CBASS0_ERR_REGS_ERR_END                                                     (0x000000047203ffU)

/* Properties of firewall at slave: MCU_TIMER0_CFG */
#define CSL_STD_FW_MCU_TIMER0_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_TIMER0_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMER0_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMER0_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_TIMER0_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_TIMER0_CFG_CFG_START                                                        (0x00000004800000U)
#define CSL_STD_FW_MCU_TIMER0_CFG_CFG_END                                                          (0x000000048003ffU)

/* Properties of firewall at slave: MCU_TIMER1_CFG */
#define CSL_STD_FW_MCU_TIMER1_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_TIMER1_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMER1_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMER1_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_TIMER1_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_TIMER1_CFG_CFG_START                                                        (0x00000004810000U)
#define CSL_STD_FW_MCU_TIMER1_CFG_CFG_END                                                          (0x000000048103ffU)

/* Properties of firewall at slave: MCU_TIMER2_CFG */
#define CSL_STD_FW_MCU_TIMER2_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_TIMER2_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMER2_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMER2_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_TIMER2_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_TIMER2_CFG_CFG_START                                                        (0x00000004820000U)
#define CSL_STD_FW_MCU_TIMER2_CFG_CFG_END                                                          (0x000000048203ffU)

/* Properties of firewall at slave: MCU_TIMER3_CFG */
#define CSL_STD_FW_MCU_TIMER3_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_TIMER3_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_TIMER3_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_TIMER3_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_TIMER3_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_TIMER3_CFG_CFG_START                                                        (0x00000004830000U)
#define CSL_STD_FW_MCU_TIMER3_CFG_CFG_END                                                          (0x000000048303ffU)

/* Properties of firewall at slave: MCU_RTI0_CFG */
#define CSL_STD_FW_MCU_RTI0_CFG_ID                                                                 (36U)
#define CSL_STD_FW_MCU_RTI0_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_RTI0_CFG_MMR_BASE                                                           (0x00000045009000U)
#define CSL_STD_FW_MCU_RTI0_CFG_NUM_REGIONS                                                        (8U)
#define CSL_STD_FW_MCU_RTI0_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_RTI0_CFG_CFG_START                                                          (0x00000004880000U)
#define CSL_STD_FW_MCU_RTI0_CFG_CFG_END                                                            (0x000000048800ffU)

/* Properties of firewall at slave: MCU_I2C0_CFG */
#define CSL_STD_FW_MCU_I2C0_CFG_ID                                                                 (36U)
#define CSL_STD_FW_MCU_I2C0_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_I2C0_CFG_MMR_BASE                                                           (0x00000045009000U)
#define CSL_STD_FW_MCU_I2C0_CFG_NUM_REGIONS                                                        (8U)
#define CSL_STD_FW_MCU_I2C0_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_I2C0_CFG_CFG_START                                                          (0x00000004900000U)
#define CSL_STD_FW_MCU_I2C0_CFG_CFG_END                                                            (0x000000049000ffU)

/* Properties of firewall at slave: MCU_UART0_MEM */
#define CSL_STD_FW_MCU_UART0_MEM_ID                                                                (36U)
#define CSL_STD_FW_MCU_UART0_MEM_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_UART0_MEM_MMR_BASE                                                          (0x00000045009000U)
#define CSL_STD_FW_MCU_UART0_MEM_NUM_REGIONS                                                       (8U)
#define CSL_STD_FW_MCU_UART0_MEM_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_MCU_UART0_MEM_START                                                             (0x00000004a00000U)
#define CSL_STD_FW_MCU_UART0_MEM_END                                                               (0x00000004a001ffU)

/* Properties of firewall at slave: MCU_MCSPI0_CFG */
#define CSL_STD_FW_MCU_MCSPI0_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCSPI0_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_CFG_START                                                        (0x00000004b00000U)
#define CSL_STD_FW_MCU_MCSPI0_CFG_CFG_END                                                          (0x00000004b003ffU)

/* Properties of firewall at slave: MCU_MCSPI1_CFG */
#define CSL_STD_FW_MCU_MCSPI1_CFG_ID                                                               (36U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCSPI1_CFG_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_CFG_START                                                        (0x00000004b10000U)
#define CSL_STD_FW_MCU_MCSPI1_CFG_CFG_END                                                          (0x00000004b103ffU)

/* Properties of firewall at slave: MCU_DCC0_CFG */
#define CSL_STD_FW_MCU_DCC0_CFG_ID                                                                 (36U)
#define CSL_STD_FW_MCU_DCC0_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_DCC0_CFG_MMR_BASE                                                           (0x00000045009000U)
#define CSL_STD_FW_MCU_DCC0_CFG_NUM_REGIONS                                                        (8U)
#define CSL_STD_FW_MCU_DCC0_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_DCC0_CFG_START                                                              (0x00000004c00000U)
#define CSL_STD_FW_MCU_DCC0_CFG_END                                                                (0x00000004c0003fU)

/* Properties of firewall at slave: MCU_DCC1_CFG */
#define CSL_STD_FW_MCU_DCC1_CFG_ID                                                                 (36U)
#define CSL_STD_FW_MCU_DCC1_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_DCC1_CFG_MMR_BASE                                                           (0x00000045009000U)
#define CSL_STD_FW_MCU_DCC1_CFG_NUM_REGIONS                                                        (8U)
#define CSL_STD_FW_MCU_DCC1_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_DCC1_CFG_START                                                              (0x00000004c10000U)
#define CSL_STD_FW_MCU_DCC1_CFG_END                                                                (0x00000004c1003fU)

/* Properties of firewall at slave: MCU_MCRC64_0_MCRC64_REGS */
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_ID                                                     (36U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_MMR_BASE                                               (0x00000045009000U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_NUM_REGIONS                                            (8U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_REGS_START                                             (0x00000004d00000U)
#define CSL_STD_FW_MCU_MCRC64_0_MCRC64_REGS_REGS_END                                               (0x00000004d00fffU)

/* Properties of firewall at slave: MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                         (36U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                   (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                (8U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                           (0x00000004e00000U)
#define CSL_STD_FW_MCU_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                             (0x00000004e07fffU)

/* Properties of firewall at slave: MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                   (36U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                             (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                          (8U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                            (0x00000004e08000U)
#define CSL_STD_FW_MCU_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                              (0x00000004e081ffU)

/* Properties of firewall at slave: MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_ID                                             (36U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                       (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                    (8U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_START                                       (0x00000004e09000U)
#define CSL_STD_FW_MCU_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_END                                         (0x00000004e090ffU)

/* Properties of firewall at slave: MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                         (36U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                   (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                (8U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                           (0x00000004e10000U)
#define CSL_STD_FW_MCU_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                             (0x00000004e17fffU)

/* Properties of firewall at slave: MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                   (36U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                             (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                          (8U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                            (0x00000004e18000U)
#define CSL_STD_FW_MCU_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                              (0x00000004e181ffU)

/* Properties of firewall at slave: MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_ID                                             (36U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                       (0x00000045009000U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                    (8U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_SS_START                                       (0x00000004e19000U)
#define CSL_STD_FW_MCU_MCAN1_MMR_MMRVBP_MCANSS_REGS_SS_END                                         (0x00000004e190ffU)

/* Properties of firewall at slave: MCU_PBIST0_MEM */
#define CSL_STD_FW_MCU_PBIST0_MEM_ID                                                               (36U)
#define CSL_STD_FW_MCU_PBIST0_MEM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_PBIST0_MEM_MMR_BASE                                                         (0x00000045009000U)
#define CSL_STD_FW_MCU_PBIST0_MEM_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MCU_PBIST0_MEM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MCU_PBIST0_MEM_START                                                            (0x00000004f00000U)
#define CSL_STD_FW_MCU_PBIST0_MEM_END                                                              (0x00000004f003ffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_ICACHE0 */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_ID                                                     (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_MMR_BASE                                               (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_NUM_REGIONS                                            (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_START                                     (0x00000073000000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_END                                       (0x000000737fffffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_DCACHE0 */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_ID                                                     (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_MMR_BASE                                               (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_NUM_REGIONS                                            (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_START                                     (0x00000073800000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_END                                       (0x00000073ffffffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_ATCM0 */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_ID                                                       (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_MMR_BASE                                                 (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_NUM_REGIONS                                              (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_CORE0_ATCM_START                                         (0x00000079000000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_ATCM0_CORE0_ATCM_END                                           (0x00000079007fffU)

/* Properties of firewall at slave: MCU_R5FSS0_CORE0_BTCM0 */
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_ID                                                       (36U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_MMR_BASE                                                 (0x00000045009000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_NUM_REGIONS                                              (8U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_CORE0_BTCM_START                                         (0x00000079020000U)
#define CSL_STD_FW_MCU_R5FSS0_CORE0_BTCM0_CORE0_BTCM_END                                           (0x00000079027fffU)

/* Properties of firewall at slave: MCU_MSRAM_256K0_RAM */
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_ID                                                          (36U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_MMR_BASE                                                    (0x00000045009000U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_NUM_REGIONS                                                 (8U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_RAM_START                                                   (0x00000079100000U)
#define CSL_STD_FW_MCU_MSRAM_256K0_RAM_RAM_END                                                     (0x0000007913ffffU)

/* Properties of firewall at slave: MCU_MSRAM_256K1_RAM */
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_ID                                                          (36U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_MMR_BASE                                                    (0x00000045009000U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_NUM_REGIONS                                                 (8U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_RAM_START                                                   (0x00000079140000U)
#define CSL_STD_FW_MCU_MSRAM_256K1_RAM_RAM_END                                                     (0x0000007917ffffU)

/* Channelized Firewall Definitions */

/* Properties of channelized firewall at: PSC0_VBUS */
#define CSL_CH_FW_PSC0_VBUS_ID                                                                     (128U)
#define CSL_CH_FW_PSC0_VBUS_TYPE                                                                   (CSL_FW_CHANNEL)
#define CSL_CH_FW_PSC0_VBUS_MMR_BASE                                                               (0x00000045020000U)
#define CSL_CH_FW_PSC0_VBUS_NUM_REGIONS                                                            (5U)
#define CSL_CH_FW_PSC0_VBUS_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_START                                                       (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_END                                                         (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_OFFSET_FIRST_RES                                            (0x0000000000000000U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_NUM_CHANNELS                                                (1U)
#define CSL_CH_FW_PSC0_VBUS_SMS_COMMON_CHANNEL_SIZE                                                (4U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_START                                                             (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_END                                                               (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_OFFSET_FIRST_RES                                                  (0x0000000000000020U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_NUM_CHANNELS                                                      (1U)
#define CSL_CH_FW_PSC0_VBUS_TIFS_CHANNEL_SIZE                                                      (4U)
#define CSL_CH_FW_PSC0_VBUS_HSM_START                                                              (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_HSM_END                                                                (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_HSM_OFFSET_FIRST_RES                                                   (0x0000000000000040U)
#define CSL_CH_FW_PSC0_VBUS_HSM_NUM_CHANNELS                                                       (1U)
#define CSL_CH_FW_PSC0_VBUS_HSM_CHANNEL_SIZE                                                       (4U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_START                                                            (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_END                                                              (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_OFFSET_FIRST_RES                                                 (0x0000000000000060U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_NUM_CHANNELS                                                     (1U)
#define CSL_CH_FW_PSC0_VBUS_SA3UL_CHANNEL_SIZE                                                     (4U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_START                                                          (0x0000000000400000U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_END                                                            (0x0000000000400004U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_OFFSET_FIRST_RES                                               (0x0000000000000080U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_NUM_CHANNELS                                                   (1U)
#define CSL_CH_FW_PSC0_VBUS_HSM_ISO_CHANNEL_SIZE                                                   (4U)

#ifdef __cplusplus
}
#endif
#endif /* CSLR_SOC_FW_H_ */
