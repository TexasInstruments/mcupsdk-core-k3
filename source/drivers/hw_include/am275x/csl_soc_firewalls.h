/********************************************************************
*
* SOC FIREWALL PROPERTIES. header file
*
* Copyright (C) 2015-2024 Texas Instruments Incorporated.
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

/* Properties of firewall at slave: FSS1_FSAS_0_DAT_REG1 */
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG1_ID                                                         (7U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG1_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG1_MMR_BASE                                                   (0x00000045001c00U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG1_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG1_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG1_DAT_REG1_START                                             (0x00000068000000U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG1_DAT_REG1_END                                               (0x0000006fffffffU)

/* Properties of firewall at slave: FSS1_FSAS_0_DAT_REG0 */
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG0_ID                                                         (7U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG0_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG0_MMR_BASE                                                   (0x00000045001c00U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG0_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG0_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG0_DAT_REG0_START                                             (0x00000200000000U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG0_DAT_REG0_END                                               (0x000002ffffffffU)

/* Properties of firewall at slave: FSS1_FSAS_0_DAT_REG3 */
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG3_ID                                                         (7U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG3_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG3_MMR_BASE                                                   (0x00000045001c00U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG3_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG3_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG3_DAT_REG3_START                                             (0x00000300000000U)
#define CSL_STD_FW_FSS1_FSAS_0_DAT_REG3_DAT_REG3_END                                               (0x000003ffffffffU)

/* Properties of firewall at slave: FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R1_MAP */
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R1_MAP_ID                                       (8U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R1_MAP_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R1_MAP_MMR_BASE                                 (0x00000045002000U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R1_MAP_NUM_REGIONS                              (8U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R1_MAP_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R1_MAP_OSPI1_R1_START                           (0x00000058000000U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R1_MAP_OSPI1_R1_END                             (0x0000005fffffffU)

/* Properties of firewall at slave: FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R0_MAP */
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R0_MAP_ID                                       (8U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R0_MAP_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R0_MAP_MMR_BASE                                 (0x00000045002000U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R0_MAP_NUM_REGIONS                              (8U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R0_MAP_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R0_MAP_OSPI1_R0_START                           (0x00000600000000U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R0_MAP_OSPI1_R0_END                             (0x000006ffffffffU)

/* Properties of firewall at slave: FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R3_MAP */
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R3_MAP_ID                                       (8U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R3_MAP_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R3_MAP_MMR_BASE                                 (0x00000045002000U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R3_MAP_NUM_REGIONS                              (8U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R3_MAP_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R3_MAP_OSPI1_R3_START                           (0x00000a00000000U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_DATA_VBP_R3_MAP_OSPI1_R3_END                             (0x00000affffffffU)

/* Properties of firewall at slave: DMASS0_ECC_AGGR_0_ECCAGGR_REGS */
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_ID                                               (9U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_START                                    (0x0000003f005000U)
#define CSL_STD_FW_DMASS0_ECC_AGGR_0_ECCAGGR_REGS_ECCAGGR_END                                      (0x0000003f0053ffU)

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

/* Properties of firewall at slave: DMASS0_ETLSW_MMRS */
#define CSL_STD_FW_DMASS0_ETLSW_MMRS_ID                                                            (9U)
#define CSL_STD_FW_DMASS0_ETLSW_MMRS_TYPE                                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_ETLSW_MMRS_MMR_BASE                                                      (0x00000045002400U)
#define CSL_STD_FW_DMASS0_ETLSW_MMRS_NUM_REGIONS                                                   (32U)
#define CSL_STD_FW_DMASS0_ETLSW_MMRS_NUM_PRIV_IDS_PER_REGION                                       (3U)
#define CSL_STD_FW_DMASS0_ETLSW_MMRS_ETLSW_MMRS_START                                              (0x00000048230000U)
#define CSL_STD_FW_DMASS0_ETLSW_MMRS_ETLSW_MMRS_END                                                (0x00000048230fffU)

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
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHAN_PKTDMA_TCHAN_END                                   (0x000000484a3fffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_TCHAN */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_ID                                                   (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_MMR_BASE                                             (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_NUM_REGIONS                                          (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_BCDMA_TCHAN_START                                    (0x000000484a4000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHAN_BCDMA_TCHAN_END                                      (0x000000484a7fffU)

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
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_START                                    (0x000000484c4000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHAN_BCDMA_RCHAN_END                                      (0x000000484c7fffU)

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
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_START                                (0x0000004a840000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_RCHANRT_BCDMA_RCHANRT_END                                  (0x0000004a87ffffU)

/* Properties of firewall at slave: DMASS0_PKTDMA_0_PKTDMA_TCHANRT */
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_ID                                               (9U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_MMR_BASE                                         (0x00000045002400U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_NUM_REGIONS                                      (32U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_PKTDMA_TCHANRT_START                             (0x0000004aa00000U)
#define CSL_STD_FW_DMASS0_PKTDMA_0_PKTDMA_TCHANRT_PKTDMA_TCHANRT_END                               (0x0000004aa3ffffU)

/* Properties of firewall at slave: DMASS0_BCDMA_0_BCDMA_TCHANRT */
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_ID                                                 (9U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_MMR_BASE                                           (0x00000045002400U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_NUM_REGIONS                                        (32U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_BCDMA_TCHANRT_START                                (0x0000004aa40000U)
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_TCHANRT_BCDMA_TCHANRT_END                                  (0x0000004aa7ffffU)

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
#define CSL_STD_FW_DMASS0_BCDMA_0_BCDMA_BCHANRT_BCDMA_BCHANRT_END                                  (0x0000004c03ffffU)

/* Properties of firewall at slave: CBASS_DBG0_ERR_REGS */
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_ID                                                          (10U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_MMR_BASE                                                    (0x00000045002800U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_NUM_REGIONS                                                 (16U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_ERR_START                                                   (0x00000000200000U)
#define CSL_STD_FW_CBASS_DBG0_ERR_REGS_ERR_END                                                     (0x000000002003ffU)

/* Properties of firewall at slave: PBIST7_MEM */
#define CSL_STD_FW_PBIST7_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST7_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST7_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST7_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST7_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST7_MEM_START                                                                (0x00000000340000U)
#define CSL_STD_FW_PBIST7_MEM_END                                                                  (0x000000003403ffU)

/* Properties of firewall at slave: PBIST8_MEM */
#define CSL_STD_FW_PBIST8_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST8_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST8_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST8_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST8_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST8_MEM_START                                                                (0x00000000350000U)
#define CSL_STD_FW_PBIST8_MEM_END                                                                  (0x000000003503ffU)

/* Properties of firewall at slave: C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST */
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_ID                                   (10U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_MMR_BASE                             (0x00000045002800U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_NUM_REGIONS                          (16U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_PBIST_START                          (0x00000000360000U)
#define CSL_STD_FW_C7X256V0_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_PBIST_END                            (0x000000003603ffU)

/* Properties of firewall at slave: C7X256V1_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST */
#define CSL_STD_FW_C7X256V1_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_ID                                   (10U)
#define CSL_STD_FW_C7X256V1_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_MMR_BASE                             (0x00000045002800U)
#define CSL_STD_FW_C7X256V1_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_NUM_REGIONS                          (16U)
#define CSL_STD_FW_C7X256V1_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_C7X256V1_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_PBIST_START                          (0x00000000370000U)
#define CSL_STD_FW_C7X256V1_PBIST_VBUSP_PBIST_CFG_VBUSP_PBIST_PBIST_END                            (0x000000003703ffU)

/* Properties of firewall at slave: PBIST0_MEM */
#define CSL_STD_FW_PBIST0_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST0_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST0_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST0_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST0_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST0_MEM_START                                                                (0x00000000390000U)
#define CSL_STD_FW_PBIST0_MEM_END                                                                  (0x000000003903ffU)

/* Properties of firewall at slave: PBIST1_MEM */
#define CSL_STD_FW_PBIST1_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST1_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST1_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST1_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST1_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST1_MEM_START                                                                (0x000000003a0000U)
#define CSL_STD_FW_PBIST1_MEM_END                                                                  (0x000000003a03ffU)

/* Properties of firewall at slave: PBIST2_MEM */
#define CSL_STD_FW_PBIST2_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST2_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST2_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST2_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST2_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST2_MEM_START                                                                (0x000000003b0000U)
#define CSL_STD_FW_PBIST2_MEM_END                                                                  (0x000000003b03ffU)

/* Properties of firewall at slave: PBIST3_MEM */
#define CSL_STD_FW_PBIST3_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST3_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST3_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST3_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST3_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST3_MEM_START                                                                (0x000000003c0000U)
#define CSL_STD_FW_PBIST3_MEM_END                                                                  (0x000000003c03ffU)

/* Properties of firewall at slave: PBIST4_MEM */
#define CSL_STD_FW_PBIST4_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST4_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST4_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST4_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST4_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST4_MEM_START                                                                (0x000000003d0000U)
#define CSL_STD_FW_PBIST4_MEM_END                                                                  (0x000000003d03ffU)

/* Properties of firewall at slave: PBIST5_MEM */
#define CSL_STD_FW_PBIST5_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST5_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST5_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST5_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST5_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST5_MEM_START                                                                (0x000000003e0000U)
#define CSL_STD_FW_PBIST5_MEM_END                                                                  (0x000000003e03ffU)

/* Properties of firewall at slave: PBIST6_MEM */
#define CSL_STD_FW_PBIST6_MEM_ID                                                                   (10U)
#define CSL_STD_FW_PBIST6_MEM_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PBIST6_MEM_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_PBIST6_MEM_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_PBIST6_MEM_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PBIST6_MEM_START                                                                (0x000000003f0000U)
#define CSL_STD_FW_PBIST6_MEM_END                                                                  (0x000000003f03ffU)

/* Properties of firewall at slave: USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE */
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_ID                          (10U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_TYPE                        (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_MMR_BASE                    (0x00000045002800U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_REGIONS                 (16U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_NUM_PRIV_IDS_PER_REGION     (3U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_START (0x00000000703000U)
#define CSL_STD_FW_USB0_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_DEBUG_TRACE_MMR_TRACE_VBUSP_USB2SS_DEBUG_TRACE_END (0x000000007031ffU)

/* Properties of firewall at slave: C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS */
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_ID                                         (10U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_MMR_BASE                                   (0x00000045002800U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_ECC_AGGR_START                             (0x0000000071a000U)
#define CSL_STD_FW_C7X256V0_ECC_AGGR_C7XV_ECC_AGGR_REGS_ECC_AGGR_END                               (0x0000000071a3ffU)

/* Properties of firewall at slave: C7X256V1_ECC_AGGR_C7XV_ECC_AGGR_REGS */
#define CSL_STD_FW_C7X256V1_ECC_AGGR_C7XV_ECC_AGGR_REGS_ID                                         (10U)
#define CSL_STD_FW_C7X256V1_ECC_AGGR_C7XV_ECC_AGGR_REGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_ECC_AGGR_C7XV_ECC_AGGR_REGS_MMR_BASE                                   (0x00000045002800U)
#define CSL_STD_FW_C7X256V1_ECC_AGGR_C7XV_ECC_AGGR_REGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_C7X256V1_ECC_AGGR_C7XV_ECC_AGGR_REGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_C7X256V1_ECC_AGGR_C7XV_ECC_AGGR_REGS_ECC_AGGR_START                             (0x0000000071b000U)
#define CSL_STD_FW_C7X256V1_ECC_AGGR_C7XV_ECC_AGGR_REGS_ECC_AGGR_END                               (0x0000000071b3ffU)

/* Properties of firewall at slave: R5FSS0_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_R5FSS0_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_ID                                 (10U)
#define CSL_STD_FW_R5FSS0_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_MMR_BASE                           (0x00000045002800U)
#define CSL_STD_FW_R5FSS0_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_NUM_REGIONS                        (16U)
#define CSL_STD_FW_R5FSS0_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_R5FSS0_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_START               (0x00000000730000U)
#define CSL_STD_FW_R5FSS0_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_END                 (0x000000007303ffU)

/* Properties of firewall at slave: R5FSS1_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_R5FSS1_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_ID                                 (10U)
#define CSL_STD_FW_R5FSS1_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_TYPE                               (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_MMR_BASE                           (0x00000045002800U)
#define CSL_STD_FW_R5FSS1_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_NUM_REGIONS                        (16U)
#define CSL_STD_FW_R5FSS1_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION            (3U)
#define CSL_STD_FW_R5FSS1_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_START               (0x00000000731000U)
#define CSL_STD_FW_R5FSS1_CORE0_ECC_AGGR_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_END                 (0x000000007313ffU)

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

/* Properties of firewall at slave: TIMER8_CFG */
#define CSL_STD_FW_TIMER8_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER8_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER8_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER8_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER8_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER8_CFG_CFG_START                                                            (0x00000002480000U)
#define CSL_STD_FW_TIMER8_CFG_CFG_END                                                              (0x000000024803ffU)

/* Properties of firewall at slave: TIMER9_CFG */
#define CSL_STD_FW_TIMER9_CFG_ID                                                                   (10U)
#define CSL_STD_FW_TIMER9_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER9_CFG_MMR_BASE                                                             (0x00000045002800U)
#define CSL_STD_FW_TIMER9_CFG_NUM_REGIONS                                                          (16U)
#define CSL_STD_FW_TIMER9_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_TIMER9_CFG_CFG_START                                                            (0x00000002490000U)
#define CSL_STD_FW_TIMER9_CFG_CFG_END                                                              (0x000000024903ffU)

/* Properties of firewall at slave: TIMER10_CFG */
#define CSL_STD_FW_TIMER10_CFG_ID                                                                  (10U)
#define CSL_STD_FW_TIMER10_CFG_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER10_CFG_MMR_BASE                                                            (0x00000045002800U)
#define CSL_STD_FW_TIMER10_CFG_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_TIMER10_CFG_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_TIMER10_CFG_CFG_START                                                           (0x000000024a0000U)
#define CSL_STD_FW_TIMER10_CFG_CFG_END                                                             (0x000000024a03ffU)

/* Properties of firewall at slave: TIMER11_CFG */
#define CSL_STD_FW_TIMER11_CFG_ID                                                                  (10U)
#define CSL_STD_FW_TIMER11_CFG_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER11_CFG_MMR_BASE                                                            (0x00000045002800U)
#define CSL_STD_FW_TIMER11_CFG_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_TIMER11_CFG_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_TIMER11_CFG_CFG_START                                                           (0x000000024b0000U)
#define CSL_STD_FW_TIMER11_CFG_CFG_END                                                             (0x000000024b03ffU)

/* Properties of firewall at slave: TIMER12_CFG */
#define CSL_STD_FW_TIMER12_CFG_ID                                                                  (10U)
#define CSL_STD_FW_TIMER12_CFG_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER12_CFG_MMR_BASE                                                            (0x00000045002800U)
#define CSL_STD_FW_TIMER12_CFG_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_TIMER12_CFG_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_TIMER12_CFG_CFG_START                                                           (0x000000024c0000U)
#define CSL_STD_FW_TIMER12_CFG_CFG_END                                                             (0x000000024c03ffU)

/* Properties of firewall at slave: TIMER13_CFG */
#define CSL_STD_FW_TIMER13_CFG_ID                                                                  (10U)
#define CSL_STD_FW_TIMER13_CFG_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER13_CFG_MMR_BASE                                                            (0x00000045002800U)
#define CSL_STD_FW_TIMER13_CFG_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_TIMER13_CFG_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_TIMER13_CFG_CFG_START                                                           (0x000000024d0000U)
#define CSL_STD_FW_TIMER13_CFG_CFG_END                                                             (0x000000024d03ffU)

/* Properties of firewall at slave: TIMER14_CFG */
#define CSL_STD_FW_TIMER14_CFG_ID                                                                  (10U)
#define CSL_STD_FW_TIMER14_CFG_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER14_CFG_MMR_BASE                                                            (0x00000045002800U)
#define CSL_STD_FW_TIMER14_CFG_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_TIMER14_CFG_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_TIMER14_CFG_CFG_START                                                           (0x000000024e0000U)
#define CSL_STD_FW_TIMER14_CFG_CFG_END                                                             (0x000000024e03ffU)

/* Properties of firewall at slave: TIMER15_CFG */
#define CSL_STD_FW_TIMER15_CFG_ID                                                                  (10U)
#define CSL_STD_FW_TIMER15_CFG_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMER15_CFG_MMR_BASE                                                            (0x00000045002800U)
#define CSL_STD_FW_TIMER15_CFG_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_TIMER15_CFG_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_TIMER15_CFG_CFG_START                                                           (0x000000024f0000U)
#define CSL_STD_FW_TIMER15_CFG_CFG_END                                                             (0x000000024f03ffU)

/* Properties of firewall at slave: R5FSS0_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS */
#define CSL_STD_FW_R5FSS0_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_ID                            (10U)
#define CSL_STD_FW_R5FSS0_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_TYPE                          (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_MMR_BASE                      (0x00000045002800U)
#define CSL_STD_FW_R5FSS0_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_NUM_REGIONS                   (16U)
#define CSL_STD_FW_R5FSS0_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_NUM_PRIV_IDS_PER_REGION       (3U)
#define CSL_STD_FW_R5FSS0_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_COMPARE_CFG_START             (0x00000005b00000U)
#define CSL_STD_FW_R5FSS0_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_COMPARE_CFG_END               (0x00000005b000ffU)

/* Properties of firewall at slave: R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS */
#define CSL_STD_FW_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_ID                                           (10U)
#define CSL_STD_FW_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_MMR_BASE                                     (0x00000045002800U)
#define CSL_STD_FW_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_REGIONS                                  (16U)
#define CSL_STD_FW_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_START                    (0x00000005b01000U)
#define CSL_STD_FW_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_END                      (0x00000005b010ffU)

/* Properties of firewall at slave: R5FSS0_CORE1_ECC_AGGR_REGS */
#define CSL_STD_FW_R5FSS0_CORE1_ECC_AGGR_REGS_ID                                                   (10U)
#define CSL_STD_FW_R5FSS0_CORE1_ECC_AGGR_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE1_ECC_AGGR_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_R5FSS0_CORE1_ECC_AGGR_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_R5FSS0_CORE1_ECC_AGGR_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_R5FSS0_CORE1_ECC_AGGR_REGS_CORE1_ECC_AGGR_START                                 (0x00000005b02000U)
#define CSL_STD_FW_R5FSS0_CORE1_ECC_AGGR_REGS_CORE1_ECC_AGGR_END                                   (0x00000005b023ffU)

/* Properties of firewall at slave: R5FSS1_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS */
#define CSL_STD_FW_R5FSS1_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_ID                            (10U)
#define CSL_STD_FW_R5FSS1_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_TYPE                          (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_MMR_BASE                      (0x00000045002800U)
#define CSL_STD_FW_R5FSS1_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_NUM_REGIONS                   (16U)
#define CSL_STD_FW_R5FSS1_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_NUM_PRIV_IDS_PER_REGION       (3U)
#define CSL_STD_FW_R5FSS1_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_COMPARE_CFG_START             (0x00000005b20000U)
#define CSL_STD_FW_R5FSS1_COMMON0_PULSAR_SL_COMPARE_WRAPPER_CFG_MMRS_COMPARE_CFG_END               (0x00000005b200ffU)

/* Properties of firewall at slave: R5FSS1_COMMON0_EVNT_BUS_VBUSP_MMRS */
#define CSL_STD_FW_R5FSS1_COMMON0_EVNT_BUS_VBUSP_MMRS_ID                                           (10U)
#define CSL_STD_FW_R5FSS1_COMMON0_EVNT_BUS_VBUSP_MMRS_TYPE                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_COMMON0_EVNT_BUS_VBUSP_MMRS_MMR_BASE                                     (0x00000045002800U)
#define CSL_STD_FW_R5FSS1_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_REGIONS                                  (16U)
#define CSL_STD_FW_R5FSS1_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_PRIV_IDS_PER_REGION                      (3U)
#define CSL_STD_FW_R5FSS1_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_START                    (0x00000005b21000U)
#define CSL_STD_FW_R5FSS1_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_END                      (0x00000005b210ffU)

/* Properties of firewall at slave: R5FSS1_CORE1_ECC_AGGR_REGS */
#define CSL_STD_FW_R5FSS1_CORE1_ECC_AGGR_REGS_ID                                                   (10U)
#define CSL_STD_FW_R5FSS1_CORE1_ECC_AGGR_REGS_TYPE                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE1_ECC_AGGR_REGS_MMR_BASE                                             (0x00000045002800U)
#define CSL_STD_FW_R5FSS1_CORE1_ECC_AGGR_REGS_NUM_REGIONS                                          (16U)
#define CSL_STD_FW_R5FSS1_CORE1_ECC_AGGR_REGS_NUM_PRIV_IDS_PER_REGION                              (3U)
#define CSL_STD_FW_R5FSS1_CORE1_ECC_AGGR_REGS_CORE1_ECC_AGGR_START                                 (0x00000005b22000U)
#define CSL_STD_FW_R5FSS1_CORE1_ECC_AGGR_REGS_CORE1_ECC_AGGR_END                                   (0x00000005b223ffU)

/* Properties of firewall at slave: RTI4_CFG */
#define CSL_STD_FW_RTI4_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI4_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI4_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI4_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI4_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI4_CFG_CFG_START                                                              (0x0000000e000000U)
#define CSL_STD_FW_RTI4_CFG_CFG_END                                                                (0x0000000e0000ffU)

/* Properties of firewall at slave: RTI5_CFG */
#define CSL_STD_FW_RTI5_CFG_ID                                                                     (10U)
#define CSL_STD_FW_RTI5_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI5_CFG_MMR_BASE                                                               (0x00000045002800U)
#define CSL_STD_FW_RTI5_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_RTI5_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI5_CFG_CFG_START                                                              (0x0000000e010000U)
#define CSL_STD_FW_RTI5_CFG_CFG_END                                                                (0x0000000e0100ffU)

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

/* Properties of firewall at slave: USB0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_ID                                                       (10U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_MMR_BASE                                                 (0x00000045002800U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_NUM_REGIONS                                              (16U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_ECC_AGGR_START                                           (0x0000000f980000U)
#define CSL_STD_FW_USB0_ECC_AGGR_CFG_REGS_ECC_AGGR_END                                             (0x0000000f9803ffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_CFG_MMR */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_ID                                                  (10U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_MMR_BASE                                            (0x00000045002800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_NUM_REGIONS                                         (16U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_START                                               (0x00000030240000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_CFG_MMR_END                                                 (0x0000003024ffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_CFG_MMR */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_CFG_MMR_ID                                                  (10U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_CFG_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_CFG_MMR_MMR_BASE                                            (0x00000045002800U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_CFG_MMR_NUM_REGIONS                                         (16U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_CFG_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_CFG_MMR_START                                               (0x00000030250000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_CFG_MMR_END                                                 (0x0000003025ffffU)

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

/* Properties of firewall at slave: CBASS0_ERR_REGS */
#define CSL_STD_FW_CBASS0_ERR_REGS_ID                                                              (10U)
#define CSL_STD_FW_CBASS0_ERR_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS0_ERR_REGS_MMR_BASE                                                        (0x00000045002800U)
#define CSL_STD_FW_CBASS0_ERR_REGS_NUM_REGIONS                                                     (16U)
#define CSL_STD_FW_CBASS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_CBASS0_ERR_REGS_ERR_START                                                       (0x0000003a000000U)
#define CSL_STD_FW_CBASS0_ERR_REGS_ERR_END                                                         (0x0000003a0003ffU)

/* Properties of firewall at slave: ECC_AGGR2_REGS */
#define CSL_STD_FW_ECC_AGGR2_REGS_ID                                                               (10U)
#define CSL_STD_FW_ECC_AGGR2_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_ECC_AGGR2_REGS_MMR_BASE                                                         (0x00000045002800U)
#define CSL_STD_FW_ECC_AGGR2_REGS_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_ECC_AGGR2_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_ECC_AGGR2_REGS_ECC_AGGR_START                                                   (0x0000003f013000U)
#define CSL_STD_FW_ECC_AGGR2_REGS_ECC_AGGR_END                                                     (0x0000003f0133ffU)

/* Properties of firewall at slave: CPSW0_CPSW_NUSS_VBUSP_ECC */
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_ID                                                    (11U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_MMR_BASE                                              (0x00000045002c00U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_NUM_REGIONS                                           (16U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_CPSW_NUSS_VBUSP_ECC_START                             (0x00000000704000U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ECC_CPSW_NUSS_VBUSP_ECC_END                               (0x000000007043ffU)

/* Properties of firewall at slave: MMCSD0_ECC_AGGR_RXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_START                             (0x00000000708000U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_RXMEM_CFG_REGS_ECC_AGGR_RXMEM_END                               (0x000000007083ffU)

/* Properties of firewall at slave: MMCSD0_ECC_AGGR_TXMEM_CFG_REGS */
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_ID                                               (11U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_TYPE                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_MMR_BASE                                         (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_NUM_REGIONS                                      (16U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_NUM_PRIV_IDS_PER_REGION                          (3U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_START                             (0x00000000709000U)
#define CSL_STD_FW_MMCSD0_ECC_AGGR_TXMEM_CFG_REGS_ECC_AGGR_TXMEM_END                               (0x000000007093ffU)

/* Properties of firewall at slave: FSS0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_ID                        (11U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_TYPE                      (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                  (0x00000045002c00U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS               (16U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION   (3U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_START (0x00000000716000U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_END (0x000000007163ffU)

/* Properties of firewall at slave: FSS0_FSAS_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_FSS0_FSAS_ECC_AGGR_CFG_REGS_ID                                                  (11U)
#define CSL_STD_FW_FSS0_FSAS_ECC_AGGR_CFG_REGS_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_ECC_AGGR_CFG_REGS_MMR_BASE                                            (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_ECC_AGGR_CFG_REGS_NUM_REGIONS                                         (16U)
#define CSL_STD_FW_FSS0_FSAS_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_FSS0_FSAS_ECC_AGGR_CFG_REGS_FSAS_ECC_AGGR_CFG_START                             (0x00000000717000U)
#define CSL_STD_FW_FSS0_FSAS_ECC_AGGR_CFG_REGS_FSAS_ECC_AGGR_CFG_END                               (0x000000007173ffU)

/* Properties of firewall at slave: MSRAM_1MB0_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MSRAM_1MB0_ECC_AGGR_REGSREGS_ID                                                 (11U)
#define CSL_STD_FW_MSRAM_1MB0_ECC_AGGR_REGSREGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB0_ECC_AGGR_REGSREGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_MSRAM_1MB0_ECC_AGGR_REGSREGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MSRAM_1MB0_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MSRAM_1MB0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                                (0x0000000071c000U)
#define CSL_STD_FW_MSRAM_1MB0_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                                  (0x0000000071c3ffU)

/* Properties of firewall at slave: MSRAM_1MB1_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MSRAM_1MB1_ECC_AGGR_REGSREGS_ID                                                 (11U)
#define CSL_STD_FW_MSRAM_1MB1_ECC_AGGR_REGSREGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB1_ECC_AGGR_REGSREGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_MSRAM_1MB1_ECC_AGGR_REGSREGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MSRAM_1MB1_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MSRAM_1MB1_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                                (0x0000000071d000U)
#define CSL_STD_FW_MSRAM_1MB1_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                                  (0x0000000071d3ffU)

/* Properties of firewall at slave: MSRAM_1MB2_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MSRAM_1MB2_ECC_AGGR_REGSREGS_ID                                                 (11U)
#define CSL_STD_FW_MSRAM_1MB2_ECC_AGGR_REGSREGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB2_ECC_AGGR_REGSREGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_MSRAM_1MB2_ECC_AGGR_REGSREGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MSRAM_1MB2_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MSRAM_1MB2_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                                (0x0000000071e000U)
#define CSL_STD_FW_MSRAM_1MB2_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                                  (0x0000000071e3ffU)

/* Properties of firewall at slave: MSRAM_1MB3_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MSRAM_1MB3_ECC_AGGR_REGSREGS_ID                                                 (11U)
#define CSL_STD_FW_MSRAM_1MB3_ECC_AGGR_REGSREGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB3_ECC_AGGR_REGSREGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_MSRAM_1MB3_ECC_AGGR_REGSREGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MSRAM_1MB3_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MSRAM_1MB3_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                                (0x0000000071f000U)
#define CSL_STD_FW_MSRAM_1MB3_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                                  (0x0000000071f3ffU)

/* Properties of firewall at slave: MSRAM_1MB4_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MSRAM_1MB4_ECC_AGGR_REGSREGS_ID                                                 (11U)
#define CSL_STD_FW_MSRAM_1MB4_ECC_AGGR_REGSREGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB4_ECC_AGGR_REGSREGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_MSRAM_1MB4_ECC_AGGR_REGSREGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MSRAM_1MB4_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MSRAM_1MB4_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                                (0x00000000720000U)
#define CSL_STD_FW_MSRAM_1MB4_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                                  (0x000000007203ffU)

/* Properties of firewall at slave: MSRAM_1MB5_ECC_AGGR_REGSREGS */
#define CSL_STD_FW_MSRAM_1MB5_ECC_AGGR_REGSREGS_ID                                                 (11U)
#define CSL_STD_FW_MSRAM_1MB5_ECC_AGGR_REGSREGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB5_ECC_AGGR_REGSREGS_MMR_BASE                                           (0x00000045002c00U)
#define CSL_STD_FW_MSRAM_1MB5_ECC_AGGR_REGSREGS_NUM_REGIONS                                        (16U)
#define CSL_STD_FW_MSRAM_1MB5_ECC_AGGR_REGSREGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MSRAM_1MB5_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_START                                (0x00000000721000U)
#define CSL_STD_FW_MSRAM_1MB5_ECC_AGGR_REGSREGS_ECC_AGGR_REGS_END                                  (0x000000007213ffU)

/* Properties of firewall at slave: FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_ECC_AGGR_CFG_REGS_ID                         (11U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_ECC_AGGR_CFG_REGS_TYPE                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_ECC_AGGR_CFG_REGS_MMR_BASE                   (0x00000045002c00U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_ECC_AGGR_CFG_REGS_NUM_REGIONS                (16U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION    (3U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_ECC_AGGR_CFG_REGS_HPB_ECC_AGGR_START         (0x00000000722000U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_ECC_AGGR_CFG_REGS_HPB_ECC_AGGR_END           (0x000000007223ffU)

/* Properties of firewall at slave: FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_ID                 (11U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_TYPE               (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE           (0x00000045002c00U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS        (16U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI0_ECC_AGGR_START (0x00000000723000U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI0_ECC_AGGR_END (0x000000007233ffU)

/* Properties of firewall at slave: FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_ID                 (11U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_TYPE               (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE           (0x00000045002c00U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS        (16U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI1_ECC_AGGR_START (0x00000000724000U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_OSPI_WRAP_ECC_AGGR_VBP_REGS_OSPI1_ECC_AGGR_END (0x000000007243ffU)

/* Properties of firewall at slave: CPSW0_CPSW_NUSS_VBUSP */
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_ID                                                        (11U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_MMR_BASE                                                  (0x00000045002c00U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_CPSW_NUSS_VBUSP_START                                     (0x00000008000000U)
#define CSL_STD_FW_CPSW0_CPSW_NUSS_VBUSP_CPSW_NUSS_VBUSP_END                                       (0x000000081fffffU)

/* Properties of firewall at slave: MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG */
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_ID                                              (11U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_MMR_BASE                                        (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_REGIONS                                     (16U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_START                                   (0x0000000fa00000U)
#define CSL_STD_FW_MMCSD0_SDHC_WRAP_CTL_CFG_CTLCFG_CTL_CFG_END                                     (0x0000000fa00fffU)

/* Properties of firewall at slave: MMCSD0_REGS_SS_CFG_SSCFG */
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_ID                                                     (11U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_MMR_BASE                                               (0x00000045002c00U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_NUM_REGIONS                                            (16U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_SS_CFG_START                                           (0x0000000fa08000U)
#define CSL_STD_FW_MMCSD0_REGS_SS_CFG_SSCFG_SS_CFG_END                                             (0x0000000fa083ffU)

/* Properties of firewall at slave: FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS */
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_ID                                         (11U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_MMR_BASE                                   (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_FSS_MMR_FSS_MMR_CFG_FSS_GEN_START          (0x0000000fc00000U)
#define CSL_STD_FW_FSS0_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_FSS_MMR_FSS_MMR_CFG_FSS_GEN_END            (0x0000000fc000ffU)

/* Properties of firewall at slave: FSS0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS */
#define CSL_STD_FW_FSS0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_ID                                          (11U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_MMR_BASE                                    (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_NUM_REGIONS                                 (16U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_FSAS_FSAS_MMR_CFG_FSAS_GEN_START            (0x0000000fc10000U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_FSAS_FSAS_MMR_CFG_FSAS_GEN_END              (0x0000000fc100ffU)

/* Properties of firewall at slave: FSS0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS */
#define CSL_STD_FW_FSS0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_ID                                       (11U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_MMR_BASE                                 (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_NUM_REGIONS                              (16U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_START       (0x0000000fc20000U)
#define CSL_STD_FW_FSS0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_END         (0x0000000fc20fffU)

/* Properties of firewall at slave: FSS1_HYPERBUS1P0_0_HB_HPB_CFG_SYS_SS_CFG_SS_CFG_REG */
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_SYS_SS_CFG_SS_CFG_REG_ID                          (11U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_SYS_SS_CFG_SS_CFG_REG_TYPE                        (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_SYS_SS_CFG_SS_CFG_REG_MMR_BASE                    (0x00000045002c00U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_SYS_SS_CFG_SS_CFG_REG_NUM_REGIONS                 (16U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_SYS_SS_CFG_SS_CFG_REG_NUM_PRIV_IDS_PER_REGION     (3U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_SYS_SS_CFG_SS_CFG_REG_HPB_SS_CFG_START            (0x0000000fc30000U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_SYS_SS_CFG_SS_CFG_REG_HPB_SS_CFG_END              (0x0000000fc300ffU)

/* Properties of firewall at slave: FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_CORE_CFG_CORE_CFG_REG */
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_CORE_CFG_CORE_CFG_REG_ID                     (11U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_CORE_CFG_CORE_CFG_REG_TYPE                   (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_CORE_CFG_CORE_CFG_REG_MMR_BASE               (0x00000045002c00U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_CORE_CFG_CORE_CFG_REG_NUM_REGIONS            (16U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_CORE_CFG_CORE_CFG_REG_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_CORE_CFG_CORE_CFG_REG_HPB_CTRL_START         (0x0000000fc34000U)
#define CSL_STD_FW_FSS1_HYPERBUS1P0_0_HB_HPB_CFG_WRAP_CORE_CFG_CORE_CFG_REG_HPB_CTRL_END           (0x0000000fc340ffU)

/* Properties of firewall at slave: FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS */
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_ID      (11U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_TYPE    (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_MMR_BASE (0x00000045002c00U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_REGIONS (16U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_START (0x0000000fc40000U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_END (0x0000000fc400ffU)

/* Properties of firewall at slave: FSS0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS */
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_ID                                    (11U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_TYPE                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_MMR_BASE                              (0x00000045002c00U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_REGIONS                           (16U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_PRIV_IDS_PER_REGION               (3U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI0_OSPI_CFG_VBUSP_MMRVBP_START     (0x0000000fc44000U)
#define CSL_STD_FW_FSS0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI0_OSPI_CFG_VBUSP_MMRVBP_END       (0x0000000fc441ffU)

/* Properties of firewall at slave: FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS */
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_ID (11U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_MMR_BASE (0x00000045002c00U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_REGIONS (16U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI1_CTRL_START (0x0000000fc50000U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI1_CTRL_END (0x0000000fc500ffU)

/* Properties of firewall at slave: FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS */
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_ID                             (11U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_MMR_BASE                       (0x00000045002c00U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_REGIONS                    (16U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI1_SS_CFG_START             (0x0000000fc54000U)
#define CSL_STD_FW_FSS1_OSPI_1_OSPI1_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI1_SS_CFG_END               (0x0000000fc541ffU)

/* Properties of firewall at slave: FSS0_FSAS_FOTA_MMR_CFG_FOTA_GENREGS */
#define CSL_STD_FW_FSS0_FSAS_FOTA_MMR_CFG_FOTA_GENREGS_ID                                          (11U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_MMR_CFG_FOTA_GENREGS_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_FOTA_MMR_CFG_FOTA_GENREGS_MMR_BASE                                    (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_MMR_CFG_FOTA_GENREGS_NUM_REGIONS                                 (16U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_MMR_CFG_FOTA_GENREGS_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_MMR_CFG_FOTA_GENREGS_FSAS_FOTA_MMR_CFG_FOTA_GEN_START            (0x0000000fc60000U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_MMR_CFG_FOTA_GENREGS_FSAS_FOTA_MMR_CFG_FOTA_GEN_END              (0x0000000fc600ffU)

/* Properties of firewall at slave: FSS0_FSAS_FOTA_PDMEM_CFG_PDMEM_GENREGS */
#define CSL_STD_FW_FSS0_FSAS_FOTA_PDMEM_CFG_PDMEM_GENREGS_ID                                       (11U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_PDMEM_CFG_PDMEM_GENREGS_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_FOTA_PDMEM_CFG_PDMEM_GENREGS_MMR_BASE                                 (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_PDMEM_CFG_PDMEM_GENREGS_NUM_REGIONS                              (16U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_PDMEM_CFG_PDMEM_GENREGS_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_PDMEM_CFG_PDMEM_GENREGS_FSAS_FOTA_PDMEM_CFG_PDMEM_GEN_START      (0x0000000fc61000U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_PDMEM_CFG_PDMEM_GENREGS_FSAS_FOTA_PDMEM_CFG_PDMEM_GEN_END        (0x0000000fc617ffU)

/* Properties of firewall at slave: FSS0_FSAS_FOTA_IMEM_CFG_IMEM_GENREGS */
#define CSL_STD_FW_FSS0_FSAS_FOTA_IMEM_CFG_IMEM_GENREGS_ID                                         (11U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_IMEM_CFG_IMEM_GENREGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_FOTA_IMEM_CFG_IMEM_GENREGS_MMR_BASE                                   (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_IMEM_CFG_IMEM_GENREGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_IMEM_CFG_IMEM_GENREGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_IMEM_CFG_IMEM_GENREGS_FSAS_FOTA_IMEM_CFG_IMEM_GEN_START          (0x0000000fc62000U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_IMEM_CFG_IMEM_GENREGS_FSAS_FOTA_IMEM_CFG_IMEM_GEN_END            (0x0000000fc620ffU)

/* Properties of firewall at slave: FSS0_FSAS_FOTA_WBUF_CFG_WBUF_GENREGS */
#define CSL_STD_FW_FSS0_FSAS_FOTA_WBUF_CFG_WBUF_GENREGS_ID                                         (11U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_WBUF_CFG_WBUF_GENREGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_FSAS_FOTA_WBUF_CFG_WBUF_GENREGS_MMR_BASE                                   (0x00000045002c00U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_WBUF_CFG_WBUF_GENREGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_WBUF_CFG_WBUF_GENREGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_WBUF_CFG_WBUF_GENREGS_FSAS_FOTA_WBUF_CFG_WBUF_GEN_START          (0x0000000fc63000U)
#define CSL_STD_FW_FSS0_FSAS_FOTA_WBUF_CFG_WBUF_GENREGS_FSAS_FOTA_WBUF_CFG_WBUF_GEN_END            (0x0000000fc631ffU)

/* Properties of firewall at slave: FSS1_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS */
#define CSL_STD_FW_FSS1_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_ID                                         (11U)
#define CSL_STD_FW_FSS1_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_MMR_BASE                                   (0x00000045002c00U)
#define CSL_STD_FW_FSS1_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_NUM_REGIONS                                (16U)
#define CSL_STD_FW_FSS1_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_FSS1_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_CFG_START                                  (0x0000000fc80000U)
#define CSL_STD_FW_FSS1_FSS_MMR_FSS_MMR_CFG_FSS_GENREGS_CFG_END                                    (0x0000000fc800ffU)

/* Properties of firewall at slave: FSS1_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS */
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_ID                                   (11U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_MMR_BASE                             (0x00000045002c00U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_NUM_REGIONS                          (16U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_FSAS_CFG_START                       (0x0000000fc90000U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_MMR_CFG_FSAS_GENREGS_FSAS_CFG_END                         (0x0000000fc900ffU)

/* Properties of firewall at slave: FSS1_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS */
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_ID                                (11U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_TYPE                              (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_MMR_BASE                          (0x00000045002c00U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_NUM_REGIONS                       (16U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_NUM_PRIV_IDS_PER_REGION           (3U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_OTFA_CFG_START                    (0x0000000fca0000U)
#define CSL_STD_FW_FSS1_FSAS_0_FSAS_FSAS_OTFA_CFG_FSAS_OTFA_REGS_OTFA_CFG_END                      (0x0000000fca0fffU)

/* Properties of firewall at slave: FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS */
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_ID (11U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_TYPE (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_MMR_BASE (0x00000045002c00U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_REGIONS (16U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_NUM_PRIV_IDS_PER_REGION (3U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI0_CTRL_START (0x0000000fcc0000U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_VBP2APB_WRAP_OSPI_CFG_VBP_OSPI_FLASH_APB_REGS_OSPI0_CTRL_END (0x0000000fcc00ffU)

/* Properties of firewall at slave: FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS */
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_ID                             (11U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_TYPE                           (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_MMR_BASE                       (0x00000045002c00U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_REGIONS                    (16U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_NUM_PRIV_IDS_PER_REGION        (3U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI0_SS_CFG_START             (0x0000000fcc4000U)
#define CSL_STD_FW_FSS1_OSPI_0_OSPI0_OSPI_CFG_VBUSP_MMR_MMRVBP_REGS_OSPI0_SS_CFG_END               (0x0000000fcc41ffU)

/* Properties of firewall at slave: ECC_AGGR3_REGS */
#define CSL_STD_FW_ECC_AGGR3_REGS_ID                                                               (11U)
#define CSL_STD_FW_ECC_AGGR3_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_ECC_AGGR3_REGS_MMR_BASE                                                         (0x00000045002c00U)
#define CSL_STD_FW_ECC_AGGR3_REGS_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_ECC_AGGR3_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_ECC_AGGR3_REGS_REGS_START                                                       (0x0000003f014000U)
#define CSL_STD_FW_ECC_AGGR3_REGS_REGS_END                                                         (0x0000003f0143ffU)

/* Properties of firewall at slave: FSS0_DAT_REG1 */
#define CSL_STD_FW_FSS0_DAT_REG1_ID                                                                (12U)
#define CSL_STD_FW_FSS0_DAT_REG1_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_DAT_REG1_MMR_BASE                                                          (0x00000045003000U)
#define CSL_STD_FW_FSS0_DAT_REG1_NUM_REGIONS                                                       (8U)
#define CSL_STD_FW_FSS0_DAT_REG1_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_FSS0_DAT_REG1_DAT_REG1_START                                                    (0x00000060000000U)
#define CSL_STD_FW_FSS0_DAT_REG1_DAT_REG1_END                                                      (0x00000067ffffffU)

/* Properties of firewall at slave: FSS0_DAT_REG0 */
#define CSL_STD_FW_FSS0_DAT_REG0_ID                                                                (12U)
#define CSL_STD_FW_FSS0_DAT_REG0_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_DAT_REG0_MMR_BASE                                                          (0x00000045003000U)
#define CSL_STD_FW_FSS0_DAT_REG0_NUM_REGIONS                                                       (8U)
#define CSL_STD_FW_FSS0_DAT_REG0_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_FSS0_DAT_REG0_DAT_REG0_START                                                    (0x00000400000000U)
#define CSL_STD_FW_FSS0_DAT_REG0_DAT_REG0_END                                                      (0x000004ffffffffU)

/* Properties of firewall at slave: FSS0_DAT_REG3 */
#define CSL_STD_FW_FSS0_DAT_REG3_ID                                                                (12U)
#define CSL_STD_FW_FSS0_DAT_REG3_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_FSS0_DAT_REG3_MMR_BASE                                                          (0x00000045003000U)
#define CSL_STD_FW_FSS0_DAT_REG3_NUM_REGIONS                                                       (8U)
#define CSL_STD_FW_FSS0_DAT_REG3_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_FSS0_DAT_REG3_DAT_REG3_START                                                    (0x00000500000000U)
#define CSL_STD_FW_FSS0_DAT_REG3_DAT_REG3_END                                                      (0x000005ffffffffU)

/* Properties of firewall at slave: MCRC64_0_MCRC64_REGS */
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_ID                                                         (13U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_MMR_BASE                                                   (0x00000045003400U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_REGS_START                                                 (0x00000030300000U)
#define CSL_STD_FW_MCRC64_0_MCRC64_REGS_REGS_END                                                   (0x00000030300fffU)

/* Properties of firewall at slave: R5FSS0_CORE0_ATCM0 */
#define CSL_STD_FW_R5FSS0_CORE0_ATCM0_ID                                                           (22U)
#define CSL_STD_FW_R5FSS0_CORE0_ATCM0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE0_ATCM0_MMR_BASE                                                     (0x00000045005800U)
#define CSL_STD_FW_R5FSS0_CORE0_ATCM0_NUM_REGIONS                                                  (1U)
#define CSL_STD_FW_R5FSS0_CORE0_ATCM0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_R5FSS0_CORE0_ATCM0_CORE0_ATCM_START                                             (0x00000005c00000U)
#define CSL_STD_FW_R5FSS0_CORE0_ATCM0_CORE0_ATCM_END                                               (0x00000005c0ffffU)

/* Properties of firewall at slave: R5FSS0_CORE0_BTCM0 */
#define CSL_STD_FW_R5FSS0_CORE0_BTCM0_ID                                                           (22U)
#define CSL_STD_FW_R5FSS0_CORE0_BTCM0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE0_BTCM0_MMR_BASE                                                     (0x00000045005800U)
#define CSL_STD_FW_R5FSS0_CORE0_BTCM0_NUM_REGIONS                                                  (1U)
#define CSL_STD_FW_R5FSS0_CORE0_BTCM0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_R5FSS0_CORE0_BTCM0_CORE0_BTCM_START                                             (0x00000005c10000U)
#define CSL_STD_FW_R5FSS0_CORE0_BTCM0_CORE0_BTCM_END                                               (0x00000005c1ffffU)

/* Properties of firewall at slave: R5FSS0_CORE0_ICACHE0 */
#define CSL_STD_FW_R5FSS0_CORE0_ICACHE0_ID                                                         (22U)
#define CSL_STD_FW_R5FSS0_CORE0_ICACHE0_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE0_ICACHE0_MMR_BASE                                                   (0x00000045005800U)
#define CSL_STD_FW_R5FSS0_CORE0_ICACHE0_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_R5FSS0_CORE0_ICACHE0_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_START                                         (0x00000076000000U)
#define CSL_STD_FW_R5FSS0_CORE0_ICACHE0_CORE0_ICACHE_END                                           (0x000000767fffffU)

/* Properties of firewall at slave: R5FSS0_CORE0_DCACHE0 */
#define CSL_STD_FW_R5FSS0_CORE0_DCACHE0_ID                                                         (22U)
#define CSL_STD_FW_R5FSS0_CORE0_DCACHE0_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE0_DCACHE0_MMR_BASE                                                   (0x00000045005800U)
#define CSL_STD_FW_R5FSS0_CORE0_DCACHE0_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_R5FSS0_CORE0_DCACHE0_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_START                                         (0x00000076800000U)
#define CSL_STD_FW_R5FSS0_CORE0_DCACHE0_CORE0_DCACHE_END                                           (0x00000076ffffffU)

/* Properties of firewall at slave: R5FSS0_CORE1_ATCM1 */
#define CSL_STD_FW_R5FSS0_CORE1_ATCM1_ID                                                           (23U)
#define CSL_STD_FW_R5FSS0_CORE1_ATCM1_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE1_ATCM1_MMR_BASE                                                     (0x00000045005c00U)
#define CSL_STD_FW_R5FSS0_CORE1_ATCM1_NUM_REGIONS                                                  (1U)
#define CSL_STD_FW_R5FSS0_CORE1_ATCM1_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_R5FSS0_CORE1_ATCM1_CORE1_ATCM_START                                             (0x00000005d00000U)
#define CSL_STD_FW_R5FSS0_CORE1_ATCM1_CORE1_ATCM_END                                               (0x00000005d07fffU)

/* Properties of firewall at slave: R5FSS0_CORE1_BTCM1 */
#define CSL_STD_FW_R5FSS0_CORE1_BTCM1_ID                                                           (23U)
#define CSL_STD_FW_R5FSS0_CORE1_BTCM1_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE1_BTCM1_MMR_BASE                                                     (0x00000045005c00U)
#define CSL_STD_FW_R5FSS0_CORE1_BTCM1_NUM_REGIONS                                                  (1U)
#define CSL_STD_FW_R5FSS0_CORE1_BTCM1_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_R5FSS0_CORE1_BTCM1_CORE1_BTCM_START                                             (0x00000005d10000U)
#define CSL_STD_FW_R5FSS0_CORE1_BTCM1_CORE1_BTCM_END                                               (0x00000005d17fffU)

/* Properties of firewall at slave: R5FSS0_CORE1_ICACHE1 */
#define CSL_STD_FW_R5FSS0_CORE1_ICACHE1_ID                                                         (23U)
#define CSL_STD_FW_R5FSS0_CORE1_ICACHE1_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE1_ICACHE1_MMR_BASE                                                   (0x00000045005c00U)
#define CSL_STD_FW_R5FSS0_CORE1_ICACHE1_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_R5FSS0_CORE1_ICACHE1_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_R5FSS0_CORE1_ICACHE1_CORE1_ICACHE_START                                         (0x00000077000000U)
#define CSL_STD_FW_R5FSS0_CORE1_ICACHE1_CORE1_ICACHE_END                                           (0x000000777fffffU)

/* Properties of firewall at slave: R5FSS0_CORE1_DCACHE1 */
#define CSL_STD_FW_R5FSS0_CORE1_DCACHE1_ID                                                         (23U)
#define CSL_STD_FW_R5FSS0_CORE1_DCACHE1_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS0_CORE1_DCACHE1_MMR_BASE                                                   (0x00000045005c00U)
#define CSL_STD_FW_R5FSS0_CORE1_DCACHE1_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_R5FSS0_CORE1_DCACHE1_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_R5FSS0_CORE1_DCACHE1_CORE1_DCACHE_START                                         (0x00000077800000U)
#define CSL_STD_FW_R5FSS0_CORE1_DCACHE1_CORE1_DCACHE_END                                           (0x00000077ffffffU)

/* Properties of firewall at slave: R5FSS1_CORE0_ATCM0 */
#define CSL_STD_FW_R5FSS1_CORE0_ATCM0_ID                                                           (24U)
#define CSL_STD_FW_R5FSS1_CORE0_ATCM0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE0_ATCM0_MMR_BASE                                                     (0x00000045006000U)
#define CSL_STD_FW_R5FSS1_CORE0_ATCM0_NUM_REGIONS                                                  (1U)
#define CSL_STD_FW_R5FSS1_CORE0_ATCM0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_R5FSS1_CORE0_ATCM0_CORE0_ATCM_START                                             (0x00000005e00000U)
#define CSL_STD_FW_R5FSS1_CORE0_ATCM0_CORE0_ATCM_END                                               (0x00000005e0ffffU)

/* Properties of firewall at slave: R5FSS1_CORE0_BTCM0 */
#define CSL_STD_FW_R5FSS1_CORE0_BTCM0_ID                                                           (24U)
#define CSL_STD_FW_R5FSS1_CORE0_BTCM0_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE0_BTCM0_MMR_BASE                                                     (0x00000045006000U)
#define CSL_STD_FW_R5FSS1_CORE0_BTCM0_NUM_REGIONS                                                  (1U)
#define CSL_STD_FW_R5FSS1_CORE0_BTCM0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_R5FSS1_CORE0_BTCM0_CORE0_BTCM_START                                             (0x00000005e10000U)
#define CSL_STD_FW_R5FSS1_CORE0_BTCM0_CORE0_BTCM_END                                               (0x00000005e1ffffU)

/* Properties of firewall at slave: R5FSS1_CORE0_ICACHE0 */
#define CSL_STD_FW_R5FSS1_CORE0_ICACHE0_ID                                                         (24U)
#define CSL_STD_FW_R5FSS1_CORE0_ICACHE0_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE0_ICACHE0_MMR_BASE                                                   (0x00000045006000U)
#define CSL_STD_FW_R5FSS1_CORE0_ICACHE0_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_R5FSS1_CORE0_ICACHE0_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_R5FSS1_CORE0_ICACHE0_CORE0_ICACHE_START                                         (0x00000079000000U)
#define CSL_STD_FW_R5FSS1_CORE0_ICACHE0_CORE0_ICACHE_END                                           (0x000000797fffffU)

/* Properties of firewall at slave: R5FSS1_CORE0_DCACHE0 */
#define CSL_STD_FW_R5FSS1_CORE0_DCACHE0_ID                                                         (24U)
#define CSL_STD_FW_R5FSS1_CORE0_DCACHE0_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE0_DCACHE0_MMR_BASE                                                   (0x00000045006000U)
#define CSL_STD_FW_R5FSS1_CORE0_DCACHE0_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_R5FSS1_CORE0_DCACHE0_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_R5FSS1_CORE0_DCACHE0_CORE0_DCACHE_START                                         (0x00000079800000U)
#define CSL_STD_FW_R5FSS1_CORE0_DCACHE0_CORE0_DCACHE_END                                           (0x00000079ffffffU)

/* Properties of firewall at slave: R5FSS1_CORE1_ATCM1 */
#define CSL_STD_FW_R5FSS1_CORE1_ATCM1_ID                                                           (25U)
#define CSL_STD_FW_R5FSS1_CORE1_ATCM1_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE1_ATCM1_MMR_BASE                                                     (0x00000045006400U)
#define CSL_STD_FW_R5FSS1_CORE1_ATCM1_NUM_REGIONS                                                  (1U)
#define CSL_STD_FW_R5FSS1_CORE1_ATCM1_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_R5FSS1_CORE1_ATCM1_CORE1_ATCM_START                                             (0x00000005f00000U)
#define CSL_STD_FW_R5FSS1_CORE1_ATCM1_CORE1_ATCM_END                                               (0x00000005f07fffU)

/* Properties of firewall at slave: R5FSS1_CORE1_BTCM1 */
#define CSL_STD_FW_R5FSS1_CORE1_BTCM1_ID                                                           (25U)
#define CSL_STD_FW_R5FSS1_CORE1_BTCM1_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE1_BTCM1_MMR_BASE                                                     (0x00000045006400U)
#define CSL_STD_FW_R5FSS1_CORE1_BTCM1_NUM_REGIONS                                                  (1U)
#define CSL_STD_FW_R5FSS1_CORE1_BTCM1_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_R5FSS1_CORE1_BTCM1_CORE1_BTCM_START                                             (0x00000005f10000U)
#define CSL_STD_FW_R5FSS1_CORE1_BTCM1_CORE1_BTCM_END                                               (0x00000005f17fffU)

/* Properties of firewall at slave: R5FSS1_CORE1_ICACHE1 */
#define CSL_STD_FW_R5FSS1_CORE1_ICACHE1_ID                                                         (25U)
#define CSL_STD_FW_R5FSS1_CORE1_ICACHE1_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE1_ICACHE1_MMR_BASE                                                   (0x00000045006400U)
#define CSL_STD_FW_R5FSS1_CORE1_ICACHE1_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_R5FSS1_CORE1_ICACHE1_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_R5FSS1_CORE1_ICACHE1_CORE1_ICACHE_START                                         (0x0000007a000000U)
#define CSL_STD_FW_R5FSS1_CORE1_ICACHE1_CORE1_ICACHE_END                                           (0x0000007a7fffffU)

/* Properties of firewall at slave: R5FSS1_CORE1_DCACHE1 */
#define CSL_STD_FW_R5FSS1_CORE1_DCACHE1_ID                                                         (25U)
#define CSL_STD_FW_R5FSS1_CORE1_DCACHE1_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_R5FSS1_CORE1_DCACHE1_MMR_BASE                                                   (0x00000045006400U)
#define CSL_STD_FW_R5FSS1_CORE1_DCACHE1_NUM_REGIONS                                                (1U)
#define CSL_STD_FW_R5FSS1_CORE1_DCACHE1_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_R5FSS1_CORE1_DCACHE1_CORE1_DCACHE_START                                         (0x0000007a800000U)
#define CSL_STD_FW_R5FSS1_CORE1_DCACHE1_CORE1_DCACHE_END                                           (0x0000007affffffU)

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
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_NUM_REGIONS                                                  (24U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_GTC_CFG0_START                                               (0x00000000a80000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG0_GTC_CFG0_END                                                 (0x00000000a803ffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG1 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_NUM_REGIONS                                                  (24U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_GTC_CFG1_START                                               (0x00000000a90000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG1_GTC_CFG1_END                                                 (0x00000000a93fffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG2 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_NUM_REGIONS                                                  (24U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_GTC_CFG2_START                                               (0x00000000aa0000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG2_GTC_CFG2_END                                                 (0x00000000aa3fffU)

/* Properties of firewall at slave: WKUP_GTC0_GTC_CFG3 */
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_ID                                                           (34U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_MMR_BASE                                                     (0x00000045008800U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_NUM_REGIONS                                                  (24U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_GTC_CFG3_START                                               (0x00000000ab0000U)
#define CSL_STD_FW_WKUP_GTC0_GTC_CFG3_GTC_CFG3_END                                                 (0x00000000ab3fffU)

/* Properties of firewall at slave: WKUP_VTM0_MMR_VBUSP_CFG1 */
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_ID                                                     (34U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_MMR_BASE                                               (0x00000045008800U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_NUM_REGIONS                                            (24U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_MMR_VBUSP_CFG1_START                                   (0x00000000b00000U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG1_MMR_VBUSP_CFG1_END                                     (0x00000000b003ffU)

/* Properties of firewall at slave: WKUP_VTM0_MMR_VBUSP_CFG2 */
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_ID                                                     (34U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_MMR_BASE                                               (0x00000045008800U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_NUM_REGIONS                                            (24U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_MMR_VBUSP_CFG2_START                                   (0x00000000b01000U)
#define CSL_STD_FW_WKUP_VTM0_MMR_VBUSP_CFG2_MMR_VBUSP_CFG2_END                                     (0x00000000b013ffU)

/* Properties of firewall at slave: WKUP_VTM0_ECCAGGR_CFG_REGS */
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_ID                                                  (34U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_MMR_BASE                                            (0x00000045008800U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_NUM_REGIONS                                         (24U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_START                                   (0x00000000b02000U)
#define CSL_STD_FW_WKUP_VTM0__ECCAGGR_CFG_REGS_ECCAGGR_CFG_END                                     (0x00000000b023ffU)

/* Properties of firewall at slave: WKUP_RTI0_CFG */
#define CSL_STD_FW_WKUP_RTI0_CFG_ID                                                                (34U)
#define CSL_STD_FW_WKUP_RTI0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_RTI0_CFG_MMR_BASE                                                          (0x00000045008800U)
#define CSL_STD_FW_WKUP_RTI0_CFG_NUM_REGIONS                                                       (24U)
#define CSL_STD_FW_WKUP_RTI0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_RTI0_CFG_CFG_START                                                         (0x0000002b000000U)
#define CSL_STD_FW_WKUP_RTI0_CFG_CFG_END                                                           (0x0000002b0000ffU)

/* Properties of firewall at slave: WKUP_RTCSS0_RTC_REGS */
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_ID                                                         (34U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_MMR_BASE                                                   (0x00000045008800U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_NUM_REGIONS                                                (24U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_RTC_START                                                  (0x0000002b1f0000U)
#define CSL_STD_FW_WKUP_RTCSS0_RTC_REGS_RTC_END                                                    (0x0000002b1f007fU)

/* Properties of firewall at slave: WKUP_I2C0_CFG */
#define CSL_STD_FW_WKUP_I2C0_CFG_ID                                                                (34U)
#define CSL_STD_FW_WKUP_I2C0_CFG_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_I2C0_CFG_MMR_BASE                                                          (0x00000045008800U)
#define CSL_STD_FW_WKUP_I2C0_CFG_NUM_REGIONS                                                       (24U)
#define CSL_STD_FW_WKUP_I2C0_CFG_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_WKUP_I2C0_CFG_CFG_START                                                         (0x0000002b200000U)
#define CSL_STD_FW_WKUP_I2C0_CFG_CFG_END                                                           (0x0000002b2000ffU)

/* Properties of firewall at slave: WKUP_UART0_MEM */
#define CSL_STD_FW_WKUP_UART0_MEM_ID                                                               (34U)
#define CSL_STD_FW_WKUP_UART0_MEM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_UART0_MEM_MMR_BASE                                                         (0x00000045008800U)
#define CSL_STD_FW_WKUP_UART0_MEM_NUM_REGIONS                                                      (24U)
#define CSL_STD_FW_WKUP_UART0_MEM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_WKUP_UART0_MEM_START                                                            (0x0000002b300000U)
#define CSL_STD_FW_WKUP_UART0_MEM_END                                                              (0x0000002b3001ffU)

/* Properties of firewall at slave: WKUP_CBASS0_ERR_REGS */
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_ID                                                         (34U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_MMR_BASE                                                   (0x00000045008800U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_NUM_REGIONS                                                (24U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_ERR_START                                                  (0x0000002b400000U)
#define CSL_STD_FW_WKUP_CBASS0_ERR_REGS_ERR_END                                                    (0x0000002b4003ffU)

/* Properties of firewall at slave: WKUP_PBIST0_MEM */
#define CSL_STD_FW_WKUP_PBIST0_MEM_ID                                                              (34U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PBIST0_MEM_MMR_BASE                                                        (0x00000045008800U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_NUM_REGIONS                                                     (24U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_START                                                           (0x0000002b500000U)
#define CSL_STD_FW_WKUP_PBIST0_MEM_END                                                             (0x0000002b5003ffU)

/* Properties of firewall at slave: WKUP_PBIST1_MEM */
#define CSL_STD_FW_WKUP_PBIST1_MEM_ID                                                              (34U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PBIST1_MEM_MMR_BASE                                                        (0x00000045008800U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_NUM_REGIONS                                                     (24U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_START                                                           (0x0000002b501000U)
#define CSL_STD_FW_WKUP_PBIST1_MEM_END                                                             (0x0000002b5013ffU)

/* Properties of firewall at slave: WKUP_ECC_AGGR0_REGS */
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_ID                                                          (34U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_MMR_BASE                                                    (0x00000045008800U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_NUM_REGIONS                                                 (24U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_ECC_AGGR_START                                              (0x0000002b600000U)
#define CSL_STD_FW_WKUP_ECC_AGGR0_REGS_ECC_AGGR_END                                                (0x0000002b6003ffU)

/* Properties of firewall at slave: WKUP_ECC_AGGR1_REGS */
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_ID                                                          (34U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_MMR_BASE                                                    (0x00000045008800U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_NUM_REGIONS                                                 (24U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_ECC_AGGR_START                                              (0x0000002b601000U)
#define CSL_STD_FW_WKUP_ECC_AGGR1_REGS_ECC_AGGR_END                                                (0x0000002b6013ffU)

/* Properties of firewall at slave: WKUP_PSRAMECC_8K0_REGS */
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_ID                                                       (34U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_MMR_BASE                                                 (0x00000045008800U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_NUM_REGIONS                                              (24U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_REGS_START                                               (0x0000002b608000U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_REGS_REGS_END                                                 (0x0000002b6083ffU)

/* Properties of firewall at slave: WKUP_PSRAM2KX32E0_REGS */
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_REGS_ID                                                       (34U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_REGS_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_REGS_MMR_BASE                                                 (0x00000045008800U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_REGS_NUM_REGIONS                                              (24U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_REGS_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_REGS_REGS_START                                               (0x0000002b609000U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_REGS_REGS_END                                                 (0x0000002b6093ffU)

/* Properties of firewall at slave: WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS */
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_ID                                      (34U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_MMR_BASE                                (0x00000045008800U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_REGIONS                             (24U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_START               (0x0000003c018000U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_EVNT_BUS_VBUSP_MMRS_EVNT_BUS_VBUSP_MMRS_END                 (0x0000003c0180ffU)

/* Properties of firewall at slave: WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS */
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_ID                                   (34U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_TYPE                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_MMR_BASE                             (0x00000045008800U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_NUM_REGIONS                          (24U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_NUM_PRIV_IDS_PER_REGION              (3U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_START                 (0x0000003f00d000U)
#define CSL_STD_FW_WKUP_R5FSS0_COMMON0_CPU0_ECC_AGGR_CFG_REGS_CORE0_ECC_AGGR_END                   (0x0000003f00d3ffU)

/* Properties of firewall at slave: WKUP_PSRAMECC_8K0_RAM */
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_ID                                                        (34U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_MMR_BASE                                                  (0x00000045008800U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_NUM_REGIONS                                               (24U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_RAM_START                                                 (0x00000041880000U)
#define CSL_STD_FW_WKUP_PSRAMECC_8K0_RAM_RAM_END                                                   (0x00000041887fffU)

/* Properties of firewall at slave: WKUP_PSRAM2KX32E0_RAM */
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_RAM_ID                                                        (34U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_RAM_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_RAM_MMR_BASE                                                  (0x00000045008800U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_RAM_NUM_REGIONS                                               (24U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_RAM_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_RAM_RAM_START                                                 (0x00000041888000U)
#define CSL_STD_FW_WKUP_PSRAM2KX32E0_RAM_RAM_END                                                   (0x00000041889fffU)

/* Properties of firewall at slave: WKUP_CTRL_MMR0_CFG0 */
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_ID                                                          (34U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_MMR_BASE                                                    (0x00000045008800U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_NUM_REGIONS                                                 (24U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_CFG0_START                                                  (0x00000043000000U)
#define CSL_STD_FW_WKUP_CTRL_MMR0_CFG0_CFG0_END                                                    (0x0000004301ffffU)

/* Properties of firewall at slave: WKUP_TIMER0_CFG */
#define CSL_STD_FW_WKUP_TIMER0_CFG_ID                                                              (40U)
#define CSL_STD_FW_WKUP_TIMER0_CFG_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_TIMER0_CFG_MMR_BASE                                                        (0x0000004500a000U)
#define CSL_STD_FW_WKUP_TIMER0_CFG_NUM_REGIONS                                                     (1U)
#define CSL_STD_FW_WKUP_TIMER0_CFG_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_WKUP_TIMER0_CFG_CFG_START                                                       (0x0000002b100000U)
#define CSL_STD_FW_WKUP_TIMER0_CFG_CFG_END                                                         (0x0000002b1003ffU)

/* Properties of firewall at slave: WKUP_TIMER1_CFG */
#define CSL_STD_FW_WKUP_TIMER1_CFG_ID                                                              (41U)
#define CSL_STD_FW_WKUP_TIMER1_CFG_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_WKUP_TIMER1_CFG_MMR_BASE                                                        (0x0000004500a400U)
#define CSL_STD_FW_WKUP_TIMER1_CFG_NUM_REGIONS                                                     (1U)
#define CSL_STD_FW_WKUP_TIMER1_CFG_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_WKUP_TIMER1_CFG_CFG_START                                                       (0x0000002b110000U)
#define CSL_STD_FW_WKUP_TIMER1_CFG_CFG_END                                                         (0x0000002b1103ffU)

/* Properties of firewall at slave: CBASS_FW0_ERR_REGS */
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_ID                                                           (66U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_TYPE                                                         (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_MMR_BASE                                                     (0x00000045010800U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_NUM_REGIONS                                                  (4U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                      (3U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_ERR_START                                                    (0x00000000220000U)
#define CSL_STD_FW_CBASS_FW0_ERR_REGS_ERR_END                                                      (0x000000002203ffU)

/* Properties of firewall at slave: AM275_MAIN_IPCSS_CBASS0_ERR_REGS */
#define CSL_STD_FW_AM275_MAIN_IPCSS_CBASS0_ERR_REGS_ID                                             (66U)
#define CSL_STD_FW_AM275_MAIN_IPCSS_CBASS0_ERR_REGS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_AM275_MAIN_IPCSS_CBASS0_ERR_REGS_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_AM275_MAIN_IPCSS_CBASS0_ERR_REGS_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_AM275_MAIN_IPCSS_CBASS0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_AM275_MAIN_IPCSS_CBASS0_ERR_REGS_ERR_START                                      (0x00000000230000U)
#define CSL_STD_FW_AM275_MAIN_IPCSS_CBASS0_ERR_REGS_ERR_END                                        (0x000000002303ffU)

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

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_4_REGS4 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_4_REGS4_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_4_REGS4_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_4_REGS4_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_4_REGS4_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_4_REGS4_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_4_REGS4_REGS4_START                                    (0x00000029040000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_4_REGS4_REGS4_END                                      (0x000000290401ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_5_REGS5 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_5_REGS5_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_5_REGS5_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_5_REGS5_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_5_REGS5_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_5_REGS5_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_5_REGS5_REGS5_START                                    (0x00000029050000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_5_REGS5_REGS5_END                                      (0x000000290501ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_6_REGS6 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_6_REGS6_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_6_REGS6_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_6_REGS6_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_6_REGS6_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_6_REGS6_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_6_REGS6_REGS6_START                                    (0x00000029060000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_6_REGS6_REGS6_END                                      (0x000000290601ffU)

/* Properties of firewall at slave: MAILBOX0_MAILBOX_CLUSTER_7_REGS7 */
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_7_REGS7_ID                                             (66U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_7_REGS7_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_7_REGS7_MMR_BASE                                       (0x00000045010800U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_7_REGS7_NUM_REGIONS                                    (4U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_7_REGS7_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_7_REGS7_REGS7_START                                    (0x00000029070000U)
#define CSL_STD_FW_MAILBOX0_MAILBOX_CLUSTER_7_REGS7_REGS7_END                                      (0x000000290701ffU)

/* Properties of firewall at slave: SPINLOCK0_REGS */
#define CSL_STD_FW_SPINLOCK0_REGS_ID                                                               (66U)
#define CSL_STD_FW_SPINLOCK0_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_SPINLOCK0_REGS_MMR_BASE                                                         (0x00000045010800U)
#define CSL_STD_FW_SPINLOCK0_REGS_NUM_REGIONS                                                      (4U)
#define CSL_STD_FW_SPINLOCK0_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_SPINLOCK0_REGS_START                                                            (0x0000002a000000U)
#define CSL_STD_FW_SPINLOCK0_REGS_END                                                              (0x0000002a007fffU)

/* Properties of firewall at slave: ECC_AGGR0_REGS */
#define CSL_STD_FW_ECC_AGGR0_REGS_ID                                                               (66U)
#define CSL_STD_FW_ECC_AGGR0_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_ECC_AGGR0_REGS_MMR_BASE                                                         (0x00000045010800U)
#define CSL_STD_FW_ECC_AGGR0_REGS_NUM_REGIONS                                                      (4U)
#define CSL_STD_FW_ECC_AGGR0_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_ECC_AGGR0_REGS_REGS_START                                                       (0x0000003f00f000U)
#define CSL_STD_FW_ECC_AGGR0_REGS_REGS_END                                                         (0x0000003f00f3ffU)

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

/* Properties of firewall at slave: ADC12FCC0_ECCREGS */
#define CSL_STD_FW_ADC12FCC0_ECCREGS_ID                                                            (192U)
#define CSL_STD_FW_ADC12FCC0_ECCREGS_TYPE                                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_ADC12FCC0_ECCREGS_MMR_BASE                                                      (0x00000045030000U)
#define CSL_STD_FW_ADC12FCC0_ECCREGS_NUM_REGIONS                                                   (1U)
#define CSL_STD_FW_ADC12FCC0_ECCREGS_NUM_PRIV_IDS_PER_REGION                                       (3U)
#define CSL_STD_FW_ADC12FCC0_ECCREGS_ECC_START                                                     (0x00000000729000U)
#define CSL_STD_FW_ADC12FCC0_ECCREGS_ECC_END                                                       (0x000000007293ffU)

/* Properties of firewall at slave: ADC12FCC0_ADCREGS */
#define CSL_STD_FW_ADC12FCC0_ADCREGS_ID                                                            (192U)
#define CSL_STD_FW_ADC12FCC0_ADCREGS_TYPE                                                          (CSL_FW_SECURITY)
#define CSL_STD_FW_ADC12FCC0_ADCREGS_MMR_BASE                                                      (0x00000045030000U)
#define CSL_STD_FW_ADC12FCC0_ADCREGS_NUM_REGIONS                                                   (1U)
#define CSL_STD_FW_ADC12FCC0_ADCREGS_NUM_PRIV_IDS_PER_REGION                                       (3U)
#define CSL_STD_FW_ADC12FCC0_ADCREGS_ADC_START                                                     (0x00000020600000U)
#define CSL_STD_FW_ADC12FCC0_ADCREGS_ADC_END                                                       (0x000000206003ffU)

/* Properties of firewall at slave: ADC12FCC0_ADC12_FIFO_DMA */
#define CSL_STD_FW_ADC12FCC0_ADC12_FIFO_DMA_ID                                                     (193U)
#define CSL_STD_FW_ADC12FCC0_ADC12_FIFO_DMA_TYPE                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_ADC12FCC0_ADC12_FIFO_DMA_MMR_BASE                                               (0x00000045030400U)
#define CSL_STD_FW_ADC12FCC0_ADC12_FIFO_DMA_NUM_REGIONS                                            (1U)
#define CSL_STD_FW_ADC12FCC0_ADC12_FIFO_DMA_NUM_PRIV_IDS_PER_REGION                                (3U)
#define CSL_STD_FW_ADC12FCC0_ADC12_FIFO_DMA_ADC12_FIFO_DMA_START                                   (0x00000020608000U)
#define CSL_STD_FW_ADC12FCC0_ADC12_FIFO_DMA_ADC12_FIFO_DMA_END                                     (0x000000206083ffU)

/* Properties of firewall at slave: CBASS_MEM0_ERR_REGS */
#define CSL_STD_FW_CBASS_MEM0_ERR_REGS_ID                                                          (194U)
#define CSL_STD_FW_CBASS_MEM0_ERR_REGS_TYPE                                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_MEM0_ERR_REGS_MMR_BASE                                                    (0x00000045030800U)
#define CSL_STD_FW_CBASS_MEM0_ERR_REGS_NUM_REGIONS                                                 (1U)
#define CSL_STD_FW_CBASS_MEM0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                     (3U)
#define CSL_STD_FW_CBASS_MEM0_ERR_REGS_ERR_START                                                   (0x00000020200000U)
#define CSL_STD_FW_CBASS_MEM0_ERR_REGS_ERR_END                                                     (0x000000202003ffU)

/* Properties of firewall at slave: ECAP0_CTL_STS */
#define CSL_STD_FW_ECAP0_CTL_STS_ID                                                                (195U)
#define CSL_STD_FW_ECAP0_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP0_CTL_STS_MMR_BASE                                                          (0x00000045030c00U)
#define CSL_STD_FW_ECAP0_CTL_STS_NUM_REGIONS                                                       (1U)
#define CSL_STD_FW_ECAP0_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP0_CTL_STS_CTL_STS_START                                                     (0x00000023100000U)
#define CSL_STD_FW_ECAP0_CTL_STS_CTL_STS_END                                                       (0x000000231000ffU)

/* Properties of firewall at slave: ECAP1_CTL_STS */
#define CSL_STD_FW_ECAP1_CTL_STS_ID                                                                (196U)
#define CSL_STD_FW_ECAP1_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP1_CTL_STS_MMR_BASE                                                          (0x00000045031000U)
#define CSL_STD_FW_ECAP1_CTL_STS_NUM_REGIONS                                                       (1U)
#define CSL_STD_FW_ECAP1_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP1_CTL_STS_CTL_STS_START                                                     (0x00000023110000U)
#define CSL_STD_FW_ECAP1_CTL_STS_CTL_STS_END                                                       (0x000000231100ffU)

/* Properties of firewall at slave: ECAP2_CTL_STS */
#define CSL_STD_FW_ECAP2_CTL_STS_ID                                                                (197U)
#define CSL_STD_FW_ECAP2_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP2_CTL_STS_MMR_BASE                                                          (0x00000045031400U)
#define CSL_STD_FW_ECAP2_CTL_STS_NUM_REGIONS                                                       (1U)
#define CSL_STD_FW_ECAP2_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP2_CTL_STS_CTL_STS_START                                                     (0x00000023120000U)
#define CSL_STD_FW_ECAP2_CTL_STS_CTL_STS_END                                                       (0x000000231200ffU)

/* Properties of firewall at slave: ECAP3_CTL_STS */
#define CSL_STD_FW_ECAP3_CTL_STS_ID                                                                (198U)
#define CSL_STD_FW_ECAP3_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP3_CTL_STS_MMR_BASE                                                          (0x00000045031800U)
#define CSL_STD_FW_ECAP3_CTL_STS_NUM_REGIONS                                                       (1U)
#define CSL_STD_FW_ECAP3_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP3_CTL_STS_CTL_STS_START                                                     (0x00000023130000U)
#define CSL_STD_FW_ECAP3_CTL_STS_CTL_STS_END                                                       (0x000000231300ffU)

/* Properties of firewall at slave: ECAP4_CTL_STS */
#define CSL_STD_FW_ECAP4_CTL_STS_ID                                                                (199U)
#define CSL_STD_FW_ECAP4_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP4_CTL_STS_MMR_BASE                                                          (0x00000045031c00U)
#define CSL_STD_FW_ECAP4_CTL_STS_NUM_REGIONS                                                       (1U)
#define CSL_STD_FW_ECAP4_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP4_CTL_STS_CTL_STS_START                                                     (0x00000023140000U)
#define CSL_STD_FW_ECAP4_CTL_STS_CTL_STS_END                                                       (0x000000231400ffU)

/* Properties of firewall at slave: ECAP5_CTL_STS */
#define CSL_STD_FW_ECAP5_CTL_STS_ID                                                                (200U)
#define CSL_STD_FW_ECAP5_CTL_STS_TYPE                                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_ECAP5_CTL_STS_MMR_BASE                                                          (0x00000045032000U)
#define CSL_STD_FW_ECAP5_CTL_STS_NUM_REGIONS                                                       (1U)
#define CSL_STD_FW_ECAP5_CTL_STS_NUM_PRIV_IDS_PER_REGION                                           (3U)
#define CSL_STD_FW_ECAP5_CTL_STS_CTL_STS_START                                                     (0x00000023150000U)
#define CSL_STD_FW_ECAP5_CTL_STS_CTL_STS_END                                                       (0x000000231500ffU)

/* Properties of firewall at slave: EPWM0_EPWM_REGS */
#define CSL_STD_FW_EPWM0_EPWM_REGS_ID                                                              (201U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_EPWM0_EPWM_REGS_MMR_BASE                                                        (0x00000045032400U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_NUM_REGIONS                                                     (1U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_EPWM_START                                                      (0x00000023000000U)
#define CSL_STD_FW_EPWM0_EPWM_REGS_EPWM_END                                                        (0x000000230000ffU)

/* Properties of firewall at slave: EPWM1_EPWM_REGS */
#define CSL_STD_FW_EPWM1_EPWM_REGS_ID                                                              (202U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_EPWM1_EPWM_REGS_MMR_BASE                                                        (0x00000045032800U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_NUM_REGIONS                                                     (1U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_EPWM_START                                                      (0x00000023010000U)
#define CSL_STD_FW_EPWM1_EPWM_REGS_EPWM_END                                                        (0x000000230100ffU)

/* Properties of firewall at slave: EPWM2_EPWM_REGS */
#define CSL_STD_FW_EPWM2_EPWM_REGS_ID                                                              (203U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_TYPE                                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_EPWM2_EPWM_REGS_MMR_BASE                                                        (0x00000045032c00U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_NUM_REGIONS                                                     (1U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_NUM_PRIV_IDS_PER_REGION                                         (3U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_EPWM_START                                                      (0x00000023020000U)
#define CSL_STD_FW_EPWM2_EPWM_REGS_EPWM_END                                                        (0x000000230200ffU)

/* Properties of firewall at slave: I2C0_CFG */
#define CSL_STD_FW_I2C0_CFG_ID                                                                     (204U)
#define CSL_STD_FW_I2C0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C0_CFG_MMR_BASE                                                               (0x00000045033000U)
#define CSL_STD_FW_I2C0_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_I2C0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C0_CFG_CFG_START                                                              (0x00000020000000U)
#define CSL_STD_FW_I2C0_CFG_CFG_END                                                                (0x000000200000ffU)

/* Properties of firewall at slave: I2C1_CFG */
#define CSL_STD_FW_I2C1_CFG_ID                                                                     (205U)
#define CSL_STD_FW_I2C1_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C1_CFG_MMR_BASE                                                               (0x00000045033400U)
#define CSL_STD_FW_I2C1_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_I2C1_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C1_CFG_CFG_START                                                              (0x00000020010000U)
#define CSL_STD_FW_I2C1_CFG_CFG_END                                                                (0x000000200100ffU)

/* Properties of firewall at slave: I2C2_CFG */
#define CSL_STD_FW_I2C2_CFG_ID                                                                     (206U)
#define CSL_STD_FW_I2C2_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C2_CFG_MMR_BASE                                                               (0x00000045033800U)
#define CSL_STD_FW_I2C2_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_I2C2_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C2_CFG_CFG_START                                                              (0x00000020020000U)
#define CSL_STD_FW_I2C2_CFG_CFG_END                                                                (0x000000200200ffU)

/* Properties of firewall at slave: I2C3_CFG */
#define CSL_STD_FW_I2C3_CFG_ID                                                                     (207U)
#define CSL_STD_FW_I2C3_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C3_CFG_MMR_BASE                                                               (0x00000045033c00U)
#define CSL_STD_FW_I2C3_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_I2C3_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C3_CFG_CFG_START                                                              (0x00000020030000U)
#define CSL_STD_FW_I2C3_CFG_CFG_END                                                                (0x000000200300ffU)

/* Properties of firewall at slave: I2C4_CFG */
#define CSL_STD_FW_I2C4_CFG_ID                                                                     (208U)
#define CSL_STD_FW_I2C4_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C4_CFG_MMR_BASE                                                               (0x00000045034000U)
#define CSL_STD_FW_I2C4_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_I2C4_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C4_CFG_CFG_START                                                              (0x00000020040000U)
#define CSL_STD_FW_I2C4_CFG_CFG_END                                                                (0x000000200400ffU)

/* Properties of firewall at slave: I2C5_CFG */
#define CSL_STD_FW_I2C5_CFG_ID                                                                     (209U)
#define CSL_STD_FW_I2C5_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C5_CFG_MMR_BASE                                                               (0x00000045034400U)
#define CSL_STD_FW_I2C5_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_I2C5_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C5_CFG_CFG_START                                                              (0x00000020050000U)
#define CSL_STD_FW_I2C5_CFG_CFG_END                                                                (0x000000200500ffU)

/* Properties of firewall at slave: I2C6_CFG */
#define CSL_STD_FW_I2C6_CFG_ID                                                                     (210U)
#define CSL_STD_FW_I2C6_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_I2C6_CFG_MMR_BASE                                                               (0x00000045034800U)
#define CSL_STD_FW_I2C6_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_I2C6_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_I2C6_CFG_CFG_START                                                              (0x00000020060000U)
#define CSL_STD_FW_I2C6_CFG_CFG_END                                                                (0x000000200600ffU)

/* Properties of firewall at slave: MCAN0_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_ID                                                 (211U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                           (0x00000045034c00U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_START                                           (0x00000020700000U)
#define CSL_STD_FW_MCAN0_MMR_MMRVBP_MCANSS_REGS_SS_END                                             (0x000000207000ffU)

/* Properties of firewall at slave: MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                       (211U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                                 (0x00000045034c00U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                              (1U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                                (0x00000020701000U)
#define CSL_STD_FW_MCAN0_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                                  (0x000000207011ffU)

/* Properties of firewall at slave: MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                             (211U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                       (0x00000045034c00U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                    (1U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                               (0x00000020708000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                                 (0x0000002070ffffU)

/* Properties of firewall at slave: MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                          (211U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                    (0x00000045034c00U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                                 (1U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                              (0x00000024018000U)
#define CSL_STD_FW_MCAN0_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                                (0x000000240183ffU)

/* Properties of firewall at slave: MCAN1_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCAN1_MMR_MMRVBP_MCANSS_REGS_ID                                                 (212U)
#define CSL_STD_FW_MCAN1_MMR_MMRVBP_MCANSS_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN1_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                           (0x00000045035000U)
#define CSL_STD_FW_MCAN1_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_MCAN1_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MCAN1_MMR_MMRVBP_MCANSS_REGS_SS_START                                           (0x00000020710000U)
#define CSL_STD_FW_MCAN1_MMR_MMRVBP_MCANSS_REGS_SS_END                                             (0x000000207100ffU)

/* Properties of firewall at slave: MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                       (212U)
#define CSL_STD_FW_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                                 (0x00000045035000U)
#define CSL_STD_FW_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                              (1U)
#define CSL_STD_FW_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                                (0x00000020711000U)
#define CSL_STD_FW_MCAN1_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                                  (0x000000207111ffU)

/* Properties of firewall at slave: MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                             (212U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                       (0x00000045035000U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                    (1U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                               (0x00000020718000U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                                 (0x0000002071ffffU)

/* Properties of firewall at slave: MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                          (212U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                    (0x00000045035000U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                                 (1U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                              (0x00000024019000U)
#define CSL_STD_FW_MCAN1_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                                (0x000000240193ffU)

/* Properties of firewall at slave: MCAN2_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCAN2_MMR_MMRVBP_MCANSS_REGS_ID                                                 (213U)
#define CSL_STD_FW_MCAN2_MMR_MMRVBP_MCANSS_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN2_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                           (0x00000045035400U)
#define CSL_STD_FW_MCAN2_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_MCAN2_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MCAN2_MMR_MMRVBP_MCANSS_REGS_SS_START                                           (0x00000020720000U)
#define CSL_STD_FW_MCAN2_MMR_MMRVBP_MCANSS_REGS_SS_END                                             (0x000000207200ffU)

/* Properties of firewall at slave: MCAN2_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCAN2_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                       (213U)
#define CSL_STD_FW_MCAN2_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN2_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                                 (0x00000045035400U)
#define CSL_STD_FW_MCAN2_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                              (1U)
#define CSL_STD_FW_MCAN2_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_MCAN2_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                                (0x00000020721000U)
#define CSL_STD_FW_MCAN2_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                                  (0x000000207211ffU)

/* Properties of firewall at slave: MCAN2_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                             (213U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                       (0x00000045035400U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                    (1U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                               (0x00000020728000U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                                 (0x0000002072ffffU)

/* Properties of firewall at slave: MCAN2_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                          (213U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                    (0x00000045035400U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                                 (1U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                              (0x0000002401a000U)
#define CSL_STD_FW_MCAN2_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                                (0x0000002401a3ffU)

/* Properties of firewall at slave: MCAN3_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCAN3_MMR_MMRVBP_MCANSS_REGS_ID                                                 (214U)
#define CSL_STD_FW_MCAN3_MMR_MMRVBP_MCANSS_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN3_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                           (0x00000045035800U)
#define CSL_STD_FW_MCAN3_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_MCAN3_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MCAN3_MMR_MMRVBP_MCANSS_REGS_SS_START                                           (0x00000020730000U)
#define CSL_STD_FW_MCAN3_MMR_MMRVBP_MCANSS_REGS_SS_END                                             (0x000000207300ffU)

/* Properties of firewall at slave: MCAN3_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCAN3_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                       (214U)
#define CSL_STD_FW_MCAN3_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN3_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                                 (0x00000045035800U)
#define CSL_STD_FW_MCAN3_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                              (1U)
#define CSL_STD_FW_MCAN3_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_MCAN3_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                                (0x00000020731000U)
#define CSL_STD_FW_MCAN3_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                                  (0x000000207311ffU)

/* Properties of firewall at slave: MCAN3_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                             (214U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                       (0x00000045035800U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                    (1U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                               (0x00000020738000U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                                 (0x0000002073ffffU)

/* Properties of firewall at slave: MCAN3_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                          (214U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                    (0x00000045035800U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                                 (1U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                              (0x0000002401b000U)
#define CSL_STD_FW_MCAN3_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                                (0x0000002401b3ffU)

/* Properties of firewall at slave: MCAN4_MMR_MMRVBP_MCANSS_REGS */
#define CSL_STD_FW_MCAN4_MMR_MMRVBP_MCANSS_REGS_ID                                                 (215U)
#define CSL_STD_FW_MCAN4_MMR_MMRVBP_MCANSS_REGS_TYPE                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN4_MMR_MMRVBP_MCANSS_REGS_MMR_BASE                                           (0x00000045035c00U)
#define CSL_STD_FW_MCAN4_MMR_MMRVBP_MCANSS_REGS_NUM_REGIONS                                        (1U)
#define CSL_STD_FW_MCAN4_MMR_MMRVBP_MCANSS_REGS_NUM_PRIV_IDS_PER_REGION                            (3U)
#define CSL_STD_FW_MCAN4_MMR_MMRVBP_MCANSS_REGS_SS_START                                           (0x00000020740000U)
#define CSL_STD_FW_MCAN4_MMR_MMRVBP_MCANSS_REGS_SS_END                                             (0x000000207400ffU)

/* Properties of firewall at slave: MCAN4_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS */
#define CSL_STD_FW_MCAN4_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_ID                                       (215U)
#define CSL_STD_FW_MCAN4_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN4_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_MMR_BASE                                 (0x00000045035c00U)
#define CSL_STD_FW_MCAN4_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_REGIONS                              (1U)
#define CSL_STD_FW_MCAN4_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_MCAN4_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_START                                (0x00000020741000U)
#define CSL_STD_FW_MCAN4_MCAN_WRAP_MCAN_CFG_VBP_MCAN_REGS_CFG_END                                  (0x000000207411ffU)

/* Properties of firewall at slave: MCAN4_MSGMEM_WRAP_MSGMEM_VBP_RAM */
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_MSGMEM_VBP_RAM_ID                                             (215U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_MSGMEM_VBP_RAM_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_MSGMEM_VBP_RAM_MMR_BASE                                       (0x00000045035c00U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_REGIONS                                    (1U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_MSGMEM_VBP_RAM_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_START                               (0x00000020748000U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_MSGMEM_VBP_RAM_MSGMEM_RAM_END                                 (0x0000002074ffffU)

/* Properties of firewall at slave: MCAN4_MSGMEM_WRAP_ECC_AGGR_VBP_REGS */
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ID                                          (215U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_MMR_BASE                                    (0x00000045035c00U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_REGIONS                                 (1U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_START                              (0x0000002401c000U)
#define CSL_STD_FW_MCAN4_MSGMEM_WRAP_ECC_AGGR_VBP_REGS_ECC_AGGR_END                                (0x0000002401c3ffU)

/* Properties of firewall at slave: PDMA0_REGS */
#define CSL_STD_FW_PDMA0_REGS_ID                                                                   (216U)
#define CSL_STD_FW_PDMA0_REGS_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PDMA0_REGS_MMR_BASE                                                             (0x00000045036000U)
#define CSL_STD_FW_PDMA0_REGS_NUM_REGIONS                                                          (1U)
#define CSL_STD_FW_PDMA0_REGS_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PDMA0_REGS_START                                                                (0x00000000c00000U)
#define CSL_STD_FW_PDMA0_REGS_END                                                                  (0x00000000c003ffU)

/* Properties of firewall at slave: PDMA4_REGS */
#define CSL_STD_FW_PDMA4_REGS_ID                                                                   (217U)
#define CSL_STD_FW_PDMA4_REGS_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PDMA4_REGS_MMR_BASE                                                             (0x00000045036400U)
#define CSL_STD_FW_PDMA4_REGS_NUM_REGIONS                                                          (1U)
#define CSL_STD_FW_PDMA4_REGS_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PDMA4_REGS_REGS_START                                                           (0x00000000c02000U)
#define CSL_STD_FW_PDMA4_REGS_REGS_END                                                             (0x00000000c023ffU)

/* Properties of firewall at slave: PDMA1_REGS */
#define CSL_STD_FW_PDMA1_REGS_ID                                                                   (218U)
#define CSL_STD_FW_PDMA1_REGS_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_PDMA1_REGS_MMR_BASE                                                             (0x00000045036800U)
#define CSL_STD_FW_PDMA1_REGS_NUM_REGIONS                                                          (1U)
#define CSL_STD_FW_PDMA1_REGS_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_PDMA1_REGS_START                                                                (0x00000000c01000U)
#define CSL_STD_FW_PDMA1_REGS_END                                                                  (0x00000000c013ffU)

/* Properties of firewall at slave: RL2_OF_CBA4_0_RL2_OF_CBA4 */
#define CSL_STD_FW_RL2_OF_CBA4_0_RL2_OF_CBA4_ID                                                    (219U)
#define CSL_STD_FW_RL2_OF_CBA4_0_RL2_OF_CBA4_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_RL2_OF_CBA4_0_RL2_OF_CBA4_MMR_BASE                                              (0x00000045036c00U)
#define CSL_STD_FW_RL2_OF_CBA4_0_RL2_OF_CBA4_NUM_REGIONS                                           (1U)
#define CSL_STD_FW_RL2_OF_CBA4_0_RL2_OF_CBA4_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_RL2_OF_CBA4_0_RL2_OF_CBA4_RL2_OF_CBA4_START                                     (0x00000025000000U)
#define CSL_STD_FW_RL2_OF_CBA4_0_RL2_OF_CBA4_RL2_OF_CBA4_END                                       (0x000000250003ffU)

/* Properties of firewall at slave: RL2_OF_CBA4_1_RL2_OF_CBA4 */
#define CSL_STD_FW_RL2_OF_CBA4_1_RL2_OF_CBA4_ID                                                    (220U)
#define CSL_STD_FW_RL2_OF_CBA4_1_RL2_OF_CBA4_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_RL2_OF_CBA4_1_RL2_OF_CBA4_MMR_BASE                                              (0x00000045037000U)
#define CSL_STD_FW_RL2_OF_CBA4_1_RL2_OF_CBA4_NUM_REGIONS                                           (1U)
#define CSL_STD_FW_RL2_OF_CBA4_1_RL2_OF_CBA4_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_RL2_OF_CBA4_1_RL2_OF_CBA4_RL2_OF_CBA4_START                                     (0x00000025001000U)
#define CSL_STD_FW_RL2_OF_CBA4_1_RL2_OF_CBA4_RL2_OF_CBA4_END                                       (0x000000250013ffU)

/* Properties of firewall at slave: RL2_OF_CBA4_2_RL2_OF_CBA4 */
#define CSL_STD_FW_RL2_OF_CBA4_2_RL2_OF_CBA4_ID                                                    (221U)
#define CSL_STD_FW_RL2_OF_CBA4_2_RL2_OF_CBA4_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_RL2_OF_CBA4_2_RL2_OF_CBA4_MMR_BASE                                              (0x00000045037400U)
#define CSL_STD_FW_RL2_OF_CBA4_2_RL2_OF_CBA4_NUM_REGIONS                                           (1U)
#define CSL_STD_FW_RL2_OF_CBA4_2_RL2_OF_CBA4_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_RL2_OF_CBA4_2_RL2_OF_CBA4_RL2_OF_CBA4_START                                     (0x00000025002000U)
#define CSL_STD_FW_RL2_OF_CBA4_2_RL2_OF_CBA4_RL2_OF_CBA4_END                                       (0x000000250023ffU)

/* Properties of firewall at slave: RL2_OF_CBA4_3_RL2_OF_CBA4 */
#define CSL_STD_FW_RL2_OF_CBA4_3_RL2_OF_CBA4_ID                                                    (222U)
#define CSL_STD_FW_RL2_OF_CBA4_3_RL2_OF_CBA4_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_RL2_OF_CBA4_3_RL2_OF_CBA4_MMR_BASE                                              (0x00000045037800U)
#define CSL_STD_FW_RL2_OF_CBA4_3_RL2_OF_CBA4_NUM_REGIONS                                           (1U)
#define CSL_STD_FW_RL2_OF_CBA4_3_RL2_OF_CBA4_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_RL2_OF_CBA4_3_RL2_OF_CBA4_RL2_OF_CBA4_START                                     (0x00000025003000U)
#define CSL_STD_FW_RL2_OF_CBA4_3_RL2_OF_CBA4_RL2_OF_CBA4_END                                       (0x000000250033ffU)

/* Properties of firewall at slave: RTI0_CFG */
#define CSL_STD_FW_RTI0_CFG_ID                                                                     (223U)
#define CSL_STD_FW_RTI0_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI0_CFG_MMR_BASE                                                               (0x00000045037c00U)
#define CSL_STD_FW_RTI0_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_RTI0_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI0_CFG_CFG_START                                                              (0x00000020800000U)
#define CSL_STD_FW_RTI0_CFG_CFG_END                                                                (0x000000208000ffU)

/* Properties of firewall at slave: RTI1_CFG */
#define CSL_STD_FW_RTI1_CFG_ID                                                                     (224U)
#define CSL_STD_FW_RTI1_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI1_CFG_MMR_BASE                                                               (0x00000045038000U)
#define CSL_STD_FW_RTI1_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_RTI1_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI1_CFG_CFG_START                                                              (0x00000020810000U)
#define CSL_STD_FW_RTI1_CFG_CFG_END                                                                (0x000000208100ffU)

/* Properties of firewall at slave: RTI2_CFG */
#define CSL_STD_FW_RTI2_CFG_ID                                                                     (225U)
#define CSL_STD_FW_RTI2_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI2_CFG_MMR_BASE                                                               (0x00000045038400U)
#define CSL_STD_FW_RTI2_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_RTI2_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI2_CFG_CFG_START                                                              (0x00000020820000U)
#define CSL_STD_FW_RTI2_CFG_CFG_END                                                                (0x000000208200ffU)

/* Properties of firewall at slave: RTI3_CFG */
#define CSL_STD_FW_RTI3_CFG_ID                                                                     (226U)
#define CSL_STD_FW_RTI3_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_RTI3_CFG_MMR_BASE                                                               (0x00000045038800U)
#define CSL_STD_FW_RTI3_CFG_NUM_REGIONS                                                            (1U)
#define CSL_STD_FW_RTI3_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_RTI3_CFG_CFG_START                                                              (0x00000020830000U)
#define CSL_STD_FW_RTI3_CFG_CFG_END                                                                (0x000000208300ffU)

/* Properties of firewall at slave: MCSPI0_CFG */
#define CSL_STD_FW_MCSPI0_CFG_ID                                                                   (227U)
#define CSL_STD_FW_MCSPI0_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI0_CFG_MMR_BASE                                                             (0x00000045038c00U)
#define CSL_STD_FW_MCSPI0_CFG_NUM_REGIONS                                                          (1U)
#define CSL_STD_FW_MCSPI0_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI0_CFG_CFG_START                                                            (0x00000020100000U)
#define CSL_STD_FW_MCSPI0_CFG_CFG_END                                                              (0x000000201003ffU)

/* Properties of firewall at slave: MCSPI1_CFG */
#define CSL_STD_FW_MCSPI1_CFG_ID                                                                   (228U)
#define CSL_STD_FW_MCSPI1_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI1_CFG_MMR_BASE                                                             (0x00000045039000U)
#define CSL_STD_FW_MCSPI1_CFG_NUM_REGIONS                                                          (1U)
#define CSL_STD_FW_MCSPI1_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI1_CFG_CFG_START                                                            (0x00000020110000U)
#define CSL_STD_FW_MCSPI1_CFG_CFG_END                                                              (0x000000201103ffU)

/* Properties of firewall at slave: MCSPI2_CFG */
#define CSL_STD_FW_MCSPI2_CFG_ID                                                                   (229U)
#define CSL_STD_FW_MCSPI2_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI2_CFG_MMR_BASE                                                             (0x00000045039400U)
#define CSL_STD_FW_MCSPI2_CFG_NUM_REGIONS                                                          (1U)
#define CSL_STD_FW_MCSPI2_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI2_CFG_CFG_START                                                            (0x00000020120000U)
#define CSL_STD_FW_MCSPI2_CFG_CFG_END                                                              (0x000000201203ffU)

/* Properties of firewall at slave: MCSPI3_CFG */
#define CSL_STD_FW_MCSPI3_CFG_ID                                                                   (230U)
#define CSL_STD_FW_MCSPI3_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI3_CFG_MMR_BASE                                                             (0x00000045039800U)
#define CSL_STD_FW_MCSPI3_CFG_NUM_REGIONS                                                          (1U)
#define CSL_STD_FW_MCSPI3_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI3_CFG_CFG_START                                                            (0x00000020130000U)
#define CSL_STD_FW_MCSPI3_CFG_CFG_END                                                              (0x000000201303ffU)

/* Properties of firewall at slave: MCSPI4_CFG */
#define CSL_STD_FW_MCSPI4_CFG_ID                                                                   (231U)
#define CSL_STD_FW_MCSPI4_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCSPI4_CFG_MMR_BASE                                                             (0x00000045039c00U)
#define CSL_STD_FW_MCSPI4_CFG_NUM_REGIONS                                                          (1U)
#define CSL_STD_FW_MCSPI4_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCSPI4_CFG_CFG_START                                                            (0x00000020140000U)
#define CSL_STD_FW_MCSPI4_CFG_CFG_END                                                              (0x000000201403ffU)

/* Properties of firewall at slave: UART0_MEM */
#define CSL_STD_FW_UART0_MEM_ID                                                                    (232U)
#define CSL_STD_FW_UART0_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART0_MEM_MMR_BASE                                                              (0x0000004503a000U)
#define CSL_STD_FW_UART0_MEM_NUM_REGIONS                                                           (1U)
#define CSL_STD_FW_UART0_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART0_MEM_START                                                                 (0x00000002800000U)
#define CSL_STD_FW_UART0_MEM_END                                                                   (0x000000028001ffU)

/* Properties of firewall at slave: UART1_MEM */
#define CSL_STD_FW_UART1_MEM_ID                                                                    (233U)
#define CSL_STD_FW_UART1_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART1_MEM_MMR_BASE                                                              (0x0000004503a400U)
#define CSL_STD_FW_UART1_MEM_NUM_REGIONS                                                           (1U)
#define CSL_STD_FW_UART1_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART1_MEM_START                                                                 (0x00000002810000U)
#define CSL_STD_FW_UART1_MEM_END                                                                   (0x000000028101ffU)

/* Properties of firewall at slave: UART2_MEM */
#define CSL_STD_FW_UART2_MEM_ID                                                                    (234U)
#define CSL_STD_FW_UART2_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART2_MEM_MMR_BASE                                                              (0x0000004503a800U)
#define CSL_STD_FW_UART2_MEM_NUM_REGIONS                                                           (1U)
#define CSL_STD_FW_UART2_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART2_MEM_START                                                                 (0x00000002820000U)
#define CSL_STD_FW_UART2_MEM_END                                                                   (0x000000028201ffU)

/* Properties of firewall at slave: UART3_MEM */
#define CSL_STD_FW_UART3_MEM_ID                                                                    (235U)
#define CSL_STD_FW_UART3_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART3_MEM_MMR_BASE                                                              (0x0000004503ac00U)
#define CSL_STD_FW_UART3_MEM_NUM_REGIONS                                                           (1U)
#define CSL_STD_FW_UART3_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART3_MEM_START                                                                 (0x00000002830000U)
#define CSL_STD_FW_UART3_MEM_END                                                                   (0x000000028301ffU)

/* Properties of firewall at slave: UART4_MEM */
#define CSL_STD_FW_UART4_MEM_ID                                                                    (236U)
#define CSL_STD_FW_UART4_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART4_MEM_MMR_BASE                                                              (0x0000004503b000U)
#define CSL_STD_FW_UART4_MEM_NUM_REGIONS                                                           (1U)
#define CSL_STD_FW_UART4_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART4_MEM_START                                                                 (0x00000002840000U)
#define CSL_STD_FW_UART4_MEM_END                                                                   (0x000000028401ffU)

/* Properties of firewall at slave: UART5_MEM */
#define CSL_STD_FW_UART5_MEM_ID                                                                    (237U)
#define CSL_STD_FW_UART5_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART5_MEM_MMR_BASE                                                              (0x0000004503b400U)
#define CSL_STD_FW_UART5_MEM_NUM_REGIONS                                                           (1U)
#define CSL_STD_FW_UART5_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART5_MEM_START                                                                 (0x00000002850000U)
#define CSL_STD_FW_UART5_MEM_END                                                                   (0x000000028501ffU)

/* Properties of firewall at slave: UART6_MEM */
#define CSL_STD_FW_UART6_MEM_ID                                                                    (238U)
#define CSL_STD_FW_UART6_MEM_TYPE                                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_UART6_MEM_MMR_BASE                                                              (0x0000004503b800U)
#define CSL_STD_FW_UART6_MEM_NUM_REGIONS                                                           (1U)
#define CSL_STD_FW_UART6_MEM_NUM_PRIV_IDS_PER_REGION                                               (3U)
#define CSL_STD_FW_UART6_MEM_START                                                                 (0x00000002860000U)
#define CSL_STD_FW_UART6_MEM_END                                                                   (0x000000028601ffU)

/* Properties of firewall at slave: CBASS_MISC_PERI0_ERR_REGS */
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_ID                                                    (239U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_TYPE                                                  (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_MMR_BASE                                              (0x0000004503bc00U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_NUM_REGIONS                                           (1U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                               (3U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_ERR_START                                             (0x000000201f0000U)
#define CSL_STD_FW_CBASS_MISC_PERI0_ERR_REGS_ERR_END                                               (0x000000201f03ffU)

/* Properties of firewall at slave: MSRAM_1MB0_RAM */
#define CSL_STD_FW_MSRAM_1MB0_RAM_ID                                                               (256U)
#define CSL_STD_FW_MSRAM_1MB0_RAM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB0_RAM_MMR_BASE                                                         (0x00000045040000U)
#define CSL_STD_FW_MSRAM_1MB0_RAM_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MSRAM_1MB0_RAM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MSRAM_1MB0_RAM_RAM_START                                                        (0x00000072000000U)
#define CSL_STD_FW_MSRAM_1MB0_RAM_RAM_END                                                          (0x000000720fffffU)

/* Properties of firewall at slave: MSRAM_1MB1_RAM */
#define CSL_STD_FW_MSRAM_1MB1_RAM_ID                                                               (257U)
#define CSL_STD_FW_MSRAM_1MB1_RAM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB1_RAM_MMR_BASE                                                         (0x00000045040400U)
#define CSL_STD_FW_MSRAM_1MB1_RAM_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MSRAM_1MB1_RAM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MSRAM_1MB1_RAM_RAM_START                                                        (0x00000072100000U)
#define CSL_STD_FW_MSRAM_1MB1_RAM_RAM_END                                                          (0x000000721fffffU)

/* Properties of firewall at slave: MSRAM_1MB2_RAM */
#define CSL_STD_FW_MSRAM_1MB2_RAM_ID                                                               (258U)
#define CSL_STD_FW_MSRAM_1MB2_RAM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB2_RAM_MMR_BASE                                                         (0x00000045040800U)
#define CSL_STD_FW_MSRAM_1MB2_RAM_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MSRAM_1MB2_RAM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MSRAM_1MB2_RAM_RAM_START                                                        (0x00000072200000U)
#define CSL_STD_FW_MSRAM_1MB2_RAM_RAM_END                                                          (0x000000722fffffU)

/* Properties of firewall at slave: MSRAM_1MB3_RAM */
#define CSL_STD_FW_MSRAM_1MB3_RAM_ID                                                               (259U)
#define CSL_STD_FW_MSRAM_1MB3_RAM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB3_RAM_MMR_BASE                                                         (0x00000045040c00U)
#define CSL_STD_FW_MSRAM_1MB3_RAM_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MSRAM_1MB3_RAM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MSRAM_1MB3_RAM_RAM_START                                                        (0x00000072300000U)
#define CSL_STD_FW_MSRAM_1MB3_RAM_RAM_END                                                          (0x000000723fffffU)

/* Properties of firewall at slave: MSRAM_1MB4_RAM */
#define CSL_STD_FW_MSRAM_1MB4_RAM_ID                                                               (260U)
#define CSL_STD_FW_MSRAM_1MB4_RAM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB4_RAM_MMR_BASE                                                         (0x00000045041000U)
#define CSL_STD_FW_MSRAM_1MB4_RAM_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MSRAM_1MB4_RAM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MSRAM_1MB4_RAM_RAM_START                                                        (0x00000072400000U)
#define CSL_STD_FW_MSRAM_1MB4_RAM_RAM_END                                                          (0x000000724fffffU)

/* Properties of firewall at slave: MSRAM_1MB5_RAM */
#define CSL_STD_FW_MSRAM_1MB5_RAM_ID                                                               (261U)
#define CSL_STD_FW_MSRAM_1MB5_RAM_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_MSRAM_1MB5_RAM_MMR_BASE                                                         (0x00000045041400U)
#define CSL_STD_FW_MSRAM_1MB5_RAM_NUM_REGIONS                                                      (8U)
#define CSL_STD_FW_MSRAM_1MB5_RAM_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_MSRAM_1MB5_RAM_RAM_START                                                        (0x00000072500000U)
#define CSL_STD_FW_MSRAM_1MB5_RAM_RAM_END                                                          (0x000000725fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_UMC_CFG */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_ID                                                  (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_MMR_BASE                                            (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_UMC_START                                           (0x0000007c000000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_CFG_UMC_END                                             (0x0000007c01ffffU)

/* Properties of firewall at slave: C7X256V0_CLEC_C7XV_CLEC_CFG */
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_ID                                                  (262U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_MMR_BASE                                            (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_CLEC_START                                          (0x0000007c200000U)
#define CSL_STD_FW_C7X256V0_CLEC_C7XV_CLEC_CFG_CLEC_END                                            (0x0000007c2fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_ID                                              (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_MMR_BASE                                        (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_NUM_REGIONS                                     (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_DRU_START                                       (0x0000007c400000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_DRU_END                                         (0x0000007c403fffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_ID                                          (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_MMR_BASE                                    (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_NUM_REGIONS                                 (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_DRU_SET_START                               (0x0000007c404000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_SET_DRU_SET_END                                 (0x0000007c407fffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_ID                                        (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_MMR_BASE                                  (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_DRU_QUEUE_START                           (0x0000007c408000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_QUEUE_DRU_QUEUE_END                             (0x0000007c40ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_ID                                        (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_MMR_BASE                                  (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_DRU_CHNRT_START                           (0x0000007c440000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHNRT_DRU_CHNRT_END                             (0x0000007c45ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_ID                                         (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_MMR_BASE                                   (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_NUM_REGIONS                                (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_DRU_CHRT_START                             (0x0000007c460000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHRT_DRU_CHRT_END                               (0x0000007c47ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_ID                               (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_MMR_BASE                         (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_NUM_REGIONS                      (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_DRU_CHATOMIC_DEBUG_START         (0x0000007c480000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_DRU_CHATOMIC_DEBUG_END           (0x0000007c49ffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_ID                                       (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_MMR_BASE                                 (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_NUM_REGIONS                              (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_DRU_CHCORE_START                         (0x0000007c4a0000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CHCORE_DRU_CHCORE_END                           (0x0000007c4bffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_ID                                        (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_MMR_BASE                                  (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_DRU_CAUSE_START                           (0x0000007c4e0000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_DRU_CFG_DRU_CAUSE_DRU_CAUSE_END                             (0x0000007c4fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_UMC_MEM_MAIN */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_ID                                             (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_MMR_BASE                                       (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_NUM_REGIONS                                    (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_UMC_MEM_MAIN_START                             (0x0000007e000000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_MAIN_UMC_MEM_MAIN_END                               (0x0000007e1fffffU)

/* Properties of firewall at slave: C7X256V0_CORE0_C7XV_UMC_MEM_AUX */
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_ID                                              (262U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_MMR_BASE                                        (0x00000045041800U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_NUM_REGIONS                                     (8U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_UMC_MEM_AUX_START                               (0x0000007e200000U)
#define CSL_STD_FW_C7X256V0_CORE0_C7XV_UMC_MEM_AUX_UMC_MEM_AUX_END                                 (0x0000007e23ffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_UMC_CFG */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_CFG_ID                                                  (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_CFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_CFG_MMR_BASE                                            (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_CFG_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_CFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_CFG_UMC_START                                           (0x0000007d000000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_CFG_UMC_END                                             (0x0000007d01ffffU)

/* Properties of firewall at slave: C7X256V1_CLEC_C7XV_CLEC_CFG */
#define CSL_STD_FW_C7X256V1_CLEC_C7XV_CLEC_CFG_ID                                                  (263U)
#define CSL_STD_FW_C7X256V1_CLEC_C7XV_CLEC_CFG_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CLEC_C7XV_CLEC_CFG_MMR_BASE                                            (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CLEC_C7XV_CLEC_CFG_NUM_REGIONS                                         (8U)
#define CSL_STD_FW_C7X256V1_CLEC_C7XV_CLEC_CFG_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_C7X256V1_CLEC_C7XV_CLEC_CFG_CLEC_START                                          (0x0000007d200000U)
#define CSL_STD_FW_C7X256V1_CLEC_C7XV_CLEC_CFG_CLEC_END                                            (0x0000007d2fffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_DRU_CFG_DRU */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_ID                                              (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_MMR_BASE                                        (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_NUM_REGIONS                                     (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_DRU_START                                       (0x0000007d400000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_DRU_END                                         (0x0000007d403fffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_DRU_CFG_DRU_SET */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_SET_ID                                          (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_SET_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_SET_MMR_BASE                                    (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_SET_NUM_REGIONS                                 (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_SET_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_SET_DRU_SET_START                               (0x0000007d404000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_SET_DRU_SET_END                                 (0x0000007d407fffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_DRU_CFG_DRU_QUEUE */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_QUEUE_ID                                        (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_QUEUE_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_QUEUE_MMR_BASE                                  (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_QUEUE_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_QUEUE_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_QUEUE_DRU_QUEUE_START                           (0x0000007d408000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_QUEUE_DRU_QUEUE_END                             (0x0000007d40ffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHNRT */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHNRT_ID                                        (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHNRT_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHNRT_MMR_BASE                                  (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHNRT_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHNRT_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHNRT_DRU_CHNRT_START                           (0x0000007d440000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHNRT_DRU_CHNRT_END                             (0x0000007d45ffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHRT */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHRT_ID                                         (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHRT_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHRT_MMR_BASE                                   (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHRT_NUM_REGIONS                                (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHRT_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHRT_DRU_CHRT_START                             (0x0000007d460000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHRT_DRU_CHRT_END                               (0x0000007d47ffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_ID                               (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_TYPE                             (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_MMR_BASE                         (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_NUM_REGIONS                      (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_NUM_PRIV_IDS_PER_REGION          (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_DRU_CHATOMIC_DEBUG_START         (0x0000007d480000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHATOMIC_DEBUG_DRU_CHATOMIC_DEBUG_END           (0x0000007d49ffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHCORE */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHCORE_ID                                       (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHCORE_TYPE                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHCORE_MMR_BASE                                 (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHCORE_NUM_REGIONS                              (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHCORE_NUM_PRIV_IDS_PER_REGION                  (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHCORE_DRU_CHCORE_START                         (0x0000007d4a0000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CHCORE_DRU_CHCORE_END                           (0x0000007d4bffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CAUSE */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CAUSE_ID                                        (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CAUSE_TYPE                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CAUSE_MMR_BASE                                  (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CAUSE_NUM_REGIONS                               (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CAUSE_NUM_PRIV_IDS_PER_REGION                   (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CAUSE_DRU_CAUSE_START                           (0x0000007d4e0000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_DRU_CFG_DRU_CAUSE_DRU_CAUSE_END                             (0x0000007d4fffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_UMC_MEM_MAIN */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_MAIN_ID                                             (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_MAIN_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_MAIN_MMR_BASE                                       (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_MAIN_NUM_REGIONS                                    (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_MAIN_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_MAIN_UMC_MEM_MAIN_START                             (0x0000007f000000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_MAIN_UMC_MEM_MAIN_END                               (0x0000007f1fffffU)

/* Properties of firewall at slave: C7X256V1_CORE0_C7XV_UMC_MEM_AUX */
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_AUX_ID                                              (263U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_AUX_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_AUX_MMR_BASE                                        (0x00000045041c00U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_AUX_NUM_REGIONS                                     (8U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_AUX_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_AUX_UMC_MEM_AUX_START                               (0x0000007f200000U)
#define CSL_STD_FW_C7X256V1_CORE0_C7XV_UMC_MEM_AUX_UMC_MEM_AUX_END                                 (0x0000007f23ffffU)

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

/* Properties of firewall at slave: SMS0_RTI_0_TIFS_WDT_RTI */
#define CSL_STD_FW_SMS0_RTI_0_TIFS_WDT_RTI_ID                                                      (544U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_WDT_RTI_TYPE                                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_WDT_RTI_MMR_BASE                                                (0x00000045088000U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_WDT_RTI_NUM_REGIONS                                             (1U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_WDT_RTI_NUM_PRIV_IDS_PER_REGION                                 (3U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_WDT_RTI_WDT_RTI_START                                           (0x00000044135000U)
#define CSL_STD_FW_SMS0_RTI_0_TIFS_WDT_RTI_WDT_RTI_END                                             (0x000000441350ffU)

/* Properties of firewall at slave: SMS0_WDTCTRL_0_TIFS_RTI_MMR */
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_RTI_MMR_ID                                                  (545U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_RTI_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_RTI_MMR_MMR_BASE                                            (0x00000045088400U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_RTI_MMR_NUM_REGIONS                                         (1U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_RTI_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_RTI_MMR_RTI_START                                           (0x00000044135100U)
#define CSL_STD_FW_SMS0_WDTCTRL_0_TIFS_RTI_MMR_RTI_END                                             (0x000000441351ffU)

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

/* Properties of firewall at slave: SMS0_RTI_1_HSM_WDT_RTI */
#define CSL_STD_FW_SMS0_RTI_1_HSM_WDT_RTI_ID                                                       (672U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_WDT_RTI_TYPE                                                     (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_RTI_1_HSM_WDT_RTI_MMR_BASE                                                 (0x000000450a8000U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_WDT_RTI_NUM_REGIONS                                              (1U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_WDT_RTI_NUM_PRIV_IDS_PER_REGION                                  (3U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_WDT_RTI_HSM_WDT_RTI_START                                        (0x00000043935000U)
#define CSL_STD_FW_SMS0_RTI_1_HSM_WDT_RTI_HSM_WDT_RTI_END                                          (0x000000439350ffU)

/* Properties of firewall at slave: SMS0_WDTCTRL_1_HSM_CTRL_MMR */
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_CTRL_MMR_ID                                                  (673U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_CTRL_MMR_TYPE                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_CTRL_MMR_MMR_BASE                                            (0x000000450a8400U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_CTRL_MMR_NUM_REGIONS                                         (1U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_CTRL_MMR_NUM_PRIV_IDS_PER_REGION                             (3U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_CTRL_MMR_HSM_CTRL_MMR_START                                  (0x00000043936000U)
#define CSL_STD_FW_SMS0_WDTCTRL_1_HSM_CTRL_MMR_HSM_CTRL_MMR_END                                    (0x00000043936fffU)

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

/* Properties of firewall at slave: MCASP0_CFG */
#define CSL_STD_FW_MCASP0_CFG_ID                                                                   (21U)
#define CSL_STD_FW_MCASP0_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP0_CFG_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP0_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP0_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP0_CFG_CFG_START                                                            (0x00000002b00000U)
#define CSL_STD_FW_MCASP0_CFG_CFG_END                                                              (0x00000002b01fffU)

/* Properties of firewall at slave: MCASP0_DMA */
#define CSL_STD_FW_MCASP0_DMA_ID                                                                   (21U)
#define CSL_STD_FW_MCASP0_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP0_DMA_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP0_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP0_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP0_DMA_DMA_START                                                            (0x00000002b08000U)
#define CSL_STD_FW_MCASP0_DMA_DMA_END                                                              (0x00000002b083ffU)

/* Properties of firewall at slave: MCASP1_CFG */
#define CSL_STD_FW_MCASP1_CFG_ID                                                                   (21U)
#define CSL_STD_FW_MCASP1_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP1_CFG_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP1_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP1_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP1_CFG_CFG_START                                                            (0x00000002b10000U)
#define CSL_STD_FW_MCASP1_CFG_CFG_END                                                              (0x00000002b11fffU)

/* Properties of firewall at slave: MCASP1_DMA */
#define CSL_STD_FW_MCASP1_DMA_ID                                                                   (21U)
#define CSL_STD_FW_MCASP1_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP1_DMA_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP1_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP1_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP1_DMA_DMA_START                                                            (0x00000002b18000U)
#define CSL_STD_FW_MCASP1_DMA_DMA_END                                                              (0x00000002b183ffU)

/* Properties of firewall at slave: MCASP2_CFG */
#define CSL_STD_FW_MCASP2_CFG_ID                                                                   (21U)
#define CSL_STD_FW_MCASP2_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP2_CFG_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP2_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP2_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP2_CFG_CFG_START                                                            (0x00000002b20000U)
#define CSL_STD_FW_MCASP2_CFG_CFG_END                                                              (0x00000002b21fffU)

/* Properties of firewall at slave: MCASP2_DMA */
#define CSL_STD_FW_MCASP2_DMA_ID                                                                   (21U)
#define CSL_STD_FW_MCASP2_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP2_DMA_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP2_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP2_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP2_DMA_DMA_START                                                            (0x00000002b28000U)
#define CSL_STD_FW_MCASP2_DMA_DMA_END                                                              (0x00000002b283ffU)

/* Properties of firewall at slave: MCASP3_CFG */
#define CSL_STD_FW_MCASP3_CFG_ID                                                                   (21U)
#define CSL_STD_FW_MCASP3_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP3_CFG_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP3_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP3_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP3_CFG_CFG_START                                                            (0x00000002b30000U)
#define CSL_STD_FW_MCASP3_CFG_CFG_END                                                              (0x00000002b31fffU)

/* Properties of firewall at slave: MCASP3_DMA */
#define CSL_STD_FW_MCASP3_DMA_ID                                                                   (21U)
#define CSL_STD_FW_MCASP3_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP3_DMA_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP3_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP3_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP3_DMA_DMA_START                                                            (0x00000002b38000U)
#define CSL_STD_FW_MCASP3_DMA_DMA_END                                                              (0x00000002b383ffU)

/* Properties of firewall at slave: MCASP4_CFG */
#define CSL_STD_FW_MCASP4_CFG_ID                                                                   (21U)
#define CSL_STD_FW_MCASP4_CFG_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP4_CFG_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP4_CFG_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP4_CFG_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP4_CFG_CFG_START                                                            (0x00000002b40000U)
#define CSL_STD_FW_MCASP4_CFG_CFG_END                                                              (0x00000002b41fffU)

/* Properties of firewall at slave: MCASP4_DMA */
#define CSL_STD_FW_MCASP4_DMA_ID                                                                   (21U)
#define CSL_STD_FW_MCASP4_DMA_TYPE                                                                 (CSL_FW_SECURITY)
#define CSL_STD_FW_MCASP4_DMA_MMR_BASE                                                             (0x00000045005400U)
#define CSL_STD_FW_MCASP4_DMA_NUM_REGIONS                                                          (8U)
#define CSL_STD_FW_MCASP4_DMA_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_STD_FW_MCASP4_DMA_DMA_START                                                            (0x00000002b48000U)
#define CSL_STD_FW_MCASP4_DMA_DMA_END                                                              (0x00000002b483ffU)

/* Properties of firewall at slave: AASRC0_AASRC_CFG */
#define CSL_STD_FW_AASRC0_AASRC_CFG_ID                                                             (21U)
#define CSL_STD_FW_AASRC0_AASRC_CFG_TYPE                                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_AASRC0_AASRC_CFG_MMR_BASE                                                       (0x00000045005400U)
#define CSL_STD_FW_AASRC0_AASRC_CFG_NUM_REGIONS                                                    (8U)
#define CSL_STD_FW_AASRC0_AASRC_CFG_NUM_PRIV_IDS_PER_REGION                                        (3U)
#define CSL_STD_FW_AASRC0_AASRC_CFG_CFG_START                                                      (0x00000002d00000U)
#define CSL_STD_FW_AASRC0_AASRC_CFG_CFG_END                                                        (0x00000002d03fffU)

/* Properties of firewall at slave: AASRC0_AASRC_DATA_R0 */
#define CSL_STD_FW_AASRC0_AASRC_DATA_R0_ID                                                         (21U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R0_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R0_MMR_BASE                                                   (0x00000045005400U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R0_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R0_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R0_DATA_R0_START                                              (0x00000002d10000U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R0_DATA_R0_END                                                (0x00000002d13fffU)

/* Properties of firewall at slave: AASRC0_AASRC_DATA_R1 */
#define CSL_STD_FW_AASRC0_AASRC_DATA_R1_ID                                                         (21U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R1_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R1_MMR_BASE                                                   (0x00000045005400U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R1_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R1_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R1_DATA_R1_START                                              (0x00000002d20000U)
#define CSL_STD_FW_AASRC0_AASRC_DATA_R1_DATA_R1_END                                                (0x00000002d23fffU)

/* Properties of firewall at slave: AASRC1_AASRC_CFG */
#define CSL_STD_FW_AASRC1_AASRC_CFG_ID                                                             (21U)
#define CSL_STD_FW_AASRC1_AASRC_CFG_TYPE                                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_AASRC1_AASRC_CFG_MMR_BASE                                                       (0x00000045005400U)
#define CSL_STD_FW_AASRC1_AASRC_CFG_NUM_REGIONS                                                    (8U)
#define CSL_STD_FW_AASRC1_AASRC_CFG_NUM_PRIV_IDS_PER_REGION                                        (3U)
#define CSL_STD_FW_AASRC1_AASRC_CFG_CFG_START                                                      (0x00000002d40000U)
#define CSL_STD_FW_AASRC1_AASRC_CFG_CFG_END                                                        (0x00000002d43fffU)

/* Properties of firewall at slave: AASRC1_AASRC_DATA_R0 */
#define CSL_STD_FW_AASRC1_AASRC_DATA_R0_ID                                                         (21U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R0_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R0_MMR_BASE                                                   (0x00000045005400U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R0_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R0_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R0_DATA_R0_START                                              (0x00000002d50000U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R0_DATA_R0_END                                                (0x00000002d53fffU)

/* Properties of firewall at slave: AASRC1_AASRC_DATA_R1 */
#define CSL_STD_FW_AASRC1_AASRC_DATA_R1_ID                                                         (21U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R1_TYPE                                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R1_MMR_BASE                                                   (0x00000045005400U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R1_NUM_REGIONS                                                (8U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R1_NUM_PRIV_IDS_PER_REGION                                    (3U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R1_DATA_R1_START                                              (0x00000002d60000U)
#define CSL_STD_FW_AASRC1_AASRC_DATA_R1_DATA_R1_END                                                (0x00000002d63fffU)

/* Properties of firewall at slave: ATL0_REG */
#define CSL_STD_FW_ATL0_REG_ID                                                                     (21U)
#define CSL_STD_FW_ATL0_REG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_ATL0_REG_MMR_BASE                                                               (0x00000045005400U)
#define CSL_STD_FW_ATL0_REG_NUM_REGIONS                                                            (8U)
#define CSL_STD_FW_ATL0_REG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_ATL0_REG_REG_START                                                              (0x0000000fee0000U)
#define CSL_STD_FW_ATL0_REG_REG_END                                                                (0x0000000fee03ffU)

/* Properties of firewall at slave: CBASS_MCASP0_ERR_REGS */
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_ID                                                        (21U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_MMR_BASE                                                  (0x00000045005400U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_NUM_REGIONS                                               (8U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_ERR_START                                                 (0x0000000fef0000U)
#define CSL_STD_FW_CBASS_MCASP0_ERR_REGS_ERR_END                                                   (0x0000000fef03ffU)

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

/* Properties of firewall at slave: PSCSS0_VBUS */
#define CSL_STD_FW_PSCSS0_VBUS_ID                                                                  (33U)
#define CSL_STD_FW_PSCSS0_VBUS_TYPE                                                                (CSL_FW_SECURITY)
#define CSL_STD_FW_PSCSS0_VBUS_MMR_BASE                                                            (0x00000045008400U)
#define CSL_STD_FW_PSCSS0_VBUS_NUM_REGIONS                                                         (16U)
#define CSL_STD_FW_PSCSS0_VBUS_NUM_PRIV_IDS_PER_REGION                                             (3U)
#define CSL_STD_FW_PSCSS0_VBUS_VBUS_START                                                          (0x00000000400000U)
#define CSL_STD_FW_PSCSS0_VBUS_VBUS_END                                                            (0x00000000400fffU)

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
#define CSL_STD_FW_DFTSS0_MEM_MEM_START                                                            (0x00000000500000U)
#define CSL_STD_FW_DFTSS0_MEM_MEM_END                                                              (0x000000005003ffU)

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
#define CSL_STD_FW_PLL0_CFG_CFG_END                                                                (0x0000000068ffffU)

/* Properties of firewall at slave: PSRAMECC0_REGS */
#define CSL_STD_FW_PSRAMECC0_REGS_ID                                                               (33U)
#define CSL_STD_FW_PSRAMECC0_REGS_TYPE                                                             (CSL_FW_SECURITY)
#define CSL_STD_FW_PSRAMECC0_REGS_MMR_BASE                                                         (0x00000045008400U)
#define CSL_STD_FW_PSRAMECC0_REGS_NUM_REGIONS                                                      (16U)
#define CSL_STD_FW_PSRAMECC0_REGS_NUM_PRIV_IDS_PER_REGION                                          (3U)
#define CSL_STD_FW_PSRAMECC0_REGS_ECC_AGGR_START                                                   (0x00000000700000U)
#define CSL_STD_FW_PSRAMECC0_REGS_ECC_AGGR_END                                                     (0x000000007003ffU)

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

/* Properties of firewall at slave: DCC7_CFG */
#define CSL_STD_FW_DCC7_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC7_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC7_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC7_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC7_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC7_CFG_START                                                                  (0x0000000081c000U)
#define CSL_STD_FW_DCC7_CFG_END                                                                    (0x0000000081c03fU)

/* Properties of firewall at slave: DCC8_CFG */
#define CSL_STD_FW_DCC8_CFG_ID                                                                     (33U)
#define CSL_STD_FW_DCC8_CFG_TYPE                                                                   (CSL_FW_SECURITY)
#define CSL_STD_FW_DCC8_CFG_MMR_BASE                                                               (0x00000045008400U)
#define CSL_STD_FW_DCC8_CFG_NUM_REGIONS                                                            (16U)
#define CSL_STD_FW_DCC8_CFG_NUM_PRIV_IDS_PER_REGION                                                (3U)
#define CSL_STD_FW_DCC8_CFG_START                                                                  (0x00000000820000U)
#define CSL_STD_FW_DCC8_CFG_END                                                                    (0x0000000082003fU)

/* Properties of firewall at slave: MAIN_GPIO_INTROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_MAIN_GPIO_INTROUTER0_INTR_ROUTER_CFG_ID                                         (33U)
#define CSL_STD_FW_MAIN_GPIO_INTROUTER0_INTR_ROUTER_CFG_TYPE                                       (CSL_FW_SECURITY)
#define CSL_STD_FW_MAIN_GPIO_INTROUTER0_INTR_ROUTER_CFG_MMR_BASE                                   (0x00000045008400U)
#define CSL_STD_FW_MAIN_GPIO_INTROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                                (16U)
#define CSL_STD_FW_MAIN_GPIO_INTROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION                    (3U)
#define CSL_STD_FW_MAIN_GPIO_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START                      (0x00000000a00000U)
#define CSL_STD_FW_MAIN_GPIO_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                        (0x00000000a00fffU)

/* Properties of firewall at slave: TIMESYNC_INTROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_TIMESYNC_INTROUTER0_INTR_ROUTER_CFG_ID                                          (33U)
#define CSL_STD_FW_TIMESYNC_INTROUTER0_INTR_ROUTER_CFG_TYPE                                        (CSL_FW_SECURITY)
#define CSL_STD_FW_TIMESYNC_INTROUTER0_INTR_ROUTER_CFG_MMR_BASE                                    (0x00000045008400U)
#define CSL_STD_FW_TIMESYNC_INTROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                                 (16U)
#define CSL_STD_FW_TIMESYNC_INTROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION                     (3U)
#define CSL_STD_FW_TIMESYNC_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START                       (0x00000000a40000U)
#define CSL_STD_FW_TIMESYNC_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                         (0x00000000a403ffU)

/* Properties of firewall at slave: IDOM0_MAIN_PLL_ECC_AGGR4_REGS */
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR4_REGS_ID                                                (33U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR4_REGS_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR4_REGS_MMR_BASE                                          (0x00000045008400U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR4_REGS_NUM_REGIONS                                       (16U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR4_REGS_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR4_REGS_REGS_START                                        (0x0000003f015000U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR4_REGS_REGS_END                                          (0x0000003f0153ffU)

/* Properties of firewall at slave: IDOM0_PULSAR_PLL_ECC_AGGR8_REGS */
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR8_REGS_ID                                              (33U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR8_REGS_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR8_REGS_MMR_BASE                                        (0x00000045008400U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR8_REGS_NUM_REGIONS                                     (16U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR8_REGS_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR8_REGS_REGS_START                                      (0x0000003f016000U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR8_REGS_REGS_END                                        (0x0000003f0163ffU)

/* Properties of firewall at slave: IDOM1_MAIN_PLL_ECC_AGGR5_REGS */
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR5_REGS_ID                                                (33U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR5_REGS_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR5_REGS_MMR_BASE                                          (0x00000045008400U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR5_REGS_NUM_REGIONS                                       (16U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR5_REGS_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR5_REGS_REGS_START                                        (0x0000003f017000U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR5_REGS_REGS_END                                          (0x0000003f0173ffU)

/* Properties of firewall at slave: IDOM1_PULSAR_PLL_ECC_AGGR9_REGS */
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR9_REGS_ID                                              (33U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR9_REGS_TYPE                                            (CSL_FW_SECURITY)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR9_REGS_MMR_BASE                                        (0x00000045008400U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR9_REGS_NUM_REGIONS                                     (16U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR9_REGS_NUM_PRIV_IDS_PER_REGION                         (3U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR9_REGS_REGS_START                                      (0x0000003f018000U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR9_REGS_REGS_END                                        (0x0000003f0183ffU)

/* Properties of firewall at slave: IDOM0_MAIN_PLL_ECC_AGGR6_REGS */
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR6_REGS_ID                                                (33U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR6_REGS_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR6_REGS_MMR_BASE                                          (0x00000045008400U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR6_REGS_NUM_REGIONS                                       (16U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR6_REGS_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR6_REGS_REGS_START                                        (0x0000003f019000U)
#define CSL_STD_FW_IDOM0_MAIN_PLL_ECC_AGGR6_REGS_REGS_END                                          (0x0000003f0193ffU)

/* Properties of firewall at slave: IDOM0_PULSAR_PLL_ECC_AGGR10_REGS */
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR10_REGS_ID                                             (33U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR10_REGS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR10_REGS_MMR_BASE                                       (0x00000045008400U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR10_REGS_NUM_REGIONS                                    (16U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR10_REGS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR10_REGS_REGS_START                                     (0x0000003f01a000U)
#define CSL_STD_FW_IDOM0_PULSAR_PLL_ECC_AGGR10_REGS_REGS_END                                       (0x0000003f01a3ffU)

/* Properties of firewall at slave: IDOM1_MAIN_PLL_ECC_AGGR7_REGS */
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR7_REGS_ID                                                (33U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR7_REGS_TYPE                                              (CSL_FW_SECURITY)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR7_REGS_MMR_BASE                                          (0x00000045008400U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR7_REGS_NUM_REGIONS                                       (16U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR7_REGS_NUM_PRIV_IDS_PER_REGION                           (3U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR7_REGS_REGS_START                                        (0x0000003f01b000U)
#define CSL_STD_FW_IDOM1_MAIN_PLL_ECC_AGGR7_REGS_REGS_END                                          (0x0000003f01b3ffU)

/* Properties of firewall at slave: IDOM1_PULSAR_PLL_ECC_AGGR11_REGS */
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR11_REGS_ID                                             (33U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR11_REGS_TYPE                                           (CSL_FW_SECURITY)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR11_REGS_MMR_BASE                                       (0x00000045008400U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR11_REGS_NUM_REGIONS                                    (16U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR11_REGS_NUM_PRIV_IDS_PER_REGION                        (3U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR11_REGS_REGS_START                                     (0x0000003f01c000U)
#define CSL_STD_FW_IDOM1_PULSAR_PLL_ECC_AGGR11_REGS_REGS_END                                       (0x0000003f01c3ffU)

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

/* Properties of firewall at slave: MCU_PADCFG_CTRL0_CFG0 */
#define CSL_STD_FW_MCU_PADCFG_CTRL0_CFG0_ID                                                        (35U)
#define CSL_STD_FW_MCU_PADCFG_CTRL0_CFG0_TYPE                                                      (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_PADCFG_CTRL0_CFG0_MMR_BASE                                                  (0x00000045008c00U)
#define CSL_STD_FW_MCU_PADCFG_CTRL0_CFG0_NUM_REGIONS                                               (16U)
#define CSL_STD_FW_MCU_PADCFG_CTRL0_CFG0_NUM_PRIV_IDS_PER_REGION                                   (3U)
#define CSL_STD_FW_MCU_PADCFG_CTRL0_CFG0_CFG0_START                                                (0x00000004080000U)
#define CSL_STD_FW_MCU_PADCFG_CTRL0_CFG0_CFG0_END                                                  (0x00000004087fffU)

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

/* Properties of firewall at slave: MCU_MCU_GPIO_INTROUTER0_INTR_ROUTER_CFG */
#define CSL_STD_FW_MCU_MCU_GPIO_INTROUTER0_INTR_ROUTER_CFG_ID                                      (35U)
#define CSL_STD_FW_MCU_MCU_GPIO_INTROUTER0_INTR_ROUTER_CFG_TYPE                                    (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_MCU_GPIO_INTROUTER0_INTR_ROUTER_CFG_MMR_BASE                                (0x00000045008c00U)
#define CSL_STD_FW_MCU_MCU_GPIO_INTROUTER0_INTR_ROUTER_CFG_NUM_REGIONS                             (16U)
#define CSL_STD_FW_MCU_MCU_GPIO_INTROUTER0_INTR_ROUTER_CFG_NUM_PRIV_IDS_PER_REGION                 (3U)
#define CSL_STD_FW_MCU_MCU_GPIO_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_START                   (0x00000004210000U)
#define CSL_STD_FW_MCU_MCU_GPIO_INTROUTER0_INTR_ROUTER_CFG_INTR_ROUTER_CFG_END                     (0x000000042103ffU)

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

/* Properties of firewall at slave: MCU_DCC0_CFG */
#define CSL_STD_FW_MCU_DCC0_CFG_ID                                                                 (35U)
#define CSL_STD_FW_MCU_DCC0_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_DCC0_CFG_MMR_BASE                                                           (0x00000045008c00U)
#define CSL_STD_FW_MCU_DCC0_CFG_NUM_REGIONS                                                        (16U)
#define CSL_STD_FW_MCU_DCC0_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_DCC0_CFG_START                                                              (0x00000004c00000U)
#define CSL_STD_FW_MCU_DCC0_CFG_END                                                                (0x00000004c0003fU)

/* Properties of firewall at slave: MCU_DCC1_CFG */
#define CSL_STD_FW_MCU_DCC1_CFG_ID                                                                 (35U)
#define CSL_STD_FW_MCU_DCC1_CFG_TYPE                                                               (CSL_FW_SECURITY)
#define CSL_STD_FW_MCU_DCC1_CFG_MMR_BASE                                                           (0x00000045008c00U)
#define CSL_STD_FW_MCU_DCC1_CFG_NUM_REGIONS                                                        (16U)
#define CSL_STD_FW_MCU_DCC1_CFG_NUM_PRIV_IDS_PER_REGION                                            (3U)
#define CSL_STD_FW_MCU_DCC1_CFG_START                                                              (0x00000004c10000U)
#define CSL_STD_FW_MCU_DCC1_CFG_END                                                                (0x00000004c1003fU)

/* Channelized Firewall Definitions */

/* Properties of channelized firewall at: PSCSS0_VBUS */
#define CSL_CH_FW_PSCSS0_VBUS_ID                                                                   (128U)
#define CSL_CH_FW_PSCSS0_VBUS_TYPE                                                                 (CSL_FW_CHANNEL)
#define CSL_CH_FW_PSCSS0_VBUS_MMR_BASE                                                             (0x00000045020000U)
#define CSL_CH_FW_PSCSS0_VBUS_NUM_REGIONS                                                          (5U)
#define CSL_CH_FW_PSCSS0_VBUS_NUM_PRIV_IDS_PER_REGION                                              (3U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_0_START                                                    (0x0000000000400000U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_0_END                                                      (0x0000000000400004U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_0_OFFSET_FIRST_RES                                         (0x0000000000000000U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_0_NUM_CHANNELS                                             (1U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_0_CHANNEL_SIZE                                             (4U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_1_START                                                    (0x0000000000400000U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_1_END                                                      (0x0000000000400004U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_1_OFFSET_FIRST_RES                                         (0x0000000000000020U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_1_NUM_CHANNELS                                             (1U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_1_CHANNEL_SIZE                                             (4U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_2_START                                                    (0x0000000000400000U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_2_END                                                      (0x0000000000400004U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_2_OFFSET_FIRST_RES                                         (0x0000000000000040U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_2_NUM_CHANNELS                                             (1U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_2_CHANNEL_SIZE                                             (4U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_3_START                                                    (0x0000000000400000U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_3_END                                                      (0x0000000000400004U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_3_OFFSET_FIRST_RES                                         (0x0000000000000060U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_3_NUM_CHANNELS                                             (1U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_3_CHANNEL_SIZE                                             (4U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_4_START                                                    (0x0000000000400000U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_4_END                                                      (0x0000000000400004U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_4_OFFSET_FIRST_RES                                         (0x0000000000000080U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_4_NUM_CHANNELS                                             (1U)
#define CSL_CH_FW_PSCSS0_VBUS_VBUS_VBUS_4_CHANNEL_SIZE                                             (4U)

#ifdef __cplusplus
}
#endif
#endif /* CSLR_SOC_FW_H_ */
