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
*  \file vhwa_ldc_api.h
*
*  \brief VHWA LDC API and struct definitions
*/
#ifndef VPAC_EX_LDC_API_H_
#define VPAC_EX_LDC_API_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>
#include <drivers/vhwa/include/vhwa_m2mLdc.h>


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
* Application test parameters
*/
#if defined (IP_VERSION_VPAC_V4)
#define APP_LDC_LUT_ADDR_2MP       (0xB1200000u)
#define APP_LDC_LUT_ADDR_1MP       (0xB1400000u)
#define APP_LDC_LUT_ADDR_HKMC      (0xB1600000u)
#else
#define APP_LDC_LUT_ADDR_2MP       (VHWA_EXAMPLE_MEM_START_ADDR + 0xA800000u)
#define APP_LDC_LUT_ADDR_1MP       (VHWA_EXAMPLE_MEM_START_ADDR + 0xA900000u)
#define APP_LDC_LUT_ADDR_HKMC      (VHWA_EXAMPLE_MEM_START_ADDR + 0xAA00000u)
#endif

#define APP_LDC_MAX_HANDLES         (4U)
#define APP_LDC_CRC_CHANNEL         (CRC_CHANNEL_1)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint32_t inWidth, inHeight, inPitch, inFmt, inCcsf;
    uint32_t enableOutput[LDC_MAX_OUTPUT];
    struct {
        uint32_t outWidth, outHeight, outPitch, outFmt, outCcsf;
    } fmt[LDC_MAX_OUTPUT];
    uint32_t enableBackmapping, pixPad, blockWidth, blockHeight;
    uint32_t lutDs;
    uint32_t lutWidth, lutHeight, lutPitch;
    uint64_t lutPtr;
    uint32_t lumaInterpolation;
    uint32_t isAffineEn;
    int32_t affineCoeff[8];
    uint32_t isLsePsa;
    uint32_t psaSign[4u];
    uint32_t isMultiRegMode;
    Ldc_RegionConfig regCfg;
    uint32_t isCrcAvail;   /* MCRC */
    uint64_t crcSign[LDC_MAX_OUTPUT];  /* MCRC */
    uint32_t isLutEnable;
    /* Optional 2nd Channel Input prms */
    struct {
        uint32_t enable, inPitch, inCcsf;
    }inIndFrm;
    struct {
        uint32_t indChOutPitch, indChOutCcsf, indCh2OutPitch;
        /* indCh2OutPitch is valid only in case of 3 Plane (Y+Y+Y) output */
    } indChFmt[LDC_MAX_OUTPUT];
} AppLdc_TestConfig;

typedef struct
{
    uint32_t                enableBwLimit;
    uint32_t                cycleCnt, tokenCnt;
    Fvid2_Handle            handle;
    /**< FVID2 Driver Handle */
    Vhwa_M2mLdcCreateArgs   createArgs;
    /**< FVID2 Create Arguments */
    Ldc_Config              ldcCfg;
    /**< LDC Configuration */
    Fvid2_Frame             inFrm;
    /**< Input Frames */
    Fvid2_Frame             outFrm[LDC_MAX_OUTPUT];
    /**< Output Frames */
    Fvid2_CbParams          cbPrms;
    /**< Callback params */
    Fvid2_FrameList         inFrmList;
    /**< Input Frame List */
    Fvid2_FrameList         outFrmList;
    /**< Output Frame List */
    SemaphoreP_Object       waitForProcessCmpl;
    /**< Semaphore to wait for completion */
} AppLdc_TestObject;

typedef struct
{
    char                    testName[50];
    /**< Name of the Test */
    uint32_t                numHandles;
    /**< Max Handles in this Test */
    uint32_t                repeatCnt;
    /**< Number of times to repeat this test */
    uint32_t                isPerformanceTest;
    /**< Flag to indicate if this is performance test */
    AppLdc_TestConfig      *testCfg[APP_LDC_MAX_HANDLES];
    /**< Pointer to the Test Config */
    uint32_t                isEnableTest;
    /**< Flag to Bypass Test */
} LdcApp_TestParams;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void AppLdcMain(void *args);
int32_t AppLdc_Init(Udma_DrvHandle udmaDrvHndl);
int32_t AppLdc_SetParams(LdcApp_TestParams *tObj, uint32_t hidx);
int32_t AppLdc_AllocBuffers(LdcApp_TestParams *tObj, uint32_t hidx,
                            uint64_t ldcTestSrcBuf, uint32_t *inFrameSize,
                            uint64_t ldcTestDstBuf, uint32_t *outFrameSize);
int32_t AppLdc_Create(LdcApp_TestParams *tObj, uint32_t hidx);
void AppLdc_Delete(LdcApp_TestParams *tObj, uint32_t hidx);
void AppLdc_PrepareRequest(LdcApp_TestParams *tObj, uint32_t hidx);
int32_t AppLdc_SubmitRequest(LdcApp_TestParams *tObj, uint32_t hidx);
int32_t AppLdc_WaitForComplRequest(LdcApp_TestParams *tObj, uint32_t hidx);
int32_t AppLdc_CrcInit(Udma_DrvHandle udmaDrvHndl);
int32_t AppLdc_CrcDeinit(Udma_DrvHandle udmaDrvHndl);
static int32_t AppLdc_CompareCrc(LdcApp_TestParams *tObj, uint32_t hIdx);
void AppLdc_SyncStart(LdcApp_TestParams *tObj, uint32_t hidx);
int32_t AppLdcFrameComplCb(Fvid2_Handle handle, void *appData);
void AppLdcErrorCb(Fvid2_Handle handle, uint32_t errEvents, void *appData);

#endif /*VPAC_EX_LDC_API_H_*/
