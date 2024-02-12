/**
 *   Copyright (c) Texas Instruments Incorporated 2023
 *   All rights reserved.
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
*  \file vhwa_msc_api.h
*
*  \brief VHWA MSC API and struct definitions
*/
#ifndef VPAC_EX_MSC_API_H_
#define VPAC_EX_MSC_API_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
* Application test parameters
*/

#define APP_MSC_MAX_HANDLES          (4u)

/** \brief Number of times to perform the memcpy operation */
#define APP_MSC_APP_LOOP_CNT         (1000U)

#if defined (IP_VERSION_VPAC_V1) || defined (IP_VERSION_VPAC_V3)
#define APP_MAX_IN_IMG_WIDTH        (1920U)
#endif
#if defined (IP_VERSION_VPAC_V4)
#define APP_MAX_IN_IMG_WIDTH        (1920U)
#endif
#define APP_IN_IMG_CCSF             (FVID2_CCSF_BITS16_PACKED)
#define APP_MAX_IN_IMG_BUFF_DEPTH   (6)

#if defined (IP_VERSION_VPAC_V1) || defined (IP_VERSION_VPAC_V3)
#define APP_MAX_OUT_IMG_WIDTH        (1920U)
#endif
#if defined (IP_VERSION_VPAC_V4)
#define APP_MAX_OUT_IMG_WIDTH        (1920U)
#endif
#define APP_OUT_IMG_CCSF             (FVID2_CCSF_BITS12_UNPACKED16)
#define APP_MAX_OUT_IMG_BUFF_DEPTH   (2)

#define APP_MSC_CRC_CHANNEL         (CRC_CHANNEL_1)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/*
* Application test parameters
*/

typedef struct
{
    uint32_t loopBack;
    uint32_t mscThreadId;

    /* Input Frame Parameter */
    struct {
        uint32_t inWidth, inHeight, inPitch, inDataFmt, inCcsf, skipInputLine;
        uint32_t tapSel;
    } inFrm;

    /* output Frame Parameter */
    struct {
        uint32_t outWidth, outHeight, outPitch, roiWidth, roiHeight;
        uint32_t outDataFmt, outCcsf;
    } outFrm[MSC_MAX_OUTPUT];

    /* Configuration for each instance */
    struct {
        uint32_t                        enable;
        Fvid2_PosConfig                 inPos;
        uint32_t                        horzAccInit;
        uint32_t                        vertAccInit;
        uint32_t                        filtMode;
        uint32_t                        phaseMode;
        uint32_t                        hsSpCoeffSel;
        uint32_t                        vsSpCoeffSel;
        uint32_t                        hsMpCoeffSel;
        uint32_t                        vsMpCoeffSel;
        uint32_t                        coeffShift;
        uint32_t                        isSignedData;
        uint32_t                        isEnableFiltSatMode;
    } mscCfgPrms[MSC_MAX_OUTPUT];
    uint32_t            isLsePsaAvail;
    uint32_t            psaSign[2][10];
    uint32_t            isCrcAvail;
    uint64_t            crcSign[10];
#if defined(IP_VERSION_VPAC_V3) || defined (IP_VERSION_VPAC_V4)
    /* Optional 2nd Channel Input prms */
    struct {
        uint32_t enable, inPitch, inCcsf;
    }inSecFrm;
#endif
} App_MscTestCfg;

typedef struct
{
    uint32_t        enableBwLimit;
    uint32_t        cycleCnt, tokenCnt;
    Fvid2_Handle    handle;
    /**< FVID2 Driver Handle */
    Vhwa_M2mMscCreatePrms createArgs;
    /**< FVID2 Create Arguments */
    Fvid2_Frame     inFrm;
    /**< Input Frame for each Handle */
    Fvid2_Frame     outFrm[MSC_MAX_OUTPUT];
    /**< Output Frame for each Handle */
    Fvid2_CbParams      cbPrms;
    /**< Callback parameters */
    Fvid2_FrameList         inFrmList;
    /**< Input Frame List */
    Fvid2_FrameList         outFrmList;
    /**< Output Frame List */
    Vhwa_M2mMscParams    mscPrms[APP_MSC_MAX_HANDLES];
    /**< MSC Parameters */
    SemaphoreP_Object       waitForProcessCmpl;
    /**< Semaphore to wait for completion */

} App_MscTestObj;

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
    App_MscTestCfg          *testCfg[APP_MSC_MAX_HANDLES];
    /**< Pointer to the Test Config */
    uint32_t                isEnableTest;
    /**< Flag to Bypass Test */
} App_MscTestParams;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t AppMsc_Init(VHWA_Udma_DrvHandle drvHandle);
int32_t AppMsc_DeInit(void);
int32_t AppMsc_Create(App_MscTestParams *tObj, uint32_t hndlIdx);
void AppMsc_Delete(App_MscTestParams *tObj, uint32_t hidx);
int32_t AppMsc_SetCoeff(App_MscTestParams *tObj, uint32_t hndlIdx,
                        Msc_Coeff * coefTbl);
int32_t AppMsc_SetParams(App_MscTestParams *tObj, uint32_t hndlIdx);
int32_t AppMsc_AllocBuffers(App_MscTestParams *tObj, uint32_t hndlIdx,
                            uint64_t srcBuf, uint32_t *srcBufSize, uint32_t srcOffset,
                            uint64_t dstBuf, uint32_t *dstBufSize, uint32_t dstOffset);
void AppMsc_PrepareRequest(App_MscTestParams *tObj, uint32_t hIdx);
int32_t AppMsc_SubmitRequest(App_MscTestParams *tObj, uint32_t hIdx);
int32_t AppMsc_WaitForComplRequest(App_MscTestParams *tObj,
                                   uint32_t hIdx);
int32_t AppMsc_CrcInit(VHWA_Udma_DrvHandle udmaDrvHndl);
int32_t AppMsc_CrcDeinit(VHWA_Udma_DrvHandle udmaDrvHndl);
static int32_t AppMsc_CompareCrc(App_MscTestParams *tObj, uint32_t hIdx);
void AppMsc_SyncStart(App_MscTestParams *tObj, uint32_t hidx);
int32_t AppMscFrameComplCb0(Fvid2_Handle handle, void *appData);
int32_t AppMscFrameComplCb1(Fvid2_Handle handle, void *appData);
void AppMscErrorCb(Fvid2_Handle handle, uint32_t errEvents, void *appData);

#endif /*VPAC_EX_MSC_API_H_*/
