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
 *
 */

 /**
 *  \file     sdl_pbist_test_cfg.c
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
int32_t PBIST_GpuAuxInitRestore(bool init);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t PBIST_MPUAuxDevList[MPU_NUM_AUX_DEVICES] =
{
    TISCI_DEV_COMPUTE_CLUSTER0,
    TISCI_DEV_A53SS0,
	TISCI_DEV_A53SS0_CORE_0,
	TISCI_DEV_A53SS0_CORE_1,
	TISCI_DEV_A53SS0_CORE_2,
	TISCI_DEV_A53SS0_CORE_3,
	TISCI_DEV_COMPUTE_CLUSTER0_PBIST_0,
};

uint32_t PBIST_MainAuxDevList[MAIN_NUM_AUX_DEVICES] =
{
	TISCI_DEV_DMASS0,
	TISCI_DEV_ICSSM0,
	TISCI_DEV_CPSW0,
	TISCI_DEV_CSI_RX_IF0,
	TISCI_DEV_USB0,
	TISCI_DEV_USB1,
	TISCI_DEV_MCAN0,
	TISCI_DEV_GICSS0,
	TISCI_DEV_MMCSD0,
	TISCI_DEV_MMCSD2,
	TISCI_DEV_MMCSD1,
	TISCI_DEV_DSS0,
};

uint32_t PBIST_GpuAuxDevList[GPU_NUM_AUX_DEVICES] =
{
    TISCI_DEV_GPU0,
    TISCI_DEV_PBIST1,
};

PBIST_TestHandle_t PBIST_TestHandleArray[PBIST_MAX_INSTANCE+1] =
{
    /* GPU PBIST  */
    {
        .testName               = "GPU PBIST",
        .pbistInst              = SDL_PBIST_INST_GPU,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST1,     /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = GPU_NUM_AUX_DEVICES,     /* No Aux devices */
        .auxDeviceIdsP          = &PBIST_GpuAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_GpuAuxInitRestore, /* Auxilliary init function */
    },

    /* MPU A53 */
    {
        .testName               = "MPU PBIST",
        .pbistInst              = SDL_PBIST_INST_MPU,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_COMPUTE_CLUSTER0_PBIST_0, /* Device Id for PBIST */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = true,                /* Secondary core needed */
        .coreName               = "MPU core 0",        /* Primary core   */
        .secCoreName            = "MPU core 1",        /* Secondary core */
        .tisciProcId            = SCICLIENT_PROC_ID_A53SS0_CORE_0,  /* A53 core 0 Proc Id */
        .tisciSecProcId         = SCICLIENT_PROC_ID_A53SS0_CORE_1,  /* A53 core 1 Proc Id */
		.tisciThirdProcId       = SCICLIENT_PROC_ID_A53SS0_CORE_2,
        .tisciForthProcId       = SCICLIENT_PROC_ID_A53SS0_CORE_3,
        .tisciDeviceId          = TISCI_DEV_A53SS0_CORE_0,      /* A53 core 0 Device Id */
        .tisciSecDeviceId       = TISCI_DEV_A53SS0_CORE_1,      /* A53 core 1 Device Id */
		.tisciThirdDeviceId     = TISCI_DEV_A53SS0_CORE_2,
        .tisciForthDeviceId     = TISCI_DEV_A53SS0_CORE_3,
        .coreCustPwrSeqNeeded   = false,                    /* MPU needs custom powerdown sequence steps */
        .numAuxDevices          = MPU_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_MPUAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_MPUAuxInitRestore, /* Auxilliary init function */
    },
    /* MAIN */
    {
        .testName               = "MAIN PBIST",
        .pbistInst              = SDL_PBIST_INST_MAIN,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST0,    /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               /* Secondary core needed */
        .coreName               = "Main",             /* No coreName   */
        .tisciProcId            = 0x0u,                /* No Proc Id needed for Main Intrastructure */
        .tisciDeviceId          = 0x0u,                /* No Device Id needed for Main infrastructure */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = MAIN_NUM_AUX_DEVICES,
        .auxDeviceIdsP          = &PBIST_MainAuxDevList[0],
        .auxInitRestoreFunction = PBIST_MainAuxInitRestore,
    },

	/* DM */
    {
        .testName               = "DM PBIST",
        .pbistInst              = SDL_PBIST_INST_DM,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_WKUP_PBIST0,    /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               /* Secondary core needed */
        .coreName               = "DM",              /* No coreName   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0x0u,                /* No Aux devices */
        .auxInitRestoreFunction = NULL,                /* Auxilliary init function */
    },
};

/* Captures common Initialization: currently nothing needed */
int32_t PBIST_commonInit(void)
{
    SDL_ErrType_t status = SDL_PASS;

    return status;
}

/* define the unlock and lock values */
#define KICK0_UNLOCK_VAL 0x68EF3490
#define KICK1_UNLOCK_VAL 0xD172BC5A
#define KICK_LOCK_VAL    0x00000000
#define A53_CFG_BISOR_OVERRIDE  0x10600
#define PBIST_MMR_EN 0xC400
/*
    InitRestore functions : Initialize or Restore based on init flag
    init : TRUE  --> Initialize
    init : FALSE --> Restore
*/
int32_t PBIST_MPUAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    uint32_t baseAddr;

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(SDL_MCU_CTRL_MMR0_CFG0_BASE);

    *((uint32_t *)(((uint32_t)baseAddr) + CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(((uint32_t)baseAddr) + CSL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1)) = KICK1_UNLOCK_VAL;
    /* BISOR override is needed to verify DC memories in cfg */
    if (init)
    {
        *((uint32_t *)(((uint32_t)baseAddr) + A53_CFG_BISOR_OVERRIDE)) = 0x1;
    }
    else
    {
        *((uint32_t *)(((uint32_t)baseAddr) + A53_CFG_BISOR_OVERRIDE)) = 0x0;
    }

    return testResult;
}

int32_t PBIST_MainAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    uint32_t baseAddr, baseAddrMain;

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(SDL_WKUP_CTRL_MMR0_CFG0_BASE);
    baseAddrMain = (uint32_t) AddrTranslateP_getLocalAddr(SDL_CTRL_MMR0_CFG0_BASE);
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1)) = KICK1_UNLOCK_VAL;
	*((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddrMain + CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddrMain + CSL_MAIN_CTRL_MMR_CFG0_LOCK2_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1)) = KICK1_UNLOCK_VAL;

    if (init)
    {
        *((uint32_t *)(baseAddr + PBIST_MMR_EN)) = 0x0831;
        *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL)) = 0x002f8000;
    }
    else
    {
        *((uint32_t *)(baseAddr + PBIST_MMR_EN)) = 0x0;
    }

    return testResult;
}

int32_t PBIST_GpuAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    uint32_t baseAddr;

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);

    *((uint32_t *)(baseAddr + CSL_MCU_CTRL_MMR_CFG0_PBIST_EN_TEST_REG)) = 0x1;

    return testResult;
}

/* Nothing past this point */