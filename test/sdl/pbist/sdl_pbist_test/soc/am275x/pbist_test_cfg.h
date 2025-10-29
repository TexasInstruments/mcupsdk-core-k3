/*
 *   Copyright (c) Texas Instruments Incorporated 2024-25
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
#include <sdl/include/am275x/sdlr_soc_baseaddress.h>
#include <pbist_test_func.h>
#include <drivers/hw_include/am275x/cslr_main_ctrl_mmr.h>
#include <drivers/hw_include/am275x/cslr_mcu_ctrl_mmr.h>
#include <drivers/hw_include/am275x/cslr_wkup_ctrl_mmr.h>
#include <drivers/sciclient/include/tisci/am275x/tisci_devices.h>
/* #define DEBUG */

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define PBIST_POST_CORE_MAX   (1U)

/* Note the following are array indexes into the test config array */

#if defined (R5FSS0)    // Cannot test Pulsar_0 while running on R5FSS0
#define PBIST_INST_MAIN_PULSAR_1            (0U)
#define PBIST_INST_C7X_0                    (1U)
#define PBIST_INST_C7X_1                    (2U)
#define PBIST_INST_DM_2  			        (3U)
#define PBIST_INST_MAIN_IP     	            (4U)
#endif

#if defined (R5FSS1)    // Cannot test Pulsar_1 while running on R5FSS1
#define PBIST_INST_MAIN_PULSAR_0            (0U)
#define PBIST_INST_C7X_0                    (1U)
#define PBIST_INST_C7X_1                    (2U)
#define PBIST_INST_DM_2  			        (3U)
#define PBIST_INST_MAIN_IP     	            (4U)
#endif

#define PBIST_MAX_INSTANCE                (PBIST_INST_MAIN_IP+1U)
#define PBIST_NUM_INSTANCE                (PBIST_INST_MAIN_IP+1U)

#define PBIST_MAX_TIMEOUT_VALUE           (10000000u)

#define Main_NUM_AUX_DEVICES               	13

#define P0_NUM_AUX_DEVICES               	1

#define P1_NUM_AUX_DEVICES               	1

#define C70_NUM_AUX_DEVICES               	2

#define C71_NUM_AUX_DEVICES               	2

#define PBIST_NEG_TEST_PBIST_CFG_BASE    (SDL_PBIST0_BASE)

#define APP_PBIST_TEST_NEG_INST          (PBIST_INST_MAIN_IP)
#define APP_PCONFIG_TEST_INSTANCE        (PBIST_INST_MAIN_IP)
#define APP_PBIST_SBL_TEST_INST          (PBIST_INST_MAIN_IP)

extern PBIST_TestHandle_t PBIST_TestHandleArray[PBIST_MAX_INSTANCE+1];

/* HW POST run status definitions */
#define PBIST_POST_COMPLETED_SUCCESS_STR      "SDL_PBIST_POST_COMPLETED_SUCCESS"
#define PBIST_POST_COMPLETED_FAILURE_STR      "SDL_PBIST_POST_COMPLETED_FAILURE"
#define PBIST_POST_ATTEMPTED_TIMEOUT_STR      "SDL_PBIST_POST_TIMEOUT"
#define PBIST_POST_NOT_RUN_STR                "SDL_PBIST_POST_NOT_RUN"

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void PBIST_printPostStatus(SDL_PBIST_postResult *result);

#ifdef __cplusplus
}
#endif

#endif /* PBIST_TEST_CFG_H */
/* Nothing past this point */