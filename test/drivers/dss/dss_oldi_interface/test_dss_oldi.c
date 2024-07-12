/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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
 *  \file test_dss.c
 *
 *  \brief DSS test application listing all test cases.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_DSS_TOTAL_FRAME_TYPES_MAX                      (33U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint8_t bytesPerPixel;
    uint32_t frameType;
    char*   frameName;
} TestDss_FrameInputData;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern int32_t TestDisp_displayControl(Dss_Object *appObj);

/* Test Cases */
static void test_dss_mulitiple_frame_formats(void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

TestDss_FrameInputData gMultipleFrameDataArray[TEST_DSS_TOTAL_FRAME_TYPES_MAX] =
{
    /* 24-bit frame formats */
    { 3U, FVID2_DF_BGR24_888, "FVID2_DF_BGR24_888"},
    { 3U, FVID2_DF_RGB24_888, "FVID2_DF_RGB24_888"},
    /* 32-bit frame formats */
    { 4U, FVID2_DF_ARGB32_8888, "FVID2_DF_ARGB32_8888"},
    { 4U, FVID2_DF_RGBA32_8888, "FVID2_DF_RGBA32_8888"},
    { 4U, FVID2_DF_BGRA32_8888, "FVID2_DF_BGRA32_8888"},
    { 4U, FVID2_DF_ABGR32_8888, "FVID2_DF_ABGR32_8888"},
    { 4U, FVID2_DF_BGRA32_1010102, "FVID2_DF_BGRA32_1010102"},
    { 4U, FVID2_DF_RGBA32_1010102, "FVID2_DF_RGBA32_1010102"},
    { 4U, FVID2_DF_BGRX32_8888, "FVID2_DF_BGRX32_8888"},
    { 4U, FVID2_DF_RGBX24_8888, "FVID2_DF_RGBX24_8888"},
    { 4U, FVID2_DF_XBGR24_8888, "FVID2_DF_XBGR24_8888"},
    { 4U, FVID2_DF_XRGB32_8888, "FVID2_DF_XRGB32_8888"},
    { 4U, FVID2_DF_BGRX32_1010102, "FVID2_DF_BGRX32_1010102"},
    { 4U, FVID2_DF_RGBX32_1010102, "FVID2_DF_RGBX32_1010102"},
    /* 16-bit frame formats */
    { 2U, FVID2_DF_BGRA16_4444, "FVID2_DF_BGRA16_4444"},
    { 2U, FVID2_DF_RGBA16_4444, "FVID2_DF_RGBA16_4444"},
    { 2U, FVID2_DF_ABGR16_4444, "FVID2_DF_ABGR16_4444"},
    { 2U, FVID2_DF_BGR16_565, "FVID2_DF_BGR16_565"},
    { 2U, FVID2_DF_RGB16_565, "FVID2_DF_RGB16_565"},
    { 2U, FVID2_DF_BGRA16_5551, "FVID2_DF_BGRA16_5551"},
    { 2U, FVID2_DF_RGBA16_5551, "FVID2_DF_RGBA16_5551"},
    { 2U, FVID2_DF_BGRX_4444, "FVID2_DF_BGRX_4444"},
    { 2U, FVID2_DF_RGBX16_4444, "FVID2_DF_RGBX16_4444"},
    { 2U, FVID2_DF_XBGR_4444, "FVID2_DF_XBGR_4444"},
    { 2U, FVID2_DF_BGRX16_5551, "FVID2_DF_BGRX16_5551"},
    { 2U, FVID2_DF_RGBX16_5551, "FVID2_DF_RGBX16_5551"},
    /* 64-bit frame formats */
    { 8U, FVID2_DF_BGRA64_16161616, "FVID2_DF_BGRA64_16161616"},
    { 8U, FVID2_DF_ABGR64_16161616, "FVID2_DF_ABGR64_16161616"},
    { 8U, FVID2_DF_BGRX64_16161616, "FVID2_DF_BGRX64_16161616"},
    { 8U, FVID2_DF_XBGR64_16161616, "FVID2_DF_XBGR64_16161616"},
    /* YUV frame formats */
    { 1U, FVID2_DF_YUV420SP_UV, "FVID2_DF_YUV420SP_UV"},
    { 2U, FVID2_DF_YUV422I_YUYV, "FVID2_DF_YUV422I_YUYV"},
    { 2U, FVID2_DF_YUV422I_UYVY, "FVID2_DF_YUV422I_UYVY"},
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    UNITY_BEGIN();

    RUN_TEST(test_dss_mulitiple_frame_formats, 4560, NULL);

    UNITY_END();

    return;
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
    /* Do nothing */
}

void tearDown(void)
{
    /* Do nothing */
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

/*
 * Test case
 */
static void test_dss_mulitiple_frame_formats(void *args)
{
    int32_t status = SystemP_FAILURE;

    for(uint32_t count = 0U; \
        count < TEST_DSS_TOTAL_FRAME_TYPES_MAX; count++)
    {
        for(uint32_t instCnt = 0U; \
            instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            gDssConfigPipelineParams.inDataFmt[instCnt] = \
                                gMultipleFrameDataArray[count].frameType;
            gDssConfigPipelineParams.pitch[instCnt][0U] = \
                                gDssConfigPipelineParams.inWidth[instCnt] * \
                                gMultipleFrameDataArray[count].bytesPerPixel;

            if(gMultipleFrameDataArray[count].frameType == FVID2_DF_YUV420SP_UV)
            {
                gDssConfigPipelineParams.pitch[instCnt][1] = \
                                gDssConfigPipelineParams.inWidth[instCnt] * \
                                gMultipleFrameDataArray[count].bytesPerPixel;
            }
        }

        DebugP_log("------------------------------------------------------\r\n");
        DebugP_log("Frame type input for test: %s\r\n", \
                    gMultipleFrameDataArray[count].frameName);
        status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    DebugP_log("------------------------------------------------------\r\n");

}

