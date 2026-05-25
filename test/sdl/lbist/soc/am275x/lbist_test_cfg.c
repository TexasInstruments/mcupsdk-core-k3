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
 *  \file     lbist_test_cfg.c
 *
 *  \brief    This file contains LBIST test configuration
 *
 *  \details  LBIST Test Configuration
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <string.h>
#include "lbist_test_cfg.h"
#include <sdl/include/am275x/sdlr_soc_baseaddress.h>
#include <sdl/include/am275x/sdlr_mcu_ctrl_mmr.h>
#include <drivers/sciclient/include/am275x/sciclient_fmwMsgParams.h>
#include <drivers/soc.h>
#include <sdl/include/hw_types.h>

/* #define DEBUG */

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

LBIST_TestHandle_t LBIST_TestHandleArray[LBIST_MAX_CORE_INDEX+1] =
{
 /*MAIN R5F 0*/
 {
  .coreName               = "MAIN-R5F0-0",
  .instance               = LBIST_MAIN_R5F0,
  .secondaryCoreNeeded    = true,                       /* Secondary core needed */
  .wfiCheckNeeded         = false,                      /* wfi check needed */
  .secCoreName            = "MAIN-R5F0-1",
  .cpuStatusFlagMask      = 0x00000002U,                /* Expected boot status value for wfi */
  .tisciProcId            = PROC_ID_R5FSS0_CORE0,       /* R5F Proc Id */
  .tisciSecProcId         = PROC_ID_R5FSS0_CORE1,
  .tisciDeviceId          = TISCI_DEV_R5FSS0_CORE0,     /* R5F Device Id */
  .tisciSecDeviceId       = TISCI_DEV_R5FSS0_CORE1,
  .numAuxDevices          = 0u,                         /* No Aux devices */
 },
  /*MAIN R5F 1*/
 {
  .coreName               = "MAIN-R5F1-0",
  .instance               = LBIST_MAIN_R5F1,
  .secondaryCoreNeeded    = true,                       /* Secondary core needed */
  .wfiCheckNeeded         = false,                      /* wfi check needed */
  .secCoreName            = "MAIN-R5F1-1",
  .cpuStatusFlagMask      = 0x00000002U,                /* Expected boot status value for wfi */
  .tisciProcId            = PROC_ID_R5FSS1_CORE0,       /* R5F Proc Id */
  .tisciSecProcId         = PROC_ID_R5FSS1_CORE1,
  .tisciDeviceId          = TISCI_DEV_R5FSS1_CORE0,     /* R5F Device Id */
  .tisciSecDeviceId       = TISCI_DEV_R5FSS1_CORE1,
  .numAuxDevices          = 0u,                         /* No Aux devices */
 },
};

#if defined(R5FSS1)
LBIST_PSC_t LBIST_pscDisableList[LBIST_NUM_DISABLES] =
{
    /* PBIST PSC */
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_0,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS0_PBIST,
    },
    /* Core PSC */
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_0,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS0_CORE0,
    },
    /* Core PSC */
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_0,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS0_CORE1,
    },
};

LBIST_PSC_t LBIST_pscEnableList[LBIST_NUM_ENABLES] = 
{

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MCU,
        .pscPowerDomainId   = CSL_WKUP_GP_CORE_CTL_MCU,
        .pscIndex           = CSL_WKUP_LPSC_DM2MCU_ISO,
    },

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_GP_CORE,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_MAIN2DM_ISO,
    },

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_0,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS0_CORE0,
    },

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_0,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS0_CORE1,
    },

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_0,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS0_PBIST,
    },
};
#elif defined(R5FSS0)
LBIST_PSC_t LBIST_pscDisableList[LBIST_NUM_DISABLES] =
{
    /* PBIST PSC */
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_1,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS1_PBIST,
    },
    /* Core PSC */
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_1,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS1_CORE0,
    },
    /* Core PSC */
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_1,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS1_CORE1,
    },
};

LBIST_PSC_t LBIST_pscEnableList[LBIST_NUM_ENABLES] = 
{

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MCU,
        .pscPowerDomainId   = CSL_WKUP_GP_CORE_CTL_MCU,
        .pscIndex           = CSL_WKUP_LPSC_DM2MCU_ISO,
    },

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_GP_CORE,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_MAIN2DM_ISO,
    },

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_1,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS1_CORE0,
    },

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_1,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS1_CORE1,
    },

    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MAIN,
        .pscPowerDomainId   = CSL_MAIN_R5SS_1,
        .pscIndex           = CSL_MAIN_LPSC_MAIN_R5SS1_PBIST,
    },
};
#endif

LBIST_TestHandle_t* LBIST_getTestHandleArray(void)
{
    return LBIST_TestHandleArray;
}

/* Nothing past this point */
