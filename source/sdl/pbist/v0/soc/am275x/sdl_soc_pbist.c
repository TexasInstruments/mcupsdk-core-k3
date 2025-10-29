/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

#include <stdint.h>
#include <sdl/include/sdl_types.h>
#include <sdl/include/hw_types.h>
#include <sdl/sdl_pbist.h>
#include <sdl/pbist/sdl_pbist_priv.h>
#include <sdl/include/am275x/sdlr_soc_baseaddress.h>
#include <sdl/include/am275x/sdlr_wkup_ctrl_mmr.h>
#include <sdl/include/am275x/sdlr_intr_esm0.h>
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
    /* Main Pulsar 0 */
	{
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST1_BASE,
        .numPBISTRuns        = SDL_PBIST1_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST1_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_PBIST1_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST1_DFT_PBIST_CPU_0,
        .doneFlag               = PBIST_NOT_DONE
    },

    /* Main Pulsar 1 */
	{
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *) SDL_PBIST2_BASE,
        .numPBISTRuns        = SDL_PBIST2_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST2_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_PBIST2_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                /*This config has been added for satisfying misra compliance, MISRA.INIT.PARTIAL.2012 */
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST2_DFT_PBIST_CPU_0,
        .doneFlag               = PBIST_NOT_DONE
    },

    /* C7X0 */
	{
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_C7X256V0_PBIST_BASE,
        .numPBISTRuns        = SDL_C7X256V0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_C7X256V0_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_C7X256V0_MEM_BITMAP_0,
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

	/* C7X1 */
	{
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_C7X256V1_PBIST_BASE,
        .numPBISTRuns        = SDL_C7X256V1_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_C7X256V1_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_C7X256V1_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = SDL_C7X256V1_ALGO_BITMAP_1,
                .memoryGroupsBitMap = SDL_C7X256V1_MEM_BITMAP_1,
                .scrambleValue      = 0xFEDCBA9876543210U,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_C7X256V1_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_C7X256V1_CLEC_DFT_PBIST_CPU_0,
        .doneFlag               = PBIST_NOT_DONE
    },

    /* DM2 */
	{
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_WKUP_PBIST1_BASE,
        .numPBISTRuns        = SDL_WKUP_PBIST1_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_WKUP_PBIST1_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_WKUP_PBIST1_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                /*This config has been added for satisfying misra compliance, MISRA.INIT.PARTIAL.2012 */
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_WKUP_PBIST1_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_WKUP_PBIST1_DFT_PBIST_CPU_0 ,
        .doneFlag               = PBIST_NOT_DONE
    },

    /* Main IP */
    {
        .PBISTRegsHiAddress  = 0x0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST0_BASE,
        .numPBISTRuns        = SDL_PBIST0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST0_ALGO_BITMAP_0,  /* Choose recommended Algo bitmap */
                .memoryGroupsBitMap = SDL_PBIST0_MEM_BITMAP_0,   /* Choose recommended mem bitmap  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
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
            .RAMT  = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT
        },

        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST0_DFT_PBIST_CPU_0,
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

static void SDL_PBIST_postCheckResult(uint32_t postStatMmrRegVal,
                                      SDL_PBIST_hwpostInst instance,
                                      bool *pResult)
{
    uint32_t mask = 0xFFFFFFFFu;
    (void)instance;


    /* Only one instance supported for am275x: SDL_PBIST_HWPOST_INST_MCU */
    mask = SDL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_DONE_MASK;


    if ((postStatMmrRegVal & mask) == ((uint32_t)0x00000000u))
    {
        *pResult = (bool)true;
    }
    else
    {
        *pResult = (bool)false;
    }


    return;
}


static void SDL_PBIST_isPostPbistTimeout(uint32_t postStatMmrRegVal,
                                         SDL_PBIST_hwpostInst instance,
                                         bool *pIsTimedOut)
{
    uint32_t shift;
    (void)instance;


    /* Only one instance supported for am275x: SDL_PBIST_HWPOST_INST_MCU */
    shift = SDL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_TIMEOUT_SHIFT;


    *pIsTimedOut = (((postStatMmrRegVal >> shift) & 0x1u) == 0x1u) ? (bool)true : (bool)false;


    return;
}


static void SDL_PBIST_isPostPbistDone(uint32_t postStatMmrRegVal,
                                      SDL_PBIST_hwpostInst instance,
                                      bool *pIsDone)
{
    uint32_t shift;
    (void)instance;


    /* Only one instance supported for am275x: SDL_PBIST_HWPOST_INST_MCU */
    shift = SDL_WKUP_CTRL_MMR_CFG0_POST_STAT_POST_PBIST_DONE_SHIFT;


    *pIsDone = (((postStatMmrRegVal >> shift) & 0x1u) == 0x1u) ? (bool)true : (bool)false;


    return;
}


static void SDL_PBIST_runPostPbistCheck(SDL_PBIST_hwpostInst instance, SDL_PBIST_postStatus *pPostStatus)
{
    uint32_t postRegVal;
    bool     PBISTResult;


    /* Get PBIST register space Pointer */
    *pPostStatus = SDL_PBIST_POST_COMPLETED_SUCCESS;


    /* Read HW POST status register */
    postRegVal = HW_RD_REG32_RAW(SDL_WKUP_CTRL_MMR0_CFG0_BASE +
                              SDL_WKUP_CTRL_MMR_CFG0_POST_STAT);


    /* Check if HW POST PBIST was performed */
    SDL_PBIST_isPostPbistDone(postRegVal, instance, &PBISTResult);


    if (PBISTResult != (bool) true)
    {
        /* HW POST: PBIST not completed, check if it timed out */
        SDL_PBIST_isPostPbistTimeout(postRegVal,
                                     instance,
                                     &PBISTResult);
        if (PBISTResult != (bool) true)
        {
            /* HW POST: PBIST was not performed at all on this device
             * for this core */
            *pPostStatus = SDL_PBIST_POST_NOT_RUN;
        }
        else
        {
            /* HW POST: PBIST was attempted but timed out for this section */
            *pPostStatus = SDL_PBIST_POST_TIMEOUT;
        }
    }
    else
    {
        /* HW POST: PBIST was completed on this device, check the result */
        SDL_PBIST_postCheckResult(postRegVal, instance, &PBISTResult);
        if (PBISTResult != (bool) true)
        {
            /* HW POST: PBIST was completed, but the test failed */
            *pPostStatus = SDL_PBIST_POST_COMPLETED_FAILURE;
        }
    } /* if (PBISTResult != (bool) true) */


    return;
}


int32_t SDL_PBIST_getDevicePostStatus(SDL_PBIST_postResult *pResult)
{
    int32_t ret = SDL_PASS;


    /* Get status for MCU */
    SDL_PBIST_runPostPbistCheck(SDL_PBIST_INST_DM, &pResult->mcuPostStatus);


    return ret;
}