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
 *  Name        : cslr_vpac_nf.h
*/
#ifndef CSLR_VPAC_NF_H_
#define CSLR_VPAC_NF_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/**************************************************************************
* Hardware Region  : MMR Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t REVISION;                  /* Revision Register */
    volatile uint32_t CONTROL;                   /* Control Register */
    volatile uint32_t CENTER_WEIGHT;             /* Central Weight Register */
    volatile uint8_t  Resv_128[116];
    volatile uint32_t DEBUG;                     /* Debug Register */
    volatile uint8_t  Resv_256[124];
    volatile uint32_t WEIGHT_LUT[320];           /* Weight LUT  */
} CSL_vpac_nfRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_VPAC_NF_REVISION                                                   (0x00000000U)
#define CSL_VPAC_NF_CONTROL                                                    (0x00000004U)
#define CSL_VPAC_NF_CENTER_WEIGHT                                              (0x00000008U)
#define CSL_VPAC_NF_DEBUG                                                      (0x00000080U)
#define CSL_VPAC_NF_WEIGHT_LUT(WEIGHT_LUT)                                     (0x00000100U+((WEIGHT_LUT)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* REVISION */

#define CSL_VPAC_NF_REVISION_MODID_MASK                                        (0xFFFF0000U)
#define CSL_VPAC_NF_REVISION_MODID_SHIFT                                       (0x00000010U)
#define CSL_VPAC_NF_REVISION_MODID_MAX                                         (0x0000FFFFU)

#define CSL_VPAC_NF_REVISION_REVRTL_MASK                                       (0x0000F800U)
#define CSL_VPAC_NF_REVISION_REVRTL_SHIFT                                      (0x0000000BU)
#define CSL_VPAC_NF_REVISION_REVRTL_MAX                                        (0x0000001FU)

#define CSL_VPAC_NF_REVISION_REVMAJ_MASK                                       (0x00000700U)
#define CSL_VPAC_NF_REVISION_REVMAJ_SHIFT                                      (0x00000008U)
#define CSL_VPAC_NF_REVISION_REVMAJ_MAX                                        (0x00000007U)

#define CSL_VPAC_NF_REVISION_CUSTOM_MASK                                       (0x000000C0U)
#define CSL_VPAC_NF_REVISION_CUSTOM_SHIFT                                      (0x00000006U)
#define CSL_VPAC_NF_REVISION_CUSTOM_MAX                                        (0x00000003U)

#define CSL_VPAC_NF_REVISION_REVMIN_MASK                                       (0x0000003FU)
#define CSL_VPAC_NF_REVISION_REVMIN_SHIFT                                      (0x00000000U)
#define CSL_VPAC_NF_REVISION_REVMIN_MAX                                        (0x0000003FU)

/* CONTROL */

#define CSL_VPAC_NF_CONTROL_SUB_TABLE_SELECT_MASK                              (0xE0000000U)
#define CSL_VPAC_NF_CONTROL_SUB_TABLE_SELECT_SHIFT                             (0x0000001DU)
#define CSL_VPAC_NF_CONTROL_SUB_TABLE_SELECT_MAX                               (0x00000007U)

#define CSL_VPAC_NF_CONTROL_NUM_SUB_TABLES_MASK                                (0x18000000U)
#define CSL_VPAC_NF_CONTROL_NUM_SUB_TABLES_SHIFT                               (0x0000001BU)
#define CSL_VPAC_NF_CONTROL_NUM_SUB_TABLES_MAX                                 (0x00000003U)

#define CSL_VPAC_NF_CONTROL_OUTPUT_OFFSET_MASK                                 (0x07FF8000U)
#define CSL_VPAC_NF_CONTROL_OUTPUT_OFFSET_SHIFT                                (0x0000000FU)
#define CSL_VPAC_NF_CONTROL_OUTPUT_OFFSET_MAX                                  (0x00000FFFU)

#define CSL_VPAC_NF_CONTROL_OUTPUT_SHIFT_MASK                                  (0x00007800U)
#define CSL_VPAC_NF_CONTROL_OUTPUT_SHIFT_SHIFT                                 (0x0000000BU)
#define CSL_VPAC_NF_CONTROL_OUTPUT_SHIFT_MAX                                   (0x0000000FU)

#define CSL_VPAC_NF_CONTROL_RSVD_MASK                                          (0x000007C0U)
#define CSL_VPAC_NF_CONTROL_RSVD_SHIFT                                         (0x00000006U)
#define CSL_VPAC_NF_CONTROL_RSVD_MAX                                           (0x0000001FU)

#define CSL_VPAC_NF_CONTROL_INTERLEAVE_MODE_MASK                               (0x00000020U)
#define CSL_VPAC_NF_CONTROL_INTERLEAVE_MODE_SHIFT                              (0x00000005U)
#define CSL_VPAC_NF_CONTROL_INTERLEAVE_MODE_MAX                                (0x00000001U)

#define CSL_VPAC_NF_CONTROL_SKIP_ODD_MODE_MASK                                 (0x00000010U)
#define CSL_VPAC_NF_CONTROL_SKIP_ODD_MODE_SHIFT                                (0x00000004U)
#define CSL_VPAC_NF_CONTROL_SKIP_ODD_MODE_MAX                                  (0x00000001U)

#define CSL_VPAC_NF_CONTROL_SKIP_MODE_MASK                                     (0x00000008U)
#define CSL_VPAC_NF_CONTROL_SKIP_MODE_SHIFT                                    (0x00000003U)
#define CSL_VPAC_NF_CONTROL_SKIP_MODE_MAX                                      (0x00000001U)

#define CSL_VPAC_NF_CONTROL_ADAPTIVE_MODE_MASK                                 (0x00000004U)
#define CSL_VPAC_NF_CONTROL_ADAPTIVE_MODE_SHIFT                                (0x00000002U)
#define CSL_VPAC_NF_CONTROL_ADAPTIVE_MODE_MAX                                  (0x00000001U)

#define CSL_VPAC_NF_CONTROL_ENABLE_GENERIC_FILTERING_MASK                      (0x00000002U)
#define CSL_VPAC_NF_CONTROL_ENABLE_GENERIC_FILTERING_SHIFT                     (0x00000001U)
#define CSL_VPAC_NF_CONTROL_ENABLE_GENERIC_FILTERING_MAX                       (0x00000001U)

#define CSL_VPAC_NF_CONTROL_RESERVED_MASK                                      (0x00000001U)
#define CSL_VPAC_NF_CONTROL_RESERVED_SHIFT                                     (0x00000000U)
#define CSL_VPAC_NF_CONTROL_RESERVED_MAX                                       (0x00000001U)

/* CENTER_WEIGHT */

#define CSL_VPAC_NF_CENTER_WEIGHT_RSVD_MASK                                    (0xFFFFFE00U)
#define CSL_VPAC_NF_CENTER_WEIGHT_RSVD_SHIFT                                   (0x00000009U)
#define CSL_VPAC_NF_CENTER_WEIGHT_RSVD_MAX                                     (0x007FFFFFU)

#define CSL_VPAC_NF_CENTER_WEIGHT_CENTRAL_PIXEL_WEIGHT_W00_MASK                (0x000001FFU)
#define CSL_VPAC_NF_CENTER_WEIGHT_CENTRAL_PIXEL_WEIGHT_W00_SHIFT               (0x00000000U)
#define CSL_VPAC_NF_CENTER_WEIGHT_CENTRAL_PIXEL_WEIGHT_W00_MAX                 (0x000001FFU)

/* DEBUG */

#define CSL_VPAC_NF_DEBUG_BYPASS_MASK                                          (0x80000000U)
#define CSL_VPAC_NF_DEBUG_BYPASS_SHIFT                                         (0x0000001FU)
#define CSL_VPAC_NF_DEBUG_BYPASS_MAX                                           (0x00000001U)

#define CSL_VPAC_NF_DEBUG_RSVD_MASK                                            (0x3FFFF000U)
#define CSL_VPAC_NF_DEBUG_RSVD_SHIFT                                           (0x0000000CU)
#define CSL_VPAC_NF_DEBUG_RSVD_MAX                                             (0x0003FFFFU)

#define CSL_VPAC_NF_DEBUG_OUT_COUNT_MASK                                       (0x00000F00U)
#define CSL_VPAC_NF_DEBUG_OUT_COUNT_SHIFT                                      (0x00000008U)
#define CSL_VPAC_NF_DEBUG_OUT_COUNT_MAX                                        (0x0000000FU)

#define CSL_VPAC_NF_DEBUG_IN_COUNT_MASK                                        (0x000000F0U)
#define CSL_VPAC_NF_DEBUG_IN_COUNT_SHIFT                                       (0x00000004U)
#define CSL_VPAC_NF_DEBUG_IN_COUNT_MAX                                         (0x0000000FU)

#define CSL_VPAC_NF_DEBUG_T_STATE_MASK                                         (0x0000000FU)
#define CSL_VPAC_NF_DEBUG_T_STATE_SHIFT                                        (0x00000000U)
#define CSL_VPAC_NF_DEBUG_T_STATE_MAX                                          (0x0000000FU)

/* WEIGHT_LUT */

#define CSL_VPAC_NF_WEIGHT_LUT_W_3_MASK                                        (0xFF000000U)
#define CSL_VPAC_NF_WEIGHT_LUT_W_3_SHIFT                                       (0x00000018U)
#define CSL_VPAC_NF_WEIGHT_LUT_W_3_MAX                                         (0x000000FFU)

#define CSL_VPAC_NF_WEIGHT_LUT_W_2_MASK                                        (0x00FF0000U)
#define CSL_VPAC_NF_WEIGHT_LUT_W_2_SHIFT                                       (0x00000010U)
#define CSL_VPAC_NF_WEIGHT_LUT_W_2_MAX                                         (0x000000FFU)

#define CSL_VPAC_NF_WEIGHT_LUT_W_1_MASK                                        (0x0000FF00U)
#define CSL_VPAC_NF_WEIGHT_LUT_W_1_SHIFT                                       (0x00000008U)
#define CSL_VPAC_NF_WEIGHT_LUT_W_1_MAX                                         (0x000000FFU)

#define CSL_VPAC_NF_WEIGHT_LUT_W_0_MASK                                        (0x000000FFU)
#define CSL_VPAC_NF_WEIGHT_LUT_W_0_SHIFT                                       (0x00000000U)
#define CSL_VPAC_NF_WEIGHT_LUT_W_0_MAX                                         (0x000000FFU)

#ifdef __cplusplus
}
#endif
#endif
