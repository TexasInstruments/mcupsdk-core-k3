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
*  \file vhwa_viss_test_api.h
*
*  \brief VHWA VISS TEST API and struct definitions
*/
#ifndef VPAC_EX_VISS_TEST_API_H_
#define VPAC_EX_VISS_TEST_API_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>

#include <drivers/vhwa/include/vhwa_m2mViss.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_VISS_CRC_CHANNEL         (CRC_CHANNEL_1)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct
{
    Rfe_PwlConfig               *vsPwlCfg;
    Rfe_PwlConfig               *sPwlCfg;
    Rfe_PwlConfig               *lPwlCfg;
    Vhwa_LutConfig              *vsLutCfg;
    Vhwa_LutConfig              *sLutCfg;
    Vhwa_LutConfig              *lLutCfg;
    Rfe_WdrConfig               *wdr1Cfg;
    Rfe_WdrConfig               *wdr2Cfg;
    Vhwa_LutConfig              *comp20To16LutCfg;
    Rfe_DpcOtfConfig            *dpcOtf;
    Rfe_DpcLutConfig            *dpcLut;
    Rfe_LscConfig               *lscCfg;
    Rfe_GainOfstConfig          *wbCfg;
    Rfe_H3aInConfig             *rfeH3aInCfg;
    Vhwa_LutConfig              *h3aLutCfg;
    Vhwa_LutConfig              *comp16To12LutCfg;
    Fcp_CfaConfig               *cfaCfg;
    Fcp_CcmConfig               *ccm;
    Fcp_GammaConfig             *gamma;
    Fcp_Rgb2HsvConfig           *rgb2Hsv;
    Fcp_Rgb2YuvConfig           *rgb2yuv;
    Fcp_YuvSatLutConfig         *yuvSatLutCfg;
    Nsf4v_Config                *nsf4Cfg;
    Glbce_Config                *glbceCfg;
    Glbce_PerceptConfig         *fwdPrcpCfg;
    Glbce_PerceptConfig         *revPrcpCfg;
    H3a_Config                  *h3aCfg;
    Fcp_EeConfig                *eeCfg;
    Fcp_HistConfig              *histCfg;
    uint32_t                     isCrcAvail;
    uint64_t                     crcSign[VHWA_M2M_VISS_MAX_OUTPUTS];

#if defined (IP_VERSION_VPAC_V3) || defined (IP_VERSION_VPAC_V4)
    Fcp_comDecomLutConfig       *comp24To12LutCfg;
    Fcp_comDecomLutConfig       *decomp16To24LutCfg;
    /* FCP 2 Config */
    Vhwa_LutConfig              *fcp2Comp16To12LutCfg;
    Fcp_CfaConfig               *fcp2CfaCfg;
    Fcp_comDecomLutConfig       *fcp2Comp24To12LutCfg;
    Fcp_comDecomLutConfig       *fcp2Decomp16To24LutCfg;
    Fcp_CcmConfig               *fcp2Ccm;
    Fcp_GammaConfig             *fcp2Gamma;
    Fcp_Rgb2HsvConfig           *fcp2Rgb2Hsv;
    Fcp_Rgb2YuvConfig           *fcp2Rgb2yuv;
    Fcp_YuvSatLutConfig         *fcp2YuvSatLutCfg;
    Fcp_EeConfig                *fcp2EeCfg;
    Fcp_HistConfig              *fcp2HistCfg;
    /* CAC Config */
    Cac_Config                  *cacCfg;
#endif
} AppViss_Cfg;

typedef struct
{
    Vhwa_M2mVissParams          vissPrms;
    /**< VISS parameters */
    AppViss_Cfg                 *vissCfg;
    /**< Pointer to VISS configuration */
    #if defined (IP_VERSION_VPAC_V4)
    Pcid_Cfg                    *pPcidCfg;
    /**< PCID Configurations */
    #endif
} AppViss_TestConfig;

typedef struct
{
    Fvid2_Handle                handle;
    /**< FVID2 Driver Handle */
    Vhwa_M2mVissCreateArgs      createArgs;
    /**< FVID2 Create Arguments */
    Fvid2_Frame                 inFrm[VHWA_M2M_VISS_MAX_INPUTS];
    /**< Input Frames */
    Fvid2_Frame                 outFrm[VHWA_M2M_VISS_MAX_OUTPUTS];
    /**< Output Frames */
    Fvid2_CbParams              cbPrms;
    /**< Callback params */
    Fvid2_FrameList             inFrmList;
    /**< Input Frame List */
    Fvid2_FrameList             outFrmList;
    /**< Output Frame List */
    SemaphoreP_Object           waitForProcessCmpl;
    /**< Semaphore to wait for completion */
} AppViss_TestObject;

typedef struct
{
    char                    testName[100];
    /**< Test Name */
    uint32_t                numHandles;
    /**< Max Handles in this Test */
    uint32_t                repeatCnt;
    /**< Number of times to repeat this test */
    uint32_t                isPerformanceTest;
    /**< Flag to indicate if this is performance test */
    AppViss_TestConfig     *testCfg[VHWA_M2M_VISS_MAX_HANDLES];
    /**< Pointer to the Test Config */
    uint32_t                isEnableTest;
    /**< Flag to enable/disable Test */
    uint32_t                isSwitchGlbceCtx;
    /* GLBCE CTX Switch */
    uint32_t                chCfgOnEachIter;
    /**< Flag to change Config on each iteration */
} AppViss_TestParams;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t AppViss_Init(VHWA_Udma_DrvHandle udmaDrvHndl);
void AppViss_deInit(VHWA_Udma_DrvHandle udmaDrvHndl);
int32_t AppViss_Create(AppViss_TestParams *tPrms, uint32_t hidx);
void AppViss_Delete(AppViss_TestParams *tPrms, uint32_t hidx);
int32_t AppViss_SetAllConfig(AppViss_TestParams *tPrms, uint32_t hidx);
int32_t AppViss_SetParams(AppViss_TestParams *tPrms, uint32_t hidx);
int32_t AppViss_SetRfeConfig(AppViss_TestParams *tPrms, uint32_t hidx);
int32_t AppViss_SetFcpConfig(AppViss_TestParams *tPrms, uint32_t hidx);
int32_t AppViss_SetGlbceConfig(AppViss_TestParams *tPrms, uint32_t hidx);
int32_t AppViss_SetNsf4Config(AppViss_TestParams *tPrms, uint32_t hidx);
#if defined (IP_VERSION_VPAC_V3) || defined (IP_VERSION_VPAC_V4)
int32_t AppViss_SetCacConfig(AppViss_TestParams *tPrms, uint32_t hidx);
#endif
int32_t AppViss_SetH3aConfig(AppViss_TestParams *tPrms, uint32_t hidx);
#if defined (IP_VERSION_VPAC_V4)
int32_t AppViss_SetPcidParams(AppViss_TestParams *tPrms, uint32_t hidx);
#endif
int32_t AppViss_AllocBuffers(AppViss_TestParams *tPrms, uint32_t hidx,
                             uint64_t srcBuf, uint32_t *inFrameSize,
                             uint64_t dstBuf, uint32_t *outFrameSize);
void AppViss_PrepareRequest(AppViss_TestParams *tObj, uint32_t hIdx);
int32_t AppViss_SubmitRequest(AppViss_TestParams *tObj, uint32_t hIdx);
int32_t AppViss_WaitForCompRequest(AppViss_TestParams *tObj, uint32_t hIdx);
void AppViss_SyncStart(AppViss_TestParams *tObj, uint32_t hidx);
int32_t AppVissFrameComplCb(Fvid2_Handle handle, void *appData);

#endif /*VPAC_EX_VISS_TEST_API_H_*/
