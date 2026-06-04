/**
 *  Copyright (C) 2026 Texas Instruments Incorporated.
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
 *  \file     core_r5_test.h
 *
 *  \brief    This file contains test code defines for R5 core.
 *
 *  \details  R5 Core register read/write and configuration tests
 **/

#if !defined(CSL_CORE_R5_TEST_H)
#define CSL_CORE_R5_TEST_H

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unity.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/MpuP_armv7.h>
#include <kernel/dpl/CpuIdP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/*===========================================================================*/
/*                         Declarations                                      */
/*===========================================================================*/

/* Define the test interface */
typedef struct coreR5Test_s
{
    int32_t (*testFunction)(void);      /* The code that runs the test */
    char                *name;          /* The test name */
} coreR5Test_t;

/* Define the MPU regions */
typedef struct coreR5TestMpuRegion_s
{
    void *    base;          /* MPU Region Base Address value */
    uint32_t    size;          /* Region Size and Enable Bits (and Subregion En) */
    MpuP_RegionAttrs    permissions;   /* The MPU region access control */
} coreR5TestMpuRegion_t;

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/

#define CORE_R5_APP_TEST_NOT_RUN        (-(int32_t) (2))
#define CORE_R5_APP_TEST_FAILED         (-(int32_t) (1))
#define CORE_R5_APP_TEST_PASS           ( (int32_t) (0))

/*===========================================================================*/
/*                         External function declarations                    */
/*===========================================================================*/

extern int32_t core_r5_pmuTest(void);
extern int32_t core_r5_cacheTest();
extern int32_t core_r5_hardErrTest(void);
extern int32_t core_r5_Test_mpu_init(void);
void run_multi_threaded_tests(void *args);
void *TestMpu_getExecBase(void);

#endif /* CSL_CORE_R5_TEST_H */

