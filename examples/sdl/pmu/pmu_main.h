/*
 * Copyright (c) 2024-25 Texas Instruments Incorporated
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
 *  \file     pmu_main.h
 *
 *  \brief    This file contains test code defines for R5 core.
 *
 *  \details  R5 Core register read/write and configuration tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sdl/include/sdl_types.h>
#include <sdl/include/sdlr.h>
#include <sdl/include/hw_types.h>
#include "ti_board_open_close.h"
#include <sdl/r5/v0/sdl_arm_r5_pmu.h>

#if defined (SOC_J722S)
#include <sdl/include/j722s/sdlr_soc.h>
#endif

#if !defined(SDL_PMU_TEST_H)
#define SDL_PMU_TEST_H

#ifdef __cplusplus
extern "C" {
#endif


/*===========================================================================*/
/*                         Declarations                                      */
/*===========================================================================*/

/* Define the test interface */
typedef struct sdlPmuTest_s
{
    int32_t  (*testFunction)(void);   /* The code that runs the test */
    char      *name;                  /* The test name */
    int32_t    testStatus;            /* Test Status */
} sdlPmuTest_t;

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/

#define SDL_APP_TEST_NOT_RUN        (-(int32_t) (2))
#define SDL_APP_TEST_FAILED         (-(int32_t) (1))
#define SDL_APP_TEST_PASS           ( (int32_t) (0))

/*===========================================================================*/
/*                         Internal function declarations                    */
/*===========================================================================*/

/*===========================================================================*/
/*                         External function declarations                    */
/*===========================================================================*/

extern int32_t sdl_core_r5_pmuTest(void);
extern void sdlApp_print(const char * str);

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif /* SDL_PMU_TEST_H */
/* Nothing past this point */
