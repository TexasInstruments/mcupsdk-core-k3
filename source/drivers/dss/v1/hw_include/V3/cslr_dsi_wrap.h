/********************************************************************
 * Copyright (C) 2018-2026 Texas Instruments Incorporated.
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
 *  Name        : cslr_dsi_wrap.h
*/
#ifndef CSLR_DSI_WRAP_H_
#define CSLR_DSI_WRAP_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : MMR Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t REVISION;                  /* revision */
    volatile uint32_t DPI_CONTROL;               /* DPI Control */
    volatile uint32_t DSC_CONTROL;               /* DSC Control */
    volatile uint32_t DPI_SECURE;                /* DPI Secure */
    volatile uint32_t DSI_0_ASF_STATUS;          /* DSI 0 ASF status */
} CSL_dsi_wrapRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_DSI_WRAP_REVISION                                                  (0x00000000U)
#define CSL_DSI_WRAP_DPI_CONTROL                                               (0x00000004U)
#define CSL_DSI_WRAP_DSC_CONTROL                                               (0x00000008U)
#define CSL_DSI_WRAP_DPI_SECURE                                                (0x0000000CU)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS                                          (0x00000010U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* REVISION */

#define CSL_DSI_WRAP_REVISION_REVMIN_MASK                                      (0x0000003FU)
#define CSL_DSI_WRAP_REVISION_REVMIN_SHIFT                                     (0x00000000U)
#define CSL_DSI_WRAP_REVISION_REVMIN_MAX                                       (0x0000003FU)

#define CSL_DSI_WRAP_REVISION_CUSTOM_MASK                                      (0x000000C0U)
#define CSL_DSI_WRAP_REVISION_CUSTOM_SHIFT                                     (0x00000006U)
#define CSL_DSI_WRAP_REVISION_CUSTOM_MAX                                       (0x00000003U)

#define CSL_DSI_WRAP_REVISION_REVMAJOR_MASK                                    (0x00000700U)
#define CSL_DSI_WRAP_REVISION_REVMAJOR_SHIFT                                   (0x00000008U)
#define CSL_DSI_WRAP_REVISION_REVMAJOR_MAX                                     (0x00000007U)

#define CSL_DSI_WRAP_REVISION_REVRTL_MASK                                      (0x0000F800U)
#define CSL_DSI_WRAP_REVISION_REVRTL_SHIFT                                     (0x0000000BU)
#define CSL_DSI_WRAP_REVISION_REVRTL_MAX                                       (0x0000001FU)

#define CSL_DSI_WRAP_REVISION_MODID_MASK                                       (0xFFFF0000U)
#define CSL_DSI_WRAP_REVISION_MODID_SHIFT                                      (0x00000010U)
#define CSL_DSI_WRAP_REVISION_MODID_MAX                                        (0x0000FFFFU)

/* DPI_CONTROL */

#define CSL_DSI_WRAP_DPI_CONTROL_DPI_0_EN_MASK                                 (0x00000001U)
#define CSL_DSI_WRAP_DPI_CONTROL_DPI_0_EN_SHIFT                                (0x00000000U)
#define CSL_DSI_WRAP_DPI_CONTROL_DPI_0_EN_MAX                                  (0x00000001U)

#define CSL_DSI_WRAP_DPI_CONTROL_DPI_0_EN_VAL_DISABLE                          (0x0U)
#define CSL_DSI_WRAP_DPI_CONTROL_DPI_0_EN_VAL_ENABLE                           (0x1U)

#define CSL_DSI_WRAP_DPI_CONTROL_DSI2_MUX_SEL_MASK                             (0x00000010U)
#define CSL_DSI_WRAP_DPI_CONTROL_DSI2_MUX_SEL_SHIFT                            (0x00000004U)
#define CSL_DSI_WRAP_DPI_CONTROL_DSI2_MUX_SEL_MAX                              (0x00000001U)

#define CSL_DSI_WRAP_DPI_CONTROL_DSI2_MUX_SEL_VAL_DPI1SEL                      (0x0U)
#define CSL_DSI_WRAP_DPI_CONTROL_DSI2_MUX_SEL_VAL_DPI2SEL                      (0x1U)

#define CSL_DSI_WRAP_DPI_CONTROL_RESERVED0_MASK                                (0x00000100U)
#define CSL_DSI_WRAP_DPI_CONTROL_RESERVED0_SHIFT                               (0x00000008U)
#define CSL_DSI_WRAP_DPI_CONTROL_RESERVED0_MAX                                 (0x00000001U)

/* DSC_CONTROL */

/* DPI_SECURE */

#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_MASK                              (0x00000001U)
#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_SHIFT                             (0x00000000U)
#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_MAX                               (0x00000001U)

#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_VAL_NONSECURE                     (0x0U)
#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_VAL_SECURE                        (0x1U)

#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_VIOLATION_MASK                    (0x00000002U)
#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_VIOLATION_SHIFT                   (0x00000001U)
#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_VIOLATION_MAX                     (0x00000001U)

#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_VIOLATION_VAL_SECOK               (0x0U)
#define CSL_DSI_WRAP_DPI_SECURE_DPI_0_SECURE_VIOLATION_VAL_SECERR              (0x1U)

/* DSI_0_ASF_STATUS */

#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_SRAM_CORR_ERR_MASK                       (0x00000001U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_SRAM_CORR_ERR_SHIFT                      (0x00000000U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_SRAM_CORR_ERR_MAX                        (0x00000001U)

#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_SRAM_UNCORR_ERR_MASK                     (0x00000002U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_SRAM_UNCORR_ERR_SHIFT                    (0x00000001U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_SRAM_UNCORR_ERR_MAX                      (0x00000001U)

#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_DAP_ERR_MASK                             (0x00000004U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_DAP_ERR_SHIFT                            (0x00000002U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_DAP_ERR_MAX                              (0x00000001U)

#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_CSR_ERR_MASK                             (0x00000008U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_CSR_ERR_SHIFT                            (0x00000003U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_CSR_ERR_MAX                              (0x00000001U)

#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_TRANS_TO_ERR_MASK                        (0x00000010U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_TRANS_TO_ERR_SHIFT                       (0x00000004U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_TRANS_TO_ERR_MAX                         (0x00000001U)

#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_PROTOCOL_ERR_MASK                        (0x00000020U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_PROTOCOL_ERR_SHIFT                       (0x00000005U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_PROTOCOL_ERR_MAX                         (0x00000001U)

#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_INTEGRITY_ERR_MASK                       (0x00000040U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_INTEGRITY_ERR_SHIFT                      (0x00000006U)
#define CSL_DSI_WRAP_DSI_0_ASF_STATUS_INTEGRITY_ERR_MAX                        (0x00000001U)

#ifdef __cplusplus
}
#endif
#endif
