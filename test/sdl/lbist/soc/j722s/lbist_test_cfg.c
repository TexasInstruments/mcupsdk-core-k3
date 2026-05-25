/*
 *  Copyright (C) 2024-2025 Texas Instruments Incorporated
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
#include <sdl/include/j722s/sdlr_soc_baseaddress.h>
#include <sdl/include/j722s/sdlr_mcu_ctrl_mmr.h>
#include <drivers/sciclient/include/j722s/sciclient_fmwMsgParams.h>
#include <drivers/soc.h>
#include <drivers/hw_include/j722s/csl_soc_psc.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* #define DEBUG */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t LBIST_R5FAuxDevList[R5F_NUM_AUX_DEVICES] =
{
    TISCI_DEV_MAIN2MCU_VD,
};

LBIST_TestHandle_t LBIST_TestHandleArray[LBIST_MAX_CORE_INDEX + 1] =
    {
        /* R5F */
        {
            .coreName = "MCU-R5F",
            .instance = LBIST_MCU_R5F,
            .secondaryCoreNeeded = false,                      /* Secondary core needed */
            .wfiCheckNeeded = false,                           /* wfi check needed */
            .cpuStatusFlagMask = 0x00000002U,                  /* Expected boot status value for wfi */
            .tisciProcId = SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, /* R5F Proc Id */
            .tisciDeviceId = TISCI_DEV_MCU_R5FSS0_CORE0,       /* MCU R5F Device Id */
            .numAuxDevices = R5F_NUM_AUX_DEVICES,
            .auxDeviceIdsP = LBIST_R5FAuxDevList,
        },
        /* VPAC0 */
        {
            .coreName = "VPAC0",
            .instance = LBIST_VPAC0,
            .secondaryCoreNeeded = false,     /* Secondary core needed */
            .wfiCheckNeeded = false,          /* wfi check needed */
            .cpuStatusFlagMask = 0x00000002U, /* Expected boot status value for wfi */
            .tisciProcId = 0u,
            .tisciDeviceId = TISCI_DEV_VPAC0, /* MCU R5F Device Id */
            .numAuxDevices = 0u,              /* No Aux devices */
        },
        /* DMPAC */
        {
            .coreName = "DMPAC",
            .instance = LBIST_DMPAC,
            .secondaryCoreNeeded = false,     /* Secondary core needed */
            .wfiCheckNeeded = false,          /* wfi check needed */
            .cpuStatusFlagMask = 0x00000002U, /* Expected boot status value for wfi */
            .tisciProcId = 0u,
            .tisciDeviceId = TISCI_DEV_DMPAC0, /* MCU R5F Device Id */
            .numAuxDevices = 0u,               /* No Aux devices */
        },

};

LBIST_PSC_t LBIST_pscDisableList[LBIST_NUM_DISABLES] =
{
    /* Core PSC */
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MCU,
        .pscPowerDomainId   = CSL_WKUP_PD_MCUSS,
        .pscIndex           = CSL_WKUP_LPSC_MCU_R5,
    },
};

LBIST_PSC_t LBIST_pscEnableList[LBIST_NUM_ENABLES] =
{
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MCU,
        .pscPowerDomainId   = CSL_WKUP_PD_MCUSS,
        .pscIndex           = CSL_WKUP_LPSC_MCU2DM_ISO,
    },
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MCU,
        .pscPowerDomainId   = CSL_WKUP_PD_MCUSS,
        .pscIndex           = CSL_WKUP_LPSC_MCU_R5,
    },
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MCU,
        .pscPowerDomainId   = CSL_WKUP_PD_MCUSS,
        .pscIndex           = CSL_WKUP_LPSC_MCU_MCANSS_0,
    },
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MCU,
        .pscPowerDomainId   = CSL_WKUP_PD_MCUSS,
        .pscIndex           = CSL_WKUP_LPSC_MCU_MCANSS_1,
    },
    {
        .pscDomainId        = SOC_PSC_DOMAIN_ID_MCU,
        .pscPowerDomainId   = CSL_WKUP_PD_MCUSS,
        .pscIndex           = CSL_WKUP_LPSC_MCU_PBIST,
    },
};

LBIST_TestHandle_t *LBIST_getTestHandleArray(void)
{
    return LBIST_TestHandleArray;
}

/* Nothing past this point */