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
 *  Name        : cslr_viss.h
*/
#ifndef CSLR_VISS_H_
#define CSLR_VISS_H_

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
    volatile uint32_t REVISION_REG;              /* PID */
    volatile uint32_t VISS_FUSE_STATUS;          /* FUSE Status Register */
    volatile uint32_t VISS_LINEMEM_SIZE;         /* Maximum Line memory Size supported in VISS */
    volatile uint32_t SYSCONFIG;                 /* SYSCONFIG */
    volatile uint32_t VISS_CNTL;                 /* VISS_CNTL */
    volatile uint32_t FREEPCLK_CFG;              /* Free Pixel Clock config */
    volatile uint8_t  Resv_64[40];
    volatile uint32_t FCP2_CNTL;                 /* Reserved for this version HW. Control register for FCP2 Input path */
    volatile uint32_t LSEOUT_MUX_CNTL;           /* Reserved for this version HW. Control register for LSE Output channel selection */
    volatile uint32_t IROUT_CNTL;                /* Control register for IR Output path */
    volatile uint8_t  Resv_112[36];
    volatile uint32_t VISS_INT_STAT;             /* VISS Top Interrupt status */
    volatile uint8_t  Resv_128[12];
    volatile uint32_t VISS_DBG_CTL;              /* VISS Debug control */
    volatile uint32_t VISS_DBG_STAT;             /* VISS Debug status */
    volatile uint8_t  Resv_256[120];
    volatile uint32_t GLBCECONFIG;               /* SYSCONFIG */
    volatile uint32_t GLBCE_VPSYNCDLY;           /* Delay of GLBCE Core */
    volatile uint32_t GLBCE_INT_STAT;            /* GLBCE Interrupt status */
    volatile uint32_t GLBCE_DBG_CTL;             /* GLBCE Debug control */
    volatile uint32_t GLBCE_DBG_STAT;            /* GLBCE Debug event status */
    volatile uint8_t  Resv_384[108];
    volatile uint32_t NSF4V_INT_STAT;            /* NSF4V Interrupt status */
    volatile uint32_t NSF4V_DBG_CTL;             /* NSF4V Debug control */
    volatile uint32_t NSF4V_DBG_STAT;            /* NSF4V Debug event status */
    volatile uint8_t  Resv_416[20];
    volatile uint32_t DBGEVT_CTL;                /* Debug Event routing control */
    volatile uint8_t  Resv_448[28];
    volatile uint32_t TEST_CNTL;                 /* TEST Control register */
} CSL_viss_topRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_VISS_TOP_REVISION_REG                                              (0x00000000U)
#define CSL_VISS_TOP_VISS_FUSE_STATUS                                          (0x00000004U)
#define CSL_VISS_TOP_VISS_LINEMEM_SIZE                                         (0x00000008U)
#define CSL_VISS_TOP_SYSCONFIG                                                 (0x0000000CU)
#define CSL_VISS_TOP_VISS_CNTL                                                 (0x00000010U)
#define CSL_VISS_TOP_FREEPCLK_CFG                                              (0x00000014U)
#define CSL_VISS_TOP_FCP2_CNTL                                                 (0x00000040U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL                                           (0x00000044U)
#define CSL_VISS_TOP_IROUT_CNTL                                                (0x00000048U)
#define CSL_VISS_TOP_VISS_INT_STAT                                             (0x00000070U)
#define CSL_VISS_TOP_VISS_DBG_CTL                                              (0x00000080U)
#define CSL_VISS_TOP_VISS_DBG_STAT                                             (0x00000084U)
#define CSL_VISS_TOP_GLBCECONFIG                                               (0x00000100U)
#define CSL_VISS_TOP_GLBCE_VPSYNCDLY                                           (0x00000104U)
#define CSL_VISS_TOP_GLBCE_INT_STAT                                            (0x00000108U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL                                             (0x0000010CU)
#define CSL_VISS_TOP_GLBCE_DBG_STAT                                            (0x00000110U)
#define CSL_VISS_TOP_NSF4V_INT_STAT                                            (0x00000180U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL                                             (0x00000184U)
#define CSL_VISS_TOP_NSF4V_DBG_STAT                                            (0x00000188U)
#define CSL_VISS_TOP_DBGEVT_CTL                                                (0x000001A0U)
#define CSL_VISS_TOP_TEST_CNTL                                                 (0x000001C0U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* REVISION_REG */

#define CSL_VISS_TOP_REVISION_REG_SCHEME_MASK                                  (0xC0000000U)
#define CSL_VISS_TOP_REVISION_REG_SCHEME_SHIFT                                 (0x0000001EU)
#define CSL_VISS_TOP_REVISION_REG_SCHEME_MAX                                   (0x00000003U)

#define CSL_VISS_TOP_REVISION_REG_BU_MASK                                      (0x30000000U)
#define CSL_VISS_TOP_REVISION_REG_BU_SHIFT                                     (0x0000001CU)
#define CSL_VISS_TOP_REVISION_REG_BU_MAX                                       (0x00000003U)

#define CSL_VISS_TOP_REVISION_REG_FUNC_MASK                                    (0x0FFF0000U)
#define CSL_VISS_TOP_REVISION_REG_FUNC_SHIFT                                   (0x00000010U)
#define CSL_VISS_TOP_REVISION_REG_FUNC_MAX                                     (0x00000FFFU)

#define CSL_VISS_TOP_REVISION_REG_RTL_MASK                                     (0x0000F800U)
#define CSL_VISS_TOP_REVISION_REG_RTL_SHIFT                                    (0x0000000BU)
#define CSL_VISS_TOP_REVISION_REG_RTL_MAX                                      (0x0000001FU)

#define CSL_VISS_TOP_REVISION_REG_MAJOR_MASK                                   (0x00000700U)
#define CSL_VISS_TOP_REVISION_REG_MAJOR_SHIFT                                  (0x00000008U)
#define CSL_VISS_TOP_REVISION_REG_MAJOR_MAX                                    (0x00000007U)

#define CSL_VISS_TOP_REVISION_REG_CUSTOM_MASK                                  (0x000000C0U)
#define CSL_VISS_TOP_REVISION_REG_CUSTOM_SHIFT                                 (0x00000006U)
#define CSL_VISS_TOP_REVISION_REG_CUSTOM_MAX                                   (0x00000003U)

#define CSL_VISS_TOP_REVISION_REG_MINOR_MASK                                   (0x0000003FU)
#define CSL_VISS_TOP_REVISION_REG_MINOR_SHIFT                                  (0x00000000U)
#define CSL_VISS_TOP_REVISION_REG_MINOR_MAX                                    (0x0000003FU)

/* VISS_FUSE_STATUS */

#define CSL_VISS_TOP_VISS_FUSE_STATUS_NIKON_DISABLE_MASK                       (0x00000002U)
#define CSL_VISS_TOP_VISS_FUSE_STATUS_NIKON_DISABLE_SHIFT                      (0x00000001U)
#define CSL_VISS_TOP_VISS_FUSE_STATUS_NIKON_DISABLE_MAX                        (0x00000001U)

#define CSL_VISS_TOP_VISS_FUSE_STATUS_GLBCE_DISABLE_MASK                       (0x00000001U)
#define CSL_VISS_TOP_VISS_FUSE_STATUS_GLBCE_DISABLE_SHIFT                      (0x00000000U)
#define CSL_VISS_TOP_VISS_FUSE_STATUS_GLBCE_DISABLE_MAX                        (0x00000001U)

/* VISS_LINEMEM_SIZE */

#define CSL_VISS_TOP_VISS_LINEMEM_SIZE_LINEMEM_SZ_MASK                         (0x00003FFFU)
#define CSL_VISS_TOP_VISS_LINEMEM_SIZE_LINEMEM_SZ_SHIFT                        (0x00000000U)
#define CSL_VISS_TOP_VISS_LINEMEM_SIZE_LINEMEM_SZ_MAX                          (0x00003FFFU)

/* SYSCONFIG */

#define CSL_VISS_TOP_SYSCONFIG_CLKCG_OVERIDE_MASK                              (0x00000002U)
#define CSL_VISS_TOP_SYSCONFIG_CLKCG_OVERIDE_SHIFT                             (0x00000001U)
#define CSL_VISS_TOP_SYSCONFIG_CLKCG_OVERIDE_MAX                               (0x00000001U)

/* VISS_CNTL */

#define CSL_VISS_TOP_VISS_CNTL_PCID_EN_MASK                                    (0x00000008U)
#define CSL_VISS_TOP_VISS_CNTL_PCID_EN_SHIFT                                   (0x00000003U)
#define CSL_VISS_TOP_VISS_CNTL_PCID_EN_MAX                                     (0x00000001U)

#define CSL_VISS_TOP_VISS_CNTL_CAC_EN_MASK                                     (0x00000004U)
#define CSL_VISS_TOP_VISS_CNTL_CAC_EN_SHIFT                                    (0x00000002U)
#define CSL_VISS_TOP_VISS_CNTL_CAC_EN_MAX                                      (0x00000001U)

#define CSL_VISS_TOP_VISS_CNTL_NSF4V_EN_MASK                                   (0x00000002U)
#define CSL_VISS_TOP_VISS_CNTL_NSF4V_EN_SHIFT                                  (0x00000001U)
#define CSL_VISS_TOP_VISS_CNTL_NSF4V_EN_MAX                                    (0x00000001U)

#define CSL_VISS_TOP_VISS_CNTL_GLBCE_EN_MASK                                   (0x00000001U)
#define CSL_VISS_TOP_VISS_CNTL_GLBCE_EN_SHIFT                                  (0x00000000U)
#define CSL_VISS_TOP_VISS_CNTL_GLBCE_EN_MAX                                    (0x00000001U)

/* FREEPCLK_CFG */

#define CSL_VISS_TOP_FREEPCLK_CFG_PCLKFREE_EN_MASK                             (0x00000001U)
#define CSL_VISS_TOP_FREEPCLK_CFG_PCLKFREE_EN_SHIFT                            (0x00000000U)
#define CSL_VISS_TOP_FREEPCLK_CFG_PCLKFREE_EN_MAX                              (0x00000001U)

#define CSL_VISS_TOP_FREEPCLK_CFG_PCLKFREE_STATE_MASK                          (0x00000002U)
#define CSL_VISS_TOP_FREEPCLK_CFG_PCLKFREE_STATE_SHIFT                         (0x00000001U)
#define CSL_VISS_TOP_FREEPCLK_CFG_PCLKFREE_STATE_MAX                           (0x00000001U)

#define CSL_VISS_TOP_FREEPCLK_CFG_CNTVAL_MASK                                  (0x1FFF0000U)
#define CSL_VISS_TOP_FREEPCLK_CFG_CNTVAL_SHIFT                                 (0x00000010U)
#define CSL_VISS_TOP_FREEPCLK_CFG_CNTVAL_MAX                                   (0x00001FFFU)

/* FCP2_CNTL */

#define CSL_VISS_TOP_FCP2_CNTL_IN_PIPEDLY_MASK                                 (0x00FF0000U)
#define CSL_VISS_TOP_FCP2_CNTL_IN_PIPEDLY_SHIFT                                (0x00000010U)
#define CSL_VISS_TOP_FCP2_CNTL_IN_PIPEDLY_MAX                                  (0x000000FFU)

#define CSL_VISS_TOP_FCP2_CNTL_IN_SEL_MASK                                     (0x00000006U)
#define CSL_VISS_TOP_FCP2_CNTL_IN_SEL_SHIFT                                    (0x00000001U)
#define CSL_VISS_TOP_FCP2_CNTL_IN_SEL_MAX                                      (0x00000003U)

#define CSL_VISS_TOP_FCP2_CNTL_PIXCLK_EN_MASK                                  (0x00000001U)
#define CSL_VISS_TOP_FCP2_CNTL_PIXCLK_EN_SHIFT                                 (0x00000000U)
#define CSL_VISS_TOP_FCP2_CNTL_PIXCLK_EN_MAX                                   (0x00000001U)

/* LSEOUT_MUX_CNTL */

#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_Y12SEL_MASK                               (0x00000007U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_Y12SEL_SHIFT                              (0x00000000U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_Y12SEL_MAX                                (0x00000007U)

#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_UV12SEL_MASK                              (0x00000070U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_UV12SEL_SHIFT                             (0x00000004U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_UV12SEL_MAX                               (0x00000007U)

#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_Y8SEL_MASK                                (0x00000700U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_Y8SEL_SHIFT                               (0x00000008U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_Y8SEL_MAX                                 (0x00000007U)

#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_UV8SEL_MASK                               (0x00007000U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_UV8SEL_SHIFT                              (0x0000000CU)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_UV8SEL_MAX                                (0x00000007U)

#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_S8SEL_MASK                                (0x00030000U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_S8SEL_SHIFT                               (0x00000010U)
#define CSL_VISS_TOP_LSEOUT_MUX_CNTL_S8SEL_MAX                                 (0x00000003U)

/* IROUT_CNTL */

#define CSL_VISS_TOP_IROUT_CNTL_PIPEDLY_MASK                                   (0x01FF0000U)
#define CSL_VISS_TOP_IROUT_CNTL_PIPEDLY_SHIFT                                  (0x00000010U)
#define CSL_VISS_TOP_IROUT_CNTL_PIPEDLY_MAX                                    (0x000001FFU)

#define CSL_VISS_TOP_IROUT_CNTL_DWIDTH_MASK                                    (0x00001F00U)
#define CSL_VISS_TOP_IROUT_CNTL_DWIDTH_SHIFT                                   (0x00000008U)
#define CSL_VISS_TOP_IROUT_CNTL_DWIDTH_MAX                                     (0x0000001FU)

/* VISS_INT_STAT */

#define CSL_VISS_TOP_VISS_INT_STAT_IROUT_OVF_ERR_MASK                          (0x00000001U)
#define CSL_VISS_TOP_VISS_INT_STAT_IROUT_OVF_ERR_SHIFT                         (0x00000000U)
#define CSL_VISS_TOP_VISS_INT_STAT_IROUT_OVF_ERR_MAX                           (0x00000001U)

/* VISS_DBG_CTL */

#define CSL_VISS_TOP_VISS_DBG_CTL_IROUT_STALL_EN_MASK                          (0x00000004U)
#define CSL_VISS_TOP_VISS_DBG_CTL_IROUT_STALL_EN_SHIFT                         (0x00000002U)
#define CSL_VISS_TOP_VISS_DBG_CTL_IROUT_STALL_EN_MAX                           (0x00000001U)

#define CSL_VISS_TOP_VISS_DBG_CTL_PRTL_WR_EN_MASK                              (0x00000002U)
#define CSL_VISS_TOP_VISS_DBG_CTL_PRTL_WR_EN_SHIFT                             (0x00000001U)
#define CSL_VISS_TOP_VISS_DBG_CTL_PRTL_WR_EN_MAX                               (0x00000001U)

#define CSL_VISS_TOP_VISS_DBG_CTL_DBG_EN_MASK                                  (0x00000001U)
#define CSL_VISS_TOP_VISS_DBG_CTL_DBG_EN_SHIFT                                 (0x00000000U)
#define CSL_VISS_TOP_VISS_DBG_CTL_DBG_EN_MAX                                   (0x00000001U)

/* VISS_DBG_STAT */

#define CSL_VISS_TOP_VISS_DBG_STAT_IROUT_STALL_MASK                            (0x00000004U)
#define CSL_VISS_TOP_VISS_DBG_STAT_IROUT_STALL_SHIFT                           (0x00000002U)
#define CSL_VISS_TOP_VISS_DBG_STAT_IROUT_STALL_MAX                             (0x00000001U)

#define CSL_VISS_TOP_VISS_DBG_STAT_PRTL_WR_MASK                                (0x00000002U)
#define CSL_VISS_TOP_VISS_DBG_STAT_PRTL_WR_SHIFT                               (0x00000001U)
#define CSL_VISS_TOP_VISS_DBG_STAT_PRTL_WR_MAX                                 (0x00000001U)

/* GLBCECONFIG */

#define CSL_VISS_TOP_GLBCECONFIG_GLBCE_PCLKFREE_MASK                           (0x00000001U)
#define CSL_VISS_TOP_GLBCECONFIG_GLBCE_PCLKFREE_SHIFT                          (0x00000000U)
#define CSL_VISS_TOP_GLBCECONFIG_GLBCE_PCLKFREE_MAX                            (0x00000001U)

/* GLBCE_VPSYNCDLY */

#define CSL_VISS_TOP_GLBCE_VPSYNCDLY_V_DLY_MASK                                (0x0000FF00U)
#define CSL_VISS_TOP_GLBCE_VPSYNCDLY_V_DLY_SHIFT                               (0x00000008U)
#define CSL_VISS_TOP_GLBCE_VPSYNCDLY_V_DLY_MAX                                 (0x000000FFU)

#define CSL_VISS_TOP_GLBCE_VPSYNCDLY_H_DLY_MASK                                (0x000000FFU)
#define CSL_VISS_TOP_GLBCE_VPSYNCDLY_H_DLY_SHIFT                               (0x00000000U)
#define CSL_VISS_TOP_GLBCE_VPSYNCDLY_H_DLY_MAX                                 (0x000000FFU)

/* GLBCE_INT_STAT */

#define CSL_VISS_TOP_GLBCE_INT_STAT_VSYNC_ERR_MASK                             (0x00000040U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_VSYNC_ERR_SHIFT                            (0x00000006U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_VSYNC_ERR_MAX                              (0x00000001U)

#define CSL_VISS_TOP_GLBCE_INT_STAT_HSYNC_ERR_MASK                             (0x00000020U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_HSYNC_ERR_SHIFT                            (0x00000005U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_HSYNC_ERR_MAX                              (0x00000001U)

#define CSL_VISS_TOP_GLBCE_INT_STAT_VP_ERR_MASK                                (0x00000010U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_VP_ERR_SHIFT                               (0x00000004U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_VP_ERR_MAX                                 (0x00000001U)

#define CSL_VISS_TOP_GLBCE_INT_STAT_FILT_DONE_MASK                             (0x00000008U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_FILT_DONE_SHIFT                            (0x00000003U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_FILT_DONE_MAX                              (0x00000001U)

#define CSL_VISS_TOP_GLBCE_INT_STAT_FILT_START_MASK                            (0x00000004U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_FILT_START_SHIFT                           (0x00000002U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_FILT_START_MAX                             (0x00000001U)

#define CSL_VISS_TOP_GLBCE_INT_STAT_STATMEM_CFG_ERR_MASK                       (0x00000002U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_STATMEM_CFG_ERR_SHIFT                      (0x00000001U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_STATMEM_CFG_ERR_MAX                        (0x00000001U)

#define CSL_VISS_TOP_GLBCE_INT_STAT_MMR_CFG_ERR_MASK                           (0x00000001U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_MMR_CFG_ERR_SHIFT                          (0x00000000U)
#define CSL_VISS_TOP_GLBCE_INT_STAT_MMR_CFG_ERR_MAX                            (0x00000001U)

/* GLBCE_DBG_CTL */

#define CSL_VISS_TOP_GLBCE_DBG_CTL_EOF_EN_MASK                                 (0x00000010U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_EOF_EN_SHIFT                                (0x00000004U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_EOF_EN_MAX                                  (0x00000001U)

#define CSL_VISS_TOP_GLBCE_DBG_CTL_EOL_EN_MASK                                 (0x00000008U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_EOL_EN_SHIFT                                (0x00000003U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_EOL_EN_MAX                                  (0x00000001U)

#define CSL_VISS_TOP_GLBCE_DBG_CTL_SOF_EN_MASK                                 (0x00000004U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_SOF_EN_SHIFT                                (0x00000002U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_SOF_EN_MAX                                  (0x00000001U)

#define CSL_VISS_TOP_GLBCE_DBG_CTL_SOL_EN_MASK                                 (0x00000002U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_SOL_EN_SHIFT                                (0x00000001U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_SOL_EN_MAX                                  (0x00000001U)

#define CSL_VISS_TOP_GLBCE_DBG_CTL_DBG_EN_MASK                                 (0x00000001U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_DBG_EN_SHIFT                                (0x00000000U)
#define CSL_VISS_TOP_GLBCE_DBG_CTL_DBG_EN_MAX                                  (0x00000001U)

/* GLBCE_DBG_STAT */

#define CSL_VISS_TOP_GLBCE_DBG_STAT_EOF_MASK                                   (0x00000010U)
#define CSL_VISS_TOP_GLBCE_DBG_STAT_EOF_SHIFT                                  (0x00000004U)
#define CSL_VISS_TOP_GLBCE_DBG_STAT_EOF_MAX                                    (0x00000001U)

#define CSL_VISS_TOP_GLBCE_DBG_STAT_EOL_MASK                                   (0x00000008U)
#define CSL_VISS_TOP_GLBCE_DBG_STAT_EOL_SHIFT                                  (0x00000003U)
#define CSL_VISS_TOP_GLBCE_DBG_STAT_EOL_MAX                                    (0x00000001U)

#define CSL_VISS_TOP_GLBCE_DBG_STAT_SOF_MASK                                   (0x00000004U)
#define CSL_VISS_TOP_GLBCE_DBG_STAT_SOF_SHIFT                                  (0x00000002U)
#define CSL_VISS_TOP_GLBCE_DBG_STAT_SOF_MAX                                    (0x00000001U)

#define CSL_VISS_TOP_GLBCE_DBG_STAT_SOL_MASK                                   (0x00000002U)
#define CSL_VISS_TOP_GLBCE_DBG_STAT_SOL_SHIFT                                  (0x00000001U)
#define CSL_VISS_TOP_GLBCE_DBG_STAT_SOL_MAX                                    (0x00000001U)

/* NSF4V_INT_STAT */

#define CSL_VISS_TOP_NSF4V_INT_STAT_VBLANK_ERR_MASK                            (0x00000010U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_VBLANK_ERR_SHIFT                           (0x00000004U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_VBLANK_ERR_MAX                             (0x00000001U)

#define CSL_VISS_TOP_NSF4V_INT_STAT_HBLANK_ERR_MASK                            (0x00000008U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_HBLANK_ERR_SHIFT                           (0x00000003U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_HBLANK_ERR_MAX                             (0x00000001U)

#define CSL_VISS_TOP_NSF4V_INT_STAT_RAWHIST_CFG_ERR_MASK                       (0x00000004U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_RAWHIST_CFG_ERR_SHIFT                      (0x00000002U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_RAWHIST_CFG_ERR_MAX                        (0x00000001U)

#define CSL_VISS_TOP_NSF4V_INT_STAT_LUT_CFG_ERR_MASK                           (0x00000002U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_LUT_CFG_ERR_SHIFT                          (0x00000001U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_LUT_CFG_ERR_MAX                            (0x00000001U)

#define CSL_VISS_TOP_NSF4V_INT_STAT_LINEMEM_CFG_ERR_MASK                       (0x00000001U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_LINEMEM_CFG_ERR_SHIFT                      (0x00000000U)
#define CSL_VISS_TOP_NSF4V_INT_STAT_LINEMEM_CFG_ERR_MAX                        (0x00000001U)

/* NSF4V_DBG_CTL */

#define CSL_VISS_TOP_NSF4V_DBG_CTL_EOF_EN_MASK                                 (0x00000010U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_EOF_EN_SHIFT                                (0x00000004U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_EOF_EN_MAX                                  (0x00000001U)

#define CSL_VISS_TOP_NSF4V_DBG_CTL_EOL_EN_MASK                                 (0x00000008U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_EOL_EN_SHIFT                                (0x00000003U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_EOL_EN_MAX                                  (0x00000001U)

#define CSL_VISS_TOP_NSF4V_DBG_CTL_SOF_EN_MASK                                 (0x00000004U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_SOF_EN_SHIFT                                (0x00000002U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_SOF_EN_MAX                                  (0x00000001U)

#define CSL_VISS_TOP_NSF4V_DBG_CTL_SOL_EN_MASK                                 (0x00000002U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_SOL_EN_SHIFT                                (0x00000001U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_SOL_EN_MAX                                  (0x00000001U)

#define CSL_VISS_TOP_NSF4V_DBG_CTL_DBG_EN_MASK                                 (0x00000001U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_DBG_EN_SHIFT                                (0x00000000U)
#define CSL_VISS_TOP_NSF4V_DBG_CTL_DBG_EN_MAX                                  (0x00000001U)

/* NSF4V_DBG_STAT */

#define CSL_VISS_TOP_NSF4V_DBG_STAT_EOF_MASK                                   (0x00000010U)
#define CSL_VISS_TOP_NSF4V_DBG_STAT_EOF_SHIFT                                  (0x00000004U)
#define CSL_VISS_TOP_NSF4V_DBG_STAT_EOF_MAX                                    (0x00000001U)

#define CSL_VISS_TOP_NSF4V_DBG_STAT_EOL_MASK                                   (0x00000008U)
#define CSL_VISS_TOP_NSF4V_DBG_STAT_EOL_SHIFT                                  (0x00000003U)
#define CSL_VISS_TOP_NSF4V_DBG_STAT_EOL_MAX                                    (0x00000001U)

#define CSL_VISS_TOP_NSF4V_DBG_STAT_SOF_MASK                                   (0x00000004U)
#define CSL_VISS_TOP_NSF4V_DBG_STAT_SOF_SHIFT                                  (0x00000002U)
#define CSL_VISS_TOP_NSF4V_DBG_STAT_SOF_MAX                                    (0x00000001U)

#define CSL_VISS_TOP_NSF4V_DBG_STAT_SOL_MASK                                   (0x00000002U)
#define CSL_VISS_TOP_NSF4V_DBG_STAT_SOL_SHIFT                                  (0x00000001U)
#define CSL_VISS_TOP_NSF4V_DBG_STAT_SOL_MAX                                    (0x00000001U)

/* DBGEVT_CTL */

#define CSL_VISS_TOP_DBGEVT_CTL_SEL1_MASK                                      (0x00000003U)
#define CSL_VISS_TOP_DBGEVT_CTL_SEL1_SHIFT                                     (0x00000000U)
#define CSL_VISS_TOP_DBGEVT_CTL_SEL1_MAX                                       (0x00000003U)

#define CSL_VISS_TOP_DBGEVT_CTL_SEL2_MASK                                      (0x0000000CU)
#define CSL_VISS_TOP_DBGEVT_CTL_SEL2_SHIFT                                     (0x00000002U)
#define CSL_VISS_TOP_DBGEVT_CTL_SEL2_MAX                                       (0x00000003U)

#define CSL_VISS_TOP_DBGEVT_CTL_SEL3_MASK                                      (0x00000030U)
#define CSL_VISS_TOP_DBGEVT_CTL_SEL3_SHIFT                                     (0x00000004U)
#define CSL_VISS_TOP_DBGEVT_CTL_SEL3_MAX                                       (0x00000003U)

/* TEST_CNTL */

#define CSL_VISS_TOP_TEST_CNTL_GATED_MEM_CLKF_MASK                             (0x00000001U)
#define CSL_VISS_TOP_TEST_CNTL_GATED_MEM_CLKF_SHIFT                            (0x00000000U)
#define CSL_VISS_TOP_TEST_CNTL_GATED_MEM_CLKF_MAX                              (0x00000001U)

#ifdef __cplusplus
}
#endif
#endif
