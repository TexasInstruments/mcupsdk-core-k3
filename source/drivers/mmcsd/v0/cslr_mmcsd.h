/********************************************************************
 * Copyright (C) 2020 Texas Instruments Incorporated.
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
 *  Name        : cslr_mmcsd.h
*/
#ifndef CSLR_MMCSD_H_
#define CSLR_MMCSD_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_MMC_CTLCFG_REGS_BASE                                               (0x00000000U)
#define CSL_MMC_ECC_AGGR_REGS_BASE                                             (0x00000000U)
#define CSL_MMC_SSCFG_REGS_BASE                                                (0x00000000U)


/**************************************************************************
* Hardware Region  : Subsystem Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t SS_ID_REV_REG;             /* Subsystem ID and Revision Register */
    volatile uint8_t  Resv_16[12];
    volatile uint32_t CTL_CFG_1_REG;             /* Controller Config 1 Register */
    volatile uint32_t CTL_CFG_2_REG;             /* Controller Config 2 Register */
    volatile uint32_t CTL_CFG_3_REG;             /* Controller Config 3 Register */
    volatile uint32_t CTL_CFG_4_REG;             /* Controller Config 4 Register */
    volatile uint32_t CTL_CFG_5_REG;             /* Controller Config 5 Register */
    volatile uint32_t CTL_CFG_6_REG;             /* Controller Config 6 Register */
    volatile uint32_t CTL_CFG_7_REG;             /* Controller Config 7 Register */
    volatile uint32_t CTL_CFG_8_REG;             /* Controller Config 8 Register */
    volatile uint32_t CTL_CFG_9_REG;             /* Controller Config 9 Register */
    volatile uint32_t CTL_CFG_10_REG;            /* Controller Config 10 Register */
    volatile uint32_t CTL_CFG_11_REG;            /* Controller Config 11 Register */
    volatile uint32_t CTL_CFG_12_REG;            /* Controller Config 12 Register */
    volatile uint32_t CTL_CFG_13_REG;            /* Controller Config 13 Register */
    volatile uint32_t CTL_CFG_14_REG;            /* Controller Config 14 Register */
    volatile uint8_t  Resv_96[24];
    volatile uint32_t CTL_STAT_1_REG;            /* Controller Status 1 Register */
    volatile uint32_t CTL_STAT_2_REG;            /* Controller Status 2 Register */
    volatile uint32_t CTL_STAT_3_REG;            /* Controller Status 3 Register */
    volatile uint32_t CTL_STAT_4_REG;            /* Controller Status 4 Register */
    volatile uint32_t CTL_STAT_5_REG;            /* Controller Status 5 Register */
    volatile uint32_t CTL_STAT_6_REG;            /* Controller Status 6 Register */
    volatile uint8_t  Resv_256[136];
    volatile uint32_t PHY_CTRL_1_REG;            /* PHY Control 1 Register */
    volatile uint32_t PHY_CTRL_2_REG;            /* PHY Control 2 Register */
    volatile uint32_t PHY_CTRL_3_REG;            /* PHY Control 3 Register */
    volatile uint32_t PHY_CTRL_4_REG;            /* PHY Control 4 Register */
    volatile uint32_t PHY_CTRL_5_REG;            /* PHY Control 5 Register */
    volatile uint32_t PHY_CTRL_6_REG;            /* PHY Control 6 Register */
    volatile uint8_t  Resv_304[24];
    volatile uint32_t PHY_STAT_1_REG;            /* PHY Status 1 Register */
    volatile uint32_t PHY_STAT_2_REG;            /* PHY Status 2 Register */
} CSL_mmc_sscfgRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MMC_SSCFG_SS_ID_REV_REG                                            (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG                                            (0x00000010U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG                                            (0x00000014U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG                                            (0x00000018U)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG                                            (0x0000001CU)
#define CSL_MMC_SSCFG_CTL_CFG_5_REG                                            (0x00000020U)
#define CSL_MMC_SSCFG_CTL_CFG_6_REG                                            (0x00000024U)
#define CSL_MMC_SSCFG_CTL_CFG_7_REG                                            (0x00000028U)
#define CSL_MMC_SSCFG_CTL_CFG_8_REG                                            (0x0000002CU)
#define CSL_MMC_SSCFG_CTL_CFG_9_REG                                            (0x00000030U)
#define CSL_MMC_SSCFG_CTL_CFG_10_REG                                           (0x00000034U)
#define CSL_MMC_SSCFG_CTL_CFG_11_REG                                           (0x00000038U)
#define CSL_MMC_SSCFG_CTL_CFG_12_REG                                           (0x0000003CU)
#define CSL_MMC_SSCFG_CTL_CFG_13_REG                                           (0x00000040U)
#define CSL_MMC_SSCFG_CTL_CFG_14_REG                                           (0x00000044U)
#define CSL_MMC_SSCFG_CTL_STAT_1_REG                                           (0x00000060U)
#define CSL_MMC_SSCFG_CTL_STAT_2_REG                                           (0x00000064U)
#define CSL_MMC_SSCFG_CTL_STAT_3_REG                                           (0x00000068U)
#define CSL_MMC_SSCFG_CTL_STAT_4_REG                                           (0x0000006CU)
#define CSL_MMC_SSCFG_CTL_STAT_5_REG                                           (0x00000070U)
#define CSL_MMC_SSCFG_CTL_STAT_6_REG                                           (0x00000074U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG                                           (0x00000100U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG                                           (0x00000104U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG                                           (0x00000108U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG                                           (0x0000010CU)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG                                           (0x00000110U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG                                           (0x00000114U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG                                           (0x00000130U)
#define CSL_MMC_SSCFG_PHY_STAT_2_REG                                           (0x00000134U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* SS_ID_REV_REG */

#define CSL_MMC_SSCFG_SS_ID_REV_REG_MOD_ID_MASK                                (0xFFFF0000U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_MOD_ID_SHIFT                               (0x00000010U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_MOD_ID_RESETVAL                            (0x00006841U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_MOD_ID_MAX                                 (0x0000FFFFU)

#define CSL_MMC_SSCFG_SS_ID_REV_REG_RTL_VER_MASK                               (0x0000F800U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_RTL_VER_SHIFT                              (0x0000000BU)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_RTL_VER_RESETVAL                           (0x0000000AU)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_RTL_VER_MAX                                (0x0000001FU)

#define CSL_MMC_SSCFG_SS_ID_REV_REG_MAJ_REV_MASK                               (0x00000700U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_MAJ_REV_SHIFT                              (0x00000008U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_MAJ_REV_RESETVAL                           (0x00000002U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_MAJ_REV_MAX                                (0x00000007U)

#define CSL_MMC_SSCFG_SS_ID_REV_REG_CUSTOM_MASK                                (0x000000C0U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_CUSTOM_SHIFT                               (0x00000006U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_CUSTOM_RESETVAL                            (0x00000000U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_CUSTOM_MAX                                 (0x00000003U)

#define CSL_MMC_SSCFG_SS_ID_REV_REG_MIN_REV_MASK                               (0x0000003FU)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_MIN_REV_SHIFT                              (0x00000000U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_MIN_REV_RESETVAL                           (0x00000000U)
#define CSL_MMC_SSCFG_SS_ID_REV_REG_MIN_REV_MAX                                (0x0000003FU)

#define CSL_MMC_SSCFG_SS_ID_REV_REG_RESETVAL                                   (0x68415200U)

/* CTL_CFG_1_REG */

#define CSL_MMC_SSCFG_CTL_CFG_1_REG_TUNINGCOUNT_MASK                           (0x3F000000U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_TUNINGCOUNT_SHIFT                          (0x00000018U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_TUNINGCOUNT_RESETVAL                       (0x00000020U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_TUNINGCOUNT_MAX                            (0x0000003FU)

#define CSL_MMC_SSCFG_CTL_CFG_1_REG_ASYNCWKUPENA_MASK                          (0x00100000U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_ASYNCWKUPENA_SHIFT                         (0x00000014U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_ASYNCWKUPENA_RESETVAL                      (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_ASYNCWKUPENA_MAX                           (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_1_REG_CQFMUL_MASK                                (0x0000F000U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_CQFMUL_SHIFT                               (0x0000000CU)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_CQFMUL_RESETVAL                            (0x00000003U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_CQFMUL_MAX                                 (0x0000000FU)

#define CSL_MMC_SSCFG_CTL_CFG_1_REG_CQFVAL_MASK                                (0x000003FFU)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_CQFVAL_SHIFT                               (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_CQFVAL_RESETVAL                            (0x000000C8U)
#define CSL_MMC_SSCFG_CTL_CFG_1_REG_CQFVAL_MAX                                 (0x000003FFU)

#define CSL_MMC_SSCFG_CTL_CFG_1_REG_RESETVAL                                   (0x201030C8U)

/* CTL_CFG_2_REG */

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SLOTTYPE_MASK                              (0xC0000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SLOTTYPE_SHIFT                             (0x0000001EU)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SLOTTYPE_RESETVAL                          (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SLOTTYPE_MAX                               (0x00000003U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_ASYNCHINTRSUPPORT_MASK                     (0x20000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_ASYNCHINTRSUPPORT_SHIFT                    (0x0000001DU)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_ASYNCHINTRSUPPORT_RESETVAL                 (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_ASYNCHINTRSUPPORT_MAX                      (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT1P8VOLT_MASK                        (0x04000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT1P8VOLT_SHIFT                       (0x0000001AU)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT1P8VOLT_RESETVAL                    (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT1P8VOLT_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT3P0VOLT_MASK                        (0x02000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT3P0VOLT_SHIFT                       (0x00000019U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT3P0VOLT_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT3P0VOLT_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT3P3VOLT_MASK                        (0x01000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT3P3VOLT_SHIFT                       (0x00000018U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT3P3VOLT_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT3P3VOLT_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUSPRESSUPPORT_MASK                        (0x00800000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUSPRESSUPPORT_SHIFT                       (0x00000017U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUSPRESSUPPORT_RESETVAL                    (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUSPRESSUPPORT_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SDMASUPPORT_MASK                           (0x00400000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SDMASUPPORT_SHIFT                          (0x00000016U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SDMASUPPORT_RESETVAL                       (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SDMASUPPORT_MAX                            (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_HIGHSPEEDSUPPORT_MASK                      (0x00200000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_HIGHSPEEDSUPPORT_SHIFT                     (0x00000015U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_HIGHSPEEDSUPPORT_RESETVAL                  (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_HIGHSPEEDSUPPORT_MAX                       (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_ADMA2SUPPORT_MASK                          (0x00080000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_ADMA2SUPPORT_SHIFT                         (0x00000013U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_ADMA2SUPPORT_RESETVAL                      (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_ADMA2SUPPORT_MAX                           (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT8BIT_MASK                           (0x00040000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT8BIT_SHIFT                          (0x00000012U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT8BIT_RESETVAL                       (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_SUPPORT8BIT_MAX                            (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_MAXBLKLENGTH_MASK                          (0x00030000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_MAXBLKLENGTH_SHIFT                         (0x00000010U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_MAXBLKLENGTH_RESETVAL                      (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_MAXBLKLENGTH_MAX                           (0x00000003U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_BASECLKFREQ_MASK                           (0x0000FF00U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_BASECLKFREQ_SHIFT                          (0x00000008U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_BASECLKFREQ_RESETVAL                       (0x000000C8U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_BASECLKFREQ_MAX                            (0x000000FFU)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_TIMEOUTCLKUNIT_MASK                        (0x00000080U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_TIMEOUTCLKUNIT_SHIFT                       (0x00000007U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_TIMEOUTCLKUNIT_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_TIMEOUTCLKUNIT_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_TIMEOUTCLKFREQ_MASK                        (0x0000003FU)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_TIMEOUTCLKFREQ_SHIFT                       (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_TIMEOUTCLKFREQ_RESETVAL                    (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_2_REG_TIMEOUTCLKFREQ_MAX                         (0x0000003FU)

#define CSL_MMC_SSCFG_CTL_CFG_2_REG_RESETVAL                                   (0x64ECC801U)

/* CTL_CFG_3_REG */

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_HS400SUPPORT_MASK                          (0x80000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_HS400SUPPORT_SHIFT                         (0x0000001FU)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_HS400SUPPORT_RESETVAL                      (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_HS400SUPPORT_MAX                           (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SUPPORT1P8VDD2_MASK                        (0x10000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SUPPORT1P8VDD2_SHIFT                       (0x0000001CU)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SUPPORT1P8VDD2_RESETVAL                    (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SUPPORT1P8VDD2_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_ADMA3SUPPORT_MASK                          (0x08000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_ADMA3SUPPORT_SHIFT                         (0x0000001BU)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_ADMA3SUPPORT_RESETVAL                      (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_ADMA3SUPPORT_MAX                           (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_CLOCKMULTIPLIER_MASK                       (0x00FF0000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_CLOCKMULTIPLIER_SHIFT                      (0x00000010U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_CLOCKMULTIPLIER_RESETVAL                   (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_CLOCKMULTIPLIER_MAX                        (0x000000FFU)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_RETUNINGMODES_MASK                         (0x0000C000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_RETUNINGMODES_SHIFT                        (0x0000000EU)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_RETUNINGMODES_RESETVAL                     (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_RETUNINGMODES_MAX                          (0x00000003U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_TUNINGFORSDR50_MASK                        (0x00002000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_TUNINGFORSDR50_SHIFT                       (0x0000000DU)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_TUNINGFORSDR50_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_TUNINGFORSDR50_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_RETUNINGTIMERCNT_MASK                      (0x00000F00U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_RETUNINGTIMERCNT_SHIFT                     (0x00000008U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_RETUNINGTIMERCNT_RESETVAL                  (0x00000004U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_RETUNINGTIMERCNT_MAX                       (0x0000000FU)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_TYPE4SUPPORT_MASK                          (0x00000080U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_TYPE4SUPPORT_SHIFT                         (0x00000007U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_TYPE4SUPPORT_RESETVAL                      (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_TYPE4SUPPORT_MAX                           (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_DDRIVERSUPPORT_MASK                        (0x00000040U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_DDRIVERSUPPORT_SHIFT                       (0x00000006U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_DDRIVERSUPPORT_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_DDRIVERSUPPORT_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_CDRIVERSUPPORT_MASK                        (0x00000020U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_CDRIVERSUPPORT_SHIFT                       (0x00000005U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_CDRIVERSUPPORT_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_CDRIVERSUPPORT_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_ADRIVERSUPPORT_MASK                        (0x00000010U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_ADRIVERSUPPORT_SHIFT                       (0x00000004U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_ADRIVERSUPPORT_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_ADRIVERSUPPORT_MAX                         (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_DDR50SUPPORT_MASK                          (0x00000004U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_DDR50SUPPORT_SHIFT                         (0x00000002U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_DDR50SUPPORT_RESETVAL                      (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_DDR50SUPPORT_MAX                           (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SDR104SUPPORT_MASK                         (0x00000002U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SDR104SUPPORT_SHIFT                        (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SDR104SUPPORT_RESETVAL                     (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SDR104SUPPORT_MAX                          (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SDR50SUPPORT_MASK                          (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SDR50SUPPORT_SHIFT                         (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SDR50SUPPORT_RESETVAL                      (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_3_REG_SDR50SUPPORT_MAX                           (0x00000001U)

#define CSL_MMC_SSCFG_CTL_CFG_3_REG_RESETVAL                                   (0x98000407U)

/* CTL_CFG_4_REG */

#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT1P8V_MASK                        (0x00FF0000U)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT1P8V_SHIFT                       (0x00000010U)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT1P8V_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT1P8V_MAX                         (0x000000FFU)

#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT3P0V_MASK                        (0x0000FF00U)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT3P0V_SHIFT                       (0x00000008U)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT3P0V_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT3P0V_MAX                         (0x000000FFU)

#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT3P3V_MASK                        (0x000000FFU)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT3P3V_SHIFT                       (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT3P3V_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_4_REG_MAXCURRENT3P3V_MAX                         (0x000000FFU)

#define CSL_MMC_SSCFG_CTL_CFG_4_REG_RESETVAL                                   (0x00000000U)

/* CTL_CFG_5_REG */

#define CSL_MMC_SSCFG_CTL_CFG_5_REG_MAXCURRENTVDD2_MASK                        (0x000000FFU)
#define CSL_MMC_SSCFG_CTL_CFG_5_REG_MAXCURRENTVDD2_SHIFT                       (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_5_REG_MAXCURRENTVDD2_RESETVAL                    (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_5_REG_MAXCURRENTVDD2_MAX                         (0x000000FFU)

#define CSL_MMC_SSCFG_CTL_CFG_5_REG_RESETVAL                                   (0x00000000U)

/* CTL_CFG_6_REG */

#define CSL_MMC_SSCFG_CTL_CFG_6_REG_INITPRESETVAL_MASK                         (0x00001FFFU)
#define CSL_MMC_SSCFG_CTL_CFG_6_REG_INITPRESETVAL_SHIFT                        (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_6_REG_INITPRESETVAL_RESETVAL                     (0x00000100U)
#define CSL_MMC_SSCFG_CTL_CFG_6_REG_INITPRESETVAL_MAX                          (0x00001FFFU)

#define CSL_MMC_SSCFG_CTL_CFG_6_REG_RESETVAL                                   (0x00000100U)

/* CTL_CFG_7_REG */

#define CSL_MMC_SSCFG_CTL_CFG_7_REG_DSPDPRESETVAL_MASK                         (0x00001FFFU)
#define CSL_MMC_SSCFG_CTL_CFG_7_REG_DSPDPRESETVAL_SHIFT                        (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_7_REG_DSPDPRESETVAL_RESETVAL                     (0x00000004U)
#define CSL_MMC_SSCFG_CTL_CFG_7_REG_DSPDPRESETVAL_MAX                          (0x00001FFFU)

#define CSL_MMC_SSCFG_CTL_CFG_7_REG_RESETVAL                                   (0x00000004U)

/* CTL_CFG_8_REG */

#define CSL_MMC_SSCFG_CTL_CFG_8_REG_HSPDPRESETVAL_MASK                         (0x00001FFFU)
#define CSL_MMC_SSCFG_CTL_CFG_8_REG_HSPDPRESETVAL_SHIFT                        (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_8_REG_HSPDPRESETVAL_RESETVAL                     (0x00000002U)
#define CSL_MMC_SSCFG_CTL_CFG_8_REG_HSPDPRESETVAL_MAX                          (0x00001FFFU)

#define CSL_MMC_SSCFG_CTL_CFG_8_REG_RESETVAL                                   (0x00000002U)

/* CTL_CFG_9_REG */

#define CSL_MMC_SSCFG_CTL_CFG_9_REG_SDR12PRESETVAL_MASK                        (0x00001FFFU)
#define CSL_MMC_SSCFG_CTL_CFG_9_REG_SDR12PRESETVAL_SHIFT                       (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_9_REG_SDR12PRESETVAL_RESETVAL                    (0x00000004U)
#define CSL_MMC_SSCFG_CTL_CFG_9_REG_SDR12PRESETVAL_MAX                         (0x00001FFFU)

#define CSL_MMC_SSCFG_CTL_CFG_9_REG_RESETVAL                                   (0x00000004U)

/* CTL_CFG_10_REG */

#define CSL_MMC_SSCFG_CTL_CFG_10_REG_SDR25PRESETVAL_MASK                       (0x00001FFFU)
#define CSL_MMC_SSCFG_CTL_CFG_10_REG_SDR25PRESETVAL_SHIFT                      (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_10_REG_SDR25PRESETVAL_RESETVAL                   (0x00000002U)
#define CSL_MMC_SSCFG_CTL_CFG_10_REG_SDR25PRESETVAL_MAX                        (0x00001FFFU)

#define CSL_MMC_SSCFG_CTL_CFG_10_REG_RESETVAL                                  (0x00000002U)

/* CTL_CFG_11_REG */

#define CSL_MMC_SSCFG_CTL_CFG_11_REG_SDR50PRESETVAL_MASK                       (0x00001FFFU)
#define CSL_MMC_SSCFG_CTL_CFG_11_REG_SDR50PRESETVAL_SHIFT                      (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_11_REG_SDR50PRESETVAL_RESETVAL                   (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_11_REG_SDR50PRESETVAL_MAX                        (0x00001FFFU)

#define CSL_MMC_SSCFG_CTL_CFG_11_REG_RESETVAL                                  (0x00000001U)

/* CTL_CFG_12_REG */

#define CSL_MMC_SSCFG_CTL_CFG_12_REG_SDR104PRESETVAL_MASK                      (0x00001FFFU)
#define CSL_MMC_SSCFG_CTL_CFG_12_REG_SDR104PRESETVAL_SHIFT                     (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_12_REG_SDR104PRESETVAL_RESETVAL                  (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_12_REG_SDR104PRESETVAL_MAX                       (0x00001FFFU)

#define CSL_MMC_SSCFG_CTL_CFG_12_REG_RESETVAL                                  (0x00000000U)

/* CTL_CFG_13_REG */

#define CSL_MMC_SSCFG_CTL_CFG_13_REG_DDR50PRESETVAL_MASK                       (0x00001FFFU)
#define CSL_MMC_SSCFG_CTL_CFG_13_REG_DDR50PRESETVAL_SHIFT                      (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_13_REG_DDR50PRESETVAL_RESETVAL                   (0x00000002U)
#define CSL_MMC_SSCFG_CTL_CFG_13_REG_DDR50PRESETVAL_MAX                        (0x00001FFFU)

#define CSL_MMC_SSCFG_CTL_CFG_13_REG_RESETVAL                                  (0x00000002U)

/* CTL_CFG_14_REG */

#define CSL_MMC_SSCFG_CTL_CFG_14_REG_HS400PRESETVAL_MASK                       (0x00001FFFU)
#define CSL_MMC_SSCFG_CTL_CFG_14_REG_HS400PRESETVAL_SHIFT                      (0x00000000U)
#define CSL_MMC_SSCFG_CTL_CFG_14_REG_HS400PRESETVAL_RESETVAL                   (0x00000001U)
#define CSL_MMC_SSCFG_CTL_CFG_14_REG_HS400PRESETVAL_MAX                        (0x00001FFFU)

#define CSL_MMC_SSCFG_CTL_CFG_14_REG_RESETVAL                                  (0x00000001U)

/* CTL_STAT_1_REG */

#define CSL_MMC_SSCFG_CTL_STAT_1_REG_SDHC_CMDIDLE_MASK                         (0x80000000U)
#define CSL_MMC_SSCFG_CTL_STAT_1_REG_SDHC_CMDIDLE_SHIFT                        (0x0000001FU)
#define CSL_MMC_SSCFG_CTL_STAT_1_REG_SDHC_CMDIDLE_RESETVAL                     (0x00000001U)
#define CSL_MMC_SSCFG_CTL_STAT_1_REG_SDHC_CMDIDLE_MAX                          (0x00000001U)

#define CSL_MMC_SSCFG_CTL_STAT_1_REG_DMADEBUGBUS_MASK                          (0x0000FFFFU)
#define CSL_MMC_SSCFG_CTL_STAT_1_REG_DMADEBUGBUS_SHIFT                         (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_1_REG_DMADEBUGBUS_RESETVAL                      (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_1_REG_DMADEBUGBUS_MAX                           (0x0000FFFFU)

#define CSL_MMC_SSCFG_CTL_STAT_1_REG_RESETVAL                                  (0x80000000U)

/* CTL_STAT_2_REG */

#define CSL_MMC_SSCFG_CTL_STAT_2_REG_CMDDEBUGBUS_MASK                          (0x0000FFFFU)
#define CSL_MMC_SSCFG_CTL_STAT_2_REG_CMDDEBUGBUS_SHIFT                         (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_2_REG_CMDDEBUGBUS_RESETVAL                      (0x00000010U)
#define CSL_MMC_SSCFG_CTL_STAT_2_REG_CMDDEBUGBUS_MAX                           (0x0000FFFFU)

#define CSL_MMC_SSCFG_CTL_STAT_2_REG_RESETVAL                                  (0x00000010U)

/* CTL_STAT_3_REG */

#define CSL_MMC_SSCFG_CTL_STAT_3_REG_TXDDEBUGBUS_MASK                          (0x0000FFFFU)
#define CSL_MMC_SSCFG_CTL_STAT_3_REG_TXDDEBUGBUS_SHIFT                         (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_3_REG_TXDDEBUGBUS_RESETVAL                      (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_3_REG_TXDDEBUGBUS_MAX                           (0x0000FFFFU)

#define CSL_MMC_SSCFG_CTL_STAT_3_REG_RESETVAL                                  (0x00000000U)

/* CTL_STAT_4_REG */

#define CSL_MMC_SSCFG_CTL_STAT_4_REG_RXDDEBUGBUS0_MASK                         (0x0000FFFFU)
#define CSL_MMC_SSCFG_CTL_STAT_4_REG_RXDDEBUGBUS0_SHIFT                        (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_4_REG_RXDDEBUGBUS0_RESETVAL                     (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_4_REG_RXDDEBUGBUS0_MAX                          (0x0000FFFFU)

#define CSL_MMC_SSCFG_CTL_STAT_4_REG_RESETVAL                                  (0x00000000U)

/* CTL_STAT_5_REG */

#define CSL_MMC_SSCFG_CTL_STAT_5_REG_RXDDEBUGBUS1_MASK                         (0x0000FFFFU)
#define CSL_MMC_SSCFG_CTL_STAT_5_REG_RXDDEBUGBUS1_SHIFT                        (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_5_REG_RXDDEBUGBUS1_RESETVAL                     (0x00000008U)
#define CSL_MMC_SSCFG_CTL_STAT_5_REG_RXDDEBUGBUS1_MAX                          (0x0000FFFFU)

#define CSL_MMC_SSCFG_CTL_STAT_5_REG_RESETVAL                                  (0x00000008U)

/* CTL_STAT_6_REG */

#define CSL_MMC_SSCFG_CTL_STAT_6_REG_TUNDEBUGBUS_MASK                          (0x0000FFFFU)
#define CSL_MMC_SSCFG_CTL_STAT_6_REG_TUNDEBUGBUS_SHIFT                         (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_6_REG_TUNDEBUGBUS_RESETVAL                      (0x00000000U)
#define CSL_MMC_SSCFG_CTL_STAT_6_REG_TUNDEBUGBUS_MAX                           (0x0000FFFFU)

#define CSL_MMC_SSCFG_CTL_STAT_6_REG_RESETVAL                                  (0x00000000U)

/* PHY_CTRL_1_REG */

#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_DR_TY_MASK                                (0x00700000U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_DR_TY_SHIFT                               (0x00000014U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_DR_TY_RESETVAL                            (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_DR_TY_MAX                                 (0x00000007U)

#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_RETRIM_MASK                               (0x00020000U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_RETRIM_SHIFT                              (0x00000011U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_RETRIM_RESETVAL                           (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_RETRIM_MAX                                (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_EN_RTRIM_MASK                             (0x00010000U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_EN_RTRIM_SHIFT                            (0x00000010U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_EN_RTRIM_RESETVAL                         (0x00000001U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_EN_RTRIM_MAX                              (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_DLL_TRM_ICP_MASK                          (0x000000F0U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_DLL_TRM_ICP_SHIFT                         (0x00000004U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_DLL_TRM_ICP_RESETVAL                      (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_DLL_TRM_ICP_MAX                           (0x0000000FU)

#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_ENDLL_MASK                                (0x00000002U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_ENDLL_SHIFT                               (0x00000001U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_ENDLL_RESETVAL                            (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_ENDLL_MAX                                 (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_PDB_MASK                                  (0x00000001U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_PDB_SHIFT                                 (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_PDB_RESETVAL                              (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_PDB_MAX                                   (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_1_REG_RESETVAL                                  (0x00010000U)

/* PHY_CTRL_2_REG */

#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_STRB_MASK                      (0x20000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_STRB_SHIFT                     (0x0000001DU)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_STRB_RESETVAL                  (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_STRB_MAX                       (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_CMD_MASK                       (0x10000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_CMD_SHIFT                      (0x0000001CU)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_CMD_RESETVAL                   (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_CMD_MAX                        (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_DAT_MASK                       (0x00FF0000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_DAT_SHIFT                      (0x00000010U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_DAT_RESETVAL                   (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_OD_RELEASE_DAT_MAX                        (0x000000FFU)

#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_STRB_MASK                            (0x00002000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_STRB_SHIFT                           (0x0000000DU)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_STRB_RESETVAL                        (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_STRB_MAX                             (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_CMD_MASK                             (0x00001000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_CMD_SHIFT                            (0x0000000CU)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_CMD_RESETVAL                         (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_CMD_MAX                              (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_DAT_MASK                             (0x000000FFU)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_DAT_SHIFT                            (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_DAT_RESETVAL                         (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_ODEN_DAT_MAX                              (0x000000FFU)

#define CSL_MMC_SSCFG_PHY_CTRL_2_REG_RESETVAL                                  (0x00000000U)

/* PHY_CTRL_3_REG */

#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_STRB_MASK                              (0x20000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_STRB_SHIFT                             (0x0000001DU)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_STRB_RESETVAL                          (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_STRB_MAX                               (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_CMD_MASK                               (0x10000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_CMD_SHIFT                              (0x0000001CU)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_CMD_RESETVAL                           (0x00000001U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_CMD_MAX                                (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_DAT_MASK                               (0x00FF0000U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_DAT_SHIFT                              (0x00000010U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_DAT_RESETVAL                           (0x000000FFU)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_PU_DAT_MAX                                (0x000000FFU)

#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_STRB_MASK                             (0x00002000U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_STRB_SHIFT                            (0x0000000DU)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_STRB_RESETVAL                         (0x00000001U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_STRB_MAX                              (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_CMD_MASK                              (0x00001000U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_CMD_SHIFT                             (0x0000000CU)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_CMD_RESETVAL                          (0x00000001U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_CMD_MAX                               (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_DAT_MASK                              (0x000000FFU)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_DAT_SHIFT                             (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_DAT_RESETVAL                          (0x000000FFU)
#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_REN_DAT_MAX                               (0x000000FFU)

#define CSL_MMC_SSCFG_PHY_CTRL_3_REG_RESETVAL                                  (0x10FF30FFU)

/* PHY_CTRL_4_REG */

#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_STRBSEL_MASK                              (0xFF000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_STRBSEL_SHIFT                             (0x00000018U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_STRBSEL_RESETVAL                          (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_STRBSEL_MAX                               (0x000000FFU)

#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_OTAPDLYENA_MASK                           (0x00100000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_OTAPDLYENA_SHIFT                          (0x00000014U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_OTAPDLYENA_RESETVAL                       (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_OTAPDLYENA_MAX                            (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_OTAPDLYSEL_MASK                           (0x0000F000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_OTAPDLYSEL_SHIFT                          (0x0000000CU)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_OTAPDLYSEL_RESETVAL                       (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_OTAPDLYSEL_MAX                            (0x0000000FU)

#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPCHGWIN_MASK                           (0x00000200U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPCHGWIN_SHIFT                          (0x00000009U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPCHGWIN_RESETVAL                       (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPCHGWIN_MAX                            (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYENA_MASK                           (0x00000100U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYENA_SHIFT                          (0x00000008U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYENA_RESETVAL                       (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYENA_MAX                            (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYSEL_MASK                           (0x0000001FU)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYSEL_SHIFT                          (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYSEL_RESETVAL                       (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_ITAPDLYSEL_MAX                            (0x0000001FU)

#define CSL_MMC_SSCFG_PHY_CTRL_4_REG_RESETVAL                                  (0x00000000U)

/* PHY_CTRL_5_REG */

#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_SELDLYTXCLK_MASK                          (0x00020000U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_SELDLYTXCLK_SHIFT                         (0x00000011U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_SELDLYTXCLK_RESETVAL                      (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_SELDLYTXCLK_MAX                           (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_SELDLYRXCLK_MASK                          (0x00010000U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_SELDLYRXCLK_SHIFT                         (0x00000010U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_SELDLYRXCLK_RESETVAL                      (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_SELDLYRXCLK_MAX                           (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_FRQSEL_MASK                               (0x00000700U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_FRQSEL_SHIFT                              (0x00000008U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_FRQSEL_RESETVAL                           (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_FRQSEL_MAX                                (0x00000007U)

#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_CLKBUFSEL_MASK                            (0x00000007U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_CLKBUFSEL_SHIFT                           (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_CLKBUFSEL_RESETVAL                        (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_CLKBUFSEL_MAX                             (0x00000007U)

#define CSL_MMC_SSCFG_PHY_CTRL_5_REG_RESETVAL                                  (0x00000000U)

/* PHY_CTRL_6_REG */

#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTENABLE_MASK                           (0x80000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTENABLE_SHIFT                          (0x0000001FU)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTENABLE_RESETVAL                       (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTENABLE_MAX                            (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTSTART_MASK                            (0x40000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTSTART_SHIFT                           (0x0000001EU)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTSTART_RESETVAL                        (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTSTART_MAX                             (0x00000001U)

#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTMODE_MASK                             (0x0F000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTMODE_SHIFT                            (0x00000018U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTMODE_RESETVAL                         (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_BISTMODE_MAX                              (0x0000000FU)

#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_TESTCTRL_MASK                             (0x000000FFU)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_TESTCTRL_SHIFT                            (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_TESTCTRL_RESETVAL                         (0x00000000U)
#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_TESTCTRL_MAX                              (0x000000FFU)

#define CSL_MMC_SSCFG_PHY_CTRL_6_REG_RESETVAL                                  (0x00000000U)

/* PHY_STAT_1_REG */

#define CSL_MMC_SSCFG_PHY_STAT_1_REG_RTRIM_MASK                                (0x000000F0U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_RTRIM_SHIFT                               (0x00000004U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_RTRIM_RESETVAL                            (0x0000000EU)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_RTRIM_MAX                                 (0x0000000FU)

#define CSL_MMC_SSCFG_PHY_STAT_1_REG_BISTDONE_MASK                             (0x00000008U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_BISTDONE_SHIFT                            (0x00000003U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_BISTDONE_RESETVAL                         (0x00000000U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_BISTDONE_MAX                              (0x00000001U)

#define CSL_MMC_SSCFG_PHY_STAT_1_REG_EXR_NINST_MASK                            (0x00000004U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_EXR_NINST_SHIFT                           (0x00000002U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_EXR_NINST_RESETVAL                        (0x00000000U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_EXR_NINST_MAX                             (0x00000001U)

#define CSL_MMC_SSCFG_PHY_STAT_1_REG_CALDONE_MASK                              (0x00000002U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_CALDONE_SHIFT                             (0x00000001U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_CALDONE_RESETVAL                          (0x00000000U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_CALDONE_MAX                               (0x00000001U)

#define CSL_MMC_SSCFG_PHY_STAT_1_REG_DLLRDY_MASK                               (0x00000001U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_DLLRDY_SHIFT                              (0x00000000U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_DLLRDY_RESETVAL                           (0x00000000U)
#define CSL_MMC_SSCFG_PHY_STAT_1_REG_DLLRDY_MAX                                (0x00000001U)

#define CSL_MMC_SSCFG_PHY_STAT_1_REG_RESETVAL                                  (0x000000E0U)

/* PHY_STAT_2_REG */

#define CSL_MMC_SSCFG_PHY_STAT_2_REG_BISTSTATUS_MASK                           (0xFFFFFFFFU)
#define CSL_MMC_SSCFG_PHY_STAT_2_REG_BISTSTATUS_SHIFT                          (0x00000000U)
#define CSL_MMC_SSCFG_PHY_STAT_2_REG_BISTSTATUS_RESETVAL                       (0x00000000U)
#define CSL_MMC_SSCFG_PHY_STAT_2_REG_BISTSTATUS_MAX                            (0xFFFFFFFFU)

#define CSL_MMC_SSCFG_PHY_STAT_2_REG_RESETVAL                                  (0x00000000U)

/**************************************************************************
* Hardware Region  : Arasan eMMC/SD Controller Registers
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint16_t SDMA_SYS_ADDR_LO;
    volatile uint16_t SDMA_SYS_ADDR_HI;
    volatile uint16_t BLOCK_SIZE;
    volatile uint16_t BLOCK_COUNT;
    volatile uint16_t ARGUMENT1_LO;
    volatile uint16_t ARGUMENT1_HI;
    volatile uint16_t TRANSFER_MODE;
    volatile uint16_t COMMAND;
    volatile uint16_t RESPONSE[8];
    volatile uint32_t DATA_PORT;
    volatile uint32_t PRESENTSTATE;
    volatile uint8_t HOST_CONTROL1;
    volatile uint8_t POWER_CONTROL;
    volatile uint8_t BLOCK_GAP_CONTROL;
    volatile uint8_t WAKEUP_CONTROL;
    volatile uint16_t CLOCK_CONTROL;
    volatile uint8_t TIMEOUT_CONTROL;
    volatile uint8_t SOFTWARE_RESET;
    volatile uint16_t NORMAL_INTR_STS;
    volatile uint16_t ERROR_INTR_STS;
    volatile uint16_t NORMAL_INTR_STS_ENA;
    volatile uint16_t ERROR_INTR_STS_ENA;
    volatile uint16_t NORMAL_INTR_SIG_ENA;
    volatile uint16_t ERROR_INTR_SIG_ENA;
    volatile uint16_t AUTOCMD_ERR_STS;
    volatile uint16_t HOST_CONTROL2;
    volatile uint64_t CAPABILITIES;
    volatile uint64_t MAX_CURRENT_CAP;
    volatile uint16_t FORCE_EVNT_ACMD_ERR_STS;
    volatile uint16_t FORCE_EVNT_ERR_INT_STS;
    volatile uint8_t ADMA_ERR_STATUS;
    volatile uint8_t  Resv_88[3];
    volatile uint64_t ADMA_SYS_ADDRESS;
    volatile uint16_t PRESET_VALUE0;
    volatile uint16_t PRESET_VALUE1;
    volatile uint16_t PRESET_VALUE2;
    volatile uint16_t PRESET_VALUE3;
    volatile uint16_t PRESET_VALUE4;
    volatile uint16_t PRESET_VALUE5;
    volatile uint16_t PRESET_VALUE6;
    volatile uint16_t PRESET_VALUE7;
    volatile uint8_t  Resv_114[2];
    volatile uint16_t PRESET_VALUE8;
    volatile uint16_t PRESET_VALUE10;
    volatile uint8_t  Resv_120[2];
    volatile uint64_t ADMA3_DESC_ADDRESS;
    volatile uint16_t UHS2_BLOCK_SIZE;
    volatile uint8_t  Resv_132[2];
    volatile uint32_t UHS2_BLOCK_COUNT;
    volatile uint8_t UHS2_COMMAND_PKT[20];
    volatile uint16_t UHS2_XFER_MODE;
    volatile uint16_t UHS2_COMMAND;
    volatile uint8_t UHS2_RESPONSE[20];
    volatile uint8_t UHS2_MESSAGE_SELECT;
    volatile uint8_t  Resv_184[3];
    volatile uint32_t UHS2_MESSAGE;
    volatile uint16_t UHS2_DEVICE_INTR_STATUS;
    volatile uint8_t UHS2_DEVICE_SELECT;
    volatile uint8_t UHS2_DEVICE_INT_CODE;
    volatile uint16_t UHS2_SOFTWARE_RESET;
    volatile uint16_t UHS2_TIMER_CONTROL;
    volatile uint32_t UHS2_ERR_INTR_STS;
    volatile uint32_t UHS2_ERR_INTR_STS_ENA;
    volatile uint32_t UHS2_ERR_INTR_SIG_ENA;
    volatile uint8_t  Resv_224[16];
    volatile uint16_t UHS2_SETTINGS_PTR;
    volatile uint16_t UHS2_CAPABILITIES_PTR;
    volatile uint16_t UHS2_TEST_PTR;
    volatile uint16_t SHARED_BUS_CTRL_PTR;
    volatile uint16_t VENDOR_SPECFIC_PTR;
    volatile uint8_t  Resv_244[10];
    volatile uint32_t BOOT_TIMEOUT_CONTROL;
    volatile uint32_t VENDOR_REGISTER;
    volatile uint16_t SLOT_INT_STS;
    volatile uint16_t HOST_CONTROLLER_VER;
    volatile uint32_t UHS2_GEN_SETTINGS;
    volatile uint32_t UHS2_PHY_SETTINGS;
    volatile uint64_t UHS2_LNK_TRN_SETTINGS;
    volatile uint32_t UHS2_GEN_CAP;
    volatile uint32_t UHS2_PHY_CAP;
    volatile uint64_t UHS2_LNK_TRN_CAP;
    volatile uint32_t FORCE_UHSII_ERR_INT_STS;
    volatile uint8_t  Resv_512[220];
    volatile uint32_t CQ_VERSION;
    volatile uint32_t CQ_CAPABILITIES;
    volatile uint32_t CQ_CONFIG;
    volatile uint32_t CQ_CONTROL;
    volatile uint32_t CQ_INTR_STS;
    volatile uint32_t CQ_INTR_STS_ENA;
    volatile uint32_t CQ_INTR_SIG_ENA;
    volatile uint32_t CQ_INTR_COALESCING;
    volatile uint32_t CQ_TDL_BASE_ADDR;
    volatile uint32_t CQ_TDL_BASE_ADDR_UPBITS;
    volatile uint32_t CQ_TASK_DOOR_BELL;
    volatile uint32_t CQ_TASK_COMP_NOTIF;
    volatile uint32_t CQ_DEV_QUEUE_STATUS;
    volatile uint32_t CQ_DEV_PENDING_TASKS;
    volatile uint32_t CQ_TASK_CLEAR;
    volatile uint8_t  Resv_576[4];
    volatile uint32_t CQ_SEND_STS_CONFIG1;
    volatile uint32_t CQ_SEND_STS_CONFIG2;
    volatile uint32_t CQ_DCMD_RESPONSE;
    volatile uint8_t  Resv_592[4];
    volatile uint32_t CQ_RESP_ERR_MASK;
    volatile uint32_t CQ_TASK_ERR_INFO;
    volatile uint32_t CQ_CMD_RESP_INDEX;
    volatile uint32_t CQ_CMD_RESP_ARG;
    volatile uint32_t CQ_ERROR_TASK_ID;
} CSL_mmc_ctlcfgRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_LO                                        (0x00000000U)
#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_HI                                        (0x00000002U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE                                              (0x00000004U)
#define CSL_MMC_CTLCFG_BLOCK_COUNT                                             (0x00000006U)
#define CSL_MMC_CTLCFG_ARGUMENT1_LO                                            (0x00000008U)
#define CSL_MMC_CTLCFG_ARGUMENT1_HI                                            (0x0000000AU)
#define CSL_MMC_CTLCFG_TRANSFER_MODE                                           (0x0000000CU)
#define CSL_MMC_CTLCFG_COMMAND                                                 (0x0000000EU)
#define CSL_MMC_CTLCFG_RESPONSE(RESPONSE)                                      (0x00000010U+((RESPONSE)*0x2U))
#define CSL_MMC_CTLCFG_DATA_PORT                                               (0x00000020U)
#define CSL_MMC_CTLCFG_PRESENTSTATE                                            (0x00000024U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1                                           (0x00000028U)
#define CSL_MMC_CTLCFG_POWER_CONTROL                                           (0x00000029U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL                                       (0x0000002AU)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL                                          (0x0000002BU)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL                                           (0x0000002CU)
#define CSL_MMC_CTLCFG_TIMEOUT_CONTROL                                         (0x0000002EU)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET                                          (0x0000002FU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS                                         (0x00000030U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS                                          (0x00000032U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA                                     (0x00000034U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA                                      (0x00000036U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA                                     (0x00000038U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA                                      (0x0000003AU)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS                                         (0x0000003CU)
#define CSL_MMC_CTLCFG_HOST_CONTROL2                                           (0x0000003EU)
#define CSL_MMC_CTLCFG_CAPABILITIES                                            (0x00000040U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP                                         (0x00000048U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS                                 (0x00000050U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS                                  (0x00000052U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS                                         (0x00000054U)
#define CSL_MMC_CTLCFG_ADMA_SYS_ADDRESS                                        (0x00000058U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0                                           (0x00000060U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1                                           (0x00000062U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2                                           (0x00000064U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3                                           (0x00000066U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4                                           (0x00000068U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5                                           (0x0000006AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE6                                           (0x0000006CU)
#define CSL_MMC_CTLCFG_PRESET_VALUE7                                           (0x0000006EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE8                                           (0x00000072U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10                                          (0x00000074U)
#define CSL_MMC_CTLCFG_ADMA3_DESC_ADDRESS                                      (0x00000078U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE                                         (0x00000080U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT                                        (0x00000084U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT(UHS2_COMMAND_PKT)                      (0x00000088U+((UHS2_COMMAND_PKT)*0x1U))
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE                                          (0x0000009CU)
#define CSL_MMC_CTLCFG_UHS2_COMMAND                                            (0x0000009EU)
#define CSL_MMC_CTLCFG_UHS2_RESPONSE(UHS2_RESPONSE)                            (0x000000A0U+((UHS2_RESPONSE)*0x1U))
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_SELECT                                     (0x000000B4U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE                                            (0x000000B8U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_INTR_STATUS                                 (0x000000BCU)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT                                      (0x000000BEU)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_INT_CODE                                    (0x000000BFU)
#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET                                     (0x000000C0U)
#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL                                      (0x000000C2U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS                                       (0x000000C4U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA                                   (0x000000C8U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA                                   (0x000000CCU)
#define CSL_MMC_CTLCFG_UHS2_SETTINGS_PTR                                       (0x000000E0U)
#define CSL_MMC_CTLCFG_UHS2_CAPABILITIES_PTR                                   (0x000000E2U)
#define CSL_MMC_CTLCFG_UHS2_TEST_PTR                                           (0x000000E4U)
#define CSL_MMC_CTLCFG_SHARED_BUS_CTRL_PTR                                     (0x000000E6U)
#define CSL_MMC_CTLCFG_VENDOR_SPECFIC_PTR                                      (0x000000E8U)
#define CSL_MMC_CTLCFG_BOOT_TIMEOUT_CONTROL                                    (0x000000F4U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER                                         (0x000000F8U)
#define CSL_MMC_CTLCFG_SLOT_INT_STS                                            (0x000000FCU)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER                                     (0x000000FEU)
#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS                                       (0x00000100U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS                                       (0x00000104U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS                                   (0x00000108U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP                                            (0x00000110U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP                                            (0x00000114U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP                                        (0x00000118U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS                                 (0x00000120U)
#define CSL_MMC_CTLCFG_CQ_VERSION                                              (0x00000200U)
#define CSL_MMC_CTLCFG_CQ_CAPABILITIES                                         (0x00000204U)
#define CSL_MMC_CTLCFG_CQ_CONFIG                                               (0x00000208U)
#define CSL_MMC_CTLCFG_CQ_CONTROL                                              (0x0000020CU)
#define CSL_MMC_CTLCFG_CQ_INTR_STS                                             (0x00000210U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA                                         (0x00000214U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA                                         (0x00000218U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING                                      (0x0000021CU)
#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR                                        (0x00000220U)
#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_UPBITS                                 (0x00000224U)
#define CSL_MMC_CTLCFG_CQ_TASK_DOOR_BELL                                       (0x00000228U)
#define CSL_MMC_CTLCFG_CQ_TASK_COMP_NOTIF                                      (0x0000022CU)
#define CSL_MMC_CTLCFG_CQ_DEV_QUEUE_STATUS                                     (0x00000230U)
#define CSL_MMC_CTLCFG_CQ_DEV_PENDING_TASKS                                    (0x00000234U)
#define CSL_MMC_CTLCFG_CQ_TASK_CLEAR                                           (0x00000238U)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1                                     (0x00000240U)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG2                                     (0x00000244U)
#define CSL_MMC_CTLCFG_CQ_DCMD_RESPONSE                                        (0x00000248U)
#define CSL_MMC_CTLCFG_CQ_RESP_ERR_MASK                                        (0x00000250U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO                                        (0x00000254U)
#define CSL_MMC_CTLCFG_CQ_CMD_RESP_INDEX                                       (0x00000258U)
#define CSL_MMC_CTLCFG_CQ_CMD_RESP_ARG                                         (0x0000025CU)
#define CSL_MMC_CTLCFG_CQ_ERROR_TASK_ID                                        (0x00000260U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* SDMA_SYS_ADDR_LO */

#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_LO_SDMA_ADDRESS_MASK                      (0xFFFFU)
#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_LO_SDMA_ADDRESS_SHIFT                     (0x0000U)
#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_LO_SDMA_ADDRESS_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_LO_SDMA_ADDRESS_MAX                       (0xFFFFU)

#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_LO_RESETVAL                               (0x0000U)

/* SDMA_SYS_ADDR_HI */

#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_HI_SDMA_ADDRESS_MASK                      (0xFFFFU)
#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_HI_SDMA_ADDRESS_SHIFT                     (0x0000U)
#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_HI_SDMA_ADDRESS_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_HI_SDMA_ADDRESS_MAX                       (0xFFFFU)

#define CSL_MMC_CTLCFG_SDMA_SYS_ADDR_HI_RESETVAL                               (0x0000U)

/* BLOCK_SIZE */

#define CSL_MMC_CTLCFG_BLOCK_SIZE_XFER_BLK_SIZE_MASK                           (0x0FFFU)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_XFER_BLK_SIZE_SHIFT                          (0x0000U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_XFER_BLK_SIZE_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_XFER_BLK_SIZE_MAX                            (0x0FFFU)

#define CSL_MMC_CTLCFG_BLOCK_SIZE_XFER_BLK_SIZE_VAL_NO_DATA_XFER               (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_XFER_BLK_SIZE_VAL_XFER_1B                    (0x1U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_XFER_BLK_SIZE_VAL_XFER_2B                    (0x2U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_XFER_BLK_SIZE_VAL_XFER_512B                  (0x200U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_XFER_BLK_SIZE_VAL_XFER_2048B                 (0x800U)

#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_MASK                           (0x7000U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_SHIFT                          (0x000CU)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_MAX                            (0x0007U)

#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_VAL_BOUND_4KB                  (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_VAL_BOUND_8KB                  (0x1U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_VAL_BOUND_16KB                 (0x2U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_VAL_BOUND_32KB                 (0x3U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_VAL_BOUND_64KB                 (0x4U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_VAL_BOUND_128KB                (0x5U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_VAL_BOUND_256KB                (0x6U)
#define CSL_MMC_CTLCFG_BLOCK_SIZE_SDMA_BUF_SIZE_VAL_BOUND_512KB                (0x7U)

#define CSL_MMC_CTLCFG_BLOCK_SIZE_RESETVAL                                     (0x0000U)

/* BLOCK_COUNT */

#define CSL_MMC_CTLCFG_BLOCK_COUNT_XFER_BLK_CNT_MASK                           (0xFFFFU)
#define CSL_MMC_CTLCFG_BLOCK_COUNT_XFER_BLK_CNT_SHIFT                          (0x0000U)
#define CSL_MMC_CTLCFG_BLOCK_COUNT_XFER_BLK_CNT_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_BLOCK_COUNT_XFER_BLK_CNT_MAX                            (0xFFFFU)

#define CSL_MMC_CTLCFG_BLOCK_COUNT_XFER_BLK_CNT_VAL_STOP_COUNT                 (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_COUNT_XFER_BLK_CNT_VAL_BLK_1                      (0x1U)
#define CSL_MMC_CTLCFG_BLOCK_COUNT_XFER_BLK_CNT_VAL_BLKS_2                     (0x2U)
#define CSL_MMC_CTLCFG_BLOCK_COUNT_XFER_BLK_CNT_VAL_BLKS_3                     (0x3U)
#define CSL_MMC_CTLCFG_BLOCK_COUNT_XFER_BLK_CNT_VAL_BLKS_65535                 (0xFFFFU)

#define CSL_MMC_CTLCFG_BLOCK_COUNT_RESETVAL                                    (0x0000U)

/* ARGUMENT1_LO */

#define CSL_MMC_CTLCFG_ARGUMENT1_LO_CMD_ARG1_MASK                              (0xFFFFU)
#define CSL_MMC_CTLCFG_ARGUMENT1_LO_CMD_ARG1_SHIFT                             (0x0000U)
#define CSL_MMC_CTLCFG_ARGUMENT1_LO_CMD_ARG1_RESETVAL                          (0x0000U)
#define CSL_MMC_CTLCFG_ARGUMENT1_LO_CMD_ARG1_MAX                               (0xFFFFU)

#define CSL_MMC_CTLCFG_ARGUMENT1_LO_RESETVAL                                   (0x0000U)

/* ARGUMENT1_HI */

#define CSL_MMC_CTLCFG_ARGUMENT1_HI_CMD_ARG1_MASK                              (0xFFFFU)
#define CSL_MMC_CTLCFG_ARGUMENT1_HI_CMD_ARG1_SHIFT                             (0x0000U)
#define CSL_MMC_CTLCFG_ARGUMENT1_HI_CMD_ARG1_RESETVAL                          (0x0000U)
#define CSL_MMC_CTLCFG_ARGUMENT1_HI_CMD_ARG1_MAX                               (0xFFFFU)

#define CSL_MMC_CTLCFG_ARGUMENT1_HI_RESETVAL                                   (0x0000U)

/* TRANSFER_MODE */

#define CSL_MMC_CTLCFG_TRANSFER_MODE_DMA_ENA_MASK                              (0x0001U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_DMA_ENA_SHIFT                             (0x0000U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_DMA_ENA_RESETVAL                          (0x0000U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_DMA_ENA_MAX                               (0x0001U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_DMA_ENA_VAL_DISABLE                       (0x0U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_DMA_ENA_VAL_ENABLE                        (0x1U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_BLK_CNT_ENA_MASK                          (0x0002U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_BLK_CNT_ENA_SHIFT                         (0x0001U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_BLK_CNT_ENA_RESETVAL                      (0x0000U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_BLK_CNT_ENA_MAX                           (0x0001U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_BLK_CNT_ENA_VAL_DISABLE                   (0x0U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_BLK_CNT_ENA_VAL_ENABLE                    (0x1U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_AUTO_CMD_ENA_MASK                         (0x000CU)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_AUTO_CMD_ENA_SHIFT                        (0x0002U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_AUTO_CMD_ENA_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_AUTO_CMD_ENA_MAX                          (0x0003U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_AUTO_CMD_ENA_VAL_ACMD_DISABLE             (0x0U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_AUTO_CMD_ENA_VAL_ACMD12_ENA               (0x1U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_AUTO_CMD_ENA_VAL_ACMD23_ENA               (0x2U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_AUTO_CMD_ENA_VAL_ACMD_AUTOSEL             (0x3U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_DATA_XFER_DIR_MASK                        (0x0010U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_DATA_XFER_DIR_SHIFT                       (0x0004U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_DATA_XFER_DIR_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_DATA_XFER_DIR_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_DATA_XFER_DIR_VAL_WRITE                   (0x0U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_DATA_XFER_DIR_VAL_READ                    (0x1U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_MULTI_BLK_SEL_MASK                        (0x0020U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_MULTI_BLK_SEL_SHIFT                       (0x0005U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_MULTI_BLK_SEL_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_MULTI_BLK_SEL_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_MULTI_BLK_SEL_VAL_SINGLE                  (0x0U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_MULTI_BLK_SEL_VAL_MULTIPLE                (0x1U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_TYPE_MASK                            (0x0040U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_TYPE_SHIFT                           (0x0006U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_TYPE_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_TYPE_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_TYPE_VAL_R1                          (0x0U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_TYPE_VAL_R5                          (0x1U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_ERR_CHK_ENA_MASK                     (0x0080U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_ERR_CHK_ENA_SHIFT                    (0x0007U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_ERR_CHK_ENA_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_ERR_CHK_ENA_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_ERR_CHK_ENA_VAL_DISABLE              (0x0U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_ERR_CHK_ENA_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_INTR_DIS_MASK                        (0x0100U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_INTR_DIS_SHIFT                       (0x0008U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_INTR_DIS_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_INTR_DIS_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_INTR_DIS_VAL_DISABLE                 (0x1U)
#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESP_INTR_DIS_VAL_ENABLE                  (0x0U)

#define CSL_MMC_CTLCFG_TRANSFER_MODE_RESETVAL                                  (0x0000U)

/* COMMAND */

#define CSL_MMC_CTLCFG_COMMAND_RESP_TYPE_SEL_MASK                              (0x0003U)
#define CSL_MMC_CTLCFG_COMMAND_RESP_TYPE_SEL_SHIFT                             (0x0000U)
#define CSL_MMC_CTLCFG_COMMAND_RESP_TYPE_SEL_RESETVAL                          (0x0000U)
#define CSL_MMC_CTLCFG_COMMAND_RESP_TYPE_SEL_MAX                               (0x0003U)

#define CSL_MMC_CTLCFG_COMMAND_RESP_TYPE_SEL_VAL_NO_RESP                       (0x0U)
#define CSL_MMC_CTLCFG_COMMAND_RESP_TYPE_SEL_VAL_RESP_136                      (0x1U)
#define CSL_MMC_CTLCFG_COMMAND_RESP_TYPE_SEL_VAL_RESP_48                       (0x2U)
#define CSL_MMC_CTLCFG_COMMAND_RESP_TYPE_SEL_VAL_RESP_48_BUSY                  (0x3U)

#define CSL_MMC_CTLCFG_COMMAND_SUB_CMD_MASK                                    (0x0004U)
#define CSL_MMC_CTLCFG_COMMAND_SUB_CMD_SHIFT                                   (0x0002U)
#define CSL_MMC_CTLCFG_COMMAND_SUB_CMD_RESETVAL                                (0x0000U)
#define CSL_MMC_CTLCFG_COMMAND_SUB_CMD_MAX                                     (0x0001U)

#define CSL_MMC_CTLCFG_COMMAND_SUB_CMD_VAL_MAIN_CMD                            (0x0U)
#define CSL_MMC_CTLCFG_COMMAND_SUB_CMD_VAL_SUB_CMD                             (0x1U)

#define CSL_MMC_CTLCFG_COMMAND_CMD_CRC_CHK_ENA_MASK                            (0x0008U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_CRC_CHK_ENA_SHIFT                           (0x0003U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_CRC_CHK_ENA_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_CRC_CHK_ENA_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_COMMAND_CMD_CRC_CHK_ENA_VAL_DISABLE                     (0x0U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_CRC_CHK_ENA_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_CHK_ENA_MASK                          (0x0010U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_CHK_ENA_SHIFT                         (0x0004U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_CHK_ENA_RESETVAL                      (0x0000U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_CHK_ENA_MAX                           (0x0001U)

#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_CHK_ENA_VAL_DISABLE                   (0x0U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_CHK_ENA_VAL_ENABLE                    (0x1U)

#define CSL_MMC_CTLCFG_COMMAND_DATA_PRESENT_MASK                               (0x0020U)
#define CSL_MMC_CTLCFG_COMMAND_DATA_PRESENT_SHIFT                              (0x0005U)
#define CSL_MMC_CTLCFG_COMMAND_DATA_PRESENT_RESETVAL                           (0x0000U)
#define CSL_MMC_CTLCFG_COMMAND_DATA_PRESENT_MAX                                (0x0001U)

#define CSL_MMC_CTLCFG_COMMAND_DATA_PRESENT_VAL_NO_DATA                        (0x0U)
#define CSL_MMC_CTLCFG_COMMAND_DATA_PRESENT_VAL_DATA_PRESENT                   (0x1U)

#define CSL_MMC_CTLCFG_COMMAND_CMD_TYPE_MASK                                   (0x00C0U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_TYPE_SHIFT                                  (0x0006U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_TYPE_RESETVAL                               (0x0000U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_TYPE_MAX                                    (0x0003U)

#define CSL_MMC_CTLCFG_COMMAND_CMD_TYPE_VAL_NORMAL                             (0x0U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_TYPE_VAL_SUSPEND                            (0x1U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_TYPE_VAL_RESUME                             (0x2U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_TYPE_VAL_ABORT                              (0x3U)

#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_MASK                                  (0x3F00U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_SHIFT                                 (0x0008U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_RESETVAL                              (0x0000U)
#define CSL_MMC_CTLCFG_COMMAND_CMD_INDEX_MAX                                   (0x003FU)

#define CSL_MMC_CTLCFG_COMMAND_RESETVAL                                        (0x0000U)

/* RESPONSE */

#define CSL_MMC_CTLCFG_RESPONSE_CMD_RESP_MASK                                  (0xFFFFU)
#define CSL_MMC_CTLCFG_RESPONSE_CMD_RESP_SHIFT                                 (0x0000U)
#define CSL_MMC_CTLCFG_RESPONSE_CMD_RESP_RESETVAL                              (0x0000U)
#define CSL_MMC_CTLCFG_RESPONSE_CMD_RESP_MAX                                   (0xFFFFU)

#define CSL_MMC_CTLCFG_RESPONSE_RESETVAL                                       (0x0000U)

/* DATA_PORT */

#define CSL_MMC_CTLCFG_DATA_PORT_BUF_RD_DATA_MASK                              (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_DATA_PORT_BUF_RD_DATA_SHIFT                             (0x00000000U)
#define CSL_MMC_CTLCFG_DATA_PORT_BUF_RD_DATA_RESETVAL                          (0x00000000U)
#define CSL_MMC_CTLCFG_DATA_PORT_BUF_RD_DATA_MAX                               (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_DATA_PORT_RESETVAL                                      (0x00000000U)

/* PRESENTSTATE */

#define CSL_MMC_CTLCFG_PRESENTSTATE_INHIBIT_CMD_MASK                           (0x00000001U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_INHIBIT_CMD_SHIFT                          (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_INHIBIT_CMD_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_INHIBIT_CMD_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_INHIBIT_DAT_MASK                           (0x00000002U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_INHIBIT_DAT_SHIFT                          (0x00000001U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_INHIBIT_DAT_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_INHIBIT_DAT_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_DATA_LINE_ACTIVE_MASK                      (0x00000004U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_DATA_LINE_ACTIVE_SHIFT                     (0x00000002U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_DATA_LINE_ACTIVE_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_DATA_LINE_ACTIVE_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_DATA_LINE_ACTIVE_VAL_INACTIVE              (0x0U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_DATA_LINE_ACTIVE_VAL_ACTIVE                (0x1U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_RETUNING_REQ_MASK                          (0x00000008U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_RETUNING_REQ_SHIFT                         (0x00000003U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_RETUNING_REQ_RESETVAL                      (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_RETUNING_REQ_MAX                           (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_RETUNING_REQ_VAL_FIXED                     (0x0U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_RETUNING_REQ_VAL_RETUNE                    (0x1U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT4IN_MASK                           (0x00000010U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT4IN_SHIFT                          (0x00000004U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT4IN_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT4IN_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT5IN_MASK                           (0x00000020U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT5IN_SHIFT                          (0x00000005U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT5IN_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT5IN_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT6IN_MASK                           (0x00000040U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT6IN_SHIFT                          (0x00000006U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT6IN_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT6IN_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT7IN_MASK                           (0x00000080U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT7IN_SHIFT                          (0x00000007U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT7IN_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT7IN_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_WR_XFER_ACTIVE_MASK                        (0x00000100U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_WR_XFER_ACTIVE_SHIFT                       (0x00000008U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_WR_XFER_ACTIVE_RESETVAL                    (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_WR_XFER_ACTIVE_MAX                         (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_WR_XFER_ACTIVE_VAL_NO_DATA                 (0x0U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_WR_XFER_ACTIVE_VAL_TRAN_DATA               (0x1U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_RD_XFER_ACTIVE_MASK                        (0x00000200U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_RD_XFER_ACTIVE_SHIFT                       (0x00000009U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_RD_XFER_ACTIVE_RESETVAL                    (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_RD_XFER_ACTIVE_MAX                         (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_RD_XFER_ACTIVE_VAL_NO_DATA                 (0x0U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_RD_XFER_ACTIVE_VAL_TRAN_DATA               (0x1U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_WR_ENA_MASK                            (0x00000400U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_WR_ENA_SHIFT                           (0x0000000AU)
#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_WR_ENA_RESETVAL                        (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_WR_ENA_MAX                             (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_WR_ENA_VAL_DISABLE                     (0x0U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_WR_ENA_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_RD_ENA_MASK                            (0x00000800U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_RD_ENA_SHIFT                           (0x0000000BU)
#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_RD_ENA_RESETVAL                        (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_RD_ENA_MAX                             (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_RD_ENA_VAL_DISABLE                     (0x0U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_BUF_RD_ENA_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_INSERTED_MASK                         (0x00010000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_INSERTED_SHIFT                        (0x00000010U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_INSERTED_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_INSERTED_MAX                          (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_STATE_STABLE_MASK                     (0x00020000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_STATE_STABLE_SHIFT                    (0x00000011U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_STATE_STABLE_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_STATE_STABLE_MAX                      (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_DETECT_MASK                           (0x00040000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_DETECT_SHIFT                          (0x00000012U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_DETECT_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CARD_DETECT_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_WRITE_PROTECT_MASK                         (0x00080000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_WRITE_PROTECT_SHIFT                        (0x00000013U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_WRITE_PROTECT_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_WRITE_PROTECT_MAX                          (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_WRITE_PROTECT_VAL_PROTECT                  (0x0U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_WRITE_PROTECT_VAL_ENABLE                   (0x1U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT0IN_MASK                           (0x00100000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT0IN_SHIFT                          (0x00000014U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT0IN_RESETVAL                       (0x00000001U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT0IN_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT1IN_MASK                           (0x00200000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT1IN_SHIFT                          (0x00000015U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT1IN_RESETVAL                       (0x00000001U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT1IN_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT2IN_MASK                           (0x00400000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT2IN_SHIFT                          (0x00000016U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT2IN_RESETVAL                       (0x00000001U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT2IN_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT3IN_MASK                           (0x00800000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT3IN_SHIFT                          (0x00000017U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT3IN_RESETVAL                       (0x00000001U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_DAT3IN_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_CMDIN_MASK                            (0x01000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_CMDIN_SHIFT                           (0x00000018U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_CMDIN_RESETVAL                        (0x00000001U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SDIF_CMDIN_MAX                             (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_CMD_NOT_ISS_BY_ERR_MASK                    (0x08000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CMD_NOT_ISS_BY_ERR_SHIFT                   (0x0000001BU)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CMD_NOT_ISS_BY_ERR_RESETVAL                (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_CMD_NOT_ISS_BY_ERR_MAX                     (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_SUB_COMMAND_STS_MASK                       (0x10000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SUB_COMMAND_STS_SHIFT                      (0x0000001CU)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SUB_COMMAND_STS_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_SUB_COMMAND_STS_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_DORMANT_MASK                          (0x20000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_DORMANT_SHIFT                         (0x0000001DU)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_DORMANT_RESETVAL                      (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_DORMANT_MAX                           (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_DORMANT_VAL_NO_DORMANT                (0x0U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_DORMANT_VAL_DORMANT                   (0x1U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_LANE_SYNC_MASK                     (0x40000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_LANE_SYNC_SHIFT                    (0x0000001EU)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_LANE_SYNC_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_LANE_SYNC_MAX                      (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_LANE_SYNC_VAL_NO_INIT              (0x0U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_LANE_SYNC_VAL_INIT                 (0x1U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_DETECTION_MASK                     (0x80000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_DETECTION_SHIFT                    (0x0000001FU)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_DETECTION_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_PRESENTSTATE_UHS2_IF_DETECTION_MAX                      (0x00000001U)

#define CSL_MMC_CTLCFG_PRESENTSTATE_RESETVAL                                   (0x01F00000U)

/* HOST_CONTROL1 */

#define CSL_MMC_CTLCFG_HOST_CONTROL1_LED_CONTROL_MASK                          (0x01U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_LED_CONTROL_SHIFT                         (0x00U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_LED_CONTROL_RESETVAL                      (0x00U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_LED_CONTROL_MAX                           (0x01U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_LED_CONTROL_VAL_LED_OFF                   (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_LED_CONTROL_VAL_LED_ON                    (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_DATA_WIDTH_MASK                           (0x02U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_DATA_WIDTH_SHIFT                          (0x01U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_DATA_WIDTH_RESETVAL                       (0x00U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_DATA_WIDTH_MAX                            (0x01U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_DATA_WIDTH_VAL_BIT1                       (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_DATA_WIDTH_VAL_BIT4                       (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_HIGH_SPEED_ENA_MASK                       (0x04U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_HIGH_SPEED_ENA_SHIFT                      (0x02U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_HIGH_SPEED_ENA_RESETVAL                   (0x00U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_HIGH_SPEED_ENA_MAX                        (0x01U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_HIGH_SPEED_ENA_VAL_NORMAL                 (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_HIGH_SPEED_ENA_VAL_HIGH                   (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_DMA_SELECT_MASK                           (0x18U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_DMA_SELECT_SHIFT                          (0x03U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_DMA_SELECT_RESETVAL                       (0x00U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_DMA_SELECT_MAX                            (0x03U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_EXT_DATA_WIDTH_MASK                       (0x20U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_EXT_DATA_WIDTH_SHIFT                      (0x05U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_EXT_DATA_WIDTH_RESETVAL                   (0x00U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_EXT_DATA_WIDTH_MAX                        (0x01U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_EXT_DATA_WIDTH_VAL_DISABLE                (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_EXT_DATA_WIDTH_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_CD_TEST_LEVEL_MASK                        (0x40U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_CD_TEST_LEVEL_SHIFT                       (0x06U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_CD_TEST_LEVEL_RESETVAL                    (0x00U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_CD_TEST_LEVEL_MAX                         (0x01U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_CD_SIG_SEL_MASK                           (0x80U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_CD_SIG_SEL_SHIFT                          (0x07U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_CD_SIG_SEL_RESETVAL                       (0x00U)
#define CSL_MMC_CTLCFG_HOST_CONTROL1_CD_SIG_SEL_MAX                            (0x01U)

#define CSL_MMC_CTLCFG_HOST_CONTROL1_RESETVAL                                  (0x00U)

/* POWER_CONTROL */

#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_POWER_MASK                         (0x01U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_POWER_SHIFT                        (0x00U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_POWER_RESETVAL                     (0x00U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_POWER_MAX                          (0x01U)

#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_POWER_VAL_PWR_OFF                  (0x0U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_POWER_VAL_PWR_ON                   (0x1U)

#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_VOLTAGE_MASK                       (0x0EU)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_VOLTAGE_SHIFT                      (0x01U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_VOLTAGE_RESETVAL                   (0x00U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_VOLTAGE_MAX                        (0x07U)

#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_VOLTAGE_VAL_RSVD                   (0x0U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_VOLTAGE_VAL_VOLT_1P8               (0x5U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_VOLTAGE_VAL_VOLT_3P0               (0x6U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_SD_BUS_VOLTAGE_VAL_VOLT_3P3               (0x7U)

#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_POWER_MASK                           (0x10U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_POWER_SHIFT                          (0x04U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_POWER_RESETVAL                       (0x00U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_POWER_MAX                            (0x01U)

#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_POWER_VAL_PWR_OFF                    (0x0U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_POWER_VAL_PWR_ON                     (0x1U)

#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_VOLTAGE_MASK                         (0xE0U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_VOLTAGE_SHIFT                        (0x05U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_VOLTAGE_RESETVAL                     (0x00U)
#define CSL_MMC_CTLCFG_POWER_CONTROL_UHS2_VOLTAGE_MAX                          (0x07U)

#define CSL_MMC_CTLCFG_POWER_CONTROL_RESETVAL                                  (0x00U)

/* BLOCK_GAP_CONTROL */

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_STOP_AT_BLK_GAP_MASK                  (0x01U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_STOP_AT_BLK_GAP_SHIFT                 (0x00U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_STOP_AT_BLK_GAP_RESETVAL              (0x00U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_STOP_AT_BLK_GAP_MAX                   (0x01U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_STOP_AT_BLK_GAP_VAL_TRAN              (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_STOP_AT_BLK_GAP_VAL_STOP              (0x1U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_CONTINUE_MASK                         (0x02U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_CONTINUE_SHIFT                        (0x01U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_CONTINUE_RESETVAL                     (0x00U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_CONTINUE_MAX                          (0x01U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_CONTINUE_VAL_IGNORE                   (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_CONTINUE_VAL_RESTART                  (0x1U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_RDWAIT_CTRL_MASK                      (0x04U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_RDWAIT_CTRL_SHIFT                     (0x02U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_RDWAIT_CTRL_RESETVAL                  (0x00U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_RDWAIT_CTRL_MAX                       (0x01U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_RDWAIT_CTRL_VAL_DISABLE               (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_RDWAIT_CTRL_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_INTRPT_AT_BLK_GAP_MASK                (0x08U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_INTRPT_AT_BLK_GAP_SHIFT               (0x03U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_INTRPT_AT_BLK_GAP_RESETVAL            (0x00U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_INTRPT_AT_BLK_GAP_MAX                 (0x01U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_SPI_MODE_MASK                         (0x10U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_SPI_MODE_SHIFT                        (0x04U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_SPI_MODE_RESETVAL                     (0x00U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_SPI_MODE_MAX                          (0x01U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_SPI_MODE_VAL_DISABLE                  (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_SPI_MODE_VAL_ENABLE                   (0x1U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ENABLE_MASK                      (0x20U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ENABLE_SHIFT                     (0x05U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ENABLE_RESETVAL                  (0x00U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ENABLE_MAX                       (0x01U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ENABLE_VAL_DISABLE               (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ENABLE_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_ALT_BOOT_MODE_MASK                    (0x40U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_ALT_BOOT_MODE_SHIFT                   (0x06U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_ALT_BOOT_MODE_RESETVAL                (0x00U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_ALT_BOOT_MODE_MAX                     (0x01U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_ALT_BOOT_MODE_VAL_DISABLE             (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_ALT_BOOT_MODE_VAL_ENABLE              (0x1U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ACK_ENA_MASK                     (0x80U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ACK_ENA_SHIFT                    (0x07U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ACK_ENA_RESETVAL                 (0x01U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ACK_ENA_MAX                      (0x01U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ACK_ENA_VAL_DISABLE              (0x0U)
#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_BOOT_ACK_ENA_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_BLOCK_GAP_CONTROL_RESETVAL                              (0x80U)

/* WAKEUP_CONTROL */

#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INTERRUPT_MASK                      (0x01U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INTERRUPT_SHIFT                     (0x00U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INTERRUPT_RESETVAL                  (0x00U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INTERRUPT_MAX                       (0x01U)

#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INTERRUPT_VAL_DISABLE               (0x0U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INTERRUPT_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INSERTION_MASK                      (0x02U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INSERTION_SHIFT                     (0x01U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INSERTION_RESETVAL                  (0x00U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INSERTION_MAX                       (0x01U)

#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INSERTION_VAL_DISABLE               (0x0U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_INSERTION_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_REMOVAL_MASK                        (0x04U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_REMOVAL_SHIFT                       (0x02U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_REMOVAL_RESETVAL                    (0x00U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_REMOVAL_MAX                         (0x01U)

#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_REMOVAL_VAL_DISABLE                 (0x0U)
#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_CARD_REMOVAL_VAL_ENABLE                  (0x1U)

#define CSL_MMC_CTLCFG_WAKEUP_CONTROL_RESETVAL                                 (0x00U)

/* CLOCK_CONTROL */

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_ENA_MASK                          (0x0001U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_ENA_SHIFT                         (0x0000U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_ENA_RESETVAL                      (0x0000U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_ENA_MAX                           (0x0001U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_ENA_VAL_STOP                      (0x0U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_ENA_VAL_OSCILLATE                 (0x1U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_STABLE_MASK                       (0x0002U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_STABLE_SHIFT                      (0x0001U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_STABLE_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_STABLE_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_STABLE_VAL_NOT_READY              (0x0U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_INT_CLK_STABLE_VAL_READY                  (0x1U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SD_CLK_ENA_MASK                           (0x0004U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SD_CLK_ENA_SHIFT                          (0x0002U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SD_CLK_ENA_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SD_CLK_ENA_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SD_CLK_ENA_VAL_DISABLE                    (0x0U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SD_CLK_ENA_VAL_ENABLE                     (0x1U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_PLL_ENA_MASK                              (0x0008U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_PLL_ENA_SHIFT                             (0x0003U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_PLL_ENA_RESETVAL                          (0x0000U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_PLL_ENA_MAX                               (0x0001U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_PLL_ENA_VAL_DISABLE                       (0x0U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_PLL_ENA_VAL_ENABLE                        (0x1U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_CLKGEN_SEL_MASK                           (0x0020U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_CLKGEN_SEL_SHIFT                          (0x0005U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_CLKGEN_SEL_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_CLKGEN_SEL_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_CLKGEN_SEL_VAL_DIV_CLK                    (0x0U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_CLKGEN_SEL_VAL_PRG_CLK                    (0x1U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SDCLK_FRQSEL_UPBITS_MASK                  (0x00C0U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SDCLK_FRQSEL_UPBITS_SHIFT                 (0x0006U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SDCLK_FRQSEL_UPBITS_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SDCLK_FRQSEL_UPBITS_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SDCLK_FRQSEL_MASK                         (0xFF00U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SDCLK_FRQSEL_SHIFT                        (0x0008U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SDCLK_FRQSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_CLOCK_CONTROL_SDCLK_FRQSEL_MAX                          (0x00FFU)

#define CSL_MMC_CTLCFG_CLOCK_CONTROL_RESETVAL                                  (0x0000U)

/* TIMEOUT_CONTROL */

#define CSL_MMC_CTLCFG_TIMEOUT_CONTROL_COUNTER_VALUE_MASK                      (0x0FU)
#define CSL_MMC_CTLCFG_TIMEOUT_CONTROL_COUNTER_VALUE_SHIFT                     (0x00U)
#define CSL_MMC_CTLCFG_TIMEOUT_CONTROL_COUNTER_VALUE_RESETVAL                  (0x00U)
#define CSL_MMC_CTLCFG_TIMEOUT_CONTROL_COUNTER_VALUE_MAX                       (0x0FU)

#define CSL_MMC_CTLCFG_TIMEOUT_CONTROL_RESETVAL                                (0x00U)

/* SOFTWARE_RESET */

#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_ALL_MASK                       (0x01U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_ALL_SHIFT                      (0x00U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_ALL_RESETVAL                   (0x00U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_ALL_MAX                        (0x01U)

#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_ALL_VAL_WORK                   (0x0U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_ALL_VAL_RESET                  (0x1U)

#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_CMD_MASK                       (0x02U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_CMD_SHIFT                      (0x01U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_CMD_RESETVAL                   (0x00U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_CMD_MAX                        (0x01U)

#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_CMD_VAL_WORK                   (0x0U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_CMD_VAL_RESET                  (0x1U)

#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_DAT_MASK                       (0x04U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_DAT_SHIFT                      (0x02U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_DAT_RESETVAL                   (0x00U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_DAT_MAX                        (0x01U)

#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_DAT_VAL_WORK                   (0x0U)
#define CSL_MMC_CTLCFG_SOFTWARE_RESET_SWRST_FOR_DAT_VAL_RESET                  (0x1U)

#define CSL_MMC_CTLCFG_SOFTWARE_RESET_RESETVAL                                 (0x00U)

/* NORMAL_INTR_STS */

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_MASK                       (0x0001U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_SHIFT                      (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_VAL_NO_INT                 (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CMD_COMPLETE_VAL_INT_SET                (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_MASK                      (0x0002U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_SHIFT                     (0x0001U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_VAL_NO_INT                (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_XFER_COMPLETE_VAL_INT_SET               (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BLK_GAP_EVENT_MASK                      (0x0004U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BLK_GAP_EVENT_SHIFT                     (0x0002U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BLK_GAP_EVENT_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BLK_GAP_EVENT_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BLK_GAP_EVENT_VAL_NO_INT                (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BLK_GAP_EVENT_VAL_INT_SET               (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_DMA_INTERRUPT_MASK                      (0x0008U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_DMA_INTERRUPT_SHIFT                     (0x0003U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_DMA_INTERRUPT_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_DMA_INTERRUPT_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_DMA_INTERRUPT_VAL_NO_INT                (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_DMA_INTERRUPT_VAL_INT_SET               (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_WR_READY_MASK                       (0x0010U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_WR_READY_SHIFT                      (0x0004U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_WR_READY_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_WR_READY_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_WR_READY_VAL_NO_INT                 (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_WR_READY_VAL_INT_SET                (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_RD_READY_MASK                       (0x0020U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_RD_READY_SHIFT                      (0x0005U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_RD_READY_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_RD_READY_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_RD_READY_VAL_NO_INT                 (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BUF_RD_READY_VAL_INT_SET                (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INS_MASK                           (0x0040U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INS_SHIFT                          (0x0006U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INS_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INS_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INS_VAL_NO_INT                     (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INS_VAL_INT_SET                    (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_REM_MASK                           (0x0080U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_REM_SHIFT                          (0x0007U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_REM_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_REM_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_REM_VAL_NO_INT                     (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_REM_VAL_INT_SET                    (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INTR_MASK                          (0x0100U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INTR_SHIFT                         (0x0008U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INTR_RESETVAL                      (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INTR_MAX                           (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INTR_VAL_NO_INT                    (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_CARD_INTR_VAL_INT_SET                   (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTA_MASK                               (0x0200U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTA_SHIFT                              (0x0009U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTA_RESETVAL                           (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTA_MAX                                (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTB_MASK                               (0x0400U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTB_SHIFT                              (0x000AU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTB_RESETVAL                           (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTB_MAX                                (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTC_MASK                               (0x0800U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTC_SHIFT                              (0x000BU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTC_RESETVAL                           (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_INTC_MAX                                (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RETUNING_EVENT_MASK                     (0x1000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RETUNING_EVENT_SHIFT                    (0x000CU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RETUNING_EVENT_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RETUNING_EVENT_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RCV_BOOT_ACK_MASK                       (0x2000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RCV_BOOT_ACK_SHIFT                      (0x000DU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RCV_BOOT_ACK_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RCV_BOOT_ACK_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RCV_BOOT_ACK_VAL_NO_INT                 (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RCV_BOOT_ACK_VAL_INT_SET                (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BOOT_COMPLETE_MASK                      (0x4000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BOOT_COMPLETE_SHIFT                     (0x000EU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BOOT_COMPLETE_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BOOT_COMPLETE_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BOOT_COMPLETE_VAL_NO_INT                (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_BOOT_COMPLETE_VAL_INT_SET               (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ERROR_INTR_MASK                         (0x8000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ERROR_INTR_SHIFT                        (0x000FU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ERROR_INTR_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ERROR_INTR_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ERROR_INTR_VAL_NO_INT                   (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ERROR_INTR_VAL_INT_SET                  (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_RESETVAL                                (0x0000U)

/* ERROR_INTR_STS */

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_TIMEOUT_MASK                         (0x0001U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_TIMEOUT_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_TIMEOUT_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_TIMEOUT_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_TIMEOUT_VAL_NO_ERR                   (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_TIMEOUT_VAL_ERROR                    (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_CRC_MASK                             (0x0002U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_CRC_SHIFT                            (0x0001U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_CRC_RESETVAL                         (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_CRC_MAX                              (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_CRC_VAL_NO_ERR                       (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_CRC_VAL_ERROR                        (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_ENDBIT_MASK                          (0x0004U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_ENDBIT_SHIFT                         (0x0002U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_ENDBIT_RESETVAL                      (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_ENDBIT_MAX                           (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_ENDBIT_VAL_NO_ERR                    (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_ENDBIT_VAL_ERROR                     (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_INDEX_MASK                           (0x0008U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_INDEX_SHIFT                          (0x0003U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_INDEX_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_INDEX_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_INDEX_VAL_NO_ERR                     (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CMD_INDEX_VAL_ERROR                      (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_TIMEOUT_MASK                        (0x0010U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_TIMEOUT_SHIFT                       (0x0004U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_TIMEOUT_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_TIMEOUT_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_TIMEOUT_VAL_NO_ERR                  (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_TIMEOUT_VAL_ERROR                   (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_CRC_MASK                            (0x0020U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_CRC_SHIFT                           (0x0005U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_CRC_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_CRC_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_CRC_VAL_NO_ERR                      (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_CRC_VAL_ERROR                       (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_ENDBIT_MASK                         (0x0040U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_ENDBIT_SHIFT                        (0x0006U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_ENDBIT_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_ENDBIT_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_ENDBIT_VAL_NO_ERR                   (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_DATA_ENDBIT_VAL_ERROR                    (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CURR_LIMIT_MASK                          (0x0080U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CURR_LIMIT_SHIFT                         (0x0007U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CURR_LIMIT_RESETVAL                      (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CURR_LIMIT_MAX                           (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CURR_LIMIT_VAL_NO_ERR                    (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_CURR_LIMIT_VAL_ERROR                     (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_AUTO_CMD_MASK                            (0x0100U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_AUTO_CMD_SHIFT                           (0x0008U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_AUTO_CMD_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_AUTO_CMD_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_AUTO_CMD_VAL_NO_ERR                      (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_AUTO_CMD_VAL_ERROR                       (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ADMA_MASK                                (0x0200U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ADMA_SHIFT                               (0x0009U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ADMA_RESETVAL                            (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ADMA_MAX                                 (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ADMA_VAL_NO_ERR                          (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ADMA_VAL_ERROR                           (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_TUNING_MASK                              (0x0400U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_TUNING_SHIFT                             (0x000AU)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_TUNING_RESETVAL                          (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_TUNING_MAX                               (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_TUNING_VAL_NO_ERR                        (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_TUNING_VAL_ERROR                         (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_RESP_MASK                                (0x0800U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_RESP_SHIFT                               (0x000BU)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_RESP_RESETVAL                            (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_RESP_MAX                                 (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_RESP_VAL_NO_ERR                          (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_RESP_VAL_ERROR                           (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_HOST_MASK                                (0x1000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_HOST_SHIFT                               (0x000CU)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_HOST_RESETVAL                            (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_HOST_MAX                                 (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_HOST_VAL_NO_ERR                          (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_HOST_VAL_ERROR                           (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_RESETVAL                                 (0x0000U)

/* NORMAL_INTR_STS_ENA */

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CMD_COMPLETE_MASK                   (0x0001U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CMD_COMPLETE_SHIFT                  (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CMD_COMPLETE_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CMD_COMPLETE_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CMD_COMPLETE_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CMD_COMPLETE_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_XFER_COMPLETE_MASK                  (0x0002U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_XFER_COMPLETE_SHIFT                 (0x0001U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_XFER_COMPLETE_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_XFER_COMPLETE_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_XFER_COMPLETE_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_XFER_COMPLETE_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BLK_GAP_EVENT_MASK                  (0x0004U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BLK_GAP_EVENT_SHIFT                 (0x0002U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BLK_GAP_EVENT_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BLK_GAP_EVENT_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BLK_GAP_EVENT_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BLK_GAP_EVENT_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_DMA_INTERRUPT_MASK                  (0x0008U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_DMA_INTERRUPT_SHIFT                 (0x0003U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_DMA_INTERRUPT_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_DMA_INTERRUPT_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_DMA_INTERRUPT_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_DMA_INTERRUPT_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_WR_READY_MASK                   (0x0010U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_WR_READY_SHIFT                  (0x0004U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_WR_READY_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_WR_READY_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_WR_READY_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_WR_READY_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_RD_READY_MASK                   (0x0020U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_RD_READY_SHIFT                  (0x0005U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_RD_READY_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_RD_READY_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_RD_READY_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BUF_RD_READY_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INSERTION_MASK                 (0x0040U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INSERTION_SHIFT                (0x0006U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INSERTION_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INSERTION_MAX                  (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INSERTION_VAL_MASK             (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INSERTION_VAL_ENABLE           (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_REMOVAL_MASK                   (0x0080U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_REMOVAL_SHIFT                  (0x0007U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_REMOVAL_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_REMOVAL_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_REMOVAL_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_REMOVAL_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INTERRUPT_MASK                 (0x0100U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INTERRUPT_SHIFT                (0x0008U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INTERRUPT_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INTERRUPT_MAX                  (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INTERRUPT_VAL_MASK             (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_CARD_INTERRUPT_VAL_ENABLE           (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTA_MASK                           (0x0200U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTA_SHIFT                          (0x0009U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTA_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTA_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTA_VAL_MASK                       (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTA_VAL_ENABLE                     (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTB_MASK                           (0x0400U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTB_SHIFT                          (0x000AU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTB_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTB_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTB_VAL_MASK                       (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTB_VAL_ENABLE                     (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTC_MASK                           (0x0800U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTC_SHIFT                          (0x000BU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTC_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTC_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTC_VAL_MASK                       (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_INTC_VAL_ENABLE                     (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RETUNING_EVENT_MASK                 (0x1000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RETUNING_EVENT_SHIFT                (0x000CU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RETUNING_EVENT_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RETUNING_EVENT_MAX                  (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RETUNING_EVENT_VAL_MASK             (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RETUNING_EVENT_VAL_ENABLE           (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RCV_BOOT_ACK_MASK                   (0x2000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RCV_BOOT_ACK_SHIFT                  (0x000DU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RCV_BOOT_ACK_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RCV_BOOT_ACK_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RCV_BOOT_ACK_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RCV_BOOT_ACK_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BOOT_COMPLETE_MASK                  (0x4000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BOOT_COMPLETE_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BOOT_COMPLETE_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BOOT_COMPLETE_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BOOT_COMPLETE_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BOOT_COMPLETE_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BIT15_FIXED0_MASK                   (0x8000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BIT15_FIXED0_SHIFT                  (0x000FU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BIT15_FIXED0_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_BIT15_FIXED0_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_STS_ENA_RESETVAL                            (0x0000U)

/* ERROR_INTR_STS_ENA */

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_TIMEOUT_MASK                     (0x0001U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_TIMEOUT_SHIFT                    (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_TIMEOUT_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_TIMEOUT_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_TIMEOUT_VAL_MASK                 (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_TIMEOUT_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_CRC_MASK                         (0x0002U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_CRC_SHIFT                        (0x0001U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_CRC_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_CRC_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_CRC_VAL_MASK                     (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_CRC_VAL_ENABLE                   (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_ENDBIT_MASK                      (0x0004U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_ENDBIT_SHIFT                     (0x0002U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_ENDBIT_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_ENDBIT_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_ENDBIT_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_ENDBIT_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_INDEX_MASK                       (0x0008U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_INDEX_SHIFT                      (0x0003U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_INDEX_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_INDEX_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_INDEX_VAL_MASK                   (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CMD_INDEX_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_TIMEOUT_MASK                    (0x0010U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_TIMEOUT_SHIFT                   (0x0004U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_TIMEOUT_RESETVAL                (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_TIMEOUT_MAX                     (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_TIMEOUT_VAL_MASK                (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_TIMEOUT_VAL_ENABLE              (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_CRC_MASK                        (0x0020U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_CRC_SHIFT                       (0x0005U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_CRC_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_CRC_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_CRC_VAL_MASK                    (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_CRC_VAL_ENABLE                  (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_ENDBIT_MASK                     (0x0040U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_ENDBIT_SHIFT                    (0x0006U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_ENDBIT_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_ENDBIT_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_ENDBIT_VAL_MASK                 (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_DATA_ENDBIT_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CURR_LIMIT_MASK                      (0x0080U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CURR_LIMIT_SHIFT                     (0x0007U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CURR_LIMIT_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CURR_LIMIT_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CURR_LIMIT_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_CURR_LIMIT_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_AUTO_CMD_MASK                        (0x0100U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_AUTO_CMD_SHIFT                       (0x0008U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_AUTO_CMD_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_AUTO_CMD_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_AUTO_CMD_VAL_MASK                    (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_AUTO_CMD_VAL_ENABLE                  (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_ADMA_MASK                            (0x0200U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_ADMA_SHIFT                           (0x0009U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_ADMA_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_ADMA_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_ADMA_VAL_MASK                        (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_ADMA_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_TUNING_MASK                          (0x0400U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_TUNING_SHIFT                         (0x000AU)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_TUNING_RESETVAL                      (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_TUNING_MAX                           (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_TUNING_VAL_MASK                      (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_TUNING_VAL_ENABLE                    (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_RESP_MASK                            (0x0800U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_RESP_SHIFT                           (0x000BU)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_RESP_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_RESP_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_RESP_VAL_MASK                        (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_RESP_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_HOST_MASK                            (0x1000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_HOST_SHIFT                           (0x000CU)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_HOST_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_HOST_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_HOST_VAL_MASK                        (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_HOST_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_VENDOR_SPECIFIC_MASK                 (0x6000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_VENDOR_SPECIFIC_SHIFT                (0x000DU)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_VENDOR_SPECIFIC_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_VENDOR_SPECIFIC_MAX                  (0x0003U)

#define CSL_MMC_CTLCFG_ERROR_INTR_STS_ENA_RESETVAL                             (0x0000U)

/* NORMAL_INTR_SIG_ENA */

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CMD_COMPLETE_MASK                   (0x0001U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CMD_COMPLETE_SHIFT                  (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CMD_COMPLETE_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CMD_COMPLETE_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CMD_COMPLETE_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CMD_COMPLETE_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_XFER_COMPLETE_MASK                  (0x0002U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_XFER_COMPLETE_SHIFT                 (0x0001U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_XFER_COMPLETE_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_XFER_COMPLETE_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_XFER_COMPLETE_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_XFER_COMPLETE_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BLK_GAP_EVENT_MASK                  (0x0004U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BLK_GAP_EVENT_SHIFT                 (0x0002U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BLK_GAP_EVENT_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BLK_GAP_EVENT_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BLK_GAP_EVENT_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BLK_GAP_EVENT_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_DMA_INTERRUPT_MASK                  (0x0008U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_DMA_INTERRUPT_SHIFT                 (0x0003U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_DMA_INTERRUPT_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_DMA_INTERRUPT_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_DMA_INTERRUPT_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_DMA_INTERRUPT_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_WR_READY_MASK                   (0x0010U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_WR_READY_SHIFT                  (0x0004U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_WR_READY_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_WR_READY_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_WR_READY_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_WR_READY_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_RD_READY_MASK                   (0x0020U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_RD_READY_SHIFT                  (0x0005U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_RD_READY_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_RD_READY_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_RD_READY_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BUF_RD_READY_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INSERTION_MASK                 (0x0040U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INSERTION_SHIFT                (0x0006U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INSERTION_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INSERTION_MAX                  (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INSERTION_VAL_MASK             (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INSERTION_VAL_ENABLE           (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_REMOVAL_MASK                   (0x0080U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_REMOVAL_SHIFT                  (0x0007U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_REMOVAL_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_REMOVAL_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_REMOVAL_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_REMOVAL_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INTERRUPT_MASK                 (0x0100U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INTERRUPT_SHIFT                (0x0008U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INTERRUPT_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INTERRUPT_MAX                  (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INTERRUPT_VAL_MASK             (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_CARD_INTERRUPT_VAL_ENABLE           (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTA_MASK                           (0x0200U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTA_SHIFT                          (0x0009U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTA_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTA_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTA_VAL_MASK                       (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTA_VAL_ENABLE                     (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTB_MASK                           (0x0400U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTB_SHIFT                          (0x000AU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTB_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTB_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTB_VAL_MASK                       (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTB_VAL_ENABLE                     (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTC_MASK                           (0x0800U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTC_SHIFT                          (0x000BU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTC_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTC_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTC_VAL_MASK                       (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_INTC_VAL_ENABLE                     (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RETUNING_EVENT_MASK                 (0x1000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RETUNING_EVENT_SHIFT                (0x000CU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RETUNING_EVENT_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RETUNING_EVENT_MAX                  (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RETUNING_EVENT_VAL_MASK             (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RETUNING_EVENT_VAL_ENABLE           (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RCV_BOOT_ACK_MASK                   (0x2000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RCV_BOOT_ACK_SHIFT                  (0x000DU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RCV_BOOT_ACK_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RCV_BOOT_ACK_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RCV_BOOT_ACK_VAL_MASK               (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RCV_BOOT_ACK_VAL_ENABLE             (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BOOT_COMPLETE_MASK                  (0x4000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BOOT_COMPLETE_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BOOT_COMPLETE_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BOOT_COMPLETE_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BOOT_COMPLETE_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BOOT_COMPLETE_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BIT15_FIXED0_MASK                   (0x8000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BIT15_FIXED0_SHIFT                  (0x000FU)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BIT15_FIXED0_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_BIT15_FIXED0_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_NORMAL_INTR_SIG_ENA_RESETVAL                            (0x0000U)

/* ERROR_INTR_SIG_ENA */

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_TIMEOUT_MASK                     (0x0001U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_TIMEOUT_SHIFT                    (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_TIMEOUT_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_TIMEOUT_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_TIMEOUT_VAL_MASK                 (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_TIMEOUT_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_CRC_MASK                         (0x0002U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_CRC_SHIFT                        (0x0001U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_CRC_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_CRC_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_CRC_VAL_MASK                     (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_CRC_VAL_ENABLE                   (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_ENDBIT_MASK                      (0x0004U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_ENDBIT_SHIFT                     (0x0002U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_ENDBIT_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_ENDBIT_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_ENDBIT_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_ENDBIT_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_INDEX_MASK                       (0x0008U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_INDEX_SHIFT                      (0x0003U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_INDEX_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_INDEX_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_INDEX_VAL_MASK                   (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CMD_INDEX_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_TIMEOUT_MASK                    (0x0010U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_TIMEOUT_SHIFT                   (0x0004U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_TIMEOUT_RESETVAL                (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_TIMEOUT_MAX                     (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_TIMEOUT_VAL_MASK                (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_TIMEOUT_VAL_ENABLE              (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_CRC_MASK                        (0x0020U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_CRC_SHIFT                       (0x0005U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_CRC_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_CRC_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_CRC_VAL_MASK                    (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_CRC_VAL_ENABLE                  (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_ENDBIT_MASK                     (0x0040U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_ENDBIT_SHIFT                    (0x0006U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_ENDBIT_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_ENDBIT_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_ENDBIT_VAL_MASK                 (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_DATA_ENDBIT_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CURR_LIMIT_MASK                      (0x0080U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CURR_LIMIT_SHIFT                     (0x0007U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CURR_LIMIT_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CURR_LIMIT_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CURR_LIMIT_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_CURR_LIMIT_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_AUTO_CMD_MASK                        (0x0100U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_AUTO_CMD_SHIFT                       (0x0008U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_AUTO_CMD_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_AUTO_CMD_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_AUTO_CMD_VAL_MASK                    (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_AUTO_CMD_VAL_ENABLE                  (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_ADMA_MASK                            (0x0200U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_ADMA_SHIFT                           (0x0009U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_ADMA_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_ADMA_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_ADMA_VAL_MASK                        (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_ADMA_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_TUNING_MASK                          (0x0400U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_TUNING_SHIFT                         (0x000AU)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_TUNING_RESETVAL                      (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_TUNING_MAX                           (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_TUNING_VAL_MASK                      (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_TUNING_VAL_ENABLE                    (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_RESP_MASK                            (0x0800U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_RESP_SHIFT                           (0x000BU)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_RESP_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_RESP_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_RESP_VAL_MASK                        (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_RESP_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_HOST_MASK                            (0x1000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_HOST_SHIFT                           (0x000CU)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_HOST_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_HOST_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_HOST_VAL_MASK                        (0x0U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_HOST_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_VENDOR_SPECIFIC_MASK                 (0x6000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_VENDOR_SPECIFIC_SHIFT                (0x000DU)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_VENDOR_SPECIFIC_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_VENDOR_SPECIFIC_MAX                  (0x0003U)

#define CSL_MMC_CTLCFG_ERROR_INTR_SIG_ENA_RESETVAL                             (0x0000U)

/* AUTOCMD_ERR_STS */

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ACMD12_NOT_EXEC_MASK                    (0x0001U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ACMD12_NOT_EXEC_SHIFT                   (0x0000U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ACMD12_NOT_EXEC_RESETVAL                (0x0000U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ACMD12_NOT_EXEC_MAX                     (0x0001U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ACMD12_NOT_EXEC_VAL_EXEC                (0x0U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ACMD12_NOT_EXEC_VAL_NOT_EXEC            (0x1U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_TIMEOUT_MASK                            (0x0002U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_TIMEOUT_SHIFT                           (0x0001U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_TIMEOUT_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_TIMEOUT_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_TIMEOUT_VAL_NO_ERR                      (0x0U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_TIMEOUT_VAL_ERROR                       (0x1U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CRC_MASK                                (0x0004U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CRC_SHIFT                               (0x0002U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CRC_RESETVAL                            (0x0000U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CRC_MAX                                 (0x0001U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CRC_VAL_NO_ERR                          (0x0U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CRC_VAL_ERROR                           (0x1U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ENDBIT_MASK                             (0x0008U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ENDBIT_SHIFT                            (0x0003U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ENDBIT_RESETVAL                         (0x0000U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ENDBIT_MAX                              (0x0001U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ENDBIT_VAL_NO_ERR                       (0x0U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_ENDBIT_VAL_ERROR                        (0x1U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_INDEX_MASK                              (0x0010U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_INDEX_SHIFT                             (0x0004U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_INDEX_RESETVAL                          (0x0000U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_INDEX_MAX                               (0x0001U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_INDEX_VAL_NO_ERR                        (0x0U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_INDEX_VAL_ERROR                         (0x1U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_RESP_MASK                               (0x0020U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_RESP_SHIFT                              (0x0005U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_RESP_RESETVAL                           (0x0000U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_RESP_MAX                                (0x0001U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_RESP_VAL_NO_ERR                         (0x0U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_RESP_VAL_ERROR                          (0x1U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CMD_NOT_ISSUED_MASK                     (0x0080U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CMD_NOT_ISSUED_SHIFT                    (0x0007U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CMD_NOT_ISSUED_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CMD_NOT_ISSUED_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CMD_NOT_ISSUED_VAL_NO_ERR               (0x0U)
#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_CMD_NOT_ISSUED_VAL_ERROR                (0x1U)

#define CSL_MMC_CTLCFG_AUTOCMD_ERR_STS_RESETVAL                                (0x0000U)

/* HOST_CONTROL2 */

#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_MASK                      (0x0007U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_SHIFT                     (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_MAX                       (0x0007U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_VAL_SDR12                 (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_VAL_SDR25                 (0x1U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_VAL_SDR50                 (0x2U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_VAL_SDR104                (0x3U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_VAL_DDR50                 (0x4U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_VAL_HS400                 (0x5U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_VAL_RSVD                  (0x6U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS_MODE_SELECT_VAL_UHS2                  (0x7U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_V1P8_SIGNAL_ENA_MASK                      (0x0008U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_V1P8_SIGNAL_ENA_SHIFT                     (0x0003U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_V1P8_SIGNAL_ENA_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_V1P8_SIGNAL_ENA_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_V1P8_SIGNAL_ENA_VAL_DISABLE               (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_V1P8_SIGNAL_ENA_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH1_MASK                     (0x0030U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH1_SHIFT                    (0x0004U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH1_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH1_MAX                      (0x0003U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH1_VAL_TYPE_B               (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH1_VAL_TYPE_A               (0x1U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH1_VAL_TYPE_C               (0x2U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH1_VAL_TYPE_D               (0x3U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_EXECUTE_TUNING_MASK                       (0x0040U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_EXECUTE_TUNING_SHIFT                      (0x0006U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_EXECUTE_TUNING_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_EXECUTE_TUNING_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_SAMPLING_CLK_SELECT_MASK                  (0x0080U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_SAMPLING_CLK_SELECT_SHIFT                 (0x0007U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_SAMPLING_CLK_SELECT_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_SAMPLING_CLK_SELECT_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_SAMPLING_CLK_SELECT_VAL_FIXED             (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_SAMPLING_CLK_SELECT_VAL_TUNED             (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS2_INTF_ENABLE_MASK                     (0x0100U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS2_INTF_ENABLE_SHIFT                    (0x0008U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS2_INTF_ENABLE_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS2_INTF_ENABLE_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS2_INTF_ENABLE_VAL_DISABLE              (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_UHS2_INTF_ENABLE_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH2_MASK                     (0x0200U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH2_SHIFT                    (0x0009U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH2_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_DRIVER_STRENGTH2_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_ADMA2_LEN_MODE_MASK                       (0x0400U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_ADMA2_LEN_MODE_SHIFT                      (0x000AU)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_ADMA2_LEN_MODE_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_ADMA2_LEN_MODE_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_ADMA2_LEN_MODE_VAL_LEN16                  (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_ADMA2_LEN_MODE_VAL_LEN26                  (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_CMD23_ENA_MASK                            (0x0800U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_CMD23_ENA_SHIFT                           (0x000BU)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_CMD23_ENA_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_CMD23_ENA_MAX                             (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_CMD23_ENA_VAL_DISABLE                     (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_CMD23_ENA_VAL_ENABLE                      (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_HOST_VER40_ENA_MASK                       (0x1000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_HOST_VER40_ENA_SHIFT                      (0x000CU)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_HOST_VER40_ENA_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_HOST_VER40_ENA_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_HOST_VER40_ENA_VAL_DISABLE                (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_HOST_VER40_ENA_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_BIT64_ADDRESSING_MASK                     (0x2000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_BIT64_ADDRESSING_SHIFT                    (0x000DU)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_BIT64_ADDRESSING_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_BIT64_ADDRESSING_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_BIT64_ADDRESSING_VAL_ADDR32               (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_BIT64_ADDRESSING_VAL_ADDR64               (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_ASYNCH_INTR_ENA_MASK                      (0x4000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_ASYNCH_INTR_ENA_SHIFT                     (0x000EU)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_ASYNCH_INTR_ENA_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_ASYNCH_INTR_ENA_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_ASYNCH_INTR_ENA_VAL_DISABLE               (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_ASYNCH_INTR_ENA_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_PRESET_VALUE_ENA_MASK                     (0x8000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_PRESET_VALUE_ENA_SHIFT                    (0x000FU)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_PRESET_VALUE_ENA_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_PRESET_VALUE_ENA_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_PRESET_VALUE_ENA_VAL_DISABLE              (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROL2_PRESET_VALUE_ENA_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_HOST_CONTROL2_RESETVAL                                  (0x0000U)

/* CAPABILITIES */

#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_FREQ_MASK                      (0x000000000000003FU)
#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_FREQ_SHIFT                     (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_FREQ_RESETVAL                  (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_FREQ_MAX                       (0x000000000000003FU)

#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_UNIT_MASK                      (0x0000000000000080U)
#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_UNIT_SHIFT                     (0x0000000000000007U)
#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_UNIT_RESETVAL                  (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_UNIT_MAX                       (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_UNIT_VAL_UNIT_KHZ              (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_TIMEOUT_CLK_UNIT_VAL_UNIT_MHZ              (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_BASE_CLK_FREQ_MASK                         (0x000000000000FF00U)
#define CSL_MMC_CTLCFG_CAPABILITIES_BASE_CLK_FREQ_SHIFT                        (0x0000000000000008U)
#define CSL_MMC_CTLCFG_CAPABILITIES_BASE_CLK_FREQ_RESETVAL                     (0x00000000000000C8U)
#define CSL_MMC_CTLCFG_CAPABILITIES_BASE_CLK_FREQ_MAX                          (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_CAPABILITIES_MAX_BLK_LENGTH_MASK                        (0x0000000000030000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_MAX_BLK_LENGTH_SHIFT                       (0x0000000000000010U)
#define CSL_MMC_CTLCFG_CAPABILITIES_MAX_BLK_LENGTH_RESETVAL                    (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_MAX_BLK_LENGTH_MAX                         (0x0000000000000003U)

#define CSL_MMC_CTLCFG_CAPABILITIES_MAX_BLK_LENGTH_VAL_MAX_512B                (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_MAX_BLK_LENGTH_VAL_MAX_1024B               (0x1U)
#define CSL_MMC_CTLCFG_CAPABILITIES_MAX_BLK_LENGTH_VAL_MAX_2048B               (0x2U)
#define CSL_MMC_CTLCFG_CAPABILITIES_MAX_BLK_LENGTH_VAL_MAX_4096B               (0x3U)

#define CSL_MMC_CTLCFG_CAPABILITIES_BUS_8BIT_SUPPORT_MASK                      (0x0000000000040000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_BUS_8BIT_SUPPORT_SHIFT                     (0x0000000000000012U)
#define CSL_MMC_CTLCFG_CAPABILITIES_BUS_8BIT_SUPPORT_RESETVAL                  (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_BUS_8BIT_SUPPORT_MAX                       (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_BUS_8BIT_SUPPORT_VAL_NOT_SUPPORT           (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_BUS_8BIT_SUPPORT_VAL_SUPPORT               (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA2_SUPPORT_MASK                         (0x0000000000080000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA2_SUPPORT_SHIFT                        (0x0000000000000013U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA2_SUPPORT_RESETVAL                     (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA2_SUPPORT_MAX                          (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA2_SUPPORT_VAL_NOT_SUPPORT              (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA2_SUPPORT_VAL_SUPPORT                  (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_HIGH_SPEED_SUPPORT_MASK                    (0x0000000000200000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_HIGH_SPEED_SUPPORT_SHIFT                   (0x0000000000000015U)
#define CSL_MMC_CTLCFG_CAPABILITIES_HIGH_SPEED_SUPPORT_RESETVAL                (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_HIGH_SPEED_SUPPORT_MAX                     (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_HIGH_SPEED_SUPPORT_VAL_NOT_SUPPORT         (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_HIGH_SPEED_SUPPORT_VAL_SUPPORT             (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SDMA_SUPPORT_MASK                          (0x0000000000400000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDMA_SUPPORT_SHIFT                         (0x0000000000000016U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDMA_SUPPORT_RESETVAL                      (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDMA_SUPPORT_MAX                           (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SDMA_SUPPORT_VAL_NOT_SUPPORT               (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDMA_SUPPORT_VAL_SUPPORT                   (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SUSP_RES_SUPPORT_MASK                      (0x0000000000800000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SUSP_RES_SUPPORT_SHIFT                     (0x0000000000000017U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SUSP_RES_SUPPORT_RESETVAL                  (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SUSP_RES_SUPPORT_MAX                       (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SUSP_RES_SUPPORT_VAL_NOT_SUPPORT           (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SUSP_RES_SUPPORT_VAL_SUPPORT               (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P3_SUPPORT_MASK                      (0x0000000001000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P3_SUPPORT_SHIFT                     (0x0000000000000018U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P3_SUPPORT_RESETVAL                  (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P3_SUPPORT_MAX                       (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P3_SUPPORT_VAL_NOT_SUPPORT           (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P3_SUPPORT_VAL_SUPPORT               (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P0_SUPPORT_MASK                      (0x0000000002000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P0_SUPPORT_SHIFT                     (0x0000000000000019U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P0_SUPPORT_RESETVAL                  (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P0_SUPPORT_MAX                       (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P0_SUPPORT_VAL_NOT_SUPPORT           (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_3P0_SUPPORT_VAL_SUPPORT               (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_1P8_SUPPORT_MASK                      (0x0000000004000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_1P8_SUPPORT_SHIFT                     (0x000000000000001AU)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_1P8_SUPPORT_RESETVAL                  (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_1P8_SUPPORT_MAX                       (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_1P8_SUPPORT_VAL_NOT_SUPPORT           (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VOLT_1P8_SUPPORT_VAL_SUPPORT               (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V4_MASK                 (0x0000000008000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V4_SHIFT                (0x000000000000001BU)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V4_RESETVAL             (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V4_MAX                  (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V4_VAL_NOT_SUPPORT      (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V4_VAL_SUPPORT          (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V3_MASK                 (0x0000000010000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V3_SHIFT                (0x000000000000001CU)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V3_RESETVAL             (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V3_MAX                  (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V3_VAL_NOT_SUPPORT      (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADDR_64BIT_SUPPORT_V3_VAL_SUPPORT          (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ASYNCH_INTR_SUPPORT_MASK                   (0x0000000020000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ASYNCH_INTR_SUPPORT_SHIFT                  (0x000000000000001DU)
#define CSL_MMC_CTLCFG_CAPABILITIES_ASYNCH_INTR_SUPPORT_RESETVAL               (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ASYNCH_INTR_SUPPORT_MAX                    (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ASYNCH_INTR_SUPPORT_VAL_NOT_SUPPORT        (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ASYNCH_INTR_SUPPORT_VAL_SUPPORT            (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SLOT_TYPE_MASK                             (0x00000000C0000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SLOT_TYPE_SHIFT                            (0x000000000000001EU)
#define CSL_MMC_CTLCFG_CAPABILITIES_SLOT_TYPE_RESETVAL                         (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SLOT_TYPE_MAX                              (0x0000000000000003U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SLOT_TYPE_VAL_REMOVABLE                    (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SLOT_TYPE_VAL_EMBEDDED                     (0x1U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SLOT_TYPE_VAL_SHARED                       (0x2U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SLOT_TYPE_VAL_RSVD                         (0x3U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SDR50_SUPPORT_MASK                         (0x0000000100000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDR50_SUPPORT_SHIFT                        (0x0000000000000020U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDR50_SUPPORT_RESETVAL                     (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDR50_SUPPORT_MAX                          (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SDR50_SUPPORT_VAL_NOT_SUPPORT              (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDR50_SUPPORT_VAL_SUPPORT                  (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SDR104_SUPPORT_MASK                        (0x0000000200000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDR104_SUPPORT_SHIFT                       (0x0000000000000021U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDR104_SUPPORT_RESETVAL                    (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDR104_SUPPORT_MAX                         (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SDR104_SUPPORT_VAL_NOT_SUPPORT             (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SDR104_SUPPORT_VAL_SUPPORT                 (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_DDR50_SUPPORT_MASK                         (0x0000000400000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DDR50_SUPPORT_SHIFT                        (0x0000000000000022U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DDR50_SUPPORT_RESETVAL                     (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DDR50_SUPPORT_MAX                          (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_DDR50_SUPPORT_VAL_NOT_SUPPORT              (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DDR50_SUPPORT_VAL_SUPPORT                  (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_UHS2_SUPPORT_MASK                          (0x0000000800000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_UHS2_SUPPORT_SHIFT                         (0x0000000000000023U)
#define CSL_MMC_CTLCFG_CAPABILITIES_UHS2_SUPPORT_RESETVAL                      (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_UHS2_SUPPORT_MAX                           (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_UHS2_SUPPORT_VAL_NOT_SUPPORT               (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_UHS2_SUPPORT_VAL_SUPPORT                   (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERA_SUPPORT_MASK                       (0x0000001000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERA_SUPPORT_SHIFT                      (0x0000000000000024U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERA_SUPPORT_RESETVAL                   (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERA_SUPPORT_MAX                        (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERA_SUPPORT_VAL_NOT_SUPPORT            (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERA_SUPPORT_VAL_SUPPORT                (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERC_SUPPORT_MASK                       (0x0000002000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERC_SUPPORT_SHIFT                      (0x0000000000000025U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERC_SUPPORT_RESETVAL                   (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERC_SUPPORT_MAX                        (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERC_SUPPORT_VAL_NOT_SUPPORT            (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERC_SUPPORT_VAL_SUPPORT                (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERD_SUPPORT_MASK                       (0x0000004000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERD_SUPPORT_SHIFT                      (0x0000000000000026U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERD_SUPPORT_RESETVAL                   (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERD_SUPPORT_MAX                        (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERD_SUPPORT_VAL_NOT_SUPPORT            (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_DRIVERD_SUPPORT_VAL_SUPPORT                (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_TIMER_CNT_MASK                    (0x00000F0000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_TIMER_CNT_SHIFT                   (0x0000000000000028U)
#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_TIMER_CNT_RESETVAL                (0x0000000000000004U)
#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_TIMER_CNT_MAX                     (0x000000000000000FU)

#define CSL_MMC_CTLCFG_CAPABILITIES_TUNING_FOR_SDR50_MASK                      (0x0000200000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_TUNING_FOR_SDR50_SHIFT                     (0x000000000000002DU)
#define CSL_MMC_CTLCFG_CAPABILITIES_TUNING_FOR_SDR50_RESETVAL                  (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_TUNING_FOR_SDR50_MAX                       (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_TUNING_FOR_SDR50_VAL_NO_TUNING             (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_TUNING_FOR_SDR50_VAL_TUNING_REQ            (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_MODES_MASK                        (0x0000C00000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_MODES_SHIFT                       (0x000000000000002EU)
#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_MODES_RESETVAL                    (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_MODES_MAX                         (0x0000000000000003U)

#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_MODES_VAL_MODE1                   (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_MODES_VAL_MODE2                   (0x1U)
#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_MODES_VAL_MODE3                   (0x2U)
#define CSL_MMC_CTLCFG_CAPABILITIES_RETUNING_MODES_VAL_RSVD                    (0x3U)

#define CSL_MMC_CTLCFG_CAPABILITIES_CLOCK_MULTIPLIER_MASK                      (0x00FF000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_CLOCK_MULTIPLIER_SHIFT                     (0x0000000000000030U)
#define CSL_MMC_CTLCFG_CAPABILITIES_CLOCK_MULTIPLIER_RESETVAL                  (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_CLOCK_MULTIPLIER_MAX                       (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_SUPPORT_MASK                           (0x0100000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_SUPPORT_SHIFT                          (0x0000000000000038U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_SUPPORT_RESETVAL                       (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_SUPPORT_MAX                            (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_SUPPORT_VAL_NOT_SUPPORT                (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_SUPPORT_VAL_SUPPORT                    (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_BLK_MODE_MASK                          (0x0200000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_BLK_MODE_SHIFT                         (0x0000000000000039U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_BLK_MODE_RESETVAL                      (0x0000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_BLK_MODE_MAX                           (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_BLK_MODE_VAL_NOT_SUPPORT               (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_SPI_BLK_MODE_VAL_SUPPORT                   (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA3_SUPPORT_MASK                         (0x0800000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA3_SUPPORT_SHIFT                        (0x000000000000003BU)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA3_SUPPORT_RESETVAL                     (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA3_SUPPORT_MAX                          (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA3_SUPPORT_VAL_NOT_SUPPORT              (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_ADMA3_SUPPORT_VAL_SUPPORT                  (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_VDD2_1P8_SUPPORT_MASK                      (0x1000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VDD2_1P8_SUPPORT_SHIFT                     (0x000000000000003CU)
#define CSL_MMC_CTLCFG_CAPABILITIES_VDD2_1P8_SUPPORT_RESETVAL                  (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VDD2_1P8_SUPPORT_MAX                       (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_VDD2_1P8_SUPPORT_VAL_NOT_SUPPORT           (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_VDD2_1P8_SUPPORT_VAL_SUPPORT               (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_HS400_SUPPORT_MASK                         (0x8000000000000000U)
#define CSL_MMC_CTLCFG_CAPABILITIES_HS400_SUPPORT_SHIFT                        (0x000000000000003FU)
#define CSL_MMC_CTLCFG_CAPABILITIES_HS400_SUPPORT_RESETVAL                     (0x0000000000000001U)
#define CSL_MMC_CTLCFG_CAPABILITIES_HS400_SUPPORT_MAX                          (0x0000000000000001U)

#define CSL_MMC_CTLCFG_CAPABILITIES_HS400_SUPPORT_VAL_NOT_SUPPORT              (0x0U)
#define CSL_MMC_CTLCFG_CAPABILITIES_HS400_SUPPORT_VAL_SUPPORT                  (0x1U)

#define CSL_MMC_CTLCFG_CAPABILITIES_RESETVAL                                   (0x980004077CECC801U)

/* MAX_CURRENT_CAP */

#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_3P3V_MASK                          (0x00000000000000FFU)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_3P3V_SHIFT                         (0x0000000000000000U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_3P3V_RESETVAL                      (0x0000000000000000U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_3P3V_MAX                           (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_3P0V_MASK                          (0x000000000000FF00U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_3P0V_SHIFT                         (0x0000000000000008U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_3P0V_RESETVAL                      (0x0000000000000000U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_3P0V_MAX                           (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_1P8V_MASK                          (0x0000000000FF0000U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_1P8V_SHIFT                         (0x0000000000000010U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_1P8V_RESETVAL                      (0x0000000000000000U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD1_1P8V_MAX                           (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD2_1P8V_MASK                          (0x000000FF00000000U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD2_1P8V_SHIFT                         (0x0000000000000020U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD2_1P8V_RESETVAL                      (0x0000000000000000U)
#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_VDD2_1P8V_MAX                           (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_MAX_CURRENT_CAP_RESETVAL                                (0x0000000000000000U)

/* FORCE_EVNT_ACMD_ERR_STS */

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ACMD_NOT_EXEC_MASK              (0x0001U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ACMD_NOT_EXEC_SHIFT             (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ACMD_NOT_EXEC_RESETVAL          (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ACMD_NOT_EXEC_MAX               (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ACMD_NOT_EXEC_VAL_NO_INT        (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ACMD_NOT_EXEC_VAL_INT_SET       (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_TIMEOUT_MASK                    (0x0002U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_TIMEOUT_SHIFT                   (0x0001U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_TIMEOUT_RESETVAL                (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_TIMEOUT_MAX                     (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_TIMEOUT_VAL_NO_INT              (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_TIMEOUT_VAL_INT_SET             (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CRC_MASK                        (0x0004U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CRC_SHIFT                       (0x0002U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CRC_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CRC_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CRC_VAL_NO_INT                  (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CRC_VAL_INT_SET                 (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ENDBIT_MASK                     (0x0008U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ENDBIT_SHIFT                    (0x0003U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ENDBIT_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ENDBIT_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ENDBIT_VAL_NO_INT               (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_ENDBIT_VAL_INT_SET              (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_INDEX_MASK                      (0x0010U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_INDEX_SHIFT                     (0x0004U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_INDEX_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_INDEX_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_INDEX_VAL_NO_INT                (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_INDEX_VAL_INT_SET               (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_RESP_MASK                       (0x0020U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_RESP_SHIFT                      (0x0005U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_RESP_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_RESP_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_RESP_VAL_NO_INT                 (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_RESP_VAL_INT_SET                (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CMD_NOT_ISS_MASK                (0x0080U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CMD_NOT_ISS_SHIFT               (0x0007U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CMD_NOT_ISS_RESETVAL            (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CMD_NOT_ISS_MAX                 (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CMD_NOT_ISS_VAL_NO_INT          (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_CMD_NOT_ISS_VAL_INT_SET         (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ACMD_ERR_STS_RESETVAL                        (0x0000U)

/* FORCE_EVNT_ERR_INT_STS */

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_TIMEOUT_MASK                 (0x0001U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_TIMEOUT_SHIFT                (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_TIMEOUT_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_TIMEOUT_MAX                  (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_TIMEOUT_VAL_NO_INT           (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_TIMEOUT_VAL_INT_SET          (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_CRC_MASK                     (0x0002U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_CRC_SHIFT                    (0x0001U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_CRC_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_CRC_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_CRC_VAL_NO_INT               (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_CRC_VAL_INT_SET              (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_ENDBIT_MASK                  (0x0004U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_ENDBIT_SHIFT                 (0x0002U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_ENDBIT_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_ENDBIT_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_ENDBIT_VAL_NO_INT            (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_ENDBIT_VAL_INT_SET           (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_INDEX_MASK                   (0x0008U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_INDEX_SHIFT                  (0x0003U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_INDEX_RESETVAL               (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_INDEX_MAX                    (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_INDEX_VAL_NO_INT             (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CMD_INDEX_VAL_INT_SET            (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_TIMEOUT_MASK                 (0x0010U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_TIMEOUT_SHIFT                (0x0004U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_TIMEOUT_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_TIMEOUT_MAX                  (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_TIMEOUT_VAL_NO_INT           (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_TIMEOUT_VAL_INT_SET          (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_CRC_MASK                     (0x0020U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_CRC_SHIFT                    (0x0005U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_CRC_RESETVAL                 (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_CRC_MAX                      (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_CRC_VAL_NO_INT               (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_CRC_VAL_INT_SET              (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_ENDBIT_MASK                  (0x0040U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_ENDBIT_SHIFT                 (0x0006U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_ENDBIT_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_ENDBIT_MAX                   (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_ENDBIT_VAL_NO_INT            (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_DAT_ENDBIT_VAL_INT_SET           (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CURR_LIM_MASK                    (0x0080U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CURR_LIM_SHIFT                   (0x0007U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CURR_LIM_RESETVAL                (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CURR_LIM_MAX                     (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CURR_LIM_VAL_NO_INT              (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_CURR_LIM_VAL_INT_SET             (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_AUTO_CMD_MASK                    (0x0100U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_AUTO_CMD_SHIFT                   (0x0008U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_AUTO_CMD_RESETVAL                (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_AUTO_CMD_MAX                     (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_AUTO_CMD_VAL_NO_INT              (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_AUTO_CMD_VAL_INT_SET             (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_ADMA_MASK                        (0x0200U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_ADMA_SHIFT                       (0x0009U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_ADMA_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_ADMA_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_ADMA_VAL_NO_INT                  (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_ADMA_VAL_INT_SET                 (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_TUNING_MASK                      (0x0400U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_TUNING_SHIFT                     (0x000AU)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_TUNING_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_TUNING_MAX                       (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_TUNING_VAL_NO_INT                (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_TUNING_VAL_INT_SET               (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_RESP_MASK                        (0x0800U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_RESP_SHIFT                       (0x000BU)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_RESP_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_RESP_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_RESP_VAL_NO_INT                  (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_RESP_VAL_INT_SET                 (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_HOST_MASK                        (0x1000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_HOST_SHIFT                       (0x000CU)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_HOST_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_HOST_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_HOST_VAL_NO_INT                  (0x0U)
#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_HOST_VAL_INT_SET                 (0x1U)

#define CSL_MMC_CTLCFG_FORCE_EVNT_ERR_INT_STS_RESETVAL                         (0x0000U)

/* ADMA_ERR_STATUS */

#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_ERR_STATE_MASK                     (0x03U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_ERR_STATE_SHIFT                    (0x00U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_ERR_STATE_RESETVAL                 (0x00U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_ERR_STATE_MAX                      (0x03U)

#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_ERR_STATE_VAL_ST_STOP              (0x0U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_ERR_STATE_VAL_ST_FDS               (0x1U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_ERR_STATE_VAL_NOT_USED             (0x2U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_ERR_STATE_VAL_ST_TFR               (0x3U)

#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_LENGTH_ERR_MASK                    (0x04U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_LENGTH_ERR_SHIFT                   (0x02U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_LENGTH_ERR_RESETVAL                (0x00U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_LENGTH_ERR_MAX                     (0x01U)

#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_LENGTH_ERR_VAL_NO_ERR              (0x0U)
#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_ADMA_LENGTH_ERR_VAL_ERROR               (0x1U)

#define CSL_MMC_CTLCFG_ADMA_ERR_STATUS_RESETVAL                                (0x00U)

/* ADMA_SYS_ADDRESS */

#define CSL_MMC_CTLCFG_ADMA_SYS_ADDRESS_ADMA_ADDR_MASK                         (0xFFFFFFFFFFFFFFFFU)
#define CSL_MMC_CTLCFG_ADMA_SYS_ADDRESS_ADMA_ADDR_SHIFT                        (0x0000000000000000U)
#define CSL_MMC_CTLCFG_ADMA_SYS_ADDRESS_ADMA_ADDR_RESETVAL                     (0x0000000000000000U)
#define CSL_MMC_CTLCFG_ADMA_SYS_ADDRESS_ADMA_ADDR_MAX                          (0xFFFFFFFFFFFFFFFFU)

#define CSL_MMC_CTLCFG_ADMA_SYS_ADDRESS_RESETVAL                               (0x0000000000000000U)

/* PRESET_VALUE0 */

#define CSL_MMC_CTLCFG_PRESET_VALUE0_SDCLK_FRQSEL_MASK                         (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_SDCLK_FRQSEL_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_SDCLK_FRQSEL_RESETVAL                     (0x0100U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_SDCLK_FRQSEL_MAX                          (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE0_CLOCK_GENSEL_MASK                         (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_CLOCK_GENSEL_SHIFT                        (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_CLOCK_GENSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_CLOCK_GENSEL_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE0_DRIVER_STRENGTH_SEL_MASK                  (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_DRIVER_STRENGTH_SEL_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_DRIVER_STRENGTH_SEL_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_DRIVER_STRENGTH_SEL_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE0_DRIVER_STRENGTH_SEL_VAL_TYPE_B            (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_DRIVER_STRENGTH_SEL_VAL_TYPE_A            (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_DRIVER_STRENGTH_SEL_VAL_TYPE_C            (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE0_DRIVER_STRENGTH_SEL_VAL_TYPE_D            (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE0_RESETVAL                                  (0x0100U)

/* PRESET_VALUE1 */

#define CSL_MMC_CTLCFG_PRESET_VALUE1_SDCLK_FRQSEL_MASK                         (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_SDCLK_FRQSEL_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_SDCLK_FRQSEL_RESETVAL                     (0x0004U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_SDCLK_FRQSEL_MAX                          (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE1_CLOCK_GENSEL_MASK                         (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_CLOCK_GENSEL_SHIFT                        (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_CLOCK_GENSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_CLOCK_GENSEL_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE1_DRIVER_STRENGTH_SEL_MASK                  (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_DRIVER_STRENGTH_SEL_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_DRIVER_STRENGTH_SEL_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_DRIVER_STRENGTH_SEL_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE1_DRIVER_STRENGTH_SEL_VAL_TYPE_B            (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_DRIVER_STRENGTH_SEL_VAL_TYPE_A            (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_DRIVER_STRENGTH_SEL_VAL_TYPE_C            (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE1_DRIVER_STRENGTH_SEL_VAL_TYPE_D            (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE1_RESETVAL                                  (0x0004U)

/* PRESET_VALUE2 */

#define CSL_MMC_CTLCFG_PRESET_VALUE2_SDCLK_FRQSEL_MASK                         (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_SDCLK_FRQSEL_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_SDCLK_FRQSEL_RESETVAL                     (0x0002U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_SDCLK_FRQSEL_MAX                          (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE2_CLOCK_GENSEL_MASK                         (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_CLOCK_GENSEL_SHIFT                        (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_CLOCK_GENSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_CLOCK_GENSEL_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE2_DRIVER_STRENGTH_SEL_MASK                  (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_DRIVER_STRENGTH_SEL_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_DRIVER_STRENGTH_SEL_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_DRIVER_STRENGTH_SEL_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE2_DRIVER_STRENGTH_SEL_VAL_TYPE_B            (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_DRIVER_STRENGTH_SEL_VAL_TYPE_A            (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_DRIVER_STRENGTH_SEL_VAL_TYPE_C            (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE2_DRIVER_STRENGTH_SEL_VAL_TYPE_D            (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE2_RESETVAL                                  (0x0002U)

/* PRESET_VALUE3 */

#define CSL_MMC_CTLCFG_PRESET_VALUE3_SDCLK_FRQSEL_MASK                         (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_SDCLK_FRQSEL_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_SDCLK_FRQSEL_RESETVAL                     (0x0004U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_SDCLK_FRQSEL_MAX                          (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE3_CLOCK_GENSEL_MASK                         (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_CLOCK_GENSEL_SHIFT                        (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_CLOCK_GENSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_CLOCK_GENSEL_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE3_DRIVER_STRENGTH_SEL_MASK                  (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_DRIVER_STRENGTH_SEL_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_DRIVER_STRENGTH_SEL_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_DRIVER_STRENGTH_SEL_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE3_DRIVER_STRENGTH_SEL_VAL_TYPE_B            (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_DRIVER_STRENGTH_SEL_VAL_TYPE_A            (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_DRIVER_STRENGTH_SEL_VAL_TYPE_C            (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE3_DRIVER_STRENGTH_SEL_VAL_TYPE_D            (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE3_RESETVAL                                  (0x0004U)

/* PRESET_VALUE4 */

#define CSL_MMC_CTLCFG_PRESET_VALUE4_SDCLK_FRQSEL_MASK                         (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_SDCLK_FRQSEL_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_SDCLK_FRQSEL_RESETVAL                     (0x0002U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_SDCLK_FRQSEL_MAX                          (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE4_CLOCK_GENSEL_MASK                         (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_CLOCK_GENSEL_SHIFT                        (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_CLOCK_GENSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_CLOCK_GENSEL_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE4_DRIVER_STRENGTH_SEL_MASK                  (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_DRIVER_STRENGTH_SEL_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_DRIVER_STRENGTH_SEL_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_DRIVER_STRENGTH_SEL_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE4_DRIVER_STRENGTH_SEL_VAL_TYPE_B            (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_DRIVER_STRENGTH_SEL_VAL_TYPE_A            (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_DRIVER_STRENGTH_SEL_VAL_TYPE_C            (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE4_DRIVER_STRENGTH_SEL_VAL_TYPE_D            (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE4_RESETVAL                                  (0x0002U)

/* PRESET_VALUE5 */

#define CSL_MMC_CTLCFG_PRESET_VALUE5_SDCLK_FRQSEL_MASK                         (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_SDCLK_FRQSEL_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_SDCLK_FRQSEL_RESETVAL                     (0x0001U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_SDCLK_FRQSEL_MAX                          (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE5_CLOCK_GENSEL_MASK                         (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_CLOCK_GENSEL_SHIFT                        (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_CLOCK_GENSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_CLOCK_GENSEL_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE5_DRIVER_STRENGTH_SEL_MASK                  (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_DRIVER_STRENGTH_SEL_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_DRIVER_STRENGTH_SEL_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_DRIVER_STRENGTH_SEL_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE5_DRIVER_STRENGTH_SEL_VAL_TYPE_B            (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_DRIVER_STRENGTH_SEL_VAL_TYPE_A            (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_DRIVER_STRENGTH_SEL_VAL_TYPE_C            (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE5_DRIVER_STRENGTH_SEL_VAL_TYPE_D            (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE5_RESETVAL                                  (0x0001U)

/* PRESET_VALUE6 */

#define CSL_MMC_CTLCFG_PRESET_VALUE6_SDCLK_FRQSEL_MASK                         (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_SDCLK_FRQSEL_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_SDCLK_FRQSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_SDCLK_FRQSEL_MAX                          (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE6_CLOCK_GENSEL_MASK                         (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_CLOCK_GENSEL_SHIFT                        (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_CLOCK_GENSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_CLOCK_GENSEL_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE6_DRIVER_STRENGTH_SEL_MASK                  (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_DRIVER_STRENGTH_SEL_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_DRIVER_STRENGTH_SEL_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_DRIVER_STRENGTH_SEL_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE6_DRIVER_STRENGTH_SEL_VAL_TYPE_B            (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_DRIVER_STRENGTH_SEL_VAL_TYPE_A            (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_DRIVER_STRENGTH_SEL_VAL_TYPE_C            (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE6_DRIVER_STRENGTH_SEL_VAL_TYPE_D            (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE6_RESETVAL                                  (0x0000U)

/* PRESET_VALUE7 */

#define CSL_MMC_CTLCFG_PRESET_VALUE7_SDCLK_FRQSEL_MASK                         (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_SDCLK_FRQSEL_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_SDCLK_FRQSEL_RESETVAL                     (0x0002U)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_SDCLK_FRQSEL_MAX                          (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE7_CLOCK_GENSEL_MASK                         (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_CLOCK_GENSEL_SHIFT                        (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_CLOCK_GENSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_CLOCK_GENSEL_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE7_DRIVER_STRENGTH_SEL_MASK                  (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_DRIVER_STRENGTH_SEL_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_DRIVER_STRENGTH_SEL_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_DRIVER_STRENGTH_SEL_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE7_DRIVER_STRENGTH_SEL_VAL_TYPE_B            (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_DRIVER_STRENGTH_SEL_VAL_TYPE_A            (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_DRIVER_STRENGTH_SEL_VAL_TYPE_C            (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE7_DRIVER_STRENGTH_SEL_VAL_TYPE_D            (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE7_RESETVAL                                  (0x0002U)

/* PRESET_VALUE8 */

#define CSL_MMC_CTLCFG_PRESET_VALUE8_SDCLK_FRQSEL_MASK                         (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_SDCLK_FRQSEL_SHIFT                        (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_SDCLK_FRQSEL_RESETVAL                     (0x0001U)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_SDCLK_FRQSEL_MAX                          (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE8_CLOCK_GENSEL_MASK                         (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_CLOCK_GENSEL_SHIFT                        (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_CLOCK_GENSEL_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_CLOCK_GENSEL_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE8_DRIVER_STRENGTH_SEL_MASK                  (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_DRIVER_STRENGTH_SEL_SHIFT                 (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_DRIVER_STRENGTH_SEL_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_DRIVER_STRENGTH_SEL_MAX                   (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE8_DRIVER_STRENGTH_SEL_VAL_TYPE_B            (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_DRIVER_STRENGTH_SEL_VAL_TYPE_A            (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_DRIVER_STRENGTH_SEL_VAL_TYPE_C            (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE8_DRIVER_STRENGTH_SEL_VAL_TYPE_D            (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE8_RESETVAL                                  (0x0001U)

/* PRESET_VALUE10 */

#define CSL_MMC_CTLCFG_PRESET_VALUE10_SDCLK_FRQSEL_MASK                        (0x03FFU)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_SDCLK_FRQSEL_SHIFT                       (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_SDCLK_FRQSEL_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_SDCLK_FRQSEL_MAX                         (0x03FFU)

#define CSL_MMC_CTLCFG_PRESET_VALUE10_CLOCK_GENSEL_MASK                        (0x0400U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_CLOCK_GENSEL_SHIFT                       (0x000AU)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_CLOCK_GENSEL_RESETVAL                    (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_CLOCK_GENSEL_MAX                         (0x0001U)

#define CSL_MMC_CTLCFG_PRESET_VALUE10_DRIVER_STRENGTH_SEL_MASK                 (0xC000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_DRIVER_STRENGTH_SEL_SHIFT                (0x000EU)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_DRIVER_STRENGTH_SEL_RESETVAL             (0x0000U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_DRIVER_STRENGTH_SEL_MAX                  (0x0003U)

#define CSL_MMC_CTLCFG_PRESET_VALUE10_DRIVER_STRENGTH_SEL_VAL_TYPE_B           (0x0U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_DRIVER_STRENGTH_SEL_VAL_TYPE_A           (0x1U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_DRIVER_STRENGTH_SEL_VAL_TYPE_C           (0x2U)
#define CSL_MMC_CTLCFG_PRESET_VALUE10_DRIVER_STRENGTH_SEL_VAL_TYPE_D           (0x3U)

#define CSL_MMC_CTLCFG_PRESET_VALUE10_RESETVAL                                 (0x0000U)

/* ADMA3_DESC_ADDRESS */

#define CSL_MMC_CTLCFG_ADMA3_DESC_ADDRESS_INTG_DESC_ADDR_MASK                  (0xFFFFFFFFFFFFFFFFU)
#define CSL_MMC_CTLCFG_ADMA3_DESC_ADDRESS_INTG_DESC_ADDR_SHIFT                 (0x0000000000000000U)
#define CSL_MMC_CTLCFG_ADMA3_DESC_ADDRESS_INTG_DESC_ADDR_RESETVAL              (0x0000000000000000U)
#define CSL_MMC_CTLCFG_ADMA3_DESC_ADDRESS_INTG_DESC_ADDR_MAX                   (0xFFFFFFFFFFFFFFFFU)

#define CSL_MMC_CTLCFG_ADMA3_DESC_ADDRESS_RESETVAL                             (0x0000000000000000U)

/* UHS2_BLOCK_SIZE */

#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_XFER_BLK_SIZE_MASK                      (0x0FFFU)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_XFER_BLK_SIZE_SHIFT                     (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_XFER_BLK_SIZE_RESETVAL                  (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_XFER_BLK_SIZE_MAX                       (0x0FFFU)

#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_XFER_BLK_SIZE_VAL_NO_DATA_XFER          (0x0U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_XFER_BLK_SIZE_VAL_XFER_1B               (0x1U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_XFER_BLK_SIZE_VAL_XFER_2B               (0x2U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_XFER_BLK_SIZE_VAL_XFER_512B             (0x200U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_XFER_BLK_SIZE_VAL_XFER_2048B            (0x800U)

#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_MASK                  (0x7000U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_SHIFT                 (0x000CU)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_RESETVAL              (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_MAX                   (0x0007U)

#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_VAL_BOUND_4KB         (0x0U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_VAL_BOUND_8KB         (0x1U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_VAL_BOUND_16KB        (0x2U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_VAL_BOUND_32KB        (0x3U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_VAL_BOUND_64KB        (0x4U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_VAL_BOUND_128KB       (0x5U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_VAL_BOUND_256KB       (0x6U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_SDMA_BUF_BOUNDARY_VAL_BOUND_512KB       (0x7U)

#define CSL_MMC_CTLCFG_UHS2_BLOCK_SIZE_RESETVAL                                (0x0000U)

/* UHS2_BLOCK_COUNT */

#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_XFER_BLK_COUNT_MASK                    (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_XFER_BLK_COUNT_SHIFT                   (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_XFER_BLK_COUNT_RESETVAL                (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_XFER_BLK_COUNT_MAX                     (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_XFER_BLK_COUNT_VAL_STOP_COUNT          (0x0U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_XFER_BLK_COUNT_VAL_BLK_1               (0x1U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_XFER_BLK_COUNT_VAL_BLKS_2              (0x2U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_XFER_BLK_COUNT_VAL_BLKS_3              (0x3U)
#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_XFER_BLK_COUNT_VAL_BLKS_4G_1           (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_UHS2_BLOCK_COUNT_RESETVAL                               (0x00000000U)

/* UHS2_COMMAND_PKT */

#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT_CMD_PKT_BYTE_MASK                      (0xFFU)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT_CMD_PKT_BYTE_SHIFT                     (0x00U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT_CMD_PKT_BYTE_RESETVAL                  (0x00U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT_CMD_PKT_BYTE_MAX                       (0xFFU)

#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT_RESETVAL                               (0x00U)

/* UHS2_XFER_MODE */

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DMA_ENA_MASK                             (0x0001U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DMA_ENA_SHIFT                            (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DMA_ENA_RESETVAL                         (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DMA_ENA_MAX                              (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DMA_ENA_VAL_DISABLE                      (0x0U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DMA_ENA_VAL_ENABLE                       (0x1U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BLK_CNT_ENA_MASK                         (0x0002U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BLK_CNT_ENA_SHIFT                        (0x0001U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BLK_CNT_ENA_RESETVAL                     (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BLK_CNT_ENA_MAX                          (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BLK_CNT_ENA_VAL_DISABLE                  (0x0U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BLK_CNT_ENA_VAL_ENABLE                   (0x1U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DATA_XFER_DIR_MASK                       (0x0010U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DATA_XFER_DIR_SHIFT                      (0x0004U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DATA_XFER_DIR_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DATA_XFER_DIR_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DATA_XFER_DIR_VAL_WRITE                  (0x1U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DATA_XFER_DIR_VAL_READ                   (0x0U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BYTE_MODE_MASK                           (0x0020U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BYTE_MODE_SHIFT                          (0x0005U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BYTE_MODE_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BYTE_MODE_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BYTE_MODE_VAL_BLOCK_MODE                 (0x0U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_BYTE_MODE_VAL_BYTE_MODE                  (0x1U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_TYPE_MASK                           (0x0040U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_TYPE_SHIFT                          (0x0006U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_TYPE_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_TYPE_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_TYPE_VAL_R1                         (0x0U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_TYPE_VAL_R5                         (0x1U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_ERR_CHK_ENA_MASK                    (0x0080U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_ERR_CHK_ENA_SHIFT                   (0x0007U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_ERR_CHK_ENA_RESETVAL                (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_ERR_CHK_ENA_MAX                     (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_ERR_CHK_ENA_VAL_DISABLE             (0x0U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_ERR_CHK_ENA_VAL_ENABLE              (0x1U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_INTR_DIS_MASK                       (0x0100U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_INTR_DIS_SHIFT                      (0x0008U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_INTR_DIS_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_INTR_DIS_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_INTR_DIS_VAL_DISABLE                (0x1U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESP_INTR_DIS_VAL_ENABLE                 (0x0U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_EBSY_WAIT_MASK                           (0x4000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_EBSY_WAIT_SHIFT                          (0x000EU)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_EBSY_WAIT_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_EBSY_WAIT_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DUPLEX_SELECT_MASK                       (0x8000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DUPLEX_SELECT_SHIFT                      (0x000FU)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DUPLEX_SELECT_RESETVAL                   (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DUPLEX_SELECT_MAX                        (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DUPLEX_SELECT_VAL_HALF_DUPLEX            (0x1U)
#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_DUPLEX_SELECT_VAL_FULL_DUPLEX            (0x0U)

#define CSL_MMC_CTLCFG_UHS2_XFER_MODE_RESETVAL                                 (0x0000U)

/* UHS2_COMMAND */

#define CSL_MMC_CTLCFG_UHS2_COMMAND_SUB_COMMAND_MASK                           (0x0004U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_SUB_COMMAND_SHIFT                          (0x0002U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_SUB_COMMAND_RESETVAL                       (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_SUB_COMMAND_MAX                            (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_COMMAND_SUB_COMMAND_VAL_MAIN_CMD                   (0x0U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_SUB_COMMAND_VAL_SUB_CMD                    (0x1U)

#define CSL_MMC_CTLCFG_UHS2_COMMAND_DATA_PRESENT_MASK                          (0x0020U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_DATA_PRESENT_SHIFT                         (0x0005U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_DATA_PRESENT_RESETVAL                      (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_DATA_PRESENT_MAX                           (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_COMMAND_DATA_PRESENT_VAL_NO_DATA                   (0x0U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_DATA_PRESENT_VAL_DATA_PRESENT              (0x1U)

#define CSL_MMC_CTLCFG_UHS2_COMMAND_CMD_TYPE_MASK                              (0x00C0U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_CMD_TYPE_SHIFT                             (0x0006U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_CMD_TYPE_RESETVAL                          (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_CMD_TYPE_MAX                               (0x0003U)

#define CSL_MMC_CTLCFG_UHS2_COMMAND_CMD_TYPE_VAL_NORMAL                        (0x0U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_CMD_TYPE_VAL_TRANS_ABORT                   (0x1U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_CMD_TYPE_VAL_ABORT                         (0x2U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_CMD_TYPE_VAL_GO_DORMANT                    (0x3U)

#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT_LENGTH_MASK                            (0x1F00U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT_LENGTH_SHIFT                           (0x0008U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT_LENGTH_RESETVAL                        (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_COMMAND_PKT_LENGTH_MAX                             (0x001FU)

#define CSL_MMC_CTLCFG_UHS2_COMMAND_RESETVAL                                   (0x0000U)

/* UHS2_RESPONSE */

#define CSL_MMC_CTLCFG_UHS2_RESPONSE_RESP_PKT_BYTE_MASK                        (0xFFU)
#define CSL_MMC_CTLCFG_UHS2_RESPONSE_RESP_PKT_BYTE_SHIFT                       (0x00U)
#define CSL_MMC_CTLCFG_UHS2_RESPONSE_RESP_PKT_BYTE_RESETVAL                    (0x00U)
#define CSL_MMC_CTLCFG_UHS2_RESPONSE_RESP_PKT_BYTE_MAX                         (0xFFU)

#define CSL_MMC_CTLCFG_UHS2_RESPONSE_RESETVAL                                  (0x00U)

/* UHS2_MESSAGE_SELECT */

#define CSL_MMC_CTLCFG_UHS2_MESSAGE_SELECT_MSG_SEL_MASK                        (0x03U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_SELECT_MSG_SEL_SHIFT                       (0x00U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_SELECT_MSG_SEL_RESETVAL                    (0x00U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_SELECT_MSG_SEL_MAX                         (0x03U)

#define CSL_MMC_CTLCFG_UHS2_MESSAGE_SELECT_RESETVAL                            (0x00U)

/* UHS2_MESSAGE */

#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE0_MASK                             (0x000000FFU)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE0_SHIFT                            (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE0_RESETVAL                         (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE0_MAX                              (0x000000FFU)

#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE1_MASK                             (0x0000FF00U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE1_SHIFT                            (0x00000008U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE1_RESETVAL                         (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE1_MAX                              (0x000000FFU)

#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE2_MASK                             (0x00FF0000U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE2_SHIFT                            (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE2_RESETVAL                         (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE2_MAX                              (0x000000FFU)

#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE3_MASK                             (0xFF000000U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE3_SHIFT                            (0x00000018U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE3_RESETVAL                         (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_MESSAGE_MSG_BYTE3_MAX                              (0x000000FFU)

#define CSL_MMC_CTLCFG_UHS2_MESSAGE_RESETVAL                                   (0x00000000U)

/* UHS2_DEVICE_INTR_STATUS */

#define CSL_MMC_CTLCFG_UHS2_DEVICE_INTR_STATUS_DEV_INT_STS_MASK                (0xFFFFU)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_INTR_STATUS_DEV_INT_STS_SHIFT               (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_INTR_STATUS_DEV_INT_STS_RESETVAL            (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_INTR_STATUS_DEV_INT_STS_MAX                 (0xFFFFU)

#define CSL_MMC_CTLCFG_UHS2_DEVICE_INTR_STATUS_RESETVAL                        (0x0000U)

/* UHS2_DEVICE_SELECT */

#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT_DEV_SEL_MASK                         (0x0FU)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT_DEV_SEL_SHIFT                        (0x00U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT_DEV_SEL_RESETVAL                     (0x00U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT_DEV_SEL_MAX                          (0x0FU)

#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT_INT_MSG_ENA_MASK                     (0x80U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT_INT_MSG_ENA_SHIFT                    (0x07U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT_INT_MSG_ENA_RESETVAL                 (0x00U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT_INT_MSG_ENA_MAX                      (0x01U)

#define CSL_MMC_CTLCFG_UHS2_DEVICE_SELECT_RESETVAL                             (0x00U)

/* UHS2_DEVICE_INT_CODE */

#define CSL_MMC_CTLCFG_UHS2_DEVICE_INT_CODE_DEV_INTR_MASK                      (0xFFU)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_INT_CODE_DEV_INTR_SHIFT                     (0x00U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_INT_CODE_DEV_INTR_RESETVAL                  (0x00U)
#define CSL_MMC_CTLCFG_UHS2_DEVICE_INT_CODE_DEV_INTR_MAX                       (0xFFU)

#define CSL_MMC_CTLCFG_UHS2_DEVICE_INT_CODE_RESETVAL                           (0x00U)

/* UHS2_SOFTWARE_RESET */

#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_FULL_RESET_MASK                (0x0001U)
#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_FULL_RESET_SHIFT               (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_FULL_RESET_RESETVAL            (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_FULL_RESET_MAX                 (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_FULL_RESET_VAL_WORK            (0x0U)
#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_FULL_RESET_VAL_RESET           (0x1U)

#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_SDTRAN_RESET_MASK              (0x0002U)
#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_SDTRAN_RESET_SHIFT             (0x0001U)
#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_SDTRAN_RESET_RESETVAL          (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_SDTRAN_RESET_MAX               (0x0001U)

#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_SDTRAN_RESET_VAL_WORK          (0x0U)
#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_HOST_SDTRAN_RESET_VAL_RESET         (0x1U)

#define CSL_MMC_CTLCFG_UHS2_SOFTWARE_RESET_RESETVAL                            (0x0000U)

/* UHS2_TIMER_CONTROL */

#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL_CMDRESP_TIMEOUT_CTR_MASK             (0x000FU)
#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL_CMDRESP_TIMEOUT_CTR_SHIFT            (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL_CMDRESP_TIMEOUT_CTR_RESETVAL         (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL_CMDRESP_TIMEOUT_CTR_MAX              (0x000FU)

#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL_DEADLOCK_TIMEOUT_CTR_MASK            (0x00F0U)
#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL_DEADLOCK_TIMEOUT_CTR_SHIFT           (0x0004U)
#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL_DEADLOCK_TIMEOUT_CTR_RESETVAL        (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL_DEADLOCK_TIMEOUT_CTR_MAX             (0x000FU)

#define CSL_MMC_CTLCFG_UHS2_TIMER_CONTROL_RESETVAL                             (0x0000U)

/* UHS2_ERR_INTR_STS */

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_HEADER_MASK                           (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_HEADER_SHIFT                          (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_HEADER_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_HEADER_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_HEADER_VAL_NO_ERR                     (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_HEADER_VAL_ERROR                      (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RESP_PKT_MASK                         (0x00000002U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RESP_PKT_SHIFT                        (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RESP_PKT_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RESP_PKT_MAX                          (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RESP_PKT_VAL_NO_ERR                   (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RESP_PKT_VAL_ERROR                    (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RETRY_EXPIRED_MASK                    (0x00000004U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RETRY_EXPIRED_SHIFT                   (0x00000002U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RETRY_EXPIRED_RESETVAL                (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RETRY_EXPIRED_MAX                     (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RETRY_EXPIRED_VAL_NO_ERR              (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RETRY_EXPIRED_VAL_ERROR               (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CRC_MASK                              (0x00000008U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CRC_SHIFT                             (0x00000003U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CRC_RESETVAL                          (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CRC_MAX                               (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CRC_VAL_NO_ERR                        (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CRC_VAL_ERROR                         (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_FRAMING_MASK                          (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_FRAMING_SHIFT                         (0x00000004U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_FRAMING_RESETVAL                      (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_FRAMING_MAX                           (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_FRAMING_VAL_NO_ERR                    (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_FRAMING_VAL_ERROR                     (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_TID_MASK                              (0x00000020U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_TID_SHIFT                             (0x00000005U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_TID_RESETVAL                          (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_TID_MAX                               (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_TID_VAL_NO_ERR                        (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_TID_VAL_ERROR                         (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_UNRECOVERABLE_MASK                    (0x00000080U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_UNRECOVERABLE_SHIFT                   (0x00000007U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_UNRECOVERABLE_RESETVAL                (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_UNRECOVERABLE_MAX                     (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_UNRECOVERABLE_VAL_NO_ERR              (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_UNRECOVERABLE_VAL_ERROR               (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_EBSY_MASK                             (0x00000100U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_EBSY_SHIFT                            (0x00000008U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_EBSY_RESETVAL                         (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_EBSY_MAX                              (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_EBSY_VAL_NO_ERR                       (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_EBSY_VAL_ERROR                        (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ADMA2_ADMA3_MASK                      (0x00008000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ADMA2_ADMA3_SHIFT                     (0x0000000FU)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ADMA2_ADMA3_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ADMA2_ADMA3_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ADMA2_ADMA3_VAL_NO_ERR                (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ADMA2_ADMA3_VAL_ERROR                 (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CMD_RESP_TIMEOUT_MASK                 (0x00010000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CMD_RESP_TIMEOUT_SHIFT                (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CMD_RESP_TIMEOUT_RESETVAL             (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CMD_RESP_TIMEOUT_MAX                  (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CMD_RESP_TIMEOUT_VAL_NO_ERR           (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_CMD_RESP_TIMEOUT_VAL_ERROR            (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_DEADLOCK_TIMEOUT_MASK                 (0x00020000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_DEADLOCK_TIMEOUT_SHIFT                (0x00000011U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_DEADLOCK_TIMEOUT_RESETVAL             (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_DEADLOCK_TIMEOUT_MAX                  (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_DEADLOCK_TIMEOUT_VAL_NO_ERR           (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_DEADLOCK_TIMEOUT_VAL_ERROR            (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_VENDOR_SPECFIC_ERR_MASK               (0xF8000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_VENDOR_SPECFIC_ERR_SHIFT              (0x0000001BU)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_VENDOR_SPECFIC_ERR_RESETVAL           (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_VENDOR_SPECFIC_ERR_MAX                (0x0000001FU)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_RESETVAL                              (0x00000000U)

/* UHS2_ERR_INTR_STS_ENA */

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_HEADER_MASK                       (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_HEADER_SHIFT                      (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_HEADER_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_HEADER_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_HEADER_VAL_MASK                   (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_HEADER_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RESP_PKT_MASK                     (0x00000002U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RESP_PKT_SHIFT                    (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RESP_PKT_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RESP_PKT_MAX                      (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RESP_PKT_VAL_MASK                 (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RESP_PKT_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RETRY_EXPIRED_MASK                (0x00000004U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RETRY_EXPIRED_SHIFT               (0x00000002U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RETRY_EXPIRED_RESETVAL            (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RETRY_EXPIRED_MAX                 (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RETRY_EXPIRED_VAL_MASK            (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RETRY_EXPIRED_VAL_ENABLE          (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CRC_MASK                          (0x00000008U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CRC_SHIFT                         (0x00000003U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CRC_RESETVAL                      (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CRC_MAX                           (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CRC_VAL_MASK                      (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CRC_VAL_ENABLE                    (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_FRAMING_MASK                      (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_FRAMING_SHIFT                     (0x00000004U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_FRAMING_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_FRAMING_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_FRAMING_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_FRAMING_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_TID_MASK                          (0x00000020U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_TID_SHIFT                         (0x00000005U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_TID_RESETVAL                      (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_TID_MAX                           (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_TID_VAL_MASK                      (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_TID_VAL_ENABLE                    (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_UNRECOVERABLE_MASK                (0x00000080U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_UNRECOVERABLE_SHIFT               (0x00000007U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_UNRECOVERABLE_RESETVAL            (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_UNRECOVERABLE_MAX                 (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_UNRECOVERABLE_VAL_MASK            (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_UNRECOVERABLE_VAL_ENABLE          (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_EBSY_MASK                         (0x00000100U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_EBSY_SHIFT                        (0x00000008U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_EBSY_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_EBSY_MAX                          (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_EBSY_VAL_MASK                     (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_EBSY_VAL_ENABLE                   (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_ADMA2_ADMA3_MASK                  (0x00008000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_ADMA2_ADMA3_SHIFT                 (0x0000000FU)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_ADMA2_ADMA3_RESETVAL              (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_ADMA2_ADMA3_MAX                   (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_ADMA2_ADMA3_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_ADMA2_ADMA3_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CMD_RESP_TIMEOUT_MASK             (0x00010000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CMD_RESP_TIMEOUT_SHIFT            (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CMD_RESP_TIMEOUT_RESETVAL         (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CMD_RESP_TIMEOUT_MAX              (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CMD_RESP_TIMEOUT_VAL_MASK         (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_CMD_RESP_TIMEOUT_VAL_ENABLE       (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_DEADLOCK_TIMEOUT_MASK             (0x00020000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_DEADLOCK_TIMEOUT_SHIFT            (0x00000011U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_DEADLOCK_TIMEOUT_RESETVAL         (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_DEADLOCK_TIMEOUT_MAX              (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_DEADLOCK_TIMEOUT_VAL_MASK         (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_DEADLOCK_TIMEOUT_VAL_ENABLE       (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_VENDOR_SPECFIC_MASK               (0xF8000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_VENDOR_SPECFIC_SHIFT              (0x0000001BU)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_VENDOR_SPECFIC_RESETVAL           (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_VENDOR_SPECFIC_MAX                (0x0000001FU)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_STS_ENA_RESETVAL                          (0x00000000U)

/* UHS2_ERR_INTR_SIG_ENA */

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_HEADER_MASK                       (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_HEADER_SHIFT                      (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_HEADER_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_HEADER_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_HEADER_VAL_MASK                   (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_HEADER_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RESP_PKT_MASK                     (0x00000002U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RESP_PKT_SHIFT                    (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RESP_PKT_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RESP_PKT_MAX                      (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RESP_PKT_VAL_MASK                 (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RESP_PKT_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RETRY_EXPIRED_SIG_ENA_MASK        (0x00000004U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RETRY_EXPIRED_SIG_ENA_SHIFT       (0x00000002U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RETRY_EXPIRED_SIG_ENA_RESETVAL    (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RETRY_EXPIRED_SIG_ENA_MAX         (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RETRY_EXPIRED_SIG_ENA_VAL_MASK    (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RETRY_EXPIRED_SIG_ENA_VAL_ENABLE  (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CRC_MASK                          (0x00000008U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CRC_SHIFT                         (0x00000003U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CRC_RESETVAL                      (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CRC_MAX                           (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CRC_VAL_MASK                      (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CRC_VAL_ENABLE                    (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_FRAMING_MASK                      (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_FRAMING_SHIFT                     (0x00000004U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_FRAMING_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_FRAMING_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_FRAMING_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_FRAMING_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_TID_MASK                          (0x00000020U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_TID_SHIFT                         (0x00000005U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_TID_RESETVAL                      (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_TID_MAX                           (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_TID_VAL_MASK                      (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_TID_VAL_ENABLE                    (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_UNRECOVERABLE_MASK                (0x00000080U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_UNRECOVERABLE_SHIFT               (0x00000007U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_UNRECOVERABLE_RESETVAL            (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_UNRECOVERABLE_MAX                 (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_UNRECOVERABLE_VAL_MASK            (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_UNRECOVERABLE_VAL_ENABLE          (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_EBSY_MASK                         (0x00000100U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_EBSY_SHIFT                        (0x00000008U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_EBSY_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_EBSY_MAX                          (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_EBSY_VAL_MASK                     (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_EBSY_VAL_ENABLE                   (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_ADMA2_ADMA3_MASK                  (0x00008000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_ADMA2_ADMA3_SHIFT                 (0x0000000FU)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_ADMA2_ADMA3_RESETVAL              (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_ADMA2_ADMA3_MAX                   (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_ADMA2_ADMA3_VAL_MASK              (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_ADMA2_ADMA3_VAL_ENABLE            (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CMD_RESP_TIMEOUT_MASK             (0x00010000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CMD_RESP_TIMEOUT_SHIFT            (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CMD_RESP_TIMEOUT_RESETVAL         (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CMD_RESP_TIMEOUT_MAX              (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CMD_RESP_TIMEOUT_VAL_MASK         (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_CMD_RESP_TIMEOUT_VAL_ENABLE       (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_DEADLOCK_TIMEOUT_MASK             (0x00020000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_DEADLOCK_TIMEOUT_SHIFT            (0x00000011U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_DEADLOCK_TIMEOUT_RESETVAL         (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_DEADLOCK_TIMEOUT_MAX              (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_DEADLOCK_TIMEOUT_VAL_MASK         (0x0U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_DEADLOCK_TIMEOUT_VAL_ENABLE       (0x1U)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_VENDOR_SPECFIC_MASK               (0xF8000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_VENDOR_SPECFIC_SHIFT              (0x0000001BU)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_VENDOR_SPECFIC_RESETVAL           (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_VENDOR_SPECFIC_MAX                (0x0000001FU)

#define CSL_MMC_CTLCFG_UHS2_ERR_INTR_SIG_ENA_RESETVAL                          (0x00000000U)

/* UHS2_SETTINGS_PTR */

#define CSL_MMC_CTLCFG_UHS2_SETTINGS_PTR_UHS2_SETTINGS_PTR_MASK                (0xFFFFU)
#define CSL_MMC_CTLCFG_UHS2_SETTINGS_PTR_UHS2_SETTINGS_PTR_SHIFT               (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_SETTINGS_PTR_UHS2_SETTINGS_PTR_RESETVAL            (0x0100U)
#define CSL_MMC_CTLCFG_UHS2_SETTINGS_PTR_UHS2_SETTINGS_PTR_MAX                 (0xFFFFU)

#define CSL_MMC_CTLCFG_UHS2_SETTINGS_PTR_RESETVAL                              (0x0100U)

/* UHS2_CAPABILITIES_PTR */

#define CSL_MMC_CTLCFG_UHS2_CAPABILITIES_PTR_UHS2_CAPABILITIES_PTR_MASK        (0xFFFFU)
#define CSL_MMC_CTLCFG_UHS2_CAPABILITIES_PTR_UHS2_CAPABILITIES_PTR_SHIFT       (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_CAPABILITIES_PTR_UHS2_CAPABILITIES_PTR_RESETVAL    (0x0110U)
#define CSL_MMC_CTLCFG_UHS2_CAPABILITIES_PTR_UHS2_CAPABILITIES_PTR_MAX         (0xFFFFU)

#define CSL_MMC_CTLCFG_UHS2_CAPABILITIES_PTR_RESETVAL                          (0x0110U)

/* UHS2_TEST_PTR */

#define CSL_MMC_CTLCFG_UHS2_TEST_PTR_UHS2_TEST_PTR_MASK                        (0xFFFFU)
#define CSL_MMC_CTLCFG_UHS2_TEST_PTR_UHS2_TEST_PTR_SHIFT                       (0x0000U)
#define CSL_MMC_CTLCFG_UHS2_TEST_PTR_UHS2_TEST_PTR_RESETVAL                    (0x0120U)
#define CSL_MMC_CTLCFG_UHS2_TEST_PTR_UHS2_TEST_PTR_MAX                         (0xFFFFU)

#define CSL_MMC_CTLCFG_UHS2_TEST_PTR_RESETVAL                                  (0x0120U)

/* SHARED_BUS_CTRL_PTR */

#define CSL_MMC_CTLCFG_SHARED_BUS_CTRL_PTR_SHARED_BUS_CTRL_PTR_MASK            (0xFFFFU)
#define CSL_MMC_CTLCFG_SHARED_BUS_CTRL_PTR_SHARED_BUS_CTRL_PTR_SHIFT           (0x0000U)
#define CSL_MMC_CTLCFG_SHARED_BUS_CTRL_PTR_SHARED_BUS_CTRL_PTR_RESETVAL        (0x0130U)
#define CSL_MMC_CTLCFG_SHARED_BUS_CTRL_PTR_SHARED_BUS_CTRL_PTR_MAX             (0xFFFFU)

#define CSL_MMC_CTLCFG_SHARED_BUS_CTRL_PTR_RESETVAL                            (0x0130U)

/* VENDOR_SPECFIC_PTR */

#define CSL_MMC_CTLCFG_VENDOR_SPECFIC_PTR_VENDOR_SPECFIC_PTR_MASK              (0xFFFFU)
#define CSL_MMC_CTLCFG_VENDOR_SPECFIC_PTR_VENDOR_SPECFIC_PTR_SHIFT             (0x0000U)
#define CSL_MMC_CTLCFG_VENDOR_SPECFIC_PTR_VENDOR_SPECFIC_PTR_RESETVAL          (0x0140U)
#define CSL_MMC_CTLCFG_VENDOR_SPECFIC_PTR_VENDOR_SPECFIC_PTR_MAX               (0xFFFFU)

#define CSL_MMC_CTLCFG_VENDOR_SPECFIC_PTR_RESETVAL                             (0x0140U)

/* BOOT_TIMEOUT_CONTROL */

#define CSL_MMC_CTLCFG_BOOT_TIMEOUT_CONTROL_DATA_TIMEOUT_CNT_MASK              (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_BOOT_TIMEOUT_CONTROL_DATA_TIMEOUT_CNT_SHIFT             (0x00000000U)
#define CSL_MMC_CTLCFG_BOOT_TIMEOUT_CONTROL_DATA_TIMEOUT_CNT_RESETVAL          (0x00000000U)
#define CSL_MMC_CTLCFG_BOOT_TIMEOUT_CONTROL_DATA_TIMEOUT_CNT_MAX               (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_BOOT_TIMEOUT_CONTROL_RESETVAL                           (0x00000000U)

/* VENDOR_REGISTER */

#define CSL_MMC_CTLCFG_VENDOR_REGISTER_ENHANCED_STROBE_MASK                    (0x00000001U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_ENHANCED_STROBE_SHIFT                   (0x00000000U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_ENHANCED_STROBE_RESETVAL                (0x00000000U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_ENHANCED_STROBE_MAX                     (0x00000001U)

#define CSL_MMC_CTLCFG_VENDOR_REGISTER_ENHANCED_STROBE_VAL_DISABLE             (0x0U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_ENHANCED_STROBE_VAL_ENABLE              (0x1U)

#define CSL_MMC_CTLCFG_VENDOR_REGISTER_EMMC_HW_RESET_MASK                      (0x00000002U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_EMMC_HW_RESET_SHIFT                     (0x00000001U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_EMMC_HW_RESET_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_EMMC_HW_RESET_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_VENDOR_REGISTER_EMMC_HW_RESET_VAL_DEASSERT              (0x0U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_EMMC_HW_RESET_VAL_ASSERT                (0x1U)

#define CSL_MMC_CTLCFG_VENDOR_REGISTER_CMD11_PD_TIMER_MASK                     (0x0000FFFCU)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_CMD11_PD_TIMER_SHIFT                    (0x00000002U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_CMD11_PD_TIMER_RESETVAL                 (0x00001388U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_CMD11_PD_TIMER_MAX                      (0x00003FFFU)

#define CSL_MMC_CTLCFG_VENDOR_REGISTER_AUTOGATE_SDCLK_MASK                     (0x00010000U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_AUTOGATE_SDCLK_SHIFT                    (0x00000010U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_AUTOGATE_SDCLK_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_AUTOGATE_SDCLK_MAX                      (0x00000001U)

#define CSL_MMC_CTLCFG_VENDOR_REGISTER_AUTOGATE_SDCLK_VAL_DISABLE              (0x0U)
#define CSL_MMC_CTLCFG_VENDOR_REGISTER_AUTOGATE_SDCLK_VAL_ENABLE               (0x1U)

#define CSL_MMC_CTLCFG_VENDOR_REGISTER_RESETVAL                                (0x00004E20U)

/* SLOT_INT_STS */

#define CSL_MMC_CTLCFG_SLOT_INT_STS_INTR_SIG_MASK                              (0x00FFU)
#define CSL_MMC_CTLCFG_SLOT_INT_STS_INTR_SIG_SHIFT                             (0x0000U)
#define CSL_MMC_CTLCFG_SLOT_INT_STS_INTR_SIG_RESETVAL                          (0x0000U)
#define CSL_MMC_CTLCFG_SLOT_INT_STS_INTR_SIG_MAX                               (0x00FFU)

#define CSL_MMC_CTLCFG_SLOT_INT_STS_RESETVAL                                   (0x0000U)

/* HOST_CONTROLLER_VER */

#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_SPEC_VER_NUM_MASK                   (0x00FFU)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_SPEC_VER_NUM_SHIFT                  (0x0000U)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_SPEC_VER_NUM_RESETVAL               (0x0004U)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_SPEC_VER_NUM_MAX                    (0x00FFU)

#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_SPEC_VER_NUM_VAL_VER1P0             (0x0U)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_SPEC_VER_NUM_VAL_VER2P0             (0x1U)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_SPEC_VER_NUM_VAL_VER3P0             (0x2U)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_SPEC_VER_NUM_VAL_VER4P0             (0x3U)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_SPEC_VER_NUM_VAL_VER4P1             (0x4U)

#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_VEN_VER_NUM_MASK                    (0xFF00U)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_VEN_VER_NUM_SHIFT                   (0x0008U)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_VEN_VER_NUM_RESETVAL                (0x0010U)
#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_VEN_VER_NUM_MAX                     (0x00FFU)

#define CSL_MMC_CTLCFG_HOST_CONTROLLER_VER_RESETVAL                            (0x1004U)

/* UHS2_GEN_SETTINGS */

#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_POWER_MODE_MASK                       (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_POWER_MODE_SHIFT                      (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_POWER_MODE_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_POWER_MODE_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_POWER_MODE_VAL_FAST_MODE              (0x0U)
#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_POWER_MODE_VAL_LP_MODE                (0x1U)

#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_NUMLANES_MASK                         (0x00003F00U)
#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_NUMLANES_SHIFT                        (0x00000008U)
#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_NUMLANES_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_NUMLANES_MAX                          (0x0000003FU)

#define CSL_MMC_CTLCFG_UHS2_GEN_SETTINGS_RESETVAL                              (0x00000000U)

/* UHS2_PHY_SETTINGS */

#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_SPEED_RANGE_MASK                      (0x000000C0U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_SPEED_RANGE_SHIFT                     (0x00000006U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_SPEED_RANGE_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_SPEED_RANGE_MAX                       (0x00000003U)

#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_SPEED_RANGE_VAL_RANGEA                (0x0U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_SPEED_RANGE_VAL_RANGEB                (0x1U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_SPEED_RANGE_VAL_RSVD2                 (0x2U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_SPEED_RANGE_VAL_RSVD3                 (0x3U)

#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_HIBERNATE_ENA_MASK                    (0x00008000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_HIBERNATE_ENA_SHIFT                   (0x0000000FU)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_HIBERNATE_ENA_RESETVAL                (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_HIBERNATE_ENA_MAX                     (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_HIBERNATE_ENA_VAL_DISABLE             (0x0U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_HIBERNATE_ENA_VAL_ENABLE              (0x1U)

#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_N_LSS_SYN_MASK                        (0x000F0000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_N_LSS_SYN_SHIFT                       (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_N_LSS_SYN_RESETVAL                    (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_N_LSS_SYN_MAX                         (0x0000000FU)

#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_N_LSS_DIR_MASK                        (0x00F00000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_N_LSS_DIR_SHIFT                       (0x00000014U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_N_LSS_DIR_RESETVAL                    (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_N_LSS_DIR_MAX                         (0x0000000FU)

#define CSL_MMC_CTLCFG_UHS2_PHY_SETTINGS_RESETVAL                              (0x00000000U)

/* UHS2_LNK_TRN_SETTINGS */

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_HOST_NFCU_MASK                    (0x000000000000FF00U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_HOST_NFCU_SHIFT                   (0x0000000000000008U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_HOST_NFCU_RESETVAL                (0x0000000000000000U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_HOST_NFCU_MAX                     (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_HOST_NFCU_VAL_BLK_256             (0x0U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_HOST_NFCU_VAL_BLK_1               (0x1U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_HOST_NFCU_VAL_BLKS_2              (0x2U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_HOST_NFCU_VAL_BLKS_3              (0x3U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_HOST_NFCU_VAL_BLKS_255            (0xFFU)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_RETRY_COUNT_MASK                  (0x0000000000030000U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_RETRY_COUNT_SHIFT                 (0x0000000000000010U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_RETRY_COUNT_RESETVAL              (0x0000000000000000U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_RETRY_COUNT_MAX                   (0x0000000000000003U)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_RETRY_COUNT_VAL_DISABLE           (0x0U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_RETRY_COUNT_VAL_RETRY_1           (0x1U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_RETRY_COUNT_VAL_RETRY_2           (0x2U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_RETRY_COUNT_VAL_RETRY_3           (0x3U)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_N_DATA_GAP_MASK                   (0x000000FF00000000U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_N_DATA_GAP_SHIFT                  (0x0000000000000020U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_N_DATA_GAP_RESETVAL               (0x0000000000000000U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_N_DATA_GAP_MAX                    (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_N_DATA_GAP_VAL_NO_GAP             (0x0U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_N_DATA_GAP_VAL_LSS1               (0x1U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_N_DATA_GAP_VAL_LSS2               (0x2U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_N_DATA_GAP_VAL_LSS3               (0x3U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_N_DATA_GAP_VAL_LSS255             (0xFFU)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_SETTINGS_RESETVAL                          (0x0000000000000000U)

/* UHS2_GEN_CAP */

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_DAP_MASK                                   (0x0000000FU)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_DAP_SHIFT                                  (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_DAP_RESETVAL                               (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_DAP_MAX                                    (0x0000000FU)

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_GAP_MASK                                   (0x000000F0U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_GAP_SHIFT                                  (0x00000004U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_GAP_RESETVAL                               (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_GAP_MAX                                    (0x0000000FU)

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_NUM_LANES_MASK                             (0x00003F00U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_NUM_LANES_SHIFT                            (0x00000008U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_NUM_LANES_RESETVAL                         (0x0000000FU)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_NUM_LANES_MAX                              (0x0000003FU)

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CFG_64BIT_ADDRESSING_MASK                  (0x00004000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CFG_64BIT_ADDRESSING_SHIFT                 (0x0000000EU)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CFG_64BIT_ADDRESSING_RESETVAL              (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CFG_64BIT_ADDRESSING_MAX                   (0x00000001U)

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_DEVICE_TYPE_MASK                           (0x00030000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_DEVICE_TYPE_SHIFT                          (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_DEVICE_TYPE_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_DEVICE_TYPE_MAX                            (0x00000003U)

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_MAX_DEVICES_MASK              (0x003C0000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_MAX_DEVICES_SHIFT             (0x00000012U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_MAX_DEVICES_RESETVAL          (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_MAX_DEVICES_MAX               (0x0000000FU)

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_MAX_DEVICES_VAL_RSVD          (0x0U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_MAX_DEVICES_VAL_DEV_1         (0x1U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_MAX_DEVICES_VAL_DEV_2         (0x2U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_MAX_DEVICES_VAL_DEV_15        (0xFU)

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_BUS_TOPLOGY_MASK              (0x00C00000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_BUS_TOPLOGY_SHIFT             (0x00000016U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_BUS_TOPLOGY_RESETVAL          (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_BUS_TOPLOGY_MAX               (0x00000003U)

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_BUS_TOPLOGY_VAL_P2P           (0x0U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_BUS_TOPLOGY_VAL_RING          (0x1U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_BUS_TOPLOGY_VAL_HUB           (0x2U)
#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_CORECFG_UHS2_BUS_TOPLOGY_VAL_HUB_RING      (0x3U)

#define CSL_MMC_CTLCFG_UHS2_GEN_CAP_RESETVAL                                   (0x00044F11U)

/* UHS2_PHY_CAP */

#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_SPEED_RANGE_MASK                           (0x000000C0U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_SPEED_RANGE_SHIFT                          (0x00000006U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_SPEED_RANGE_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_SPEED_RANGE_MAX                            (0x00000003U)

#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_SPEED_RANGE_VAL_RANGE_A                    (0x0U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_SPEED_RANGE_VAL_RANGE_AB                   (0x1U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_SPEED_RANGE_VAL_RSVD_2                     (0x2U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_SPEED_RANGE_VAL_RSVD_3                     (0x3U)

#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_N_LSS_SYN_MASK                             (0x000F0000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_N_LSS_SYN_SHIFT                            (0x00000010U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_N_LSS_SYN_RESETVAL                         (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_N_LSS_SYN_MAX                              (0x0000000FU)

#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_N_LSS_DIR_MASK                             (0x00F00000U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_N_LSS_DIR_SHIFT                            (0x00000014U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_N_LSS_DIR_RESETVAL                         (0x00000001U)
#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_N_LSS_DIR_MAX                              (0x0000000FU)

#define CSL_MMC_CTLCFG_UHS2_PHY_CAP_RESETVAL                                   (0x00110000U)

/* UHS2_LNK_TRN_CAP */

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_FCU_MASK                             (0x000000000000FF00U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_FCU_SHIFT                            (0x0000000000000008U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_FCU_RESETVAL                         (0x0000000000000001U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_FCU_MAX                              (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_FCU_VAL_BLK_256                      (0x0U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_FCU_VAL_BLK_1                        (0x1U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_FCU_VAL_BLKS_2                       (0x2U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_FCU_VAL_BLKS_3                       (0x3U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_FCU_VAL_BLKS_255                     (0xFFU)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_MAX_BLK_LENGTH_MASK                    (0x00000000FFF00000U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_MAX_BLK_LENGTH_SHIFT                   (0x0000000000000014U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_MAX_BLK_LENGTH_RESETVAL                (0x0000000000000200U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_MAX_BLK_LENGTH_MAX                     (0x0000000000000FFFU)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_DATA_GAP_MASK                        (0x000000FF00000000U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_DATA_GAP_SHIFT                       (0x0000000000000020U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_DATA_GAP_RESETVAL                    (0x0000000000000081U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_DATA_GAP_MAX                         (0x00000000000000FFU)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_DATA_GAP_VAL_NO_GAP                  (0x0U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_DATA_GAP_VAL_LSS1                    (0x1U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_DATA_GAP_VAL_LSS2                    (0x2U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_DATA_GAP_VAL_LSS3                    (0x3U)
#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_N_DATA_GAP_VAL_LSS255                  (0xFFU)

#define CSL_MMC_CTLCFG_UHS2_LNK_TRN_CAP_RESETVAL                               (0x0000008120000100U)

/* FORCE_UHSII_ERR_INT_STS */

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_HEADER_MASK                     (0x00000001U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_HEADER_SHIFT                    (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_HEADER_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_HEADER_MAX                      (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_HEADER_VAL_NO_INT               (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_HEADER_VAL_INT_SET              (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RES_PKT_MASK                    (0x00000002U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RES_PKT_SHIFT                   (0x00000001U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RES_PKT_RESETVAL                (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RES_PKT_MAX                     (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RES_PKT_VAL_NO_INT              (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RES_PKT_VAL_INT_SET             (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RETRY_EXPIRED_MASK              (0x00000004U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RETRY_EXPIRED_SHIFT             (0x00000002U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RETRY_EXPIRED_RESETVAL          (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RETRY_EXPIRED_MAX               (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RETRY_EXPIRED_VAL_NO_INT        (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RETRY_EXPIRED_VAL_INT_SET       (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_CRC_MASK                        (0x00000008U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_CRC_SHIFT                       (0x00000003U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_CRC_RESETVAL                    (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_CRC_MAX                         (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_CRC_VAL_NO_INT                  (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_CRC_VAL_INT_SET                 (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_FRAMING_MASK                    (0x00000010U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_FRAMING_SHIFT                   (0x00000004U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_FRAMING_RESETVAL                (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_FRAMING_MAX                     (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_FRAMING_VAL_NO_INT              (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_FRAMING_VAL_INT_SET             (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TID_MASK                        (0x00000020U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TID_SHIFT                       (0x00000005U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TID_RESETVAL                    (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TID_MAX                         (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TID_VAL_NO_INT                  (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TID_VAL_INT_SET                 (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_UNRECOVERABLE_MASK              (0x00000080U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_UNRECOVERABLE_SHIFT             (0x00000007U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_UNRECOVERABLE_RESETVAL          (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_UNRECOVERABLE_MAX               (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_UNRECOVERABLE_VAL_NO_INT        (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_UNRECOVERABLE_VAL_INT_SET       (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_EBSY_MASK                       (0x00000100U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_EBSY_SHIFT                      (0x00000008U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_EBSY_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_EBSY_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_EBSY_VAL_NO_INT                 (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_EBSY_VAL_INT_SET                (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_ADMA_MASK                       (0x00008000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_ADMA_SHIFT                      (0x0000000FU)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_ADMA_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_ADMA_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_ADMA_VAL_NO_INT                 (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_ADMA_VAL_INT_SET                (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_CMD_RES_MASK            (0x00010000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_CMD_RES_SHIFT           (0x00000010U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_CMD_RES_RESETVAL        (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_CMD_RES_MAX             (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_CMD_RES_VAL_NO_INT      (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_CMD_RES_VAL_INT_SET     (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_DEADLOCK_MASK           (0x00020000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_DEADLOCK_SHIFT          (0x00000011U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_DEADLOCK_RESETVAL       (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_DEADLOCK_MAX            (0x00000001U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_DEADLOCK_VAL_NO_INT     (0x0U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_TIMEOUT_DEADLOCK_VAL_INT_SET    (0x1U)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_VENDOR_SPECIFIC_MASK            (0xF8000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_VENDOR_SPECIFIC_SHIFT           (0x0000001BU)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_VENDOR_SPECIFIC_RESETVAL        (0x00000000U)
#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_VENDOR_SPECIFIC_MAX             (0x0000001FU)

#define CSL_MMC_CTLCFG_FORCE_UHSII_ERR_INT_STS_RESETVAL                        (0x00000000U)

/* CQ_VERSION */

#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_VERSION_SUFFIX_MASK                     (0x0000000FU)
#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_VERSION_SUFFIX_SHIFT                    (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_VERSION_SUFFIX_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_VERSION_SUFFIX_MAX                      (0x0000000FU)

#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_MINOR_VER_NUM_MASK                      (0x000000F0U)
#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_MINOR_VER_NUM_SHIFT                     (0x00000004U)
#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_MINOR_VER_NUM_RESETVAL                  (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_MINOR_VER_NUM_MAX                       (0x0000000FU)

#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_MAJOR_VER_NUM_MASK                      (0x00000F00U)
#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_MAJOR_VER_NUM_SHIFT                     (0x00000008U)
#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_MAJOR_VER_NUM_RESETVAL                  (0x00000005U)
#define CSL_MMC_CTLCFG_CQ_VERSION_EMMC_MAJOR_VER_NUM_MAX                       (0x0000000FU)

#define CSL_MMC_CTLCFG_CQ_VERSION_RESETVAL                                     (0x00000510U)

/* CQ_CAPABILITIES */

#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_VAL_MASK                             (0x000003FFU)
#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_VAL_SHIFT                            (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_VAL_RESETVAL                         (0x000000C8U)
#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_VAL_MAX                              (0x000003FFU)

#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_MUL_MASK                             (0x0000F000U)
#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_MUL_SHIFT                            (0x0000000CU)
#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_MUL_RESETVAL                         (0x00000003U)
#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_MUL_MAX                              (0x0000000FU)

#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_MUL_VAL_MHZ_1                        (0x3U)
#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_CF_MUL_VAL_MHZ_10                       (0x4U)

#define CSL_MMC_CTLCFG_CQ_CAPABILITIES_RESETVAL                                (0x000030C8U)

/* CQ_CONFIG */

#define CSL_MMC_CTLCFG_CQ_CONFIG_CQ_ENABLE_MASK                                (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_CQ_ENABLE_SHIFT                               (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_CQ_ENABLE_RESETVAL                            (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_CQ_ENABLE_MAX                                 (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_CONFIG_CQ_ENABLE_VAL_DISABLE                         (0x0U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_CQ_ENABLE_VAL_ENABLE                          (0x1U)

#define CSL_MMC_CTLCFG_CQ_CONFIG_TASK_DESC_SIZE_MASK                           (0x00000100U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_TASK_DESC_SIZE_SHIFT                          (0x00000008U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_TASK_DESC_SIZE_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_TASK_DESC_SIZE_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_CONFIG_TASK_DESC_SIZE_VAL_DESC_128                   (0x1U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_TASK_DESC_SIZE_VAL_DESC_64                    (0x0U)

#define CSL_MMC_CTLCFG_CQ_CONFIG_DCMD_ENA_MASK                                 (0x00001000U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_DCMD_ENA_SHIFT                                (0x0000000CU)
#define CSL_MMC_CTLCFG_CQ_CONFIG_DCMD_ENA_RESETVAL                             (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_DCMD_ENA_MAX                                  (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_CONFIG_DCMD_ENA_VAL_DCMD_DESC                        (0x1U)
#define CSL_MMC_CTLCFG_CQ_CONFIG_DCMD_ENA_VAL_DATA_DESC                        (0x0U)

#define CSL_MMC_CTLCFG_CQ_CONFIG_RESETVAL                                      (0x00000000U)

/* CQ_CONTROL */

#define CSL_MMC_CTLCFG_CQ_CONTROL_HALT_BIT_MASK                                (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_CONTROL_HALT_BIT_SHIFT                               (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CONTROL_HALT_BIT_RESETVAL                            (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CONTROL_HALT_BIT_MAX                                 (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_CONTROL_CLEAR_ALL_TASKS_MASK                         (0x00000100U)
#define CSL_MMC_CTLCFG_CQ_CONTROL_CLEAR_ALL_TASKS_SHIFT                        (0x00000008U)
#define CSL_MMC_CTLCFG_CQ_CONTROL_CLEAR_ALL_TASKS_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CONTROL_CLEAR_ALL_TASKS_MAX                          (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_CONTROL_RESETVAL                                     (0x00000000U)

/* CQ_INTR_STS */

#define CSL_MMC_CTLCFG_CQ_INTR_STS_HALT_COMPLETE_MASK                          (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_HALT_COMPLETE_SHIFT                         (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_HALT_COMPLETE_RESETVAL                      (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_HALT_COMPLETE_MAX                           (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_HALT_COMPLETE_VAL_NO_INT                    (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_HALT_COMPLETE_VAL_INT_SET                   (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_COMPLETE_MASK                          (0x00000002U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_COMPLETE_SHIFT                         (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_COMPLETE_RESETVAL                      (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_COMPLETE_MAX                           (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_COMPLETE_VAL_NO_INT                    (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_COMPLETE_VAL_INT_SET                   (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_RESP_ERR_DET_MASK                           (0x00000004U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_RESP_ERR_DET_SHIFT                          (0x00000002U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_RESP_ERR_DET_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_RESP_ERR_DET_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_CLEARED_MASK                           (0x00000008U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_CLEARED_SHIFT                          (0x00000003U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_CLEARED_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_CLEARED_MAX                            (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_CLEARED_VAL_NO_INT                     (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_CLEARED_VAL_INT_SET                    (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_ERROR_MASK                             (0x00000010U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_ERROR_SHIFT                            (0x00000004U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_ERROR_RESETVAL                         (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_ERROR_MAX                              (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_ERROR_VAL_NO_INT                       (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_TASK_ERROR_VAL_INT_SET                      (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_RESETVAL                                    (0x00000000U)

/* CQ_INTR_STS_ENA */

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_HALT_COMPLETE_MASK                      (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_HALT_COMPLETE_SHIFT                     (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_HALT_COMPLETE_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_HALT_COMPLETE_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_HALT_COMPLETE_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_HALT_COMPLETE_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_COMPLETE_MASK                      (0x00000002U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_COMPLETE_SHIFT                     (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_COMPLETE_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_COMPLETE_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_COMPLETE_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_COMPLETE_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_RESP_ERR_DET_MASK                       (0x00000004U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_RESP_ERR_DET_SHIFT                      (0x00000002U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_RESP_ERR_DET_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_RESP_ERR_DET_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_RESP_ERR_DET_VAL_MASK                   (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_RESP_ERR_DET_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_CLEARED_MASK                       (0x00000008U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_CLEARED_SHIFT                      (0x00000003U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_CLEARED_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_CLEARED_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_CLEARED_VAL_MASK                   (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_CLEARED_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_ERROR_MASK                         (0x00000010U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_ERROR_SHIFT                        (0x00000004U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_ERROR_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_ERROR_MAX                          (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_ERROR_VAL_MASK                     (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_TASK_ERROR_VAL_ENABLE                   (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_STS_ENA_RESETVAL                                (0x00000000U)

/* CQ_INTR_SIG_ENA */

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_HALT_COMPLETE_MASK                      (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_HALT_COMPLETE_SHIFT                     (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_HALT_COMPLETE_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_HALT_COMPLETE_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_HALT_COMPLETE_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_HALT_COMPLETE_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_COMPLETE_MASK                      (0x00000002U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_COMPLETE_SHIFT                     (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_COMPLETE_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_COMPLETE_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_COMPLETE_VAL_MASK                  (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_COMPLETE_VAL_ENABLE                (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_RESP_ERR_DET_MASK                       (0x00000004U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_RESP_ERR_DET_SHIFT                      (0x00000002U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_RESP_ERR_DET_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_RESP_ERR_DET_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_RESP_ERR_DET_VAL_MASK                   (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_RESP_ERR_DET_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_CLEARED_MASK                       (0x00000008U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_CLEARED_SHIFT                      (0x00000003U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_CLEARED_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_CLEARED_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_CLEARED_VAL_MASK                   (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_CLEARED_VAL_ENABLE                 (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_ERROR_MASK                         (0x00000010U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_ERROR_SHIFT                        (0x00000004U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_ERROR_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_ERROR_MAX                          (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_ERROR_VAL_MASK                     (0x0U)
#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_TASK_ERROR_VAL_ENABLE                   (0x1U)

#define CSL_MMC_CTLCFG_CQ_INTR_SIG_ENA_RESETVAL                                (0x00000000U)

/* CQ_INTR_COALESCING */

#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_TIMEOUT_VAL_MASK                     (0x0000007FU)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_TIMEOUT_VAL_SHIFT                    (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_TIMEOUT_VAL_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_TIMEOUT_VAL_MAX                      (0x0000007FU)

#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_CTR_THRESHOLD_MASK                   (0x00001F00U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_CTR_THRESHOLD_SHIFT                  (0x00000008U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_CTR_THRESHOLD_RESETVAL               (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_CTR_THRESHOLD_MAX                    (0x0000001FU)

#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_IC_STATUS_MASK                       (0x00100000U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_IC_STATUS_SHIFT                      (0x00000014U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_IC_STATUS_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_IC_STATUS_MAX                        (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_CQINTCOALESC_ENABLE_MASK             (0x80000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_CQINTCOALESC_ENABLE_SHIFT            (0x0000001FU)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_CQINTCOALESC_ENABLE_RESETVAL         (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_CQINTCOALESC_ENABLE_MAX              (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_INTR_COALESCING_RESETVAL                             (0x00000000U)

/* CQ_TDL_BASE_ADDR */

#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_CQTDLBA_LO_MASK                        (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_CQTDLBA_LO_SHIFT                       (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_CQTDLBA_LO_RESETVAL                    (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_CQTDLBA_LO_MAX                         (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_RESETVAL                               (0x00000000U)

/* CQ_TDL_BASE_ADDR_UPBITS */

#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_UPBITS_CQTDLBA_HI_MASK                 (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_UPBITS_CQTDLBA_HI_SHIFT                (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_UPBITS_CQTDLBA_HI_RESETVAL             (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_UPBITS_CQTDLBA_HI_MAX                  (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_TDL_BASE_ADDR_UPBITS_RESETVAL                        (0x00000000U)

/* CQ_TASK_DOOR_BELL */

#define CSL_MMC_CTLCFG_CQ_TASK_DOOR_BELL_CQTDB_VAL_MASK                        (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_TASK_DOOR_BELL_CQTDB_VAL_SHIFT                       (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_DOOR_BELL_CQTDB_VAL_RESETVAL                    (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_DOOR_BELL_CQTDB_VAL_MAX                         (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_TASK_DOOR_BELL_RESETVAL                              (0x00000000U)

/* CQ_TASK_COMP_NOTIF */

#define CSL_MMC_CTLCFG_CQ_TASK_COMP_NOTIF_CQTCN_VAL_MASK                       (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_TASK_COMP_NOTIF_CQTCN_VAL_SHIFT                      (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_COMP_NOTIF_CQTCN_VAL_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_COMP_NOTIF_CQTCN_VAL_MAX                        (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_TASK_COMP_NOTIF_RESETVAL                             (0x00000000U)

/* CQ_DEV_QUEUE_STATUS */

#define CSL_MMC_CTLCFG_CQ_DEV_QUEUE_STATUS_CQDQ_STS_MASK                       (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_DEV_QUEUE_STATUS_CQDQ_STS_SHIFT                      (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_DEV_QUEUE_STATUS_CQDQ_STS_RESETVAL                   (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_DEV_QUEUE_STATUS_CQDQ_STS_MAX                        (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_DEV_QUEUE_STATUS_RESETVAL                            (0x00000000U)

/* CQ_DEV_PENDING_TASKS */

#define CSL_MMC_CTLCFG_CQ_DEV_PENDING_TASKS_CQDP_TSKS_MASK                     (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_DEV_PENDING_TASKS_CQDP_TSKS_SHIFT                    (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_DEV_PENDING_TASKS_CQDP_TSKS_RESETVAL                 (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_DEV_PENDING_TASKS_CQDP_TSKS_MAX                      (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_DEV_PENDING_TASKS_RESETVAL                           (0x00000000U)

/* CQ_TASK_CLEAR */

#define CSL_MMC_CTLCFG_CQ_TASK_CLEAR_CQTCLR_MASK                               (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_TASK_CLEAR_CQTCLR_SHIFT                              (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_CLEAR_CQTCLR_RESETVAL                           (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_CLEAR_CQTCLR_MAX                                (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_TASK_CLEAR_RESETVAL                                  (0x00000000U)

/* CQ_SEND_STS_CONFIG1 */

#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1_CMD_IDLE_TIMER_MASK                 (0x0000FFFFU)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1_CMD_IDLE_TIMER_SHIFT                (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1_CMD_IDLE_TIMER_RESETVAL             (0x00001000U)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1_CMD_IDLE_TIMER_MAX                  (0x0000FFFFU)

#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1_CMD_BLK_CNTR_MASK                   (0x000F0000U)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1_CMD_BLK_CNTR_SHIFT                  (0x00000010U)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1_CMD_BLK_CNTR_RESETVAL               (0x00000001U)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1_CMD_BLK_CNTR_MAX                    (0x0000000FU)

#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG1_RESETVAL                            (0x00011000U)

/* CQ_SEND_STS_CONFIG2 */

#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG2_QUEUE_RCA_MASK                      (0x0000FFFFU)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG2_QUEUE_RCA_SHIFT                     (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG2_QUEUE_RCA_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG2_QUEUE_RCA_MAX                       (0x0000FFFFU)

#define CSL_MMC_CTLCFG_CQ_SEND_STS_CONFIG2_RESETVAL                            (0x00000000U)

/* CQ_DCMD_RESPONSE */

#define CSL_MMC_CTLCFG_CQ_DCMD_RESPONSE_LAST_RESP_MASK                         (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_DCMD_RESPONSE_LAST_RESP_SHIFT                        (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_DCMD_RESPONSE_LAST_RESP_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_DCMD_RESPONSE_LAST_RESP_MAX                          (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_DCMD_RESPONSE_RESETVAL                               (0x00000000U)

/* CQ_RESP_ERR_MASK */

#define CSL_MMC_CTLCFG_CQ_RESP_ERR_MASK_CQRMEM_MASK                            (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_RESP_ERR_MASK_CQRMEM_SHIFT                           (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_RESP_ERR_MASK_CQRMEM_RESETVAL                        (0xFDF9A080U)
#define CSL_MMC_CTLCFG_CQ_RESP_ERR_MASK_CQRMEM_MAX                             (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_RESP_ERR_MASK_RESETVAL                               (0xFDF9A080U)

/* CQ_TASK_ERR_INFO */

#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_CMD_INDEX_MASK               (0x0000003FU)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_CMD_INDEX_SHIFT              (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_CMD_INDEX_RESETVAL           (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_CMD_INDEX_MAX                (0x0000003FU)

#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_TASK_ID_MASK                 (0x00001F00U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_TASK_ID_SHIFT                (0x00000008U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_TASK_ID_RESETVAL             (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_TASK_ID_MAX                  (0x0000001FU)

#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_VALID_MASK                   (0x00008000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_VALID_SHIFT                  (0x0000000FU)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_VALID_RESETVAL               (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESP_MODE_VALID_MAX                    (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_CMD_INDEX_MASK                  (0x003F0000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_CMD_INDEX_SHIFT                 (0x00000010U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_CMD_INDEX_RESETVAL              (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_CMD_INDEX_MAX                   (0x0000003FU)

#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_TASK_ID_MASK                    (0x1F000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_TASK_ID_SHIFT                   (0x00000018U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_TASK_ID_RESETVAL                (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_TASK_ID_MAX                     (0x0000001FU)

#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_VALID_MASK                      (0x80000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_VALID_SHIFT                     (0x0000001FU)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_VALID_RESETVAL                  (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_DATERR_VALID_MAX                       (0x00000001U)

#define CSL_MMC_CTLCFG_CQ_TASK_ERR_INFO_RESETVAL                               (0x00000000U)

/* CQ_CMD_RESP_INDEX */

#define CSL_MMC_CTLCFG_CQ_CMD_RESP_INDEX_LAST_CRI_MASK                         (0x0000003FU)
#define CSL_MMC_CTLCFG_CQ_CMD_RESP_INDEX_LAST_CRI_SHIFT                        (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CMD_RESP_INDEX_LAST_CRI_RESETVAL                     (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CMD_RESP_INDEX_LAST_CRI_MAX                          (0x0000003FU)

#define CSL_MMC_CTLCFG_CQ_CMD_RESP_INDEX_RESETVAL                              (0x00000000U)

/* CQ_CMD_RESP_ARG */

#define CSL_MMC_CTLCFG_CQ_CMD_RESP_ARG_LAST_CRA_MASK                           (0xFFFFFFFFU)
#define CSL_MMC_CTLCFG_CQ_CMD_RESP_ARG_LAST_CRA_SHIFT                          (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CMD_RESP_ARG_LAST_CRA_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_CMD_RESP_ARG_LAST_CRA_MAX                            (0xFFFFFFFFU)

#define CSL_MMC_CTLCFG_CQ_CMD_RESP_ARG_RESETVAL                                (0x00000000U)

/* CQ_ERROR_TASK_ID */

#define CSL_MMC_CTLCFG_CQ_ERROR_TASK_ID_TERR_ID_MASK                           (0x0000001FU)
#define CSL_MMC_CTLCFG_CQ_ERROR_TASK_ID_TERR_ID_SHIFT                          (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_ERROR_TASK_ID_TERR_ID_RESETVAL                       (0x00000000U)
#define CSL_MMC_CTLCFG_CQ_ERROR_TASK_ID_TERR_ID_MAX                            (0x0000001FU)

#define CSL_MMC_CTLCFG_CQ_ERROR_TASK_ID_RESETVAL                               (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
