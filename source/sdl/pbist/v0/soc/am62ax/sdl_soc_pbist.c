/**
 * @file  sdl_soc_pbist.c
 *
 * @brief
 *  SDL implementation file for the SoC-specific pbist implementations.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2023, Texas Instruments, Inc.
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
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_pbist.h>
#include <sdl/pbist/sdl_pbist_priv.h>
#include <sdl/include/am62ax/sdlr_soc_baseaddress.h>
#include <sdl/include/am62ax/sdlr_intr_esm0.h>
#include <sdl/esm/v0/esm.h>
#include <sdl/sdl_esm.h>
#include <sdl/esm/sdl_esm_priv.h>

#define ECR_CLR_VAL                     (1U)

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

/*
 * Note: the order for the below must match order of SDL_PBIST_inst
 */

static SDL_pbistInstInfo SDL_PBIST_InstInfoArray[SDL_PBIST_NUM_INSTANCES] =
{
    /*A53 mpu COMPUTE_CLUSTER0_PBIST */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_COMPUTE_CLUSTER0_PBIST_BASE,

        .numPBISTRuns        = SDL_COMPUTE_CLUSTER0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_COMPUTE_CLUSTER0_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_COMPUTE_CLUSTER0_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,  /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },

        .PBISTNegConfigRun =
        {
            .CA0   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_COMPUTE_CLUSTER0_FAIL_INSERTION_TEST_VECTOR_RAMT
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_COMPUTE_CLUSTER0_PBIST_0_DFT_PBIST_CPU_0,
        .doneFlag               = PBIST_NOT_DONE
    },

    /* CODEC Instance PBIST3 */
    {
        .PBISTRegsHiAddress  = 0x0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST3_BASE,
        .numPBISTRuns        = SDL_PBIST3_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST3_ALGO_BITMAP_0,  /* Choose recommended Algo bitmap */
                .memoryGroupsBitMap = SDL_PBIST3_MEM_BITMAP_0,   /* Choose recommended mem bitmap  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = SDL_PBIST3_ALGO_BITMAP_1,
                .memoryGroupsBitMap = SDL_PBIST3_MEM_BITMAP_1,
                .scrambleValue      = 0xFEDCBA9876543210U,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_RAMT
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST3_K3_PBIST_8C28P_4BIT_WRAP__DFT_PBIST_CPU_0,
        .doneFlag               = PBIST_NOT_DONE
    },

    /* C7X256V0 Instance C7X256V0_PBIST */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_C7X256V0_PBIST_BASE,
        .numPBISTRuns        = SDL_C7X256V0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_C7X256V0_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_C7X256V0_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = SDL_C7X256V0_ALGO_BITMAP_1,
                .memoryGroupsBitMap = SDL_C7X256V0_MEM_BITMAP_1,
                .scrambleValue      = 0xFEDCBA9876543210U,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_C7X256V0_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_C7X256V0_CLEC_DFT_PBIST_CPU_0,
        .doneFlag               = PBIST_NOT_DONE
    },

        /* VPAC Instance VPAC0_PBIST */
	{
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_VPAC0_MEM_BASE,
        .numPBISTRuns        = SDL_VPAC0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_VPAC0_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_VPAC0_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = SDL_VPAC0_ALGO_BITMAP_1,
                .memoryGroupsBitMap = SDL_VPAC0_MEM_BITMAP_1,
                .scrambleValue      = 0xFEDCBA9876543210U,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_VPAC0_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_VPAC0_COMMON_0_K3_PBIST_8C28P_4BIT_WRAP__DFT_PBIST_CPU_0,
        .doneFlag               = PBIST_NOT_DONE
    },

		/* MAIN Instance PBIST0 */
	{
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST0_BASE,
        .numPBISTRuns        = SDL_PBIST0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST0_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_PBIST0_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = SDL_PBIST0_ALGO_BITMAP_1,
                .memoryGroupsBitMap = SDL_PBIST0_MEM_BITMAP_1,
                .scrambleValue      = 0xFEDCBA9876543210U,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST0_DFT_PBIST_CPU_0,
        .doneFlag               = PBIST_NOT_DONE
    },

    /* MCU_PULSER Instance MCU_PBIST0(WKUP_R5F) */
	{
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_MCU_PBIST0_BASE,
        .numPBISTRuns        = SDL_WKUP_R5FSS0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_WKUP_R5FSS0_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_WKUP_R5FSS0_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_WKUP_R5FSS0_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_MCU_PBIST0_DFT_PBIST_CPU_0 ,
        .doneFlag               = PBIST_NOT_DONE
    },

};

SDL_pbistInstInfo * SDL_PBIST_getInstInfo(SDL_PBIST_inst instance)
{
    SDL_pbistInstInfo *pInfo = NULL;

    if ((uint32_t)instance < SDL_PBIST_NUM_INSTANCES)
    {
        pInfo = &SDL_PBIST_InstInfoArray[instance];
    }

    return pInfo;
}


void SDL_PBIST_eventHandler( uint32_t instanceId)
{

    SDL_PBIST_InstInfoArray[instanceId].doneFlag = PBIST_DONE;

    return;
}

void SDL_PBIST_checkDone(SDL_pbistInstInfo *pInfo)
{
    uint32_t intStatus;
    uint32_t localAddr;

    if (pInfo != NULL)
    {
        (void)SDL_ESM_getBaseAddr(pInfo->esmInst, &localAddr);
        (void)SDL_ESM_getIntrStatusRAW(localAddr, pInfo->esmEventNumber, &intStatus);
        if (intStatus == (uint32_t)0x1)
        {
            pInfo->doneFlag = PBIST_DONE;
            (void)SDL_ESM_clearIntrStatus(localAddr, pInfo->esmEventNumber);
        }
    }

    return;
}