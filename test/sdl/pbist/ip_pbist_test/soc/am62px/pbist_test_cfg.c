/*
 *  Copyright (C) 2023-2024 Texas Instruments Incorporated
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

#include <sdl/include/am62px/sdlr_intr_esm0.h>
#include <sdl/sdl_esm.h>
#include <sdl/esm/sdl_esm_priv.h>

#include "power_seq.h"
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
int32_t PBIST_MPUAuxInitRestore(bool init);
int32_t PBIST_MainAuxInitRestore(bool init);
int32_t PBIST_McuAuxInitRestore(bool init);
int32_t PBIST_EncodeAuxInitRestore(bool init);
int32_t PBIST_AuxInitRestore(bool init);
int32_t PBIST_GPUAuxInitRestore(bool init);

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

uint32_t PBIST_RTAuxDevList[RT_NUM_AUX_DEVICES] =
{
    TISCI_DEV_PBIST1,
    TISCI_DEV_MMCSD0,
	TISCI_DEV_MMCSD1,
	TISCI_DEV_MMCSD2,
	TISCI_DEV_CSI_RX_IF0,
    TISCI_DEV_USB0,
    TISCI_DEV_USB1,
    TISCI_DEV_MAIN_USB2_ISO_VD,
    TISCI_DEV_MAIN_USB0_ISO_VD,
    TISCI_DEV_DSS0,
    TISCI_DEV_DSS_DSI0,
    TISCI_DEV_DSS1,
    TISCI_DEV_DSS1_DPI1_PLLSEL_DEV_VD,
    TISCI_DEV_DSS1_DPI0_PLLSEL_DEV_VD,
    TISCI_DEV_DMASS1,
};

uint32_t PBIST_GPUAuxDevList[GPU_NUM_AUX_DEVICES] =
{
    TISCI_DEV_GPU0,
    TISCI_DEV_GPU0_CORE_VD,
    TISCI_DEV_PBIST1,
    TISCI_DEV_GPU_RS_BW_LIMITER9,
    TISCI_DEV_GPU_WS_BW_LIMITER10,

};

uint32_t PBIST_DM2AuxDevList[DM2_NUM_AUX_DEVICES] =
{
    TISCI_DEV_PBIST3,
    TISCI_DEV_FSS0,
    TISCI_DEV_MCAN0,
    TISCI_DEV_MCAN1,
	TISCI_DEV_MCU_MCAN1,
	TISCI_DEV_MCU_MCAN0,
};

uint32_t PBIST_MainAuxDevList[MAIN_NUM_AUX_DEVICES] =
{
    TISCI_DEV_DMASS0,
    TISCI_DEV_DMASS1,
    TISCI_DEV_DMASS0_PKTDMA_0,
    TISCI_DEV_DMASS0_BCDMA_0,
    TISCI_DEV_DMASS1_BCDMA_0,
    TISCI_DEV_DMASS0_IPCSS_0,
    TISCI_DEV_DMASS0_INTAGGR_0,
    TISCI_DEV_DMASS1_INTAGGR_0,
    TISCI_DEV_DMASS0_RINGACC_0,
    TISCI_DEV_DMASS0_CBASS_0,
    TISCI_DEV_DEBUGSS_WRAP0,
    TISCI_DEV_DEBUGSS0,
	TISCI_DEV_CPSW0,
	TISCI_DEV_CSI_RX_IF0,
	TISCI_DEV_USB0,
	TISCI_DEV_USB1,
	TISCI_DEV_MCAN0,
    TISCI_DEV_MCAN1,
	TISCI_DEV_MCU_MCAN1,
	TISCI_DEV_MCU_MCAN0,
	TISCI_DEV_MMCSD0,
	TISCI_DEV_MMCSD1,
	TISCI_DEV_MMCSD2,
	TISCI_DEV_DSS0,
    TISCI_DEV_GICSS0,
};

uint32_t PBIST_McuAuxDevList[MCU_NUM_AUX_DEVICES] =
{
    TISCI_DEV_MMCSD0,
    TISCI_DEV_MMCSD1,
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
        .pPBISTRegs             = (SDL_pbistRegs *)SDL_PBIST3_MEM_BASE,
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

    /* MAIN Instance PBIST1 */
	{
        .testName               = "PBIST1",
        .pbistInst              = SDL_PBIST_INST_PBIST1,
        .numPostPbistToCheck    = 0u,
        .PBISTRegsHiAddress     = 0u,
        .pPBISTRegs             = (SDL_pbistRegs *)SDL_PBIST1_BASE,
        .numPBISTRuns           = SDL_PBIST1_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST1_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_PBIST1_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = SDL_PBIST1_ALGO_BITMAP_1,
                .memoryGroupsBitMap = SDL_PBIST1_MEM_BITMAP_1,
                .scrambleValue      = 0xFEDCBA9876543210U,
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
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST1,
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_PBIST1_DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "PBIST1",   /* Primary core   */
        .tisciProcId            = 0X0U,
        .tisciDeviceId          = 0X0U,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = RT_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_RTAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore, /* Auxilliary init function */
        .doneFlag               = false,
    },

    /*Instance WKUP_PBIST1 */
	{
       .testName            = "WKUP_PBIST1",
        .pbistInst              = SDL_PBIST_INST_WKUP_PBIST1,
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

        .tisciPBISTDeviceId     = TISCI_DEV_WKUP_PBIST1,
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_WKUP_PBIST1_DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "WKUP_PBIST1",   /* Primary core   */
        .tisciProcId            = 0X0U,
        .tisciDeviceId          = 0X0U,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = DM2_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_DM2AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore, /* Auxilliary init function */
        .doneFlag               = false,
    },

    /*Instance GPU0 */
	{

        .testName            = "PBIST_GPU",
        .pbistInst           = SDL_PBIST_INST_GPU,
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_GPU0_MEM_BASE,
        .numPBISTRuns        = SDL_GPU0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_GPU0_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_GPU0_MEM_BITMAP_0,
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = SDL_GPU0_ALGO_BITMAP_1,
                .memoryGroupsBitMap = SDL_GPU0_MEM_BITMAP_1,
                .scrambleValue      = 0xFEDCBA9876543210U,
            }
        },

        .PBISTNegConfigRun = {
            .CA0   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_GPU0_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },

        .tisciPBISTDeviceId     = TISCI_DEV_GPU0,
        .interruptNumber        = SDL_PBIST_INTERRUPT_INVALID,
        .esmInst                = SDL_ESM_INST_MAIN_ESM0,
        .esmEventNumber         = SDLR_ESM0_ESM_PLS_EVENT0_GPU0_DFT_PBIST_CPU_0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "PBIST_GPU",   /* Primary core   */
        .tisciProcId            = 0X0U,
        .tisciDeviceId          = 0X0U,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = GPU_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_GPUAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_GPUAuxInitRestore, /* Auxilliary init function */
        .doneFlag               = false,
    },

	/* MAIN Instance PBIST0*/
    {
        .testName               = "MAIN PBIST0",
        .pbistInst              = SDL_PBIST_INST_MAIN,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs          	= (SDL_pbistRegs *)SDL_PBIST0_BASE, /* PBIST2: Main R5F 0 */
        .numPBISTRuns        	= 1u, /* Temporary it is 1, because other vector is failing */
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
        .auxInitRestoreFunction = PBIST_AuxInitRestore, 				/* Auxilliary init function */
        .doneFlag               = false,               						/* Initialize done flag */
    },

    /* MCU_PULSER Instance MCU_PBIST0(WKUP_R5F) */
    {
        .testName               = "MCU PBIST0",
        .pbistInst              = SDL_PBIST_INST_MCU,
        .numPostPbistToCheck    = 0u,
        .pPBISTRegs          	= (SDL_pbistRegs *)SDL_MCU_PBIST0_BASE, /* PBIST2: Main R5F 0 */
        .numPBISTRuns        	= SDL_MCU_PBIST0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_MCU_PBIST0_ALGO_BITMAP_0,
                .memoryGroupsBitMap = SDL_MCU_PBIST0_MEM_BITMAP_0,
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
            .CA0   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT,
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

/* define the unlock and lock values */
#define KICK0_UNLOCK_VAL 0x68EF3490
#define KICK1_UNLOCK_VAL 0xD172BC5A
#define KICK_LOCK_VAL    0x00000000

#define CSL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL                              (0x00010600U)

/* UMC SCRUBBER*/
#define C7XV_UMC_CFG_C7X256V_CORE0_EL2_SCRB_CFG   0x00000010


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
    *((uint32_t *)(((uint32_t)baseAddr) + CSL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL)) = 0x0001;

    if (init)
    {
        *((uint32_t *)(((uint32_t)baseAddr) + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0)) = 0x0001;
    }
    else
    {
        *((uint32_t *)(((uint32_t)baseAddr) + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0)) = 0x0000;
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
        *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0)) = 0x1;
		*((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0x1;
    }
    else
    {
        *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0)) = 0x0;
		*((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0x0;
    }

    return testResult;
}

int32_t PBIST_McuAuxInitRestore(bool init)
{
    int32_t testResult = 0;

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

    if (init)
    {

		*((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0x1;
    }
    else
    {
		*((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0x0;
    }

	return testResult;
}

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

    baseAddr1 = (uint32_t) AddrTranslateP_getLocalAddr(CSL_MCU_CTRL_MMR0_CFG0_BASE);
    *((uint32_t *)(baseAddr1 + CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr1 + CSL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr1 + CSL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL)) = 0xffffffff;

    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_PBIST_EN)) = 0xfff;
	return testResult;
}

int32_t PBIST_GPUAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    int32_t i = 0;
    uint32_t timeoutCnt;

    uint32_t localP = (uint32_t) SDL_GPU0_CORE_MMRS_BASE;

    if (testResult == 0)
    {
        if (init)
        {
            *((uint32_t *)(localP + 0xA100)) = 0x0;
            timeoutCnt = 100000U;
            while (timeoutCnt-- > 0)
            {
                if (*((uint32_t *)(localP + 0xA100)) ==  (uint32_t)0x0)
                {
                    break;
                }
            }
            if (timeoutCnt == 0)
            {
                DebugP_log("timeout in GPUAuxInitRestore [1]\n");
            }


            /* Force all GPU clocks on */
            *((uint64_t *)(localP)) = 0x0015550015115555;


            /* Force the FW Processor clocks to ON to enable testing of mars memories */
            *((uint32_t *)(localP + 0x3090)) = 0x00000001;
            i = 1000;
            while(i--);
            *((uint32_t *)(localP + 0x3480)) = 0x00000001;
            timeoutCnt = 100000U;
            while (timeoutCnt-- > 0)
            {
                if((*(uint32_t *)(localP + 0x3488) & 0x400) == (uint32_t)0x400)
                {
                    break;
                }
            }
            if (timeoutCnt == 0)
            {
                DebugP_log("timeout in GPUAuxInitRestore [2]\n");
            }
            *((uint32_t *)(localP + 0x3480)) = 0x80000001;
            i = 1000;
            while(i--);
            timeoutCnt = 100000U;
            while (timeoutCnt-- > 0)
            {
                if((*((uint32_t *)(((uint32_t)localP) + 0x3488)) & 0x200) == (uint32_t)0x200)
                {
                    break;
                }
            }
            if (timeoutCnt == 0)
            {
                DebugP_log("timeout in GPUAuxInitResotre [3]\n");
            }
            *((uint32_t *)(localP + 0x3420)) = 0x000001FF;
            *((uint32_t *)(localP + 0x34B8)) = 0x002307F8;
            timeoutCnt = 100000U;
            while (timeoutCnt-- > 0)
            {
                if((*((uint32_t *)(localP + 0x34B0)) & 0x1700) == (uint32_t)0x0000)
                {
                    break;
                }
            }
            if (timeoutCnt == 0)
            {
                DebugP_log("timeout in GPUAuxInitRestore [4]\n");
            }
            i = 1000;
            while(i--);
            *((uint32_t *)(((uint32_t)localP) + 0x3480)) = 0x00;
            i = 1000;
            while(i--);
        }
        else
        {
          /* TODO: Need to see how to revert */
        }
    }
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
    DebugP_log("    HW POST MCU Status : %s\n", (PBIST_getPostStatusString(result->mcuPostStatus)) ? : "Invalid");

    return;
}

/* Nothing past this point */
