/*
 *   Copyright (c) Texas Instruments Incorporated 2025-2026
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
 *
 */

#ifndef ECC_MAIN_H
#define ECC_MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_ecc.h>
#include <sdl/sdl_esm.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define SDL_APP_TEST_NOT_RUN        (-(int32_t) (2))
#define SDL_APP_TEST_FAILED         (-(int32_t) (1))
#define SDL_APP_TEST_PASS           ( (int32_t) (0))

#define  ECC_FUNC_TEST_ID         (0U)
#define  ECC_ERROR_TEST_ID        (1U)
#define  ECC_TOTAL_NUM_TESTS      (2U)

/* Captures ESM/ECC callback data for logging outside ISR context */
typedef struct {
    uint32_t invoked;           /* Callback invocation count */
    uint32_t esmInst;           /* ESM instance */
    uint32_t esmIntrType;       /* ESM interrupt type (PLS/LVL) */
    uint32_t grpChannel;        /* ESM group/channel */
    uint32_t index;             /* ESM index within group */
    uint32_t intSrc;            /* ESM event source */
    bool eccInfoValid;          /* True when the ECC fields below are valid */
    bool eccFatalPath;          /* True when handled via the CSI/DSI FATAL path */
    uint32_t eccMemType;        /* ECC memory type */
    uint32_t eccIntrSrc;        /* SEC/DED source */
    uint32_t eccMemSubType;     /* RAM ID */
    uint32_t bitErrCnt;         /* Natural error count */
    uint32_t injectBitErrCnt;   /* Injected error count */
    uint64_t bitErrorOffset;    /* Error bit offset */
    uint32_t bitErrorGroup;     /* Error group */
    int32_t ackRetVal;          /* SDL_ECC_ackIntr result */
} SDL_ECC_ESMCallbackInfo_t;

extern volatile SDL_ECC_ESMCallbackInfo_t esmEccInfo;

/* Logs esmEccInfo from normal, non-ISR context */
extern void ECC_reportEsmEccInfo(void);

/* ========================================================================== */
/*                 External Function Declarations                             */
/* ========================================================================== */

extern int32_t ECC_funcTest(void);
extern int32_t ECC_errTest(void);

#ifdef __cplusplus
}
#endif

#endif /* ECC_MAIN_H */

/* Nothing past this point */
