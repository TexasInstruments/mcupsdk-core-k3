/*
 *  Copyright (C) 2024-2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file     sdl_soc_lbist.c
 *
 *  \brief    This file contains LBIST test configuration
 *
 *  \details  LBIST Test Configuration
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_lbist.h>
#include <sdl/lbist/sdl_lbist_priv.h>
#include <sdl/include/j722s/sdlr_mcu_ctrl_mmr.h>
#include <sdl/include/j722s/sdlr_main_ctrl_mmr.h>
#include <sdl/include/j722s/sdlr_soc_baseaddress.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* Lbist Parameters */
#define LBIST_DC_DEF         (0x3U)
#define LBIST_DIVIDE_RATIO   (0x01U)
#define LBIST_RESET_PC_DEF   (0x0FU)
#define LBIST_SET_PC_DEF     (0x00U)
#define LBIST_SCAN_PC_DEF    (0x08U)
#define LBIST_VPAC_DMPAC_SCAN_PC_DEF    (0x04U)
#define LBIST_PRPG_DEF       (0x1FFFFFFFFFFFFFU)

/* PC Definitions */
#define LBIST_WKUP_STATIC_PC_DEF        (0X400U)
#define LBIST_VPAC_STATIC_PC_DEF        (0XFF0U)
#define LBIST_DMPAC_STATIC_PC_DEF       (0X620U)

/*
* LBIST expected MISR's (using parameters above)
*/
#define WKUP_MISR_EXP_VAL           (0x6D240CC7U)
#define VPAC0_MISR_EXP_VAL          (0x51b7ca92U)
#define DMPAC_MISR_EXP_VAL          (0xa4ea22e1U)


#define SDL_MCU_WKUP0_LBIST_BASE (SDL_MCU_CTRL_MMR0_CFG0_BASE + SDL_MCU_CTRL_MMR_CFG0_MCU_R5FSS0_LBIST_CTRL)
#define SDL_MAIN_VPAC0_LBIST_BASE (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_VPAC0_LBIST_CTRL)
#define SDL_MAIN_DMPAC_LBIST_BASE (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_DMPAC_LBIST_CTRL)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

SDL_lbistInstInfo SDL_LBIST_InstInfoArray[SDL_LBIST_NUM_INSTANCES] =
{
    /* WKUP */
    {
        .pLBISTRegs             = (SDL_lbistRegs *)(SDL_MCU_WKUP0_LBIST_BASE),
        .pLBISTSig              = NULL,
        .expectedMISR           = WKUP_MISR_EXP_VAL,        /* Expected signature for main R5 0*/
        .handler                = NULL,                     /* LBIST event handler */
        .doneFlag               = LBIST_NOT_DONE,           /* Initialize done flag */
        .LBISTConfig = {
            .dc_def        = LBIST_DC_DEF,
            .divide_ratio  = LBIST_DIVIDE_RATIO,
            .static_pc_def = LBIST_WKUP_STATIC_PC_DEF,
            .set_pc_def    = LBIST_SET_PC_DEF,
            .reset_pc_def  = LBIST_RESET_PC_DEF,
            .scan_pc_def   = LBIST_SCAN_PC_DEF,
            .prpg_def      = LBIST_PRPG_DEF,
        },
    },
    /* VPAC */
    {
        .pLBISTRegs             = (SDL_lbistRegs *)(SDL_MAIN_VPAC0_LBIST_BASE),
        .pLBISTSig              = NULL,
        .expectedMISR           = VPAC0_MISR_EXP_VAL,       /* Expected signature for main R5 0*/
        .handler                = NULL,                     /* LBIST event handler */
        .doneFlag               = LBIST_NOT_DONE,           /* Initialize done flag */
        .LBISTConfig = {
            .dc_def        = LBIST_DC_DEF,
            .divide_ratio  = LBIST_DIVIDE_RATIO,
            .static_pc_def = LBIST_VPAC_STATIC_PC_DEF,
            .set_pc_def    = LBIST_SET_PC_DEF,
            .reset_pc_def  = LBIST_RESET_PC_DEF,
            .scan_pc_def   = LBIST_VPAC_DMPAC_SCAN_PC_DEF,
            .prpg_def      = LBIST_PRPG_DEF,
        },
    },
    /* DMPAC */
    {
        .pLBISTRegs             = (SDL_lbistRegs *)(SDL_MAIN_DMPAC_LBIST_BASE),
        .pLBISTSig              = NULL,
        .expectedMISR           = DMPAC_MISR_EXP_VAL,       /* Expected signature for main R5 0*/
        .handler                = NULL,                     /* LBIST event handler */
        .doneFlag               = LBIST_NOT_DONE,           /* Initialize done flag */
        .LBISTConfig = {
            .dc_def        = LBIST_DC_DEF,
            .divide_ratio  = LBIST_DIVIDE_RATIO,
            .static_pc_def = LBIST_DMPAC_STATIC_PC_DEF,
            .set_pc_def    = LBIST_SET_PC_DEF,
            .reset_pc_def  = LBIST_RESET_PC_DEF,
            .scan_pc_def   = LBIST_VPAC_DMPAC_SCAN_PC_DEF,
            .prpg_def      = LBIST_PRPG_DEF,
        },
    },

};

/* ========================================================================== */
/*                            Function Definitions                            */
/* ========================================================================== */

/**
 * \brief Returns a pointer to the SDL LBIST Instance structure at the provided index.
 *
 * \param index The index of the SDL_lbistInstInfo structure to retrieve.
 *
 * \return A pointer to the SDL_lbistInstInfo structure at the specified index.
 */
SDL_lbistInstInfo* SDL_LBIST_getInstInfo(uint32_t index)
{
    SDL_lbistInstInfo *handle;
    SDL_lbistInstInfo *pInfo = NULL;

    handle = SDL_LBIST_InstInfoArray;
    pInfo = &handle[index];

    return pInfo;
}

/**
 * \brief LBIST event handler function.
 *
 * This function is the event handler for LBIST. It checks if the LBIST done flag
 * is set and if so, sets the doneFlag of the provided instance to LBIST_DONE.
 * It also stops the LBIST by calling the SDL_LBIST_stop function.
 *
 * \param pInstInfo Pointer to the LBIST instance information.
 *
 * \return None
 */
void SDL_LBIST_eventHandler(SDL_lbistInstInfo *pInstInfo)
{
    int32_t status;
    bool isLBISTDone = FALSE;
    SDL_lbistRegs *pLBISTRegs;

    if (pInstInfo != NULL)
    {
        pLBISTRegs = pInstInfo->pLBISTRegs;
        /* Check if the LBIST done flag is set */
        status = SDL_LBIST_isDone(pLBISTRegs, &isLBISTDone);
        if ((status == SDL_PASS) && (isLBISTDone == TRUE))
        {
            pInstInfo->doneFlag = LBIST_DONE;
            /* Need to pull run down to low to clear the done interrupt */
            (void)SDL_LBIST_stop( pLBISTRegs );
        }
    }
    return;

}
/* Nothing past this point */
