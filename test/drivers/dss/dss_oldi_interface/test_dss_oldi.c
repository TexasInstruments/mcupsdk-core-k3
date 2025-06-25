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
#if defined (SOC_AM62PX)
#include "test_ids.h"
#endif

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
#if defined (SOC_AM62PX)
extern int32_t TestDisp_ioctlErrors(Dss_Object *appObj, uint32_t testId);
extern int32_t TestDisp_dctrlIoctls(Dss_Object *appObj, uint32_t testId);
#endif

/* Test Cases */
static void test_dss_mulitiple_frame_formats(void *args);
#if defined (SOC_AM62PX)
static void TestDisp_initErrorChecks(void *args);
static void TestDisp_ioctlErrorChecks(uint32_t testId);
static void TestDisp_dctrlIoctl(uint32_t testId);
static void TestDisp_verifyOldiMapType(void *args);
static void TestDisp_ioctltestIDparams(void *args);
static void TestDisp_dctrlioctltestIDparams(void *args);
#endif

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

extern uint32_t gLineNumCallbackHit;
extern uint32_t gSyncLostCallbackHit;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    UNITY_BEGIN();

    RUN_TEST(test_dss_mulitiple_frame_formats, 4560, NULL);

#if defined (SOC_AM62PX)
    /* Disable the FVID2 asserts */
    Fvid2Utils_controlAssert(false);

    RUN_TEST(TestDisp_dctrlioctltestIDparams, 6069, NULL);

    RUN_TEST(TestDisp_verifyOldiMapType, 7529, NULL);

    RUN_TEST(TestDisp_ioctltestIDparams, 6070, NULL);

    RUN_TEST(TestDisp_initErrorChecks, 6071, NULL);

    /* Enable back the FVID2 asserts */
    Fvid2Utils_controlAssert(true);

#endif

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

#if defined (SOC_AM62PX)
static void TestDisp_dctrlioctltestIDparams(void *args)
{
    /* Passing TEST_DSS_IOCTL_DCTRL_LINENUM_CB testID to TestDisp_dctrlIoctl*/
    DebugP_log("Test for registering a line callback \r\n");
    TestDisp_dctrlIoctl(TEST_DSS_IOCTL_DCTRL_LINENUM_CB);

    /* Passing TEST_DSS_IOCTL_DCTRL_SYNCLOST_CB testID to TestDisp_dctrlIoctl */
    DebugP_log("Test for registering a sync lost callback \r\n");
    TestDisp_dctrlIoctl(TEST_DSS_IOCTL_DCTRL_SYNCLOST_CB);

    /* Passing TEST_DSS_IOCTL_DCTRL_INVALID_IOCTL testID to TestDisp_dctrlIoctl */
    DebugP_log("Test for registering a invalid IOCTL testID \r\n");
    TestDisp_dctrlIoctl(TEST_DSS_IOCTL_DCTRL_INVALID_IOCTL);

    /* Passing TEST_DSS_IOCTL_DCTRL_INVALID_VP_ERR_STATS testID to TestDisp_dctrlIoctl */
    DebugP_log("Call ioctl for pipeline errors \r\n");
    TestDisp_dctrlIoctl(TEST_DSS_IOCTL_DCTRL_INVALID_VP_ERR_STATS);

    /* This should always be called in the end */
    DebugP_log("Test for registering a ioctl dctrl de-init error \r\n");
    TestDisp_dctrlIoctl(TEST_DSS_IOCTL_DCTRL_DEINIT_ERR);
}

static void TestDisp_ioctltestIDparams(void *args)
{
    /* Passing TEST_DSS_DISP_VSYNC_ENABLE testId to TestDisp_ioctlErrorChecks */
    DebugP_log("Create display driver with vsync enabled\r\n");
    TestDisp_ioctlErrorChecks(TEST_DSS_DISP_VSYNC_ENABLE);

    /* Passing TEST_DSS_IOCTL_DCTRL_SET_INVALID_PATH_INFO testId to TestDisp_ioctlErrorChecks */
    DebugP_log("Set invalid overlay path info\r\n");
    TestDisp_ioctlErrorChecks(TEST_DSS_IOCTL_DCTRL_SET_INVALID_PATH_INFO);

    /* Passing TEST_DSS_IOCTL_DCTRL_SET_ZERO_PATH_EDGES testId to TestDisp_ioctlErrorChecks */
    DebugP_log("Set invalid vp id for driver creation\r\n");
    TestDisp_ioctlErrorChecks(TEST_DSS_IOCTL_DCTRL_SET_ZERO_PATH_EDGES);

    /* Passing TEST_DSS_IOCTL_DCTRL_SET_INVALID_VP_ID testId to TestDisp_ioctlErrorChecks */
    DebugP_log("Configure display control with invalid vp id\r\n");
    TestDisp_ioctlErrorChecks(TEST_DSS_IOCTL_DCTRL_SET_INVALID_VP_ID);

    /* Passing TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_LAYER_NUM testId to TestDisp_ioctlErrorChecks */
    DebugP_log("Configure display control with wrong number of overlays\r\n");
    TestDisp_ioctlErrorChecks(TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_LAYER_NUM);

     /* Passing TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_ID testId to TestDisp_ioctlErrorChecks */
    DebugP_log("Configure display control with wrong overlay id\r\n");
    TestDisp_ioctlErrorChecks(TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_ID);
    Fvid2Utils_controlAssert(false);

    /* Passing TEST_DSS_IOCTL_DCTRL_SET_INVALID_LAYER_PARAMS testId to TestDisp_ioctlErrorChecks */
    DebugP_log("Set invalid layer params dor dctrl \r\n");
    TestDisp_ioctlErrorChecks(TEST_DSS_IOCTL_DCTRL_SET_INVALID_LAYER_PARAMS);

    /* Passing TEST_DSS_IOCTL_DCTRL_SET_INVALID_ADV_VP_ID testId to TestDisp_ioctlErrorChecks */
    DebugP_log("Configure display driver with invalid adv vp id\r\n");
    TestDisp_ioctlErrorChecks(TEST_DSS_IOCTL_DCTRL_SET_INVALID_ADV_VP_ID);

    /* Passing TEST_DSS_IOCTL_DCTRL_INVALID_SAFETY_CHK_PRMS testId to TestDisp_ioctlErrorChecks */
    DebugP_log("Set display control with invalid safety params\r\n");
    TestDisp_ioctlErrorChecks(TEST_DSS_IOCTL_DCTRL_INVALID_SAFETY_CHK_PRMS);
}

static void TestDisp_ioctlErrorChecks(uint32_t testId)
{
    int32_t status = SystemP_SUCCESS;

    for(uint32_t instCnt = 0U; \
        instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = \
                            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0U] = \
                            gDssConfigPipelineParams.inWidth[instCnt] * \
                            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] = \
                            gDssConfigPipelineParams.inWidth[instCnt] * \
                            gMultipleFrameDataArray[0].bytesPerPixel;
        }

        DebugP_log("Calling ioctl for test IDs: %d %s\r\n", \
                    testId,gMultipleFrameDataArray[0].frameName);
        status = TestDisp_ioctlErrors(&gDssObjects[CONFIG_DSS0], testId);
        if(testId == TEST_DSS_DISP_VSYNC_ENABLE)
        {
            TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
        }
        else
        {
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        }
    }

}

static void TestDisp_dctrlIoctl(uint32_t testId)
{
    int32_t status = SystemP_FAILURE;
        for(uint32_t instCnt = 0U; \
            instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            gDssConfigPipelineParams.inDataFmt[instCnt] = \
                                gMultipleFrameDataArray[0].frameType;
            gDssConfigPipelineParams.pitch[instCnt][0U] = \
                                gDssConfigPipelineParams.inWidth[instCnt] * \
                                gMultipleFrameDataArray[0].bytesPerPixel;

            if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
            {
                gDssConfigPipelineParams.pitch[instCnt][1] = \
                                gDssConfigPipelineParams.inWidth[instCnt] * \
                                gMultipleFrameDataArray[0].bytesPerPixel;
            }
        }

        DebugP_log("Configure display control for different tests: %s\r\n", \
                    gMultipleFrameDataArray[0].frameName);
        status = TestDisp_dctrlIoctls(&gDssObjects[CONFIG_DSS0], testId);
        if(testId == TEST_DSS_IOCTL_DCTRL_DEINIT_ERR || testId == TEST_DSS_DCTRL_DRV_DELETE_ERR 
            || testId == TEST_DSS_IOCTL_DCTRL_INVALID_VP_ERR_STATS || testId == TEST_DSS_IOCTL_DCTRL_STOP_VP)
        {
            TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
        }
        else
        {
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        }

}

static void TestDisp_initErrorChecks(void *args)
{
    int32_t status = SystemP_SUCCESS;
    Dss_InitParams initParams;

    DebugP_log("Test invalid values for initalization\r\n");

    /* Calling initParams init with NULL parameter */
    Dss_initParamsInit(NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Calling DSS init with NULL parameters */
    status = Dss_init(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_EBADARGS, status);

    /* DSS init with pipe and port not available*/
    Dss_initParamsInit(&initParams);
    initParams.socParams.rmInfo.isPortAvailable[0]      = FALSE;
    initParams.socParams.rmInfo.isPipeAvailable[0]      = FALSE;
    initParams.socParams.rmInfo.isCommRegAvailable[0]   = FALSE;
    initParams.socParams.rmInfo.isOverlayAvailable[0]   = FALSE;
    status = Dss_init(&initParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    Dss_deInit();
}

static void TestDisp_verifyOldiMapType(void *args)
{
    int32_t status = SystemP_FAILURE;

    for(uint32_t instCnt = 0U; \
        instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = \
                            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0U] = \
                            gDssConfigPipelineParams.inWidth[instCnt] * \
                            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] = \
                            gDssConfigPipelineParams.inWidth[instCnt] * \
                            gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    DebugP_log("Configure display for different oldi map types: %s\r\n", \
                gMultipleFrameDataArray[0].frameName);
    status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gDssObjects[CONFIG_DSS0].oldiParams->oldiCfg.oldiMapType = CSL_DSS_VP_OLDI_MAP_TYPE_E;
    status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gDssObjects[CONFIG_DSS0].oldiParams->oldiCfg.oldiMapType = CSL_DSS_VP_OLDI_MAP_TYPE_D;
    status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gDssObjects[CONFIG_DSS0].oldiParams->oldiCfg.oldiMapType = CSL_DSS_VP_OLDI_MAP_TYPE_C;
    status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gDssObjects[CONFIG_DSS0].oldiParams->oldiCfg.oldiMapType = CSL_DSS_VP_OLDI_MAP_TYPE_B;
    status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gDssObjects[CONFIG_DSS0].oldiParams->oldiCfg.oldiMapType = CSL_DSS_VP_OLDI_MAP_TYPE_A;
    status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    gDssObjects[CONFIG_DSS0].oldiParams->oldiCfg.oldiMapType = CSL_DSS_VP_OLDI_MAP_TYPE_F+1;
    status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

}
#endif
