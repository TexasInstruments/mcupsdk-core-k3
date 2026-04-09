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
#include "../test_ids.h"
#include <drivers/dss/v0/disp/dss_dispDrv.h>
#include <drivers/dss/v0/disp/dss_dispPriv.h>
#include <drivers/dss/v0/common/dss_evtMgr.h>
#include <drivers/dss/v0/dctrl/dss_dctrlDrv.h>
#include <drivers/dss/v0/dctrl/dss_dctrlPriv.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_DSS_TOTAL_FRAME_TYPES_MAX                      (33U)

/* Safety test defines */
#define TEST_DSS_SAFETY_NUM_FRAMES                          (100U)
#define TEST_DSS_SAFETY_CORRUPT_FRAME_NUM                   (70U)
#define TEST_DSS_SAFETY_FREEZE_THRESHOLD                    ((uint32_t)30U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint8_t bytesPerPixel;
    uint32_t frameType;
    char*   frameName;
} TestDss_FrameInputData;

typedef struct
{
    uint32_t safetyInterrupt;
    uint32_t regionId;
    uint32_t vpId;
    uint32_t frameCount;
    uint32_t safetyCheckMode;
    uint64_t capturedSign;
} TestDss_SafetyCbData;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */


/* Runtime VP safety globals from test_display_control.c */
extern uint32_t TestDss_numVpSafetyRegions;
extern Dss_DctrlVpSafetyChkParams TestDss_vpSafetyParamsRuntime[CSL_DSS_VP_SAFETY_REGION_MAX];

extern int32_t TestDisp_displayControl(Dss_Object *appObj);
extern int32_t TestDisp_vpSafetyDisplayControlCommon(Dss_Object *appObj, uint32_t safetyMode);
extern int32_t TestDisp_pipeSafetyDisplayControl(Dss_Object *appObj,
                                                 uint32_t safetyMode);
extern int32_t TestDisp_frameSkipDisplayControl(Dss_Object *appObj,
                                                uint32_t frameSkipVal);
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
#endif/* Safety test case declarations */
static void TestDss_vpSafetyDataIntegrityOldi(void *args);
static void TestDss_vpSafetyFreezeDetectOldi(void *args);
static void TestDss_pipeSafetyDataIntegrityOldi(void *args);
static void TestDss_pipeSafetyFreezeDetectOldi(void *args);
static void TestDss_multiRegionIndependentOldi(void *args);
static void TestDss_safetyFrameSkipOldi(void *args);
static void TestDss_bitmapClutProgrammingOldi(void *args);

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
/* Extern frame buffer from test_display_control.c (3840*1080*4 = DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX) */
extern uint8_t gFirstPipelineFrameBuf[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE][3840U*1080U*4U];
/* Extern safety callback data from test_display_control.c */
extern TestDss_SafetyCbData TestDss_vpSafetyCbData[];
extern volatile uint32_t TestDss_safetyLoopCount;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    UNITY_BEGIN();

    RUN_TEST(test_dss_mulitiple_frame_formats, 4560, NULL);
    RUN_TEST(TestDss_bitmapClutProgrammingOldi, 11282, NULL);
    RUN_TEST(TestDss_vpSafetyDataIntegrityOldi, 11257, NULL);
    RUN_TEST(TestDss_vpSafetyFreezeDetectOldi, 11256, NULL);
    RUN_TEST(TestDss_pipeSafetyDataIntegrityOldi, 11258, NULL);
    RUN_TEST(TestDss_pipeSafetyFreezeDetectOldi, 11259, NULL);
    RUN_TEST(TestDss_multiRegionIndependentOldi, 11260, NULL);
    RUN_TEST(TestDss_safetyFrameSkipOldi, 11261, NULL);

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

/**
 * \brief  VP safety data integrity detection for the OLDI interface.
 *
 *  Test Category: Functionality
 *
 *  This test configures four VP safety regions (360x270 quadrants within the
 *  VID1 active output area of 720x540) in DATA_INTEGRITY mode with zero
 *  reference MISR signature.  The display is started on VP1 (OLDI) with a
 *  single YUV420 frame.  At frame 70, the frame buffer is corrupted by
 *  overwriting a portion of the Y component data.  The test verifies that
 *  the safety error callback fires for all four regions, confirming the
 *  MISR signature mismatch detection mechanism is functional.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_vpSafetyDataIntegrityOldi(void *args)
{
    int32_t status = SystemP_FAILURE;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS VP Safety Data Integrity Test for OLDI\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format for safety test */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] =
            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] *
            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] =
                gDssConfigPipelineParams.inWidth[instCnt] *
                gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    /* Enable VP safety at runtime — CONFIG_DSS_NUM_SAFETY_REGIONS = 0 by
     * default so the IOCTL loops are compiled away. Configure 4 quadrant
     * regions within VID1 active output area (720x540 at origin) to ensure
     * all regions have active pipeline pixels for reliable MISR violation.
     * referenceSign = 0U: MISR of any real frame content is never 0. */
    TestDss_numVpSafetyRegions = 4U;
    for(uint32_t r = 0U; r < TestDss_numVpSafetyRegions; r++)
    {
        Dss_dctrlVpSafetyChkParamsInit(&TestDss_vpSafetyParamsRuntime[r]);
        TestDss_vpSafetyParamsRuntime[r].vpId             = CSL_DSS_VP_ID_1;
        /* Non-zero seed exercises CSL_dssVpSetSafetySignSeedVal().
         * referenceSign=0U means any MISR triggers violation regardless
         * of seed, so test pass/fail behaviour is unchanged. */
        TestDss_vpSafetyParamsRuntime[r].safetySignSeedVal = 0xA5A5A5A5U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.regionId      =
            r;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.referenceSign = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkEnable = TRUE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkMode   =
            CSL_DSS_SAFETY_CHK_DATA_INTEGRITY;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.seedSelectEnable = FALSE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.thresholdValue  = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.frameSkip       =
            CSL_DSS_SAFETY_CHK_FRAME_SKIP_NO;
        /* 4 quadrants within VID1 output (720x540): each 360x270 */
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionPos.startX =
            (r & 1U) ? 360U : 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionPos.startY =
            (r & 2U) ? 270U : 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionSize.width  = 360U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionSize.height = 270U;
    }

    DebugP_log("Frame type input for safety test: %s\r\n",
               gMultipleFrameDataArray[0].frameName);

    status = TestDisp_vpSafetyDisplayControlCommon(&gDssObjects[CONFIG_DSS0], CSL_DSS_SAFETY_CHK_DATA_INTEGRITY);

    /* Restore defaults */
    TestDss_numVpSafetyRegions = 0U;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("VP Safety Data Integrity test completed\r\n");
    DebugP_log("======================================================\r\n");
}

/**
 * \brief  VP safety frame freeze detection for the OLDI interface.
 *
 *  Test Category: Functionality
 *
 *  This test configures four VP safety regions (360x270 quadrants within the
 *  VID1 active output area of 720x540) in FRAME_FREEZE_DETECT mode with a
 *  threshold of TEST_DSS_SAFETY_FREEZE_THRESHOLD frames.  A single frame is
 *  queued and the display is started on VP1 (OLDI).  The same frame is
 *  repeatedly re-queued until the freeze threshold is crossed.  The test
 *  verifies that the safety error callback fires for all four regions,
 *  confirming the freeze detection mechanism is functional.  A new buffer
 *  with a different pattern is then queued to confirm the freeze clears
 *  after fresh content is provided.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_vpSafetyFreezeDetectOldi(void *args)
{
    int32_t status = SystemP_FAILURE;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS VP Safety Freeze Frame Detection Test for OLDI\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format for freeze detect test */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] =
            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] *
            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] =
                gDssConfigPipelineParams.inWidth[instCnt] *
                gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    /* Enable VP safety at runtime — 4 quadrant regions within VID1 active
     * output area (720x540 at origin) to ensure all regions have active
     * pipeline pixels. TestDisp_safetyInitDssParams will override mode to
     * FRAME_FREEZE_DETECT and set thresholdValue=TEST_DSS_SAFETY_FREEZE_THRESHOLD
     * when called with CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT mode. */
    TestDss_numVpSafetyRegions = 4U;
    for(uint32_t r = 0U; r < TestDss_numVpSafetyRegions; r++)
    {
        Dss_dctrlVpSafetyChkParamsInit(&TestDss_vpSafetyParamsRuntime[r]);
        TestDss_vpSafetyParamsRuntime[r].vpId              = CSL_DSS_VP_ID_1;
        TestDss_vpSafetyParamsRuntime[r].safetySignSeedVal = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.regionId      =
            r;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.referenceSign = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkEnable  = TRUE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkMode    =
            CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.seedSelectEnable = FALSE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.thresholdValue   =
            TEST_DSS_SAFETY_FREEZE_THRESHOLD;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.frameSkip        =
            CSL_DSS_SAFETY_CHK_FRAME_SKIP_NO;
        /* 4 quadrants within VID1 output (720x540): each 360x270 */
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionPos.startX =
            (r & 1U) ? 360U : 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionPos.startY =
            (r & 2U) ? 270U : 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionSize.width  = 360U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionSize.height = 270U;
    }

    DebugP_log("Frame type input for freeze detect test: %s\r\n",
               gMultipleFrameDataArray[0].frameName);

    status = TestDisp_vpSafetyDisplayControlCommon(&gDssObjects[CONFIG_DSS0], CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT);

    /* Restore defaults */
    TestDss_numVpSafetyRegions = 0U;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("VP Safety Freeze Frame Detection test completed\r\n");
    DebugP_log("======================================================\r\n");
}

/**
 * \brief  Pipeline safety data integrity detection for the OLDI interface.
 *
 *  Test Category: Functionality
 *
 *  This test enables DATA_INTEGRITY safety check on the VID1 pipeline with
 *  zero reference MISR signature.  The display is started on VP1 (OLDI) with
 *  a single YUV420 frame.  The test verifies that the safety error callback
 *  fires on the first frame due to MISR mismatch (zero reference signature
 *  does not match any real frame content), confirming the pipeline-level
 *  data integrity detection mechanism is functional.  Note: AM62PX VIDL1 lite
 *  pipeline safety check interrupt is not functional on this hardware.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_pipeSafetyDataIntegrityOldi(void *args)
{
    int32_t status = SystemP_FAILURE;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Pipeline Safety Data Integrity Test for OLDI\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format for pipeline safety test */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] =
            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] *
            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] =
                gDssConfigPipelineParams.inWidth[instCnt] *
                gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    /* Enable pipeline safety on VID1 only — AM62PX VIDL1 lite pipeline safety
     * check interrupt is not functional on this hardware. VID1 DATA_INTEGRITY
     * with referenceSign=0U fires on the first frame, covering
     * Dss_dispSafetyErrCbFxn. */
    {
        uint32_t instCnt = 0U;  /* VID1 only */
        gDssConfigPipelineParams.safetyCheck[instCnt] = TRUE;
        Dss_dispPipeSafetyChkParamsInit(&gDssPipelineSafetyParams[instCnt]);

        gDssPipelineSafetyParams[instCnt].safetySignSeedVal            = 0xA5A5A5A5U;
        gDssPipelineSafetyParams[instCnt].referenceSign                = 0U;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkEnable = TRUE;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkMode   =
            CSL_DSS_SAFETY_CHK_DATA_INTEGRITY;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.seedSelectEnable = FALSE;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.frameSkip        =
            CSL_DSS_SAFETY_CHK_FRAME_SKIP_NO;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionPos.startX  = 0U;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionPos.startY  = 0U;
        /* Use input (frame buffer) dimensions — pipeline safety check is
         * at the frame buffer level, before any scaler. */
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionSize.width  =
            gDssConfigPipelineParams.inWidth[instCnt];
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionSize.height =
            gDssConfigPipelineParams.inHeight[instCnt];
    }

    DebugP_log("Frame type input for pipeline safety test: %s\r\n",
               gMultipleFrameDataArray[0].frameName);

    status = TestDisp_pipeSafetyDisplayControl(
        &gDssObjects[CONFIG_DSS0],
        CSL_DSS_SAFETY_CHK_DATA_INTEGRITY);

    /* Restore syscfg defaults */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.safetyCheck[instCnt] = FALSE;
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("======================================================\r\n");
    DebugP_log("Pipeline Safety Data Integrity test completed\r\n");
    DebugP_log("======================================================\r\n");
}

/**
 * \brief  Pipeline safety frame freeze detection for the OLDI interface.
 *
 *  Test Category: Functionality
 *
 *  This test enables FRAME_FREEZE_DETECT safety check on the VID1 pipeline
 *  with a threshold of TEST_DSS_SAFETY_FREEZE_THRESHOLD frames.  A single YUV420
 *  frame is queued and the display is started on VP1 (OLDI).  The same frame
 *  is repeatedly re-queued until the freeze threshold is crossed.  The test
 *  verifies that the safety error callback fires, confirming the pipeline-level
 *  freeze detection mechanism is functional.  Note: AM62PX VIDL1 lite pipeline
 *  safety check interrupt is not functional on this hardware.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_pipeSafetyFreezeDetectOldi(void *args)
{
    int32_t status = SystemP_FAILURE;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Pipeline Safety Freeze Frame Detection Test for OLDI\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format for pipeline freeze detect test */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] =
            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] *
            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] =
                gDssConfigPipelineParams.inWidth[instCnt] *
                gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    /* Enable pipeline safety on VID1 only — AM62PX VIDL1 lite pipeline safety
     * check interrupt is not functional on this hardware. VID1 FREEZE_DETECT
     * fires after TEST_DSS_SAFETY_FREEZE_THRESHOLD identical frames. */
    {
        uint32_t instCnt = 0U;  /* VID1 only */
        gDssConfigPipelineParams.safetyCheck[instCnt] = TRUE;
        Dss_dispPipeSafetyChkParamsInit(&gDssPipelineSafetyParams[instCnt]);
        gDssPipelineSafetyParams[instCnt].safetySignSeedVal            = 0U;
        gDssPipelineSafetyParams[instCnt].referenceSign                = 0U;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkEnable  = TRUE;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkMode    =
            CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.seedSelectEnable  = FALSE;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.thresholdValue   =
            TEST_DSS_SAFETY_FREEZE_THRESHOLD;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.frameSkip        =
            CSL_DSS_SAFETY_CHK_FRAME_SKIP_NO;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionPos.startX  = 0U;
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionPos.startY  = 0U;
        /* Use input (frame buffer) dimensions — pipeline safety check is
         * at the frame buffer level, before any scaler. */
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionSize.width  =
            gDssConfigPipelineParams.inWidth[instCnt];
        gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionSize.height =
            gDssConfigPipelineParams.inHeight[instCnt];
    }

    DebugP_log("Frame type input for pipeline freeze detect test: %s\r\n",
               gMultipleFrameDataArray[0].frameName);

    status = TestDisp_pipeSafetyDisplayControl(
        &gDssObjects[CONFIG_DSS0],
        CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT);

    /* Restore syscfg defaults */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.safetyCheck[instCnt] = FALSE;
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("Pipeline Safety Freeze Frame Detection test completed\r\n");
    DebugP_log("======================================================\r\n");
}

/**
 * \brief  VP safety multi-region independent verification for the OLDI interface.
 *
 *  Test Category: Functionality
 *
 *  This test configures four VP safety regions (360x270 quadrants within the
 *  VID1 active output area of 720x540) in DATA_INTEGRITY mode with zero
 *  reference MISR signature (triggering on all frames).  The display is started
 *  on VP1 (OLDI) and the frame buffer is corrupted at frame 70.  The test
 *  verifies that all four regions fire independently with their own regionId,
 *  confirming that each safety region manages events and errors autonomously
 *  rather than being blocked or combined.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_multiRegionIndependentOldi(void *args)
{
    int32_t status = SystemP_FAILURE;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Multi-Region Independent Safety Test for OLDI\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] =
            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] *
            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] =
                gDssConfigPipelineParams.inWidth[instCnt] *
                gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    /* Enable VP safety at runtime — same 4 quadrant regions within VID1
     * active output area (720x540) as data integrity test. All regions use
     * referenceSign=0U so all trigger simultaneously, verifying each region
     * fires independently with its own regionId. */
    TestDss_numVpSafetyRegions = 4U;
    for(uint32_t r = 0U; r < TestDss_numVpSafetyRegions; r++)
    {
        Dss_dctrlVpSafetyChkParamsInit(&TestDss_vpSafetyParamsRuntime[r]);
        TestDss_vpSafetyParamsRuntime[r].vpId              = CSL_DSS_VP_ID_1;
        TestDss_vpSafetyParamsRuntime[r].safetySignSeedVal = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.regionId      =
            r;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.referenceSign = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkEnable  = TRUE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkMode    =
            CSL_DSS_SAFETY_CHK_DATA_INTEGRITY;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.seedSelectEnable = FALSE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.thresholdValue   = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.frameSkip        =
            CSL_DSS_SAFETY_CHK_FRAME_SKIP_NO;
        /* 4 quadrants within VID1 output (720x540): each 360x270 */
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionPos.startX =
            (r & 1U) ? 360U : 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionPos.startY =
            (r & 2U) ? 270U : 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionSize.width  = 360U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionSize.height = 270U;
    }

    DebugP_log("Verifying all %d regions trigger independently with correct regionId\r\n",
               TestDss_numVpSafetyRegions);

    status = TestDisp_vpSafetyDisplayControlCommon(&gDssObjects[CONFIG_DSS0], CSL_DSS_SAFETY_CHK_DATA_INTEGRITY);

    /* Restore defaults */
    TestDss_numVpSafetyRegions = 0U;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify each region triggered independently with correct region ID.
     * referenceSign=0U causes DATA_INTEGRITY violations on all checked
     * frames (MISR is never 0 for real content). Each region fires its
     * own callback and records its own regionId — proving independent
     * per-region event management even when all regions fire together. */
    DebugP_log("Verifying callback independence across regions...\r\n");

    for(uint32_t i = 0U; i < 4U; i++)
    {
        TEST_ASSERT_EQUAL_UINT32(TRUE,
            TestDss_vpSafetyCbData[i].safetyInterrupt);
        TEST_ASSERT_EQUAL_UINT32(i,
            TestDss_vpSafetyCbData[i].regionId);
        TEST_ASSERT_NOT_EQUAL(0U,
            TestDss_vpSafetyCbData[i].capturedSign);
        DebugP_log("Region %d: triggered, regionId=%d, signature=0x%lX\r\n",
                   i, TestDss_vpSafetyCbData[i].regionId,
                   TestDss_vpSafetyCbData[i].capturedSign);
    }

    DebugP_log("Multi-Region Independent Safety test completed\r\n");
    DebugP_log("======================================================\r\n");
}

/**
 * \brief  VP safety frame skip control for the OLDI interface.
 *
 *  Test Category: Functionality
 *
 *  This test configures four VP safety regions in DATA_INTEGRITY mode and
 *  enables frame skip (FRAME_SKIP_EVEN) to bypass safety checks on even-numbered
 *  frames.  The display is started on VP1 (OLDI) and the frame buffer is
 *  corrupted.  The test verifies that safety callbacks fire only on odd frames
 *  (when checks are enabled), confirming the frame skip filtering mechanism
 *  works correctly.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_safetyFrameSkipOldi(void *args)
{
    int32_t status = SystemP_FAILURE;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Safety Frame Skip Test for OLDI\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] =
            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] *
            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] =
                gDssConfigPipelineParams.inWidth[instCnt] *
                gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    /* Enable VP safety at runtime — same 4 quadrant regions within VID1
     * active output area (720x540) as other VP safety tests.
     * referenceSign=0U means any MISR of real content (never 0) triggers
     * violation on first checked frame after FRAME_SKIP_EVEN. */
    TestDss_numVpSafetyRegions = 4U;
    for(uint32_t r = 0U; r < TestDss_numVpSafetyRegions; r++)
    {
        Dss_dctrlVpSafetyChkParamsInit(&TestDss_vpSafetyParamsRuntime[r]);
        TestDss_vpSafetyParamsRuntime[r].vpId              = CSL_DSS_VP_ID_1;
        TestDss_vpSafetyParamsRuntime[r].safetySignSeedVal = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.regionId      =
            r;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.referenceSign = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkEnable  = TRUE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkMode    =
            CSL_DSS_SAFETY_CHK_DATA_INTEGRITY;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.seedSelectEnable = FALSE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.thresholdValue   = 0U;
        /* frameSkip will be overridden to CSL_DSS_SAFETY_CHK_FRAME_SKIP_EVEN
         * by TestDisp_frameSkipDisplayControl internally */
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.frameSkip        =
            CSL_DSS_SAFETY_CHK_FRAME_SKIP_NO;
        /* 4 quadrants within VID1 output (720x540): each 360x270 */
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionPos.startX =
            (r & 1U) ? 360U : 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionPos.startY =
            (r & 2U) ? 270U : 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionSize.width  = 360U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.regionSize.height = 270U;
    }

    DebugP_log("Running VP safety with frame skip = EVEN (skip even frames)\r\n");

    /* TestDisp_frameSkipDisplayControl overrides frameSkip to FRAME_SKIP_EVEN
     * for all regions, then runs the standard safety flow. With referenceSign=0U
     * the MISR mismatch occurs on the first checked (odd) frame. */
    status = TestDisp_frameSkipDisplayControl(
        &gDssObjects[CONFIG_DSS0],
        CSL_DSS_SAFETY_CHK_FRAME_SKIP_EVEN);

    /* Restore defaults */
    TestDss_numVpSafetyRegions = 0U;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify all regions triggered — TestDisp_logVpSafetyData (called
     * internally) already asserts safetyInterrupt == TRUE per region. */
    DebugP_log("Verifying safety detection with frame skip enabled...\r\n");
    for(uint32_t i = 0U; i < 4U; i++)
    {
        TEST_ASSERT_EQUAL_UINT32(TRUE, TestDss_vpSafetyCbData[i].safetyInterrupt);
        DebugP_log("  Region %d: callback triggered (frame skip EVEN)\r\n", i);
    }

    DebugP_log("Safety Frame Skip test completed\r\n");
    DebugP_log("======================================================\r\n");
}


/**
 * \brief  CLUT (Color Look-Up Table) programming and gamma table configuration.
 *
 *  Test Category: Functionality
 *
 *  This test validates the DSS CLUT programming functionality by exercising
 *  gamma table configuration with different color mappings. The test verifies:
 *    - BITMAP8 format rejection (known driver limitation)
 *    - CLUT programming with gammaEnable and rainbow color table
 *    - CLUT reprogramming with grayscale/identity mapping
 *    - Normal display operation after CLUT exercises
 *
 *  The CLUT maps palette indices to full RGB colors, allowing indexed color
 *  modes and gamma correction functionality.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_bitmapClutProgrammingOldi(void *args)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    Fvid2_InitPrms initPrms;
    Dss_InstObject *instObj;
    Dss_DispParams dispParams;
    Dss_DctrlVpParams vpParams;
    Dss_DctrlAdvVpParams advVpParams;
    Dss_DctrlOverlayParams overlayParams;
    Dss_DctrlOverlayLayerParams layerParams;
    Dss_DctrlGlobalDssParams globalDssParams;
    Fvid2_Frame frm;
    Fvid2_FrameList frmList;
    uint32_t idx;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Bitmap CLUT Programming Test (OLDI)\r\n");
    DebugP_log("======================================================\r\n");

    width  = gDssConfigPipelineParams.inWidth[0U];
    height = gDssConfigPipelineParams.inHeight[0U];

    /* Attempt FVID2_DF_BITMAP8 via IOCTL                     */
    DebugP_log("BITMAP8 format via IOCTL (expected fail)\r\n");

    /* Initialize FVID2, DSS, create DCTRL handle */
    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

    /* Configure DCTRL path */
    Dss_dctrlVpParamsInit(&vpParams);
    vpParams.vpId = gDssVpParams.vpId;
    memcpy(&vpParams.lcdOpTimingCfg.mInfo,
           &gDssVpParams.lcdOpTimingCfg.mInfo,
           sizeof(Fvid2_ModeInfo));
    vpParams.lcdOpTimingCfg.mInfo.scanFormat = FVID2_SF_PROGRESSIVE;
    vpParams.lcdOpTimingCfg.dvoFormat =
        gDssVpParams.lcdOpTimingCfg.dvoFormat;
    vpParams.lcdOpTimingCfg.videoIfWidth =
        gDssVpParams.lcdOpTimingCfg.videoIfWidth;
    vpParams.lcdPolarityCfg = gDssVpParams.lcdPolarityCfg;

    Dss_dctrlAdvVpParamsInit(&advVpParams);
    advVpParams.vpId = gDssAdvVpParams.vpId;
    advVpParams.lcdAdvSignalCfg.hVAlign =
        gDssAdvVpParams.lcdAdvSignalCfg.hVAlign;
    advVpParams.lcdAdvSignalCfg.hVClkControl =
        gDssAdvVpParams.lcdAdvSignalCfg.hVClkControl;

    Dss_dctrlOverlayParamsInit(&overlayParams);
    overlayParams.overlayId = gDssOverlayParams.overlayId;
    overlayParams.colorbarEnable = gDssOverlayParams.colorbarEnable;
    overlayParams.overlayCfg = gDssOverlayParams.overlayCfg;

    Dss_dctrlOverlayLayerParamsInit(&layerParams);
    layerParams.overlayId = gDssOverlayLayerParams.overlayId;
    memcpy(layerParams.pipeLayerNum,
           gDssOverlayLayerParams.pipeLayerNum,
           sizeof(gDssOverlayLayerParams.pipeLayerNum));

    Dss_dctrlGlobalDssParamsInit(&globalDssParams);

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_PATH,
        gDssObjects[CONFIG_DSS0].dctrlPathInfo, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS, &advVpParams, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_PARAMS, &vpParams, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    if(gDssObjects[CONFIG_DSS0].oldiParams != NULL)
    {
        retVal = Fvid2_control(
            gDssObjects[CONFIG_DSS0].dctrlHandle,
            IOCTL_DSS_DCTRL_SET_OLDI_PARAMS,
            gDssObjects[CONFIG_DSS0].oldiParams, NULL);
        TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    }

    if(gDssObjects[CONFIG_DSS0].oldiParams != NULL)
    {
        Dss_setOLDITxPowerDown(
            gDssObjects[CONFIG_DSS0].oldiParams->oldiCfg.oldiMapType, TRUE);
    }

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS, &overlayParams, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_LAYER_PARAMS, &layerParams, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS, &globalDssParams, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Create display driver */
    instObj = &gDssObjects[CONFIG_DSS0].instObj[0U];
    instObj->instId = gDssConfigPipelineParams.instId[0U];
    Dss_dispCreateParamsInit(&instObj->createParams);
    Fvid2CbParams_init(&instObj->cbParams);
    instObj->cbParams.cbFxn = NULL;

    status = SemaphoreP_constructBinary(&instObj->syncSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    instObj->drvHandle = Fvid2_create(
        DSS_DISP_DRV_ID,
        instObj->instId,
        &instObj->createParams,
        &instObj->createStatus,
        &instObj->cbParams);
    TEST_ASSERT_NOT_NULL(instObj->drvHandle);

    /* Configure BITMAP8: 1 byte per pixel, pitch = width * 1.
     * The frame buffer contains palette indices (0–255) and the
     * 256-entry CLUT maps each index to a full RGB color.
     * gammaEnable is FALSE for true bitmap/palette mode. */
    Dss_dispParamsInit(&dispParams);
    dispParams.pipeCfg.pipeType =
        gDssConfigPipelineParams.pipeType[0U];
    dispParams.pipeCfg.inFmt.width  = width;
    dispParams.pipeCfg.inFmt.height = height;
    dispParams.pipeCfg.inFmt.pitch[0U] = width;   /* 1 byte/pixel for BITMAP8 */
    dispParams.pipeCfg.inFmt.dataFormat = FVID2_DF_BITMAP8;
    dispParams.pipeCfg.inFmt.scanFormat =
        gDssConfigPipelineParams.inScanFmt[0U];
    dispParams.pipeCfg.outWidth  = width;
    dispParams.pipeCfg.outHeight = height;
    dispParams.pipeCfg.scEnable  = FALSE;
    dispParams.pipeCfg.gammaEnable = FALSE;   /* palette mode, not gamma */
    dispParams.pipeCfg.nibbleModeEnable = FALSE;
    dispParams.layerPos.startX   = gDssConfigPipelineParams.posx[0U];
    dispParams.layerPos.startY   = gDssConfigPipelineParams.posy[0U];

    /* Program 256-entry rainbow CLUT: index -> full RGB color.
     * CLUT_0 register format: bits[31:24]=INDEX, [23:16]=R, [15:8]=G, [7:0]=B */
    for(idx = 0U; idx < CSL_DSS_NUM_LUT_ENTRIES; idx++)
    {
        uint32_t sector = (idx * 6U) / 256U;
        uint32_t offset = ((idx * 6U) % 256U);
        uint8_t r = 0U, g = 0U, b = 0U;
        switch(sector)
        {
            case 0U: r = 255U; g = (uint8_t)offset;       b = 0U;   break;
            case 1U: r = (uint8_t)(255U - offset); g = 255U; b = 0U;   break;
            case 2U: r = 0U;   g = 255U; b = (uint8_t)offset;       break;
            case 3U: r = 0U;   g = (uint8_t)(255U - offset); b = 255U; break;
            case 4U: r = (uint8_t)offset;       g = 0U;   b = 255U; break;
            default: r = 255U; g = 0U;   b = (uint8_t)(255U - offset); break;
        }
        dispParams.pipeCfg.clutData[idx] =
            (idx << 24U) | ((uint32_t)r << 16U) |
            ((uint32_t)g << 8U) | (uint32_t)b;
    }

    /* IOCTL should FAIL: CSL_dssVidPipeGetRowInc returns CSL_EBADARGS
     * for bitmap formats because they are not handled in the pitch
     * classification (Fvid2_isDataFmtRgb16/24/32/64bit, Fvid2_isDataFmtYuv). */
    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_DSS_DISP_SET_DSS_PARAMS,
        &dispParams, NULL);
    TEST_ASSERT_NOT_EQUAL(FVID2_SOK, retVal);
    DebugP_log("  BITMAP8 IOCTL correctly rejected (retVal=%d)\r\n", retVal);
    DebugP_log("  BITMAP8 negative test PASSED\r\n");

    /*  gammaEnable=TRUE with BGRA32 + rainbow CLUT            */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" gammaEnable + rainbow CLUT (BGRA32)\r\n");

    pitch = width * 4U;   /* BGRA32 = 4 bytes/pixel */

    Dss_dispParamsInit(&dispParams);
    dispParams.pipeCfg.pipeType =
        gDssConfigPipelineParams.pipeType[0U];
    dispParams.pipeCfg.inFmt.width  = width;
    dispParams.pipeCfg.inFmt.height = height;
    dispParams.pipeCfg.inFmt.pitch[0U] = pitch;
    dispParams.pipeCfg.inFmt.dataFormat = FVID2_DF_BGRA32_8888;
    dispParams.pipeCfg.inFmt.scanFormat =
        gDssConfigPipelineParams.inScanFmt[0U];
    dispParams.pipeCfg.outWidth  = width;
    dispParams.pipeCfg.outHeight = height;
    dispParams.pipeCfg.scEnable  = FALSE;
    dispParams.layerPos.startX   = gDssConfigPipelineParams.posx[0U];
    dispParams.layerPos.startY   = gDssConfigPipelineParams.posy[0U];

    /* Enable gamma to trigger CLUT programming path */
    dispParams.pipeCfg.gammaEnable = TRUE;

    /* Rainbow CLUT: index -> rainbow color.
     * Format: 0xIIRRGGBB where II=index (CLUT_0 register addressing) */
    for(idx = 0U; idx < CSL_DSS_NUM_LUT_ENTRIES; idx++)
    {
        uint32_t sector = (idx * 6U) / 256U;
        uint32_t offset = ((idx * 6U) % 256U);
        uint8_t r = 0U, g = 0U, b = 0U;
        switch(sector)
        {
            case 0U: r = 255U; g = (uint8_t)offset;       b = 0U;   break;
            case 1U: r = (uint8_t)(255U - offset); g = 255U; b = 0U;   break;
            case 2U: r = 0U;   g = 255U; b = (uint8_t)offset;       break;
            case 3U: r = 0U;   g = (uint8_t)(255U - offset); b = 255U; break;
            case 4U: r = (uint8_t)offset;       g = 0U;   b = 255U; break;
            default: r = 255U; g = 0U;   b = (uint8_t)(255U - offset); break;
        }
        dispParams.pipeCfg.clutData[idx] =
            (idx << 24U) | ((uint32_t)r << 16U) |
            ((uint32_t)g << 8U) | (uint32_t)b;
    }

    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_DSS_DISP_SET_DSS_PARAMS,
        &dispParams, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  Rainbow CLUT + gammaEnable config accepted (FVID2_SOK)\r\n");

    /* Fill frame buffer with vertical gradient: each row has a uniform
     * gray value (row % 256).  With the CLUT, row N's channels each
     * look up CLUT[N % 256], producing rainbow horizontal bands. */
    {
        uint8_t *fb = &gFirstPipelineFrameBuf[0U][0U];
        uint32_t row, col;
        for(row = 0U; row < height; row++)
        {
            uint8_t val = (uint8_t)(row % 256U);
            uint8_t *rowPtr = fb + (row * pitch);
            for(col = 0U; col < width; col++)
            {
                /* BGRA32: B=val, G=val, R=val, A=0xFF */
                rowPtr[col * 4U + 0U] = val;
                rowPtr[col * 4U + 1U] = val;
                rowPtr[col * 4U + 2U] = val;
                rowPtr[col * 4U + 3U] = 0xFFU;
            }
        }
        CacheP_wbInv(fb, height * pitch, CacheP_TYPE_ALL);
    }

    /* Queue, start, display for 1 second, stop */
    Fvid2Frame_init(&frm);
    frm.addr[0U] = (uint64_t)&gFirstPipelineFrameBuf[0U][0U];
    frm.fid = FVID2_FID_FRAME;

    Fvid2FrameList_init(&frmList);
    frmList.frames[0U] = &frm;
    frmList.numFrames = 1U;

    retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    retVal = Fvid2_start(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  Display started with rainbow CLUT — rendering gradient\r\n");

    ClockP_sleep(1U);

    retVal = Fvid2_stop(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Fvid2FrameList_init(&frmList);
    retVal = Fvid2_dequeue(instObj->drvHandle, &frmList, 0U,
                           FVID2_TIMEOUT_NONE);
    DebugP_log("  Rainbow CLUT display PASSED\r\n");

    /*CLUT reprogramming — grayscale/identity palette        */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("CLUT reprogramming (grayscale identity)\r\n");

    Dss_dispParamsInit(&dispParams);
    dispParams.pipeCfg.pipeType =
        gDssConfigPipelineParams.pipeType[0U];
    dispParams.pipeCfg.inFmt.width  = width;
    dispParams.pipeCfg.inFmt.height = height;
    dispParams.pipeCfg.inFmt.pitch[0U] = pitch;
    dispParams.pipeCfg.inFmt.dataFormat = FVID2_DF_BGRA32_8888;
    dispParams.pipeCfg.inFmt.scanFormat =
        gDssConfigPipelineParams.inScanFmt[0U];
    dispParams.pipeCfg.outWidth  = width;
    dispParams.pipeCfg.outHeight = height;
    dispParams.pipeCfg.scEnable  = FALSE;
    dispParams.layerPos.startX   = gDssConfigPipelineParams.posx[0U];
    dispParams.layerPos.startY   = gDssConfigPipelineParams.posy[0U];
    dispParams.pipeCfg.gammaEnable = TRUE;

    /* Identity CLUT: CLUT[N] = (N,N,N) — no color change.
     * Format: 0xIIRRGGBB where II=index */
    for(idx = 0U; idx < CSL_DSS_NUM_LUT_ENTRIES; idx++)
    {
        dispParams.pipeCfg.clutData[idx] =
            (idx << 24U) | (idx << 16U) | (idx << 8U) | idx;
    }

    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_DSS_DISP_SET_DSS_PARAMS,
        &dispParams, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  Grayscale CLUT applied (FVID2_SOK)\r\n");

    /* Queue, start, display, stop */
    Fvid2Frame_init(&frm);
    frm.addr[0U] = (uint64_t)&gFirstPipelineFrameBuf[0U][0U];
    frm.fid = FVID2_FID_FRAME;

    Fvid2FrameList_init(&frmList);
    frmList.frames[0U] = &frm;
    frmList.numFrames = 1U;

    retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    retVal = Fvid2_start(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  Display started with grayscale CLUT\r\n");

    ClockP_sleep(1U);

    retVal = Fvid2_stop(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Fvid2FrameList_init(&frmList);
    retVal = Fvid2_dequeue(instObj->drvHandle, &frmList, 0U,
                           FVID2_TIMEOUT_NONE);
    DebugP_log("Grayscale CLUT reprogramming PASSED\r\n");

    /* Cleanup */
    retVal = Fvid2_delete(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    SemaphoreP_destruct(&instObj->syncSem);

    Dss_dctrlVpParamsInit(&vpParams);
    vpParams.vpId = gDssVpParams.vpId;
    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_STOP_VP, &vpParams, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_CLEAR_PATH,
        gDssObjects[CONFIG_DSS0].dctrlPathInfo, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /*Full display cycle (baseline verification)             */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" Full display cycle (baseline)\r\n");

    for(idx = 0U; idx < gDssConfigPipelineParams.numTestPipes; idx++)
    {
        gDssConfigPipelineParams.inDataFmt[idx] = FVID2_DF_BGRA32_8888;
        gDssConfigPipelineParams.pitch[idx][0U] =
            gDssConfigPipelineParams.inWidth[idx] * 4U;
    }

    status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("Full display cycle PASSED\r\n");

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Bitmap CLUT Programming Test (OLDI) Completed!\r\n");
    DebugP_log("======================================================\r\n");
}
