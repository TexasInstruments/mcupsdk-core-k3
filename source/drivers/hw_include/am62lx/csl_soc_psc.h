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
*  WKUP PD
*/

#define CSL_WKUP_GP_CORE_CTL                                                                       (0U)
#define CSL_WKUP_PD_CRYPTO                                                                         (1U)
#define CSL_WKUP_PD_DDR                                                                            (2U)
#define CSL_WKUP_PD_MAINIP                                                                         (3U)
#define CSL_WKUP_PD_MPU_CLST0                                                                      (4U)
#define CSL_WKUP_PD_MPU_CLST0_CORE0                                                                (5U)
#define CSL_WKUP_PD_MPU_CLST0_CORE1                                                                (6U)
#define CSL_WKUP_PD_MPU_CLST0_CORE2                                                                (7U)
#define CSL_WKUP_PD_MPU_CLST0_CORE3                                                                (8U)
#define CSL_WKUP_PD_PER                                                                            (9U)
#define CSL_WKUP_PD_MCUSS0                                                                         (10U)
#define CSL_WKUP_PD_C6DSP                                                                          (11U)
#define CSL_WKUP_PD_ICSS                                                                           (12U)
#define CSL_WKUP_PD_PRUSS                                                                          (13U)
#define CSL_WKUP_PD_ISP                                                                            (14U)
#define CSL_WKUP_PD_DLA                                                                            (15U)
#define CSL_WKUP_PD_ENCODE                                                                         (16U)
#define CSL_WKUP_PD_DECODE                                                                         (17U)
#define CSL_WKUP_PD_GPUCORE                                                                        (18U)
#define CSL_WKUP_PD_GPUCTRL                                                                        (19U)
#define CSL_WKUP_PD_RSVD0                                                                          (20U)
#define CSL_WKUP_PD_RSVD1                                                                          (21U)
#define CSL_WKUP_PD_RSVD2                                                                          (22U)
#define CSL_WKUP_PD_RSVD3                                                                          (23U)
/*
* LPSC Modules:
*/

/*
*  WKUP LPSC
*/

#define CSL_WKUP_LPSC_MAIN_GP_ALWAYSON                                                             (0U)
#define CSL_WKUP_LPSC_MAIN_GP_TEST                                                                 (1U)
#define CSL_WKUP_LPSC_MAIN_GP_PBIST0                                                               (2U)
#define CSL_WKUP_LPSC_MAIN_GP_ISO0_N                                                               (3U)
#define CSL_WKUP_LPSC_MAIN_GP_ISO1_N                                                               (4U)
#define CSL_WKUP_LPSC_MAIN_GP_TIFS                                                                 (5U)
#define CSL_WKUP_LPSC_MAIN_GP_DPHY_RX0                                                             (6U)
#define CSL_WKUP_LPSC_MAIN_GP_USB0                                                                 (7U)
#define CSL_WKUP_LPSC_MAIN_GP_USB0_ISO_N                                                           (8U)
#define CSL_WKUP_LPSC_MAIN_GP_USB1                                                                 (9U)
#define CSL_WKUP_LPSC_MAIN_GP_USB1_ISO_N                                                           (10U)
#define CSL_WKUP_LPSC_MAIN_GP_DPHY_TX                                                              (11U)
#define CSL_WKUP_LPSC_GP_RSVD0                                                                     (12U)
#define CSL_WKUP_LPSC_GP_RSVD1                                                                     (13U)
#define CSL_WKUP_LPSC_GP_RSVD2                                                                     (14U)
#define CSL_WKUP_LPSC_GP_RSVD3                                                                     (15U)
#define CSL_WKUP_LPSC_GP_RSVD4                                                                     (16U)
#define CSL_WKUP_LPSC_GP_RSVD5                                                                     (17U)
#define CSL_WKUP_LPSC_MAIN_GP_WKPERI                                                               (18U)
#define CSL_WKUP_LPSC_MAIN_CRYPTO                                                                  (19U)
#define CSL_WKUP_LPSC_MAIN_CRYPTO_RSVD                                                             (20U)
#define CSL_WKUP_LPSC_MAIN_DDR_LOCAL                                                               (21U)
#define CSL_WKUP_LPSC_MAIN_DDR_CFG_ISO_N                                                           (22U)
#define CSL_WKUP_LPSC_MAIN_DDR_DATA_ISO_N                                                          (23U)
#define CSL_WKUP_LPSC_MAINIP_COMMON                                                                (24U)
#define CSL_WKUP_LPSC_MAINIP_DSS                                                                   (25U)
#define CSL_WKUP_LPSC_MAINIP_DSI                                                                   (26U)
#define CSL_WKUP_LPSC_MAINIP_EMMC8B                                                                (27U)
#define CSL_WKUP_LPSC_MAINIP_EMMC4B0                                                               (28U)
#define CSL_WKUP_LPSC_MAINIP_EMMC4B1                                                               (29U)
#define CSL_WKUP_LPSC_MAINIP_CPSW                                                                  (30U)
#define CSL_WKUP_LPSC_MAINIP_CSI_RX0                                                               (31U)
#define CSL_WKUP_LPSC_MAINIP_GIC                                                                   (32U)
#define CSL_WKUP_LPSC_MAINIP_PBIST                                                                 (33U)
#define CSL_WKUP_LPSC_MAINIP_RSVD0                                                                 (34U)
#define CSL_WKUP_LPSC_MAINIP_RSVD1                                                                 (35U)
#define CSL_WKUP_LPSC_MAINIP_RSVD2                                                                 (36U)
#define CSL_WKUP_LPSC_MAINIP_RSVD3                                                                 (37U)
#define CSL_WKUP_LPSC_MAIN_MPU_CLST0                                                               (38U)
#define CSL_WKUP_LPSC_MAIN_MPU_CLST0_PBIST                                                         (39U)
#define CSL_WKUP_LPSC_MAIN_MPU_CLST0_CORE0                                                         (40U)
#define CSL_WKUP_LPSC_MAIN_MPU_CLST0_CORE1                                                         (41U)
#define CSL_WKUP_LPSC_MAIN_MPU_CLST0_CORE2                                                         (42U)
#define CSL_WKUP_LPSC_MAIN_MPU_CLST0_CORE3                                                         (43U)
#define CSL_WKUP_LPSC_MAIN_PER_COMMON                                                              (44U)
#define CSL_WKUP_LPSC_MAIN_PER_MCASP0                                                              (45U)
#define CSL_WKUP_LPSC_MAIN_PER_MCASP1                                                              (46U)
#define CSL_WKUP_LPSC_MAIN_PER_MCASP2                                                              (47U)
#define CSL_WKUP_LPSC_MAIN_PER_XSPI                                                                (48U)
#define CSL_WKUP_LPSC_MAIN_PER_MCAN0                                                               (49U)
#define CSL_WKUP_LPSC_MAIN_PER_MCAN1                                                               (50U)
#define CSL_WKUP_LPSC_MAIN_PER_MCAN2                                                               (51U)
#define CSL_WKUP_LPSC_MAIN_PER_GPMC                                                                (52U)
#define CSL_WKUP_LPSC_MAIN_PER_ADC                                                                 (53U)
#define CSL_WKUP_LPSC_MAIN_PER_RSVD0                                                               (54U)
#define CSL_WKUP_LPSC_MAIN_DEBUGSS                                                                 (55U)
#define CSL_WKUP_LPSC_MAIN_MCUSS0_CORE0                                                            (56U)
#define CSL_WKUP_LPSC_MAIN_MCUSS0_PBIST                                                            (57U)
#define CSL_WKUP_LPSC_MAIN_C6DSP_CORE                                                              (58U)
#define CSL_WKUP_LPSC_MAIN_C6DSP_PBIST                                                             (59U)
#define CSL_WKUP_LPSC_MAIN_ICSS                                                                    (60U)
#define CSL_WKUP_LPSC_MAIN_ICSS_RSVD                                                               (61U)
#define CSL_WKUP_LPSC_MAIN_PRUSS                                                                   (62U)
#define CSL_WKUP_LPSC_MAIN_PRUSS_RSVD                                                              (63U)
#define CSL_WKUP_LPSC_MAIN_ISP                                                                     (64U)
#define CSL_WKUP_LPSC_MAIN_ISP_PBIST                                                               (65U)
#define CSL_WKUP_LPSC_MAIN_DLA_COMMON                                                              (66U)
#define CSL_WKUP_LPSC_MAIN_DLA_PBIST                                                               (67U)
#define CSL_WKUP_LPSC_MAIN_DLA_CORE                                                                (68U)
#define CSL_WKUP_LPSC_MAIN_ENCODE                                                                  (69U)
#define CSL_WKUP_LPSC_MAIN_ENCODE_PBIST                                                            (70U)
#define CSL_WKUP_LPSC_MAIN_DECODE                                                                  (71U)
#define CSL_WKUP_LPSC_MAIN_DECODE_PBIST                                                            (72U)
#define CSL_WKUP_LPSC_MAIN_GPUCORE                                                                 (73U)
#define CSL_WKUP_LPSC_MAIN_GPUCTRL_COMMON                                                          (74U)
#define CSL_WKUP_LPSC_MAIN_GPUCTRL_PBIST                                                           (75U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD0_RSVD0                                                           (76U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD0_RSVD1                                                           (77U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD0_RSVD2                                                           (78U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD1_RSVD0                                                           (79U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD1_RSVD1                                                           (80U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD1_RSVD2                                                           (81U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD2_RSVD0                                                           (82U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD2_RSVD1                                                           (83U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD2_RSVD2                                                           (84U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD3_RSVD0                                                           (85U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD3_RSVD1                                                           (86U)
#define CSL_WKUP_LPSC_MAIN_PDRSVD3_RSVD2                                                           (87U)

#ifdef __cplusplus
}
#endif
#endif /* CSL_SOC_PSC_H_ */
