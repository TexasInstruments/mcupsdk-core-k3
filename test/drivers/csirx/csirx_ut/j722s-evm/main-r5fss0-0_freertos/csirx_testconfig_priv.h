/*
 *  Copyright (c) Texas Instruments Incorporated 2019-25
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
 */

/**
 *  \file csirx_testconfig_priv.h
 *
 *  \brief This file defines macros for common configurations of tests
 */

#ifndef CSIRX_TESTCONFIG_PRIV_H_
#define CSIRX_TESTCONFIG_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "csirx_test.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CSIRX_TEST_RGB888_PITCH(x)                          ((uint32_t)(x * 4))
#define CSIRX_TEST_RAW12_UN_PITCH(x)                        ((uint32_t)(x * 2))
#define CSIRX_TEST_YUV422_8BIT_PITCH(x)                     ((uint32_t)(x * 4))

/* Reserving for 4K frame with RGB888 format which is maximum */
#define CSIRX_TEST_MAX_LINE_SIZE_BYTES                      ((uint32_t)(4096 * 4))
/* Numbe of channel configuration available */
#define CSIRX_TEST_NUM_CH_CFG_PARAMS                        ((sizeof (gChCfgInfo)) / \
                                                        (sizeof (CsirxChCfgInfo)))

/* Numbe of instance configuration available */
#define CSIRX_TEST_NUM_INST_CFG_PARAMS                      ((sizeof (gInstCfgInfo)) / \
                                                        (sizeof (CsirxInstCfgInfo)))

/* Numbe of task configuration available */
#define CSIRX_TEST_NUM_TASK_CFG_PARAMS                      ((sizeof (gTestTaskCfg)) / \
                                                        (sizeof (CsirxTestTaskCfg)))

/* IDs for test task configuration */
#define TASK_CFG_ID_1CH_RGB888                              ((uint32_t)0U)
#define TASK_CFG_ID_4CH_RAW12                               ((uint32_t)1U)
#define TASK_CFG_ID_1CH_RGB888_2DL                          ((uint32_t)2U)
#define TASK_CFG_ID_1CH_YUV422_8BIT                         ((uint32_t)3U)
#define TASK_CFG_ID_2CH_RAW12_TRUNC_ENL_FRM                 ((uint32_t)4U)
#define TASK_CFG_ID_2CH_RGB888_RAW12                        ((uint32_t)5U)
#define TASK_CFG_ID_1CH_RGB888_INST_1                       ((uint32_t)6U)
#define TASK_CFG_ID_1CH_RAW12                               ((uint32_t)7U)
#define TASK_CFG_ID_2CH_RAW12_STRM_FIFO_OVERFLOW            ((uint32_t)8U)
#define TASK_CFG_ID_1CH_YUV422_8BIT_DUAL_PIXEL              ((uint32_t)9U)

/* IDs for channel configuration */
#define CH_CFG_ID_RGB888_1920_1080                          ((uint32_t)0U)
#define CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH0              ((uint32_t)1U)
#define CH_CFG_ID_RAW12_PACKED_800_600                      ((uint32_t)2U)
#define CH_CFG_ID_YUV422_8BIT_1920_1080                     ((uint32_t)3U)
#define CH_CFG_ID_RAW12_1936_1100_TRUNC_FRM                 ((uint32_t)4U)
#define CH_CFG_ID_RAW12_1936_1100_ELONG_FRM                 ((uint32_t)5U)
#define CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH1              ((uint32_t)6U)
#define CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH2              ((uint32_t)7U)
#define CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH3              ((uint32_t)8U)

/* IDs for instance configuration */
#define INST_CFG_ID_DRV_ID0_1CH_RGB888                      ((uint32_t)0U)
#define INST_CFG_ID_DRV_ID0_2CH_RGB888_RAW12                ((uint32_t)1U)
#define INST_CFG_ID_DRV_ID0_4CH_RAW12                       ((uint32_t)2U)
#define INST_CFG_ID_DRV_ID0_1CH_RGB888_2DL                  ((uint32_t)3U)
#define INST_CFG_ID_DRV_ID0_1CH_YUV422_8BIT                 ((uint32_t)4U)
#define INST_CFG_ID_DRV_ID0_2CH_RAW12_TRUNC_ENL_FRM         ((uint32_t)5U)
#define INST_CFG_ID_DRV_ID0_1CH_RGB888_INST_1               ((uint32_t)6U)
#define INST_CFG_ID_DRV_ID0_1CH_RAW12                       ((uint32_t)7U)
#define INST_CFG_ID_DRV_ID0_2CH_RAW12_STRM_FIFO_OVERFLOW    ((uint32_t)8U)
#define INST_CFG_ID_DRV_ID0_1CH_YUV422_8BIT_DUAL_PIXEL      ((uint32_t)9U)

#endif /* #ifdef CSIRX_TESTCONFIG_PRIV_H */
