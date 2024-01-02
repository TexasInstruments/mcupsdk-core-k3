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
 */


#include <stdio.h>
#include <kernel/dpl/DebugP.h>
#include <sdl/include/sdl_types.h>
#include <sdl/dpl/sdl_dpl.h>
#include <sdl/sdl_lbist.h>
#include <sdl/sdl_pbist.h>

#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "dpl_interface.h"

/* MCU LBIST/PBIST Instance */
#if defined (SOC_AM62X)
#define LBIST_INSTANCE      (LBIST_MAIN_M4F)
#define PBIST_INSTANCE      (SDL_PBIST_INST_MCU)
#elif defined (SOC_AM62AX)
#define LBIST_INSTANCE      (LBIST_MCU_R5F)
#define PBIST_INSTANCE      (SDL_PBIST_INST_MCU)
#endif

void bist_check_result_main(void *args)
{
    int32_t  status = SystemP_SUCCESS;
    int32_t  ret;
    bool result = false;

    SDL_dplInit();

    ret = SDL_LBIST_checkResult(LBIST_INSTANCE, &result);
    if ((ret != SDL_PASS) || (result == false))
    {
        DebugP_log("LBIST check failed!!\r\n");
        status = SystemP_FAILURE;
    }

    ret = SDL_SBL_PBIST_checkResult(PBIST_INSTANCE);
    if (ret != SDL_PASS)
    {
        DebugP_log("PBIST check failed!!\r\n");
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

}

