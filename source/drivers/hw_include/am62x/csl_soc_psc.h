/********************************************************************
*
* SOC PSC PD and LPSC ID definitions. header file
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
#ifndef CSL_SOC_PSC_H_
#define CSL_SOC_PSC_H_

#include <drivers/hw_include/cslr.h>
#include <drivers/hw_include/tistdtypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
* Auto-generated PSC definitions File
*/

/*
* PD Indices:
*/

/*
*  MAIN PD
*/

#define CSL_MAIN_GP_CORE_CTL                                                                       (0U)
#define CSL_MAIN_PD_ICSSM                                                                          (1U)
#define CSL_MAIN_PD_CPSW                                                                           (2U)
#define CSL_MAIN_PD_A53_CLUSTER_0                                                                  (3U)
#define CSL_MAIN_PD_A53_0                                                                          (4U)
#define CSL_MAIN_PD_A53_1                                                                          (5U)
#define CSL_MAIN_PD_A53_2                                                                          (6U)
#define CSL_MAIN_PD_A53_3                                                                          (7U)
#define CSL_MAIN_PD_GPU                                                                            (8U)
#define CSL_MAIN_PD_DSS                                                                            (9U)
/*
*  WKUP PD
*/

#define CSL_WKUP_GP_CORE_CTL_MCU                                                                   (0U)
#define CSL_WKUP_PD_M4F                                                                            (1U)
/*
* LPSC Modules:
*/

/*
*  MAIN LPSC
*/

#define CSL_MAIN_LPSC_MAIN_ALWAYSON                                                                (0U)
#define CSL_MAIN_LPSC_MAIN_DM                                                                      (1U)
#define CSL_MAIN_LPSC_DM_PBIST                                                                     (2U)
#define CSL_MAIN_LPSC_MAIN2DM_ISO                                                                  (3U)
#define CSL_MAIN_LPSC_DM2MAIN_ISO                                                                  (4U)
#define CSL_MAIN_LPSC_DM2MAIN_INFRA_ISO                                                            (5U)
#define CSL_MAIN_LPSC_DM2CENTRAL_ISO                                                               (6U)
#define CSL_MAIN_LPSC_CENTRAL2DM_ISO                                                               (7U)
#define CSL_MAIN_LPSC_GP_SPARE0                                                                    (8U)
#define CSL_MAIN_LPSC_EMIF_LOCAL                                                                   (9U)
#define CSL_MAIN_LPSC_EMIF_CFG_ISO                                                                 (10U)
#define CSL_MAIN_LPSC_EMIF_DATA_ISO                                                                (11U)
#define CSL_MAIN_LPSC_MAIN_USB0_ISO                                                                (12U)
#define CSL_MAIN_LPSC_MAIN_USB1_ISO                                                                (13U)
#define CSL_MAIN_LPSC_MAIN_TEST                                                                    (14U)
#define CSL_MAIN_LPSC_GPMC                                                                         (15U)
#define CSL_MAIN_LPSC_GP_SPARE1                                                                    (16U)
#define CSL_MAIN_LPSC_MAIN_MCASP_0                                                                 (17U)
#define CSL_MAIN_LPSC_MAIN_MCASP_1                                                                 (18U)
#define CSL_MAIN_LPSC_MAIN_MCASP_2                                                                 (19U)
#define CSL_MAIN_LPSC_EMMC_8B                                                                      (20U)
#define CSL_MAIN_LPSC_EMMC_4B_0                                                                    (21U)
#define CSL_MAIN_LPSC_EMMC_4B_1                                                                    (22U)
#define CSL_MAIN_LPSC_USB_0                                                                        (23U)
#define CSL_MAIN_LPSC_USB_1                                                                        (24U)
#define CSL_MAIN_LPSC_CSI_RX_0                                                                     (25U)
#define CSL_MAIN_LPSC_DPHY_0                                                                       (26U)
#define CSL_MAIN_LPSC_SMS_COMMON                                                                   (27U)
#define CSL_MAIN_LPSC_FSS_OSPI                                                                     (28U)
#define CSL_MAIN_LPSC_TIFS                                                                         (29U)
#define CSL_MAIN_LPSC_HSM                                                                          (30U)
#define CSL_MAIN_LPSC_SA3UL                                                                        (31U)
#define CSL_MAIN_LPSC_HSM_ISO                                                                      (32U)
#define CSL_MAIN_LPSC_DEBUGSS                                                                      (33U)
#define CSL_MAIN_LPSC_MAIN_IP                                                                      (34U)
#define CSL_MAIN_LPSC_MAIN_MCANSS_0                                                                (35U)
#define CSL_MAIN_LPSC_GIC                                                                          (36U)
#define CSL_MAIN_LPSC_MAIN_PBIST                                                                   (37U)
#define CSL_MAIN_LPSC_MAIN_SPARE0                                                                  (38U)
#define CSL_MAIN_LPSC_MAIN_SPARE1                                                                  (39U)
#define CSL_MAIN_LPSC_ICSSM                                                                        (40U)
#define CSL_MAIN_LPSC_CPSW3G                                                                       (41U)
#define CSL_MAIN_LPSC_A53_CLUSTER_0                                                                (42U)
#define CSL_MAIN_LPSC_A53_CLUSTER_0_PBIST_0                                                        (43U)
#define CSL_MAIN_LPSC_A53_CLUSTER_0_PBIST_1                                                        (44U)
#define CSL_MAIN_LPSC_A53_0                                                                        (45U)
#define CSL_MAIN_LPSC_A53_1                                                                        (46U)
#define CSL_MAIN_LPSC_A53_2                                                                        (47U)
#define CSL_MAIN_LPSC_A53_3                                                                        (48U)
#define CSL_MAIN_LPSC_GPU                                                                          (49U)
#define CSL_MAIN_LPSC_GPU_PBIST                                                                    (50U)
#define CSL_MAIN_LPSC_DSS                                                                          (51U)
/*
*  WKUP LPSC
*/

#define CSL_WKUP_LPSC_MCU_ALWAYSON                                                                 (0U)
#define CSL_WKUP_LPSC_MAIN2MCU_ISO                                                                 (1U)
#define CSL_WKUP_LPSC_MCU2MAIN_ISO                                                                 (2U)
#define CSL_WKUP_LPSC_DM2SAFE_ISO                                                                  (3U)
#define CSL_WKUP_LPSC_MCU2DM_ISO                                                                   (4U)
#define CSL_WKUP_LPSC_MCU_TEST                                                                     (5U)
#define CSL_WKUP_LPSC_MCU_M4F                                                                      (6U)
#define CSL_WKUP_LPSC_MCU_MCANSS_0                                                                 (7U)
#define CSL_WKUP_LPSC_MCU_MCANSS_1                                                                 (8U)
#define CSL_WKUP_LPSC_MCU_COMMON                                                                   (9U)

#ifdef __cplusplus
}
#endif
#endif /* CSL_SOC_PSC_H_ */

