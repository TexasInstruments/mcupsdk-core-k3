/********************************************************************
 * Copyright (C) 2017-25 Texas Instruments Incorporated.
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
 *  Name        : cslr_csi_rx_if.h
*/
#ifndef CSLR_CSI_RX_IF_H_
#define CSLR_CSI_RX_IF_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <drivers/hw_include/cslr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t DMACNTX;                   /* DMA Channel Context */
    volatile uint32_t PSI_CFG0;                  /* psi configuration register0 */
    volatile uint32_t PSI_CFG1;                  /* psi configuration register1 */
    volatile uint8_t  Resv_32[20];
} CSL_csi_rx_ifRegs_cntx_cntl;


typedef struct {
    volatile uint32_t CSIRX_ID;
    volatile uint8_t  Resv_8[4];
    volatile uint32_t VP0;                       /* Video Port 0 config */
    volatile uint32_t VP1;                       /* Video Port 1 config */
    volatile uint32_t CNTL;                      /* control register for csi rx wrapper */
    volatile uint8_t  Resv_32[12];
    CSL_csi_rx_ifRegs_cntx_cntl CNTX_CNTL[32];
} CSL_csi_rx_ifRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_CSI_RX_IF_CSIRX_ID                                                 (0x00000000U)
#define CSL_CSI_RX_IF_VP0                                                      (0x00000008U)
#define CSL_CSI_RX_IF_VP1                                                      (0x0000000CU)
#define CSL_CSI_RX_IF_CNTL                                                     (0x00000010U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX(CNTX_CNTL)                             (0x00000020U+((CNTX_CNTL)*0x20U))
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG0(CNTX_CNTL)                            (0x00000024U+((CNTX_CNTL)*0x20U))
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG1(CNTX_CNTL)                            (0x00000028U+((CNTX_CNTL)*0x20U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* DMACNTX */

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_EN_CFG_MASK                            (0x80000000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_EN_CFG_SHIFT                           (0x0000001FU)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_EN_CFG_MAX                             (0x00000001U)

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_RSV0_MASK                              (0x20000000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_RSV0_SHIFT                             (0x0000001DU)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_RSV0_MAX                               (0x00000001U)

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_RSV1_MASK                              (0x10000000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_RSV1_SHIFT                             (0x0000001CU)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_RSV1_MAX                               (0x00000001U)

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_YUV422_MODE_CFG_MASK                   (0x0C000000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_YUV422_MODE_CFG_SHIFT                  (0x0000001AU)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_YUV422_MODE_CFG_MAX                    (0x00000003U)

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_RSV2_MASK                              (0x02000000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_RSV2_SHIFT                             (0x00000019U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_RSV2_MAX                               (0x00000001U)

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_DUAL_PCK_CFG_MASK                      (0x01000000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_DUAL_PCK_CFG_SHIFT                     (0x00000018U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_DUAL_PCK_CFG_MAX                       (0x00000001U)

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_SIZE_CFG_MASK                          (0x00300000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_SIZE_CFG_SHIFT                         (0x00000014U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_SIZE_CFG_MAX                           (0x00000003U)

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_PCK12_CFG_MASK                         (0x00040000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_PCK12_CFG_SHIFT                        (0x00000012U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_PCK12_CFG_MAX                          (0x00000001U)

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_VIRTCH_CFG_MASK                        (0x000003C0U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_VIRTCH_CFG_SHIFT                       (0x00000006U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_VIRTCH_CFG_MAX                         (0x0000000FU)

#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_DATTYP_CFG_MASK                        (0x0000003FU)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_DATTYP_CFG_SHIFT                       (0x00000000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_DMACNTX_DATTYP_CFG_MAX                         (0x0000003FU)

/* PSI_CFG0 */

#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG0_SRC_TAG_MASK                          (0x0000FFFFU)
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG0_SRC_TAG_SHIFT                         (0x00000000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG0_SRC_TAG_MAX                           (0x0000FFFFU)

#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG0_DST_TAG_MASK                          (0xFFFF0000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG0_DST_TAG_SHIFT                         (0x00000010U)
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG0_DST_TAG_MAX                           (0x0000FFFFU)

/* PSI_CFG1 */

#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG1_PKT_TYPE_MASK                         (0x0000001FU)
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG1_PKT_TYPE_SHIFT                        (0x00000000U)
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG1_PKT_TYPE_MAX                          (0x0000001FU)

#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG1_PS_FLAGS_MASK                         (0x00000F00U)
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG1_PS_FLAGS_SHIFT                        (0x00000008U)
#define CSL_CSI_RX_IF_CNTX_CNTL_PSI_CFG1_PS_FLAGS_MAX                          (0x0000000FU)

/* CSIRX_ID */

#define CSL_CSI_RX_IF_CSIRX_ID_SCHEME_MASK                                     (0xC0000000U)
#define CSL_CSI_RX_IF_CSIRX_ID_SCHEME_SHIFT                                    (0x0000001EU)
#define CSL_CSI_RX_IF_CSIRX_ID_SCHEME_MAX                                      (0x00000003U)

#define CSL_CSI_RX_IF_CSIRX_ID_BU_MASK                                         (0x30000000U)
#define CSL_CSI_RX_IF_CSIRX_ID_BU_SHIFT                                        (0x0000001CU)
#define CSL_CSI_RX_IF_CSIRX_ID_BU_MAX                                          (0x00000003U)

#define CSL_CSI_RX_IF_CSIRX_ID_FUNC_MASK                                       (0x0FFF0000U)
#define CSL_CSI_RX_IF_CSIRX_ID_FUNC_SHIFT                                      (0x00000010U)
#define CSL_CSI_RX_IF_CSIRX_ID_FUNC_MAX                                        (0x00000FFFU)

#define CSL_CSI_RX_IF_CSIRX_ID_RTLVER_MASK                                     (0x0000F800U)
#define CSL_CSI_RX_IF_CSIRX_ID_RTLVER_SHIFT                                    (0x0000000BU)
#define CSL_CSI_RX_IF_CSIRX_ID_RTLVER_MAX                                      (0x0000001FU)

#define CSL_CSI_RX_IF_CSIRX_ID_MAJREV_MASK                                     (0x00000700U)
#define CSL_CSI_RX_IF_CSIRX_ID_MAJREV_SHIFT                                    (0x00000008U)
#define CSL_CSI_RX_IF_CSIRX_ID_MAJREV_MAX                                      (0x00000007U)

#define CSL_CSI_RX_IF_CSIRX_ID_CUSTOM_MASK                                     (0x000000C0U)
#define CSL_CSI_RX_IF_CSIRX_ID_CUSTOM_SHIFT                                    (0x00000006U)
#define CSL_CSI_RX_IF_CSIRX_ID_CUSTOM_MAX                                      (0x00000003U)

#define CSL_CSI_RX_IF_CSIRX_ID_MINREV_MASK                                     (0x0000003FU)
#define CSL_CSI_RX_IF_CSIRX_ID_MINREV_SHIFT                                    (0x00000000U)
#define CSL_CSI_RX_IF_CSIRX_ID_MINREV_MAX                                      (0x0000003FU)

/* VP0 */

#define CSL_CSI_RX_IF_VP0_EN_CFG_MASK                                          (0x80000000U)
#define CSL_CSI_RX_IF_VP0_EN_CFG_SHIFT                                         (0x0000001FU)
#define CSL_CSI_RX_IF_VP0_EN_CFG_MAX                                           (0x00000001U)

#define CSL_CSI_RX_IF_VP0_IH_CFG_MASK                                          (0x1FFF0000U)
#define CSL_CSI_RX_IF_VP0_IH_CFG_SHIFT                                         (0x00000010U)
#define CSL_CSI_RX_IF_VP0_IH_CFG_MAX                                           (0x00001FFFU)

#define CSL_CSI_RX_IF_VP0_IW_CFG_MASK                                          (0x00001FFFU)
#define CSL_CSI_RX_IF_VP0_IW_CFG_SHIFT                                         (0x00000000U)
#define CSL_CSI_RX_IF_VP0_IW_CFG_MAX                                           (0x00001FFFU)

/* VP1 */

#define CSL_CSI_RX_IF_VP1_EN_CFG_MASK                                          (0x80000000U)
#define CSL_CSI_RX_IF_VP1_EN_CFG_SHIFT                                         (0x0000001FU)
#define CSL_CSI_RX_IF_VP1_EN_CFG_MAX                                           (0x00000001U)

#define CSL_CSI_RX_IF_VP1_IH_CFG_MASK                                          (0x1FFF0000U)
#define CSL_CSI_RX_IF_VP1_IH_CFG_SHIFT                                         (0x00000010U)
#define CSL_CSI_RX_IF_VP1_IH_CFG_MAX                                           (0x00001FFFU)

#define CSL_CSI_RX_IF_VP1_IW_CFG_MASK                                          (0x00001FFFU)
#define CSL_CSI_RX_IF_VP1_IW_CFG_SHIFT                                         (0x00000000U)
#define CSL_CSI_RX_IF_VP1_IW_CFG_MAX                                           (0x00001FFFU)

/* CNTL */

#define CSL_CSI_RX_IF_CNTL_PIXEL_RESET_MASK                                    (0x00000001U)
#define CSL_CSI_RX_IF_CNTL_PIXEL_RESET_SHIFT                                   (0x00000000U)
#define CSL_CSI_RX_IF_CNTL_PIXEL_RESET_MAX                                     (0x00000001U)

#define CSL_CSI_RX_IF_CNTL_STREAM0_IDLE_MASK                                   (0x00000100U)
#define CSL_CSI_RX_IF_CNTL_STREAM0_IDLE_SHIFT                                  (0x00000008U)
#define CSL_CSI_RX_IF_CNTL_STREAM0_IDLE_MAX                                    (0x00000001U)

#define CSL_CSI_RX_IF_CNTL_STREAM1_IDLE_MASK                                   (0x00000200U)
#define CSL_CSI_RX_IF_CNTL_STREAM1_IDLE_SHIFT                                  (0x00000009U)
#define CSL_CSI_RX_IF_CNTL_STREAM1_IDLE_MAX                                    (0x00000001U)

#define CSL_CSI_RX_IF_CNTL_STREAM2_IDLE_MASK                                   (0x00000400U)
#define CSL_CSI_RX_IF_CNTL_STREAM2_IDLE_SHIFT                                  (0x0000000AU)
#define CSL_CSI_RX_IF_CNTL_STREAM2_IDLE_MAX                                    (0x00000001U)

#define CSL_CSI_RX_IF_CNTL_STREAM3_IDLE_MASK                                   (0x00000800U)
#define CSL_CSI_RX_IF_CNTL_STREAM3_IDLE_SHIFT                                  (0x0000000BU)
#define CSL_CSI_RX_IF_CNTL_STREAM3_IDLE_MAX                                    (0x00000001U)

#ifdef __cplusplus
}
#endif
#endif
