/********************************************************************
*
* SOC PBIST PROPERTIES. header file
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
#ifndef SDLR_SOC_PBIST_H_
#define SDLR_SOC_PBIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*
* Auto-generated SDL definitions for SoC PBIST Instances:
*/


/* Properties of PBIST instances in: PBIST0 */
#define SDL_PBIST0_NUM_TEST_VECTORS                                                                (2U)
#define SDL_PBIST0_ALGO_BITMAP_0                                                                   (0x0000000000000055U)
#define SDL_PBIST0_MEM_BITMAP_0                                                                    (0x0000000000213500U)
#define SDL_PBIST0_ALGO_BITMAP_1                                                                   (0x00000000000000AAU)
#define SDL_PBIST0_MEM_BITMAP_1                                                                    (0x0000000420800000U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0                                                  (0x00000000U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1                                                  (0x0000001FU)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2                                                  (0x0000001FU)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0                                                  (0x0000000FU)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR                                                  (0x00000003U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0                                                   (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1                                                   (0x00000002U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2                                                   (0x00000002U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3                                                   (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT                                                 (0x38004028U)

/* Properties of PBIST instances in: PBIST3 */
#define SDL_PBIST3_NUM_TEST_VECTORS                                                                (2U)
#define SDL_PBIST3_ALGO_BITMAP_0                                                                   (0x0000000000000055U)
#define SDL_PBIST3_MEM_BITMAP_0                                                                    (0x0000000001221042U)
#define SDL_PBIST3_ALGO_BITMAP_1                                                                   (0x00000000000000AAU)
#define SDL_PBIST3_MEM_BITMAP_1                                                                    (0x0000000208000000U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA0                                                  (0x00000000U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA1                                                  (0x0000003FU)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA2                                                  (0x0000003FU)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA3                                                  (0x00000001U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL0                                                  (0x0000003FU)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL1                                                  (0x00000000U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL2                                                  (0x00000000U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL3                                                  (0x00000001U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CMS                                                  (0x00000000U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CSR                                                  (0x00000010U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I0                                                   (0x00000001U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I1                                                   (0x00000001U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I2                                                   (0x00000002U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I3                                                   (0x00000000U)
#define SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_RAMT                                                 (0x00042028U)

/* Properties of PBIST instances in: WKUP_R5FSS0 */
#define SDL_WKUP_R5FSS0_NUM_TEST_VECTORS                                                           (1U)
#define SDL_WKUP_R5FSS0_ALGO_BITMAP_0                                                              (0x000000000000000FU)
#define SDL_WKUP_R5FSS0_MEM_BITMAP_0                                                               (0x0000000000000211U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CA0                                             (0x00000000U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CA1                                             (0x000003FFU)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CA2                                             (0x000003FFU)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CA3                                             (0x00000001U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CL0                                             (0x000000FFU)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CL1                                             (0x00000003U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CL2                                             (0x00000003U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CL3                                             (0x00000001U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CMS                                             (0x00000000U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CSR                                             (0x00000003U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_I0                                              (0x00000001U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_I1                                              (0x00000004U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_I2                                              (0x00000002U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_I3                                              (0x00000003U)
#define SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_RAMT                                            (0x00004028U)

/* Properties of PBIST instances in: VPAC0 */
#define SDL_VPAC0_NUM_TEST_VECTORS                                                                 (2U)
#define SDL_VPAC0_ALGO_BITMAP_0                                                                    (0x0000000000000055U)
#define SDL_VPAC0_MEM_BITMAP_0                                                                     (0x00000000000008A2U)
#define SDL_VPAC0_ALGO_BITMAP_1                                                                    (0x00000000000000AAU)
#define SDL_VPAC0_MEM_BITMAP_1                                                                     (0x0000000000002000U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CA0                                                   (0x00000000U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CA1                                                   (0x0000013FU)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CA2                                                   (0x0000013FU)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CA3                                                   (0x00000001U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CL0                                                   (0x0000004FU)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CL1                                                   (0x00000003U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CL2                                                   (0x00000003U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CL3                                                   (0x00000001U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CMS                                                   (0x00000000U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CSR                                                   (0x04000000U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_I0                                                    (0x00000001U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_I1                                                    (0x00000004U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_I2                                                    (0x00000002U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_I3                                                    (0x00000003U)
#define SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_RAMT                                                  (0x011A1228U)

/* Properties of PBIST instances in: WKUP_PBIST0 */
#define SDL_WKUP_PBIST0_NUM_TEST_VECTORS                                                           (1U)
#define SDL_WKUP_PBIST0_ALGO_BITMAP_0                                                              (0x000000000000000FU)
#define SDL_WKUP_PBIST0_MEM_BITMAP_0                                                               (0x0000000000011911U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0                                             (0x00000000U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1                                             (0x000003FFU)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2                                             (0x000003FFU)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3                                             (0x00000001U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0                                             (0x000000FFU)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1                                             (0x00000003U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2                                             (0x00000003U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3                                             (0x00000001U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS                                             (0x00000000U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR                                             (0x0000000CU)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0                                              (0x00000001U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1                                              (0x00000004U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2                                              (0x00000002U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3                                              (0x00000003U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT                                            (0x09024028U)

/* Properties of PBIST instances in: C7X256V0 */
#define SDL_C7X256V0_NUM_TEST_VECTORS                                                              (2U)
#define SDL_C7X256V0_ALGO_BITMAP_0                                                                 (0x0000000000000055U)
#define SDL_C7X256V0_MEM_BITMAP_0                                                                  (0x0000000000071366U)
#define SDL_C7X256V0_ALGO_BITMAP_1                                                                 (0x00000000000000AAU)
#define SDL_C7X256V0_MEM_BITMAP_1                                                                  (0x0000000000500000U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CA0                                                (0x00000000U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CA1                                                (0x000001FFU)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CA2                                                (0x000001FFU)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CA3                                                (0x00000001U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CL0                                                (0x0000007FU)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CL1                                                (0x00000003U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CL2                                                (0x00000003U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CL3                                                (0x00000001U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CMS                                                (0x00000000U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CSR                                                (0x00000001U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_I0                                                 (0x00000001U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_I1                                                 (0x00000004U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_I2                                                 (0x00000002U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_I3                                                 (0x00000003U)
#define SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_RAMT                                               (0x54001C20U)

/* Properties of PBIST instances in: WKUP_PBIST1 */
#define SDL_WKUP_PBIST1_NUM_TEST_VECTORS                                                           (2U)
#define SDL_WKUP_PBIST1_ALGO_BITMAP_0                                                              (0x0000000000000055U)
#define SDL_WKUP_PBIST1_MEM_BITMAP_0                                                               (0x0000000000000108U)
#define SDL_WKUP_PBIST1_ALGO_BITMAP_1                                                              (0x00000000000000AAU)
#define SDL_WKUP_PBIST1_MEM_BITMAP_1                                                               (0x0000000000410000U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA0                                             (0x00000000U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA1                                             (0x000000FFU)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA2                                             (0x000000FFU)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA3                                             (0x00000001U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL0                                             (0x0000003FU)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL1                                             (0x00000003U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL2                                             (0x00000003U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL3                                             (0x00000001U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CMS                                             (0x00000003U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CSR                                             (0x00000001U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_I0                                              (0x00000001U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_I1                                              (0x00000004U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_I2                                              (0x00000002U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_I3                                              (0x00000003U)
#define SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_RAMT                                            (0x08002728U)

/* Properties of PBIST instances in: COMPUTE_CLUSTER0 */
#define SDL_COMPUTE_CLUSTER0_NUM_TEST_VECTORS                                                      (1U)
#define SDL_COMPUTE_CLUSTER0_ALGO_BITMAP_0                                                         (0x000000000000000FU)
#define SDL_COMPUTE_CLUSTER0_MEM_BITMAP_0                                                          (0x00000000FFFFFFFFU)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CA0                                        (0x00000000U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CA1                                        (0x000001FFU)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CA2                                        (0x000001FFU)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CA3                                        (0x00000001U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CL0                                        (0x0000007FU)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CL1                                        (0x00000003U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CL2                                        (0x00000003U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CL3                                        (0x00000001U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CMS                                        (0x00000000U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CSR                                        (0x00000001U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_I0                                         (0x00000001U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_I1                                         (0x00000004U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_I2                                         (0x00000002U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_I3                                         (0x00000003U)
#define SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_RAMT                                       (0x06002624U)

#ifdef __cplusplus
}
#endif
#endif /* SDLR_SOC_PBIST_H_ */