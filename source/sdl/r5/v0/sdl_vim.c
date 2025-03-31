/*
 *   Copyright (C) Texas Instruments Incorporated 2024-25
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

#include <stdint.h>
#include "sdl_vim.h"
#include <sdl/include/sdl_types.h>
#include <sdl/include/sdlr.h>

#define         SDL_MCU_ARMSS_VIM_NULL_ADDR           ((void *) 0 )

/**
 * Design: PROC_SDL-2126
 */
void SDL_VIM_setDedVectorAddr( SDL_vimRegs *pRegs, uint32_t dedVectorAddr )
{
    void       *pChkRegs = (void *) pRegs;

    if (pChkRegs != SDL_MCU_ARMSS_VIM_NULL_ADDR)
    {
        SDL_REG32_WR( &pRegs->DEDVEC, (dedVectorAddr & SDL_VIM_DEDVEC_ADDR_MASK) );
    }
}

/**
 * Design: PROC_SDL-2127
 */
int32_t SDL_VIM_getDedVectorAddr( SDL_vimRegs *pRegs, uint32_t *pDedVectorAddr )
{
    int32_t     retVal = SDL_PASS;
    uint32_t    dedVecAddr;
    void       *pChkDedVecAddr = (void *) pDedVectorAddr;
    void       *pChkRegs = (void *) pRegs;
    if ( (pChkRegs == SDL_MCU_ARMSS_VIM_NULL_ADDR) ||
         (pChkDedVecAddr == SDL_MCU_ARMSS_VIM_NULL_ADDR))
    {
        retVal = SDL_EFAIL;
    }

    if (retVal == SDL_PASS)
    {
        dedVecAddr = SDL_REG32_RD( &pRegs->DEDVEC);
       *pDedVectorAddr = dedVecAddr;
    }
    return (retVal);
}


/* nothing past this point */
