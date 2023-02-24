/********************************************************************
*
* SOC PBIST PROPERTIES. header file
*
* Copyright (C) 2015-2020 Texas Instruments Incorporated.
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
#define SDL_PBIST0_MEM_BITMAP_0                                                                    (0x000000000058B304U)
#define SDL_PBIST0_ALGO_BITMAP_1                                                                   (0x00000000000000AAU)
#define SDL_PBIST0_MEM_BITMAP_1                                                                    (0x0000001292000000U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0                                                  (0x00000000U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1                                                  (0x00000017U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2                                                  (0x00000017U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0                                                  (0x0000000BU)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS                                                  (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR                                                  (0x00000007U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0                                                   (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1                                                   (0x00000002U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2                                                   (0x00000002U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3                                                   (0x00000001U)
#define SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT                                                 (0x20004028U)

/* Properties of PBIST instances in: PBIST1 */
#define SDL_PBIST1_NUM_TEST_VECTORS                                                                (2U)
#define SDL_PBIST1_ALGO_BITMAP_0                                                                   (0x0000000000000055U)
#define SDL_PBIST1_MEM_BITMAP_0                                                                    (0x0000000004110042U)
#define SDL_PBIST1_ALGO_BITMAP_1                                                                   (0x00000000000000AAU)
#define SDL_PBIST1_MEM_BITMAP_1                                                                    (0x0000004040000000U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA0                                                  (0x00000000U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA1                                                  (0x000000FFU)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA2                                                  (0x000000FFU)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA3                                                  (0x00000001U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL0                                                  (0x0000007FU)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL1                                                  (0x00000001U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL2                                                  (0x00000001U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL3                                                  (0x00000001U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CMS                                                  (0x00000000U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CSR                                                  (0x00000001U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I0                                                   (0x00000001U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I1                                                   (0x00000002U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I2                                                   (0x00000002U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I3                                                   (0x00000001U)
#define SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_RAMT                                                 (0x00000828U)

/* Properties of PBIST instances in: WKUP_PBIST0 */
#define SDL_WKUP_PBIST0_NUM_TEST_VECTORS                                                           (2U)
#define SDL_WKUP_PBIST0_ALGO_BITMAP_0                                                              (0x0000000000000055U)
#define SDL_WKUP_PBIST0_MEM_BITMAP_0                                                               (0x000000000A810811U)
#define SDL_WKUP_PBIST0_ALGO_BITMAP_1                                                              (0x00000000000000AAU)
#define SDL_WKUP_PBIST0_MEM_BITMAP_1                                                               (0x0000001540000000U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0                                             (0x00000000U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1                                             (0x000000FFU)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2                                             (0x000000FFU)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3                                             (0x00000001U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0                                             (0x0000003FU)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1                                             (0x00000003U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2                                             (0x00000003U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3                                             (0x00000001U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS                                             (0x00000000U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR                                             (0x00000001U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0                                              (0x00000001U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1                                              (0x00000004U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2                                              (0x00000002U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3                                              (0x00000003U)
#define SDL_WKUP_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT                                            (0x28001C28U)

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

