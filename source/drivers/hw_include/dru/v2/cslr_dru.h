/********************************************************************
 * Copyright (C) 2024 Texas Instruments Incorporated.
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
 *  Name        : cslr_dru.h
*/
#ifndef CSLR_DRU_H_
#define CSLR_DRU_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

/**************************************************************************
* Module Base Offset Values
**************************************************************************/

#define CSL_DRU_ATOMIC_REGS_BASE                                               (0x00080000U)
#define CSL_DRU_CAUSE_REGS_BASE                                                (0x000E0000U)
#define CSL_DRU_CHNRT_REGS_BASE                                                (0x00040000U)
#define CSL_DRU_CHRT_REGS_BASE                                                 (0x00060000U)
#define CSL_DRU_QUEUE_REGS_BASE                                                (0x00008000U)
#define CSL_DRU_REGS_BASE                                                      (0x00000000U)
#define CSL_DRU_SET_REGS_BASE                                                  (0x00004000U)


/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint64_t DRU_PID;                   /* Peripheral ID Register */
    volatile uint64_t DRU_CAPABILITIES;          /* DRU Capabilities: Lists the capabilities of the channel for TR TYPE and formatting functions */
    volatile uint8_t  Resv_64[48];
    volatile uint64_t DRU_PRI_MASK0;             /* DRU Priority Mask */
} CSL_druRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_DRU_PID                                                        (0x00000000U)
#define CSL_DRU_CAPABILITIES                                               (0x00000008U)
#define CSL_DRU_PRI_MASK0                                                  (0x00000040U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* DRU_PID */

#define CSL_DRU_PID_MINOR_MASK                                             (0x000000000000003FU)
#define CSL_DRU_PID_MINOR_SHIFT                                            (0x0000000000000000U)
#define CSL_DRU_PID_MINOR_RESETVAL                                         (0x0000000000000003U)
#define CSL_DRU_PID_MINOR_MAX                                              (0x000000000000003FU)

#define CSL_DRU_PID_CUSTOM_MASK                                            (0x00000000000000C0U)
#define CSL_DRU_PID_CUSTOM_SHIFT                                           (0x0000000000000006U)
#define CSL_DRU_PID_CUSTOM_RESETVAL                                        (0x0000000000000000U)
#define CSL_DRU_PID_CUSTOM_MAX                                             (0x0000000000000003U)

#define CSL_DRU_PID_MAJOR_MASK                                             (0x0000000000000700U)
#define CSL_DRU_PID_MAJOR_SHIFT                                            (0x0000000000000008U)
#define CSL_DRU_PID_MAJOR_RESETVAL                                         (0x0000000000000001U)
#define CSL_DRU_PID_MAJOR_MAX                                              (0x0000000000000007U)

#define CSL_DRU_PID_RTL_MASK                                               (0x000000000000F800U)
#define CSL_DRU_PID_RTL_SHIFT                                              (0x000000000000000BU)
#define CSL_DRU_PID_RTL_RESETVAL                                           (0x0000000000000001U)
#define CSL_DRU_PID_RTL_MAX                                                (0x000000000000001FU)

#define CSL_DRU_PID_FUNC_MASK                                              (0x000000000FFF0000U)
#define CSL_DRU_PID_FUNC_SHIFT                                             (0x0000000000000010U)
#define CSL_DRU_PID_FUNC_RESETVAL                                          (0x000000000000062CU)
#define CSL_DRU_PID_FUNC_MAX                                               (0x0000000000000FFFU)

#define CSL_DRU_PID_BU_MASK                                                (0x0000000030000000U)
#define CSL_DRU_PID_BU_SHIFT                                               (0x000000000000001CU)
#define CSL_DRU_PID_BU_RESETVAL                                            (0x0000000000000002U)
#define CSL_DRU_PID_BU_MAX                                                 (0x0000000000000003U)

#define CSL_DRU_PID_SCHEME_MASK                                            (0x00000000C0000000U)
#define CSL_DRU_PID_SCHEME_SHIFT                                           (0x000000000000001EU)
#define CSL_DRU_PID_SCHEME_RESETVAL                                        (0x0000000000000001U)
#define CSL_DRU_PID_SCHEME_MAX                                             (0x0000000000000003U)

#define CSL_DRU_PID_RSVD_MASK                                              (0xFFFFFFFF00000000U)
#define CSL_DRU_PID_RSVD_SHIFT                                             (0x0000000000000020U)
#define CSL_DRU_PID_RSVD_RESETVAL                                          (0x0000000000000000U)
#define CSL_DRU_PID_RSVD_MAX                                               (0x00000000FFFFFFFFU)

#define CSL_DRU_PID_RESETVAL                                               (0x00000000662C0903U)

/* DRU_CAPABILITIES */

#define CSL_DRU_CAPABILITIES_TYPE0_MASK                                    (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_TYPE0_SHIFT                                   (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE0_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE0_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE1_MASK                                    (0x0000000000000002U)
#define CSL_DRU_CAPABILITIES_TYPE1_SHIFT                                   (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_TYPE1_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE1_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE2_MASK                                    (0x0000000000000004U)
#define CSL_DRU_CAPABILITIES_TYPE2_SHIFT                                   (0x0000000000000002U)
#define CSL_DRU_CAPABILITIES_TYPE2_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE2_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE3_MASK                                    (0x0000000000000008U)
#define CSL_DRU_CAPABILITIES_TYPE3_SHIFT                                   (0x0000000000000003U)
#define CSL_DRU_CAPABILITIES_TYPE3_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE3_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE4_MASK                                    (0x0000000000000010U)
#define CSL_DRU_CAPABILITIES_TYPE4_SHIFT                                   (0x0000000000000004U)
#define CSL_DRU_CAPABILITIES_TYPE4_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE4_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE5_MASK                                    (0x0000000000000020U)
#define CSL_DRU_CAPABILITIES_TYPE5_SHIFT                                   (0x0000000000000005U)
#define CSL_DRU_CAPABILITIES_TYPE5_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE5_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE6_MASK                                    (0x0000000000000040U)
#define CSL_DRU_CAPABILITIES_TYPE6_SHIFT                                   (0x0000000000000006U)
#define CSL_DRU_CAPABILITIES_TYPE6_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE6_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE7_MASK                                    (0x0000000000000080U)
#define CSL_DRU_CAPABILITIES_TYPE7_SHIFT                                   (0x0000000000000007U)
#define CSL_DRU_CAPABILITIES_TYPE7_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE7_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE8_MASK                                    (0x0000000000000100U)
#define CSL_DRU_CAPABILITIES_TYPE8_SHIFT                                   (0x0000000000000008U)
#define CSL_DRU_CAPABILITIES_TYPE8_RESETVAL                                (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_TYPE8_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE9_MASK                                    (0x0000000000000200U)
#define CSL_DRU_CAPABILITIES_TYPE9_SHIFT                                   (0x0000000000000009U)
#define CSL_DRU_CAPABILITIES_TYPE9_RESETVAL                                (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_TYPE9_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE10_MASK                                   (0x0000000000000400U)
#define CSL_DRU_CAPABILITIES_TYPE10_SHIFT                                  (0x000000000000000AU)
#define CSL_DRU_CAPABILITIES_TYPE10_RESETVAL                               (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_TYPE10_MAX                                    (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE11_MASK                                   (0x0000000000000800U)
#define CSL_DRU_CAPABILITIES_TYPE11_SHIFT                                  (0x000000000000000BU)
#define CSL_DRU_CAPABILITIES_TYPE11_RESETVAL                               (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_TYPE11_MAX                                    (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE12_MASK                                   (0x0000000000001000U)
#define CSL_DRU_CAPABILITIES_TYPE12_SHIFT                                  (0x000000000000000CU)
#define CSL_DRU_CAPABILITIES_TYPE12_RESETVAL                               (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE12_MAX                                    (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE13_MASK                                   (0x0000000000002000U)
#define CSL_DRU_CAPABILITIES_TYPE13_SHIFT                                  (0x000000000000000DU)
#define CSL_DRU_CAPABILITIES_TYPE13_RESETVAL                               (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE13_MAX                                    (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE14_MASK                                   (0x0000000000004000U)
#define CSL_DRU_CAPABILITIES_TYPE14_SHIFT                                  (0x000000000000000EU)
#define CSL_DRU_CAPABILITIES_TYPE14_RESETVAL                               (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE14_MAX                                    (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TYPE15_MASK                                   (0x0000000000008000U)
#define CSL_DRU_CAPABILITIES_TYPE15_SHIFT                                  (0x000000000000000FU)
#define CSL_DRU_CAPABILITIES_TYPE15_RESETVAL                               (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_TYPE15_MAX                                    (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_TRSTATIC_MASK                                 (0x0000000000010000U)
#define CSL_DRU_CAPABILITIES_TRSTATIC_SHIFT                                (0x0000000000000010U)
#define CSL_DRU_CAPABILITIES_TRSTATIC_RESETVAL                             (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_TRSTATIC_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_EOL_MASK                                      (0x0000000000020000U)
#define CSL_DRU_CAPABILITIES_EOL_SHIFT                                     (0x0000000000000011U)
#define CSL_DRU_CAPABILITIES_EOL_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_EOL_MAX                                       (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_LOCAL_TRIG_MASK                               (0x0000000000040000U)
#define CSL_DRU_CAPABILITIES_LOCAL_TRIG_SHIFT                              (0x0000000000000012U)
#define CSL_DRU_CAPABILITIES_LOCAL_TRIG_RESETVAL                           (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_LOCAL_TRIG_MAX                                (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_GLOBAL_TRIG_MASK                              (0x0000000000080000U)
#define CSL_DRU_CAPABILITIES_GLOBAL_TRIG_SHIFT                             (0x0000000000000013U)
#define CSL_DRU_CAPABILITIES_GLOBAL_TRIG_RESETVAL                          (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_GLOBAL_TRIG_MAX                               (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_RSVD_CONF_SPEC_MASK                           (0x00000000FFF00000U)
#define CSL_DRU_CAPABILITIES_RSVD_CONF_SPEC_SHIFT                          (0x0000000000000014U)
#define CSL_DRU_CAPABILITIES_RSVD_CONF_SPEC_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_RSVD_CONF_SPEC_MAX                            (0x0000000000000FFFU)

#define CSL_DRU_CAPABILITIES_AMODE_MASK                                    (0x0000000700000000U)
#define CSL_DRU_CAPABILITIES_AMODE_SHIFT                                   (0x0000000000000020U)
#define CSL_DRU_CAPABILITIES_AMODE_RESETVAL                                (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_AMODE_MAX                                     (0x0000000000000007U)

#define CSL_DRU_CAPABILITIES_ELTYPE_MASK                                   (0x0000007800000000U)
#define CSL_DRU_CAPABILITIES_ELTYPE_SHIFT                                  (0x0000000000000023U)
#define CSL_DRU_CAPABILITIES_ELTYPE_RESETVAL                               (0x000000000000000BU)
#define CSL_DRU_CAPABILITIES_ELTYPE_MAX                                    (0x000000000000000FU)

#define CSL_DRU_CAPABILITIES_DFMT_MASK                                     (0x0000078000000000U)
#define CSL_DRU_CAPABILITIES_DFMT_SHIFT                                    (0x0000000000000027U)
#define CSL_DRU_CAPABILITIES_DFMT_RESETVAL                                 (0x0000000000000001U)
#define CSL_DRU_CAPABILITIES_DFMT_MAX                                      (0x000000000000000FU)

#define CSL_DRU_CAPABILITIES_SECTR_MASK                                    (0x0000780000000000U)
#define CSL_DRU_CAPABILITIES_SECTR_SHIFT                                   (0x000000000000002BU)
#define CSL_DRU_CAPABILITIES_SECTR_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_SECTR_MAX                                     (0x000000000000000FU)

#define CSL_DRU_CAPABILITIES_ACOMP_MASK                                    (0x0000800000000000U)
#define CSL_DRU_CAPABILITIES_ACOMP_SHIFT                                   (0x000000000000002FU)
#define CSL_DRU_CAPABILITIES_ACOMP_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_ACOMP_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_VCOMP_MASK                                    (0x0001000000000000U)
#define CSL_DRU_CAPABILITIES_VCOMP_SHIFT                                   (0x0000000000000030U)
#define CSL_DRU_CAPABILITIES_VCOMP_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_VCOMP_MAX                                     (0x0000000000000001U)

#define CSL_DRU_CAPABILITIES_RSVD_MASK                                     (0xFFFE000000000000U)
#define CSL_DRU_CAPABILITIES_RSVD_SHIFT                                    (0x0000000000000031U)
#define CSL_DRU_CAPABILITIES_RSVD_RESETVAL                                 (0x0000000000000000U)
#define CSL_DRU_CAPABILITIES_RSVD_MAX                                      (0x0000000000007FFFU)

#define CSL_DRU_CAPABILITIES_RESETVAL                                      (0x000000D9000D0F00U)

/* DRU_PRI_MASK0 */

#define CSL_DRU_PRI_MASK0_MASK0_MASK                                       (0x0000000000000001U)
#define CSL_DRU_PRI_MASK0_MASK0_SHIFT                                      (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK0_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK0_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK1_MASK                                       (0x0000000000000002U)
#define CSL_DRU_PRI_MASK0_MASK1_SHIFT                                      (0x0000000000000001U)
#define CSL_DRU_PRI_MASK0_MASK1_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK1_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK2_MASK                                       (0x0000000000000004U)
#define CSL_DRU_PRI_MASK0_MASK2_SHIFT                                      (0x0000000000000002U)
#define CSL_DRU_PRI_MASK0_MASK2_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK2_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK3_MASK                                       (0x0000000000000008U)
#define CSL_DRU_PRI_MASK0_MASK3_SHIFT                                      (0x0000000000000003U)
#define CSL_DRU_PRI_MASK0_MASK3_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK3_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK4_MASK                                       (0x0000000000000010U)
#define CSL_DRU_PRI_MASK0_MASK4_SHIFT                                      (0x0000000000000004U)
#define CSL_DRU_PRI_MASK0_MASK4_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK4_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK5_MASK                                       (0x0000000000000020U)
#define CSL_DRU_PRI_MASK0_MASK5_SHIFT                                      (0x0000000000000005U)
#define CSL_DRU_PRI_MASK0_MASK5_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK5_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK6_MASK                                       (0x0000000000000040U)
#define CSL_DRU_PRI_MASK0_MASK6_SHIFT                                      (0x0000000000000006U)
#define CSL_DRU_PRI_MASK0_MASK6_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK6_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK7_MASK                                       (0x0000000000000080U)
#define CSL_DRU_PRI_MASK0_MASK7_SHIFT                                      (0x0000000000000007U)
#define CSL_DRU_PRI_MASK0_MASK7_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK7_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK8_MASK                                       (0x0000000000000100U)
#define CSL_DRU_PRI_MASK0_MASK8_SHIFT                                      (0x0000000000000008U)
#define CSL_DRU_PRI_MASK0_MASK8_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK8_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK9_MASK                                       (0x0000000000000200U)
#define CSL_DRU_PRI_MASK0_MASK9_SHIFT                                      (0x0000000000000009U)
#define CSL_DRU_PRI_MASK0_MASK9_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK9_MAX                                        (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK10_MASK                                      (0x0000000000000400U)
#define CSL_DRU_PRI_MASK0_MASK10_SHIFT                                     (0x000000000000000AU)
#define CSL_DRU_PRI_MASK0_MASK10_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK10_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK11_MASK                                      (0x0000000000000800U)
#define CSL_DRU_PRI_MASK0_MASK11_SHIFT                                     (0x000000000000000BU)
#define CSL_DRU_PRI_MASK0_MASK11_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK11_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK12_MASK                                      (0x0000000000001000U)
#define CSL_DRU_PRI_MASK0_MASK12_SHIFT                                     (0x000000000000000CU)
#define CSL_DRU_PRI_MASK0_MASK12_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK12_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK13_MASK                                      (0x0000000000002000U)
#define CSL_DRU_PRI_MASK0_MASK13_SHIFT                                     (0x000000000000000DU)
#define CSL_DRU_PRI_MASK0_MASK13_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK13_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK14_MASK                                      (0x0000000000004000U)
#define CSL_DRU_PRI_MASK0_MASK14_SHIFT                                     (0x000000000000000EU)
#define CSL_DRU_PRI_MASK0_MASK14_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK14_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK15_MASK                                      (0x0000000000008000U)
#define CSL_DRU_PRI_MASK0_MASK15_SHIFT                                     (0x000000000000000FU)
#define CSL_DRU_PRI_MASK0_MASK15_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK15_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK16_MASK                                      (0x0000000000010000U)
#define CSL_DRU_PRI_MASK0_MASK16_SHIFT                                     (0x0000000000000010U)
#define CSL_DRU_PRI_MASK0_MASK16_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK16_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK17_MASK                                      (0x0000000000020000U)
#define CSL_DRU_PRI_MASK0_MASK17_SHIFT                                     (0x0000000000000011U)
#define CSL_DRU_PRI_MASK0_MASK17_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK17_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK18_MASK                                      (0x0000000000040000U)
#define CSL_DRU_PRI_MASK0_MASK18_SHIFT                                     (0x0000000000000012U)
#define CSL_DRU_PRI_MASK0_MASK18_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK18_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK19_MASK                                      (0x0000000000080000U)
#define CSL_DRU_PRI_MASK0_MASK19_SHIFT                                     (0x0000000000000013U)
#define CSL_DRU_PRI_MASK0_MASK19_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK19_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK20_MASK                                      (0x0000000000100000U)
#define CSL_DRU_PRI_MASK0_MASK20_SHIFT                                     (0x0000000000000014U)
#define CSL_DRU_PRI_MASK0_MASK20_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK20_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK21_MASK                                      (0x0000000000200000U)
#define CSL_DRU_PRI_MASK0_MASK21_SHIFT                                     (0x0000000000000015U)
#define CSL_DRU_PRI_MASK0_MASK21_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK21_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK22_MASK                                      (0x0000000000400000U)
#define CSL_DRU_PRI_MASK0_MASK22_SHIFT                                     (0x0000000000000016U)
#define CSL_DRU_PRI_MASK0_MASK22_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK22_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK23_MASK                                      (0x0000000000800000U)
#define CSL_DRU_PRI_MASK0_MASK23_SHIFT                                     (0x0000000000000017U)
#define CSL_DRU_PRI_MASK0_MASK23_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK23_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK24_MASK                                      (0x0000000001000000U)
#define CSL_DRU_PRI_MASK0_MASK24_SHIFT                                     (0x0000000000000018U)
#define CSL_DRU_PRI_MASK0_MASK24_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK24_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK25_MASK                                      (0x0000000002000000U)
#define CSL_DRU_PRI_MASK0_MASK25_SHIFT                                     (0x0000000000000019U)
#define CSL_DRU_PRI_MASK0_MASK25_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK25_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK26_MASK                                      (0x0000000004000000U)
#define CSL_DRU_PRI_MASK0_MASK26_SHIFT                                     (0x000000000000001AU)
#define CSL_DRU_PRI_MASK0_MASK26_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK26_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK27_MASK                                      (0x0000000008000000U)
#define CSL_DRU_PRI_MASK0_MASK27_SHIFT                                     (0x000000000000001BU)
#define CSL_DRU_PRI_MASK0_MASK27_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK27_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK28_MASK                                      (0x0000000010000000U)
#define CSL_DRU_PRI_MASK0_MASK28_SHIFT                                     (0x000000000000001CU)
#define CSL_DRU_PRI_MASK0_MASK28_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK28_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK29_MASK                                      (0x0000000020000000U)
#define CSL_DRU_PRI_MASK0_MASK29_SHIFT                                     (0x000000000000001DU)
#define CSL_DRU_PRI_MASK0_MASK29_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK29_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK30_MASK                                      (0x0000000040000000U)
#define CSL_DRU_PRI_MASK0_MASK30_SHIFT                                     (0x000000000000001EU)
#define CSL_DRU_PRI_MASK0_MASK30_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK30_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK31_MASK                                      (0x0000000080000000U)
#define CSL_DRU_PRI_MASK0_MASK31_SHIFT                                     (0x000000000000001FU)
#define CSL_DRU_PRI_MASK0_MASK31_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK31_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK32_MASK                                      (0x0000000100000000U)
#define CSL_DRU_PRI_MASK0_MASK32_SHIFT                                     (0x0000000000000020U)
#define CSL_DRU_PRI_MASK0_MASK32_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK32_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK33_MASK                                      (0x0000000200000000U)
#define CSL_DRU_PRI_MASK0_MASK33_SHIFT                                     (0x0000000000000021U)
#define CSL_DRU_PRI_MASK0_MASK33_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK33_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK34_MASK                                      (0x0000000400000000U)
#define CSL_DRU_PRI_MASK0_MASK34_SHIFT                                     (0x0000000000000022U)
#define CSL_DRU_PRI_MASK0_MASK34_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK34_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK35_MASK                                      (0x0000000800000000U)
#define CSL_DRU_PRI_MASK0_MASK35_SHIFT                                     (0x0000000000000023U)
#define CSL_DRU_PRI_MASK0_MASK35_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK35_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK36_MASK                                      (0x0000001000000000U)
#define CSL_DRU_PRI_MASK0_MASK36_SHIFT                                     (0x0000000000000024U)
#define CSL_DRU_PRI_MASK0_MASK36_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK36_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK37_MASK                                      (0x0000002000000000U)
#define CSL_DRU_PRI_MASK0_MASK37_SHIFT                                     (0x0000000000000025U)
#define CSL_DRU_PRI_MASK0_MASK37_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK37_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK38_MASK                                      (0x0000004000000000U)
#define CSL_DRU_PRI_MASK0_MASK38_SHIFT                                     (0x0000000000000026U)
#define CSL_DRU_PRI_MASK0_MASK38_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK38_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK39_MASK                                      (0x0000008000000000U)
#define CSL_DRU_PRI_MASK0_MASK39_SHIFT                                     (0x0000000000000027U)
#define CSL_DRU_PRI_MASK0_MASK39_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK39_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK40_MASK                                      (0x0000010000000000U)
#define CSL_DRU_PRI_MASK0_MASK40_SHIFT                                     (0x0000000000000028U)
#define CSL_DRU_PRI_MASK0_MASK40_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK40_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK41_MASK                                      (0x0000020000000000U)
#define CSL_DRU_PRI_MASK0_MASK41_SHIFT                                     (0x0000000000000029U)
#define CSL_DRU_PRI_MASK0_MASK41_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK41_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK42_MASK                                      (0x0000040000000000U)
#define CSL_DRU_PRI_MASK0_MASK42_SHIFT                                     (0x000000000000002AU)
#define CSL_DRU_PRI_MASK0_MASK42_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK42_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK43_MASK                                      (0x0000080000000000U)
#define CSL_DRU_PRI_MASK0_MASK43_SHIFT                                     (0x000000000000002BU)
#define CSL_DRU_PRI_MASK0_MASK43_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK43_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK44_MASK                                      (0x0000100000000000U)
#define CSL_DRU_PRI_MASK0_MASK44_SHIFT                                     (0x000000000000002CU)
#define CSL_DRU_PRI_MASK0_MASK44_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK44_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK45_MASK                                      (0x0000200000000000U)
#define CSL_DRU_PRI_MASK0_MASK45_SHIFT                                     (0x000000000000002DU)
#define CSL_DRU_PRI_MASK0_MASK45_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK45_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK46_MASK                                      (0x0000400000000000U)
#define CSL_DRU_PRI_MASK0_MASK46_SHIFT                                     (0x000000000000002EU)
#define CSL_DRU_PRI_MASK0_MASK46_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK46_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK47_MASK                                      (0x0000800000000000U)
#define CSL_DRU_PRI_MASK0_MASK47_SHIFT                                     (0x000000000000002FU)
#define CSL_DRU_PRI_MASK0_MASK47_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK47_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK48_MASK                                      (0x0001000000000000U)
#define CSL_DRU_PRI_MASK0_MASK48_SHIFT                                     (0x0000000000000030U)
#define CSL_DRU_PRI_MASK0_MASK48_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK48_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK49_MASK                                      (0x0002000000000000U)
#define CSL_DRU_PRI_MASK0_MASK49_SHIFT                                     (0x0000000000000031U)
#define CSL_DRU_PRI_MASK0_MASK49_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK49_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK50_MASK                                      (0x0004000000000000U)
#define CSL_DRU_PRI_MASK0_MASK50_SHIFT                                     (0x0000000000000032U)
#define CSL_DRU_PRI_MASK0_MASK50_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK50_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK51_MASK                                      (0x0008000000000000U)
#define CSL_DRU_PRI_MASK0_MASK51_SHIFT                                     (0x0000000000000033U)
#define CSL_DRU_PRI_MASK0_MASK51_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK51_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK52_MASK                                      (0x0010000000000000U)
#define CSL_DRU_PRI_MASK0_MASK52_SHIFT                                     (0x0000000000000034U)
#define CSL_DRU_PRI_MASK0_MASK52_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK52_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK53_MASK                                      (0x0020000000000000U)
#define CSL_DRU_PRI_MASK0_MASK53_SHIFT                                     (0x0000000000000035U)
#define CSL_DRU_PRI_MASK0_MASK53_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK53_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK54_MASK                                      (0x0040000000000000U)
#define CSL_DRU_PRI_MASK0_MASK54_SHIFT                                     (0x0000000000000036U)
#define CSL_DRU_PRI_MASK0_MASK54_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK54_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK55_MASK                                      (0x0080000000000000U)
#define CSL_DRU_PRI_MASK0_MASK55_SHIFT                                     (0x0000000000000037U)
#define CSL_DRU_PRI_MASK0_MASK55_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK55_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK56_MASK                                      (0x0100000000000000U)
#define CSL_DRU_PRI_MASK0_MASK56_SHIFT                                     (0x0000000000000038U)
#define CSL_DRU_PRI_MASK0_MASK56_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK56_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK57_MASK                                      (0x0200000000000000U)
#define CSL_DRU_PRI_MASK0_MASK57_SHIFT                                     (0x0000000000000039U)
#define CSL_DRU_PRI_MASK0_MASK57_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK57_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK58_MASK                                      (0x0400000000000000U)
#define CSL_DRU_PRI_MASK0_MASK58_SHIFT                                     (0x000000000000003AU)
#define CSL_DRU_PRI_MASK0_MASK58_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK58_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK59_MASK                                      (0x0800000000000000U)
#define CSL_DRU_PRI_MASK0_MASK59_SHIFT                                     (0x000000000000003BU)
#define CSL_DRU_PRI_MASK0_MASK59_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK59_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK60_MASK                                      (0x1000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK60_SHIFT                                     (0x000000000000003CU)
#define CSL_DRU_PRI_MASK0_MASK60_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK60_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK61_MASK                                      (0x2000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK61_SHIFT                                     (0x000000000000003DU)
#define CSL_DRU_PRI_MASK0_MASK61_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK61_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK62_MASK                                      (0x4000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK62_SHIFT                                     (0x000000000000003EU)
#define CSL_DRU_PRI_MASK0_MASK62_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK62_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_MASK63_MASK                                      (0x8000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK63_SHIFT                                     (0x000000000000003FU)
#define CSL_DRU_PRI_MASK0_MASK63_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_PRI_MASK0_MASK63_MAX                                       (0x0000000000000001U)

#define CSL_DRU_PRI_MASK0_RESETVAL                                         (0x0000000000000000U)

/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint64_t CFG[5];                    /* Configuration Register for Queue 0 */
    volatile uint8_t  Resv_64[8];
    volatile uint64_t STATUS[5];                 /* Status Register for Queue 0 */
} CSL_dru_queueRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_DRU_QUEUE_CFG(CFG)                                                 (0x00000000U+((CFG)*0x8U))
#define CSL_DRU_QUEUE_STATUS(STATUS)                                           (0x00000040U+((STATUS)*0x8U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CFG */

#define CSL_DRU_QUEUE_CFG_CONSECUTIVE_TRANS_MASK                               (0x0000000000FF0000U)
#define CSL_DRU_QUEUE_CFG_CONSECUTIVE_TRANS_SHIFT                              (0x0000000000000010U)
#define CSL_DRU_QUEUE_CFG_CONSECUTIVE_TRANS_RESETVAL                           (0x0000000000000000U)
#define CSL_DRU_QUEUE_CFG_CONSECUTIVE_TRANS_MAX                                (0x00000000000000FFU)

#define CSL_DRU_QUEUE_CFG_ORDERID_MASK                                         (0x00000000000000F0U)
#define CSL_DRU_QUEUE_CFG_ORDERID_SHIFT                                        (0x0000000000000004U)
#define CSL_DRU_QUEUE_CFG_ORDERID_RESETVAL                                     (0x0000000000000000U)
#define CSL_DRU_QUEUE_CFG_ORDERID_MAX                                          (0x000000000000000FU)

#define CSL_DRU_QUEUE_CFG_PRI_MASK                                             (0x0000000000000007U)
#define CSL_DRU_QUEUE_CFG_PRI_SHIFT                                            (0x0000000000000000U)
#define CSL_DRU_QUEUE_CFG_PRI_RESETVAL                                         (0x0000000000000000U)
#define CSL_DRU_QUEUE_CFG_PRI_MAX                                              (0x0000000000000007U)

#define CSL_DRU_QUEUE_CFG_QOS_MASK                                             (0x0000000000000700U)
#define CSL_DRU_QUEUE_CFG_QOS_SHIFT                                            (0x0000000000000008U)
#define CSL_DRU_QUEUE_CFG_QOS_RESETVAL                                         (0x0000000000000000U)
#define CSL_DRU_QUEUE_CFG_QOS_MAX                                              (0x0000000000000007U)

#define CSL_DRU_QUEUE_CFG_REARB_WAIT_MASK                                      (0x00000000FF000000U)
#define CSL_DRU_QUEUE_CFG_REARB_WAIT_SHIFT                                     (0x0000000000000018U)
#define CSL_DRU_QUEUE_CFG_REARB_WAIT_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_QUEUE_CFG_REARB_WAIT_MAX                                       (0x00000000000000FFU)

#define CSL_DRU_QUEUE_CFG_RSVD_MASK                                            (0xFFFFFFFF00000000U)
#define CSL_DRU_QUEUE_CFG_RSVD_SHIFT                                           (0x0000000000000020U)
#define CSL_DRU_QUEUE_CFG_RSVD_RESETVAL                                        (0x0000000000000000U)
#define CSL_DRU_QUEUE_CFG_RSVD_MAX                                             (0x00000000FFFFFFFFU)

#define CSL_DRU_QUEUE_CFG_RESETVAL                                             (0x0000000000000000U)

/* STATUS */

#define CSL_DRU_QUEUE_STATUS_RD_TOP_MASK                                       (0x0000000007FC0000U)
#define CSL_DRU_QUEUE_STATUS_RD_TOP_SHIFT                                      (0x0000000000000012U)
#define CSL_DRU_QUEUE_STATUS_RD_TOP_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_QUEUE_STATUS_RD_TOP_MAX                                        (0x00000000000001FFU)

#define CSL_DRU_QUEUE_STATUS_RD_TOTAL_MASK                                     (0x0000000FF8000000U)
#define CSL_DRU_QUEUE_STATUS_RD_TOTAL_SHIFT                                    (0x000000000000001BU)
#define CSL_DRU_QUEUE_STATUS_RD_TOTAL_RESETVAL                                 (0x0000000000000000U)
#define CSL_DRU_QUEUE_STATUS_RD_TOTAL_MAX                                      (0x00000000000001FFU)

#define CSL_DRU_QUEUE_STATUS_RSVD_MASK                                         (0xFFFFFFF000000000U)
#define CSL_DRU_QUEUE_STATUS_RSVD_SHIFT                                        (0x0000000000000024U)
#define CSL_DRU_QUEUE_STATUS_RSVD_RESETVAL                                     (0x0000000000000000U)
#define CSL_DRU_QUEUE_STATUS_RSVD_MAX                                          (0x000000000FFFFFFFU)

#define CSL_DRU_QUEUE_STATUS_WR_TOP_MASK                                       (0x00000000000001FFU)
#define CSL_DRU_QUEUE_STATUS_WR_TOP_SHIFT                                      (0x0000000000000000U)
#define CSL_DRU_QUEUE_STATUS_WR_TOP_RESETVAL                                   (0x0000000000000000U)
#define CSL_DRU_QUEUE_STATUS_WR_TOP_MAX                                        (0x00000000000001FFU)

#define CSL_DRU_QUEUE_STATUS_WR_TOTAL_MASK                                     (0x000000000003FE00U)
#define CSL_DRU_QUEUE_STATUS_WR_TOTAL_SHIFT                                    (0x0000000000000009U)
#define CSL_DRU_QUEUE_STATUS_WR_TOTAL_RESETVAL                                 (0x0000000000000000U)
#define CSL_DRU_QUEUE_STATUS_WR_TOTAL_MAX                                      (0x00000000000001FFU)

#define CSL_DRU_QUEUE_STATUS_RESETVAL                                          (0x0000000000000000U)

/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint64_t DRU_SHARED_EVT_SET;        /* DRU Shared Event Set Register */
    volatile uint8_t  Resv_64[56];
    volatile uint64_t DRU_COMP_EVT_SET0;         /* DRU Completion Event Set Register */
    volatile uint8_t  Resv_128[56];
    volatile uint64_t DRU_ERR_EVT_SET0;          /* DRU Error Event Set Register */
    volatile uint8_t  Resv_192[56];
    volatile uint64_t DRU_LOCAL_EVT_SET0;        /* DRU Local Event Set Register */
} CSL_dru_setRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_DRU_SET_DRU_SHARED_EVT_SET                                         (0x00000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0                                          (0x00000040U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0                                           (0x00000080U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0                                         (0x000000C0U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* DRU_SHARED_EVT_SET */

#define CSL_DRU_SET_DRU_SHARED_EVT_SET_PROT_ERR_MASK                           (0x0000000000000001U)
#define CSL_DRU_SET_DRU_SHARED_EVT_SET_PROT_ERR_SHIFT                          (0x0000000000000000U)
#define CSL_DRU_SET_DRU_SHARED_EVT_SET_PROT_ERR_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_SHARED_EVT_SET_PROT_ERR_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_SHARED_EVT_SET_RSVD_MASK                               (0xFFFFFFFFFFFFFFFEU)
#define CSL_DRU_SET_DRU_SHARED_EVT_SET_RSVD_SHIFT                              (0x0000000000000001U)
#define CSL_DRU_SET_DRU_SHARED_EVT_SET_RSVD_RESETVAL                           (0x0000000000000000U)
#define CSL_DRU_SET_DRU_SHARED_EVT_SET_RSVD_MAX                                (0x7FFFFFFFFFFFFFFFU)

#define CSL_DRU_SET_DRU_SHARED_EVT_SET_RESETVAL                                (0x0000000000000000U)

/* DRU_COMP_EVT_SET0 */

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT0_MASK                           (0x0000000000000001U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT0_SHIFT                          (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT0_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT0_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT1_MASK                           (0x0000000000000002U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT1_SHIFT                          (0x0000000000000001U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT1_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT1_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT2_MASK                           (0x0000000000000004U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT2_SHIFT                          (0x0000000000000002U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT2_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT2_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT3_MASK                           (0x0000000000000008U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT3_SHIFT                          (0x0000000000000003U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT3_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT3_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT4_MASK                           (0x0000000000000010U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT4_SHIFT                          (0x0000000000000004U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT4_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT4_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT5_MASK                           (0x0000000000000020U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT5_SHIFT                          (0x0000000000000005U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT5_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT5_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT6_MASK                           (0x0000000000000040U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT6_SHIFT                          (0x0000000000000006U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT6_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT6_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT7_MASK                           (0x0000000000000080U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT7_SHIFT                          (0x0000000000000007U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT7_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT7_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT8_MASK                           (0x0000000000000100U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT8_SHIFT                          (0x0000000000000008U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT8_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT8_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT9_MASK                           (0x0000000000000200U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT9_SHIFT                          (0x0000000000000009U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT9_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT9_MAX                            (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT10_MASK                          (0x0000000000000400U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT10_SHIFT                         (0x000000000000000AU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT10_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT10_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT11_MASK                          (0x0000000000000800U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT11_SHIFT                         (0x000000000000000BU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT11_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT11_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT12_MASK                          (0x0000000000001000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT12_SHIFT                         (0x000000000000000CU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT12_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT12_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT13_MASK                          (0x0000000000002000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT13_SHIFT                         (0x000000000000000DU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT13_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT13_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT14_MASK                          (0x0000000000004000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT14_SHIFT                         (0x000000000000000EU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT14_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT14_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT15_MASK                          (0x0000000000008000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT15_SHIFT                         (0x000000000000000FU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT15_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT15_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT16_MASK                          (0x0000000000010000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT16_SHIFT                         (0x0000000000000010U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT16_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT16_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT17_MASK                          (0x0000000000020000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT17_SHIFT                         (0x0000000000000011U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT17_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT17_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT18_MASK                          (0x0000000000040000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT18_SHIFT                         (0x0000000000000012U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT18_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT18_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT19_MASK                          (0x0000000000080000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT19_SHIFT                         (0x0000000000000013U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT19_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT19_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT20_MASK                          (0x0000000000100000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT20_SHIFT                         (0x0000000000000014U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT20_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT20_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT21_MASK                          (0x0000000000200000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT21_SHIFT                         (0x0000000000000015U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT21_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT21_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT22_MASK                          (0x0000000000400000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT22_SHIFT                         (0x0000000000000016U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT22_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT22_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT23_MASK                          (0x0000000000800000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT23_SHIFT                         (0x0000000000000017U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT23_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT23_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT24_MASK                          (0x0000000001000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT24_SHIFT                         (0x0000000000000018U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT24_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT24_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT25_MASK                          (0x0000000002000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT25_SHIFT                         (0x0000000000000019U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT25_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT25_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT26_MASK                          (0x0000000004000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT26_SHIFT                         (0x000000000000001AU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT26_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT26_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT27_MASK                          (0x0000000008000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT27_SHIFT                         (0x000000000000001BU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT27_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT27_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT28_MASK                          (0x0000000010000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT28_SHIFT                         (0x000000000000001CU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT28_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT28_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT29_MASK                          (0x0000000020000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT29_SHIFT                         (0x000000000000001DU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT29_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT29_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT30_MASK                          (0x0000000040000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT30_SHIFT                         (0x000000000000001EU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT30_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT30_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT31_MASK                          (0x0000000080000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT31_SHIFT                         (0x000000000000001FU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT31_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT31_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT32_MASK                          (0x0000000100000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT32_SHIFT                         (0x0000000000000020U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT32_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT32_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT33_MASK                          (0x0000000200000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT33_SHIFT                         (0x0000000000000021U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT33_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT33_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT34_MASK                          (0x0000000400000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT34_SHIFT                         (0x0000000000000022U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT34_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT34_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT35_MASK                          (0x0000000800000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT35_SHIFT                         (0x0000000000000023U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT35_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT35_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT36_MASK                          (0x0000001000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT36_SHIFT                         (0x0000000000000024U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT36_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT36_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT37_MASK                          (0x0000002000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT37_SHIFT                         (0x0000000000000025U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT37_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT37_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT38_MASK                          (0x0000004000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT38_SHIFT                         (0x0000000000000026U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT38_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT38_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT39_MASK                          (0x0000008000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT39_SHIFT                         (0x0000000000000027U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT39_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT39_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT40_MASK                          (0x0000010000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT40_SHIFT                         (0x0000000000000028U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT40_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT40_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT41_MASK                          (0x0000020000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT41_SHIFT                         (0x0000000000000029U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT41_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT41_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT42_MASK                          (0x0000040000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT42_SHIFT                         (0x000000000000002AU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT42_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT42_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT43_MASK                          (0x0000080000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT43_SHIFT                         (0x000000000000002BU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT43_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT43_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT44_MASK                          (0x0000100000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT44_SHIFT                         (0x000000000000002CU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT44_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT44_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT45_MASK                          (0x0000200000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT45_SHIFT                         (0x000000000000002DU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT45_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT45_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT46_MASK                          (0x0000400000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT46_SHIFT                         (0x000000000000002EU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT46_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT46_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT47_MASK                          (0x0000800000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT47_SHIFT                         (0x000000000000002FU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT47_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT47_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT48_MASK                          (0x0001000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT48_SHIFT                         (0x0000000000000030U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT48_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT48_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT49_MASK                          (0x0002000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT49_SHIFT                         (0x0000000000000031U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT49_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT49_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT50_MASK                          (0x0004000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT50_SHIFT                         (0x0000000000000032U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT50_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT50_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT51_MASK                          (0x0008000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT51_SHIFT                         (0x0000000000000033U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT51_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT51_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT52_MASK                          (0x0010000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT52_SHIFT                         (0x0000000000000034U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT52_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT52_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT53_MASK                          (0x0020000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT53_SHIFT                         (0x0000000000000035U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT53_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT53_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT54_MASK                          (0x0040000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT54_SHIFT                         (0x0000000000000036U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT54_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT54_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT55_MASK                          (0x0080000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT55_SHIFT                         (0x0000000000000037U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT55_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT55_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT56_MASK                          (0x0100000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT56_SHIFT                         (0x0000000000000038U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT56_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT56_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT57_MASK                          (0x0200000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT57_SHIFT                         (0x0000000000000039U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT57_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT57_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT58_MASK                          (0x0400000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT58_SHIFT                         (0x000000000000003AU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT58_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT58_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT59_MASK                          (0x0800000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT59_SHIFT                         (0x000000000000003BU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT59_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT59_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT60_MASK                          (0x1000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT60_SHIFT                         (0x000000000000003CU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT60_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT60_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT61_MASK                          (0x2000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT61_SHIFT                         (0x000000000000003DU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT61_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT61_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT62_MASK                          (0x4000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT62_SHIFT                         (0x000000000000003EU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT62_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT62_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT63_MASK                          (0x8000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT63_SHIFT                         (0x000000000000003FU)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT63_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_COMP_EVT_SET0_COMP_EVT63_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_COMP_EVT_SET0_RESETVAL                                 (0x0000000000000000U)

/* DRU_ERR_EVT_SET0 */

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT0_MASK                             (0x0000000000000001U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT0_SHIFT                            (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT0_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT0_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT1_MASK                             (0x0000000000000002U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT1_SHIFT                            (0x0000000000000001U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT1_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT1_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT2_MASK                             (0x0000000000000004U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT2_SHIFT                            (0x0000000000000002U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT2_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT2_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT3_MASK                             (0x0000000000000008U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT3_SHIFT                            (0x0000000000000003U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT3_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT3_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT4_MASK                             (0x0000000000000010U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT4_SHIFT                            (0x0000000000000004U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT4_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT4_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT5_MASK                             (0x0000000000000020U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT5_SHIFT                            (0x0000000000000005U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT5_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT5_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT6_MASK                             (0x0000000000000040U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT6_SHIFT                            (0x0000000000000006U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT6_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT6_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT7_MASK                             (0x0000000000000080U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT7_SHIFT                            (0x0000000000000007U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT7_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT7_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT8_MASK                             (0x0000000000000100U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT8_SHIFT                            (0x0000000000000008U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT8_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT8_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT9_MASK                             (0x0000000000000200U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT9_SHIFT                            (0x0000000000000009U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT9_RESETVAL                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT9_MAX                              (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT10_MASK                            (0x0000000000000400U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT10_SHIFT                           (0x000000000000000AU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT10_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT10_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT11_MASK                            (0x0000000000000800U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT11_SHIFT                           (0x000000000000000BU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT11_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT11_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT12_MASK                            (0x0000000000001000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT12_SHIFT                           (0x000000000000000CU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT12_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT12_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT13_MASK                            (0x0000000000002000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT13_SHIFT                           (0x000000000000000DU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT13_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT13_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT14_MASK                            (0x0000000000004000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT14_SHIFT                           (0x000000000000000EU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT14_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT14_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT15_MASK                            (0x0000000000008000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT15_SHIFT                           (0x000000000000000FU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT15_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT15_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT16_MASK                            (0x0000000000010000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT16_SHIFT                           (0x0000000000000010U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT16_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT16_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT17_MASK                            (0x0000000000020000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT17_SHIFT                           (0x0000000000000011U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT17_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT17_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT18_MASK                            (0x0000000000040000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT18_SHIFT                           (0x0000000000000012U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT18_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT18_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT19_MASK                            (0x0000000000080000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT19_SHIFT                           (0x0000000000000013U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT19_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT19_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT20_MASK                            (0x0000000000100000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT20_SHIFT                           (0x0000000000000014U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT20_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT20_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT21_MASK                            (0x0000000000200000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT21_SHIFT                           (0x0000000000000015U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT21_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT21_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT22_MASK                            (0x0000000000400000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT22_SHIFT                           (0x0000000000000016U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT22_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT22_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT23_MASK                            (0x0000000000800000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT23_SHIFT                           (0x0000000000000017U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT23_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT23_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT24_MASK                            (0x0000000001000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT24_SHIFT                           (0x0000000000000018U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT24_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT24_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT25_MASK                            (0x0000000002000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT25_SHIFT                           (0x0000000000000019U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT25_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT25_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT26_MASK                            (0x0000000004000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT26_SHIFT                           (0x000000000000001AU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT26_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT26_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT27_MASK                            (0x0000000008000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT27_SHIFT                           (0x000000000000001BU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT27_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT27_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT28_MASK                            (0x0000000010000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT28_SHIFT                           (0x000000000000001CU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT28_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT28_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT29_MASK                            (0x0000000020000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT29_SHIFT                           (0x000000000000001DU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT29_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT29_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT30_MASK                            (0x0000000040000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT30_SHIFT                           (0x000000000000001EU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT30_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT30_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT31_MASK                            (0x0000000080000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT31_SHIFT                           (0x000000000000001FU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT31_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT31_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT32_MASK                            (0x0000000100000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT32_SHIFT                           (0x0000000000000020U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT32_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT32_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT33_MASK                            (0x0000000200000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT33_SHIFT                           (0x0000000000000021U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT33_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT33_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT34_MASK                            (0x0000000400000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT34_SHIFT                           (0x0000000000000022U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT34_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT34_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT35_MASK                            (0x0000000800000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT35_SHIFT                           (0x0000000000000023U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT35_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT35_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT36_MASK                            (0x0000001000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT36_SHIFT                           (0x0000000000000024U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT36_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT36_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT37_MASK                            (0x0000002000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT37_SHIFT                           (0x0000000000000025U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT37_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT37_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT38_MASK                            (0x0000004000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT38_SHIFT                           (0x0000000000000026U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT38_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT38_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT39_MASK                            (0x0000008000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT39_SHIFT                           (0x0000000000000027U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT39_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT39_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT40_MASK                            (0x0000010000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT40_SHIFT                           (0x0000000000000028U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT40_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT40_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT41_MASK                            (0x0000020000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT41_SHIFT                           (0x0000000000000029U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT41_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT41_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT42_MASK                            (0x0000040000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT42_SHIFT                           (0x000000000000002AU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT42_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT42_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT43_MASK                            (0x0000080000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT43_SHIFT                           (0x000000000000002BU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT43_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT43_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT44_MASK                            (0x0000100000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT44_SHIFT                           (0x000000000000002CU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT44_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT44_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT45_MASK                            (0x0000200000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT45_SHIFT                           (0x000000000000002DU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT45_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT45_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT46_MASK                            (0x0000400000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT46_SHIFT                           (0x000000000000002EU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT46_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT46_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT47_MASK                            (0x0000800000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT47_SHIFT                           (0x000000000000002FU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT47_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT47_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT48_MASK                            (0x0001000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT48_SHIFT                           (0x0000000000000030U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT48_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT48_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT49_MASK                            (0x0002000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT49_SHIFT                           (0x0000000000000031U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT49_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT49_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT50_MASK                            (0x0004000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT50_SHIFT                           (0x0000000000000032U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT50_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT50_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT51_MASK                            (0x0008000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT51_SHIFT                           (0x0000000000000033U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT51_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT51_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT52_MASK                            (0x0010000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT52_SHIFT                           (0x0000000000000034U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT52_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT52_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT53_MASK                            (0x0020000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT53_SHIFT                           (0x0000000000000035U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT53_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT53_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT54_MASK                            (0x0040000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT54_SHIFT                           (0x0000000000000036U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT54_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT54_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT55_MASK                            (0x0080000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT55_SHIFT                           (0x0000000000000037U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT55_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT55_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT56_MASK                            (0x0100000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT56_SHIFT                           (0x0000000000000038U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT56_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT56_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT57_MASK                            (0x0200000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT57_SHIFT                           (0x0000000000000039U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT57_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT57_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT58_MASK                            (0x0400000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT58_SHIFT                           (0x000000000000003AU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT58_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT58_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT59_MASK                            (0x0800000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT59_SHIFT                           (0x000000000000003BU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT59_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT59_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT60_MASK                            (0x1000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT60_SHIFT                           (0x000000000000003CU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT60_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT60_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT61_MASK                            (0x2000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT61_SHIFT                           (0x000000000000003DU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT61_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT61_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT62_MASK                            (0x4000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT62_SHIFT                           (0x000000000000003EU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT62_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT62_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT63_MASK                            (0x8000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT63_SHIFT                           (0x000000000000003FU)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT63_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_SET_DRU_ERR_EVT_SET0_ERR_EVT63_MAX                             (0x0000000000000001U)

#define CSL_DRU_SET_DRU_ERR_EVT_SET0_RESETVAL                                  (0x0000000000000000U)

/* DRU_LOCAL_EVT_SET0 */

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT0_MASK                          (0x0000000000000001U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT0_SHIFT                         (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT0_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT0_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT1_MASK                          (0x0000000000000002U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT1_SHIFT                         (0x0000000000000001U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT1_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT1_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT2_MASK                          (0x0000000000000004U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT2_SHIFT                         (0x0000000000000002U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT2_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT2_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT3_MASK                          (0x0000000000000008U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT3_SHIFT                         (0x0000000000000003U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT3_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT3_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT4_MASK                          (0x0000000000000010U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT4_SHIFT                         (0x0000000000000004U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT4_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT4_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT5_MASK                          (0x0000000000000020U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT5_SHIFT                         (0x0000000000000005U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT5_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT5_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT6_MASK                          (0x0000000000000040U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT6_SHIFT                         (0x0000000000000006U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT6_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT6_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT7_MASK                          (0x0000000000000080U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT7_SHIFT                         (0x0000000000000007U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT7_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT7_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT8_MASK                          (0x0000000000000100U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT8_SHIFT                         (0x0000000000000008U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT8_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT8_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT9_MASK                          (0x0000000000000200U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT9_SHIFT                         (0x0000000000000009U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT9_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT9_MAX                           (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT10_MASK                         (0x0000000000000400U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT10_SHIFT                        (0x000000000000000AU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT10_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT10_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT11_MASK                         (0x0000000000000800U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT11_SHIFT                        (0x000000000000000BU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT11_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT11_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT12_MASK                         (0x0000000000001000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT12_SHIFT                        (0x000000000000000CU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT12_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT12_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT13_MASK                         (0x0000000000002000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT13_SHIFT                        (0x000000000000000DU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT13_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT13_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT14_MASK                         (0x0000000000004000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT14_SHIFT                        (0x000000000000000EU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT14_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT14_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT15_MASK                         (0x0000000000008000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT15_SHIFT                        (0x000000000000000FU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT15_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT15_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT16_MASK                         (0x0000000000010000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT16_SHIFT                        (0x0000000000000010U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT16_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT16_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT17_MASK                         (0x0000000000020000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT17_SHIFT                        (0x0000000000000011U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT17_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT17_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT18_MASK                         (0x0000000000040000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT18_SHIFT                        (0x0000000000000012U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT18_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT18_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT19_MASK                         (0x0000000000080000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT19_SHIFT                        (0x0000000000000013U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT19_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT19_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT20_MASK                         (0x0000000000100000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT20_SHIFT                        (0x0000000000000014U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT20_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT20_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT21_MASK                         (0x0000000000200000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT21_SHIFT                        (0x0000000000000015U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT21_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT21_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT22_MASK                         (0x0000000000400000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT22_SHIFT                        (0x0000000000000016U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT22_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT22_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT23_MASK                         (0x0000000000800000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT23_SHIFT                        (0x0000000000000017U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT23_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT23_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT24_MASK                         (0x0000000001000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT24_SHIFT                        (0x0000000000000018U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT24_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT24_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT25_MASK                         (0x0000000002000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT25_SHIFT                        (0x0000000000000019U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT25_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT25_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT26_MASK                         (0x0000000004000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT26_SHIFT                        (0x000000000000001AU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT26_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT26_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT27_MASK                         (0x0000000008000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT27_SHIFT                        (0x000000000000001BU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT27_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT27_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT28_MASK                         (0x0000000010000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT28_SHIFT                        (0x000000000000001CU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT28_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT28_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT29_MASK                         (0x0000000020000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT29_SHIFT                        (0x000000000000001DU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT29_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT29_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT30_MASK                         (0x0000000040000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT30_SHIFT                        (0x000000000000001EU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT30_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT30_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT31_MASK                         (0x0000000080000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT31_SHIFT                        (0x000000000000001FU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT31_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT31_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT32_MASK                         (0x0000000100000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT32_SHIFT                        (0x0000000000000020U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT32_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT32_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT33_MASK                         (0x0000000200000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT33_SHIFT                        (0x0000000000000021U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT33_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT33_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT34_MASK                         (0x0000000400000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT34_SHIFT                        (0x0000000000000022U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT34_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT34_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT35_MASK                         (0x0000000800000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT35_SHIFT                        (0x0000000000000023U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT35_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT35_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT36_MASK                         (0x0000001000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT36_SHIFT                        (0x0000000000000024U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT36_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT36_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT37_MASK                         (0x0000002000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT37_SHIFT                        (0x0000000000000025U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT37_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT37_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT38_MASK                         (0x0000004000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT38_SHIFT                        (0x0000000000000026U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT38_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT38_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT39_MASK                         (0x0000008000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT39_SHIFT                        (0x0000000000000027U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT39_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT39_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT40_MASK                         (0x0000010000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT40_SHIFT                        (0x0000000000000028U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT40_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT40_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT41_MASK                         (0x0000020000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT41_SHIFT                        (0x0000000000000029U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT41_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT41_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT42_MASK                         (0x0000040000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT42_SHIFT                        (0x000000000000002AU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT42_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT42_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT43_MASK                         (0x0000080000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT43_SHIFT                        (0x000000000000002BU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT43_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT43_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT44_MASK                         (0x0000100000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT44_SHIFT                        (0x000000000000002CU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT44_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT44_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT45_MASK                         (0x0000200000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT45_SHIFT                        (0x000000000000002DU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT45_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT45_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT46_MASK                         (0x0000400000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT46_SHIFT                        (0x000000000000002EU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT46_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT46_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT47_MASK                         (0x0000800000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT47_SHIFT                        (0x000000000000002FU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT47_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT47_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT48_MASK                         (0x0001000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT48_SHIFT                        (0x0000000000000030U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT48_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT48_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT49_MASK                         (0x0002000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT49_SHIFT                        (0x0000000000000031U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT49_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT49_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT50_MASK                         (0x0004000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT50_SHIFT                        (0x0000000000000032U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT50_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT50_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT51_MASK                         (0x0008000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT51_SHIFT                        (0x0000000000000033U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT51_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT51_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT52_MASK                         (0x0010000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT52_SHIFT                        (0x0000000000000034U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT52_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT52_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT53_MASK                         (0x0020000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT53_SHIFT                        (0x0000000000000035U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT53_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT53_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT54_MASK                         (0x0040000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT54_SHIFT                        (0x0000000000000036U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT54_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT54_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT55_MASK                         (0x0080000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT55_SHIFT                        (0x0000000000000037U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT55_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT55_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT56_MASK                         (0x0100000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT56_SHIFT                        (0x0000000000000038U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT56_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT56_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT57_MASK                         (0x0200000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT57_SHIFT                        (0x0000000000000039U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT57_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT57_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT58_MASK                         (0x0400000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT58_SHIFT                        (0x000000000000003AU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT58_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT58_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT59_MASK                         (0x0800000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT59_SHIFT                        (0x000000000000003BU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT59_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT59_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT60_MASK                         (0x1000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT60_SHIFT                        (0x000000000000003CU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT60_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT60_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT61_MASK                         (0x2000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT61_SHIFT                        (0x000000000000003DU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT61_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT61_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT62_MASK                         (0x4000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT62_SHIFT                        (0x000000000000003EU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT62_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT62_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT63_MASK                         (0x8000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT63_SHIFT                        (0x000000000000003FU)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT63_RESETVAL                     (0x0000000000000000U)
#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_COMP_EVT63_MAX                          (0x0000000000000001U)

#define CSL_DRU_SET_DRU_LOCAL_EVT_SET0_RESETVAL                                (0x0000000000000000U)

/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint64_t CFG;                       /* Channel Configuration Register. The Channel Configuration Register is used to initialize static mode settings for the DMA Channel. The register may only be written when the chanel is disable in the ch_enable field in the REALTIME CONTROL register is 0. */
    volatile uint8_t  Resv_32[24];
    volatile uint64_t CHOES0;                    /* The Output Event Steering Registers are used to specify a global event number to generate anytime the required event generation criteria specified in a TR are met. A single event with the event number set equal to the value in the corresponding register will be generated.  This register is provided in order to allow security SW to lock down which events in the global space any given channel/ thread is allowed to generate */
    volatile uint8_t  Resv_64[24];
    volatile uint64_t CHRING_ADDR;               /* Ring Base Address Register */
    volatile uint64_t SIZE;                      /* Ring Size Register */
    volatile uint8_t  Resv_96[16];
    volatile uint64_t CHST_SCHED;                /* Channel Static Scheduler Config Register */
    volatile uint8_t  Resv_256[152];
} CSL_DRU_CHNRTRegs_CHNRT;


typedef struct {
    CSL_DRU_CHNRTRegs_CHNRT CHNRT[512];
} CSL_dru_chnrtRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_DRU_CHNRT_CFG(CHNRT)                                         (0x00000000U+((CHNRT)*0x100U))
#define CSL_DRU_CHNRT_CHOES0(CHNRT)                                      (0x00000020U+((CHNRT)*0x100U))
#define CSL_DRU_CHNRT_CHRING_ADDR(CHNRT)                                 (0x00000040U+((CHNRT)*0x100U))
#define CSL_DRU_CHNRT_SIZE(CHNRT)                                        (0x00000048U+((CHNRT)*0x100U))
#define CSL_DRU_CHNRT_CHST_SCHED(CHNRT)                                  (0x00000060U+((CHNRT)*0x100U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CFG */

#define CSL_DRU_CHNRT_CFG_CHAN_TYPE_MASK                                 (0x0000000000070000U)
#define CSL_DRU_CHNRT_CFG_CHAN_TYPE_SHIFT                                (0x0000000000000010U)
#define CSL_DRU_CHNRT_CFG_CHAN_TYPE_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CHNRT_CFG_CHAN_TYPE_MAX                                  (0x0000000000000007U)

#define CSL_DRU_CHNRT_CFG_CHAN_TYPE_OWNER_MASK                           (0x0000000000080000U)
#define CSL_DRU_CHNRT_CFG_CHAN_TYPE_OWNER_SHIFT                          (0x0000000000000013U)
#define CSL_DRU_CHNRT_CFG_CHAN_TYPE_OWNER_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_CHNRT_CFG_CHAN_TYPE_OWNER_MAX                            (0x0000000000000001U)

#define CSL_DRU_CHNRT_CFG_PAUSE_ON_ERR_MASK                              (0x0000000080000000U)
#define CSL_DRU_CHNRT_CFG_PAUSE_ON_ERR_SHIFT                             (0x000000000000001FU)
#define CSL_DRU_CHNRT_CFG_PAUSE_ON_ERR_RESETVAL                          (0x0000000000000000U)
#define CSL_DRU_CHNRT_CFG_PAUSE_ON_ERR_MAX                               (0x0000000000000001U)

#define CSL_DRU_CHNRT_CFG_RSVD_MASK                                      (0xFFFFFFFF00000000U)
#define CSL_DRU_CHNRT_CFG_RSVD_SHIFT                                     (0x0000000000000020U)
#define CSL_DRU_CHNRT_CFG_RSVD_RESETVAL                                  (0x0000000000000000U)
#define CSL_DRU_CHNRT_CFG_RSVD_MAX                                       (0x00000000FFFFFFFFU)

#define CSL_DRU_CHNRT_CFG_RESETVAL                                       (0x0000000000000000U)

/* CHOES0 */

#define CSL_DRU_CHNRT_CHOES0_EVT_NUM_MASK                                (0x000000000000FFFFU)
#define CSL_DRU_CHNRT_CHOES0_EVT_NUM_SHIFT                               (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHOES0_EVT_NUM_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHOES0_EVT_NUM_MAX                                 (0x000000000000FFFFU)

#define CSL_DRU_CHNRT_CHOES0_FRING_EVT_NUM_MASK                          (0x00000000FFFF0000U)
#define CSL_DRU_CHNRT_CHOES0_FRING_EVT_NUM_SHIFT                         (0x0000000000000010U)
#define CSL_DRU_CHNRT_CHOES0_FRING_EVT_NUM_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHOES0_FRING_EVT_NUM_MAX                           (0x000000000000FFFFU)

#define CSL_DRU_CHNRT_CHOES0_RRING_EVT_NUM_MASK                          (0x0000FFFF00000000U)
#define CSL_DRU_CHNRT_CHOES0_RRING_EVT_NUM_SHIFT                         (0x0000000000000020U)
#define CSL_DRU_CHNRT_CHOES0_RRING_EVT_NUM_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHOES0_RRING_EVT_NUM_MAX                           (0x000000000000FFFFU)

#define CSL_DRU_CHNRT_CHOES0_RSVD_MASK                                   (0xFFFF000000000000U)
#define CSL_DRU_CHNRT_CHOES0_RSVD_SHIFT                                  (0x0000000000000030U)
#define CSL_DRU_CHNRT_CHOES0_RSVD_RESETVAL                               (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHOES0_RSVD_MAX                                    (0x000000000000FFFFU)

#define CSL_DRU_CHNRT_CHOES0_RESETVAL                                    (0x0000000000000000U)

/* CHRING_ADDR */

#define CSL_DRU_CHNRT_CHRING_ADDR_ADDR_MASK                              (0x0000000FFFFFFFFFU)
#define CSL_DRU_CHNRT_CHRING_ADDR_ADDR_SHIFT                             (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHRING_ADDR_ADDR_RESETVAL                          (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHRING_ADDR_ADDR_MAX                               (0x0000000FFFFFFFFFU)

#define CSL_DRU_CHNRT_CHRING_ADDR_ASEL_MASK                              (0x000F000000000000U)
#define CSL_DRU_CHNRT_CHRING_ADDR_ASEL_SHIFT                             (0x0000000000000030U)
#define CSL_DRU_CHNRT_CHRING_ADDR_ASEL_RESETVAL                          (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHRING_ADDR_ASEL_MAX                               (0x000000000000000FU)

#define CSL_DRU_CHNRT_CHRING_ADDR_RESETVAL                               (0x0000000000000000U)

/* SIZE */

#define CSL_DRU_CHNRT_SIZE_QMODE_MASK                                    (0x00000000E0000000U)
#define CSL_DRU_CHNRT_SIZE_QMODE_SHIFT                                   (0x000000000000001DU)
#define CSL_DRU_CHNRT_SIZE_QMODE_RESETVAL                                (0x0000000000000001U)
#define CSL_DRU_CHNRT_SIZE_QMODE_MAX                                     (0x0000000000000007U)

#define CSL_DRU_CHNRT_SIZE_QMODE_VAL_DRING_MODE                          (0x1U)

#define CSL_DRU_CHNRT_SIZE_ELSIZE_MASK                                   (0x0000000007000000U)
#define CSL_DRU_CHNRT_SIZE_ELSIZE_SHIFT                                  (0x0000000000000018U)
#define CSL_DRU_CHNRT_SIZE_ELSIZE_RESETVAL                               (0x0000000000000001U)
#define CSL_DRU_CHNRT_SIZE_ELSIZE_MAX                                    (0x0000000000000007U)

#define CSL_DRU_CHNRT_SIZE_ELCNT_MASK                                    (0x000000000000FFFFU)
#define CSL_DRU_CHNRT_SIZE_ELCNT_SHIFT                                   (0x0000000000000000U)
#define CSL_DRU_CHNRT_SIZE_ELCNT_RESETVAL                                (0x0000000000000000U)
#define CSL_DRU_CHNRT_SIZE_ELCNT_MAX                                     (0x000000000000FFFFU)

#define CSL_DRU_CHNRT_SIZE_RESETVAL                                      (0x0000000021000000U)

/* CHST_SCHED */

#define CSL_DRU_CHNRT_CHST_SCHED_QUEUE_MASK                              (0x0000000000000003U)
#define CSL_DRU_CHNRT_CHST_SCHED_QUEUE_SHIFT                             (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHST_SCHED_QUEUE_RESETVAL                          (0x0000000000000000U)
#define CSL_DRU_CHNRT_CHST_SCHED_QUEUE_MAX                               (0x0000000000000003U)

#define CSL_DRU_CHNRT_CHST_SCHED_RESETVAL                                (0x0000000000000000U)

/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint64_t CHRT_CTL;                  /* The channel realtime control register contains real-time cotrol and status information for the DMA Channel. The fields in this regsiter can be changed while the channel is in operation. */
    volatile uint64_t CHRT_SWTRIG;               /* The Software Trigger Register provides a mechanism by which software can directly trigger the channel in a secure way. */
    volatile uint64_t CHRT_STATUS_DET;           /* The channel status details */
    volatile uint64_t CHRT_STATUS_CNT;           /* The channel count details */
    volatile uint64_t RING_FWD_DB;               /* Realtime Ring N Forward Doorbell Register */
    volatile uint64_t RING_FWD_OCC;              /* Realtime Ring N Forward Occupancy Register */
    volatile uint8_t  Resv_64[16];
    volatile uint64_t RING_RVRS_DB;              /* Realtime Ring N Reverse Doorbell Register */
    volatile uint64_t RING_RCVS_OCC;             /* Realtime Ring N Reverse Occupancy Register */
    volatile uint8_t  Resv_256[176];
} CSL_DRU_CHRTRegs_CHRT;


typedef struct {
    CSL_DRU_CHRTRegs_CHRT CHRT[64];
} CSL_dru_chrtRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_DRU_CHRT_CTL(CHRT)                                       (0x00000000U+((CHRT)*0x100U))
#define CSL_DRU_CHRT_SWTRIG(CHRT)                                    (0x00000008U+((CHRT)*0x100U))
#define CSL_DRU_CHRT_STATUS_DET(CHRT)                                (0x00000010U+((CHRT)*0x100U))
#define CSL_DRU_CHRT_STATUS_CNT(CHRT)                                (0x00000018U+((CHRT)*0x100U))
#define CSL_DRU_CHRT_CHRT_RING_FWD_DB(CHRT)                                    (0x00000020U+((CHRT)*0x100U))
#define CSL_DRU_CHRT_CHRT_RING_FWD_OCC(CHRT)                                   (0x00000028U+((CHRT)*0x100U))
#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB(CHRT)                                   (0x00000040U+((CHRT)*0x100U))
#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC(CHRT)                                  (0x00000048U+((CHRT)*0x100U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CHRT_CTL */

#define CSL_DRU_CHRT_CTL_ENABLE_MASK                                 (0x0000000080000000U)
#define CSL_DRU_CHRT_CTL_ENABLE_SHIFT                                (0x000000000000001FU)
#define CSL_DRU_CHRT_CTL_ENABLE_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CHRT_CTL_ENABLE_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CHRT_CTL_PAUSE_MASK                                  (0x0000000020000000U)
#define CSL_DRU_CHRT_CTL_PAUSE_SHIFT                                 (0x000000000000001DU)
#define CSL_DRU_CHRT_CTL_PAUSE_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CHRT_CTL_PAUSE_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CHRT_CTL_RSVD_MASK                                   (0xFFFFFFFF00000000U)
#define CSL_DRU_CHRT_CTL_RSVD_SHIFT                                  (0x0000000000000020U)
#define CSL_DRU_CHRT_CTL_RSVD_RESETVAL                               (0x0000000000000000U)
#define CSL_DRU_CHRT_CTL_RSVD_MAX                                    (0x00000000FFFFFFFFU)

#define CSL_DRU_CHRT_CTL_TEARDOWN_MASK                               (0x0000000040000000U)
#define CSL_DRU_CHRT_CTL_TEARDOWN_SHIFT                              (0x000000000000001EU)
#define CSL_DRU_CHRT_CTL_TEARDOWN_RESETVAL                           (0x0000000000000000U)
#define CSL_DRU_CHRT_CTL_TEARDOWN_MAX                                (0x0000000000000001U)

#define CSL_DRU_CHRT_CTL_FORCED_TEARDOWN_MASK                        (0x0000000010000000U)
#define CSL_DRU_CHRT_CTL_FORCED_TEARDOWN_SHIFT                       (0x000000000000001CU)
#define CSL_DRU_CHRT_CTL_FORCED_TEARDOWN_RESETVAL                    (0x0000000000000000U)
#define CSL_DRU_CHRT_CTL_FORCED_TEARDOWN_MAX                         (0x0000000000000001U)

#define CSL_DRU_CHRT_CTL_RESETVAL                                    (0x0000000000000000U)

/* CHRT_SWTRIG */

#define CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER0_MASK                     (0x0000000000000001U)
#define CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER0_SHIFT                    (0x0000000000000000U)
#define CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER0_RESETVAL                 (0x0000000000000000U)
#define CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER0_MAX                      (0x0000000000000001U)

#define CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER1_MASK                     (0x0000000000000002U)
#define CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER1_SHIFT                    (0x0000000000000001U)
#define CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER1_RESETVAL                 (0x0000000000000000U)
#define CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER1_MAX                      (0x0000000000000001U)

#define CSL_DRU_CHRT_SWTRIG_LOCAL_TRIGGER0_MASK                      (0x0000000000000004U)
#define CSL_DRU_CHRT_SWTRIG_LOCAL_TRIGGER0_SHIFT                     (0x0000000000000002U)
#define CSL_DRU_CHRT_SWTRIG_LOCAL_TRIGGER0_RESETVAL                  (0x0000000000000000U)
#define CSL_DRU_CHRT_SWTRIG_LOCAL_TRIGGER0_MAX                       (0x0000000000000001U)

#define CSL_DRU_CHRT_SWTRIG_RSVD_MASK                                (0xFFFFFFFFFFFFFFF8U)
#define CSL_DRU_CHRT_SWTRIG_RSVD_SHIFT                               (0x0000000000000003U)
#define CSL_DRU_CHRT_SWTRIG_RSVD_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CHRT_SWTRIG_RSVD_MAX                                 (0x1FFFFFFFFFFFFFFFU)

#define CSL_DRU_CHRT_SWTRIG_RESETVAL                                 (0x0000000000000000U)

/* CHRT_STATUS_DET */

#define CSL_DRU_CHRT_STATUS_DET_STATUS_TYPE_MASK                     (0x000000000000000FU)
#define CSL_DRU_CHRT_STATUS_DET_STATUS_TYPE_SHIFT                    (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_STATUS_TYPE_RESETVAL                 (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_STATUS_TYPE_MAX                      (0x000000000000000FU)

#define CSL_DRU_CHRT_STATUS_DET_INFO_MASK                            (0x00000000000000F0U)
#define CSL_DRU_CHRT_STATUS_DET_INFO_SHIFT                           (0x0000000000000004U)
#define CSL_DRU_CHRT_STATUS_DET_INFO_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_INFO_MAX                             (0x000000000000000FU)

#define CSL_DRU_CHRT_STATUS_DET_CMD_ID_MASK                          (0x000000000000FF00U)
#define CSL_DRU_CHRT_STATUS_DET_CMD_ID_SHIFT                         (0x0000000000000008U)
#define CSL_DRU_CHRT_STATUS_DET_CMD_ID_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_CMD_ID_MAX                           (0x00000000000000FFU)

#define CSL_DRU_CHRT_STATUS_DET_TR_CNT_MASK                          (0x0000000000FF0000U)
#define CSL_DRU_CHRT_STATUS_DET_TR_CNT_SHIFT                         (0x0000000000000010U)
#define CSL_DRU_CHRT_STATUS_DET_TR_CNT_RESETVAL                      (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_TR_CNT_MAX                           (0x00000000000000FFU)

#define CSL_DRU_CHRT_STATUS_DET_TR_IN_QUEUE_CNT_MASK                 (0x00000000FF000000U)
#define CSL_DRU_CHRT_STATUS_DET_TR_IN_QUEUE_CNT_SHIFT                (0x0000000000000018U)
#define CSL_DRU_CHRT_STATUS_DET_TR_IN_QUEUE_CNT_RESETVAL             (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_TR_IN_QUEUE_CNT_MAX                  (0x00000000000000FFU)

#define CSL_DRU_CHRT_STATUS_DET_RSVD_MASK                            (0x1FFFFFFF00000000U)
#define CSL_DRU_CHRT_STATUS_DET_RSVD_SHIFT                           (0x0000000000000020U)
#define CSL_DRU_CHRT_STATUS_DET_RSVD_RESETVAL                        (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_RSVD_MAX                             (0x000000001FFFFFFFU)

#define CSL_DRU_CHRT_STATUS_DET_RD_ACTIVE_MASK                       (0x2000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_RD_ACTIVE_SHIFT                      (0x000000000000003DU)
#define CSL_DRU_CHRT_STATUS_DET_RD_ACTIVE_RESETVAL                   (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_RD_ACTIVE_MAX                        (0x0000000000000001U)

#define CSL_DRU_CHRT_STATUS_DET_WR_ACTIVE_MASK                       (0x4000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_WR_ACTIVE_SHIFT                      (0x000000000000003EU)
#define CSL_DRU_CHRT_STATUS_DET_WR_ACTIVE_RESETVAL                   (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_WR_ACTIVE_MAX                        (0x0000000000000001U)

#define CSL_DRU_CHRT_STATUS_DET_CH_ACTIVE_MASK                       (0x8000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_CH_ACTIVE_SHIFT                      (0x000000000000003FU)
#define CSL_DRU_CHRT_STATUS_DET_CH_ACTIVE_RESETVAL                   (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_DET_CH_ACTIVE_MAX                        (0x0000000000000001U)

#define CSL_DRU_CHRT_STATUS_DET_RESETVAL                             (0x0000000000000000U)

/* CHRT_STATUS_CNT */

#define CSL_DRU_CHRT_STATUS_CNT_ICNT0_MASK                           (0x000000000000FFFFU)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT0_SHIFT                          (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT0_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT0_MAX                            (0x000000000000FFFFU)

#define CSL_DRU_CHRT_STATUS_CNT_ICNT1_MASK                           (0x00000000FFFF0000U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT1_SHIFT                          (0x0000000000000010U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT1_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT1_MAX                            (0x000000000000FFFFU)

#define CSL_DRU_CHRT_STATUS_CNT_ICNT2_MASK                           (0x0000FFFF00000000U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT2_SHIFT                          (0x0000000000000020U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT2_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT2_MAX                            (0x000000000000FFFFU)

#define CSL_DRU_CHRT_STATUS_CNT_ICNT3_MASK                           (0xFFFF000000000000U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT3_SHIFT                          (0x0000000000000030U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT3_RESETVAL                       (0x0000000000000000U)
#define CSL_DRU_CHRT_STATUS_CNT_ICNT3_MAX                            (0x000000000000FFFFU)

#define CSL_DRU_CHRT_STATUS_CNT_RESETVAL                             (0x0000000000000000U)

/* RING_FWD_DB */

#define CSL_DRU_CHRT_CHRT_RING_FWD_DB_CNT_MASK                                 (0x00000000000000FFU)
#define CSL_DRU_CHRT_CHRT_RING_FWD_DB_CNT_SHIFT                                (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_FWD_DB_CNT_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_FWD_DB_CNT_MAX                                  (0x00000000000000FFU)

#define CSL_DRU_CHRT_CHRT_RING_FWD_DB_RESETVAL                                 (0x0000000000000000U)

/* RING_FWD_OCC */

#define CSL_DRU_CHRT_CHRT_RING_FWD_OCC_CNT_MASK                                (0x000000000001FFFFU)
#define CSL_DRU_CHRT_CHRT_RING_FWD_OCC_CNT_SHIFT                               (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_FWD_OCC_CNT_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_FWD_OCC_CNT_MAX                                 (0x000000000001FFFFU)

#define CSL_DRU_CHRT_CHRT_RING_FWD_OCC_RESETVAL                                (0x0000000000000000U)

/* RING_RVRS_DB */

#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB_ACK_MASK                                (0x0000000080000000U)
#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB_ACK_SHIFT                               (0x000000000000001FU)
#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB_ACK_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB_ACK_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB_CNT_MASK                                (0x00000000000000FFU)
#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB_CNT_SHIFT                               (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB_CNT_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB_CNT_MAX                                 (0x00000000000000FFU)

#define CSL_DRU_CHRT_CHRT_RING_RVRS_DB_RESETVAL                                (0x0000000000000000U)

/* RING_RCVS_OCC */

#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC_COMP_MASK                              (0x0000000080000000U)
#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC_COMP_SHIFT                             (0x000000000000001FU)
#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC_COMP_RESETVAL                          (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC_COMP_MAX                               (0x0000000000000001U)

#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC_CNT_MASK                               (0x000000000001FFFFU)
#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC_CNT_SHIFT                              (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC_CNT_RESETVAL                           (0x0000000000000000U)
#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC_CNT_MAX                                (0x000000000001FFFFU)

#define CSL_DRU_CHRT_CHRT_RING_RCVS_OCC_RESETVAL                               (0x0000000000000000U)

/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint64_t NEXT_TR_WORD0_1;           /* The first TR submission word */
    volatile uint64_t NEXT_TR_WORD2_3;           /* The second TR submission word */
    volatile uint64_t NEXT_TR_WORD4_5;           /* The third TR submission word */
    volatile uint64_t NEXT_TR_WORD6_7;           /* The fourth TR submission word */
    volatile uint64_t NEXT_TR_WORD8_9;           /* The fifth TR submission word */
    volatile uint64_t NEXT_TR_WORD10_11;         /* The sixth TR submission word */
    volatile uint64_t NEXT_TR_WORD12_13;         /* The seventh TR submission word */
    volatile uint64_t NEXT_TR_WORD14_15;         /* The eight TR submission word */
} CSL_dru_atomicRegs_CHATOMIC_DEBUG_DEBUG;


typedef struct {
    volatile uint64_t ATOMIC_SUBMIT_CURR_TR_WORD0_1;   /* The first TR submission word */
    volatile uint64_t ATOMIC_SUBMIT_CURR_TR_WORD2_3;   /* The second TR submission word */
    volatile uint64_t ATOMIC_SUBMIT_CURR_TR_WORD4_5;   /* The third TR submission word */
    volatile uint64_t ATOMIC_SUBMIT_CURR_TR_WORD6_7;   /* The fourth TR submission word */
    volatile uint64_t ATOMIC_SUBMIT_CURR_TR_WORD8_9;   /* The fifth TR submission word */
    volatile uint64_t ATOMIC_SUBMIT_CURR_TR_WORD10_11;   /* The sixth TR submission word */
    volatile uint64_t ATOMIC_SUBMIT_CURR_TR_WORD12_13;   /* The seventh TR submission word */
    volatile uint64_t ATOMIC_SUBMIT_CURR_TR_WORD14_15;   /* The eight TR submission word */
    CSL_dru_atomicRegs_CHATOMIC_DEBUG_DEBUG DEBUG[3];
} CSL_dru_atomicRegs_CHATOMIC_DEBUG;


typedef struct {
    CSL_dru_atomicRegs_CHATOMIC_DEBUG CHATOMIC_DEBUG[64];
} CSL_dru_atomicRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1(CHATOMIC_DEBUG) (0x00000000U+((CHATOMIC_DEBUG)*0x100U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3(CHATOMIC_DEBUG) (0x00000008U+((CHATOMIC_DEBUG)*0x100U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5(CHATOMIC_DEBUG) (0x00000010U+((CHATOMIC_DEBUG)*0x100U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7(CHATOMIC_DEBUG) (0x00000018U+((CHATOMIC_DEBUG)*0x100U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9(CHATOMIC_DEBUG) (0x00000020U+((CHATOMIC_DEBUG)*0x100U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11(CHATOMIC_DEBUG) (0x00000028U+((CHATOMIC_DEBUG)*0x100U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13(CHATOMIC_DEBUG) (0x00000030U+((CHATOMIC_DEBUG)*0x100U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15(CHATOMIC_DEBUG) (0x00000038U+((CHATOMIC_DEBUG)*0x100U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1(CHATOMIC_DEBUG, DEBUG) (0x00000040U+((CHATOMIC_DEBUG)*0x100U)+((DEBUG)*0x40U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3(CHATOMIC_DEBUG, DEBUG) (0x00000048U+((CHATOMIC_DEBUG)*0x100U)+((DEBUG)*0x40U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5(CHATOMIC_DEBUG, DEBUG) (0x00000050U+((CHATOMIC_DEBUG)*0x100U)+((DEBUG)*0x40U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7(CHATOMIC_DEBUG, DEBUG) (0x00000058U+((CHATOMIC_DEBUG)*0x100U)+((DEBUG)*0x40U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9(CHATOMIC_DEBUG, DEBUG) (0x00000060U+((CHATOMIC_DEBUG)*0x100U)+((DEBUG)*0x40U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11(CHATOMIC_DEBUG, DEBUG) (0x00000068U+((CHATOMIC_DEBUG)*0x100U)+((DEBUG)*0x40U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13(CHATOMIC_DEBUG, DEBUG) (0x00000070U+((CHATOMIC_DEBUG)*0x100U)+((DEBUG)*0x40U))
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15(CHATOMIC_DEBUG, DEBUG) (0x00000078U+((CHATOMIC_DEBUG)*0x100U)+((DEBUG)*0x40U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* NEXT_TR_WORD0_1 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_FLAGS_MASK         (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_FLAGS_SHIFT        (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_FLAGS_RESETVAL     (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_FLAGS_MAX          (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_ICNT0_MASK         (0x0000FFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_ICNT0_SHIFT        (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_ICNT0_RESETVAL     (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_ICNT0_MAX          (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_ICNT1_MASK         (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_ICNT1_SHIFT        (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_ICNT1_RESETVAL     (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_ICNT1_MAX          (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD0_1_RESETVAL           (0x0000000000000000U)

/* NEXT_TR_WORD2_3 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3_RSVD_MASK          (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3_RSVD_SHIFT         (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3_RSVD_RESETVAL      (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3_RSVD_MAX           (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3_SRC_ADDR_MASK      (0x0000FFFFFFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3_SRC_ADDR_SHIFT     (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3_SRC_ADDR_RESETVAL  (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3_SRC_ADDR_MAX       (0x0000FFFFFFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD2_3_RESETVAL           (0x0000000000000000U)

/* NEXT_TR_WORD4_5 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_DIM1_MASK          (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_DIM1_SHIFT         (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_DIM1_RESETVAL      (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_DIM1_MAX           (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_ICNT2_MASK         (0x0000FFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_ICNT2_SHIFT        (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_ICNT2_RESETVAL     (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_ICNT2_MAX          (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_ICNT3_MASK         (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_ICNT3_SHIFT        (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_ICNT3_RESETVAL     (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_ICNT3_MAX          (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD4_5_RESETVAL           (0x0000000000000000U)

/* NEXT_TR_WORD6_7 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7_DIM2_MASK          (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7_DIM2_SHIFT         (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7_DIM2_RESETVAL      (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7_DIM2_MAX           (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7_DIM3_MASK          (0xFFFFFFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7_DIM3_SHIFT         (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7_DIM3_RESETVAL      (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7_DIM3_MAX           (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD6_7_RESETVAL           (0x0000000000000000U)

/* NEXT_TR_WORD8_9 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9_DDIM1_MASK         (0xFFFFFFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9_DDIM1_SHIFT        (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9_DDIM1_RESETVAL     (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9_DDIM1_MAX          (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9_FMTFLAGS_MASK      (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9_FMTFLAGS_SHIFT     (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9_FMTFLAGS_RESETVAL  (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9_FMTFLAGS_MAX       (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD8_9_RESETVAL           (0x0000000000000000U)

/* NEXT_TR_WORD10_11 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11_DADDR_MASK       (0x0000FFFFFFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11_DADDR_SHIFT      (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11_DADDR_RESETVAL   (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11_DADDR_MAX        (0x0000FFFFFFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11_RSVD_MASK        (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11_RSVD_SHIFT       (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11_RSVD_RESETVAL    (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11_RSVD_MAX         (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD10_11_RESETVAL         (0x0000000000000000U)

/* NEXT_TR_WORD12_13 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13_DDIM2_MASK       (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13_DDIM2_SHIFT      (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13_DDIM2_RESETVAL   (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13_DDIM2_MAX        (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13_DDIM3_MASK       (0xFFFFFFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13_DDIM3_SHIFT      (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13_DDIM3_RESETVAL   (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13_DDIM3_MAX        (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD12_13_RESETVAL         (0x0000000000000000U)

/* NEXT_TR_WORD14_15 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT0_MASK      (0x000000000000FFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT0_SHIFT     (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT0_RESETVAL  (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT0_MAX       (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT1_MASK      (0x00000000FFFF0000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT1_SHIFT     (0x0000000000000010U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT1_RESETVAL  (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT1_MAX       (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT2_MASK      (0x0000FFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT2_SHIFT     (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT2_RESETVAL  (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT2_MAX       (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT3_MASK      (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT3_SHIFT     (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT3_RESETVAL  (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_DICNT3_MAX       (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_DEBUG_NEXT_TR_WORD14_15_RESETVAL         (0x0000000000000000U)

/* ATOMIC_SUBMIT_CURR_TR_WORD0_1 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_FLAGS_MASK (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_FLAGS_SHIFT (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_FLAGS_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_FLAGS_MAX  (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT0_MASK (0x0000FFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT0_SHIFT (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT0_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT0_MAX  (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT1_MASK (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT1_SHIFT (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT1_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT1_MAX  (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD0_1_RESETVAL   (0x0000000000000000U)

/* ATOMIC_SUBMIT_CURR_TR_WORD2_3 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3_RSVD_MASK  (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3_RSVD_SHIFT (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3_RSVD_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3_RSVD_MAX   (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3_SRC_ADDR_MASK (0x0000FFFFFFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3_SRC_ADDR_SHIFT (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3_SRC_ADDR_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3_SRC_ADDR_MAX (0x0000FFFFFFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD2_3_RESETVAL   (0x0000000000000000U)

/* ATOMIC_SUBMIT_CURR_TR_WORD4_5 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_DIM1_MASK  (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_DIM1_SHIFT (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_DIM1_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_DIM1_MAX   (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT2_MASK (0x0000FFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT2_SHIFT (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT2_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT2_MAX  (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT3_MASK (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT3_SHIFT (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT3_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT3_MAX  (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD4_5_RESETVAL   (0x0000000000000000U)

/* ATOMIC_SUBMIT_CURR_TR_WORD6_7 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM2_MASK  (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM2_SHIFT (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM2_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM2_MAX   (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM3_MASK  (0xFFFFFFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM3_SHIFT (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM3_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM3_MAX   (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD6_7_RESETVAL   (0x0000000000000000U)

/* ATOMIC_SUBMIT_CURR_TR_WORD8_9 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9_DDIM1_MASK (0xFFFFFFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9_DDIM1_SHIFT (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9_DDIM1_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9_DDIM1_MAX  (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9_FMTFLAGS_MASK (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9_FMTFLAGS_SHIFT (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9_FMTFLAGS_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9_FMTFLAGS_MAX (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD8_9_RESETVAL   (0x0000000000000000U)

/* ATOMIC_SUBMIT_CURR_TR_WORD10_11 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11_DADDR_MASK (0x0000FFFFFFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11_DADDR_SHIFT (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11_DADDR_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11_DADDR_MAX (0x0000FFFFFFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11_RSVD_MASK (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11_RSVD_SHIFT (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11_RSVD_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11_RSVD_MAX (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD10_11_RESETVAL (0x0000000000000000U)

/* ATOMIC_SUBMIT_CURR_TR_WORD12_13 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM2_MASK (0x00000000FFFFFFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM2_SHIFT (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM2_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM2_MAX (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM3_MASK (0xFFFFFFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM3_SHIFT (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM3_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM3_MAX (0x00000000FFFFFFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD12_13_RESETVAL (0x0000000000000000U)

/* ATOMIC_SUBMIT_CURR_TR_WORD14_15 */

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT0_MASK (0x000000000000FFFFU)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT0_SHIFT (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT0_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT0_MAX (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT1_MASK (0x00000000FFFF0000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT1_SHIFT (0x0000000000000010U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT1_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT1_MAX (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT2_MASK (0x0000FFFF00000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT2_SHIFT (0x0000000000000020U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT2_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT2_MAX (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT3_MASK (0xFFFF000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT3_SHIFT (0x0000000000000030U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT3_RESETVAL (0x0000000000000000U)
#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT3_MAX (0x000000000000FFFFU)

#define CSL_DRU_ATOMIC_CHATOMIC_DEBUG_ATOMIC_SUBMIT_CURR_TR_WORD14_15_RESETVAL (0x0000000000000000U)

/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint64_t CAUSE[4];                  /* Error Register cause for channels 0 to 15 */
    volatile uint8_t  Resv_256[224];
} CSL_dru_causeRegs_CAUSE;


typedef struct {
    CSL_dru_causeRegs_CAUSE CAUSE;
} CSL_dru_causeRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define CSL_DRU_CAUSE(CAUSE)                                       (0x00000000U+((CAUSE)*0x8U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CAUSE */

#define CSL_DRU_CAUSE_R_ERR15_MASK                                 (0x8000000000000000U)
#define CSL_DRU_CAUSE_R_ERR15_SHIFT                                (0x000000000000003FU)
#define CSL_DRU_CAUSE_R_ERR15_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR15_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND15_MASK                                (0x4000000000000000U)
#define CSL_DRU_CAUSE_R_PEND15_SHIFT                               (0x000000000000003EU)
#define CSL_DRU_CAUSE_R_PEND15_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND15_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR15_MASK                                 (0x2000000000000000U)
#define CSL_DRU_CAUSE_T_ERR15_SHIFT                                (0x000000000000003DU)
#define CSL_DRU_CAUSE_T_ERR15_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR15_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND15_MASK                                (0x1000000000000000U)
#define CSL_DRU_CAUSE_T_PEND15_SHIFT                               (0x000000000000003CU)
#define CSL_DRU_CAUSE_T_PEND15_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND15_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR14_MASK                                 (0x0800000000000000U)
#define CSL_DRU_CAUSE_R_ERR14_SHIFT                                (0x000000000000003BU)
#define CSL_DRU_CAUSE_R_ERR14_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR14_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND14_MASK                                (0x0400000000000000U)
#define CSL_DRU_CAUSE_R_PEND14_SHIFT                               (0x000000000000003AU)
#define CSL_DRU_CAUSE_R_PEND14_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND14_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR14_MASK                                 (0x0200000000000000U)
#define CSL_DRU_CAUSE_T_ERR14_SHIFT                                (0x0000000000000039U)
#define CSL_DRU_CAUSE_T_ERR14_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR14_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND14_MASK                                (0x0100000000000000U)
#define CSL_DRU_CAUSE_T_PEND14_SHIFT                               (0x0000000000000038U)
#define CSL_DRU_CAUSE_T_PEND14_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND14_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR13_MASK                                 (0x0080000000000000U)
#define CSL_DRU_CAUSE_R_ERR13_SHIFT                                (0x0000000000000037U)
#define CSL_DRU_CAUSE_R_ERR13_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR13_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND13_MASK                                (0x0040000000000000U)
#define CSL_DRU_CAUSE_R_PEND13_SHIFT                               (0x0000000000000036U)
#define CSL_DRU_CAUSE_R_PEND13_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND13_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR13_MASK                                 (0x0020000000000000U)
#define CSL_DRU_CAUSE_T_ERR13_SHIFT                                (0x0000000000000035U)
#define CSL_DRU_CAUSE_T_ERR13_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR13_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND13_MASK                                (0x0010000000000000U)
#define CSL_DRU_CAUSE_T_PEND13_SHIFT                               (0x0000000000000034U)
#define CSL_DRU_CAUSE_T_PEND13_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND13_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR12_MASK                                 (0x0008000000000000U)
#define CSL_DRU_CAUSE_R_ERR12_SHIFT                                (0x0000000000000033U)
#define CSL_DRU_CAUSE_R_ERR12_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR12_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND12_MASK                                (0x0004000000000000U)
#define CSL_DRU_CAUSE_R_PEND12_SHIFT                               (0x0000000000000032U)
#define CSL_DRU_CAUSE_R_PEND12_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND12_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR12_MASK                                 (0x0002000000000000U)
#define CSL_DRU_CAUSE_T_ERR12_SHIFT                                (0x0000000000000031U)
#define CSL_DRU_CAUSE_T_ERR12_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR12_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND12_MASK                                (0x0001000000000000U)
#define CSL_DRU_CAUSE_T_PEND12_SHIFT                               (0x0000000000000030U)
#define CSL_DRU_CAUSE_T_PEND12_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND12_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR11_MASK                                 (0x0000800000000000U)
#define CSL_DRU_CAUSE_R_ERR11_SHIFT                                (0x000000000000002FU)
#define CSL_DRU_CAUSE_R_ERR11_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR11_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND11_MASK                                (0x0000400000000000U)
#define CSL_DRU_CAUSE_R_PEND11_SHIFT                               (0x000000000000002EU)
#define CSL_DRU_CAUSE_R_PEND11_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND11_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR11_MASK                                 (0x0000200000000000U)
#define CSL_DRU_CAUSE_T_ERR11_SHIFT                                (0x000000000000002DU)
#define CSL_DRU_CAUSE_T_ERR11_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR11_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND11_MASK                                (0x0000100000000000U)
#define CSL_DRU_CAUSE_T_PEND11_SHIFT                               (0x000000000000002CU)
#define CSL_DRU_CAUSE_T_PEND11_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND11_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR10_MASK                                 (0x0000080000000000U)
#define CSL_DRU_CAUSE_R_ERR10_SHIFT                                (0x000000000000002BU)
#define CSL_DRU_CAUSE_R_ERR10_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR10_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND10_MASK                                (0x0000040000000000U)
#define CSL_DRU_CAUSE_R_PEND10_SHIFT                               (0x000000000000002AU)
#define CSL_DRU_CAUSE_R_PEND10_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND10_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR10_MASK                                 (0x0000020000000000U)
#define CSL_DRU_CAUSE_T_ERR10_SHIFT                                (0x0000000000000029U)
#define CSL_DRU_CAUSE_T_ERR10_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR10_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND10_MASK                                (0x0000010000000000U)
#define CSL_DRU_CAUSE_T_PEND10_SHIFT                               (0x0000000000000028U)
#define CSL_DRU_CAUSE_T_PEND10_RESETVAL                            (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND10_MAX                                 (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR9_MASK                                  (0x0000008000000000U)
#define CSL_DRU_CAUSE_R_ERR9_SHIFT                                 (0x0000000000000027U)
#define CSL_DRU_CAUSE_R_ERR9_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR9_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND9_MASK                                 (0x0000004000000000U)
#define CSL_DRU_CAUSE_R_PEND9_SHIFT                                (0x0000000000000026U)
#define CSL_DRU_CAUSE_R_PEND9_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND9_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR9_MASK                                  (0x0000002000000000U)
#define CSL_DRU_CAUSE_T_ERR9_SHIFT                                 (0x0000000000000025U)
#define CSL_DRU_CAUSE_T_ERR9_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR9_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND9_MASK                                 (0x0000001000000000U)
#define CSL_DRU_CAUSE_T_PEND9_SHIFT                                (0x0000000000000024U)
#define CSL_DRU_CAUSE_T_PEND9_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND9_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR8_MASK                                  (0x0000000800000000U)
#define CSL_DRU_CAUSE_R_ERR8_SHIFT                                 (0x0000000000000023U)
#define CSL_DRU_CAUSE_R_ERR8_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR8_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND8_MASK                                 (0x0000000400000000U)
#define CSL_DRU_CAUSE_R_PEND8_SHIFT                                (0x0000000000000022U)
#define CSL_DRU_CAUSE_R_PEND8_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND8_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR8_MASK                                  (0x0000000200000000U)
#define CSL_DRU_CAUSE_T_ERR8_SHIFT                                 (0x0000000000000021U)
#define CSL_DRU_CAUSE_T_ERR8_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR8_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND8_MASK                                 (0x0000000100000000U)
#define CSL_DRU_CAUSE_T_PEND8_SHIFT                                (0x0000000000000020U)
#define CSL_DRU_CAUSE_T_PEND8_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND8_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR7_MASK                                  (0x0000000080000000U)
#define CSL_DRU_CAUSE_R_ERR7_SHIFT                                 (0x000000000000001FU)
#define CSL_DRU_CAUSE_R_ERR7_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR7_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND7_MASK                                 (0x0000000040000000U)
#define CSL_DRU_CAUSE_R_PEND7_SHIFT                                (0x000000000000001EU)
#define CSL_DRU_CAUSE_R_PEND7_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND7_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR7_MASK                                  (0x0000000020000000U)
#define CSL_DRU_CAUSE_T_ERR7_SHIFT                                 (0x000000000000001DU)
#define CSL_DRU_CAUSE_T_ERR7_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR7_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND7_MASK                                 (0x0000000010000000U)
#define CSL_DRU_CAUSE_T_PEND7_SHIFT                                (0x000000000000001CU)
#define CSL_DRU_CAUSE_T_PEND7_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND7_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR6_MASK                                  (0x0000000008000000U)
#define CSL_DRU_CAUSE_R_ERR6_SHIFT                                 (0x000000000000001BU)
#define CSL_DRU_CAUSE_R_ERR6_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR6_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND6_MASK                                 (0x0000000004000000U)
#define CSL_DRU_CAUSE_R_PEND6_SHIFT                                (0x000000000000001AU)
#define CSL_DRU_CAUSE_R_PEND6_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND6_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR6_MASK                                  (0x0000000002000000U)
#define CSL_DRU_CAUSE_T_ERR6_SHIFT                                 (0x0000000000000019U)
#define CSL_DRU_CAUSE_T_ERR6_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR6_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND6_MASK                                 (0x0000000001000000U)
#define CSL_DRU_CAUSE_T_PEND6_SHIFT                                (0x0000000000000018U)
#define CSL_DRU_CAUSE_T_PEND6_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND6_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR5_MASK                                  (0x0000000000800000U)
#define CSL_DRU_CAUSE_R_ERR5_SHIFT                                 (0x0000000000000017U)
#define CSL_DRU_CAUSE_R_ERR5_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR5_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND5_MASK                                 (0x0000000000400000U)
#define CSL_DRU_CAUSE_R_PEND5_SHIFT                                (0x0000000000000016U)
#define CSL_DRU_CAUSE_R_PEND5_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND5_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR5_MASK                                  (0x0000000000200000U)
#define CSL_DRU_CAUSE_T_ERR5_SHIFT                                 (0x0000000000000015U)
#define CSL_DRU_CAUSE_T_ERR5_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR5_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND5_MASK                                 (0x0000000000100000U)
#define CSL_DRU_CAUSE_T_PEND5_SHIFT                                (0x0000000000000014U)
#define CSL_DRU_CAUSE_T_PEND5_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND5_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR4_MASK                                  (0x0000000000080000U)
#define CSL_DRU_CAUSE_R_ERR4_SHIFT                                 (0x0000000000000013U)
#define CSL_DRU_CAUSE_R_ERR4_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR4_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND4_MASK                                 (0x0000000000040000U)
#define CSL_DRU_CAUSE_R_PEND4_SHIFT                                (0x0000000000000012U)
#define CSL_DRU_CAUSE_R_PEND4_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND4_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR4_MASK                                  (0x0000000000020000U)
#define CSL_DRU_CAUSE_T_ERR4_SHIFT                                 (0x0000000000000011U)
#define CSL_DRU_CAUSE_T_ERR4_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR4_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND4_MASK                                 (0x0000000000010000U)
#define CSL_DRU_CAUSE_T_PEND4_SHIFT                                (0x0000000000000010U)
#define CSL_DRU_CAUSE_T_PEND4_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND4_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR3_MASK                                  (0x0000000000008000U)
#define CSL_DRU_CAUSE_R_ERR3_SHIFT                                 (0x000000000000000FU)
#define CSL_DRU_CAUSE_R_ERR3_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR3_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND3_MASK                                 (0x0000000000004000U)
#define CSL_DRU_CAUSE_R_PEND3_SHIFT                                (0x000000000000000EU)
#define CSL_DRU_CAUSE_R_PEND3_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND3_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR3_MASK                                  (0x0000000000002000U)
#define CSL_DRU_CAUSE_T_ERR3_SHIFT                                 (0x000000000000000DU)
#define CSL_DRU_CAUSE_T_ERR3_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR3_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND3_MASK                                 (0x0000000000001000U)
#define CSL_DRU_CAUSE_T_PEND3_SHIFT                                (0x000000000000000CU)
#define CSL_DRU_CAUSE_T_PEND3_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND3_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR2_MASK                                  (0x0000000000000800U)
#define CSL_DRU_CAUSE_R_ERR2_SHIFT                                 (0x000000000000000BU)
#define CSL_DRU_CAUSE_R_ERR2_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR2_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND2_MASK                                 (0x0000000000000400U)
#define CSL_DRU_CAUSE_R_PEND2_SHIFT                                (0x000000000000000AU)
#define CSL_DRU_CAUSE_R_PEND2_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND2_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR2_MASK                                  (0x0000000000000200U)
#define CSL_DRU_CAUSE_T_ERR2_SHIFT                                 (0x0000000000000009U)
#define CSL_DRU_CAUSE_T_ERR2_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR2_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND2_MASK                                 (0x0000000000000100U)
#define CSL_DRU_CAUSE_T_PEND2_SHIFT                                (0x0000000000000008U)
#define CSL_DRU_CAUSE_T_PEND2_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND2_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR1_MASK                                  (0x0000000000000080U)
#define CSL_DRU_CAUSE_R_ERR1_SHIFT                                 (0x0000000000000007U)
#define CSL_DRU_CAUSE_R_ERR1_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR1_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND1_MASK                                 (0x0000000000000040U)
#define CSL_DRU_CAUSE_R_PEND1_SHIFT                                (0x0000000000000006U)
#define CSL_DRU_CAUSE_R_PEND1_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND1_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR1_MASK                                  (0x0000000000000020U)
#define CSL_DRU_CAUSE_T_ERR1_SHIFT                                 (0x0000000000000005U)
#define CSL_DRU_CAUSE_T_ERR1_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR1_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND1_MASK                                 (0x0000000000000010U)
#define CSL_DRU_CAUSE_T_PEND1_SHIFT                                (0x0000000000000004U)
#define CSL_DRU_CAUSE_T_PEND1_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND1_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_ERR0_MASK                                  (0x0000000000000008U)
#define CSL_DRU_CAUSE_R_ERR0_SHIFT                                 (0x0000000000000003U)
#define CSL_DRU_CAUSE_R_ERR0_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_ERR0_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_R_PEND0_MASK                                 (0x0000000000000004U)
#define CSL_DRU_CAUSE_R_PEND0_SHIFT                                (0x0000000000000002U)
#define CSL_DRU_CAUSE_R_PEND0_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_R_PEND0_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_ERR0_MASK                                  (0x0000000000000002U)
#define CSL_DRU_CAUSE_T_ERR0_SHIFT                                 (0x0000000000000001U)
#define CSL_DRU_CAUSE_T_ERR0_RESETVAL                              (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_ERR0_MAX                                   (0x0000000000000001U)

#define CSL_DRU_CAUSE_T_PEND0_MASK                                 (0x0000000000000001U)
#define CSL_DRU_CAUSE_T_PEND0_SHIFT                                (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND0_RESETVAL                             (0x0000000000000000U)
#define CSL_DRU_CAUSE_T_PEND0_MAX                                  (0x0000000000000001U)

#define CSL_DRU_CAUSE_RESETVAL                                     (0x0000000000000000U)

/**************************************************************************
* Hardware Region  :
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint64_t SUBMIT_WORD0_1;            /* The first TR submission word */
    volatile uint64_t SUBMIT_WORD2_3;            /* The second TR submission word */
    volatile uint64_t SUBMIT_WORD4_5;            /* The third TR submission word */
    volatile uint64_t SUBMIT_WORD6_7;            /* The fourth TR submission word */
    volatile uint64_t SUBMIT_WORD8_9;            /* The fifth TR submission word */
    volatile uint64_t SUBMIT_WORD10_11;          /* The sixth TR submission word */
    volatile uint64_t SUBMIT_WORD12_13;          /* The seventh TR submission word */
    volatile uint64_t SUBMIT_WORD14_15;          /* The eight TR submission word */
} CSL_DRU_CHCORERegs_CHCORE_CORE;


typedef struct {
    CSL_DRU_CHCORERegs_CHCORE_CORE CORE[4];
} CSL_DRU_CHCORERegs_CHCORE;


typedef struct {
    CSL_DRU_CHCORERegs_CHCORE CHCORE[512];
} CSL_DRU_CHCORERegs;
/**************************************************************************
 *  DRU TOP LEVEL Struct (hand created DLB)
 *************************************************************************/

typedef struct {
    CSL_druRegs            DRURegs;
    uint8_t                    RSVD01[16312];
    CSL_dru_setRegs          DRUEvtSet;
    uint8_t                    RSVD02[16184];
    CSL_dru_queueRegs          DRUQueues;
    uint8_t                    RSVD03[32600];
    uint8_t                    RSVD04[196688];
    CSL_DRU_CHNRTRegs_CHNRT              CHNRT[512];
    CSL_DRU_CHRTRegs_CHRT               CHRT[512];
    CSL_dru_atomicRegs_CHATOMIC_DEBUG           CHATOMIC[512];
    CSL_DRU_CHCORERegs_CHCORE  CHCORE[512];
    CSL_DRU_CHCORERegs_CHCORE             CHCOREHI[512];
    CSL_dru_causeRegs          CAUSE;
} CSL_DRU_t;
#ifdef __cplusplus
}
#endif
#endif
