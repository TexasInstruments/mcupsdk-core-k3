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
 *  \file csirx_testconfig.h
 *
 *  \brief This file defines the common configurations like driver config etc...
 */

#ifndef CSIRX_TEST_CONFIG_H_
#define CSIRX_TEST_CONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "csirx_test.h"
#include "csirx_testconfig_priv.h"
#ifdef __cplusplus
extern "C" {
#endif


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static inline CsirxTestTaskCfg* Test_getTaskCfgParams(uint32_t taskCfgId);
static inline CsirxChCfgInfo* Test_getChCfgParams(uint32_t chCfgId);
static inline CsirxInstCfgInfo* Test_getInstCfgParams(uint32_t instCfgId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/**
 *  \brief Different channels configuration parameters.
 */
Csirx_ChCfg gChCfg[] =
{
    /* This is default configuration */
    /* CFG 0: 1920 x 1080 RGB888 capture */
    {
        .chId          = 0U,
        .chType        = CSIRX_CH_TYPE_CAPT,
        .vcNum         = 0U,
        .inCsiDataType = FVID2_CSI2_DF_RGB888,
        .outFmt        = {
                            .width      = 1920U,
                            .height     = 1080U,
                            .pitch[0]   = CSIRX_TEST_RGB888_PITCH(1920U),
                            .dataFormat = FVID2_DF_BGRX32_8888,
                            .ccsFormat  = FVID2_CCSF_BITS12_UNPACKED16,
                         },
    },
    /* CFG 1: IMX390 - 1936 x 1100 RAW12 Unpacked capture */
    {
        .chId          = 0U,
        .chType        = CSIRX_CH_TYPE_CAPT,
        .vcNum         = 0U,
        .inCsiDataType = FVID2_CSI2_DF_RAW12,
        .outFmt        = {
                            .width      = 1936U,
                            .height     = 1100U,
                            .pitch[0]   = CSIRX_TEST_RAW12_UN_PITCH(1936U),
                            .dataFormat = FVID2_DF_BGRX32_8888,
                            .ccsFormat  = FVID2_CCSF_BITS12_UNPACKED16,
                         },
    },
    /* CFG 2: 800 x 600 RAW12 Packed capture */
    {
        .chId          = 0U,
        .chType        = CSIRX_CH_TYPE_CAPT,
        .vcNum         = 0U,
        .inCsiDataType = FVID2_CSI2_DF_RAW12,
        .outFmt        = {
                            .width      = 1920U,
                            .height     = 1080U,
                            .pitch[0]   = CSIRX_TEST_RAW12_UN_PITCH(1920U),
                            .dataFormat = FVID2_DF_BGRX32_8888,
                            .ccsFormat  = FVID2_CCSF_BITS12_PACKED,
                         },
    },
    /* CFG 3: 1920 x 1080 YUV422-8bit Packed capture */
    {
        .chId          = 0U,
        .chType        = CSIRX_CH_TYPE_CAPT,
        .vcNum         = 0U,
        .inCsiDataType = FVID2_CSI2_DF_YUV422_8B,
        .outFmt        = {
                            .width      = 1920U,
                            .height     = 1080U,
                            .pitch[0]   = CSIRX_TEST_YUV422_8BIT_PITCH(1920U),
                            .dataFormat = FVID2_DF_YUV422I_VYUY,
                            .ccsFormat  = FVID2_CCSF_BITS12_PACKED,
                         },
    },
    /* CFG 4: 1920 x 1081 RAW12 capture - Truncated frame */
    {
        .chId          = 0U,
        .chType        = CSIRX_CH_TYPE_CAPT,
        .vcNum         = 0U,
        .inCsiDataType = FVID2_CSI2_DF_RAW12,
        .outFmt        = {
                            .width      = 1936U,
                            .height     = 1101U,
                            .pitch[0]   = CSIRX_TEST_RAW12_UN_PITCH(1936U),
                            .dataFormat = FVID2_DF_BGRX32_8888,
                            .ccsFormat  = FVID2_CCSF_BITS12_UNPACKED16,
                         },
    },
    /* CFG 5: 1920 x 1079 RAW12 capture - Elongated frame */
    {
        .chId          = 1U,
        .chType        = CSIRX_CH_TYPE_CAPT,
        .vcNum         = 1U,
        .inCsiDataType = FVID2_CSI2_DF_RAW12,
        .outFmt        = {
                            .width      = 1936U,
                            .height     = 1099U,
                            .pitch[0]   = CSIRX_TEST_RAW12_UN_PITCH(1936U),
                            .dataFormat = FVID2_DF_BGRX32_8888,
                            .ccsFormat  = FVID2_CCSF_BITS12_UNPACKED16,
                         },
    },
    /* CFG 6: IMX390 - 1936 x 1100 RAW12 Unpacked capture, Ch1 */
    {
        .chId          = 1U,
        .chType        = CSIRX_CH_TYPE_CAPT,
        .vcNum         = 1U,
        .inCsiDataType = FVID2_CSI2_DF_RAW12,
        .outFmt        = {
                            .width      = 1936U,
                            .height     = 1100U,
                            .pitch[0]   = CSIRX_TEST_RAW12_UN_PITCH(1936U),
                            .dataFormat = FVID2_DF_BGRX32_8888,
                            .ccsFormat  = FVID2_CCSF_BITS12_UNPACKED16,
                         },
    },
    /* CFG 7: IMX390 - 1936 x 1100 RAW12 Unpacked capture, Ch2 */
    {
        .chId          = 2U,
        .chType        = CSIRX_CH_TYPE_CAPT,
        .vcNum         = 2U,
        .inCsiDataType = FVID2_CSI2_DF_RAW12,
        .outFmt        = {
                            .width      = 1936U,
                            .height     = 1100U,
                            .pitch[0]   = CSIRX_TEST_RAW12_UN_PITCH(1936U),
                            .dataFormat = FVID2_DF_BGRX32_8888,
                            .ccsFormat  = FVID2_CCSF_BITS12_UNPACKED16,
                         },
    },
    /* CFG 8: IMX390 - 1936 x 1100 RAW12 Unpacked capture, Ch3 */
    {
        .chId          = 3U,
        .chType        = CSIRX_CH_TYPE_CAPT,
        .vcNum         = 3U,
        .inCsiDataType = FVID2_CSI2_DF_RAW12,
        .outFmt        = {
                            .width      = 1936U,
                            .height     = 1100U,
                            .pitch[0]   = CSIRX_TEST_RAW12_UN_PITCH(1936U),
                            .dataFormat = FVID2_DF_BGRX32_8888,
                            .ccsFormat  = FVID2_CCSF_BITS12_UNPACKED16,
                         },
    },
};

/**
 *  \brief Different channels Info and configuration parameters.
 */
CsirxChCfgInfo gChCfgInfo[] =
{
    /* This is default configuration */
    /* 1920 x 1080 RGB888 capture */
    {
        .chCfgInfoId     = CH_CFG_ID_RGB888_1920_1080,
        .numCaptFrames   = 10U,
        .numFrames       = 4U,
        .chCfg           = &gChCfg[0U],
        .heapId          = UTILS_MEM_HEAP_ID_DDR,
    },
    /* 1936 x 1100 RAW12 Unpacked capture */
    {
        .chCfgInfoId     = CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH0,
        .numCaptFrames   = 1000U,
        .numFrames       = 4U,
        .chCfg           = &gChCfg[1U],
        .heapId          = UTILS_MEM_HEAP_ID_DDR,
    },
    /* 800 x 600 RAW12 Packed capture */
    {
        .chCfgInfoId     = CH_CFG_ID_RAW12_PACKED_800_600,
        .numCaptFrames   = 10U,
        .numFrames       = 4U,
        .chCfg           = &gChCfg[2U],
        .heapId          = UTILS_MEM_HEAP_ID_DDR,
    },
    /* 1920 x 1080 YUV422-8bit capture */
    {
        .chCfgInfoId     = CH_CFG_ID_YUV422_8BIT_1920_1080,
        .numCaptFrames   = 10U,
        .numFrames       = 4U,
        .chCfg           = &gChCfg[3U],
        .heapId          = UTILS_MEM_HEAP_ID_DDR,
    },
    /* Truncated frame: 1936 x 1101 RAW12 capture */
    {
        .chCfgInfoId     = CH_CFG_ID_RAW12_1936_1100_TRUNC_FRM,
        .numCaptFrames   = 1U,
        .numFrames       = 1U,
        .chCfg           = &gChCfg[4U],
        .heapId          = UTILS_MEM_HEAP_ID_DDR,
    },
    /* Elongated frame: 1936 x 1099 RAW12 capture */
    {
        .chCfgInfoId     = CH_CFG_ID_RAW12_1936_1100_ELONG_FRM,
        .numCaptFrames   = 1U,
        .numFrames       = 1U,
        .chCfg           = &gChCfg[5U],
        .heapId          = UTILS_MEM_HEAP_ID_DDR,
    },
    /* 1936 x 1100 RAW12 Unpacked capture, Ch1 */
    {
        .chCfgInfoId     = CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH1,
        .numCaptFrames   = 1000U,
        .numFrames       = 4U,
        .chCfg           = &gChCfg[6U],
        .heapId          = UTILS_MEM_HEAP_ID_DDR,
    },
    /* 1936 x 1100 RAW12 Unpacked capture, Ch2 */
    {
        .chCfgInfoId     = CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH2,
        .numCaptFrames   = 1000U,
        .numFrames       = 4U,
        .chCfg           = &gChCfg[7U],
        .heapId          = UTILS_MEM_HEAP_ID_DDR,
    },
    /* 1936 x 1100 RAW12 Unpacked capture, Ch3 */
    {
        .chCfgInfoId     = CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH3,
        .numCaptFrames   = 1000U,
        .numFrames       = 4U,
        .chCfg           = &gChCfg[8U],
        .heapId          = UTILS_MEM_HEAP_ID_DDR,
    },
};

/**
 *  \brief Different CSIRX DRV instanes configuration parameters.
 */
Csirx_InstCfg gInstCfg[] =
{
    /* Instance config No. 0 */
    /* This is default configuration */
    {
        .enableCsiv2p0Support = UTRUE,
        .numDataLanes         = 4U,
        .dataLanesMap         = {1U, 2U, 3U, 4U},
        .enableErrbypass      = UFALSE,
        .numPixelsStrm0       = 0,
    },
    /* Instance config No. 1 */
    {
        .enableCsiv2p0Support = UTRUE,
        .numDataLanes         = 3U,
        .dataLanesMap         = {1U, 2U, 3U, 4U},
        .enableErrbypass      = UFALSE,
        .numPixelsStrm0       = 0,
    },
    /* Instance config No. 2 */
    {
        .enableCsiv2p0Support = UTRUE,
        .numDataLanes         = 2U,
        .dataLanesMap         = {1U, 2U, 3U, 4U},
        .enableErrbypass      = UFALSE,
        .numPixelsStrm0       = 0,
    },
    /* Instance config No. 3 */
    {
        .enableCsiv2p0Support = UTRUE,
        .numDataLanes         = 1U,
        .dataLanesMap         = {1U, 2U, 3U, 4U},
        .enableErrbypass      = UFALSE,
        .numPixelsStrm0       = 0,
    },
    /* Instance config No. 4 */
    {
        .enableCsiv2p0Support = UTRUE,
        .numDataLanes         = 4U,
        .dataLanesMap         = {1U, 2U, 3U, 4U},
        .enableErrbypass      = UFALSE,
        .numPixelsStrm0       = 1,
    },
};

/**
 *  \brief Different CSIRX DRV instanes Info and configuration parameters.
 */
CsirxInstCfgInfo gInstCfgInfo[] =
{
    /* This is default configuration */
    /* Instance config No. 0 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_1CH_RGB888,
        .csiDrvInst       = CSIRX_INSTANCE_ID_0,
        .instCfg          = &gInstCfg[0U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 1U,
        .chCfgId          = {
                                CH_CFG_ID_RGB888_1920_1080,
                           },
    },
    /* Instance config No. 1 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_2CH_RGB888_RAW12,
        .csiDrvInst       = CSIRX_INSTANCE_ID_0,
        .instCfg          = &gInstCfg[0U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 2U,
        .chCfgId          = {
                                CH_CFG_ID_RGB888_1920_1080,
                                CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH0,
                           },
    },
    /* Instance config No. 2 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_4CH_RAW12,
        .csiDrvInst       = CSIRX_INSTANCE_ID_0,
        .instCfg          = &gInstCfg[0U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 4U,
        .chCfgId          = {
                                CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH0,
                                CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH1,
                                CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH2,
                                CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH3,
                           },
    },
    /* Instance config No. 3 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_1CH_RGB888_2DL,
        .csiDrvInst       = CSIRX_INSTANCE_ID_0,
        .instCfg          = &gInstCfg[1U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 1U,
        .chCfgId          = {
                                CH_CFG_ID_RGB888_1920_1080,
                           },
    },
    /* Instance config No. 4 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_1CH_YUV422_8BIT,
        .csiDrvInst       = CSIRX_INSTANCE_ID_0,
        .instCfg          = &gInstCfg[0U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 1U,
        .chCfgId          = {
                                CH_CFG_ID_YUV422_8BIT_1920_1080,
                           },
    },
    /* Instance config No. 5 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_2CH_RAW12_TRUNC_ENL_FRM,
        .csiDrvInst       = CSIRX_INSTANCE_ID_0,
        .instCfg          = &gInstCfg[0U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 2U,
        .chCfgId          = {
                                CH_CFG_ID_RAW12_1936_1100_TRUNC_FRM,
                                CH_CFG_ID_RAW12_1936_1100_ELONG_FRM,
                           },
    },
    /* Instance config No. 6 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_1CH_RGB888_INST_1,
        .csiDrvInst       = CSIRX_INSTANCE_ID_1,
        .instCfg          = &gInstCfg[0U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 1U,
        .chCfgId          = {
                                CH_CFG_ID_RGB888_1920_1080,
                           },
    },
    /* Instance config No. 7 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_1CH_RAW12,
        .csiDrvInst       = CSIRX_INSTANCE_ID_0,
        .instCfg          = &gInstCfg[1U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 1U,
        .chCfgId          = {
                                CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH0,
                           },
    },
    /* Instance config No. 8 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_2CH_RAW12_STRM_FIFO_OVERFLOW,
        .csiDrvInst       = CSIRX_INSTANCE_ID_0,
        .instCfg          = &gInstCfg[1U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 2U,
        .chCfgId          = {
                                CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH0,
                                CH_CFG_ID_RAW12_UNPACKED_1936_1100_CH1,
                           },
    },
    /* Instance config No. 9 */
    {
        .instCfgInfoId    = INST_CFG_ID_DRV_ID0_1CH_YUV422_8BIT_DUAL_PIXEL,
        .csiDrvInst       = CSIRX_INSTANCE_ID_0,
        .instCfg          = &gInstCfg[4U],
        .frameDropBuf     = (uint64_t)NULL,
        .frameDropBufLen  = CSIRX_TEST_MAX_LINE_SIZE_BYTES,
        .numCh            = 1U,
        .chCfgId          = {
                                CH_CFG_ID_YUV422_8BIT_1920_1080,
                           },
    },

};

CsirxTestTaskCfg gTestTaskCfg[] =
{
    /* This is default configuration */
    /* Single Channel RGB Capture */
    {
        .taskCfgId   = TASK_CFG_ID_1CH_RGB888,
        .instCfgId   = INST_CFG_ID_DRV_ID0_1CH_RGB888,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },
    /* Four Channel RAW12 Capture */
    {
        .taskCfgId   = TASK_CFG_ID_4CH_RAW12,
        .instCfgId   = INST_CFG_ID_DRV_ID0_4CH_RAW12,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },
    /* Single Channel RGB Capture on 2 data lanes */
    {
        .taskCfgId   = TASK_CFG_ID_1CH_RGB888_2DL,
        .instCfgId   = INST_CFG_ID_DRV_ID0_1CH_RGB888_2DL,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },
    /* Single Channel YUV422-8bit Capture */
    {
        .taskCfgId   = TASK_CFG_ID_1CH_YUV422_8BIT,
        .instCfgId   = INST_CFG_ID_DRV_ID0_1CH_YUV422_8BIT,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },
    /* Multi Channel RGB888 Capture, Truncated/Elongated frames */
    {
        .taskCfgId   = TASK_CFG_ID_2CH_RAW12_TRUNC_ENL_FRM,
        .instCfgId   = INST_CFG_ID_DRV_ID0_2CH_RAW12_TRUNC_ENL_FRM,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },
    /* Multi Channel RGB888 and RAW12 Capture */
    {
        .taskCfgId   = TASK_CFG_ID_2CH_RGB888_RAW12,
        .instCfgId   = INST_CFG_ID_DRV_ID0_2CH_RGB888_RAW12,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },
    /* Single Channel RGB888 Capture on instance 1 */
    {
        .taskCfgId   = TASK_CFG_ID_1CH_RGB888_INST_1,
        .instCfgId   = INST_CFG_ID_DRV_ID0_1CH_RGB888_INST_1,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },
    /* Single Channel RAW12 Capture */
    {
        .taskCfgId   = TASK_CFG_ID_1CH_RAW12,
        .instCfgId   = INST_CFG_ID_DRV_ID0_1CH_RAW12,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },
    /* Two Channel RAW12 Capture Stream FIFO overflow scenario */
    {
        .taskCfgId   = TASK_CFG_ID_2CH_RAW12_STRM_FIFO_OVERFLOW,
        .instCfgId   = INST_CFG_ID_DRV_ID0_2CH_RAW12_STRM_FIFO_OVERFLOW,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },
    /* Single Channel YUV422-8bit Capture dual pixel */
    {
        .taskCfgId   = TASK_CFG_ID_1CH_YUV422_8BIT_DUAL_PIXEL,
        .instCfgId   = INST_CFG_ID_DRV_ID0_1CH_YUV422_8BIT_DUAL_PIXEL,
        .taskId      = 0U,
        .testFxnPtr  = &Csirx_captureTest,
    },

};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
static inline CsirxTestTaskCfg* Test_getTaskCfgParams(uint32_t taskCfgId)
{
    uint32_t loopCnt;

    for (loopCnt = 0U ;loopCnt < CSIRX_TEST_NUM_TASK_CFG_PARAMS ; loopCnt++)
    {
        if (gTestTaskCfg[loopCnt].taskCfgId == taskCfgId)
        {
            break;
        }
    }

    if (loopCnt < CSIRX_TEST_NUM_TASK_CFG_PARAMS)
    {
        return (&gTestTaskCfg[loopCnt]);
    }
    else
    {
        return (NULL);
    }
}
static inline CsirxChCfgInfo* Test_getChCfgParams(uint32_t chCfgId)
{
    uint32_t loopCnt;

    for (loopCnt = 0U ;loopCnt < CSIRX_TEST_NUM_CH_CFG_PARAMS ; loopCnt++)
    {
        if (gChCfgInfo[loopCnt].chCfgInfoId == chCfgId)
        {
            break;
        }
    }

    if (loopCnt < CSIRX_TEST_NUM_CH_CFG_PARAMS)
    {
        return (&gChCfgInfo[loopCnt]);
    }
    else
    {
        return (NULL);
    }
}

static inline CsirxInstCfgInfo* Test_getInstCfgParams(uint32_t instCfgId)
{
    uint32_t loopCnt;

    for (loopCnt = 0U ;loopCnt < CSIRX_TEST_NUM_INST_CFG_PARAMS ; loopCnt++)
    {
        if (gInstCfgInfo[loopCnt].instCfgInfoId == instCfgId)
        {
            break;
        }
    }

    if (loopCnt < CSIRX_TEST_NUM_INST_CFG_PARAMS)
    {
        return (&gInstCfgInfo[loopCnt]);
    }
    else
    {
        return (NULL);
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSIRX_TEST_CONFIG_H_ */
