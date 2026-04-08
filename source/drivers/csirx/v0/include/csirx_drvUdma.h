/*
 *  Copyright (c) Texas Instruments Incorporated 2018-25
 *  All rights reserved.
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
 *  \file csirx_drvUdma.h
 *
 *  \brief CSIRX Driver UDMA initialization and configuration APIs.
 */
/**
 *  \ingroup DRV_CSIRX_MODULE
 *  \defgroup CSIRX_UDMA_API UDMA Capture API
 *
 *  This modules define APIs to initialize and configure UDMA for capture.
 *  @{
 */

#ifndef CSIRX_UDMA_H_
#define CSIRX_UDMA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "csirx_drvPriv.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CSIRX_DRV_UDMA_MASTER_EVNT_INIT_DONE        ((uint32_t)0x1U)
#define CSIRX_DRV_UDMA_MASTER_EVNT_INIT_PENDING     ((uint32_t)0x0U)

/* PSIL Source Tag */
#define CSIRX_DRV_PSI_SRC_TAG                         ((uint32_t)0x0)
/* PSIL Destination Tag */
#define CSIRX_DRV_PSI_DEST_TAG                        ((uint32_t)0x1)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
int32_t CsirxDrv_getDMACfgParams(CsirxDrv_ChObj *chObj);

int32_t CsirxDrv_setChUdmaParams(CsirxDrv_ChObj *chObj);

int32_t CsirxDrv_clearUdmaParams(CsirxDrv_ChObj *chObj);

int32_t CsirxDrv_udmaRxTrpdInit(Udma_ChHandle rxChHandle,
                                uint8_t *pTrpdMem,
                                const uint32_t *destBuf,
                                const Csirx_ChCfg *chCfg,
                                uint32_t chIdx);

void CsirxDrv_udmaCQEventCb(Udma_EventHandle eventHandle,
                            uint32_t eventType,
                            void *appData);

void CsirxDrv_cacheWb(const void *addr, uint32_t size);

void CsirxDrv_cacheInv(const void * addr, uint32_t size);

uint8_t* CsirxDrv_getTrpdMemAddr(CsirxDrv_ChObj *chObj, uint32_t qCnt);

/**
 *  \brief This function maps UDMA error status to corresponding FVID2 error status.
 *
 *  \param udmaErr   UDMA Error status
 *  \return FVID2 Error status
 *
 */
int32_t CsirxDrv_udmaToFvid2ErrorMap(int32_t udmaErr);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSIRX_UDMA_H_ */

/** @} */
