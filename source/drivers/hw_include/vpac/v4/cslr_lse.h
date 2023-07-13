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
 *  Name        : cslr_lse.h
*/
#ifndef CSLR_LSE_H_
#define CSLR_LSE_H_

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
    volatile uint32_t CFG;                       /* SRC[a]_CFG */
    volatile uint32_t VPIN_CFG;                  /* SRC[a]_VPIN_CFG */
    volatile uint32_t FRAME_SIZE;                /* SRC[a]_FRAME_SIZE */
    volatile uint32_t BUF_ATTR;                  /* SRC[a]_BUF_ATTR */
    volatile uint32_t BUF_BA[4];                 /* SRC[a]_BUF_BA[b] */
} CSL_lseRegs_src;


typedef struct {
    volatile uint32_t BUF_CFG;                   /* DST[a]_BUF_CFG */
    volatile uint32_t BUF_ATTR0;                 /* DST[a]_BUF_ATTR0 */
    volatile uint32_t BUF_ATTR1;                 /* DST[a]_BUF_ATTR1 */
    volatile uint32_t BUF_BA;                    /* DST[a]_BUF_BA */
} CSL_lseRegs_dst;


typedef struct {
    volatile uint32_t BUF_ATTR;                  /* H3A_BUF_ATTR */
    volatile uint8_t  Resv_8[4];
    volatile uint32_t BUF_BA;                    /* H3A_BUF_BA */
    volatile uint8_t  Resv_16[4];
} CSL_lseRegs_h3a;


typedef struct {
    volatile uint32_t ROW;                       /* row */
} CSL_lseRegs_common_cfg_;


typedef struct {
    volatile uint32_t STATUS_PARAM;              /* status_param */
    volatile uint32_t STATUS_ERROR;              /* status_error */
    volatile uint32_t STATUS_IDLE_MODE;          /* status_idle_mode */
    volatile uint32_t CFG_LSE;                   /* cfg_lse */
    CSL_lseRegs_src SRC[2];
    CSL_lseRegs_dst DST[10];
    CSL_lseRegs_h3a H3A;
    CSL_lseRegs_common_cfg_ COMMON_CFG_[3];
    volatile uint8_t  Resv_316[48];
    volatile uint32_t DST_COMMON_CFG;            /* dst_common_cfg */
    volatile uint32_t PSA_SIGNATURE[11];         /* psa_signature */
    volatile uint8_t  Resv_368[4];
    volatile uint32_t SRC0_CFG1;                 /* src0_cfg1 */
    volatile uint32_t SRC0_FRAME_SIZE1;          /* src0_frame_size1 */
    volatile uint32_t SRC0_CFG2;                 /* src0_cfg2 */
    volatile uint32_t SRC0_FRAME_SIZE2;          /* src0_frame_size2 */
    volatile uint32_t SRC0_CFG3;                 /* src0_cfg3 */
    volatile uint32_t SRC0_FRAME_SIZE3;          /* src0_frame_size3 */
    volatile uint8_t  Resv_400[8];
    volatile uint32_t SRC1_CFG1;                 /* src1_cfg1 */
    volatile uint32_t SRC1_FRAME_SIZE1;          /* src1_frame_size1 */
    volatile uint32_t SRC1_CFG2;                 /* src1_cfg2 */
    volatile uint32_t SRC1_FRAME_SIZE2;          /* src1_frame_size2 */
    volatile uint32_t SRC1_CFG3;                 /* src1_cfg3 */
    volatile uint32_t SRC1_FRAME_SIZE3;          /* src1_frame_size3 */
    volatile uint8_t  Resv_480[56];
    volatile uint32_t DBG[5];                    /* dbg */
} CSL_lseRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_LSE_STATUS_PARAM                                                   (0x00000000U)
#define CSL_LSE_STATUS_ERROR                                                   (0x00000004U)
#define CSL_LSE_STATUS_IDLE_MODE                                               (0x00000008U)
#define CSL_LSE_CFG_LSE                                                        (0x0000000CU)
#define CSL_LSE_SRC_CFG(SRC)                                                   (0x00000010U+((SRC)*0x20U))
#define CSL_LSE_SRC_VPIN_CFG(SRC)                                              (0x00000014U+((SRC)*0x20U))
#define CSL_LSE_SRC_FRAME_SIZE(SRC)                                            (0x00000018U+((SRC)*0x20U))
#define CSL_LSE_SRC_BUF_ATTR(SRC)                                              (0x0000001CU+((SRC)*0x20U))
#define CSL_LSE_SRC_BUF_BA(SRC,BUF_BA)                                         (0x00000020U+((SRC)*0x20U)+((BUF_BA)*0x4U))
#define CSL_LSE_DST_BUF_CFG(DST)                                               (0x00000050U+((DST)*0x10U))
#define CSL_LSE_DST_BUF_ATTR0(DST)                                             (0x00000054U+((DST)*0x10U))
#define CSL_LSE_DST_BUF_ATTR1(DST)                                             (0x00000058U+((DST)*0x10U))
#define CSL_LSE_DST_BUF_BA(DST)                                                (0x0000005CU+((DST)*0x10U))
#define CSL_LSE_H3A_BUF_ATTR                                                   (0x000000F0U)
#define CSL_LSE_H3A_BUF_BA                                                     (0x000000F8U)
#define CSL_LSE_COMMON_CFG__ROW(COMMON_CFG_)                                   (0x00000100U+((COMMON_CFG_)*0x4U))
#define CSL_LSE_DST_COMMON_CFG                                                 (0x0000013CU)
#define CSL_LSE_PSA_SIGNATURE(PSA_SIGNATURE)                                   (0x00000140U+((PSA_SIGNATURE)*0x4U))
#define CSL_LSE_SRC0_CFG1                                                      (0x00000170U)
#define CSL_LSE_SRC0_FRAME_SIZE1                                               (0x00000174U)
#define CSL_LSE_SRC0_CFG2                                                      (0x00000178U)
#define CSL_LSE_SRC0_FRAME_SIZE2                                               (0x0000017CU)
#define CSL_LSE_SRC0_CFG3                                                      (0x00000180U)
#define CSL_LSE_SRC0_FRAME_SIZE3                                               (0x00000184U)
#define CSL_LSE_SRC1_CFG1                                                      (0x00000190U)
#define CSL_LSE_SRC1_FRAME_SIZE1                                               (0x00000194U)
#define CSL_LSE_SRC1_CFG2                                                      (0x00000198U)
#define CSL_LSE_SRC1_FRAME_SIZE2                                               (0x0000019CU)
#define CSL_LSE_SRC1_CFG3                                                      (0x000001A0U)
#define CSL_LSE_SRC1_FRAME_SIZE3                                               (0x000001A4U)
#define CSL_LSE_DBG(DBG)                                                       (0x000001E0U+((DBG)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CFG */

#define CSL_LSE_SRC_CFG_VP_HBLNK_CNT_MASK                                      (0xFFC00000U)
#define CSL_LSE_SRC_CFG_VP_HBLNK_CNT_SHIFT                                     (0x00000016U)
#define CSL_LSE_SRC_CFG_VP_HBLNK_CNT_MAX                                       (0x000003FFU)

#define CSL_LSE_SRC_CFG_KERN_TPAD_SZ_MASK                                      (0x00380000U)
#define CSL_LSE_SRC_CFG_KERN_TPAD_SZ_SHIFT                                     (0x00000013U)
#define CSL_LSE_SRC_CFG_KERN_TPAD_SZ_MAX                                       (0x00000007U)

#define CSL_LSE_SRC_CFG_KERN_BPAD_SZ_MASK                                      (0x00070000U)
#define CSL_LSE_SRC_CFG_KERN_BPAD_SZ_SHIFT                                     (0x00000010U)
#define CSL_LSE_SRC_CFG_KERN_BPAD_SZ_MAX                                       (0x00000007U)

#define CSL_LSE_SRC_CFG_KERN_LN_OFFSET_MASK                                    (0x0000F000U)
#define CSL_LSE_SRC_CFG_KERN_LN_OFFSET_SHIFT                                   (0x0000000CU)
#define CSL_LSE_SRC_CFG_KERN_LN_OFFSET_MAX                                     (0x0000000FU)

#define CSL_LSE_SRC_CFG_KERN_SZ_HEIGHT_MASK                                    (0x00000F00U)
#define CSL_LSE_SRC_CFG_KERN_SZ_HEIGHT_SHIFT                                   (0x00000008U)
#define CSL_LSE_SRC_CFG_KERN_SZ_HEIGHT_MAX                                     (0x0000000FU)

#define CSL_LSE_SRC_CFG_SRC_LN_INC_2_MASK                                      (0x00000080U)
#define CSL_LSE_SRC_CFG_SRC_LN_INC_2_SHIFT                                     (0x00000007U)
#define CSL_LSE_SRC_CFG_SRC_LN_INC_2_MAX                                       (0x00000001U)

#define CSL_LSE_SRC_CFG_PIX_FMT_ALIGN_MASK                                     (0x00000010U)
#define CSL_LSE_SRC_CFG_PIX_FMT_ALIGN_SHIFT                                    (0x00000004U)
#define CSL_LSE_SRC_CFG_PIX_FMT_ALIGN_MAX                                      (0x00000001U)

#define CSL_LSE_SRC_CFG_PIX_FMT_CNTRSZ_MASK                                    (0x0000000CU)
#define CSL_LSE_SRC_CFG_PIX_FMT_CNTRSZ_SHIFT                                   (0x00000002U)
#define CSL_LSE_SRC_CFG_PIX_FMT_CNTRSZ_MAX                                     (0x00000003U)

#define CSL_LSE_SRC_CFG_PIX_FMT_PW_MASK                                        (0x00000003U)
#define CSL_LSE_SRC_CFG_PIX_FMT_PW_SHIFT                                       (0x00000000U)
#define CSL_LSE_SRC_CFG_PIX_FMT_PW_MAX                                         (0x00000003U)

/* VPIN_CFG */

#define CSL_LSE_SRC_VPIN_CFG_VP_PROTOCOL_CHK_MASK                              (0x00000010U)
#define CSL_LSE_SRC_VPIN_CFG_VP_PROTOCOL_CHK_SHIFT                             (0x00000004U)
#define CSL_LSE_SRC_VPIN_CFG_VP_PROTOCOL_CHK_MAX                               (0x00000001U)

#define CSL_LSE_SRC_VPIN_CFG_VPORT_PW_MASK                                     (0x0000000CU)
#define CSL_LSE_SRC_VPIN_CFG_VPORT_PW_SHIFT                                    (0x00000002U)
#define CSL_LSE_SRC_VPIN_CFG_VPORT_PW_MAX                                      (0x00000003U)

#define CSL_LSE_SRC_VPIN_CFG_VPORT_TWO_PIXEL_MASK                              (0x00000002U)
#define CSL_LSE_SRC_VPIN_CFG_VPORT_TWO_PIXEL_SHIFT                             (0x00000001U)
#define CSL_LSE_SRC_VPIN_CFG_VPORT_TWO_PIXEL_MAX                               (0x00000001U)

#define CSL_LSE_SRC_VPIN_CFG_VPORT_EN_MASK                                     (0x00000001U)
#define CSL_LSE_SRC_VPIN_CFG_VPORT_EN_SHIFT                                    (0x00000000U)
#define CSL_LSE_SRC_VPIN_CFG_VPORT_EN_MAX                                      (0x00000001U)

/* FRAME_SIZE */

#define CSL_LSE_SRC_FRAME_SIZE_HEIGHT_MASK                                     (0x1FFF0000U)
#define CSL_LSE_SRC_FRAME_SIZE_HEIGHT_SHIFT                                    (0x00000010U)
#define CSL_LSE_SRC_FRAME_SIZE_HEIGHT_MAX                                      (0x00001FFFU)

#define CSL_LSE_SRC_FRAME_SIZE_WIDTH_MASK                                      (0x00001FFFU)
#define CSL_LSE_SRC_FRAME_SIZE_WIDTH_SHIFT                                     (0x00000000U)
#define CSL_LSE_SRC_FRAME_SIZE_WIDTH_MAX                                       (0x00001FFFU)

/* BUF_ATTR */

#define CSL_LSE_SRC_BUF_ATTR_START_NIB_OFFSET_MASK                             (0xFE000000U)
#define CSL_LSE_SRC_BUF_ATTR_START_NIB_OFFSET_SHIFT                            (0x00000019U)
#define CSL_LSE_SRC_BUF_ATTR_START_NIB_OFFSET_MAX                              (0x0000007FU)

#define CSL_LSE_SRC_BUF_ATTR_CBUF_SIZE_MASK                                    (0x01FF0000U)
#define CSL_LSE_SRC_BUF_ATTR_CBUF_SIZE_SHIFT                                   (0x00000010U)
#define CSL_LSE_SRC_BUF_ATTR_CBUF_SIZE_MAX                                     (0x000001FFU)

#define CSL_LSE_SRC_BUF_ATTR_BUF_STRIDE_MASK                                   (0x0000FFC0U)
#define CSL_LSE_SRC_BUF_ATTR_BUF_STRIDE_SHIFT                                  (0x00000006U)
#define CSL_LSE_SRC_BUF_ATTR_BUF_STRIDE_MAX                                    (0x000003FFU)

#define CSL_LSE_SRC_BUF_ATTR_BUF_STRIDE_6_LSB_MASK                             (0x0000003FU)
#define CSL_LSE_SRC_BUF_ATTR_BUF_STRIDE_6_LSB_SHIFT                            (0x00000000U)
#define CSL_LSE_SRC_BUF_ATTR_BUF_STRIDE_6_LSB_MAX                              (0x0000003FU)

/* BUF_BA */

#define CSL_LSE_SRC_BUF_BA_ENABLE_MASK                                         (0x80000000U)
#define CSL_LSE_SRC_BUF_BA_ENABLE_SHIFT                                        (0x0000001FU)
#define CSL_LSE_SRC_BUF_BA_ENABLE_MAX                                          (0x00000001U)

#define CSL_LSE_SRC_BUF_BA_SKIP_ODD_LINE_PROC_MASK                             (0x40000000U)
#define CSL_LSE_SRC_BUF_BA_SKIP_ODD_LINE_PROC_SHIFT                            (0x0000001EU)
#define CSL_LSE_SRC_BUF_BA_SKIP_ODD_LINE_PROC_MAX                              (0x00000001U)

#define CSL_LSE_SRC_BUF_BA_SKIP_ALTERNATE_LINE_PROC_MASK                       (0x20000000U)
#define CSL_LSE_SRC_BUF_BA_SKIP_ALTERNATE_LINE_PROC_SHIFT                      (0x0000001DU)
#define CSL_LSE_SRC_BUF_BA_SKIP_ALTERNATE_LINE_PROC_MAX                        (0x00000001U)

#define CSL_LSE_SRC_BUF_BA_ENABLE_INTERLEAVED_PIXEL_EXTRACTION_MASK            (0x10000000U)
#define CSL_LSE_SRC_BUF_BA_ENABLE_INTERLEAVED_PIXEL_EXTRACTION_SHIFT           (0x0000001CU)
#define CSL_LSE_SRC_BUF_BA_ENABLE_INTERLEAVED_PIXEL_EXTRACTION_MAX             (0x00000001U)

#define CSL_LSE_SRC_BUF_BA_EXTRACT_INTERLEAVED_ODD_PIXELS_MASK                 (0x08000000U)
#define CSL_LSE_SRC_BUF_BA_EXTRACT_INTERLEAVED_ODD_PIXELS_SHIFT                (0x0000001BU)
#define CSL_LSE_SRC_BUF_BA_EXTRACT_INTERLEAVED_ODD_PIXELS_MAX                  (0x00000001U)

#define CSL_LSE_SRC_BUF_BA_ADDR_MASK                                           (0x00FFFFC0U)
#define CSL_LSE_SRC_BUF_BA_ADDR_SHIFT                                          (0x00000006U)
#define CSL_LSE_SRC_BUF_BA_ADDR_MAX                                            (0x0003FFFFU)

#define CSL_LSE_SRC_BUF_BA_ADDR_6_LSB_MASK                                     (0x0000003FU)
#define CSL_LSE_SRC_BUF_BA_ADDR_6_LSB_SHIFT                                    (0x00000000U)
#define CSL_LSE_SRC_BUF_BA_ADDR_6_LSB_MAX                                      (0x0000003FU)

/* BUF_CFG */

#define CSL_LSE_DST_BUF_CFG_CH_DISABLED_MASK                                   (0x80000000U)
#define CSL_LSE_DST_BUF_CFG_CH_DISABLED_SHIFT                                  (0x0000001FU)
#define CSL_LSE_DST_BUF_CFG_CH_DISABLED_MAX                                    (0x00000001U)

#define CSL_LSE_DST_BUF_CFG_YUV422_INTLV_ORDER_MASK                            (0x20000000U)
#define CSL_LSE_DST_BUF_CFG_YUV422_INTLV_ORDER_SHIFT                           (0x0000001DU)
#define CSL_LSE_DST_BUF_CFG_YUV422_INTLV_ORDER_MAX                             (0x00000001U)

#define CSL_LSE_DST_BUF_CFG_YUV422_OUT_EN_MASK                                 (0x10000000U)
#define CSL_LSE_DST_BUF_CFG_YUV422_OUT_EN_SHIFT                                (0x0000001CU)
#define CSL_LSE_DST_BUF_CFG_YUV422_OUT_EN_MAX                                  (0x00000001U)

#define CSL_LSE_DST_BUF_CFG_ENABLE_SIGNED_ACCLERATOR_DATA_MASK                 (0x00000400U)
#define CSL_LSE_DST_BUF_CFG_ENABLE_SIGNED_ACCLERATOR_DATA_SHIFT                (0x0000000AU)
#define CSL_LSE_DST_BUF_CFG_ENABLE_SIGNED_ACCLERATOR_DATA_MAX                  (0x00000001U)

#define CSL_LSE_DST_BUF_CFG_ENABLE_OUTPUT_PIXEL_ROUNDING_MASK                  (0x00000200U)
#define CSL_LSE_DST_BUF_CFG_ENABLE_OUTPUT_PIXEL_ROUNDING_SHIFT                 (0x00000009U)
#define CSL_LSE_DST_BUF_CFG_ENABLE_OUTPUT_PIXEL_ROUNDING_MAX                   (0x00000001U)

#define CSL_LSE_DST_BUF_CFG_CHAN_THREAD_MAP_MASK                               (0x00000100U)
#define CSL_LSE_DST_BUF_CFG_CHAN_THREAD_MAP_SHIFT                              (0x00000008U)
#define CSL_LSE_DST_BUF_CFG_CHAN_THREAD_MAP_MAX                                (0x00000001U)

#define CSL_LSE_DST_BUF_CFG_THREAD_MAP_MASK                                    (0x00000080U)
#define CSL_LSE_DST_BUF_CFG_THREAD_MAP_SHIFT                                   (0x00000007U)
#define CSL_LSE_DST_BUF_CFG_THREAD_MAP_MAX                                     (0x00000001U)

#define CSL_LSE_DST_BUF_CFG_PIX_FMT_ALIGN_MASK                                 (0x00000010U)
#define CSL_LSE_DST_BUF_CFG_PIX_FMT_ALIGN_SHIFT                                (0x00000004U)
#define CSL_LSE_DST_BUF_CFG_PIX_FMT_ALIGN_MAX                                  (0x00000001U)

#define CSL_LSE_DST_BUF_CFG_PIX_FMT_CNTRSZ_MASK                                (0x0000000CU)
#define CSL_LSE_DST_BUF_CFG_PIX_FMT_CNTRSZ_SHIFT                               (0x00000002U)
#define CSL_LSE_DST_BUF_CFG_PIX_FMT_CNTRSZ_MAX                                 (0x00000003U)

#define CSL_LSE_DST_BUF_CFG_PIX_FMT_PW_MASK                                    (0x00000003U)
#define CSL_LSE_DST_BUF_CFG_PIX_FMT_PW_SHIFT                                   (0x00000000U)
#define CSL_LSE_DST_BUF_CFG_PIX_FMT_PW_MAX                                     (0x00000003U)

/* BUF_ATTR0 */

#define CSL_LSE_DST_BUF_ATTR0_LOUT_SKIP_INIT_MASK                              (0xFE000000U)
#define CSL_LSE_DST_BUF_ATTR0_LOUT_SKIP_INIT_SHIFT                             (0x00000019U)
#define CSL_LSE_DST_BUF_ATTR0_LOUT_SKIP_INIT_MAX                               (0x0000007FU)

#define CSL_LSE_DST_BUF_ATTR0_CBUF_SIZE_MASK                                   (0x01FF0000U)
#define CSL_LSE_DST_BUF_ATTR0_CBUF_SIZE_SHIFT                                  (0x00000010U)
#define CSL_LSE_DST_BUF_ATTR0_CBUF_SIZE_MAX                                    (0x000001FFU)

#define CSL_LSE_DST_BUF_ATTR0_BUF_STRIDE_MASK                                  (0x0000FFC0U)
#define CSL_LSE_DST_BUF_ATTR0_BUF_STRIDE_SHIFT                                 (0x00000006U)
#define CSL_LSE_DST_BUF_ATTR0_BUF_STRIDE_MAX                                   (0x000003FFU)

#define CSL_LSE_DST_BUF_ATTR0_BUF_STRIDE_6_LSB_MASK                            (0x0000003FU)
#define CSL_LSE_DST_BUF_ATTR0_BUF_STRIDE_6_LSB_SHIFT                           (0x00000000U)
#define CSL_LSE_DST_BUF_ATTR0_BUF_STRIDE_6_LSB_MAX                             (0x0000003FU)

/* BUF_ATTR1 */

#define CSL_LSE_DST_BUF_ATTR1_CBUF_BPR_CHAN_MASK                               (0x03FF0000U)
#define CSL_LSE_DST_BUF_ATTR1_CBUF_BPR_CHAN_SHIFT                              (0x00000010U)
#define CSL_LSE_DST_BUF_ATTR1_CBUF_BPR_CHAN_MAX                                (0x000003FFU)

#define CSL_LSE_DST_BUF_ATTR1_TDONE_GEN_MODE_MASK                              (0x00000004U)
#define CSL_LSE_DST_BUF_ATTR1_TDONE_GEN_MODE_SHIFT                             (0x00000002U)
#define CSL_LSE_DST_BUF_ATTR1_TDONE_GEN_MODE_MAX                               (0x00000001U)

#define CSL_LSE_DST_BUF_ATTR1_BPR_SEL_MODE_MASK                                (0x00000002U)
#define CSL_LSE_DST_BUF_ATTR1_BPR_SEL_MODE_SHIFT                               (0x00000001U)
#define CSL_LSE_DST_BUF_ATTR1_BPR_SEL_MODE_MAX                                 (0x00000001U)

#define CSL_LSE_DST_BUF_ATTR1_CBUF_VWRAP_EN_MASK                               (0x00000001U)
#define CSL_LSE_DST_BUF_ATTR1_CBUF_VWRAP_EN_SHIFT                              (0x00000000U)
#define CSL_LSE_DST_BUF_ATTR1_CBUF_VWRAP_EN_MAX                                (0x00000001U)

/* BUF_BA */

#define CSL_LSE_DST_BUF_BA_ENABLE_MASK                                         (0x80000000U)
#define CSL_LSE_DST_BUF_BA_ENABLE_SHIFT                                        (0x0000001FU)
#define CSL_LSE_DST_BUF_BA_ENABLE_MAX                                          (0x00000001U)

#define CSL_LSE_DST_BUF_BA_SKIP_ODD_LINE_PROC_MASK                             (0x40000000U)
#define CSL_LSE_DST_BUF_BA_SKIP_ODD_LINE_PROC_SHIFT                            (0x0000001EU)
#define CSL_LSE_DST_BUF_BA_SKIP_ODD_LINE_PROC_MAX                              (0x00000001U)

#define CSL_LSE_DST_BUF_BA_SKIP_ALTERNATE_LINE_PROC_MASK                       (0x20000000U)
#define CSL_LSE_DST_BUF_BA_SKIP_ALTERNATE_LINE_PROC_SHIFT                      (0x0000001DU)
#define CSL_LSE_DST_BUF_BA_SKIP_ALTERNATE_LINE_PROC_MAX                        (0x00000001U)

#define CSL_LSE_DST_BUF_BA_ADDR_MASK                                           (0x00FFFFC0U)
#define CSL_LSE_DST_BUF_BA_ADDR_SHIFT                                          (0x00000006U)
#define CSL_LSE_DST_BUF_BA_ADDR_MAX                                            (0x0003FFFFU)

#define CSL_LSE_DST_BUF_BA_ADDR_6_LSB_MASK                                     (0x0000003FU)
#define CSL_LSE_DST_BUF_BA_ADDR_6_LSB_SHIFT                                    (0x00000000U)
#define CSL_LSE_DST_BUF_BA_ADDR_6_LSB_MAX                                      (0x0000003FU)

/* BUF_ATTR */

#define CSL_LSE_H3A_BUF_ATTR_CBUF_SIZE_MASK                                    (0x01FF0000U)
#define CSL_LSE_H3A_BUF_ATTR_CBUF_SIZE_SHIFT                                   (0x00000010U)
#define CSL_LSE_H3A_BUF_ATTR_CBUF_SIZE_MAX                                     (0x000001FFU)

#define CSL_LSE_H3A_BUF_ATTR_H3A_LN_SIZE_MASK                                  (0x0000FFC0U)
#define CSL_LSE_H3A_BUF_ATTR_H3A_LN_SIZE_SHIFT                                 (0x00000006U)
#define CSL_LSE_H3A_BUF_ATTR_H3A_LN_SIZE_MAX                                   (0x000003FFU)

#define CSL_LSE_H3A_BUF_ATTR_H3A_LN_SIZE_6_LSB_MASK                            (0x0000003FU)
#define CSL_LSE_H3A_BUF_ATTR_H3A_LN_SIZE_6_LSB_SHIFT                           (0x00000000U)
#define CSL_LSE_H3A_BUF_ATTR_H3A_LN_SIZE_6_LSB_MAX                             (0x0000003FU)

/* BUF_BA */

#define CSL_LSE_H3A_BUF_BA_ENABLE_MASK                                         (0x80000000U)
#define CSL_LSE_H3A_BUF_BA_ENABLE_SHIFT                                        (0x0000001FU)
#define CSL_LSE_H3A_BUF_BA_ENABLE_MAX                                          (0x00000001U)

#define CSL_LSE_H3A_BUF_BA_ADDR_MASK                                           (0x00FFFFC0U)
#define CSL_LSE_H3A_BUF_BA_ADDR_SHIFT                                          (0x00000006U)
#define CSL_LSE_H3A_BUF_BA_ADDR_MAX                                            (0x0003FFFFU)

#define CSL_LSE_H3A_BUF_BA_ADDR_6_LSB_MASK                                     (0x0000003FU)
#define CSL_LSE_H3A_BUF_BA_ADDR_6_LSB_SHIFT                                    (0x00000000U)
#define CSL_LSE_H3A_BUF_BA_ADDR_6_LSB_MAX                                      (0x0000003FU)

/* ROW */

#define CSL_LSE_COMMON_CFG__ROW_BPR0_MASK                                      (0x3FF00000U)
#define CSL_LSE_COMMON_CFG__ROW_BPR0_SHIFT                                     (0x00000014U)
#define CSL_LSE_COMMON_CFG__ROW_BPR0_MAX                                       (0x000003FFU)

#define CSL_LSE_COMMON_CFG__ROW_BPR1_MASK                                      (0x000FFC00U)
#define CSL_LSE_COMMON_CFG__ROW_BPR1_SHIFT                                     (0x0000000AU)
#define CSL_LSE_COMMON_CFG__ROW_BPR1_MAX                                       (0x000003FFU)

#define CSL_LSE_COMMON_CFG__ROW_BPR2_MASK                                      (0x000003FFU)
#define CSL_LSE_COMMON_CFG__ROW_BPR2_SHIFT                                     (0x00000000U)
#define CSL_LSE_COMMON_CFG__ROW_BPR2_MAX                                       (0x000003FFU)

/* STATUS_PARAM */

#define CSL_LSE_STATUS_PARAM_BYPASS_CH_MASK                                    (0xC0000000U)
#define CSL_LSE_STATUS_PARAM_BYPASS_CH_SHIFT                                   (0x0000001EU)
#define CSL_LSE_STATUS_PARAM_BYPASS_CH_MAX                                     (0x00000003U)

#define CSL_LSE_STATUS_PARAM_OUT_SKIP_EN_MASK                                  (0x20000000U)
#define CSL_LSE_STATUS_PARAM_OUT_SKIP_EN_SHIFT                                 (0x0000001DU)
#define CSL_LSE_STATUS_PARAM_OUT_SKIP_EN_MAX                                   (0x00000001U)

#define CSL_LSE_STATUS_PARAM_CORE_OUT_2D_MASK                                  (0x10000000U)
#define CSL_LSE_STATUS_PARAM_CORE_OUT_2D_SHIFT                                 (0x0000001CU)
#define CSL_LSE_STATUS_PARAM_CORE_OUT_2D_MAX                                   (0x00000001U)

#define CSL_LSE_STATUS_PARAM_CORE_OUT_DW_MASK                                  (0x0F800000U)
#define CSL_LSE_STATUS_PARAM_CORE_OUT_DW_SHIFT                                 (0x00000017U)
#define CSL_LSE_STATUS_PARAM_CORE_OUT_DW_MAX                                   (0x0000001FU)

#define CSL_LSE_STATUS_PARAM_LINE_SKIP_EN_MASK                                 (0x00400000U)
#define CSL_LSE_STATUS_PARAM_LINE_SKIP_EN_SHIFT                                (0x00000016U)
#define CSL_LSE_STATUS_PARAM_LINE_SKIP_EN_MAX                                  (0x00000001U)

#define CSL_LSE_STATUS_PARAM_BIT_AOFFSET_MASK                                  (0x00200000U)
#define CSL_LSE_STATUS_PARAM_BIT_AOFFSET_SHIFT                                 (0x00000015U)
#define CSL_LSE_STATUS_PARAM_BIT_AOFFSET_MAX                                   (0x00000001U)

#define CSL_LSE_STATUS_PARAM_HV_INSERT_MASK                                    (0x00100000U)
#define CSL_LSE_STATUS_PARAM_HV_INSERT_SHIFT                                   (0x00000014U)
#define CSL_LSE_STATUS_PARAM_HV_INSERT_MAX                                     (0x00000001U)

#define CSL_LSE_STATUS_PARAM_PIX_MX_HT_MASK                                    (0x000E0000U)
#define CSL_LSE_STATUS_PARAM_PIX_MX_HT_SHIFT                                   (0x00000011U)
#define CSL_LSE_STATUS_PARAM_PIX_MX_HT_MAX                                     (0x00000007U)

#define CSL_LSE_STATUS_PARAM_CORE_DW_MASK                                      (0x0001F000U)
#define CSL_LSE_STATUS_PARAM_CORE_DW_SHIFT                                     (0x0000000CU)
#define CSL_LSE_STATUS_PARAM_CORE_DW_MAX                                       (0x0000001FU)

#define CSL_LSE_STATUS_PARAM_SL2_OUT_H3A_CH_MASK                               (0x00000C00U)
#define CSL_LSE_STATUS_PARAM_SL2_OUT_H3A_CH_SHIFT                              (0x0000000AU)
#define CSL_LSE_STATUS_PARAM_SL2_OUT_H3A_CH_MAX                                (0x00000003U)

#define CSL_LSE_STATUS_PARAM_SL2_OUT_CH_MASK                                   (0x000003C0U)
#define CSL_LSE_STATUS_PARAM_SL2_OUT_CH_SHIFT                                  (0x00000006U)
#define CSL_LSE_STATUS_PARAM_SL2_OUT_CH_MAX                                    (0x0000000FU)

#define CSL_LSE_STATUS_PARAM_SL2_IN_CH_THR_MASK                                (0x00000038U)
#define CSL_LSE_STATUS_PARAM_SL2_IN_CH_THR_SHIFT                               (0x00000003U)
#define CSL_LSE_STATUS_PARAM_SL2_IN_CH_THR_MAX                                 (0x00000007U)

#define CSL_LSE_STATUS_PARAM_VPORT_THR_MASK                                    (0x00000004U)
#define CSL_LSE_STATUS_PARAM_VPORT_THR_SHIFT                                   (0x00000002U)
#define CSL_LSE_STATUS_PARAM_VPORT_THR_MAX                                     (0x00000001U)

#define CSL_LSE_STATUS_PARAM_NTHR_MASK                                         (0x00000003U)
#define CSL_LSE_STATUS_PARAM_NTHR_SHIFT                                        (0x00000000U)
#define CSL_LSE_STATUS_PARAM_NTHR_MAX                                          (0x00000003U)

/* STATUS_ERROR */

#define CSL_LSE_STATUS_ERROR_VPORT_IN_ERR_MASK                                 (0x07FF0000U)
#define CSL_LSE_STATUS_ERROR_VPORT_IN_ERR_SHIFT                                (0x00000010U)
#define CSL_LSE_STATUS_ERROR_VPORT_IN_ERR_MAX                                  (0x000007FFU)

#define CSL_LSE_STATUS_ERROR_VM_WR_ERR_MASK                                    (0x00007F00U)
#define CSL_LSE_STATUS_ERROR_VM_WR_ERR_SHIFT                                   (0x00000008U)
#define CSL_LSE_STATUS_ERROR_VM_WR_ERR_MAX                                     (0x0000007FU)

#define CSL_LSE_STATUS_ERROR_VM_RD_ERR_MASK                                    (0x0000001FU)
#define CSL_LSE_STATUS_ERROR_VM_RD_ERR_SHIFT                                   (0x00000000U)
#define CSL_LSE_STATUS_ERROR_VM_RD_ERR_MAX                                     (0x0000001FU)

/* STATUS_IDLE_MODE */

#define CSL_LSE_STATUS_IDLE_MODE_LSE_OUT_H3A_CHAN_MASK                         (0x01000000U)
#define CSL_LSE_STATUS_IDLE_MODE_LSE_OUT_H3A_CHAN_SHIFT                        (0x00000018U)
#define CSL_LSE_STATUS_IDLE_MODE_LSE_OUT_H3A_CHAN_MAX                          (0x00000001U)

#define CSL_LSE_STATUS_IDLE_MODE_LSE_OUT_CHAN_MASK                             (0x003FF000U)
#define CSL_LSE_STATUS_IDLE_MODE_LSE_OUT_CHAN_SHIFT                            (0x0000000CU)
#define CSL_LSE_STATUS_IDLE_MODE_LSE_OUT_CHAN_MAX                              (0x000003FFU)

#define CSL_LSE_STATUS_IDLE_MODE_VPORT_IN_CHAN_MASK                            (0x00000800U)
#define CSL_LSE_STATUS_IDLE_MODE_VPORT_IN_CHAN_SHIFT                           (0x0000000BU)
#define CSL_LSE_STATUS_IDLE_MODE_VPORT_IN_CHAN_MAX                             (0x00000001U)

#define CSL_LSE_STATUS_IDLE_MODE_LSE_IN_CHAN_MASK                              (0x000000F0U)
#define CSL_LSE_STATUS_IDLE_MODE_LSE_IN_CHAN_SHIFT                             (0x00000004U)
#define CSL_LSE_STATUS_IDLE_MODE_LSE_IN_CHAN_MAX                               (0x0000000FU)

#define CSL_LSE_STATUS_IDLE_MODE_VM_WR_PORT_MASK                               (0x00000002U)
#define CSL_LSE_STATUS_IDLE_MODE_VM_WR_PORT_SHIFT                              (0x00000001U)
#define CSL_LSE_STATUS_IDLE_MODE_VM_WR_PORT_MAX                                (0x00000001U)

#define CSL_LSE_STATUS_IDLE_MODE_VM_RD_PORT_MASK                               (0x00000001U)
#define CSL_LSE_STATUS_IDLE_MODE_VM_RD_PORT_SHIFT                              (0x00000000U)
#define CSL_LSE_STATUS_IDLE_MODE_VM_RD_PORT_MAX                                (0x00000001U)

/* CFG_LSE */

#define CSL_LSE_CFG_LSE_PSA_EN_MASK                                            (0x00000100U)
#define CSL_LSE_CFG_LSE_PSA_EN_SHIFT                                           (0x00000008U)
#define CSL_LSE_CFG_LSE_PSA_EN_MAX                                             (0x00000001U)

#define CSL_LSE_CFG_LSE_IN_CH_SYNC_MODE_MASK                                   (0x00000020U)
#define CSL_LSE_CFG_LSE_IN_CH_SYNC_MODE_SHIFT                                  (0x00000005U)
#define CSL_LSE_CFG_LSE_IN_CH_SYNC_MODE_MAX                                    (0x00000001U)

#define CSL_LSE_CFG_LSE_VM_ARB_FIXED_MODE_MASK                                 (0x00000010U)
#define CSL_LSE_CFG_LSE_VM_ARB_FIXED_MODE_SHIFT                                (0x00000004U)
#define CSL_LSE_CFG_LSE_VM_ARB_FIXED_MODE_MAX                                  (0x00000001U)

#define CSL_LSE_CFG_LSE_LOOPBACK_IN_CH_SEL_MASK                                (0x0000000CU)
#define CSL_LSE_CFG_LSE_LOOPBACK_IN_CH_SEL_SHIFT                               (0x00000002U)
#define CSL_LSE_CFG_LSE_LOOPBACK_IN_CH_SEL_MAX                                 (0x00000002U)

#define CSL_LSE_CFG_LSE_LOOPBACK_CORE_EN_MASK                                  (0x00000002U)
#define CSL_LSE_CFG_LSE_LOOPBACK_CORE_EN_SHIFT                                 (0x00000001U)
#define CSL_LSE_CFG_LSE_LOOPBACK_CORE_EN_MAX                                   (0x00000001U)

#define CSL_LSE_CFG_LSE_LOOPBACK_EN_MASK                                       (0x00000001U)
#define CSL_LSE_CFG_LSE_LOOPBACK_EN_SHIFT                                      (0x00000000U)
#define CSL_LSE_CFG_LSE_LOOPBACK_EN_MAX                                        (0x00000001U)

/* DST_COMMON_CFG */

#define CSL_LSE_DST_COMMON_CFG_ROUNDING_OFFSET_MASK                            (0x0000003FU)
#define CSL_LSE_DST_COMMON_CFG_ROUNDING_OFFSET_SHIFT                           (0x00000000U)
#define CSL_LSE_DST_COMMON_CFG_ROUNDING_OFFSET_MAX                             (0x0000003FU)

/* PSA_SIGNATURE */

#define CSL_LSE_PSA_SIGNATURE_VALUE_MASK                                       (0xFFFFFFFFU)
#define CSL_LSE_PSA_SIGNATURE_VALUE_SHIFT                                      (0x00000000U)
#define CSL_LSE_PSA_SIGNATURE_VALUE_MAX                                        (0xFFFFFFFFU)

/* SRC0_CFG1 */

#define CSL_LSE_SRC0_CFG1_SKIP_SL2_READS_MASK                                  (0x00000040U)
#define CSL_LSE_SRC0_CFG1_SKIP_SL2_READS_SHIFT                                 (0x00000006U)
#define CSL_LSE_SRC0_CFG1_SKIP_SL2_READS_MAX                                   (0x00000001U)

#define CSL_LSE_SRC0_CFG1_ENABLE_CHAN_SPECIFIC_PARAMS_MASK                     (0x00000020U)
#define CSL_LSE_SRC0_CFG1_ENABLE_CHAN_SPECIFIC_PARAMS_SHIFT                    (0x00000005U)
#define CSL_LSE_SRC0_CFG1_ENABLE_CHAN_SPECIFIC_PARAMS_MAX                      (0x00000001U)

#define CSL_LSE_SRC0_CFG1_PIX_FMT_ALIGN_MASK                                   (0x00000010U)
#define CSL_LSE_SRC0_CFG1_PIX_FMT_ALIGN_SHIFT                                  (0x00000004U)
#define CSL_LSE_SRC0_CFG1_PIX_FMT_ALIGN_MAX                                    (0x00000001U)

#define CSL_LSE_SRC0_CFG1_PIX_FMT_CNTRSZ_MASK                                  (0x0000000CU)
#define CSL_LSE_SRC0_CFG1_PIX_FMT_CNTRSZ_SHIFT                                 (0x00000002U)
#define CSL_LSE_SRC0_CFG1_PIX_FMT_CNTRSZ_MAX                                   (0x00000003U)

#define CSL_LSE_SRC0_CFG1_PIX_FMT_PW_MASK                                      (0x00000003U)
#define CSL_LSE_SRC0_CFG1_PIX_FMT_PW_SHIFT                                     (0x00000000U)
#define CSL_LSE_SRC0_CFG1_PIX_FMT_PW_MAX                                       (0x00000003U)

/* SRC0_FRAME_SIZE1 */

#define CSL_LSE_SRC0_FRAME_SIZE1_WIDTH_MASK                                    (0x00001FFFU)
#define CSL_LSE_SRC0_FRAME_SIZE1_WIDTH_SHIFT                                   (0x00000000U)
#define CSL_LSE_SRC0_FRAME_SIZE1_WIDTH_MAX                                     (0x00001FFFU)

/* SRC0_CFG2 */

#define CSL_LSE_SRC0_CFG2_SKIP_SL2_READS_MASK                                  (0x00000040U)
#define CSL_LSE_SRC0_CFG2_SKIP_SL2_READS_SHIFT                                 (0x00000006U)
#define CSL_LSE_SRC0_CFG2_SKIP_SL2_READS_MAX                                   (0x00000001U)

#define CSL_LSE_SRC0_CFG2_ENABLE_CHAN_SPECIFIC_PARAMS_MASK                     (0x00000020U)
#define CSL_LSE_SRC0_CFG2_ENABLE_CHAN_SPECIFIC_PARAMS_SHIFT                    (0x00000005U)
#define CSL_LSE_SRC0_CFG2_ENABLE_CHAN_SPECIFIC_PARAMS_MAX                      (0x00000001U)

#define CSL_LSE_SRC0_CFG2_PIX_FMT_ALIGN_MASK                                   (0x00000010U)
#define CSL_LSE_SRC0_CFG2_PIX_FMT_ALIGN_SHIFT                                  (0x00000004U)
#define CSL_LSE_SRC0_CFG2_PIX_FMT_ALIGN_MAX                                    (0x00000001U)

#define CSL_LSE_SRC0_CFG2_PIX_FMT_CNTRSZ_MASK                                  (0x0000000CU)
#define CSL_LSE_SRC0_CFG2_PIX_FMT_CNTRSZ_SHIFT                                 (0x00000002U)
#define CSL_LSE_SRC0_CFG2_PIX_FMT_CNTRSZ_MAX                                   (0x00000003U)

#define CSL_LSE_SRC0_CFG2_PIX_FMT_PW_MASK                                      (0x00000003U)
#define CSL_LSE_SRC0_CFG2_PIX_FMT_PW_SHIFT                                     (0x00000000U)
#define CSL_LSE_SRC0_CFG2_PIX_FMT_PW_MAX                                       (0x00000003U)

/* SRC0_FRAME_SIZE2 */

#define CSL_LSE_SRC0_FRAME_SIZE2_WIDTH_MASK                                    (0x00001FFFU)
#define CSL_LSE_SRC0_FRAME_SIZE2_WIDTH_SHIFT                                   (0x00000000U)
#define CSL_LSE_SRC0_FRAME_SIZE2_WIDTH_MAX                                     (0x00001FFFU)

/* SRC0_CFG3 */

#define CSL_LSE_SRC0_CFG3_SKIP_SL2_READS_MASK                                  (0x00000040U)
#define CSL_LSE_SRC0_CFG3_SKIP_SL2_READS_SHIFT                                 (0x00000006U)
#define CSL_LSE_SRC0_CFG3_SKIP_SL2_READS_MAX                                   (0x00000001U)

#define CSL_LSE_SRC0_CFG3_ENABLE_CHAN_SPECIFIC_PARAMS_MASK                     (0x00000020U)
#define CSL_LSE_SRC0_CFG3_ENABLE_CHAN_SPECIFIC_PARAMS_SHIFT                    (0x00000005U)
#define CSL_LSE_SRC0_CFG3_ENABLE_CHAN_SPECIFIC_PARAMS_MAX                      (0x00000001U)

#define CSL_LSE_SRC0_CFG3_PIX_FMT_ALIGN_MASK                                   (0x00000010U)
#define CSL_LSE_SRC0_CFG3_PIX_FMT_ALIGN_SHIFT                                  (0x00000004U)
#define CSL_LSE_SRC0_CFG3_PIX_FMT_ALIGN_MAX                                    (0x00000001U)

#define CSL_LSE_SRC0_CFG3_PIX_FMT_CNTRSZ_MASK                                  (0x0000000CU)
#define CSL_LSE_SRC0_CFG3_PIX_FMT_CNTRSZ_SHIFT                                 (0x00000002U)
#define CSL_LSE_SRC0_CFG3_PIX_FMT_CNTRSZ_MAX                                   (0x00000003U)

#define CSL_LSE_SRC0_CFG3_PIX_FMT_PW_MASK                                      (0x00000003U)
#define CSL_LSE_SRC0_CFG3_PIX_FMT_PW_SHIFT                                     (0x00000000U)
#define CSL_LSE_SRC0_CFG3_PIX_FMT_PW_MAX                                       (0x00000003U)

/* SRC0_FRAME_SIZE3 */

#define CSL_LSE_SRC0_FRAME_SIZE3_WIDTH_MASK                                    (0x00001FFFU)
#define CSL_LSE_SRC0_FRAME_SIZE3_WIDTH_SHIFT                                   (0x00000000U)
#define CSL_LSE_SRC0_FRAME_SIZE3_WIDTH_MAX                                     (0x00001FFFU)

/* SRC1_CFG1 */

#define CSL_LSE_SRC1_CFG1_SKIP_SL2_READS_MASK                                  (0x00000040U)
#define CSL_LSE_SRC1_CFG1_SKIP_SL2_READS_SHIFT                                 (0x00000006U)
#define CSL_LSE_SRC1_CFG1_SKIP_SL2_READS_MAX                                   (0x00000001U)

#define CSL_LSE_SRC1_CFG1_ENABLE_CHAN_SPECIFIC_PARAMS_MASK                     (0x00000020U)
#define CSL_LSE_SRC1_CFG1_ENABLE_CHAN_SPECIFIC_PARAMS_SHIFT                    (0x00000005U)
#define CSL_LSE_SRC1_CFG1_ENABLE_CHAN_SPECIFIC_PARAMS_MAX                      (0x00000001U)

#define CSL_LSE_SRC1_CFG1_PIX_FMT_ALIGN_MASK                                   (0x00000010U)
#define CSL_LSE_SRC1_CFG1_PIX_FMT_ALIGN_SHIFT                                  (0x00000004U)
#define CSL_LSE_SRC1_CFG1_PIX_FMT_ALIGN_MAX                                    (0x00000001U)

#define CSL_LSE_SRC1_CFG1_PIX_FMT_CNTRSZ_MASK                                  (0x0000000CU)
#define CSL_LSE_SRC1_CFG1_PIX_FMT_CNTRSZ_SHIFT                                 (0x00000002U)
#define CSL_LSE_SRC1_CFG1_PIX_FMT_CNTRSZ_MAX                                   (0x00000003U)

#define CSL_LSE_SRC1_CFG1_PIX_FMT_PW_MASK                                      (0x00000003U)
#define CSL_LSE_SRC1_CFG1_PIX_FMT_PW_SHIFT                                     (0x00000000U)
#define CSL_LSE_SRC1_CFG1_PIX_FMT_PW_MAX                                       (0x00000003U)

/* SRC1_FRAME_SIZE1 */

#define CSL_LSE_SRC1_FRAME_SIZE1_WIDTH_MASK                                    (0x00001FFFU)
#define CSL_LSE_SRC1_FRAME_SIZE1_WIDTH_SHIFT                                   (0x00000000U)
#define CSL_LSE_SRC1_FRAME_SIZE1_WIDTH_MAX                                     (0x00001FFFU)

/* SRC1_CFG2 */

#define CSL_LSE_SRC1_CFG2_SKIP_SL2_READS_MASK                                  (0x00000040U)
#define CSL_LSE_SRC1_CFG2_SKIP_SL2_READS_SHIFT                                 (0x00000006U)
#define CSL_LSE_SRC1_CFG2_SKIP_SL2_READS_MAX                                   (0x00000001U)

#define CSL_LSE_SRC1_CFG2_ENABLE_CHAN_SPECIFIC_PARAMS_MASK                     (0x00000020U)
#define CSL_LSE_SRC1_CFG2_ENABLE_CHAN_SPECIFIC_PARAMS_SHIFT                    (0x00000005U)
#define CSL_LSE_SRC1_CFG2_ENABLE_CHAN_SPECIFIC_PARAMS_MAX                      (0x00000001U)

#define CSL_LSE_SRC1_CFG2_PIX_FMT_ALIGN_MASK                                   (0x00000010U)
#define CSL_LSE_SRC1_CFG2_PIX_FMT_ALIGN_SHIFT                                  (0x00000004U)
#define CSL_LSE_SRC1_CFG2_PIX_FMT_ALIGN_MAX                                    (0x00000001U)

#define CSL_LSE_SRC1_CFG2_PIX_FMT_CNTRSZ_MASK                                  (0x0000000CU)
#define CSL_LSE_SRC1_CFG2_PIX_FMT_CNTRSZ_SHIFT                                 (0x00000002U)
#define CSL_LSE_SRC1_CFG2_PIX_FMT_CNTRSZ_MAX                                   (0x00000003U)

#define CSL_LSE_SRC1_CFG2_PIX_FMT_PW_MASK                                      (0x00000003U)
#define CSL_LSE_SRC1_CFG2_PIX_FMT_PW_SHIFT                                     (0x00000000U)
#define CSL_LSE_SRC1_CFG2_PIX_FMT_PW_MAX                                       (0x00000003U)

/* SRC1_FRAME_SIZE2 */

#define CSL_LSE_SRC1_FRAME_SIZE2_WIDTH_MASK                                    (0x00001FFFU)
#define CSL_LSE_SRC1_FRAME_SIZE2_WIDTH_SHIFT                                   (0x00000000U)
#define CSL_LSE_SRC1_FRAME_SIZE2_WIDTH_MAX                                     (0x00001FFFU)

/* SRC1_CFG3 */

#define CSL_LSE_SRC1_CFG3_SKIP_SL2_READS_MASK                                  (0x00000040U)
#define CSL_LSE_SRC1_CFG3_SKIP_SL2_READS_SHIFT                                 (0x00000006U)
#define CSL_LSE_SRC1_CFG3_SKIP_SL2_READS_MAX                                   (0x00000001U)

#define CSL_LSE_SRC1_CFG3_ENABLE_CHAN_SPECIFIC_PARAMS_MASK                     (0x00000020U)
#define CSL_LSE_SRC1_CFG3_ENABLE_CHAN_SPECIFIC_PARAMS_SHIFT                    (0x00000005U)
#define CSL_LSE_SRC1_CFG3_ENABLE_CHAN_SPECIFIC_PARAMS_MAX                      (0x00000001U)

#define CSL_LSE_SRC1_CFG3_PIX_FMT_ALIGN_MASK                                   (0x00000010U)
#define CSL_LSE_SRC1_CFG3_PIX_FMT_ALIGN_SHIFT                                  (0x00000004U)
#define CSL_LSE_SRC1_CFG3_PIX_FMT_ALIGN_MAX                                    (0x00000001U)

#define CSL_LSE_SRC1_CFG3_PIX_FMT_CNTRSZ_MASK                                  (0x0000000CU)
#define CSL_LSE_SRC1_CFG3_PIX_FMT_CNTRSZ_SHIFT                                 (0x00000002U)
#define CSL_LSE_SRC1_CFG3_PIX_FMT_CNTRSZ_MAX                                   (0x00000003U)

#define CSL_LSE_SRC1_CFG3_PIX_FMT_PW_MASK                                      (0x00000003U)
#define CSL_LSE_SRC1_CFG3_PIX_FMT_PW_SHIFT                                     (0x00000000U)
#define CSL_LSE_SRC1_CFG3_PIX_FMT_PW_MAX                                       (0x00000003U)

/* SRC1_FRAME_SIZE3 */

#define CSL_LSE_SRC1_FRAME_SIZE3_WIDTH_MASK                                    (0x00001FFFU)
#define CSL_LSE_SRC1_FRAME_SIZE3_WIDTH_SHIFT                                   (0x00000000U)
#define CSL_LSE_SRC1_FRAME_SIZE3_WIDTH_MAX                                     (0x00001FFFU)

/* DBG */

#define CSL_LSE_DBG_STATUS_MASK                                                (0xFFFFFFFFU)
#define CSL_LSE_DBG_STATUS_SHIFT                                               (0x00000000U)
#define CSL_LSE_DBG_STATUS_MAX                                                 (0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif
#endif
