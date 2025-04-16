/*
 *   Copyright (c) Texas Instruments Incorporated 2024
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
        // .numPostPbistToCheck    = 1u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST1,    /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = true,                 /* Secondary core needed */
        .coreName               = "R5F0 core 0",   /* Primary core   */
        .secCoreName            = "R5F0 core 1",   /* Secondary core */
        .tisciProcId            = PROC_ID_R5FSS0_CORE0,
        .tisciSecProcId         = PROC_ID_R5FSS0_CORE1,
        .tisciDeviceId          = TISCI_DEV_R5FSS0_CORE0,
        .tisciSecDeviceId       = TISCI_DEV_R5FSS0_CORE1,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = P0_NUM_AUX_DEVICES,     			/* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_P0AuxDevList[0], 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore,				/* Auxilliary init function */              /* Initialize done flag  */
    },
    #endif

    #if defined (R5FSS0)
    /* PBIST2 */
	{
        .testName               = "Pulsar1",
        .pbistInst              = SDL_PBIST_INST_MAIN_PULSAR_1,
        // .numPostPbistToCheck    = 1u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST2,
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
    },
    #endif

    /* C7X256V0 */
	{
       .testName                = "C7X0",
        .pbistInst              = SDL_PBIST_INST_C7X_0,
        .tisciPBISTDeviceId     = TISCI_DEV_C7X256V0_PBIST,
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "C7X256V0",   /* Primary core   */
        .tisciProcId            = PROC_ID_C7X256V0_C7XV_CORE_0,
        .tisciDeviceId          = TISCI_DEV_C7X256V0_C7XV_CORE_0,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = C70_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_C70AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore,
    },

    /* C7X256V1 */
	{

        .testName               = "C7X1",
        .pbistInst              = SDL_PBIST_INST_C7X_1,
        .tisciPBISTDeviceId     = TISCI_DEV_C7X256V1_PBIST,
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "C7X256V1",   /* Primary core   */
        .tisciProcId            = PROC_ID_C7X256V1_C7XV_CORE_0,
        .tisciDeviceId          = TISCI_DEV_C7X256V1_C7XV_CORE_0,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = C71_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_C71AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore,
    },

	/* WKUP_PBIST1 */
    {
        .testName               = "DM2",
        .pbistInst              = SDL_PBIST_INST_DM_2,
        .numPostPbistToCheck    = 1u,
        .tisciPBISTDeviceId     = TISCI_DEV_WKUP_PBIST1,    /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               	/* Secondary core needed */
        .coreName               = "WKUP_PBIST1",             	/* No coreName   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0,    				/* No Aux devices */
        .auxDeviceIdsP          = NULL, 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore,
    },

    /* PBIST0  */
    {
        .testName               = "Main IP",
        .pbistInst              = SDL_PBIST_INST_MAIN_IP,
        // .numPostPbistToCheck    = 1u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST0,     /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "PBIST0",   /* Primary core   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = Main_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_MainAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore,     /* Auxilliary init function */
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
