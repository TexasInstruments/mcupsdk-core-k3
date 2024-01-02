/*
 *   Copyright (c) Texas Instruments Incorporated 2023
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
#include <sdl/include/am62px/sdlr_soc_baseaddress.h>
#include <pbist_test_func.h>
#include <drivers/hw_include/am62px/cslr_main_ctrl_mmr.h>
#include <drivers/hw_include/am62px/cslr_mcu_ctrl_mmr.h>
#include <drivers/hw_include/am62px/cslr_wkup_ctrl_mmr.h>
#include <drivers/sciclient/include/tisci/am62px/tisci_devices.h>
/* #define DEBUG */

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* Note the following are array indexes into the test config array */

#define PBIST_INSTANCE_MPU     					(0U)
#define PBIST_INSTANCE_ENCODE      				(1U)
#define PBIST_INSTANCE_PBIST1                   (2U)
#define PBIST_INSTANCE_WKUP_PBIST1              (3U)
#define PBIST_INSTANCE_PBIST_GPU                (4U)
#define PBIST_INSTANCE_MAIN  					(5U)
#define PBIST_INSTANCE_MCU 						(6U)

#define PBIST_MAX_INSTANCE                (PBIST_INSTANCE_MCU+1U)
#define PBIST_NUM_INSTANCE                (PBIST_INSTANCE_MAIN+1U)

#define PBIST_MAX_TIMEOUT_VALUE           (10000000u)

#define MPU_NUM_AUX_DEVICES               	5

#define RT_NUM_AUX_DEVICES               	15

#define GPU_NUM_AUX_DEVICES               	5

#define DM2_NUM_AUX_DEVICES               	6

#define DM1_NUM_AUX_DEVICES               	5

#define MAIN_NUM_AUX_DEVICES             	25

#define MCU_NUM_AUX_DEVICES               	2

#define CODEC_NUM_AUX_DEVICES				1

#define PBIST_NEG_TEST_PBIST_CFG_BASE    (SDL_PBIST0_BASE) //Need to update

#define APP_PBIST_TEST_NEG_INST          (PBIST_INSTANCE_MPU) //Need to update
#define APP_PCONFIG_TEST_INSTANCE        (PBIST_INSTANCE_MPU) //Need to update

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