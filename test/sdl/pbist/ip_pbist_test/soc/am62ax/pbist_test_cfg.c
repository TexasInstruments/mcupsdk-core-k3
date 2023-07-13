/*
 *   Copyright (c) Texas Instruments Incorporated 2020-2023
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

#include <sdl/include/am62ax/sdlr_intr_esm0.h>
#include <sdl/sdl_esm.h>
#include <sdl/esm/sdl_esm_priv.h>

#include "power_seq.h"
#include "pbist_test_cfg.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* define the unlock and lock values */
#define KICK0_UNLOCK_VAL 0x68EF3490
#define KICK1_UNLOCK_VAL 0xD172BC5A
#define KICK_LOCK_VAL    0x00000000

#define CSL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL                              (0x00010600U)

/* UMC SCRUBBER*/
#define C7XV_UMC_CFG_C7X256V_CORE0_EL2_SCRB_CFG   0x00000010



/* ========================================================================== */
/*                            Local function prototypes                       */
/* ========================================================================== */
/*
    InitRestore functions : Initialize or Restore based on init flag
    init : TRUE  --> Initialize
    init : FALSE --> Restore
*/
int32_t PBIST_MPUAuxInitRestore(bool init);
int32_t PBIST_MainAuxInitRestore(bool init);
int32_t PBIST_McuAuxInitRestore(bool init);
int32_t PBIST_C7xAuxInitRestore(bool init);
int32_t PBIST_VpacAuxInitRestore(bool init);
int32_t PBIST_EncodeAuxInitRestore(bool init);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t PBIST_MPUAuxDevList[MPU_NUM_AUX_DEVICES] =
{
    TISCI_DEV_COMPUTE_CLUSTER0,
    TISCI_DEV_A53SS0_CORE_0,
	TISCI_DEV_A53SS0_CORE_1,
	TISCI_DEV_A53SS0_CORE_2,
	TISCI_DEV_A53SS0_CORE_3,
};

uint32_t PBIST_MainAuxDevList[MAIN_NUM_AUX_DEVICES] =
{
    TISCI_DEV_DMASS0,
	TISCI_DEV_CPSW0,
	TISCI_DEV_CSI_RX_IF0,
	TISCI_DEV_USB0,
	TISCI_DEV_USB1,
	TISCI_DEV_MCAN0,
	TISCI_DEV_MCU_MCAN1,
	TISCI_DEV_MCU_MCAN0,
	TISCI_DEV_MMCSD0,
	TISCI_DEV_MMCSD1,
	TISCI_DEV_DSS0,
};

uint32_t PBIST_McuAuxDevList[MCU_NUM_AUX_DEVICES] =
{
    TISCI_DEV_MMCSD0,
    TISCI_DEV_MMCSD1,
};

uint32_t PBIST_C7xAuxDevList[C7X_NUM_AUX_DEVICES] =
{
    TISCI_DEV_C7X256V0,
	TISCI_DEV_C7X256V0_PBIST,
};

uint32_t PBIST_CodecAuxDevList[CODEC_NUM_AUX_DEVICES]=
{
    TISCI_DEV_CODEC0,
};
PBIST_TestHandle_t PBIST_TestHandleArray[PBIST_MAX_INSTANCE+1] =
{
	/* COMPUTE_CLUSTER0_PBIST : MPU  */
    {
        .testName               = "A53 MPU CLUSTER0",
        .pbistInst              = SDL_PBIST_INST_MPU,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs             = (SDL_pbistRegs *)SDL_COMPUTE_CLUSTER0_PBIST_BASE,
        .numPBISTRuns        	= SDL_COMPUTE_CLUSTER0_NUM_TEST_VECTORS,
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

        .PBISTNegConfigRun = {
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

        .tisciPBISTDeviceId     = TISCI_DEV_COMPUTE_CLUSTER0_PBIST_0,     /* PBIST device id  */
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_COMPUTE_CLUSTER0_PBIST_0_DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = true,                /* Secondary core needed */
        .coreName               = "MPU core 0",   /* Primary core   */
        .secCoreName            = "MPU core 1",   /* Secondary core */
        .tisciProcId            = SCICLIENT_PROC_ID_A53SS0_CORE_0,
        .tisciSecProcId         = SCICLIENT_PROC_ID_A53SS0_CORE_1,
        .tisciDeviceId          = TISCI_DEV_A53SS0_CORE_0,
        .tisciSecDeviceId       = TISCI_DEV_A53SS0_CORE_1,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = MPU_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_MPUAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_MPUAuxInitRestore, /* Auxilliary init function */
        .doneFlag               = false,                /* Initialize done flag  */
    },

    /* CODEC Instance PBIST3  */
    {
        .testName               = "CODEC PBIST3",
        .pbistInst              = SDL_PBIST_INST_ENCODE,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs             = (SDL_pbistRegs *)SDL_PBIST3_BASE,
        .numPBISTRuns           = SDL_PBIST3_NUM_TEST_VECTORS,
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

        .PBISTNegConfigRun =
        {
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

        .tisciPBISTDeviceId     = TISCI_DEV_PBIST3,    /* PBIST device id  */
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST3_K3_PBIST_8C28P_4BIT_WRAP__DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                 /* Secondary core needed */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = CODEC_NUM_AUX_DEVICES,     			/* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_CodecAuxDevList[0], 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_EncodeAuxInitRestore, 				/* Auxilliary init function */
        .doneFlag               = false,                /* Initialize done flag  */
    },
    /* C7X256V0 Instance C7X256V0_PBIST  */
    {
        .testName               = "C7X256V0 PBIST",
        .pbistInst              = SDL_PBIST_INST_C7X,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs             = (SDL_pbistRegs *)SDL_C7X256V0_PBIST_BASE,
        .numPBISTRuns        	= SDL_C7X256V0_NUM_TEST_VECTORS,
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

        .tisciPBISTDeviceId     = TISCI_DEV_C7X256V0_PBIST,    /* PBIST device id  */
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_C7X256V0_CLEC_DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                	/* Secondary core needed */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = C7X_NUM_AUX_DEVICES,     				/* No Aux devices */
        .auxDeviceIdsP          = &PBIST_C7xAuxDevList[0], 					/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_C7xAuxInitRestore, 					/* Auxilliary init function */
        .doneFlag               = false,                    /* Initialize done flag */
    },

    	/* VPAC Instance VPAC0_PBIST*/
    {
        .testName               = "VPAC INST",
        .pbistInst              = SDL_PBIST_INST_VPAC,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs          	= (SDL_pbistRegs *)SDL_VPAC0_MEM_BASE, /* PBIST2: Main R5F 0 */
        .numPBISTRuns        	= SDL_VPAC0_NUM_TEST_VECTORS,
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

        .tisciPBISTDeviceId     = TISCI_DEV_VPAC0,    /* PBIST device id  */
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_VPAC0_COMMON_0_K3_PBIST_8C28P_4BIT_WRAP__DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               	/* Secondary core needed */
        .coreName               = "VPAC",             	/* No coreName   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0x0u,    				/* No Aux devices */
        .auxDeviceIdsP          = 0x0u, 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_VpacAuxInitRestore, 				/* Auxilliary init function */
        .doneFlag               = false,               	/* Initialize done flag */
    },

	/* MAIN Instance PBIST0*/
    {
        .testName               = "MAIN PBIST0",
        .pbistInst              = SDL_PBIST_INST_MAIN,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs          	= (SDL_pbistRegs *)SDL_PBIST0_BASE, /* PBIST2: Main R5F 0 */
        .numPBISTRuns        	= SDL_PBIST0_NUM_TEST_VECTORS,
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

        .tisciPBISTDeviceId     = TISCI_DEV_PBIST0,    /* PBIST device id  */
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST0_DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               	/* Secondary core needed */
        .coreName               = "MAIN",             	/* No coreName   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = MAIN_NUM_AUX_DEVICES,    				/* No Aux devices */
        .auxDeviceIdsP          = &PBIST_MainAuxDevList[0], 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_MainAuxInitRestore, 				/* Auxilliary init function */
        .doneFlag               = false,               						/* Initialize done flag */
    },

    /* MCU_PULSER Instance MCU_PBIST0(WKUP_R5F) */
    {
        .testName               = "MCU PBIST0",
        .pbistInst              = SDL_PBIST_INST_MCU,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs          	= (SDL_pbistRegs *)SDL_MCU_PBIST0_BASE, /* PBIST2: Main R5F 0 */
        .numPBISTRuns        	= SDL_WKUP_R5FSS0_NUM_TEST_VECTORS,
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

        .tisciPBISTDeviceId     = TISCI_DEV_MCU_PBIST0,    /* PBIST device id  */
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_MCU_PBIST0_DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               	/* Secondary core needed */
        .coreName               = "MCU PULSER",             	/* No coreName   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = MCU_NUM_AUX_DEVICES,    				/* No Aux devices */
        .auxDeviceIdsP          = &PBIST_McuAuxDevList[0], 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_McuAuxInitRestore, 				/* Auxilliary init function */
        .doneFlag               = false,               					/* Initialize done flag */
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


/*
    InitRestore functions : Initialize or Restore based on init flag
    init : TRUE  --> Initialize
    init : FALSE --> Restore
*/
int32_t PBIST_MPUAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    uint32_t baseAddr;

	baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);

    *((uint32_t *)(((uint32_t)baseAddr) + CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(((uint32_t)baseAddr) + CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1)) = KICK1_UNLOCK_VAL;
    /* BISOR override is needed to verify DC memories in cfg */
    if (init)
    {
        *((uint32_t *)(((uint32_t)baseAddr) + CSL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL)) = 0x0001;
    }
    else
    {
        *((uint32_t *)(((uint32_t)baseAddr) + CSL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL)) = 0x0001;
    }

    return testResult;
}

int32_t PBIST_MainAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    uint32_t baseAddr;

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1)) = KICK1_UNLOCK_VAL;

    if (init)
    {
        *((uint32_t *)(baseAddr + CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG)) = 0x0831;
        *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0)) = 0x1;
		*((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0x1;

    }
    else
    {
        *((uint32_t *)(baseAddr + CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG)) = 0x0;
    }

    return testResult;
}

int32_t PBIST_McuAuxInitRestore(bool init)
{
    int32_t testResult = 0;

    return testResult;
}

int32_t PBIST_C7xAuxInitRestore(bool init)
{
    int32_t testResult = 0;
	uint32_t baseAddr;
    uint32_t C7X256V0_UMC_MEM_MAIN = 0x7c000000;
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);

    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0x00000800;

    /* Disable the L2 EDC scrubber */
    *((uint32_t *)(C7X256V0_UMC_MEM_MAIN + C7XV_UMC_CFG_C7X256V_CORE0_EL2_SCRB_CFG)) = 0x0u;


	return testResult;
}

int32_t PBIST_EncodeAuxInitRestore(bool init)
{
    int32_t testResult = 0;
	uint32_t baseAddr;
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);

    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0x00000008;

	return testResult;
}

int32_t PBIST_VpacAuxInitRestore(bool init)
{
    int32_t testResult = 0;
	uint32_t baseAddr;
    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);

    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0x00008000;

	return testResult;
}
/* Nothing past this point */
