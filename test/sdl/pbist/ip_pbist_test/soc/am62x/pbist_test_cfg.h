/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     pbist_test_cfg.h
 *
 *  \brief    This file contains PBIST test configuration
 *
 *  \details  PBIST Test configuration
 **/
#ifndef PBIST_TEST_CFG_H
#define PBIST_TEST_CFG_H

#ifdef __cplusplus
extern "C"
{
#endif
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <sdl/include/am62x/sdlr_soc_baseaddress.h>
#include <pbist_test_func.h>
#include <drivers/hw_include/am62x/cslr_main_ctrl_mmr.h>
#include <drivers/hw_include/am62x/cslr_mcu_ctrl_mmr.h>
/* #define DEBUG */

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* Note the following are array indexes into the test config array */

#define PBIST_INSTANCE_GPU      	(0U)
#define PBIST_INSTANCE_MPU      	(1U)
#define PBIST_INSTANCE_MAIN        	(2U)
#define PBIST_INSTANCE_DM  			(3U)


#define PBIST_MAX_INSTANCE                (PBIST_INSTANCE_MAIN+1U)
#define PBIST_NUM_INSTANCE                (PBIST_INSTANCE_MAIN+1U)

#define PBIST_MAX_TIMEOUT_VALUE           (100000000u)

#define MPU_NUM_AUX_DEVICES               	7

#define MAIN_NUM_AUX_DEVICES             	12

#define GPU_NUM_AUX_DEVICES               	2

#define PBIST_NEG_TEST_PBIST_CFG_BASE    (SDL_PBIST0_BASE)

#define APP_PBIST_TEST_NEG_INST          (PBIST_INSTANCE_MPU)
#define APP_PCONFIG_TEST_INSTANCE        (PBIST_INSTANCE_MAIN)

extern PBIST_TestHandle_t PBIST_TestHandleArray[PBIST_MAX_INSTANCE+1];

#ifdef __cplusplus
}
#endif

#endif /* PBIST_TEST_CFG_H */
/* Nothing past this point */