/**
 *  Copyright (C) 2023-25 Texas Instruments Incorporated.
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

 /**
 *  \file     test_core_r5_cache.c
 *
 *  \brief    This file contains cache test code for R5 core.
 *
 *  \details  Cache APIs tests
 **/

/* =========================================================================== */
/*                            Include files                                    */
/* =========================================================================== */

#include "core_r5_test.h"
#include <kernel/dpl/CacheP.h>
#include <kernel/nortos/dpl/r5/CacheP_armv7r.h>
#include <kernel/nortos/dpl/r5/UtilsP_armv7r.h>

/* =========================================================================== */
/*                            Declarations                                     */
/* =========================================================================== */

/* None */

/* =========================================================================== */
/*                            Macros                                           */
/* =========================================================================== */

/* None */

/* =========================================================================== */
/*                            Internal function declarations                   */
/* =========================================================================== */

/* None */

/* =========================================================================== */
/*                            Global Variables                                 */
/* =========================================================================== */

uint32_t cacheTestBuf[256];

/* =========================================================================== */
/*                      Local Function definitions                             */
/* =========================================================================== */

/* None */

/* =========================================================================== */
/*                           Test Function definitions                         */
/* =========================================================================== */

/* This function tests the Cache APIs */
int32_t core_r5_cacheTest(void)
{
    /* Declarations of variables */
    int32_t    testResult = CORE_R5_APP_TEST_PASS;
    uint32_t   icacheLineSize;

    CacheP_disable(CacheP_TYPE_L1P);
    CacheP_disable(CacheP_TYPE_L1D);
    CacheP_enable(CacheP_TYPE_L1P);
    CacheP_enable(CacheP_TYPE_L1D);

    CacheP_invL1pAll();
    CacheP_invL1dAll();

    CacheP_wb((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_L1P);
    CacheP_wb((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_L1D);
    CacheP_wbInv((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_L1P);
    CacheP_wbInv((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_L1D);
    CacheP_inv((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_L1P);
    CacheP_inv((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_L1D);

    CacheP_InvalidateIcacheMva((uint32_t)core_r5_cacheTest);
    CacheP_InvalidateDcacheSetWay(0U, 0U);
    CacheP_CleanDcacheSetWay(0U, 0U);
    CacheP_CleanInvalidateDcacheSetWay(0U, 0U);

    CacheP_DisableEcc();
    CacheP_EnableAxiAccess();

    UtilsP_Dsb();

    icacheLineSize = CacheP_GetIcacheLineSize();

    DebugP_log("I-Cache Line Size is: ");
    DebugP_log("0x%x \n", icacheLineSize);
    DebugP_log(" \n\r ");

   return (testResult);
}
