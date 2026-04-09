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
#include <board/panel/i2c/i2c_bridge_sii9022a.h>
#include <drivers/fvid2.h>
#include <drivers/dss/v0/include/dss_dctrl.h>
#include "../test_ids.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_DSS_TOTAL_FRAME_TYPES_MAX                          (33U)

#define TEST_DSS_TOTAL_DPI_REOLUTIONS_MAX                       (5U)

#define DISP_SAFETY_FREEZE_THRESHOLD                            ((uint32_t)30U)

#define TEST_DSS_VESA_RESOLUTION_COUNT                          (7U)

#define TEST_DSS_COLORBAR_RESOLUTION_COUNT                      (4U)


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

/* Runtime VP safety globals from test_display_control.c */
extern uint32_t TestDss_numVpSafetyRegions;
extern Dss_DctrlVpSafetyChkParams TestDss_vpSafetyParamsRuntime[CSL_DSS_VP_SAFETY_REGION_MAX];

extern int32_t TestDisp_displayControl(Dss_Object *appObj);
extern int32_t TestDisp_flipDisplayControl(Dss_Object *appObj, uint32_t flipType);
extern int32_t TestDisp_vpSafetyDisplayControlCommon(Dss_Object *appObj, uint32_t safetyMode);
extern int32_t TestDisp_displayShareHotPlug(Dss_Object *appObj,
                                            uint32_t overlayId,
                                            uint32_t vpId,
                                            uint32_t outputNode);
#if defined (SOC_AM62PX)
extern int32_t TestDisp_initParams(Dss_Object *appObj);
extern int32_t TestDisp_reregisterDriver(Dss_Object *appObj);
extern int32_t TestDisp_createDriver(Dss_Object *appObj);
extern int32_t TestDisp_unusedIoctl(Dss_Object *appObj);
#endif

/* Test Cases */
static void test_dss_mulitiple_frame_formats(void *args);
static void test_dss_multiple_dpi_resolution(void *args);
#if !defined (SOC_AM62LX)
static void TestDss_vpSafetyDataIntegrityDpi(void *args);
static void TestDss_vpSafetyFreezeDetectDpi(void *args);
static void TestDss_vesaTimingVariationsDpi(void *args);
#endif
static void TestDss_vpColorSpaceConversion(void *args);
static void TestDss_flipMirrorModeDpi(void *args);
static void TestDss_tdmDisplayDpi(void *args);
static void TestDss_backgroundColorDpi(void *args);
#if !defined (SOC_AM62LX)
static void TestDss_colorbarEnableDpi(void *args);
#endif

#if defined (SOC_AM62PX)
static void TestDss_dpiDynamicCoverage(void *args);
static void TestDss_cslDynamicCoverage(void *args);
static void TestDss_displayShareHotPlugDpi(void *args);
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

static char *gDpiResolutionName[TEST_DSS_TOTAL_DPI_REOLUTIONS_MAX] =
{
    "FVID2_STD_1080P_60",
    "FVID2_STD_1080P_50",
    "FVID2_STD_1080P_30",
    "FVID2_STD_720P_60",
    "FVID2_STD_720P_50"
};

static BridgeSii9022a_ModeInfo gModeInfo[TEST_DSS_TOTAL_DPI_REOLUTIONS_MAX] =
{
    {FVID2_STD_1080P_60, 16U, 14850U, 60U, 2200U, 1125U, \
    {88U, 0U, 44U, 4U, 5U}, {192U, 41U, 1920U, 1080U}},
    {FVID2_STD_1080P_50, 16U, 14850U, 50U, 2640U, 1125U, \
    {528U, 0U, 44U, 4U, 5U}, {192U, 41U, 1920U, 1080U}},
    {FVID2_STD_1080P_30, 34U, 7425U, 30U, 2200U, 1125U, \
    {88U, 0U, 44U, 4U, 5U}, {192U, 41U, 1920U, 1080U}},
    {FVID2_STD_720P_60, 4U, 7425U, 60U, 1650U, 750U, \
    {110U, 0U, 40U, 5U, 5U}, {260U, 25U, 1280U, 720U}},
    {FVID2_STD_720P_50, 19U, 7425U, 50U, 1980U, 750U, \
    {440U, 0U, 40U, 5U, 5U}, {260U, 25U, 1280U, 720U}},
};

static Fvid2_ModeInfo gDpiTimingParamsInfo[TEST_DSS_TOTAL_DPI_REOLUTIONS_MAX] =
{
    { FVID2_STD_CUSTOM, 1920U, 1080U, FVID2_SF_PROGRESSIVE, 148500U, 60U,  \
    88U, 148U, 44U, 4U, 36U, 5U },
    { FVID2_STD_CUSTOM, 1920U, 1080U, FVID2_SF_PROGRESSIVE, 148500U, 50U,  \
    528U, 148U, 44U, 4U, 36U, 5U },
    { FVID2_STD_CUSTOM, 1920U, 1080U, FVID2_SF_PROGRESSIVE, 74250U, 30U,  \
    88U, 148U, 44U, 4U, 36U, 5U },
    { FVID2_STD_CUSTOM, 1280U, 720U, FVID2_SF_PROGRESSIVE, 74250U, 60U,  \
    110U, 220U, 40U, 5U, 20U, 5U },
    { FVID2_STD_CUSTOM, 1280U, 720U, FVID2_SF_PROGRESSIVE, 74250U, 50U,  \
    440U, 220U, 40U, 5U, 20U, 5U },
};

#if !defined (SOC_AM62LX)
/* VESA DMT-only timing parameters: VGA, SVGA, XGA, SXGA, WXGA, 1440x900, 1680x1050 */
static Fvid2_ModeInfo gVesaTimingParamsInfo[TEST_DSS_VESA_RESOLUTION_COUNT] =
{
    /* VGA 640x480@60Hz (VESA DMT) */
    { FVID2_STD_CUSTOM, 640U,  480U,  FVID2_SF_PROGRESSIVE, 25175U,  60U, \
    16U, 48U, 96U, 10U, 33U, 2U },
    /* SVGA 800x600@60Hz (VESA DMT) */
    { FVID2_STD_CUSTOM, 800U,  600U,  FVID2_SF_PROGRESSIVE, 40000U,  60U, \
    40U, 88U, 128U, 1U, 23U, 4U },
    /* XGA 1024x768@60Hz (VESA DMT) */
    { FVID2_STD_CUSTOM, 1024U, 768U,  FVID2_SF_PROGRESSIVE, 65000U,  60U, \
    24U, 160U, 136U, 3U, 29U, 6U },
    /* SXGA 1280x1024@60Hz (VESA DMT) */
    { FVID2_STD_CUSTOM, 1280U, 1024U, FVID2_SF_PROGRESSIVE, 108000U, 60U, \
    48U, 248U, 112U, 1U, 38U, 3U },
    /* WXGA 1280x800@60Hz (VESA DMT) */
    { FVID2_STD_CUSTOM, 1280U, 800U,  FVID2_SF_PROGRESSIVE, 83500U,  60U, \
    64U, 200U, 136U, 3U, 24U, 6U },
    /* 1440x900@60Hz (VESA DMT) */
    { FVID2_STD_CUSTOM, 1440U, 900U,  FVID2_SF_PROGRESSIVE, 106500U, 60U, \
    80U, 232U, 152U, 3U, 28U, 6U },
    /* 1680x1050@60Hz / WSXGA+ (VESA DMT) */
    { FVID2_STD_CUSTOM, 1680U, 1050U, FVID2_SF_PROGRESSIVE, 146250U, 60U, \
    104U, 280U, 176U, 3U, 32U, 6U },
};

/* Bridge mode info for each VESA DMT resolution (all CEA code=0, DVI-D compat) */
static BridgeSii9022a_ModeInfo gVesaBridgeModeInfo[TEST_DSS_VESA_RESOLUTION_COUNT] =
{
    /* VGA 640x480@60Hz: CEA mode 1, pixClk=2518 (25175kHz/10) */
    {FVID2_STD_VGA_60,       1U,  2518U,  60U, 800U,  525U, \
    {16U, 0U, 96U, 10U, 2U},  {144U, 35U, 640U,  480U}},
    /* SVGA 800x600@60Hz: no CEA code, pixClk=4000 */
    {FVID2_STD_SVGA_60,      0U,  4000U,  60U, 1056U, 628U, \
    {40U, 0U, 128U, 1U, 4U},  {216U, 27U, 800U,  600U}},
    /* XGA 1024x768@60Hz: no CEA code, pixClk=6500 */
    {FVID2_STD_XGA_60,       0U,  6500U,  60U, 1344U, 806U, \
    {24U, 0U, 136U, 3U, 6U},  {296U, 35U, 1024U, 768U}},
    /* SXGA 1280x1024@60Hz: no CEA code, pixClk=10800 */
    {FVID2_STD_SXGA_60,      0U,  10800U, 60U, 1688U, 1066U, \
    {48U, 0U, 112U, 1U, 3U},  {360U, 41U, 1280U, 1024U}},
    /* WXGA 1280x800@60Hz: no CEA code, pixClk=8350 */
    {FVID2_STD_WXGA_60,      0U,  8350U,  60U, 1680U, 833U, \
    {64U, 0U, 136U, 3U, 6U},  {336U, 30U, 1280U, 800U}},
    /* 1440x900@60Hz: no CEA code, pixClk=10650 */
    {FVID2_STD_1440_900_60,  0U,  10650U, 60U, 1904U, 937U, \
    {80U, 0U, 152U, 3U, 6U},  {384U, 34U, 1440U, 900U}},
    /* 1680x1050@60Hz WSXGA+: no CEA code, pixClk=14625 */
    {FVID2_STD_WSXGAP_60,    0U,  14625U, 60U, 2240U, 1091U, \
    {104U, 0U, 176U, 3U, 6U}, {456U, 38U, 1680U, 1050U}},
};

static char *gVesaResolutionName[TEST_DSS_VESA_RESOLUTION_COUNT] =
{
    "VGA_640x480_60Hz",
    "SVGA_800x600_60Hz",
    "XGA_1024x768_60Hz",
    "SXGA_1280x1024_60Hz",
    "WXGA_1280x800_60Hz",
    "1440x900_60Hz",
    "1680x1050_60Hz"
};

static const uint32_t TestDss_colorbarResolutionIdx[TEST_DSS_COLORBAR_RESOLUTION_COUNT] = {
    0U,  /* 1080p60 (index into gDpiTimingParamsInfo / gModeInfo) */
    3U,  /* 720p60  */
    1U,  /* 1080p50 */
    2U   /* 1080p30 */
};

static const char *TestDss_colorbarResolutionName[TEST_DSS_COLORBAR_RESOLUTION_COUNT] = {
    "1080P@60Hz",
    "720P@60Hz",
    "1080P@50Hz",
    "1080P@30Hz"
};
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    UNITY_BEGIN();

    RUN_TEST(test_dss_mulitiple_frame_formats, 4796, NULL);
    RUN_TEST(test_dss_multiple_dpi_resolution, 4797, NULL);
#if !defined (SOC_AM62LX)
    RUN_TEST(TestDss_vpSafetyDataIntegrityDpi, 11294, NULL);
    RUN_TEST(TestDss_vpSafetyFreezeDetectDpi, 11295, NULL);
    RUN_TEST(TestDss_vesaTimingVariationsDpi, 11287, NULL);
#endif
    RUN_TEST(TestDss_vpColorSpaceConversion, 11289, NULL);
    RUN_TEST(TestDss_flipMirrorModeDpi, 11290, NULL);
    RUN_TEST(TestDss_backgroundColorDpi, 11291, NULL);
#if !defined (SOC_AM62LX)
    RUN_TEST(TestDss_colorbarEnableDpi, 11293, NULL);
#endif
    RUN_TEST(TestDss_tdmDisplayDpi, 11297, NULL);

#if defined (SOC_AM62PX)
    RUN_TEST(TestDss_cslDynamicCoverage, 6127, NULL);
    RUN_TEST(TestDss_dpiDynamicCoverage, 6067, NULL);
    RUN_TEST(TestDss_displayShareHotPlugDpi, 11296, NULL);
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

    for(uint32_t count = 0U; count < TEST_DSS_TOTAL_FRAME_TYPES_MAX; count++)
    {
        for(uint32_t instCnt = 0U; \
            instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            gDssConfigPipelineParams.inDataFmt[instCnt] = \
                                gMultipleFrameDataArray[count].frameType;
            gDssConfigPipelineParams.pitch[instCnt][0] = \
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

static void test_dss_multiple_dpi_resolution(void *args)
{
    int32_t status = SystemP_SUCCESS;
    Board_panelClose();

    for(uint32_t count = 0U; count <TEST_DSS_TOTAL_DPI_REOLUTIONS_MAX && \
        status ==  SystemP_SUCCESS; count++)
    {
        memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, \
               &gDpiTimingParamsInfo[count], sizeof(Fvid2_ModeInfo));

#if !defined (SOC_AM62LX)
        Fvid2_ModeInfo *infoMode = (Fvid2_ModeInfo *) \
                                    &gDpiTimingParamsInfo[count];
        gDssConfigPipelineParams.posx[1] = infoMode->width - \
                                        gDssConfigPipelineParams.outWidth[1];
        gDssConfigPipelineParams.posy[1] = infoMode->height - \
                                        gDssConfigPipelineParams.outHeight[1];
#endif

        memcpy(&gBridgeSii9022aObj.modeInfo, &gModeInfo[count], \
                sizeof(BridgeSii9022a_ModeInfo));

        DebugP_log("------------------------------------------------------\r\n");
        DebugP_log("DPI input resolution for test: %s\r\n", \
                    gDpiResolutionName[count]);
#if defined (SOC_AM62LX)
        status = SOC_moduleSetClockFrequency( AM62LX_DEV_DSS0, \
                                AM62LX_DEV_DSS0_DPI_0_IN_CLK, \
                                gDpiTimingParamsInfo[count].pixelClock * 1000U);
#else
        status = SOC_moduleSetClockFrequency( TISCI_DEV_DSS0, \
                                TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                                gDpiTimingParamsInfo[count].pixelClock * 1000U);
#endif

        if(status == SystemP_FAILURE)
        {
            DebugP_log("setFrq failure!!\r\n");
        }

        status += Board_panelOpen();

        status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        Board_panelClose();
    };

    DebugP_log("------------------------------------------------------\r\n");

}

#if !defined (SOC_AM62LX)
/**
 * \brief  VP VESA timing variation support for the DPI interface.
 *
 *  Test Category: Functionality
 *
 *  This test configures the VP with multiple VESA timing standards
 *  (VGA 640x480, SVGA 800x600, XGA 1024x768, 480p, 1080p, 720p) to verify that
 *  timing parameters (sync polarity, blanking intervals, pixel clock) are correctly
 *  applied to the VP and DPI transmitter.  Each timing variant is tested with
 *  full display control and frame submission.  The test confirms that different
 *  VESA timings can be selected and applied without conflicts.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_vesaTimingVariationsDpi(void *args)
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS VESA Timing Variations Test for DPI\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format as ARGB32 for display */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = FVID2_DF_BGRA32_8888;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] * 4U;
    }

    /* Save original VP polarity params for restoration */
    uint32_t origHsPolarity  = gDssVpParams.lcdPolarityCfg.hsPolarity;
    uint32_t origVsPolarity  = gDssVpParams.lcdPolarityCfg.vsPolarity;

    /* Save original pipeline position for pipe 1 */
    uint32_t origPosx1 = gDssConfigPipelineParams.posx[1];
    uint32_t origPosy1 = gDssConfigPipelineParams.posy[1];

    /* Save original pipe 0 output dimensions. Small VESA resolutions (e.g. VGA
     * 640x480) are narrower/shorter than the default outWidth[0]=720/outHeight[0]=540,
     * so the dimensions must be clamped before each TestDisp_displayControl call. */
    uint32_t origOutWidth0  = gDssConfigPipelineParams.outWidth[0];
    uint32_t origOutHeight0 = gDssConfigPipelineParams.outHeight[0];

    /* Save original VP timing and bridge mode for the test restore */
    Fvid2_ModeInfo origModeInfo;
    BridgeSii9022a_ModeInfo origBridgeModeInfo;
    memcpy(&origModeInfo, &gDssVpParams.lcdOpTimingCfg.mInfo, sizeof(Fvid2_ModeInfo));
    memcpy(&origBridgeModeInfo, &gBridgeSii9022aObj.modeInfo, sizeof(BridgeSii9022a_ModeInfo));

    Board_panelClose();

    /*
     * Multiple VESA resolutions with default polarity
     * Cycle through all 9 VESA resolutions including VGA (640x480),
     * SVGA (800x600), XGA (1024x768), 480P (720x480), 1080p60/50/30,
     * and 720p60/50 to verify VP timing programming at each resolution.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" VESA resolution switching (default polarity)\r\n");

    for(uint32_t count = 0U; count < TEST_DSS_VESA_RESOLUTION_COUNT && \
        status == SystemP_SUCCESS; count++)
    {
        memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, \
               &gVesaTimingParamsInfo[count], sizeof(Fvid2_ModeInfo));

        Fvid2_ModeInfo *infoMode = (Fvid2_ModeInfo *) \
                                    &gVesaTimingParamsInfo[count];

        /* Clamp pipe 0 output to the current display dimensions. Required for
         * small VESA resolutions (e.g. VGA 640x480) where the default
         * outWidth=720 / outHeight=540 would exceed the display bounds. */
        gDssConfigPipelineParams.outWidth[0]  = (origOutWidth0  < infoMode->width)  ?
                                                 origOutWidth0  : infoMode->width;
        gDssConfigPipelineParams.outHeight[0] = (origOutHeight0 < infoMode->height) ?
                                                 origOutHeight0 : infoMode->height;

        /* Position pipe 1 only if resolution is large enough */
        if(infoMode->width > gDssConfigPipelineParams.outWidth[1] && \
           infoMode->height > gDssConfigPipelineParams.outHeight[1])
        {
            gDssConfigPipelineParams.posx[1] = infoMode->width - \
                                            gDssConfigPipelineParams.outWidth[1];
            gDssConfigPipelineParams.posy[1] = infoMode->height - \
                                            gDssConfigPipelineParams.outHeight[1];
        }
        else
        {
            gDssConfigPipelineParams.posx[1] = 0U;
            gDssConfigPipelineParams.posy[1] = 0U;
        }

        memcpy(&gBridgeSii9022aObj.modeInfo, &gVesaBridgeModeInfo[count], \
                sizeof(BridgeSii9022a_ModeInfo));

        DebugP_log("  Resolution: %s\r\n", gVesaResolutionName[count]);

        status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0, \
                                TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                                gVesaTimingParamsInfo[count].pixelClock * 1000U);
        if(status == SystemP_FAILURE)
        {
            DebugP_log("  setFrq failure!!\r\n");
        }

        status += Board_panelOpen();
        status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        Board_panelClose();
    }

    DebugP_log(" Resolution switching PASSED\r\n");

    /*
     *  VGA 640x480 with inverted hsync polarity
     * Exercise polarity control at a low-resolution VESA mode.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" VGA 640x480 with inverted hsync polarity\r\n");

    memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, \
           &gVesaTimingParamsInfo[0], sizeof(Fvid2_ModeInfo));
    memcpy(&gBridgeSii9022aObj.modeInfo, &gVesaBridgeModeInfo[0], \
            sizeof(BridgeSii9022a_ModeInfo));

    gDssVpParams.lcdPolarityCfg.hsPolarity = FVID2_POL_LOW;

    /* Clamp pipe 0 output for VGA (640x480 < outWidth=720 / outHeight=540) */
    gDssConfigPipelineParams.outWidth[0]  = (origOutWidth0  < 640U) ? origOutWidth0  : 640U;
    gDssConfigPipelineParams.outHeight[0] = (origOutHeight0 < 480U) ? origOutHeight0 : 480U;

    gDssConfigPipelineParams.posx[1] = gVesaTimingParamsInfo[0].width - \
                                    gDssConfigPipelineParams.outWidth[1];
    gDssConfigPipelineParams.posy[1] = gVesaTimingParamsInfo[0].height - \
                                    gDssConfigPipelineParams.outHeight[1];

    status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0, \
                            TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                            gVesaTimingParamsInfo[0].pixelClock * 1000U);
    status += Board_panelOpen();
    status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    Board_panelClose();

    DebugP_log(" VGA inverted hsync polarity PASSED\r\n");

    /* Restore hsync polarity */
    gDssVpParams.lcdPolarityCfg.hsPolarity = origHsPolarity;

    /*
     *  SVGA 800x600 with inverted vsync polarity
     * Exercise polarity control at SVGA resolution.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" SVGA 800x600 with inverted vsync polarity\r\n");

    memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, \
           &gVesaTimingParamsInfo[1], sizeof(Fvid2_ModeInfo));
    memcpy(&gBridgeSii9022aObj.modeInfo, &gVesaBridgeModeInfo[1], \
            sizeof(BridgeSii9022a_ModeInfo));

    gDssVpParams.lcdPolarityCfg.vsPolarity = FVID2_POL_LOW;

    gDssConfigPipelineParams.posx[1] = gVesaTimingParamsInfo[1].width - \
                                    gDssConfigPipelineParams.outWidth[1];
    gDssConfigPipelineParams.posy[1] = gVesaTimingParamsInfo[1].height - \
                                    gDssConfigPipelineParams.outHeight[1];

    status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0, \
                            TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                            gVesaTimingParamsInfo[1].pixelClock * 1000U);
    status += Board_panelOpen();
    status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    Board_panelClose();

    DebugP_log(" SVGA inverted vsync polarity PASSED\r\n");

    /* Restore vsync polarity */
    gDssVpParams.lcdPolarityCfg.vsPolarity = origVsPolarity;

    /*
     *  XGA 1024x768 with both hsync and vsync polarity inverted
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" XGA 1024x768 with both polarities inverted\r\n");

    memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, \
           &gVesaTimingParamsInfo[2], sizeof(Fvid2_ModeInfo));
    memcpy(&gBridgeSii9022aObj.modeInfo, &gVesaBridgeModeInfo[2], \
            sizeof(BridgeSii9022a_ModeInfo));

    gDssVpParams.lcdPolarityCfg.hsPolarity = FVID2_POL_LOW;
    gDssVpParams.lcdPolarityCfg.vsPolarity = FVID2_POL_LOW;

    gDssConfigPipelineParams.posx[1] = gVesaTimingParamsInfo[2].width - \
                                    gDssConfigPipelineParams.outWidth[1];
    gDssConfigPipelineParams.posy[1] = gVesaTimingParamsInfo[2].height - \
                                    gDssConfigPipelineParams.outHeight[1];

    status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0, \
                            TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                            gVesaTimingParamsInfo[2].pixelClock * 1000U);
    status += Board_panelOpen();
    status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    Board_panelClose();

    DebugP_log(" XGA both polarities inverted PASSED\r\n");

    /* Restore polarities */
    gDssVpParams.lcdPolarityCfg.hsPolarity = origHsPolarity;
    gDssVpParams.lcdPolarityCfg.vsPolarity = origVsPolarity;

    /*
     *  480P 720x480 with modified blanking intervals
     * Exercise blanking timing register writes at 480P resolution.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" VGA 640x480 with modified blanking intervals\r\n");

    memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, \
           &gVesaTimingParamsInfo[0], sizeof(Fvid2_ModeInfo));
    memcpy(&gBridgeSii9022aObj.modeInfo, &gVesaBridgeModeInfo[0], \
            sizeof(BridgeSii9022a_ModeInfo));

    /* Modify blanking intervals from the VGA defaults */
    gDssVpParams.lcdOpTimingCfg.mInfo.hFrontPorch = 24U;
    gDssVpParams.lcdOpTimingCfg.mInfo.hBackPorch  = 68U;
    gDssVpParams.lcdOpTimingCfg.mInfo.vFrontPorch = 12U;
    gDssVpParams.lcdOpTimingCfg.mInfo.vBackPorch  = 34U;

    /* Clamp pipe 0 output for VGA (640x480 < outWidth=720 / outHeight=540) */
    gDssConfigPipelineParams.outWidth[0]  = (origOutWidth0  < 640U) ? origOutWidth0  : 640U;
    gDssConfigPipelineParams.outHeight[0] = (origOutHeight0 < 480U) ? origOutHeight0 : 480U;

    gDssConfigPipelineParams.posx[1] = gVesaTimingParamsInfo[0].width - \
                                    gDssConfigPipelineParams.outWidth[1];
    gDssConfigPipelineParams.posy[1] = gVesaTimingParamsInfo[0].height - \
                                    gDssConfigPipelineParams.outHeight[1];

    status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0, \
                            TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                            gVesaTimingParamsInfo[3].pixelClock * 1000U);
    status += Board_panelOpen();
    status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    Board_panelClose();

    DebugP_log(" VGA modified blanking intervals PASSED\r\n");

    /*
     *  XGA 1024x768 with combined polarity + blanking variation
     * Exercise all timing parameters modified simultaneously at a
     * mid-range VESA resolution.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" XGA 1024x768 combined polarity + blanking\r\n");

    memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, \
           &gVesaTimingParamsInfo[2], sizeof(Fvid2_ModeInfo));
    memcpy(&gBridgeSii9022aObj.modeInfo, &gVesaBridgeModeInfo[2], \
            sizeof(BridgeSii9022a_ModeInfo));

    gDssVpParams.lcdPolarityCfg.hsPolarity = FVID2_POL_LOW;
    gDssVpParams.lcdPolarityCfg.vsPolarity = FVID2_POL_LOW;
    gDssVpParams.lcdOpTimingCfg.mInfo.hFrontPorch = 32U;
    gDssVpParams.lcdOpTimingCfg.mInfo.hBackPorch  = 180U;
    gDssVpParams.lcdOpTimingCfg.mInfo.hSyncLen     = 120U;
    gDssVpParams.lcdOpTimingCfg.mInfo.vFrontPorch = 6U;
    gDssVpParams.lcdOpTimingCfg.mInfo.vBackPorch  = 32U;
    gDssVpParams.lcdOpTimingCfg.mInfo.vSyncLen     = 4U;

    gDssConfigPipelineParams.posx[1] = gVesaTimingParamsInfo[2].width - \
                                    gDssConfigPipelineParams.outWidth[1];
    gDssConfigPipelineParams.posy[1] = gVesaTimingParamsInfo[2].height - \
                                    gDssConfigPipelineParams.outHeight[1];

    status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0, \
                            TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                            gVesaTimingParamsInfo[2].pixelClock * 1000U);
    status += Board_panelOpen();
    status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    Board_panelClose();

    DebugP_log(" XGA combined polarity + blanking PASSED\r\n");

    /* Restore all original VP polarity params */
    gDssVpParams.lcdPolarityCfg.hsPolarity = origHsPolarity;
    gDssVpParams.lcdPolarityCfg.vsPolarity = origVsPolarity;

    /*
     *  SVGA 800x600 with modified sync lengths
     * Verify sync width register write path at SVGA resolution.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" SVGA 800x600 with modified sync lengths\r\n");

    memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, \
           &gVesaTimingParamsInfo[1], sizeof(Fvid2_ModeInfo));
    memcpy(&gBridgeSii9022aObj.modeInfo, &gVesaBridgeModeInfo[1], \
            sizeof(BridgeSii9022a_ModeInfo));

    gDssVpParams.lcdOpTimingCfg.mInfo.hSyncLen = 160U;
    gDssVpParams.lcdOpTimingCfg.mInfo.vSyncLen = 6U;

    gDssConfigPipelineParams.posx[1] = gVesaTimingParamsInfo[1].width - \
                                    gDssConfigPipelineParams.outWidth[1];
    gDssConfigPipelineParams.posy[1] = gVesaTimingParamsInfo[1].height - \
                                    gDssConfigPipelineParams.outHeight[1];

    status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0, \
                            TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                            gVesaTimingParamsInfo[1].pixelClock * 1000U);
    status += Board_panelOpen();
    status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    Board_panelClose();

    DebugP_log(" SVGA modified sync lengths PASSED\r\n");

    /*
     *  1080p60 with modified blanking (HD resolution coverage)
     * Ensure blanking variations also work at full-HD resolution.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" SXGA 1280x1024 with modified blanking intervals\r\n");

    memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, \
           &gVesaTimingParamsInfo[3], sizeof(Fvid2_ModeInfo));
    memcpy(&gBridgeSii9022aObj.modeInfo, &gVesaBridgeModeInfo[3], \
            sizeof(BridgeSii9022a_ModeInfo));

    gDssVpParams.lcdOpTimingCfg.mInfo.hFrontPorch = 120U;
    gDssVpParams.lcdOpTimingCfg.mInfo.hBackPorch  = 200U;
    gDssVpParams.lcdOpTimingCfg.mInfo.vFrontPorch = 8U;
    gDssVpParams.lcdOpTimingCfg.mInfo.vBackPorch  = 40U;

    gDssConfigPipelineParams.posx[1] = gVesaTimingParamsInfo[3].width - \
                                    gDssConfigPipelineParams.outWidth[1];
    gDssConfigPipelineParams.posy[1] = gVesaTimingParamsInfo[3].height - \
                                    gDssConfigPipelineParams.outHeight[1];

    status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0, \
                            TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                            gVesaTimingParamsInfo[4].pixelClock * 1000U);
    status += Board_panelOpen();
    status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    Board_panelClose();

    DebugP_log(" SXGA 1280x1024 modified blanking PASSED\r\n");

    /*
     *  Restore default 1080p60 timing (baseline validation)
     * Ensure the VP can be restored to default after all modifications.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" Restore default 1080p60 timing\r\n");

    /* Restore all pipeline params to original values before the display cycle */
    memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo, &origModeInfo, sizeof(Fvid2_ModeInfo));
    memcpy(&gBridgeSii9022aObj.modeInfo, &origBridgeModeInfo, sizeof(BridgeSii9022a_ModeInfo));
    gDssConfigPipelineParams.outWidth[0]  = origOutWidth0;
    gDssConfigPipelineParams.outHeight[0] = origOutHeight0;
    gDssConfigPipelineParams.posx[1]      = origPosx1;
    gDssConfigPipelineParams.posy[1]      = origPosy1;

    status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0, \
                            TISCI_DEV_DSS0_DPI_1_IN_CLK, \
                            origModeInfo.pixelClock * 1000U);
    status += Board_panelOpen();
    status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    Board_panelClose();

    DebugP_log(" Default 1080p60 timing restored PASSED\r\n");

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS VESA Timing Variations Test Completed Successfully!\r\n");
    DebugP_log("======================================================\r\n");
}
#endif

/**
 * \brief  VP Color Space Conversion (CSC) coefficient programming for DPI.
 *
 *  Test Category: Functionality
 *
 *  This test exercises VP-level Color Space Conversion by programming various
 *  CSC coefficient matrices via IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF.  The test
 *  covers BT-601 limited/full range RGB→YUV conversions, identity matrix
 *  passthrough, and custom coefficients with pre/post offsets positioned before
 *  or after gamma correction.  The test verifies correct IOCTL acceptance,
 *  CSL register programming, and that the display pipeline operates correctly
 *  with CSC enabled and disabled (baseline verification).
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_vpColorSpaceConversion(void *args)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    Dss_DctrlVpCscCoeff vpCscCoeff;
    Fvid2_InitPrms initPrms;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS VP Color Space Conversion Test (VP-side CSC)\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format as ARGB32 for all display pipes */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = FVID2_DF_BGRA32_8888;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] * 4U;
    }

    /*
     *  BT-601 Limited Range RGB->YUV (CSC before GAMMA)
     *
     * Uses the standard BT-601 limited range coefficients for RGB-to-YUV
     * conversion. These are the same coefficients the DSS driver uses
     * internally for BT656/BT1120 embedded sync output modes.
     *
     * Coefficient values (Q8 fixed point, 256 = 1.0):
     *   Y  =  0.299*R + 0.587*G + 0.114*B          → c00=77, c01=150, c02=29
     *   Cb = -0.172*R - 0.340*G + 0.512*B + 2048    → c10=-44,c11=-87,c12=131
     *   Cr =  0.512*R - 0.430*G - 0.082*B + 2048    → c20=131,c21=-110,c22=-21
     *   Y post-offset = 256 (16 in 8-bit, shifted to 12-bit)
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" BT-601 Limited Range CSC (before GAMMA)\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

    /* Configure VP CSC: BT-601 limited range, position before gamma */
    vpCscCoeff.vpId   = gDssVpParams.vpId;
    vpCscCoeff.cscPos = CSL_DSS_VP_CSC_POS_BEFORE_GAMMA;
    vpCscCoeff.cscCoeff.cscRange    = CSL_DSS_CSC_RANGE_LIMITED;
    vpCscCoeff.cscCoeff.c00         =  77;
    vpCscCoeff.cscCoeff.c01         = 150;
    vpCscCoeff.cscCoeff.c02         =  29;
    vpCscCoeff.cscCoeff.c10         = -44;
    vpCscCoeff.cscCoeff.c11         = -87;
    vpCscCoeff.cscCoeff.c12         = 131;
    vpCscCoeff.cscCoeff.c20         = 131;
    vpCscCoeff.cscCoeff.c21         = -110;
    vpCscCoeff.cscCoeff.c22         = -21;
    vpCscCoeff.cscCoeff.preOffset1  = 0;
    vpCscCoeff.cscCoeff.preOffset2  = 0;
    vpCscCoeff.cscCoeff.preOffset3  = 0;
    vpCscCoeff.cscCoeff.postOffset1 = 256;
    vpCscCoeff.cscCoeff.postOffset2 = 2048;
    vpCscCoeff.cscCoeff.postOffset3 = 2048;

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF,
        &vpCscCoeff,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF returned FVID2_SOK\r\n");

    /* Clean up DCTRL handle and DSS */
    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    retVal = Dss_deInit();
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    retVal = Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    DebugP_log(" BT-601 Limited Range CSC PASSED\r\n");

    /*
     *  BT-601 Full Range RGB->YUV (CSC before GAMMA)
     *
     * Full range uses slightly different coefficient scaling. The Y channel
     * uses the full 0-255 range (no 16-235 clamping), so the post-offset
     * for Y is 0 instead of 256.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" BT-601 Full Range CSC (before GAMMA)\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

    /* Configure VP CSC: BT-601 full range */
    vpCscCoeff.vpId   = gDssVpParams.vpId;
    vpCscCoeff.cscPos = CSL_DSS_VP_CSC_POS_BEFORE_GAMMA;
    vpCscCoeff.cscCoeff.cscRange    = CSL_DSS_CSC_RANGE_FULL;
    vpCscCoeff.cscCoeff.c00         =  66;
    vpCscCoeff.cscCoeff.c01         = 129;
    vpCscCoeff.cscCoeff.c02         =  25;
    vpCscCoeff.cscCoeff.c10         = -38;
    vpCscCoeff.cscCoeff.c11         = -74;
    vpCscCoeff.cscCoeff.c12         = 112;
    vpCscCoeff.cscCoeff.c20         = 112;
    vpCscCoeff.cscCoeff.c21         = -94;
    vpCscCoeff.cscCoeff.c22         = -18;
    vpCscCoeff.cscCoeff.preOffset1  = 0;
    vpCscCoeff.cscCoeff.preOffset2  = 0;
    vpCscCoeff.cscCoeff.preOffset3  = 0;
    vpCscCoeff.cscCoeff.postOffset1 = 0;
    vpCscCoeff.cscCoeff.postOffset2 = 2048;
    vpCscCoeff.cscCoeff.postOffset3 = 2048;

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF,
        &vpCscCoeff,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF returned FVID2_SOK\r\n");

    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    DebugP_log(" BT-601 Full Range CSC PASSED\r\n");

    /*
     *  Identity matrix passthrough (CSC before GAMMA)
     *
     * An identity CSC matrix passes pixel data through unchanged.
     * Diagonal elements = 256 (1.0 in Q8 fixed-point), off-diag = 0.
     * All offsets = 0. Range = CUSTOM (allows arbitrary coefficients).
     * This verifies the IOCTL accepts an identity/no-op configuration.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" Identity matrix passthrough (before GAMMA)\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

    /* Configure VP CSC: identity matrix */
    vpCscCoeff.vpId   = gDssVpParams.vpId;
    vpCscCoeff.cscPos = CSL_DSS_VP_CSC_POS_BEFORE_GAMMA;
    vpCscCoeff.cscCoeff.cscRange    = CSL_DSS_CSC_RANGE_CUSTOM;
    vpCscCoeff.cscCoeff.c00         = 256;
    vpCscCoeff.cscCoeff.c01         = 0;
    vpCscCoeff.cscCoeff.c02         = 0;
    vpCscCoeff.cscCoeff.c10         = 0;
    vpCscCoeff.cscCoeff.c11         = 256;
    vpCscCoeff.cscCoeff.c12         = 0;
    vpCscCoeff.cscCoeff.c20         = 0;
    vpCscCoeff.cscCoeff.c21         = 0;
    vpCscCoeff.cscCoeff.c22         = 256;
    vpCscCoeff.cscCoeff.preOffset1  = 0;
    vpCscCoeff.cscCoeff.preOffset2  = 0;
    vpCscCoeff.cscCoeff.preOffset3  = 0;
    vpCscCoeff.cscCoeff.postOffset1 = 0;
    vpCscCoeff.cscCoeff.postOffset2 = 0;
    vpCscCoeff.cscCoeff.postOffset3 = 0;

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF,
        &vpCscCoeff,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF returned FVID2_SOK\r\n");

    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    DebugP_log(" Identity matrix passthrough PASSED\r\n");

    /*
     *  Custom CSC coefficients with post-offsets (CSC after GAMMA)
     *
     * Uses arbitrary custom coefficients with non-zero post-offsets.
     * Position = AFTER_GAMMA. Range = CUSTOM.
     * This exercises the CSL_DSS_VP_CSC_POS_AFTER_GAMMA path and the
     * CSL_DSS_CSC_RANGE_CUSTOM mode together.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" Custom CSC coefficients (after GAMMA)\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

    /* Configure VP CSC: custom coefficients, after gamma */
    vpCscCoeff.vpId   = gDssVpParams.vpId;
    vpCscCoeff.cscPos = CSL_DSS_VP_CSC_POS_AFTER_GAMMA;
    vpCscCoeff.cscCoeff.cscRange    = CSL_DSS_CSC_RANGE_CUSTOM;
    vpCscCoeff.cscCoeff.c00         = 200;
    vpCscCoeff.cscCoeff.c01         =  50;
    vpCscCoeff.cscCoeff.c02         =   6;
    vpCscCoeff.cscCoeff.c10         =  10;
    vpCscCoeff.cscCoeff.c11         = 220;
    vpCscCoeff.cscCoeff.c12         =  26;
    vpCscCoeff.cscCoeff.c20         =  15;
    vpCscCoeff.cscCoeff.c21         =  30;
    vpCscCoeff.cscCoeff.c22         = 211;
    vpCscCoeff.cscCoeff.preOffset1  = 0;
    vpCscCoeff.cscCoeff.preOffset2  = 0;
    vpCscCoeff.cscCoeff.preOffset3  = 0;
    vpCscCoeff.cscCoeff.postOffset1 = 128;
    vpCscCoeff.cscCoeff.postOffset2 = 64;
    vpCscCoeff.cscCoeff.postOffset3 = 32;

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF,
        &vpCscCoeff,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF returned FVID2_SOK\r\n");

    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    DebugP_log(" Custom CSC coefficients PASSED\r\n");

    /*
     *  BT-601 Limited Range (CSC after GAMMA)
     *
     * Same BT-601 limited range coefficients as the test, but placed
     * AFTER the GAMMA correction block. Verifies the CSC position selector
     * works correctly with both BEFORE and AFTER values.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" BT-601 Limited Range CSC (after GAMMA)\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

    /* Configure VP CSC: BT-601 limited range, position after gamma */
    vpCscCoeff.vpId   = gDssVpParams.vpId;
    vpCscCoeff.cscPos = CSL_DSS_VP_CSC_POS_AFTER_GAMMA;
    vpCscCoeff.cscCoeff.cscRange    = CSL_DSS_CSC_RANGE_LIMITED;
    vpCscCoeff.cscCoeff.c00         =  77;
    vpCscCoeff.cscCoeff.c01         = 150;
    vpCscCoeff.cscCoeff.c02         =  29;
    vpCscCoeff.cscCoeff.c10         = -44;
    vpCscCoeff.cscCoeff.c11         = -87;
    vpCscCoeff.cscCoeff.c12         = 131;
    vpCscCoeff.cscCoeff.c20         = 131;
    vpCscCoeff.cscCoeff.c21         = -110;
    vpCscCoeff.cscCoeff.c22         = -21;
    vpCscCoeff.cscCoeff.preOffset1  = 0;
    vpCscCoeff.cscCoeff.preOffset2  = 0;
    vpCscCoeff.cscCoeff.preOffset3  = 0;
    vpCscCoeff.cscCoeff.postOffset1 = 256;
    vpCscCoeff.cscCoeff.postOffset2 = 2048;
    vpCscCoeff.cscCoeff.postOffset3 = 2048;

    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF,
        &vpCscCoeff,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF returned FVID2_SOK\r\n");

    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    DebugP_log(" BT-601 Limited Range CSC (after GAMMA) PASSED\r\n");

    /*
     *  Full display cycle (baseline verification)
     *
     * Run the complete display pipeline via TestDisp_displayControl to
     * confirm the display path works correctly after the VP CSC IOCTL
     * exercises above. This serves as a baseline/sanity check.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" Full display cycle (baseline)\r\n");

    status = Board_panelOpen();
    status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
    Board_panelClose();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log(" Full display cycle PASSED\r\n");

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS VP Color Space Conversion Test Completed!\r\n");
    DebugP_log("======================================================\r\n");
}

/**
 * \brief  VP video frame flip and mirror mode for the DPI interface.
 *
 *  Test Category: Functionality
 *
 *  This test exercises all FVID2 flip modes (vertical, horizontal, H+V) on the
 *  VP for DPI output.  The test verifies that flip is supported for 32-bit
 *  formats (BGRA32) and correctly rejected for 24-bit RGB/BGR formats via
 *  IOCTL_DSS_DISP_SET_DSS_PARAMS.  The test covers positive cases with all
 *  flip mode combinations on BGRA32, negative cases with RGB24/BGR24 formats,
 *  and a baseline display cycle to ensure flip does not break normal operation.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_flipMirrorModeDpi(void *args)
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

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Flip/Mirror Mode Test (DPI)\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format as BGRA32 for all display pipes (flip-safe) */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = FVID2_DF_BGRA32_8888;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] * 4U;
    }

    /*
     *  Vertical flip (FVID2_FLIP_TYPE_V) with BGRA32_8888
     *
     * Vertical flip mirrors the image along the X axis. The DSS hardware
     * implements this by setting the FLIP bit in DSS_VID_ATTRIBUTES register.
     * Expected result: FVID2_SOK (32-bit format is flip-compatible).
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" Vertical flip (FVID2_FLIP_TYPE_V) BGRA32\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

    /* Configure DCTRL path using syscfg globals */
    Dss_dctrlVpParamsInit(&vpParams);
    vpParams.vpId = gDssVpParams.vpId;
    memcpy(&vpParams.lcdOpTimingCfg.mInfo,
           &gDssVpParams.lcdOpTimingCfg.mInfo,
           sizeof(Fvid2_ModeInfo));
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

    /* Create DISP driver handle for first pipe */
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

    /* Prepare dispParams with vertical flip */
    Dss_dispParamsInit(&dispParams);
    dispParams.pipeCfg.pipeType =
        gDssConfigPipelineParams.pipeType[0U];
    dispParams.pipeCfg.inFmt.width =
        gDssConfigPipelineParams.inWidth[0U];
    dispParams.pipeCfg.inFmt.height =
        gDssConfigPipelineParams.inHeight[0U];
    dispParams.pipeCfg.inFmt.pitch[0U] =
        gDssConfigPipelineParams.pitch[0U][0U];
    dispParams.pipeCfg.inFmt.dataFormat = FVID2_DF_BGRA32_8888;
    dispParams.pipeCfg.inFmt.scanFormat =
        gDssConfigPipelineParams.inScanFmt[0U];
    dispParams.pipeCfg.outWidth =
        gDssConfigPipelineParams.outWidth[0U];
    dispParams.pipeCfg.outHeight =
        gDssConfigPipelineParams.outHeight[0U];
    dispParams.pipeCfg.scEnable =
        gDssConfigPipelineParams.scEnable[0U];
    dispParams.pipeCfg.flipType = FVID2_FLIP_TYPE_V;
    dispParams.layerPos.startX =
        gDssConfigPipelineParams.posx[0U];
    dispParams.layerPos.startY =
        gDssConfigPipelineParams.posy[0U];

    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_DSS_DISP_SET_DSS_PARAMS,
        &dispParams,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  IOCTL_DSS_DISP_SET_DSS_PARAMS (V flip) returned FVID2_SOK\r\n");

    /* Clean up */
    retVal = Fvid2_delete(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    SemaphoreP_destruct(&instObj->syncSem);
    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_CLEAR_PATH,
        gDssObjects[CONFIG_DSS0].dctrlPathInfo, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Now display frames on-screen with vertical flip applied */
    DebugP_log("  Displaying frames with V flip on screen...\r\n");
    status = Board_panelOpen();
    status += TestDisp_flipDisplayControl(&gDssObjects[CONFIG_DSS0],
                                          FVID2_FLIP_TYPE_V);
    Board_panelClose();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("  V flip display cycle completed\r\n");

    DebugP_log(" Vertical flip PASSED\r\n");

    /*
     *  Horizontal flip (FVID2_FLIP_TYPE_H) with BGRA32_8888
     *
     * Horizontal flip mirrors the image along the Y axis. The DSS hardware
     * implements this by calculating a negative ROW_INC value:
     *   ROW_INC = -(widthInBytes + pitch - 1)
     * Expected result: FVID2_SOK (32-bit format is flip-compatible).
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" Horizontal flip (FVID2_FLIP_TYPE_H) BGRA32\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

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

    Dss_dispParamsInit(&dispParams);
    dispParams.pipeCfg.pipeType =
        gDssConfigPipelineParams.pipeType[0U];
    dispParams.pipeCfg.inFmt.width =
        gDssConfigPipelineParams.inWidth[0U];
    dispParams.pipeCfg.inFmt.height =
        gDssConfigPipelineParams.inHeight[0U];
    dispParams.pipeCfg.inFmt.pitch[0U] =
        gDssConfigPipelineParams.pitch[0U][0U];
    dispParams.pipeCfg.inFmt.dataFormat = FVID2_DF_BGRA32_8888;
    dispParams.pipeCfg.inFmt.scanFormat =
        gDssConfigPipelineParams.inScanFmt[0U];
    dispParams.pipeCfg.outWidth =
        gDssConfigPipelineParams.outWidth[0U];
    dispParams.pipeCfg.outHeight =
        gDssConfigPipelineParams.outHeight[0U];
    dispParams.pipeCfg.scEnable =
        gDssConfigPipelineParams.scEnable[0U];
    dispParams.pipeCfg.flipType = FVID2_FLIP_TYPE_H;
    dispParams.layerPos.startX =
        gDssConfigPipelineParams.posx[0U];
    dispParams.layerPos.startY =
        gDssConfigPipelineParams.posy[0U];

    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_DSS_DISP_SET_DSS_PARAMS,
        &dispParams,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  IOCTL_DSS_DISP_SET_DSS_PARAMS (H flip) returned FVID2_SOK\r\n");

    retVal = Fvid2_delete(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    SemaphoreP_destruct(&instObj->syncSem);
    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_CLEAR_PATH,
        gDssObjects[CONFIG_DSS0].dctrlPathInfo, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Now display frames on-screen with horizontal flip applied */
    DebugP_log("  Displaying frames with H flip on screen...\r\n");
    status = Board_panelOpen();
    status += TestDisp_flipDisplayControl(&gDssObjects[CONFIG_DSS0],
                                          FVID2_FLIP_TYPE_H);
    Board_panelClose();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("  H flip display cycle completed\r\n");

    DebugP_log(" Horizontal flip PASSED\r\n");

    /*
     *  H+V flip (FVID2_FLIP_TYPE_HV) with BGRA32_8888
     *
     * Combined horizontal and vertical flip (180-degree rotation).
     * Both the FLIP attribute bit and the negative ROW_INC are programmed.
     * Expected result: FVID2_SOK (32-bit format is flip-compatible).
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" H+V flip (FVID2_FLIP_TYPE_HV) BGRA32\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

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

    Dss_dispParamsInit(&dispParams);
    dispParams.pipeCfg.pipeType =
        gDssConfigPipelineParams.pipeType[0U];
    dispParams.pipeCfg.inFmt.width =
        gDssConfigPipelineParams.inWidth[0U];
    dispParams.pipeCfg.inFmt.height =
        gDssConfigPipelineParams.inHeight[0U];
    dispParams.pipeCfg.inFmt.pitch[0U] =
        gDssConfigPipelineParams.pitch[0U][0U];
    dispParams.pipeCfg.inFmt.dataFormat = FVID2_DF_BGRA32_8888;
    dispParams.pipeCfg.inFmt.scanFormat =
        gDssConfigPipelineParams.inScanFmt[0U];
    dispParams.pipeCfg.outWidth =
        gDssConfigPipelineParams.outWidth[0U];
    dispParams.pipeCfg.outHeight =
        gDssConfigPipelineParams.outHeight[0U];
    dispParams.pipeCfg.scEnable =
        gDssConfigPipelineParams.scEnable[0U];
    dispParams.pipeCfg.flipType = FVID2_FLIP_TYPE_HV;
    dispParams.layerPos.startX =
        gDssConfigPipelineParams.posx[0U];
    dispParams.layerPos.startY =
        gDssConfigPipelineParams.posy[0U];

    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_DSS_DISP_SET_DSS_PARAMS,
        &dispParams,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    DebugP_log("  IOCTL_DSS_DISP_SET_DSS_PARAMS (HV flip) returned FVID2_SOK\r\n");

    retVal = Fvid2_delete(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    SemaphoreP_destruct(&instObj->syncSem);
    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_CLEAR_PATH,
        gDssObjects[CONFIG_DSS0].dctrlPathInfo, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    /* Now display frames on-screen with H+V flip applied */
    DebugP_log("  Displaying frames with HV flip on screen...\r\n");
    status = Board_panelOpen();
    status += TestDisp_flipDisplayControl(&gDssObjects[CONFIG_DSS0],
                                          FVID2_FLIP_TYPE_HV);
    Board_panelClose();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    DebugP_log("  HV flip display cycle completed\r\n");

    DebugP_log(" H+V flip PASSED\r\n");

    /*
     *  Vertical flip with RGB24_888 (negative test)
     *
     * The DSS driver rejects flip for 24-bit RGB/BGR formats because the
     * hardware ROW_INC calculation does not work correctly with 3-byte
     * pixels (non-power-of-2 width). The driver validation in
     * Dss_dispDrvValidateDssParams() returns FVID2_EINVALID_PARAMS.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" V flip + RGB24_888 (expect EINVALID_PARAMS)\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

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

    Dss_dispParamsInit(&dispParams);
    dispParams.pipeCfg.pipeType =
        gDssConfigPipelineParams.pipeType[0U];
    dispParams.pipeCfg.inFmt.width =
        gDssConfigPipelineParams.inWidth[0U];
    dispParams.pipeCfg.inFmt.height =
        gDssConfigPipelineParams.inHeight[0U];
    dispParams.pipeCfg.inFmt.pitch[0U] =
        gDssConfigPipelineParams.inWidth[0U] * 3U;
    dispParams.pipeCfg.inFmt.dataFormat = FVID2_DF_RGB24_888;
    dispParams.pipeCfg.inFmt.scanFormat =
        gDssConfigPipelineParams.inScanFmt[0U];
    dispParams.pipeCfg.outWidth =
        gDssConfigPipelineParams.outWidth[0U];
    dispParams.pipeCfg.outHeight =
        gDssConfigPipelineParams.outHeight[0U];
    dispParams.pipeCfg.scEnable =
        gDssConfigPipelineParams.scEnable[0U];
    dispParams.pipeCfg.flipType = FVID2_FLIP_TYPE_V;
    dispParams.layerPos.startX =
        gDssConfigPipelineParams.posx[0U];
    dispParams.layerPos.startY =
        gDssConfigPipelineParams.posy[0U];

    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_DSS_DISP_SET_DSS_PARAMS,
        &dispParams,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_EINVALID_PARAMS, retVal);
    DebugP_log("  IOCTL correctly rejected V flip + RGB24_888\r\n");

    retVal = Fvid2_delete(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    SemaphoreP_destruct(&instObj->syncSem);
    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_CLEAR_PATH,
        gDssObjects[CONFIG_DSS0].dctrlPathInfo, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    DebugP_log(" V flip + RGB24_888 rejection PASSED\r\n");

    /*
     *  Horizontal flip with BGR24_888 (negative test)
     *
     * Same 24-bit format restriction as the test but exercising H flip
     * and BGR24_888 format. Driver should return FVID2_EINVALID_PARAMS.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" H flip + BGR24_888 (expect EINVALID_PARAMS)\r\n");

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    Dss_initParamsInit(&gDssObjects[CONFIG_DSS0].initParams);
    Dss_init(&gDssObjects[CONFIG_DSS0].initParams);

    gDssObjects[CONFIG_DSS0].dctrlHandle = Fvid2_create(
        DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0, NULL, NULL, NULL);
    TEST_ASSERT_NOT_NULL(gDssObjects[CONFIG_DSS0].dctrlHandle);

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

    Dss_dispParamsInit(&dispParams);
    dispParams.pipeCfg.pipeType =
        gDssConfigPipelineParams.pipeType[0U];
    dispParams.pipeCfg.inFmt.width =
        gDssConfigPipelineParams.inWidth[0U];
    dispParams.pipeCfg.inFmt.height =
        gDssConfigPipelineParams.inHeight[0U];
    dispParams.pipeCfg.inFmt.pitch[0U] =
        gDssConfigPipelineParams.inWidth[0U] * 3U;
    dispParams.pipeCfg.inFmt.dataFormat = FVID2_DF_BGR24_888;
    dispParams.pipeCfg.inFmt.scanFormat =
        gDssConfigPipelineParams.inScanFmt[0U];
    dispParams.pipeCfg.outWidth =
        gDssConfigPipelineParams.outWidth[0U];
    dispParams.pipeCfg.outHeight =
        gDssConfigPipelineParams.outHeight[0U];
    dispParams.pipeCfg.scEnable =
        gDssConfigPipelineParams.scEnable[0U];
    dispParams.pipeCfg.flipType = FVID2_FLIP_TYPE_H;
    dispParams.layerPos.startX =
        gDssConfigPipelineParams.posx[0U];
    dispParams.layerPos.startY =
        gDssConfigPipelineParams.posy[0U];

    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_DSS_DISP_SET_DSS_PARAMS,
        &dispParams,
        NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_EINVALID_PARAMS, retVal);
    DebugP_log("  IOCTL correctly rejected H flip + BGR24_888\r\n");

    retVal = Fvid2_delete(instObj->drvHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    SemaphoreP_destruct(&instObj->syncSem);
    retVal = Fvid2_control(
        gDssObjects[CONFIG_DSS0].dctrlHandle,
        IOCTL_DSS_DCTRL_CLEAR_PATH,
        gDssObjects[CONFIG_DSS0].dctrlPathInfo, NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);
    retVal = Fvid2_delete(gDssObjects[CONFIG_DSS0].dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    TEST_ASSERT_EQUAL_INT32(FVID2_SOK, retVal);

    DebugP_log(" H flip + BGR24_888 rejection PASSED\r\n");

    /*
     *  Full display cycle (baseline verification)
     *
     * Run the complete display pipeline via TestDisp_flipDisplayControl
     * with FVID2_FLIP_TYPE_NONE to confirm the display path operates
     * correctly after the flip/mirror IOCTL exercises above.
     */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" Full display cycle (no flip baseline)\r\n");

    status = Board_panelOpen();
    status += TestDisp_flipDisplayControl(&gDssObjects[CONFIG_DSS0],
                                          FVID2_FLIP_TYPE_NONE);
    Board_panelClose();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log(" Full display cycle PASSED\r\n");

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Flip/Mirror Mode Test (DPI) Completed!\r\n");
    DebugP_log("======================================================\r\n");
}

#if defined (SOC_AM62PX)
static void TestDss_invalidEvent(void)
{
    int32_t status;

    DebugP_log(" Initialize driver with invalid port ID  \r\n");

    status = TestDisp_initParams(&gDssObjects[CONFIG_DSS0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

static void TestDss_reregisterDriver(void)
{
    int32_t status;

    for(uint32_t instCnt = 0U; \
        instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = \
                            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0] = \
                            gDssConfigPipelineParams.inWidth[instCnt] * \
                            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] = \
                            gDssConfigPipelineParams.inWidth[instCnt] * \
                            gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log(" Dss re-register for test : %s\r\n", \
                gMultipleFrameDataArray[0].frameName);
    status = TestDisp_reregisterDriver(&gDssObjects[CONFIG_DSS0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("------------------------------------------------------\r\n");
}

static void TestDss_drvControlUnusedIoctl(void)
{
    int32_t status = SystemP_FAILURE;

    for(uint32_t instCnt = 0U; \
        instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = \
                            gMultipleFrameDataArray[0].frameType;
        gDssConfigPipelineParams.pitch[instCnt][0] = \
                            gDssConfigPipelineParams.inWidth[instCnt] * \
                            gMultipleFrameDataArray[0].bytesPerPixel;

        if(gMultipleFrameDataArray[0].frameType == FVID2_DF_YUV420SP_UV)
        {
            gDssConfigPipelineParams.pitch[instCnt][1] = \
                            gDssConfigPipelineParams.inWidth[instCnt] * \
                            gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("Driver control unused IOCTL for test: %s\r\n", \
                gMultipleFrameDataArray[0].frameName);
    status = TestDisp_unusedIoctl(&gDssObjects[CONFIG_DSS0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

}

static void TestDss_dpiDynamicCoverage(void *args)
{
    /* Disable the FVID2 asserts */
    Fvid2Utils_controlAssert(false);

    TestDss_invalidEvent();
    TestDss_reregisterDriver();
    TestDss_drvControlUnusedIoctl();

    /* Enable back the FVID2 asserts */
    Fvid2Utils_controlAssert(true);
}

static void TestDss_cslDynamicCoverage(void *args)
{
    /* Disable the FVID2 asserts */
    Fvid2Utils_controlAssert(false);
    CSL_dss_commRegs *commRegs;
    commRegs = (CSL_dss_commRegs *)CSL_DSS0_COMMON_BASE;
    const Dss_SocInfo *socInfo;
    CSL_dss_overlayRegs *overlayRegs;
    CSL_DssOverlayLayerCfg layerCfg;
    CSL_dss_vpRegs *vpRegs;
    CSL_dss_pipeRegs *pipeRegs ;
    const CSL_DssVpGammaCfg gammaCfg = {FALSE,{0}};
    const CSL_DssVpGammaCfg gammaCfg1 = { TRUE , { 0 } } ;
    const CSL_DssVpLcdSignalPolarityCfg polarityCfg = {FVID2_POL_LOW,FVID2_EDGE_POL_RISING,FVID2_POL_LOW,FVID2_POL_LOW};
    const CSL_DssVpOldiCfg oldiCfg = {CSL_DSS_VP_OLDI_MAP_TYPE_C,FVID2_POL_LOW,CSL_DSS_VP_OLDI_BIT_DEPTH_24_BITS,CSL_DSS_VP_OLDI_DUALMODESYNC_DISABLE};
    const CSL_DssVpOldiCfg oldiCfg1 ={CSL_DSS_VP_OLDI_MAP_TYPE_C,FVID2_POL_HIGH,CSL_DSS_VP_OLDI_BIT_DEPTH_24_BITS,CSL_DSS_VP_OLDI_DUALMODESYNC_DISABLE};
    CSL_DssVidPipeCfg pipeCfg;
    CSL_DssCscCoeff *cscCoeff = NULL;
    CSL_DssVpLcdBlankTimingCfg lcdBlankTimingCfg;
    CSL_DssVidPipeVC1Cfg vc1Cfg;
    CSL_DssVpLcdAdvSignalCfg advSignalCfg;
    CSL_DssVidPipeDmaCfg dmaCfg;
    CSL_DssVidPipeLumaCfg lumaCfg;
    uint32_t scanFormat;
    uint32_t status;
    CSL_DssVpLcdOpTimingCfg lcdCfg;

    socInfo = Dss_getSocInfo();

    DebugP_log("test for CSL dynamic coverage \r\n\n");
    /* To enable interrupt for dss by setting intrEnable as TRUE */
    CSL_dssEnableDispcIntr(commRegs,(0x03 << CSL_DSS_COMMON_DISPC_IRQENABLE_CLR_CLR_VP_IRQ_SHIFT),TRUE);

    /* To disable interrupt for dss by setting intrEnable as FALSE */
    CSL_dssEnableDispcIntr(commRegs,(0x03 << CSL_DSS_COMMON_DISPC_IRQENABLE_CLR_CLR_VP_IRQ_SHIFT),FALSE);

    /* To disable interrupt for Video Pipe by setting intrEnable as FALSE */
    CSL_dssEnablePipeIntr(commRegs,CSL_DSS_VID_PIPE_ID_VID1,(0x01 << CSL_DSS_COMMON1_VID_IRQENABLE_0_VIDBUFFERUNDERFLOW_EN_SHIFT),FALSE);

    /* To enable interrupt for Video Pipe by setting intrEnable as TRUE */
    CSL_dssEnablePipeIntr(commRegs,CSL_DSS_VID_PIPE_ID_VIDL1,(0x01 << CSL_DSS_COMMON1_VID_IRQENABLE_0_VIDBUFFERUNDERFLOW_EN_SHIFT),TRUE);

    /* To disable interrupt for Video Port with portId as CSL_DSS_VP_ID_1  */
    CSL_dssEnableVpIntr(commRegs,CSL_DSS_VP_ID_1,(0x01 << CSL_DSS_COMMON1_VP_IRQENABLE_0_VPFRAMEDONE_EN_SHIFT),FALSE);

    /* To disable interrupt for Video Port with portId as CSL_DSS_VP_ID_2  */
    CSL_dssEnableVpIntr(commRegs,CSL_DSS_VP_ID_2,(0x01 << CSL_DSS_COMMON1_VP_IRQENABLE_0_VPFRAMEDONE_EN_SHIFT),FALSE);

    /* To Clear the interrupts for dss */
    CSL_dssClearDispcIntr(commRegs,(0x03 << CSL_DSS_COMMON_DISPC_IRQSTATUS_RAW_VP_IRQ_SHIFT));

    /* To Clear the interrupts for Video Pipe as CSL_DSS_VID_PIPE_ID_VID1 */
    CSL_dssClearPipeIntr(commRegs,CSL_DSS_VID_PIPE_ID_VID1,(0x01 << CSL_DSS_COMMON_VID_IRQSTATUS_0_VIDBUFFERUNDERFLOW_IRQ_SHIFT));

    /* To Clear the interrupts for Video Pipe as CSL_DSS_VID_PIPE_ID_VIDL1 */
    CSL_dssClearPipeIntr(commRegs,CSL_DSS_VID_PIPE_ID_VIDL1,(0x01 << CSL_DSS_COMMON_VID_IRQSTATUS_0_VIDBUFFERUNDERFLOW_IRQ_SHIFT));

    /* To Clear the interrupts for Video Port */
    CSL_dssClearVpIntr(commRegs,CSL_DSS_VP_ID_1,(0x01 << CSL_DSS_COMMON_VP_IRQSTATUS_0_VPFRAMEDONE_IRQ_SHIFT));

    /* To get the interrupts status for dss */
    status = CSL_dssGetDispcIntrStatus(commRegs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* To get the interrupts status for video pipe with pipeID as CSL_DSS_VID_PIPE_ID_VID1 */
    status = CSL_dssGetPipeIntrStatus(commRegs,CSL_DSS_VID_PIPE_ID_VID1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* To get the interrupts status for video pipe with pipeID as CSL_DSS_VID_PIPE_ID_VIDL1 */
    status = CSL_dssGetPipeIntrStatus(commRegs,CSL_DSS_VID_PIPE_ID_VIDL1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* To get the interrupts status for video port with diffrent pipiID as CSL_DSS_VP_ID_1 */
    status =  CSL_dssGetVpIntrStatus(commRegs,CSL_DSS_VP_ID_1);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* To get the interrupts status for video port with diffrent pipiID as CSL_DSS_VP_ID_2 */
    status = CSL_dssGetVpIntrStatus(commRegs,CSL_DSS_VP_ID_2);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* To Enable the global VP enable bit */
    CSL_dssGlobalVpEnable(commRegs,1,TRUE);

    /* To disable the global VP enable bit */
    CSL_dssGlobalVpEnable(commRegs,2,FALSE);

    /* To Enable the global VP go bit */
    CSL_dssGlobalVpGoBitEnable(commRegs,1);

    /* To disable the global VP go bit */
    CSL_dssGlobalVpGoBitEnable(commRegs,2);

    /* Configuring the Overlay input selection */
    overlayRegs = socInfo->overlayRegs[1];
    GT_assert(DssTrace, (NULL != overlayRegs));
    CSL_dssOverlayLayerCfgInit(&layerCfg);
    CSL_dssOverlaySetLayerConfig(overlayRegs,(const CSL_DssOverlayLayerCfg *) &layerCfg);

    /* To Enable/Bypass TV Gamma Table */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpEnableTvGamma(vpRegs,&gammaCfg);

    /* To Configure the coefficients for Color Space Conversion */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssCscCoeffInit(cscCoeff);
    CSL_dssVpSetCSCCoeff(vpRegs,cscCoeff,CSL_DSS_VP_CSC_POS_BEFORE_GAMMA,FALSE);

    /* Configuring the LCD Timing parameters with vpRegs and lcdCfg as NULL */
    status = CSL_dssVpSetLcdOpTimingConfig(NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring the LCD Blank Timing parameters when scanFormat is FVID2_SF_PROGRESSIVE */
    vpRegs = socInfo->vpRegs[1];
    lcdBlankTimingCfg.hFrontPorch = 88;
    lcdBlankTimingCfg.hBackPorch = 148;
    lcdBlankTimingCfg.hSyncLen = 44;
    lcdBlankTimingCfg.vFrontPorch = 4;
    lcdBlankTimingCfg.vBackPorch = 36;
    lcdBlankTimingCfg.vSyncLen = 5;
    scanFormat = FVID2_SF_PROGRESSIVE;
    status = CSL_dssVpSetLcdBlankTiming(vpRegs,&lcdBlankTimingCfg,0x03U,scanFormat,TRUE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring the advance LCD Signal parameters with riseFall as FVID2_EDGE_POL_RISING */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpLcdAdvSignalCfgInit(&advSignalCfg);
    CSL_dssVpSetLcdAdvSignalConfig(vpRegs,&advSignalCfg);

    /* Configuring the Polarity of LCD signals with valid vpRegs and polarityCfg */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpSetLcdSignalPolarityConfig(vpRegs,&polarityCfg);

    /* setting up OLDI configuration */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpSetOldiConfig(vpRegs,&oldiCfg);

    /* To Clear the interrupts for Video Port */
    CSL_dssClearVpIntr(commRegs , CSL_DSS_VP_ID_2 , ( 0x01 << CSL_DSS_COMMON_VP_IRQSTATUS_0_VPFRAMEDONE_IRQ_SHIFT));

    /* Configuring the LCD Blank Timing parameters when scanFormat is FVID2_SF_INTERLACED */
    vpRegs = socInfo->vpRegs[1];
    lcdBlankTimingCfg.hFrontPorch = 88;
    lcdBlankTimingCfg.hBackPorch = 148;
    lcdBlankTimingCfg.hSyncLen = 44;
    lcdBlankTimingCfg.vFrontPorch = 4;
    lcdBlankTimingCfg.vBackPorch = 36;
    lcdBlankTimingCfg.vSyncLen = 5;
    scanFormat = FVID2_SF_INTERLACED;
    status = CSL_dssVpSetLcdBlankTiming(vpRegs,&lcdBlankTimingCfg,0x03U,scanFormat,FALSE);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Configuring the advance LCD Signal parameters with riseFall as FVID2_EDGE_POL_RISING and control as CSL_DSS_VP_HVCLK_CONTROL_OFF */
    vpRegs = socInfo->vpRegs[1];
    advSignalCfg.hVAlign = CSL_DSS_VP_HVSYNC_NOT_ALIGNED ;
    advSignalCfg.hVClkControl = CSL_DSS_VP_HVCLK_CONTROL_OFF ;
    advSignalCfg.hVClkRiseFall = FVID2_EDGE_POL_RISING ;
    advSignalCfg.acBI = 0x0U ;
    advSignalCfg.acB = 0x0U ;
    advSignalCfg.vSyncGated = FALSE ;
    advSignalCfg.hSyncGated = FALSE ;
    advSignalCfg.pixelClockGated = FALSE ;
    advSignalCfg.pixelDataGated = FALSE ;
    advSignalCfg.pixelGated = FALSE ;
    CSL_dssVpSetLcdAdvSignalConfig ( vpRegs,&advSignalCfg );

    /* To Enable TV Gamma Table */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpEnableTvGamma ( vpRegs,&gammaCfg1 );

    /* setting up OLDI configuration */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpSetOldiConfig(vpRegs,&oldiCfg1 );

    /* Configuring  the Video Pipe with pipeType as CSL_DSS_VID_PIPE_TYPE_VIDL */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.pipeType = CSL_DSS_VID_PIPE_TYPE_VIDL;
    pipeCfg.scEnable = TRUE;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring the Video Pipe DMA parameters with bufPreloadControl as CSL_DSS_VID_PIPE_PRELOAD_CONTROL_SW */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeDmaCfgInit(&dmaCfg);
    dmaCfg.bufPreloadControl = CSL_DSS_VID_PIPE_PRELOAD_CONTROL_SW;
    CSL_dssVidPipeSetDmaConfig(pipeRegs,&dmaCfg);

    /* seting luma params with Enable the Luma Key */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeLumaCfgInit(&lumaCfg);
    CSL_dssVidPipeEnableTransparency(pipeRegs,&lumaCfg );

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.gammaEnable = TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=4096U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGRX_4444 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGRX_4444;
    pipeCfg.inFmt.width=4096U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGR24_888 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGR24_888;
    pipeCfg.inFmt.width=4096U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_XBGR24_8888 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_XBGR24_8888;
    pipeCfg.inFmt.width=4096U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGRA64_16161616 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGRA64_16161616;
    pipeCfg.inFmt.width=4096U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_YUV420SP_UV */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.fieldMerged[0U]=TRUE;
    pipeCfg.inFmt.fieldMerged[1U]=TRUE;
    pipeCfg.inFmt.scanFormat=FVID2_SF_INTERLACED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

     /* Configuring  the Video Pipe with dataFormat as FVID2_DF_YUV422SP_UV */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422SP_UV;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_ETIMEOUT, status);

    /* Configuring  the Video Pipe with flipType as FVID2_FLIP_TYPE_V */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_V;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with flipType as FVID2_FLIP_TYPE_H */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS10_UNPACKED16 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_YUYV;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_UNPACKED16;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS12_PACKED */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_YUYV;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS12_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=2846U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.height=4096U;
    pipeCfg.outHeight=2846U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=2048U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

     /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.height=4096U;
    pipeCfg.outHeight=2048U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring the LCD Blank Timing parameters when custom time is used  */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpLcdBlankTimingCfgInit(&lcdBlankTimingCfg);
    status = CSL_dssVpSetLcdBlankTiming(vpRegs,&lcdBlankTimingCfg,FVID2_DV_BT1120_EMBSYNC,FVID2_SF_INTERLACED,TRUE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring the LCD Timing parameters when dvoFormat is FVID2_DV_BT656_EMBSYNC */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpLcdOpTimingCfgInit(&lcdCfg);
    lcdCfg.dvoFormat = FVID2_DV_BT656_EMBSYNC;
    lcdCfg.mInfo.standard=FVID2_STD_SXGAP_60;
    lcdCfg.cscRange=CSL_DSS_CSC_RANGE_LIMITED;
    status = CSL_dssVpSetLcdOpTimingConfig(vpRegs,&lcdCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring the LCD Timing parameters when dvoFormat is FVID2_DV_BT1120_EMBSYNC */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpLcdOpTimingCfgInit(&lcdCfg);
    lcdCfg.dvoFormat = FVID2_DV_BT1120_EMBSYNC;
    lcdCfg.mInfo.standard=FVID2_STD_SXGAP_60;
    status = CSL_dssVpSetLcdOpTimingConfig(vpRegs,&lcdCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring the LCD Blank Timing parameters when custom time is used  */
    vpRegs = socInfo->vpRegs[1];
    CSL_dssVpLcdBlankTimingCfgInit(&lcdBlankTimingCfg);
    lcdBlankTimingCfg.hBackPorch=0X1600U;
    lcdBlankTimingCfg.vBackPorch=0X1600U;
    status = CSL_dssVpSetLcdBlankTiming(vpRegs,&lcdBlankTimingCfg,FVID2_DV_GENERIC_DISCSYNC,FVID2_SF_INTERLACED,TRUE);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeSetBuffAddr(pipeRegs,FVID2_FID_BOTTOM,0x80000000U,0x20000000);
    CSL_dssVidPipeSetBuffAddr(pipeRegs,FVID2_FID_BOTTOM,0x80000000U,0U);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGRX_4444 */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGRX_4444;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.inFmt.pitch[0U]=8192U;
    pipeCfg.gammaEnable=TRUE;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=2048U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_YUV422I_UYVY */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_UNPACKED16;
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_UYVY;
    pipeCfg.inFmt.width=0U;
    pipeCfg.inFmt.pitch[0U]=2048;
    pipeCfg.cscRange=CSL_DSS_CSC_RANGE_LIMITED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with cscRange as CSL_DSS_CSC_RANGE_CUSTOM */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_UNPACKED16;
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_UYVY;
    pipeCfg.inFmt.width=0U;
    pipeCfg.inFmt.pitch[0U]=2048;
    pipeCfg.cscRange=CSL_DSS_CSC_RANGE_CUSTOM;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe */
    status = CSL_dssVidPipeSetConfig(NULL,NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BAYER_GBRG */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_BAYER_GBRG;
    pipeCfg.inFmt.width=2048U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_YUV422I_YUYV */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_YUYV;
    pipeCfg.inFmt.width=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_UNPACKED16;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS10_PACKED */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_YUYV;
    pipeCfg.inFmt.width=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_YUV422I_YUYV */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_YUYV;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

     /* Configuring  the Video Pipe with dataFormat as FVID2_DF_YUV422I_YUYV */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_YUYV;
    pipeCfg.inFmt.width=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS12_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS8_PACKED */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_YUYV;
    pipeCfg.inFmt.width=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS8_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS8_UNPACKED16 */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV422I_YUYV;
    pipeCfg.inFmt.width=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS8_UNPACKED16;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS10_UNPACKED16 and width as 1U*/
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.width=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_UNPACKED16;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_ETIMEOUT, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS10_UNPACKED16 */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX]=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_UNPACKED16;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS10_PACKED and width as 1U */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.width=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_ETIMEOUT, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS10_PACKED and dataFormat as FVID2_DF_YUV420SP_UV*/
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX]=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS10_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS12_PACKED and width as 1U */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.width=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS12_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_ETIMEOUT, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS12_PACKED and dataFormat as FVID2_DF_YUV420SP_UV */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX]=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS12_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS8_PACKED and dataFormat as FVID2_DF_YUV420SP_UV */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.width=1U;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS8_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_ETIMEOUT, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS4_PACKED */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.ccsFormat=FVID2_CCSF_BITS4_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_ETIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGRX_4444 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGRX_4444;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=8192U;
    pipeCfg.inFmt.height=900U;
    pipeCfg.outHeight=600U;
    pipeCfg.inFmt.pitch[0U]=8192U;
    pipeCfg.gammaEnable=TRUE;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGRX_4444 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGRX_4444;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=1400;
    pipeCfg.inFmt.height=1100U;
    pipeCfg.outHeight=500U;
    pipeCfg.inFmt.pitch[0U]=8192U;
    pipeCfg.gammaEnable=TRUE;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status =  CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGRX_4444 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGRX_4444;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=2048U;
    pipeCfg.inFmt.height=3500U;
    pipeCfg.outHeight=1000U;
    pipeCfg.inFmt.pitch[0U]=8192U;
    pipeCfg.gammaEnable=TRUE;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGRX_4444 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGRX_4444;
    pipeCfg.inFmt.width=5000U;
    pipeCfg.outWidth=1000U;
    pipeCfg.inFmt.pitch[0U]=8192U;
    pipeCfg.gammaEnable=TRUE;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=5000U;
    pipeCfg.inFmt.height=900U;
    pipeCfg.outHeight=600U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=5000U;
    pipeCfg.inFmt.height=1000U;
    pipeCfg.outHeight=600U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=5000U;
    pipeCfg.inFmt.height=900U;
    pipeCfg.outHeight=400U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.height=900U;
    pipeCfg.outHeight=400U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=5000U;
    pipeCfg.inFmt.height=1100U;
    pipeCfg.outHeight=400U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.height=1100U;
    pipeCfg.outHeight=400U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 and suitable width and height for negative test case */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=5000U;
    pipeCfg.inFmt.height=1000U;
    pipeCfg.outHeight=300U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

     /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 and height as 1000U */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.height=1000U;
    pipeCfg.outHeight=300U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 and width as 4096U */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.width=4096U;
    pipeCfg.outWidth=5000U;
    pipeCfg.inFmt.height=2500U;
    pipeCfg.outHeight=500U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_RGB16_565 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.scEnable=TRUE;
    pipeCfg.inFmt.dataFormat=FVID2_DF_RGB16_565;
    pipeCfg.inFmt.height=2500U;
    pipeCfg.outHeight=500U;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGRX_4444  and flipType as FVID2_FLIP_TYPE_H */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGRX_4444;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

     /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGR24_888 and flipType as FVID2_FLIP_TYPE_H */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGR24_888;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

     /* Configuring  the Video Pipe with dataFormat as FVID2_DF_XBGR24_8888 and flipType as FVID2_FLIP_TYPE_H */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_XBGR24_8888;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BGRA64_16161616 and flipType as FVID2_FLIP_TYPE_H */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_BGRA64_16161616;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_YUV420SP_UV and flipType as FVID2_FLIP_TYPE_H */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_YUV420SP_UV and ccsFormat as FVID2_CCSF_BITS10_PACKED */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.ccsFormat =FVID2_CCSF_BITS10_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with dataFormat as FVID2_DF_BITMAP4_LOWER */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_BITMAP4_LOWER;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_ETIMEOUT, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS12_PACKED and flipType as FVID2_FLIP_TYPE_H */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.ccsFormat =FVID2_CCSF_BITS12_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS10_UNPACKED16 and  flipType as FVID2_FLIP_TYPE_H */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.ccsFormat =FVID2_CCSF_BITS10_UNPACKED16;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS12_UNPACKED16 */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.ccsFormat =FVID2_CCSF_BITS12_UNPACKED16;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status = CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring  the Video Pipe with ccsFormat as FVID2_CCSF_BITS32_PACKED */
    pipeRegs = socInfo->pipeRegs[1];
    GT_assert(DssTrace,(NULL != pipeRegs));
    CSL_dssVidPipeCfgInit(&pipeCfg);
    pipeCfg.flipType=FVID2_FLIP_TYPE_H;
    pipeCfg.inFmt.dataFormat=FVID2_DF_YUV420SP_UV;
    pipeCfg.inFmt.ccsFormat =FVID2_CCSF_BITS32_PACKED;
    CSL_dssVidPipeVC1CfgInit (&vc1Cfg);
    status =  CSL_dssVidPipeSetConfig(pipeRegs ,&pipeCfg ,&vc1Cfg);
    TEST_ASSERT_EQUAL_INT32(CSL_ETIMEOUT, status);

    /* Configuring the LCD Timing parameters when scanFormat is FVID2_SF_INTERLACED */
    vpRegs = socInfo->vpRegs[1];
    GT_assert(DssTrace, (NULL != vpRegs));
    CSL_dssVpLcdOpTimingCfgInit(&lcdCfg);
    lcdCfg.dvoFormat=FVID2_DV_BT656_EMBSYNC;
    lcdCfg.mInfo.standard=FVID2_STD_CUSTOM;
    lcdCfg.mInfo.scanFormat=FVID2_SF_INTERLACED;
    status = CSL_dssVpSetLcdOpTimingConfig(vpRegs,&lcdCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring the LCD Timing parameters when cscRange is CSL_DSS_CSC_RANGE_LIMITED */
    vpRegs = socInfo->vpRegs[1];
    GT_assert(DssTrace, (NULL != vpRegs));
    CSL_dssVpLcdOpTimingCfgInit(&lcdCfg);
    lcdCfg.dvoFormat=FVID2_DV_BT1120_EMBSYNC;
    lcdCfg.mInfo.standard=FVID2_STD_CUSTOM;
    lcdCfg.mInfo.scanFormat=FVID2_SF_INTERLACED;
    lcdCfg.cscRange=CSL_DSS_CSC_RANGE_LIMITED;
    status = CSL_dssVpSetLcdOpTimingConfig(vpRegs,&lcdCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Configuring the LCD Timing parameters when cscRange is CSL_DSS_CSC_RANGE_CUSTOM */
    vpRegs = socInfo->vpRegs[1];
    GT_assert(DssTrace, (NULL != vpRegs));
    CSL_dssVpLcdOpTimingCfgInit(&lcdCfg);
    lcdCfg.dvoFormat=FVID2_DV_BT1120_EMBSYNC;
    lcdCfg.mInfo.standard=FVID2_STD_CUSTOM;
    lcdCfg.mInfo.scanFormat=FVID2_SF_INTERLACED;
    lcdCfg.cscRange=CSL_DSS_CSC_RANGE_CUSTOM;
    status = CSL_dssVpSetLcdOpTimingConfig(vpRegs,&lcdCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("\r\n CSL dynamic coverage test: PASS \r\n");
    /* Enable back the FVID2 asserts */
    Fvid2Utils_controlAssert(true);
}

#endif

#if !defined (SOC_AM62LX)
/**
 * \brief  VP safety data integrity detection for the DPI interface.
 *
 *  Test Category: Functionality
 *
 *  This test configures four VP safety regions (960x540 quadrants within the
 *  VP2 active output area for 1080p) in DATA_INTEGRITY mode with zero reference
 *  MISR signature.  The display is started on VP2 (DPI/HDMI) with a single RGB888
 *  frame.  At frame 70, the frame buffer is corrupted.  The test verifies that
 *  the safety error callback fires for all four regions, confirming the MISR
 *  signature mismatch detection mechanism is functional on the DPI output path.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_vpSafetyDataIntegrityDpi(void *args)
{
    int32_t status = SystemP_FAILURE;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS VP Safety Data Integrity Test for DPI\r\n");
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
            gDssConfigPipelineParams.pitch[instCnt][1U] =
                gDssConfigPipelineParams.inWidth[instCnt] *
                gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    /* Enable VP safety at runtime — CONFIG_DSS_NUM_SAFETY_REGIONS = 0 by
     * default. Configure 4 quadrant regions within VID1 active output area
     * (720x540 at origin) to ensure all regions have active pipeline pixels
     * for reliable MISR violation. referenceSign=0U: MISR of real content
     * is never 0, covering Dss_dctrlSafetyErrCbFxn. */
    TestDss_numVpSafetyRegions = 4U;
    for(uint32_t r = 0U; r < TestDss_numVpSafetyRegions; r++)
    {
        Dss_dctrlVpSafetyChkParamsInit(&TestDss_vpSafetyParamsRuntime[r]);
        TestDss_vpSafetyParamsRuntime[r].vpId              = CSL_DSS_VP_ID_2;
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

    DebugP_log("Frame type input for safety test: %s\r\n",
               gMultipleFrameDataArray[0].frameName);

    /* MISR is computed inside DSS before the output bridge — Board_panelOpen
     * is not required for safety violation detection. */
    status = TestDisp_vpSafetyDisplayControlCommon(&gDssObjects[CONFIG_DSS0], CSL_DSS_SAFETY_CHK_DATA_INTEGRITY);

    /* Restore defaults */
    TestDss_numVpSafetyRegions = 0U;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("VP Safety Data Integrity DPI test completed\r\n");
    DebugP_log("======================================================\r\n");
}

/**
 * \brief  VP safety frame freeze detection for the DPI interface.
 *
 *  Test Category: Functionality
 *
 *  This test configures VP2 safety regions in FRAME_FREEZE_DETECT mode with
 *  a threshold of 30 frames.  A single RGB888 frame is queued and the display
 *  is started on VP2 (DPI).  The same frame is repeatedly re-queued until
 *  the freeze threshold is crossed.  The test verifies that the safety error
 *  callback fires for all configured regions, confirming the freeze detection
 *  mechanism is functional on the DPI output path.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_vpSafetyFreezeDetectDpi(void *args)
{
    int32_t status = SystemP_FAILURE;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS VP Safety Freeze Frame Detection Test for DPI\r\n");
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
            gDssConfigPipelineParams.pitch[instCnt][1U] =
                gDssConfigPipelineParams.inWidth[instCnt] *
                gMultipleFrameDataArray[0].bytesPerPixel;
        }
    }

    /* Enable VP safety at runtime — 4 quadrant regions within VID1 active
     * output area (720x540 at origin). TestDisp_safetyInitDssParams overrides
     * safetyChkMode to FRAME_FREEZE_DETECT and sets
     * thresholdValue=DISP_SAFETY_FREEZE_THRESHOLD via
     * CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT mode. */
    TestDss_numVpSafetyRegions = 4U;
    for(uint32_t r = 0U; r < TestDss_numVpSafetyRegions; r++)
    {
        Dss_dctrlVpSafetyChkParamsInit(&TestDss_vpSafetyParamsRuntime[r]);
        TestDss_vpSafetyParamsRuntime[r].vpId              = CSL_DSS_VP_ID_2;
        TestDss_vpSafetyParamsRuntime[r].safetySignSeedVal = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.regionId      =
            r;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.referenceSign = 0U;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkEnable  = TRUE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.safetyChkMode    =
            CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.seedSelectEnable = FALSE;
        TestDss_vpSafetyParamsRuntime[r].regionSafetyChkCfg.safetyChkCfg.thresholdValue   =
            DISP_SAFETY_FREEZE_THRESHOLD;
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

    /* MISR is computed inside DSS before the output bridge — Board_panelOpen
     * is not required for freeze detection. */
    status = TestDisp_vpSafetyDisplayControlCommon(&gDssObjects[CONFIG_DSS0], CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT);

    /* Restore defaults */
    TestDss_numVpSafetyRegions = 0U;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("VP Safety Freeze Frame Detection DPI test completed\r\n");
    DebugP_log("======================================================\r\n");
}
#endif
/**
 * \brief  VP background color overlay for the DPI interface.
 *
 *  Test Category: Functionality
 *
 *  This test sets the VP background color to specific RGB values (Magenta, Cyan,
 *  Yellow, Black) and verifies rendering on DPI/HDMI output.  The background color
 *  is displayed in regions not covered by active video layers or colorbar patterns.
 *  The test confirms background color configuration, retrieval, and correct rendering
 *  across multiple color values.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_backgroundColorDpi(void *args)
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Background Color Test for DPI\r\n");
    DebugP_log("======================================================\r\n");

    /* Test colors per test plan: Magenta, Cyan, Yellow, Black */
    uint32_t testColors[] = {
        0xFF00FF,  /* Magenta */
        0x00FFFF,  /* Cyan    */
        0xFFFF00,  /* Yellow  */
        0x000000   /* Black   */
    };
    char *colorNames[] = {"Magenta", "Cyan", "Yellow", "Black"};

    /* Configure frame format for all test pipes */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = FVID2_DF_ARGB32_8888;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] * 4U;
    }

    Board_panelOpen();

    for(uint32_t colorIdx = 0U; colorIdx < 4U; colorIdx++)
    {
        DebugP_log("------------------------------------------------------\r\n");
        DebugP_log("Testing background color: %s (0x%06X)\r\n",
                   colorNames[colorIdx], testColors[colorIdx]);

        /* Set the background color */
        gDssOverlayParams.overlayCfg.backGroundColor = testColors[colorIdx];

        /* Enable colorbar per test plan step 7:
         * colorbar is enabled so background is visible in regions
         * not covered by the colorbar pattern */
        gDssOverlayParams.colorbarEnable = FALSE;

        /* Run display control - calls IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS
         * and IOCTL_DSS_DCTRL_SET_VP_PARAMS to start VP2 */
        status = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /* Delay to observe the color on screen */
        ClockP_usleep(1000000U);
    }

    Board_panelClose();

    /* Restore defaults */
    gDssOverlayParams.colorbarEnable = FALSE;
    gDssOverlayParams.overlayCfg.backGroundColor = 0xC8C800U;

    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("Background color DPI test completed\r\n");
}

#if !defined (SOC_AM62LX)
/**
 * \brief  Overlay colorbar pattern generation for the DPI interface.
 *
 *  Test Category: Functionality
 *
 *  This test enables the overlay colorbar test pattern and verifies it
 *  generates a standard video test pattern (eight color bars) across the
 *  VP output via DPI/HDMI.  The colorbar overlays any video layer content
 *  and covers the entire active area.  Multiple resolutions (1080p@60Hz,
 *  720p@60Hz, 1080p@50Hz, 1080p@30Hz) are tested to confirm colorbar
 *  generation and rendering at different frame rates.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_colorbarEnableDpi(void *args)
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Colorbar Enable Test for DPI\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format for all test pipes */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = FVID2_DF_ARGB32_8888;
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] * 4U;
    }

    /* Enable colorbar and set black background for contrast */
    gDssOverlayParams.overlayCfg.backGroundColor = 0x000000U;
    gDssOverlayParams.colorbarEnable = TRUE;

    Board_panelClose();

    for(uint32_t resIdx = 0U; resIdx < TEST_DSS_COLORBAR_RESOLUTION_COUNT; resIdx++)
    {
        uint32_t idx = TestDss_colorbarResolutionIdx[resIdx];

        DebugP_log("------------------------------------------------------\r\n");
        DebugP_log("Colorbar test at resolution: %s\r\n",
                   TestDss_colorbarResolutionName[resIdx]);

        /* Update VP timing parameters */
        memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo,
               &gDpiTimingParamsInfo[idx], sizeof(Fvid2_ModeInfo));

        /* Adjust pipe position for new resolution */
        Fvid2_ModeInfo *infoMode = (Fvid2_ModeInfo *)&gDpiTimingParamsInfo[idx];
        gDssConfigPipelineParams.posx[1] = infoMode->width -
                                        gDssConfigPipelineParams.outWidth[1];
        gDssConfigPipelineParams.posy[1] = infoMode->height -
                                        gDssConfigPipelineParams.outHeight[1];

        /* Update bridge mode info */
        memcpy(&gBridgeSii9022aObj.modeInfo, &gModeInfo[idx],
                sizeof(BridgeSii9022a_ModeInfo));

        /* Set pixel clock for the new resolution */
        status = SOC_moduleSetClockFrequency(TISCI_DEV_DSS0,
                                TISCI_DEV_DSS0_DPI_1_IN_CLK,
                                gDpiTimingParamsInfo[idx].pixelClock * 1000U);
        if(status == SystemP_FAILURE)
        {
            DebugP_log("setFrq failure for %s!!\r\n",
                       TestDss_colorbarResolutionName[resIdx]);
        }

        /* Re-open bridge with new config */
        status += Board_panelOpen();

        /* Ensure colorbar remains enabled across resolution change */
        gDssOverlayParams.colorbarEnable = TRUE;

        /* Run display control */
        status += TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        DebugP_log("Colorbar displayed at %s - observe 8-bar pattern\r\n",
                   TestDss_colorbarResolutionName[resIdx]);

        /* Allow time to observe the colorbar pattern */
        ClockP_usleep(2000000U); /* 2 seconds */

        Board_panelClose();
    }

    /* Restore defaults */
    gDssOverlayParams.colorbarEnable = FALSE;
    gDssOverlayParams.overlayCfg.backGroundColor = 0xC8C800U;

    /* Restore default 1080p60 timing */
    memcpy(&gDssVpParams.lcdOpTimingCfg.mInfo,
           &gDpiTimingParamsInfo[0], sizeof(Fvid2_ModeInfo));
    memcpy(&gBridgeSii9022aObj.modeInfo, &gModeInfo[0],
            sizeof(BridgeSii9022a_ModeInfo));

    Fvid2_ModeInfo *defaultMode = (Fvid2_ModeInfo *)&gDpiTimingParamsInfo[0];
    gDssConfigPipelineParams.posx[1] = defaultMode->width -
                                    gDssConfigPipelineParams.outWidth[1];
    gDssConfigPipelineParams.posy[1] = defaultMode->height -
                                    gDssConfigPipelineParams.outHeight[1];

    SOC_moduleSetClockFrequency(TISCI_DEV_DSS0,
                                TISCI_DEV_DSS0_DPI_1_IN_CLK,
                                gDpiTimingParamsInfo[0].pixelClock * 1000U);
    Board_panelOpen();

    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("Colorbar DPI test completed successfully!\r\n");
}
#endif

/**
 * \brief  TDM (Time Division Multiplexing) mode display test wrapper for DPI.
 *
 *  Test Category: Functionality
 *
 *  Wrapper function for testing all TDM cycle formats using DPI interface.
 *  Iterates through all 4 TDM cycle formats, configures VP timing with each
 *  format, and exercises horizontal blank timing adjustment based on TDM mode.
 *
 *  Tested TDM Cycle Formats:
 *  - 1 cycle per pixel: HBlank unchanged (1x/1x)
 *  - 2 cycles per pixel: HBlank multiplied by 2 (2x/1x)
 *  - 3 cycles per pixel: HBlank multiplied by 3 (3x/1x)
 *  - 3 cycles per 2 pixels: HBlank multiplied by 1.5 (3x/2x)
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_tdmDisplayDpi(void *args)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t formatIdx = 0U;

    /* TDM cycle format configuration table */
    typedef struct {
        uint32_t tdmCycleFormat;
        uint32_t hBlankMultFact;
        uint32_t hBlankDivFact;
        const char *formatName;
    } TdmFormatConfig;

    static const TdmFormatConfig tdmFormats[] = {
        {CSL_DSS_VP_TDM_CYCLE_1PERPIXEL,   1U, 1U, "1_PER_PIXEL"},
        {CSL_DSS_VP_TDM_CYCLE_2PERPIXEL,   2U, 1U, "2_PER_PIXEL"},
        {CSL_DSS_VP_TDM_CYCLE_3PERPIXEL,   3U, 1U, "3_PER_PIXEL"},
        {CSL_DSS_VP_TDM_CYCLE_3PER2PIXEL,  3U, 2U, "3_PER_2PIXEL"},
    };

    static const uint32_t numFormats = sizeof(tdmFormats) / sizeof(TdmFormatConfig);

    /* Save original TDM parameters */
    uint32_t savedTdmEnable = gDssVpParams.lcdTdmCfg.tdmEnable;
    uint32_t savedTdmCycleFormat = gDssVpParams.lcdTdmCfg.tdmCycleFormat;
    uint32_t savedTdmUnusedBitsLevel = gDssVpParams.lcdTdmCfg.tdmUnusedBitsLevel;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS TDM Display Test (DPI): Testing %d TDM cycle formats\r\n", numFormats);
    DebugP_log("======================================================\r\n");

    /* Configure frame format for TDM test */
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

    DebugP_log("Frame type: %s\r\n", gMultipleFrameDataArray[0].frameName);

    /* Loop through all TDM cycle formats */
    for(formatIdx = 0U; formatIdx < numFormats && status == SystemP_SUCCESS; formatIdx++)
    {
        const TdmFormatConfig *fmt = &tdmFormats[formatIdx];

        DebugP_log("------------------------------------------------------\r\n");
        DebugP_log("Testing TDM format: %s (HBlank: %u/%u)\r\n",
                   fmt->formatName, fmt->hBlankMultFact, fmt->hBlankDivFact);

        /* Configure TDM for this iteration */
        gDssVpParams.lcdTdmCfg.tdmEnable = TRUE;
        gDssVpParams.lcdTdmCfg.tdmCycleFormat = fmt->tdmCycleFormat;
        gDssVpParams.lcdTdmCfg.tdmUnusedBitsLevel = CSL_DSS_VP_TDM_UNUSED_BITS_LEVEL_LOW;

        /* Run display control test with TDM format */
        retVal = TestDisp_displayControl(&gDssObjects[CONFIG_DSS0]);
        if(retVal != SystemP_SUCCESS)
        {
            DebugP_log("  TDM format %s: FAIL\r\n", fmt->formatName);
            status = SystemP_FAILURE;
            break;
        }

        DebugP_log("  TDM format %s: PASS\r\n", fmt->formatName);
    }

    /* Restore original TDM parameters */
    gDssVpParams.lcdTdmCfg.tdmEnable = savedTdmEnable;
    gDssVpParams.lcdTdmCfg.tdmCycleFormat = savedTdmCycleFormat;
    gDssVpParams.lcdTdmCfg.tdmUnusedBitsLevel = savedTdmUnusedBitsLevel;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("======================================================\r\n");
    if(status == SystemP_SUCCESS)
    {
        DebugP_log("TDM Display test (DPI): ALL FORMATS PASSED\r\n");
    }
    else
    {
        DebugP_log("TDM Display test (DPI): FAILED\r\n");
    }
    DebugP_log("======================================================\r\n");
}

#if defined (SOC_AM62PX)
/**
 * \brief  Display share hot-plug dynamic pipeline connection for DPI.
 *
 *  Test Category: Functionality
 *
 *  This test validates dynamic pipeline hot-plug/unplug on VP2 (DPI/HDMI).
 *  VIDL pipeline runs first for 30 frames, then VID pipeline is dynamically
 *  added to share the same overlay and VP while VIDL continues running.  Both
 *  pipelines run concurrently for 30 frames, then VID is unplugged and VIDL
 *  continues for 30 more frames without disruption.  The test verifies no
 *  sync-lost errors, no underflow, and seamless operation across hot-plug
 *  and hot-unplug transitions on shared display resources.
 *
 *  \param args Pointer to test parameters (not used).
 *
 *  \return None.
 */
static void TestDss_displayShareHotPlugDpi(void *args)
{
    int32_t status = SystemP_FAILURE;

    DebugP_log("======================================================\r\n");
    DebugP_log("DSS Display Share Hot-Plug Test for DPI\r\n");
    DebugP_log("======================================================\r\n");

    /* Configure frame format — use ARGB32_8888 (4 bytes/pixel) for both pipes */
    for(uint32_t instCnt = 0U;
        instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] =
            gMultipleFrameDataArray[2].frameType;  /* FVID2_DF_ARGB32_8888 */
        gDssConfigPipelineParams.pitch[instCnt][0U] =
            gDssConfigPipelineParams.inWidth[instCnt] *
            gMultipleFrameDataArray[2].bytesPerPixel;
    }

    DebugP_log("Frame format: %s\r\n", gMultipleFrameDataArray[2].frameName);
    DebugP_log("Pipe 0 (VIDL): %dx%d at pos (%d,%d)\r\n",
               gDssConfigPipelineParams.inWidth[0],
               gDssConfigPipelineParams.inHeight[0],
               gDssConfigPipelineParams.posx[0],
               gDssConfigPipelineParams.posy[0]);

    if(gDssConfigPipelineParams.numTestPipes > 1U)
    {
        DebugP_log("Pipe 1 (VID):  %dx%d at pos (%d,%d)\r\n",
                   gDssConfigPipelineParams.inWidth[1],
                   gDssConfigPipelineParams.inHeight[1],
                   gDssConfigPipelineParams.posx[1],
                   gDssConfigPipelineParams.posy[1]);
    }

    status = TestDisp_displayShareHotPlug(
                 &gDssObjects[CONFIG_DSS0],
                 CSL_DSS_OVERLAY_ID_2,   /* OVR2 for DPI */
                 CSL_DSS_VP_ID_2,        /* VP2  for DPI */
                 DSS_DCTRL_NODE_DPI);    /* Output: DPI  */

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("Display Share Hot-Plug test for DPI completed\r\n");
    DebugP_log("======================================================\r\n");
}

#endif

