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

 /**
 *  \file     pbist_test_cfg.c
 *
 *  \brief    This file contains PBIST test configuration
 *
 *  \details  PBIST Test Configuration
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <sdl/include/sdl_types.h>
#include <sdl/pbist/sdl_pbist_priv.h>
#include <sdl/sdl_pbist.h>
#include <drivers/sciclient.h>
#include <kernel/dpl/AddrTranslateP.h>

#include <sdl/include/am275x/sdlr_intr_esm0.h>
#include <sdl/sdl_esm.h>
#include <sdl/esm/sdl_esm_priv.h>

#include "pbist_test_cfg.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* ========================================================================== */
/*                            Local function prototypes                       */
/* ========================================================================== */
/*
    InitRestore functions : Initialize or Restore based on init flag
    init : TRUE  --> Initialize
    init : FALSE --> Restore
*/

int32_t PBIST_AuxInitRestore(bool init);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
// TEMPLATE
// uint32_t <PBIST_{custom_name}AuxDevList>[{custom_name}_NUM_AUX_DEVICES] =
// {
//     TISCI_DEV_{device1},    Refer DV Test files -> pbist_functions.c and "LPSC Feature" table in TRM
//     TISCI_DEV_{device2},    Can enable more devices than the necessary ones though not recommended
//     TISCI_DEV_{device3},
// };

uint32_t PBIST_MainAuxDevList[Main_NUM_AUX_DEVICES] =
{
    TISCI_DEV_MCAN0,
    TISCI_DEV_MCAN1,
    TISCI_DEV_MCAN2,
    TISCI_DEV_MCAN3,
    TISCI_DEV_MCAN4,
    TISCI_DEV_CPSW0,
    TISCI_DEV_MMCSD0,
    TISCI_DEV_USB0,
    TISCI_DEV_DEBUGSS0,
    TISCI_DEV_FSS0,
    TISCI_DEV_MLB0,
    TISCI_DEV_AASRC0,
    TISCI_DEV_AASRC1,
};

uint32_t PBIST_P0AuxDevList[P0_NUM_AUX_DEVICES] =
{
    TISCI_DEV_R5FSS0,
};

uint32_t PBIST_P1AuxDevList[P1_NUM_AUX_DEVICES] =
{
    TISCI_DEV_R5FSS1,
};

uint32_t PBIST_C70AuxDevList[C70_NUM_AUX_DEVICES] =
{
    TISCI_DEV_C7X256V0,
    TISCI_DEV_C7X256V0_CORE0,
};

uint32_t PBIST_C71AuxDevList[C71_NUM_AUX_DEVICES] =
{
    TISCI_DEV_C7X256V1,
    TISCI_DEV_C7X256V1_CORE0,
};


PBIST_TestHandle_t PBIST_TestHandleArray[PBIST_MAX_INSTANCE+1] =
{
    #if defined (R5FSS1)
	/* PBIST1  */
    {
        .testName               = "Pulsar0",
        .pbistInst              = SDL_PBIST_INST_MAIN_PULSAR_0,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs             = (SDL_pbistRegs *)SDL_PBIST1_BASE,
        .numPBISTRuns           = SDL_PBIST1_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST1_ALGO_BITMAP_0,  /* Choose recommended Algo bitmap */
                .memoryGroupsBitMap = SDL_PBIST1_MEM_BITMAP_0,   /* Choose recommended mem bitmap  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
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
            .RAMT  = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_RAMT
        },

        .tisciPBISTDeviceId     = TISCI_DEV_PBIST1,    /* PBIST device id  */
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST1_DFT_PBIST_CPU_0,
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = true,                /* Secondary core needed */
        .coreName               = "R5F0 core 0",   /* Primary core   */
        .secCoreName            = "R5F0 core 1",   /* Secondary core */
        .tisciProcId            = PROC_ID_R5FSS0_CORE0,
        .tisciSecProcId         = PROC_ID_R5FSS0_CORE1,
        .tisciDeviceId          = TISCI_DEV_R5FSS0_CORE0,
        .tisciSecDeviceId       = TISCI_DEV_R5FSS0_CORE1,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = P0_NUM_AUX_DEVICES,     			/* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_P0AuxDevList[0], 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore,
        .doneFlag               = false,                /* Initialize done flag  */
    },
    #endif

    #if defined (R5FSS0)
    /* PBIST2 */
	{
        .testName               = "Pulsar1",
        .pbistInst              = SDL_PBIST_INST_MAIN_PULSAR_1,
        .numPostPbistToCheck    = 0u,
        .PBISTRegsHiAddress     = 0u,
        .pPBISTRegs             = (SDL_pbistRegs *)SDL_PBIST2_BASE,
        .numPBISTRuns           = SDL_PBIST2_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST2_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_PBIST2_MEM_BITMAP_0,
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
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST2,
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST2_DFT_PBIST_CPU_0,
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = true,                /* Secondary core needed */
        .coreName               = "R5F1 core 0",   /* Primary core   */
        .secCoreName            = "R5F1 core 1",   /* Secondary core */
        .tisciProcId            = PROC_ID_R5FSS1_CORE0,
        .tisciSecProcId         = PROC_ID_R5FSS1_CORE1,
        .tisciDeviceId          = TISCI_DEV_R5FSS1_CORE0,
        .tisciSecDeviceId       = TISCI_DEV_R5FSS1_CORE1,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = P1_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_P1AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore, /* Auxilliary init function */
        .doneFlag               = false,
    },
    #endif

    /* C7X256V0 */
	{
        .testName            = "C7X0",
        .pbistInst           = SDL_PBIST_INST_C7X_0,
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
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_C7X256V0_ALGO_BITMAP_1,
                .memoryGroupsBitMap = SDL_C7X256V0_MEM_BITMAP_1,
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
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

        .tisciPBISTDeviceId     = TISCI_DEV_C7X256V0_PBIST,
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_C7X256V0_CLEC_DFT_PBIST_CPU_0,
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "C7X256V0",   /* Primary core   */
        .tisciProcId            = PROC_ID_C7X256V0_C7XV_CORE_0,
        .tisciDeviceId          = TISCI_DEV_C7X256V0_C7XV_CORE_0,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = C70_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_C70AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore, /* Auxilliary init function */
        .doneFlag               = false,
    },

    /* C7X256V1 */
	{

        .testName            = "C7X1",
        .pbistInst           = SDL_PBIST_INST_C7X_1,
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

        .tisciPBISTDeviceId     = TISCI_DEV_C7X256V1_PBIST,
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_C7X256V1_CLEC_DFT_PBIST_CPU_0,
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "C7X256V1",   /* Primary core   */
        .tisciProcId            = PROC_ID_C7X256V1_C7XV_CORE_0,
        .tisciDeviceId          = TISCI_DEV_C7X256V1_C7XV_CORE_0,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = C71_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_C71AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore,
        .doneFlag               = false,
    },

	/* WKUP_PBIST1 */
    {
        .testName               = "DM2",
        .pbistInst              = SDL_PBIST_INST_DM_2,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs          	= (SDL_pbistRegs *)SDL_WKUP_PBIST1_BASE,
        .numPBISTRuns        	= SDL_WKUP_PBIST1_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_WKUP_PBIST1_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_WKUP_PBIST1_MEM_BITMAP_0,
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

        .tisciPBISTDeviceId     = TISCI_DEV_WKUP_PBIST1,    /* PBIST device id  */
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_WKUP_PBIST1_DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               	/* Secondary core needed */
        .coreName               = "WKUP_PBIST1",             	/* No coreName   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0,    				/* No Aux devices */
        .auxDeviceIdsP          = NULL, 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore, 				/* Auxilliary init function */
        .doneFlag               = false,               						/* Initialize done flag */
    },

    /* PBIST0  */
    {
        .testName               = "Main IP",
        .pbistInst              = SDL_PBIST_INST_MAIN_IP,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs             = (SDL_pbistRegs *)SDL_PBIST0_BASE,
        .numPBISTRuns        	= SDL_PBIST0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST0_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_PBIST0_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,  /* Scramble Value */
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

        .tisciPBISTDeviceId     = TISCI_DEV_PBIST0,     /* PBIST device id  */
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST0_DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "Main core 0",   /* Primary core   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = Main_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_MainAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore,
        .doneFlag               = false,                /* Initialize done flag  */
    },
};

/* Captures common Initialization: currently nothing needed */
int32_t PBIST_commonInit(void)
{
    SDL_ErrType_t status = SDL_PASS;

    return status;
}

void PBIST_eventHandler( uint32_t instanceId)
{

    PBIST_TestHandleArray[instanceId].doneFlag = true;

    return;
}

/* define the unlock and lock values */
#define KICK0_UNLOCK_VAL 0x68EF3490
#define KICK1_UNLOCK_VAL 0xD172BC5A
#define KICK_LOCK_VAL    0x00000000


/*
    InitRestore functions : Initialize or Restore based on init flag
    init : TRUE  --> Initialize
    init : FALSE --> Restore
*/


int32_t PBIST_AuxInitRestore(bool init)
{
    int32_t testResult = 0;
	uint32_t baseAddr;
    uint32_t baseAddr1;
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);

    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0)) = 0xffffffff;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0xffffffff;

    baseAddr1 = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE);
    *((uint32_t *)(baseAddr1 + CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr1 + CSL_MAIN_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr1 + CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL)) = 0xffffffff;

    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN)) = 0xffffffff;
	return testResult;
}

char * PBIST_getPostStatusString(SDL_PBIST_postStatus postStatus)
{
    if (postStatus == SDL_PBIST_POST_NOT_RUN)
    {
        return PBIST_POST_NOT_RUN_STR;
    }
    else if (postStatus == SDL_PBIST_POST_TIMEOUT)
    {
        return PBIST_POST_ATTEMPTED_TIMEOUT_STR;
    }
    else if (postStatus == SDL_PBIST_POST_COMPLETED_FAILURE)
    {
        return PBIST_POST_COMPLETED_FAILURE_STR;
    }
    else if (postStatus == SDL_PBIST_POST_COMPLETED_SUCCESS)
    {
        return PBIST_POST_COMPLETED_SUCCESS_STR;
    }
    return NULL;
}

void PBIST_printPostStatus(SDL_PBIST_postResult *result)
{
    DebugP_log("    HW POST MCU Status : %s\r\n", (PBIST_getPostStatusString(result->mcuPostStatus)) ? : "Invalid");

    return;
}

/* Nothing past this point */
