/*
 *   Copyright (c) Texas Instruments Incorporated 2025
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
 *  \file     ecc_func.h
 *
 *  \brief    This file contains ECC main test defines.
 *
 *  \details  ECC unit tests
 **/
#ifndef ECC_FUNC_H
#define ECC_FUNC_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define SDL_R5F_ECC_AGGR_NUM_RAMS                                           (21)    /* Number of RAM IDs*/

SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
{
    .esmErrorConfig = {0u, 8u}, /* Self test error config */
    .enableBitmap = { 0x00000000u, 0x00000000u, 0x00000000u,0x00000000u,
                      0x00000000u, 0x00000000u, 0x00180000u,0x00000000u,
                    },
     /**< All events enable: except clkstop events for unused clocks */
    .priorityBitmap = { 0x00000000u, 0x00000000u, 0x00000000u,0x00000000u,
                        0x00000000u, 0x00000000u, 0x00180000u,0x00000000u,
                      },
    /**< All events high priority: except clkstop events for unused clocks */
    .errorpinBitmap = { 0x00000000u, 0x00000000u, 0x00000000u,0x00000000u,
                        0x00000000u, 0x00000000u, 0x00180000u,0x00000000u,
                      },
    /**< All events high priority: except clkstop for unused clocks
     *   and selftest error events */
};

static SDL_ECC_MemSubType ECC_Test_SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_subMemTypeList[SDL_R5F_ECC_AGGR_NUM_RAMS] =
{
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_ITAG_RAM0_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_ITAG_RAM1_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_ITAG_RAM2_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_ITAG_RAM3_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_IDATA_BANK0_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_IDATA_BANK1_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_IDATA_BANK2_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_IDATA_BANK3_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DTAG_RAM0_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DTAG_RAM1_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DTAG_RAM2_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DTAG_RAM3_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DDIRTY_RAM_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DDATA_RAM0_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DDATA_RAM1_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DDATA_RAM2_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DDATA_RAM3_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DDATA_RAM4_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DDATA_RAM5_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DDATA_RAM6_RAM_ID,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_DDATA_RAM7_RAM_ID,
};

static SDL_ECC_InitConfig_t ECC_Test_SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_initConfig =
{
    .numRams = SDL_R5F_ECC_AGGR_NUM_RAMS,
    /**< Number of Rams ECC is enabled */
    .pMemSubTypeList = &(ECC_Test_SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_subMemTypeList[0]),
    /**< Sub type list */
};

typedef struct
{
    SDL_ECC_InitConfig_t *initConfig;
    SDL_ECC_MemType eccMemType;
    char *aggrName;
    SDL_ESM_Inst instance;
    SDL_ESM_config *pConfig;
} SDL_Test_EccConfig;

static SDL_Test_EccConfig ECC_Test_config =
{
    &ECC_Test_SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_initConfig,
    SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR,
    "SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR",
    SDL_ESM_INST_MAIN_ESM0,
    &ECC_Test_esmInitConfig_MAIN
};

#ifdef __cplusplus
}
#endif

#endif /* ECC_FUNC_H */

/* Nothing past this point */
