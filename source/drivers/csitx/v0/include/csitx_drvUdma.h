/*
 *  Copyright (c) Texas Instruments Incorporated 2020-25
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
 *  \file csitx_drvUdma.h
 *
 *  \brief CSITX Driver UDMA initialization and configuration APIs.
 */
/**
 *  \ingroup DRV_CSITX_MODULE
 *  \defgroup CSITX_UDMA_API CSITX UDMA Capture API
 *
 *  This modules define APIs to initialize and configure UDMA for capture.
 *  @{
 */

#ifndef CSITX_UDMA_H_
#define CSITX_UDMA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "csitx_drvPriv.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* PSIL Source Tag */
#define CSITX_DRV_PSI_SRC_TAG                         ((uint32_t)0x4)
/* PSIL Destination Tag */
#define CSITX_DRV_PSI_DEST_TAG                        ((uint32_t)0x8)

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
int32_t CsitxDrv_setDMACfgParams(CsitxDrv_ChObj *chObj);

int32_t CsitxDrv_setUdmaParams(CsitxDrv_CommonObj *txObj,
                               CsitxDrv_InstObj *instObj);

int32_t CsitxDrv_clearUdmaParams(CsitxDrv_InstObj *instObj);

int32_t CsitxDrv_udmaTxTrpdInit(Udma_ChHandle txChHandle,
                                uint8_t *pTrpdMem,
                                const uint32_t *destBuf,
                                const Csitx_ChCfg *chCfg,
                                uint32_t chIdx);

void CsitxDrv_udmaCQEventCb(Udma_EventHandle eventHandle,
                            uint32_t eventType,
                            void *appData);

void CsitxDrv_cacheWb(const void *addr, int32_t size);

void CsitxDrv_cacheInv(const void * addr, int32_t size);

uint8_t* CsitxDrv_getTrpdMemAddr(uint32_t chIdx, uint32_t qCnt);
/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CSITX_UDMA_H_ */

/* @} */
