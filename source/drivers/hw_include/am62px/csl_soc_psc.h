/********************************************************************
*
* SOC PSC PD and LPSC ID definitions. header file
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

#define CSL_MAIN_GP_CORE                                                                           (0U)
#define CSL_MAIN_PD_GPU_CORE                                                                       (1U)
#define CSL_MAIN_PD_CPSW                                                                           (2U)
#define CSL_MAIN_PD_MPU_CLST0                                                                      (3U)
#define CSL_MAIN_PD_MPU_CLST0_CORE0                                                                (4U)
#define CSL_MAIN_PD_MPU_CLST0_CORE1                                                                (5U)
#define CSL_MAIN_PD_MPU_CLST0_CORE2                                                                (6U)
#define CSL_MAIN_PD_MPU_CLST0_CORE3                                                                (7U)
#define CSL_MAIN_PD_GPU_CTRL                                                                       (8U)
#define CSL_MAIN_PD_RSVD2                                                                          (9U)
#define CSL_MAIN_PD_CODEC                                                                          (10U)
#define CSL_MAIN_PD_C7DSP0                                                                         (11U)
#define CSL_MAIN_PD_VPAC                                                                           (12U)
#define CSL_MAIN_PD_DDR                                                                            (13U)
#define CSL_MAIN_PD_PCIE                                                                           (14U)
#define CSL_MAIN_PD_C7DSP1                                                                         (15U)
#define CSL_MAIN_PD_MAIN_MCUSS0                                                                    (16U)
#define CSL_MAIN_PD_MAIN_SRAM0                                                                     (17U)
#define CSL_MAIN_PD_MAIN_SRAM1                                                                     (18U)
#define CSL_MAIN_PD_RSVD0                                                                          (19U)
#define CSL_MAIN_PD_RSVD1                                                                          (20U)
#define CSL_MAIN_PD_DSS                                                                            (21U)
/*
*  WKUP PD
*/

#define CSL_WKUP_GP_CORE_CTL_MCU                                                                   (0U)
#define CSL_WKUP_PD_MCUSS                                                                          (1U)
/*
* LPSC Modules:
*/

/*
*  MAIN LPSC
*/

#define CSL_MAIN_LPSC_MAIN_ALWAYSON                                                                (0U)
#define CSL_MAIN_LPSC_MAIN_DM                                                                      (1U)
#define CSL_MAIN_LPSC_MAIN_DM_PBIST0                                                               (2U)
#define CSL_MAIN_LPSC_MAIN_MAIN2DM_ISO                                                             (3U)
#define CSL_MAIN_LPSC_MAIN_DM2MAIN_ISO                                                             (4U)
#define CSL_MAIN_LPSC_MAIN_DM2MAIN_INFRA_ISO                                                       (5U)
#define CSL_MAIN_LPSC_MAIN_DM2CENTRAL_ISO                                                          (6U)
#define CSL_MAIN_LPSC_MAIN_CENTRAL2DM_ISO                                                          (7U)
#define CSL_MAIN_LPSC_MAIN_DM_PBIST1                                                               (8U)
#define CSL_MAIN_LPSC_MAIN_CSI_RX1                                                                 (9U)
#define CSL_MAIN_LPSC_MAIN_DPHY_RX1                                                                (10U)
#define CSL_MAIN_LPSC_MAIN_CSI_TX0                                                                 (11U)
#define CSL_MAIN_LPSC_MAIN_USB0_ISO                                                                (12U)
#define CSL_MAIN_LPSC_MAIN_USB2_ISO                                                                (13U)
#define CSL_MAIN_LPSC_MAIN_TEST                                                                    (14U)
#define CSL_MAIN_LPSC_MAIN_GPMC                                                                    (15U)
#define CSL_MAIN_LPSC_MAIN_MCANSS1                                                                 (16U)
#define CSL_MAIN_LPSC_MAIN_MCASP0                                                                  (17U)
#define CSL_MAIN_LPSC_MAIN_MCASP1                                                                  (18U)
#define CSL_MAIN_LPSC_MAIN_MCASP2                                                                  (19U)
#define CSL_MAIN_LPSC_MAIN_EMMC8B                                                                  (20U)
#define CSL_MAIN_LPSC_MAIN_EMMC4B0                                                                 (21U)
#define CSL_MAIN_LPSC_MAIN_EMMC4B1                                                                 (22U)
#define CSL_MAIN_LPSC_MAIN_USB0                                                                    (23U)
#define CSL_MAIN_LPSC_MAIN_USB2                                                                    (24U)
#define CSL_MAIN_LPSC_MAIN_CSI_RX0                                                                 (25U)
#define CSL_MAIN_LPSC_MAIN_DPHY_RX0                                                                (26U)
#define CSL_MAIN_LPSC_MAIN_SMS_COMMON                                                              (27U)
#define CSL_MAIN_LPSC_MAIN_FSS_OSPI                                                                (28U)
#define CSL_MAIN_LPSC_MAIN_TIFS                                                                    (29U)
#define CSL_MAIN_LPSC_MAIN_HSM                                                                     (30U)
#define CSL_MAIN_LPSC_MAIN_SA3UL                                                                   (31U)
#define CSL_MAIN_LPSC_MAIN_HSM_ISO                                                                 (32U)
#define CSL_MAIN_LPSC_MAIN_DEBUGSS                                                                 (33U)
#define CSL_MAIN_LPSC_MAIN_IP                                                                      (34U)
#define CSL_MAIN_LPSC_MAIN_MCANSS0                                                                 (35U)
#define CSL_MAIN_LPSC_MAIN_GIC                                                                     (36U)
#define CSL_MAIN_LPSC_MAIN_PBIST0                                                                  (37U)
#define CSL_MAIN_LPSC_MAIN_DPHY_TX0                                                                (38U)
#define CSL_MAIN_LPSC_MAIN_JPEG                                                                    (39U)
#define CSL_MAIN_LPSC_MAIN_SERDES0                                                                 (40U)
#define CSL_MAIN_LPSC_MAIN_SERDES1                                                                 (41U)
#define CSL_MAIN_LPSC_MAIN_CPSW                                                                    (42U)
#define CSL_MAIN_LPSC_MAIN_GPCORE_RSVD2                                                            (43U)
#define CSL_MAIN_LPSC_MAIN_CSI_RX3                                                                 (44U)
#define CSL_MAIN_LPSC_MAIN_DPHY_RX3                                                                (45U)
#define CSL_MAIN_LPSC_MAIN_PBIST1                                                                  (46U)
#define CSL_MAIN_LPSC_MAIN_USB1                                                                    (47U)
#define CSL_MAIN_LPSC_MAIN_CSI_RX2                                                                 (48U)
#define CSL_MAIN_LPSC_MAIN_CSI_DPHY_RX2                                                            (49U)
#define CSL_MAIN_LPSC_MAIN_GPCORE_RSVD3                                                            (50U)
#define CSL_MAIN_LPSC_MAIN_GPU_CORE                                                                (51U)
#define CSL_MAIN_LPSC_MAIN_GPCORE_RSVD5                                                            (52U)
#define CSL_MAIN_LPSC_MAIN_MPU_CLST0                                                               (53U)
#define CSL_MAIN_LPSC_MAIN_MPU_CLST0_PBIST0                                                        (54U)
#define CSL_MAIN_LPSC_MAIN_MPU_CLST0_PBIST1                                                        (55U)
#define CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE0                                                         (56U)
#define CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE1                                                         (57U)
#define CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE2                                                         (58U)
#define CSL_MAIN_LPSC_MAIN_MPU_CLST0_CORE3                                                         (59U)
#define CSL_MAIN_LPSC_MAIN_GPU_CTRL                                                                (60U)
#define CSL_MAIN_LPSC_MAIN_GPU_PBIST                                                               (61U)
#define CSL_MAIN_LPSC_PDRSVD2_RSVD0                                                                (62U)
#define CSL_MAIN_LPSC_PDRSVD2_RSVD1                                                                (63U)
#define CSL_MAIN_LPSC_PDRSVD2_RSVD2                                                                (64U)
#define CSL_MAIN_LPSC_MAIN_CODEC                                                                   (65U)
#define CSL_MAIN_LPSC_MAIN_CODEC_PBIST                                                             (66U)
#define CSL_MAIN_LPSC_MAIN_C7DSP0_CORE                                                             (67U)
#define CSL_MAIN_LPSC_MAIN_C7DSP0_PBIST                                                            (68U)
#define CSL_MAIN_LPSC_MAIN_C7DSP0_COMMON                                                           (69U)
#define CSL_MAIN_LPSC_MAIN_VPAC                                                                    (70U)
#define CSL_MAIN_LPSC_MAIN_VPAC_PBIST                                                              (71U)
#define CSL_MAIN_LPSC_MAIN_EMIF_LOCAL                                                              (72U)
#define CSL_MAIN_LPSC_MAIN_EMIF_CFG_ISO                                                            (73U)
#define CSL_MAIN_LPSC_MAIN_EMIF_DATA_ISO                                                           (74U)
#define CSL_MAIN_LPSC_MAIN_PCIE0                                                                   (75U)
#define CSL_MAIN_LPSC_MAIN_C7DSP1_CORE                                                             (76U)
#define CSL_MAIN_LPSC_MAIN_C7DSP1_PBIST                                                            (77U)
#define CSL_MAIN_LPSC_MAIN_C7DSP1_COMMON                                                           (78U)
#define CSL_MAIN_LPSC_MAIN_MCUSS0_CORE0                                                            (79U)
#define CSL_MAIN_LPSC_MAIN_MCUSS0_PBIST                                                            (80U)
#define CSL_MAIN_LPSC_MAIN_SRAM0_MSRAM                                                             (81U)
#define CSL_MAIN_LPSC_MAIN_SRAM0_PBIST                                                             (82U)
#define CSL_MAIN_LPSC_MAIN_SRAM1_MSRAM                                                             (83U)
#define CSL_MAIN_LPSC_MAIN_SRAM1_PBIST                                                             (84U)
#define CSL_MAIN_LPSC_PDRSVD0_RSVD0                                                                (85U)
#define CSL_MAIN_LPSC_PDRSVD0_RSVD1                                                                (86U)
#define CSL_MAIN_LPSC_PDRSVD0_RSVD2                                                                (87U)
#define CSL_MAIN_LPSC_PDRSVD1_RSVD0                                                                (88U)
#define CSL_MAIN_LPSC_RSVD1_RSVD1                                                                  (89U)
#define CSL_MAIN_LPSC_RSVD1_RSVD2                                                                  (90U)
#define CSL_MAIN_LPSC_MAIN_DSS0                                                                    (91U)
#define CSL_MAIN_LPSC_MAIN_DSS1                                                                    (92U)
#define CSL_MAIN_LPSC_MAIN_DSS_DSI0                                                                (93U)
#define CSL_MAIN_LPSC_MAIN_OLDI0                                                                   (94U)
#define CSL_MAIN_LPSC_MAIN_OLDI1                                                                   (95U)
/*
*  WKUP LPSC
*/

#define CSL_WKUP_LPSC_MCU_ALWAYSON                                                                 (0U)
#define CSL_WKUP_LPSC_MAIN2MCU_ISO                                                                 (1U)
#define CSL_WKUP_LPSC_DM2MCU_ISO                                                                   (2U)
#define CSL_WKUP_LPSC_DM2SAFE_ISO                                                                  (3U)
#define CSL_WKUP_LPSC_MCU2DM_ISO                                                                   (4U)
#define CSL_WKUP_LPSC_MCU_TEST                                                                     (5U)
#define CSL_WKUP_LPSC_MCU_R5                                                                       (6U)
#define CSL_WKUP_LPSC_MCU_MCANSS_0                                                                 (7U)
#define CSL_WKUP_LPSC_MCU_MCANSS_1                                                                 (8U)
#define CSL_WKUP_LPSC_MCU_COMMON                                                                   (9U)
#define CSL_WKUP_LPSC_MCU_PBIST                                                                    (10U)

#ifdef __cplusplus
}
#endif
#endif /* CSL_SOC_PSC_H_ */

