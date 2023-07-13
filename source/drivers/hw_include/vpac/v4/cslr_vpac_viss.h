/********************************************************************
 * Copyright (C) 2023 Texas Instruments Incorporated.
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
 *  Name        : cslr_vpac_viss.h
*/
#ifndef CSLR_VPAC_VISS_H_
#define CSLR_VPAC_VISS_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_VPAC_VISS_ECC_AGGR_REGS_BASE                                       (0x00000000U)
#define CSL_VPAC_VISS_FLEXCC_C8G8_REGS_BASE                                    (0x00012800U)
#define CSL_VPAC_VISS_FLEXCC_C8G8_REGS_1_BASE                                  (0x00072800U)
#define CSL_VPAC_VISS_FLEXCC_CFG_REGS_BASE                                     (0x00010000U)
#define CSL_VPAC_VISS_FLEXCC_CFG_REGS_1_BASE                                   (0x00070000U)
#define CSL_VPAC_VISS_FLEXCC_CONTRASTC1_REGS_BASE                              (0x00010800U)
#define CSL_VPAC_VISS_FLEXCC_CONTRASTC1_REGS_1_BASE                            (0x00070800U)
#define CSL_VPAC_VISS_FLEXCC_CONTRASTC2_REGS_BASE                              (0x00011000U)
#define CSL_VPAC_VISS_FLEXCC_CONTRASTC2_REGS_1_BASE                            (0x00071000U)
#define CSL_VPAC_VISS_FLEXCC_CONTRASTC3_REGS_BASE                              (0x00011800U)
#define CSL_VPAC_VISS_FLEXCC_CONTRASTC3_REGS_1_BASE                            (0x00071800U)
#define CSL_VPAC_VISS_FLEXCC_HIST_REGS_BASE                                    (0x00013800U)
#define CSL_VPAC_VISS_FLEXCC_HIST_REGS_1_BASE                                  (0x00073800U)
#define CSL_VPAC_VISS_FLEXCC_LINE_REGS_BASE                                    (0x00018000U)
#define CSL_VPAC_VISS_FLEXCC_LINE_REGS_1_BASE                                  (0x00078000U)
#define CSL_VPAC_VISS_FLEXCC_S8B8_REGS_BASE                                    (0x00013000U)
#define CSL_VPAC_VISS_FLEXCC_S8B8_REGS_1_BASE                                  (0x00073000U)
#define CSL_VPAC_VISS_FLEXCC_Y8R8_REGS_BASE                                    (0x00012000U)
#define CSL_VPAC_VISS_FLEXCC_Y8R8_REGS_1_BASE                                  (0x00072000U)
#define CSL_VPAC_VISS_FLEXCFA_DLUTS_REGS_BASE                                  (0x00058000U)
#define CSL_VPAC_VISS_FLEXCFA_DLUTS_REGS_1_BASE                                (0x0005C000U)
#define CSL_VPAC_VISS_FLEXCFA_REGS_BASE                                        (0x00008000U)
#define CSL_VPAC_VISS_FLEXCFA_REGS_1_BASE                                      (0x00068000U)
#define CSL_VPAC_VISS_FLEXEE_REGS_BASE                                         (0x00050000U)
#define CSL_VPAC_VISS_FLEXEE_REGS_1_BASE                                       (0x00060000U)
#define CSL_VPAC_VISS_GLBCE_CFG_REGS_BASE                                      (0x00003800U)
#define CSL_VPAC_VISS_GLBCE_STATMEM_REGS_BASE                                  (0x00004000U)
#define CSL_VPAC_VISS_LSE_REGS_BASE                                            (0x00000400U)
#define CSL_VPAC_VISS_NSF4V_MEM_REGS_BASE                                      (0x00044000U)
#define CSL_VPAC_VISS_NSF4V_REGS_BASE                                          (0x00040000U)
#define CSL_VPAC_VISS_RAWFE_CFG_REGS_BASE                                      (0x00020000U)
#define CSL_VPAC_VISS_RAWFE_DPC_LRAM_REGS_BASE                                 (0x00024000U)
#define CSL_VPAC_VISS_RAWFE_DPC_LUT_RAM_REGS_BASE                              (0x00023000U)
#define CSL_VPAC_VISS_RAWFE_H3A_ARAM_REGS_BASE                                 (0x00030000U)
#define CSL_VPAC_VISS_RAWFE_H3A_CFG_REGS_BASE                                  (0x00020400U)
#define CSL_VPAC_VISS_RAWFE_H3A_LRAM_REGS_BASE                                 (0x00032000U)
#define CSL_VPAC_VISS_RAWFE_H3A_LUT_RAM_REGS_BASE                              (0x00022800U)
#define CSL_VPAC_VISS_RAWFE_LSC_LUT_RAM_REGS_BASE                              (0x00028000U)
#define CSL_VPAC_VISS_RAWFE_PWL_LUT1_RAM_REGS_BASE                             (0x00021800U)
#define CSL_VPAC_VISS_RAWFE_PWL_LUT2_RAM_REGS_BASE                             (0x00021000U)
#define CSL_VPAC_VISS_RAWFE_PWL_LUT3_RAM_REGS_BASE                             (0x00020800U)
#define CSL_VPAC_VISS_RAWFE_WDR_LUT_RAM_REGS_BASE                              (0x00022000U)
#define CSL_VPAC_VISS_RAWHIST_LUT_REGS_BASE                                    (0x00041000U)
#define CSL_VPAC_VISS_RAWHIST_DATA_REGS_BASE                                   (0x00040800U)
#define CSL_VPAC_VISS_CAC_LUT_REGS_BASE                                        (0x00082000U)
#define CSL_VPAC_VISS_CAC_REGS_BASE                                            (0x00080000U)
#define CSL_VPAC_VISS_CAC_LINEMEM_REGS_BASE                                    (0x00084000U)
#define CSL_VPAC_VISS_PCID_REGS_BASE                                           (0x00088000U)
#define CSL_VPAC_VISS_PCID_IRLUT_REGS_BASE                                     (0x00088800U)
#define CSL_VPAC_VISS_VISS_TOP_REGS_BASE                                       (0x00000000U)


#ifdef __cplusplus
}
#endif
#endif
