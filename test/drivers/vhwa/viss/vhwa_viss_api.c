/*
*  Copyright (c) Texas Instruments Incorporated 2023
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
*  \file vhwa_viss_api.c
*
*  \brief VHWA VISS APIs
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>
#include <drivers/vhwa/include/vhwa_m2mViss.h>
#include "vhwa_viss_test_api.h"
#include "vhwa_viss_cfg.h"

#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/gtc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 *  Input Offset between two test cases, used mainly for zebu/qt,
 *  so that buffers can be loaded in one shot
 */
#define VHWA_VISS_TEST_IN_BUF_OFFSET     (8*1024*1024)

/*
 *  Output Offset between two test cases, used mainly for zebu/qt,
 *  so that buffers can be saved in one shot
 */
#define VHWA_VISS_TEST_OUT_BUF_OFFSET    (16*1024*1024)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t AppViss_test(AppViss_TestParams *tPrms);
static int32_t VissApp_init();

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

AppViss_TestObject  gAppVissTestObject[VHWA_M2M_VISS_MAX_HANDLES];

bool gConfigThroughUDMA = false;

uint32_t configTicks;

/* ========================================================================== */
/*                            Static Variables                                */
/* ========================================================================== */

static uint64_t gVissTestSrcBuf = (uint64_t )(0xB0000000u);
static uint64_t gVissTestDestBuf = (uint64_t )(0xB8000000u);

static uint32_t gVissTestSrcBufFreeIdx = 0u;
static uint32_t gVissTestDstBufFreeIdx = 0u;

static struct VHWA_Udma_DrvObj gVissAppUdmaDrvObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void AppVissMain(void *args)
{
    int32_t                 status;
    VHWA_Udma_DrvHandle          drvHandle = &gVissAppUdmaDrvObj;
    AppViss_TestParams     *tPrms;

    Drivers_open();
    Board_driversOpen();

    status = VissApp_init();

    GTC_enable();
    int32_t testCaseID = -1;

    if (FVID2_SOK == status)
    {
        while(1)
        {
            DebugP_log (" Enter test ID to run [-1 for all tests, 0 >=  Specific test case]: ");
            scanf("%d", &testCaseID);
            
            tPrms = &gAppVissTestPrms[testCaseID];

            gVissTestSrcBufFreeIdx = 0u;
            gVissTestDstBufFreeIdx = 0u;

            DebugP_log (" Starting Test %s\n", tPrms->testName);
            if(tPrms->isEnableTest == TRUE)
            {
                status = AppViss_test(tPrms);
            }
            else
            {
                DebugP_log ("Test Case Disabled\n");
            }
            if (FVID2_SOK != status)
            {
                DebugP_log ("Error Running TestCase: %s\n", tPrms->testName);
                break;
            }
        }
    }

    AppViss_deInit(drvHandle);

    DebugP_log (" Exiting \n");

    Board_driversClose();
    Drivers_close();
}

int32_t AppViss_Init(VHWA_Udma_DrvHandle udmaDrvHndl)
{
    int32_t                 status;
    Vhwa_M2mVissSl2Params   sl2AllocPrms;
    Vhwa_M2mVissInitParams  initPrms;

    /* Initialize VISS Init parameters */
    Vhwa_m2mVissInitParamsInit(&initPrms);

    /* Set UDMA driver handle */
    initPrms.udmaDrvHndl = NULL;

    status = Vhwa_m2mVissInit(&initPrms);
    if (FVID2_SOK != status)
    {
        DebugP_log(" VISS_TEST_APP: VISS Init Failed\n");
    }
    else
    {
        Vhwa_m2mVissSl2ParamsInit(&sl2AllocPrms);

        status = Vhwa_m2mVissAllocSl2(&sl2AllocPrms);
        if (FVID2_SOK != status)
        {
            DebugP_log(" VISS_TEST_APP: SL2 Alloc Failed !!!\n");
        }
    }

    Fvid2Utils_memset(gAppVissTestObject, 0x0,
        sizeof(AppViss_TestObject)*VHWA_M2M_VISS_MAX_HANDLES);

    return (status);
}

void AppViss_deInit(VHWA_Udma_DrvHandle udmaDrvHndl)
{
    int32_t         status;

    Vhwa_m2mVissDeInit();

    status = Vhwa_Udma_deinit(udmaDrvHndl);
    if(UDMA_SOK != status)
    {
        //DebugP_log("[Error] UDMA deinit failed!!\n");
    }

    Fvid2_deInit(NULL);
}


int32_t AppVissFrameComplCb(Fvid2_Handle handle, void *appData)
{
    AppViss_TestObject *tObj = (AppViss_TestObject *)appData;

    if (NULL != tObj)
    {
        SemaphoreP_post(&tObj->waitForProcessCmpl);
    }

    return FVID2_SOK;
}

int32_t AppViss_Create(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t              status;

    AppViss_TestObject   *tObj = &gAppVissTestObject[hidx];

    status = SemaphoreP_constructMutex(&tObj->waitForProcessCmpl);

    if (SystemP_SUCCESS == status)
    {
        tObj->createArgs.enablePsa = FALSE;

        tObj->cbPrms.cbFxn   = AppVissFrameComplCb;
        tObj->cbPrms.appData = tObj;

        tObj->handle = Fvid2_create(FVID2_VHWA_M2M_VISS_DRV_ID,
            VHWA_M2M_VISS_DRV_INST0, (void *)&tObj->createArgs,
            NULL, &tObj->cbPrms);
    }
    else
    {
        DebugP_log (" Could not Create Semaphore %d \n", hidx);
    }

    if (NULL != tObj->handle)
    {
        status = FVID2_SOK;
    }
    else
    {
        DebugP_log (" Could not Create Handlle%d \n", hidx);
        status = FVID2_EFAIL;
    }

    return (status);
}


void AppViss_Delete(AppViss_TestParams *tPrms, uint32_t hidx)
{
    AppViss_TestObject   *tObj = &gAppVissTestObject[hidx];

    if (NULL != tObj->handle)
    {
        Fvid2_delete(tObj->handle, NULL);
        tObj->handle = NULL;
    }

    SemaphoreP_destruct(&tObj->waitForProcessCmpl);

}
int32_t AppViss_SetParams(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];
    AppViss_TestConfig *tCfg = NULL;

    tCfg = tPrms->testCfg[hidx];

    status = Fvid2_control(tObj->handle, IOCTL_VHWA_M2M_VISS_SET_PARAMS,
        (void *)&tCfg->vissPrms, NULL);

    return (status);
}

int32_t AppViss_SetAllConfig(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status = FVID2_EBADARGS;
    Vhwa_M2mVissParams *vissPrms = NULL;

    if ((NULL != tPrms) && (hidx < VHWA_M2M_VISS_MAX_HANDLES))
    {
        vissPrms = &tPrms->testCfg[hidx]->vissPrms;

        status = AppViss_SetParams(tPrms, hidx);
        if (FVID2_SOK != status)
        {
            DebugP_log(" VISS_TEST_APP: SetParams Failed \n");
            status = FVID2_EFAIL;
            return status;
        }

        status = AppViss_SetRfeConfig(tPrms, hidx);
        if (FVID2_SOK != status)
        {
            DebugP_log(" VISS_TEST_APP: Set RFE Config Failed \n");
            status = FVID2_EFAIL;
            return status;
        }
        status = AppViss_SetFcpConfig(tPrms, hidx);
        if (FVID2_SOK != status)
        {
            DebugP_log(" VISS_TEST_APP: Set FCP Config Failed \n");
            status = FVID2_EFAIL;
            return status;
        }
        if(vissPrms->enableGlbce == (uint32_t)TRUE)
        {
            status = AppViss_SetGlbceConfig(tPrms, hidx);
            if (FVID2_SOK != status)
            {
                DebugP_log(" VISS_TEST_APP: Set GLBCE Config Failed \n");
                status = FVID2_EFAIL;
                return status;
            }
        }
        if(vissPrms->enableNsf4 == (uint32_t)TRUE)
        {
            status = AppViss_SetNsf4Config(tPrms, hidx);
            if (FVID2_SOK != status)
            {
                DebugP_log(" VISS_TEST_APP: Set NSF4 Config Failed \n");
                status = FVID2_EFAIL;
                return status;
            }
        }
        status = AppViss_SetH3aConfig(tPrms, hidx);
        if (FVID2_SOK != status)
        {
            DebugP_log(" VISS_TEST_APP: Set H3A Config Failed \n");
            status = FVID2_EFAIL;
            return status;
        }
#if defined (IP_VERSION_VPAC_V3)
        status = AppViss_SetFcp2Config(tPrms, hidx);
        if (FVID2_SOK != status)
        {
            DebugP_log(" VISS_TEST_APP: Set FCP2 Config Failed \n");
            status = FVID2_EFAIL;
            return status;
        }
#endif
#if defined (IP_VERSION_VPAC_V3) || defined (IP_VERSION_VPAC_V4)
        if(vissPrms->enableCac == (uint32_t)TRUE)
        {
            status = AppViss_SetCacConfig(tPrms, hidx);
            if (FVID2_SOK != status)
            {
                DebugP_log(" VISS_TEST_APP: Set CAC Config Failed \n");
                status = FVID2_EFAIL;
                return status;
            }
        }
#endif
#if defined (IP_VERSION_VPAC_V4)
        if(vissPrms->enablePcid == (uint32_t)TRUE)
        {
            status = AppViss_SetPcidParams(tPrms, hidx);
            if (FVID2_SOK != status)
            {
                DebugP_log(" VISS_TEST_APP: SetParams for PCID Failed \n");
                status = FVID2_EFAIL;
                return status;
            }
        }
#endif
    }

    return status;
}


int32_t AppViss_SetRfeConfig(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status = FVID2_SOK;
    AppViss_Cfg        *vissCfg = NULL;
    Rfe_Control         rfeCtrl;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    vissCfg = tPrms->testCfg[hidx]->vissCfg;

    if (NULL != vissCfg->lPwlCfg)
    {
        /* PWL for Long Input */
        rfeCtrl.module  = RFE_MODULE_PWL1;
        rfeCtrl.pwl1Cfg = vissCfg->lPwlCfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->sPwlCfg)
    {
        /* PWL for Short Input */
        rfeCtrl.module  = RFE_MODULE_PWL2;
        rfeCtrl.pwl2Cfg = vissCfg->sPwlCfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->vsPwlCfg)
    {
        /* PWL for Very Short Input */
        rfeCtrl.module  = RFE_MODULE_PWL3;
        rfeCtrl.pwl3Cfg = vissCfg->vsPwlCfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->lLutCfg)
    {
        /* PWL Lut for Long Input */
        rfeCtrl.module          = RFE_MODULE_DECOMP_LUT1;
        rfeCtrl.decomp1Cfg      = vissCfg->lLutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->sLutCfg)
    {
        /* PWL Lut for Short Input */
        rfeCtrl.module          = RFE_MODULE_DECOMP_LUT2;
        rfeCtrl.decomp2Cfg      = vissCfg->sLutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->vsLutCfg)
    {
        /* PWL Lut for Very Short Input */
        rfeCtrl.module          = RFE_MODULE_DECOMP_LUT3;
        rfeCtrl.decomp3Cfg      = vissCfg->vsLutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->wdr1Cfg)
    {
        /* WDR Merge 1 block configuration */
        rfeCtrl.module       = RFE_MODULE_WDR_MERGE_MA1;
        rfeCtrl.wdrMergeMa1  = vissCfg->wdr1Cfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->wdr2Cfg)
    {
        rfeCtrl.module       = RFE_MODULE_WDR_MERGE_MA2;
        rfeCtrl.wdrMergeMa2  = vissCfg->wdr2Cfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->comp20To16LutCfg)
    {
        /* Set Companding Lut to convert from 20 to 16bits */
        rfeCtrl.module       = RFE_MODULE_COMP_LUT;
        rfeCtrl.compCfg      = vissCfg->comp20To16LutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->dpcOtf)
    {
        rfeCtrl.module       = RFE_MODULE_DPC_OTF;
        rfeCtrl.dpcOtfCfg    = vissCfg->dpcOtf;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->dpcLut)
    {
        rfeCtrl.module       = RFE_MODULE_DPC_LUT;
        rfeCtrl.dpcLutCfg    = vissCfg->dpcLut;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->lscCfg)
    {
        rfeCtrl.module      = RFE_MODULE_LSC;
        rfeCtrl.lscConfig   = vissCfg->lscCfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->wbCfg)
    {
        rfeCtrl.module       = RFE_MODULE_GAIN_OFST;
        rfeCtrl.wbConfig     = vissCfg->wbCfg;
        status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
            (void *)&rfeCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    return (status);
}

int32_t AppViss_SetFcpConfig(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status = FVID2_SOK;
    Fcp_Control         fcpCtrl;
    AppViss_Cfg        *vissCfg = NULL;
    Vhwa_M2mVissParams *vissPrms = NULL;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    vissCfg = tPrms->testCfg[hidx]->vissCfg;
    vissPrms = &tPrms->testCfg[hidx]->vissPrms;

    if (NULL != vissCfg->comp16To12LutCfg)
    {
        fcpCtrl.module = FCP_MODULE_COMPANDING;
        fcpCtrl.inComp = vissCfg->comp16To12LutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->cfaCfg)
    {
        fcpCtrl.module          = FCP_MODULE_CFA;
        fcpCtrl.cfa             = vissCfg->cfaCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->ccm)
    {
        fcpCtrl.module      = FCP_MODULE_CCM;
        fcpCtrl.ccm         = vissCfg->ccm;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->gamma)
    {
        fcpCtrl.module = FCP_MODULE_GAMMA;
        fcpCtrl.gamma  = vissCfg->gamma;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->rgb2Hsv)
    {
        fcpCtrl.module          = FCP_MODULE_RGB2HSV;
        fcpCtrl.rgb2Hsv         = vissCfg->rgb2Hsv;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->rgb2yuv)
    {
        fcpCtrl.module          = FCP_MODULE_RGB2YUV;
        fcpCtrl.rgb2Yuv         = vissCfg->rgb2yuv;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->yuvSatLutCfg)
    {
        fcpCtrl.module                  = FCP_MODULE_YUV_SAT_LUT;
        fcpCtrl.yuvSatLut               = vissCfg->yuvSatLutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->histCfg)
    {
        fcpCtrl.module                  = FCP_MODULE_HISTOGRAM;
        fcpCtrl.hist                    = vissCfg->histCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }
#if defined (IP_VERSION_VPAC_V3) || defined (IP_VERSION_VPAC_V4)
    if (NULL != vissCfg->comp24To12LutCfg)
    {
        fcpCtrl.module = FCP_MODULE_CFA_COMPANDING;
        fcpCtrl.cLutComp = vissCfg->comp24To12LutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->decomp16To24LutCfg)
    {
        fcpCtrl.module = FCP_MODULE_DECOMPANDING;
        fcpCtrl.dLutComp = vissCfg->decomp16To24LutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }
#endif
    if (NULL != vissCfg->eeCfg)
    {
        if (0 != (VHWA_M2M_VISS_EE_ON_LUMA12 & vissPrms->edgeEnhancerMode))
        {
            vissCfg->eeCfg->bypassY12 = FALSE;
            vissCfg->eeCfg->bypassY8 = TRUE;
            vissCfg->eeCfg->eeForY12OrY8 = 0u;
            vissCfg->eeCfg->leftShift = 0u;
            vissCfg->eeCfg->rightShift = 0u;
        }
        else if (0 != (VHWA_M2M_VISS_EE_ON_LUMA8 & vissPrms->edgeEnhancerMode))
        {
            vissCfg->eeCfg->bypassY8 = FALSE;
            vissCfg->eeCfg->bypassY12 = TRUE;
            vissCfg->eeCfg->eeForY12OrY8 = 1u;
            vissCfg->eeCfg->leftShift = 2u;
            vissCfg->eeCfg->rightShift = 2u;
        }
        else
        {
            vissCfg->eeCfg->bypassY12 = TRUE;
            vissCfg->eeCfg->bypassY8 = TRUE;
        }

        fcpCtrl.module              = FCP_MODULE_EE;
        fcpCtrl.eeCfg               = vissCfg->eeCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    return (status);
}

#if defined (IP_VERSION_VPAC_V3)
int32_t AppViss_SetFcp2Config(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status = FVID2_SOK;
    Fcp_Control         fcpCtrl;
    AppViss_Cfg        *vissCfg = NULL;
    Vhwa_M2mVissParams *vissPrms = NULL;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    vissCfg = tPrms->testCfg[hidx]->vissCfg;
    vissPrms = &tPrms->testCfg[hidx]->vissPrms;

    if (NULL != vissCfg->fcp2Comp16To12LutCfg)
    {
        fcpCtrl.module = FCP_MODULE_COMPANDING;
        fcpCtrl.inComp = vissCfg->fcp2Comp16To12LutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2CfaCfg)
    {
        fcpCtrl.module          = FCP_MODULE_CFA;
        fcpCtrl.cfa             = vissCfg->fcp2CfaCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2Comp24To12LutCfg)
    {
        fcpCtrl.module = FCP_MODULE_CFA_COMPANDING;
        fcpCtrl.cLutComp = vissCfg->fcp2Comp24To12LutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2Decomp16To24LutCfg)
    {
        fcpCtrl.module = FCP_MODULE_DECOMPANDING;
        fcpCtrl.dLutComp = vissCfg->fcp2Decomp16To24LutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2Ccm)
    {
        fcpCtrl.module      = FCP_MODULE_CCM;
        fcpCtrl.ccm         = vissCfg->fcp2Ccm;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2Gamma)
    {
        fcpCtrl.module = FCP_MODULE_GAMMA;
        fcpCtrl.gamma  = vissCfg->fcp2Gamma;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2Rgb2Hsv)
    {
        fcpCtrl.module          = FCP_MODULE_RGB2HSV;
        fcpCtrl.rgb2Hsv         = vissCfg->fcp2Rgb2Hsv;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2Rgb2yuv)
    {
        fcpCtrl.module          = FCP_MODULE_RGB2YUV;
        fcpCtrl.rgb2Yuv         = vissCfg->fcp2Rgb2yuv;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2YuvSatLutCfg)
    {
        fcpCtrl.module                  = FCP_MODULE_YUV_SAT_LUT;
        fcpCtrl.yuvSatLut               = vissCfg->fcp2YuvSatLutCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2HistCfg)
    {
        fcpCtrl.module                  = FCP_MODULE_HISTOGRAM;
        fcpCtrl.hist                    = vissCfg->fcp2HistCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    if (NULL != vissCfg->fcp2EeCfg)
    {
        if (0 != (VHWA_M2M_VISS_EE_ON_MV_LUMA12 & vissPrms->edgeEnhancerMode))
        {
            vissCfg->fcp2EeCfg->bypassY12 = FALSE;
            vissCfg->fcp2EeCfg->bypassY8 = TRUE;
            vissCfg->fcp2EeCfg->eeForY12OrY8 = 0u;
        }
        else if (0 != (VHWA_M2M_VISS_EE_ON_MV_LUMA8 & vissPrms->edgeEnhancerMode))
        {
            vissCfg->fcp2EeCfg->bypassY8 = FALSE;
            vissCfg->fcp2EeCfg->bypassY12 = TRUE;
            vissCfg->fcp2EeCfg->eeForY12OrY8 = 1u;
            vissCfg->fcp2EeCfg->leftShift = 2u;
            vissCfg->fcp2EeCfg->rightShift = 2u;
        }
        else
        {
            vissCfg->fcp2EeCfg->bypassY12 = TRUE;
            vissCfg->fcp2EeCfg->bypassY8 = TRUE;
        }

        fcpCtrl.module              = FCP_MODULE_EE;
        fcpCtrl.eeCfg               = vissCfg->fcp2EeCfg;
        status = Fvid2_control(tObj->handle, IOCTL_FCP2_SET_CONFIG,
            (void *)&fcpCtrl, NULL);
        if (FVID2_SOK != status)
        {
            return (status);
        }
    }

    return (status);
}
#endif

int32_t AppViss_SetGlbceConfig(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status = FVID2_SOK;
    AppViss_Cfg        *vissCfg = NULL;
    Vhwa_M2mVissParams *vissPrms = NULL;
    Glbce_Control       glbceCtrl;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    vissCfg = tPrms->testCfg[hidx]->vissCfg;
    vissPrms = &tPrms->testCfg[hidx]->vissPrms;

    if (TRUE == vissPrms->enableGlbce)
    {
        if (NULL != vissCfg->glbceCfg)
        {
            glbceCtrl.module = GLBCE_MODULE_GLBCE;
            glbceCtrl.glbceCfg = vissCfg->glbceCfg;
            status = Fvid2_control(tObj->handle, IOCTL_GLBCE_SET_CONFIG,
                (void *)&glbceCtrl, NULL);
            if (FVID2_SOK != status)
            {
                return (status);
            }
        }

        if (NULL != vissCfg->fwdPrcpCfg)
        {
            glbceCtrl.module = GLBCE_MODULE_FWD_PERCEPT;
            glbceCtrl.fwdPrcptCfg = vissCfg->fwdPrcpCfg;
            status = Fvid2_control(tObj->handle, IOCTL_GLBCE_SET_CONFIG,
                (void *)&glbceCtrl, NULL);
            if (FVID2_SOK != status)
            {
                return (status);
            }
        }

        if (NULL != vissCfg->revPrcpCfg)
        {
            glbceCtrl.module = GLBCE_MODULE_REV_PERCEPT;
            glbceCtrl.revPrcptCfg = vissCfg->revPrcpCfg;
            status = Fvid2_control(tObj->handle, IOCTL_GLBCE_SET_CONFIG,
                (void *)&glbceCtrl, NULL);
            if (FVID2_SOK != status)
            {
                return (status);
            }
        }
    }

    return (status);
}

int32_t AppViss_SetNsf4Config(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status = FVID2_SOK;
    AppViss_Cfg        *vissCfg = NULL;
    Vhwa_M2mVissParams *vissPrms = NULL;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    vissCfg = tPrms->testCfg[hidx]->vissCfg;
    vissPrms = &tPrms->testCfg[hidx]->vissPrms;

    if ((TRUE == vissPrms->enableNsf4) && (NULL != vissCfg->nsf4Cfg))
    {
        status = Fvid2_control(tObj->handle, IOCTL_NSF4_SET_CONFIG,
            (void *)vissCfg->nsf4Cfg, NULL);
    }

    return (status);
}

#if defined (IP_VERSION_VPAC_V3) || defined (IP_VERSION_VPAC_V4)
int32_t AppViss_SetCacConfig(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status = FVID2_SOK;
    AppViss_Cfg        *vissCfg = NULL;
    Vhwa_M2mVissParams *vissPrms = NULL;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    vissCfg = tPrms->testCfg[hidx]->vissCfg;
    vissPrms = &tPrms->testCfg[hidx]->vissPrms;

    if ((TRUE == vissPrms->enableCac) && (NULL != vissCfg->cacCfg))
    {
        status = Fvid2_control(tObj->handle, IOCTL_CAC_SET_CONFIG,
            (void *)vissCfg->cacCfg, NULL);
    }

    return (status);
}
#endif

#if defined (IP_VERSION_VPAC_V4)
int32_t AppViss_SetPcidParams(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];
    AppViss_TestConfig *tCfg = NULL;
    Vhwa_M2mVissParams *vissPrms = NULL;

    vissPrms = &tPrms->testCfg[hidx]->vissPrms;

    tCfg = tPrms->testCfg[hidx];

    if (TRUE == vissPrms->enablePcid)
    {
        status = Fvid2_control(tObj->handle, IOCTL_PCID_SET_CONFIG,
                                    (void *)tCfg->pPcidCfg, NULL);
    }
    else
    {
        status = FVID2_EFAIL;
    }
    return (status);
}
#endif

int32_t AppViss_SetH3aConfig(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status = FVID2_SOK;
    Rfe_Control         rfeCtrl;
    AppViss_Cfg        *vissCfg = NULL;
    Vhwa_M2mVissParams *vissPrms = NULL;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    vissCfg = tPrms->testCfg[hidx]->vissCfg;
    vissPrms = &tPrms->testCfg[hidx]->vissPrms;

    if ((uint32_t)TRUE == vissPrms->outPrms[VHWA_M2M_VISS_OUT_H3A_IDX].enable)
    {
        if (NULL != vissCfg->rfeH3aInCfg)
        {
            /* H3A Input Selection and Lut configuration */
            rfeCtrl.module   = RFE_MODULE_H3A;
            rfeCtrl.h3aInCfg = vissCfg->rfeH3aInCfg;

            status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
                (void *)&rfeCtrl, NULL);
            if (FVID2_SOK != status)
            {
                return (status);
            }
        }

        if (NULL != vissCfg->h3aLutCfg)
        {
            /* H3A Input Selection and Lut configuration */
            rfeCtrl.module   = RFE_MODULE_H3A_LUT;
            rfeCtrl.h3aLutCfg = vissCfg->h3aLutCfg;

            status = Fvid2_control(tObj->handle, IOCTL_RFE_SET_CONFIG,
                (void *)&rfeCtrl, NULL);
            if (FVID2_SOK != status)
            {
                return (status);
            }
        }

        if (NULL != vissCfg->h3aCfg)
        {
            status = Fvid2_control(tObj->handle, IOCTL_H3A_SET_CONFIG,
                (void *)vissCfg->h3aCfg, NULL);
        }
    }

    return (status);
}

int32_t AppViss_AllocBuffers(AppViss_TestParams *tPrms, uint32_t hidx,
    uint64_t srcBuf, uint32_t *inFrameSize,
    uint64_t dstBuf, uint32_t *outFrameSize)
{
    uint32_t                cnt;
    uint32_t                numIns;
    uint32_t                chromaOffset = 0;
    uint32_t                frameEnd = 0;
    AppViss_Cfg            *vissCfg = NULL;
    Vhwa_M2mVissParams     *vissPrms = NULL;
    Fvid2_Format           *outFmt = NULL;
    Fvid2_Format           *inFmt = NULL;
    AppViss_TestObject     *tObj = &gAppVissTestObject[hidx];

    vissCfg = tPrms->testCfg[hidx]->vissCfg;
    vissPrms = &tPrms->testCfg[hidx]->vissPrms;

    if (VHWA_M2M_VISS_MODE_SINGLE_FRAME_INPUT == vissPrms->inputMode)
    {
        numIns = 1;
    }
    else if (VHWA_M2M_VISS_MODE_TWO_FRAME_MERGE == vissPrms->inputMode)
    {
        numIns = 2;
    }
    else
    {
        numIns = 3;
    }

    inFmt    = &vissPrms->inFmt;
    frameEnd = inFmt->pitch[0] * inFmt->height;

    #ifdef VHWA_RUN_FROM_MSMC
    frameEnd = 16*1024 + 16;
    #endif

    for (cnt = 0u; cnt < numIns; cnt ++)
    {
        tObj->inFrm[cnt].addr[0U] = srcBuf;

        /* Move Buffer Index */
        srcBuf += frameEnd;
        *inFrameSize += frameEnd;

        DebugP_log (" VISS: Input%d: 0x%llx\n", cnt,
            tObj->inFrm[cnt].addr[0U]);
    }

    for (cnt = 0u; cnt < VHWA_M2M_VISS_MAX_OUTPUTS; cnt ++)
    {
        if (FALSE == vissPrms->outPrms[cnt].enable)
        {
            continue;
        }

        outFmt = &vissPrms->outPrms[cnt].fmt;

        chromaOffset = 0u;
        switch (outFmt->dataFormat)
        {
            case FVID2_DF_YUV422I_UYVY:
            case FVID2_DF_YUV422I_YUYV:
                frameEnd = outFmt->pitch[0] * outFmt->height;
                break;
            case FVID2_DF_RGB24_888_PLANAR:
                chromaOffset = outFmt->pitch[0] * outFmt->height;
                frameEnd = chromaOffset * 3;
                break;
            case FVID2_DF_GREY:
            case FVID2_DF_SATURATION:
                switch (outFmt->ccsFormat)
                {
                    case FVID2_CCSF_BITS8_PACKED:
                    case FVID2_CCSF_BITS8_UNPACKED16:
                    case FVID2_CCSF_BITS12_PACKED:
                    case FVID2_CCSF_BITS12_UNPACKED16:
                        frameEnd = (outFmt->pitch[0] * outFmt->height);
                        break;
                    default:
                        DebugP_log(
                            "Error FVID2_DF_GREY/SATUR : outCcsf =  0x%x \n",
                            outFmt->ccsFormat);
                        return FVID2_EFAIL;
                }
                break;

            case FVID2_DF_YUV420SP_UV:
                switch (outFmt->ccsFormat)
                {
                    case FVID2_CCSF_BITS12_PACKED:
                    case FVID2_CCSF_BITS12_UNPACKED16_MSB_ALIGNED:
                    case FVID2_CCSF_BITS12_UNPACKED16:
                    case FVID2_CCSF_BITS8_PACKED:
                    case FVID2_CCSF_BITS8_UNPACKED16:
                    case FVID2_CCSF_BITS16_PACKED:
                        chromaOffset = outFmt->pitch[0] * outFmt->height;
                        frameEnd = ((outFmt->pitch[0] * outFmt->height) * 3) / 2;
                        break;
                    default:
                        DebugP_log(
                            "Error FVID2_DF_YUV420SP_UV : outCcsf =  0x%x \n",
                            outFmt->ccsFormat);
                        return FVID2_EFAIL;
                }
                break;
#if defined (IP_VERSION_VPAC_V3) || defined (IP_VERSION_VPAC_V4)
            case FVID2_DF_YUV422SP_UV:
                switch (outFmt->ccsFormat)
                {
                    case FVID2_CCSF_BITS12_PACKED:
                    case FVID2_CCSF_BITS12_UNPACKED16_MSB_ALIGNED:
                    case FVID2_CCSF_BITS12_UNPACKED16:
                    case FVID2_CCSF_BITS8_PACKED:
                    case FVID2_CCSF_BITS8_UNPACKED16:
                    case FVID2_CCSF_BITS16_PACKED:
                        chromaOffset = outFmt->pitch[0] * outFmt->height;
                        frameEnd = outFmt->pitch[0] * outFmt->height * 2u;
                        break;
                    default:
                        DebugP_log(
                            "Error FVID2_DF_YUV422SP_UV : outCcsf =  0x%x \n",
                            outFmt->ccsFormat);
                        return FVID2_EFAIL;
                }
                break;
            case FVID2_DF_RAW08:
            case FVID2_DF_RAW12:
            case FVID2_DF_RAW16:
            case FVID2_DF_LUMA_ONLY:
                switch (outFmt->ccsFormat)
                {
                    case FVID2_CCSF_BITS12_PACKED:
                    case FVID2_CCSF_BITS12_UNPACKED16_MSB_ALIGNED:
                    case FVID2_CCSF_BITS12_UNPACKED16:
                    case FVID2_CCSF_BITS8_PACKED:
                    case FVID2_CCSF_BITS8_UNPACKED16:
                    case FVID2_CCSF_BITS16_PACKED:
                        chromaOffset = outFmt->pitch[0] * outFmt->height;
                        frameEnd = ((outFmt->pitch[0] * outFmt->height) * 3) / 2;
                        break;
                    default:
                        DebugP_log(
                            "Error FVID2_DF_LUMA_ONLY : outCcsf =  0x%x \n",
                            outFmt->ccsFormat);
                        return FVID2_EFAIL;
                }
                break;
            case FVID2_DF_RGI:
	            chromaOffset = 0;
                frameEnd = outFmt->pitch[0] * outFmt->height;
                break;
	        case FVID2_DF_BLUE:
  	            chromaOffset = 0;
                frameEnd = outFmt->pitch[0] * outFmt->height;
                break;
#endif
            case FVID2_DF_RAW:
                if (VHWA_M2M_VISS_OUT_H3A_IDX == cnt)
                {
                    uint32_t wins;

                    wins = (vissCfg->h3aCfg->aewbCfg.winCfg.horzCount *
                        vissCfg->h3aCfg->aewbCfg.winCfg.vertCount);

                    dstBuf += (wins * 32) + ((wins/8) *16);
                    *outFrameSize += (wins * 32) + ((wins/8) *16);
                    if (wins%8 != 0)
                    {
                        dstBuf += 16;
                        *outFrameSize += 16;
                    }
                }
                break;
            default:
                DebugP_log("Error : Unsupported format 0x%x \n",
                    outFmt->dataFormat);
                return FVID2_EFAIL;
        }

        tObj->outFrm[cnt].addr[0U] = dstBuf;
        tObj->outFrm[cnt].addr[1U] = (dstBuf + chromaOffset);
        tObj->outFrm[cnt].addr[2U] = (dstBuf + 2*chromaOffset);

        /* Move Buffer Index */
        dstBuf += frameEnd;
        *outFrameSize += frameEnd;

        DebugP_log(" VISS: Output%d:", cnt);
        DebugP_log(" 0x%x 0x%x 0x%x\n",
            (uint32_t)tObj->outFrm[cnt].addr[0U],
            (uint32_t)tObj->outFrm[cnt].addr[1U],
            (uint32_t)tObj->outFrm[cnt].addr[2U]);
    }

    return (FVID2_SOK);
}

void AppViss_PrepareRequest(AppViss_TestParams *tPrms, uint32_t hidx)
{
    uint32_t            cnt;
    Fvid2_FrameList    *inFrmList;
    Fvid2_FrameList    *outFrmList;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    inFrmList = &tObj->inFrmList;
    outFrmList = &tObj->outFrmList;

    for (cnt = 0u; cnt < VHWA_M2M_VISS_MAX_INPUTS; cnt ++)
    {
        /* Initialize VISS Input Frame List */
        inFrmList->frames[cnt] = &tObj->inFrm[cnt];
    }
    inFrmList->numFrames = VHWA_M2M_VISS_MAX_INPUTS;

    /* Initialize VISS Output Frame List */
    outFrmList->numFrames = VHWA_M2M_VISS_MAX_OUTPUTS;
    for (cnt = 0u; cnt < VHWA_M2M_VISS_MAX_OUTPUTS; cnt++)
    {
        outFrmList->frames[cnt] = &tObj->outFrm[cnt];
    }
}

int32_t AppViss_SubmitRequest(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t             status;
    Fvid2_FrameList    *inFrmList;
    Fvid2_FrameList    *outFrmList;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    inFrmList = &tObj->inFrmList;
    outFrmList = &tObj->outFrmList;

    /* Submit VISS Request*/
    status = Fvid2_processRequest(tObj->handle, inFrmList,
        outFrmList, FVID2_TIMEOUT_FOREVER);
    if (FVID2_SOK != status)
    {
        DebugP_log
            (" VISS: Fvid2_processRequest returned %x for VISS Handle # %d\n",
            status, hidx);
    }

    return (status);
}

int32_t AppViss_WaitForCompRequest(AppViss_TestParams *tPrms, uint32_t hidx)
{
    int32_t          status;
    Fvid2_FrameList *inFrmList;
    Fvid2_FrameList *outFrmList;
    AppViss_TestObject *tObj = &gAppVissTestObject[hidx];

    SemaphoreP_pend(&tObj->waitForProcessCmpl, SystemP_WAIT_FOREVER);

    inFrmList = &tObj->inFrmList;
    outFrmList = &tObj->outFrmList;

    status = Fvid2_getProcessedRequest(tObj->handle,
        inFrmList, outFrmList, 0);
    if (FVID2_SOK != status)
    {
        DebugP_log (" VISS: Failed VISS Handle Cnt %d; status = %x\n",
            hidx, status);
        return (status);
    }

    return (status);
}

void AppViss_SyncStart(AppViss_TestParams *tObj, uint32_t hidx)
{
    uint32_t status;
    AppViss_TestObject  *appObj = &gAppVissTestObject[hidx];

    status = Fvid2_control(appObj->handle,
                            IOCTL_VHWA_M2M_VISS_SYNC_START,
                            NULL, NULL);
    if(FVID2_SOK != status)
    {
        DebugP_log(" VISS Sync Start Failed \n");
    }
}

/* ========================================================================== */
/*                          Static Function Definitions                       */
/* ========================================================================== */

static int32_t VissApp_init()
{
    int32_t        status;
    uint32_t       instId;
    VHWA_Udma_InitPrms  udmaInitPrms;
    VHWA_Udma_DrvHandle drvHandle = &gVissAppUdmaDrvObj;

    status = Fvid2_init(NULL);
    if (FVID2_SOK != status)
    {
        DebugP_log(" main: FVID2_Init Failed !!!\r\n");
    }

    if (FVID2_SOK == status)
    {
        /* Initialize UDMA and get the handle, it will be used in both CRC layer,
           as well as in the driver */
        /* UDMA driver init */
        instId = VHWA_UDMA_INST_ID_MAIN_0;
        Vhwa_UdmaInitPrms_init(instId, &udmaInitPrms);
        status = Vhwa_Udma_init(drvHandle, &udmaInitPrms);
        if(UDMA_SOK != status)
        {
            DebugP_log("[Error] UDMA init failed!!\n");
            status = FVID2_EFAIL;
        }
    }

    status = AppViss_Init(drvHandle);

    return (status);
}

static int32_t AppViss_test(AppViss_TestParams *tPrms)
{
    int32_t     status;
    uint32_t    repCnt;
    uint32_t    hCnt;
    uint64_t    timeCount;
    uint64_t    perf;
    
    for(hCnt = 0U; hCnt < tPrms->numHandles; hCnt++)
    {
        status = AppViss_Create(tPrms, hCnt);
        if (FVID2_SOK != status)
        {
            DebugP_log (" Failed to create\n");
        }

        if ((uint32_t)TRUE != tPrms->chCfgOnEachIter)
        {
            status = AppViss_SetAllConfig(tPrms, hCnt);
            if (FVID2_SOK != status)
            {
                DebugP_log (" Failed to Set all Config\n");
            }
        }

        status = AppViss_AllocBuffers(tPrms, hCnt,
            gVissTestSrcBuf, &gVissTestSrcBufFreeIdx,
            gVissTestDestBuf, &gVissTestDstBufFreeIdx);
        if (FVID2_SOK != status)
        {
            DebugP_log (" Failed to Set all Config\n");
        }
    }

    if(tPrms->isPerformanceTest)
    {
        timeCount = ClockP_getTimeUsec();
    }
    
    for (repCnt = 0U; repCnt < tPrms->repeatCnt; repCnt ++)
    {
        for(hCnt = 0U; hCnt < tPrms->numHandles; hCnt++)
        {
            if ((uint32_t)TRUE == tPrms->chCfgOnEachIter)
            {
                status = AppViss_SetAllConfig(tPrms, hCnt);
                if (FVID2_SOK != status)
                {
                    DebugP_log(" SetAllConfig Failed \n");
                    status = FVID2_EFAIL;
                }
            }

            AppViss_PrepareRequest(tPrms, hCnt);

            status = AppViss_SubmitRequest(tPrms, hCnt);
            if (FVID2_SOK != status)
            {
                DebugP_log (" Failed to Submit Request\n");
            }

            status = AppViss_WaitForCompRequest(tPrms, hCnt);
            if (FVID2_SOK != status)
            {
                DebugP_log (" Failed to Get back Request\n");
            }
            else
            {
                DebugP_log (" Completed RepeatCnt = %d\n", repCnt);
            }
        }
    }
    if(tPrms->isPerformanceTest)
    {
        timeCount = ClockP_getTimeUsec() - timeCount;
        DebugP_log ("Performance:\n\t FrameCount: %d: Time in uSec: %d\n",
                    tPrms->repeatCnt, timeCount);

        perf = (uint64_t)tPrms->testCfg[0]->vissPrms.inFmt.width
                *(uint64_t)tPrms->testCfg[0]->vissPrms.inFmt.height
                *(uint64_t)tPrms->repeatCnt;
        DebugP_log("Width %d\n",(uint64_t)tPrms->testCfg[0]->vissPrms.inFmt.width);
        DebugP_log("Height %d\n",(uint64_t)tPrms->testCfg[0]->vissPrms.inFmt.height);

        DebugP_log ("\t MPix/s: %d.%d\n",
            (uint32_t)(perf/timeCount),
                (uint32_t)(((perf*(uint64_t)100)/timeCount)%100));
    }

    AppViss_Delete(tPrms, 0U);

    return (status);
}
