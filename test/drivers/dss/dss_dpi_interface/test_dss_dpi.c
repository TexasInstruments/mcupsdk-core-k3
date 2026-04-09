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
extern int32_t TestDisp_vpSafetyDisplayControlCommon(Dss_Object *appObj, uint32_t safetyMode);
#if defined (SOC_AM62PX)
extern int32_t TestDisp_initParams(Dss_Object *appObj);
extern int32_t TestDisp_reregisterDriver(Dss_Object *appObj);
extern int32_t TestDisp_createDriver(Dss_Object *appObj);
extern int32_t TestDisp_unusedIoctl(Dss_Object *appObj);
#endif

/* Test Cases */
static void test_dss_mulitiple_frame_formats(void *args);
static void test_dss_multiple_dpi_resolution(void *args);
static void TestDss_vpSafetyDataIntegrityDpi(void *args);
static void TestDss_vpSafetyFreezeDetectDpi(void *args);

#if defined (SOC_AM62PX)
static void TestDss_dpiDynamicCoverage(void *args);
static void TestDss_cslDynamicCoverage(void *args);
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

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{

    UNITY_BEGIN();

    RUN_TEST(test_dss_mulitiple_frame_formats, 4796, NULL);
    RUN_TEST(test_dss_multiple_dpi_resolution, 4797, NULL);
    RUN_TEST(TestDss_vpSafetyDataIntegrityDpi, 11294, NULL);
    RUN_TEST(TestDss_vpSafetyFreezeDetectDpi, 11295, NULL);

#if defined (SOC_AM62PX)
    RUN_TEST(TestDss_cslDynamicCoverage, 6127, NULL);
    RUN_TEST(TestDss_dpiDynamicCoverage, 6067, NULL);
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
