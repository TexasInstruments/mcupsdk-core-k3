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
 *
 */

/**
 *  \file sciclient_ccs_init.c
 *
 *  \brief Implementation of System firmware boot + BoardCfg setting for CCS boot in K3 devices
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <drivers/sciclient/sciclient_priv.h>
#if defined ENABLE_SCICLIENT_DIRECT
/* WKUP R5 will use the SCI Client direct */
#include <drivers/device_manager/sciclient.h>
#else
#include <drivers/sciclient.h>
#endif
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

#if defined(SOC_J722S)
/* RM/PM/SEC Board Config Headers */
#include <drivers/sciclient/sciclient_default_boardcfg/j722s/sciclient_defaultBoardcfg_rm_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/j722s/sciclient_defaultBoardcfg_pm_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/j722s/sciclient_defaultBoardcfg_security_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/j722s/sciclient_defaultBoardcfg.h>

#elif defined(SOC_AM275X)
/* RM/PM/SEC Board Config Headers */
#include <drivers/sciclient/soc/am275x/sysfw_hs_fs_signed.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am275x/sciclient_defaultBoardcfg_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am275x/sciclient_defaultBoardcfg_rm_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am275x/sciclient_defaultBoardcfg_pm_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am275x/sciclient_defaultBoardcfg_security_hex.h>
#include <drivers/sciclient/sciclient_default_boardcfg/am275x/sciclient_defaultBoardcfg.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(SOC_J722S)
#define SCISERVER_POPULATE_BOARDCFG         (1U)

/** \brief Aligned address at which the Board Config header is placed. */
#define SCISERVER_BOARDCONFIG_HEADER_ADDR   (0x43c7c800U)

/** \brief Aligned address at which the Board Config is placed. */
#define SCISERVER_BOARDCONFIG_DATA_ADDR     (0x43c7c840U)
#endif  /* SOC_J722S */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#if defined (SCISERVER_POPULATE_BOARDCFG)
static int32_t Sciclient_ccsSetBoardConfigHeader();
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t sciclient_set_boardcfg(void)
{
    int32_t status;

    status = Sciclient_getVersionCheck(1);
    if(SystemP_SUCCESS == status)
    {
        /* Do an ABI check */
        status = Sciclient_abiCheck();
        if (SystemP_SUCCESS == status)
        {
            DebugP_log("[SCICLIENT] ABI check PASSED \r\n");
        }
        else
        {
            DebugP_logError("[SCICLIENT] ABI check has failed \r\n");
        }
    }
    if(SystemP_SUCCESS == status)
    {
        /* Do common board  configuration */
        Sciclient_BoardCfgPrms_t boardCfgPrms =
        {
            .boardConfigLow = (uint32_t) &gBoardConfigLow_debug,
            .boardConfigHigh = 0,
            .boardConfigSize = sizeof(gBoardConfigLow_debug),
            .devGrp = DEVGRP_ALL,
        };

        status = Sciclient_boardCfg(&boardCfgPrms);
        if (SystemP_SUCCESS == status)
        {
            DebugP_log("[SCICLIENT] Common Board Configuration PASSED \r\n");
        }
        else
        {
            DebugP_logError("[SCICLIENT] Sciclient Common Board Configuration has failed \r\n");
        }
    }
    if(SystemP_SUCCESS == status)
    {
        status = Sciclient_setDebugConfig();
    }
    if(SystemP_SUCCESS == status)
    {
        /* Do board configuration for Power Management */
        static uint8_t boardCfgLow[] = SCICLIENT_BOARDCFG_PM;
        Sciclient_BoardCfgPrms_t boardCfgPrms_pm =
        {
            .boardConfigLow = (uint32_t)boardCfgLow,
            .boardConfigHigh = 0,
            .boardConfigSize = 0,
            .devGrp = DEVGRP_ALL,
        };
        status = Sciclient_boardCfgPm(&boardCfgPrms_pm);

        if (SystemP_SUCCESS == status)
        {
            DebugP_log("[SCICLIENT] PM Board Configuration PASSED \r\n");
        }
        else
        {
            DebugP_logError("[SCICLIENT] PM Board Configuration has failed \r\n");
        }
    }
    if (SystemP_SUCCESS == status)
    {
        /* Do board configuration for Resource Management */
        static uint8_t boardCfgLow[] = SCICLIENT_BOARDCFG_RM;
        Sciclient_BoardCfgPrms_t boardCfgPrms_rm =
        {
            .boardConfigLow = (uint32_t)boardCfgLow,
            .boardConfigHigh = 0,
            .boardConfigSize = SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES,
            .devGrp = DEVGRP_ALL,
        };
        status = Sciclient_boardCfgRm(&boardCfgPrms_rm);
        if (SystemP_SUCCESS == status)
        {
            DebugP_log("[SCICLIENT] RM Board Configuration PASSED \r\n");
        }
        else
        {
            DebugP_logError("[SCICLIENT] RM Board Configuration has failed \r\n");
        }
    }
    if (status == SystemP_SUCCESS)
    {
        /* Do board configuration for Security */
        static uint8_t boardCfgLow[] = SCICLIENT_BOARDCFG_SECURITY;
        Sciclient_BoardCfgPrms_t boardCfgPrms_sec =
        {
            .boardConfigLow = (uint32_t)boardCfgLow,
            .boardConfigHigh = 0,
            .boardConfigSize = SCICLIENT_BOARDCFG_SECURITY_SIZE_IN_BYTES,
            .devGrp = DEVGRP_ALL,
        };
        status = Sciclient_boardCfgSec(&boardCfgPrms_sec) ;
        if (SystemP_SUCCESS == status)
        {
            DebugP_log("[SCICLIENT] Security Board Configuration PASSED \r\n");
        }
        else
        {
            DebugP_logError("[SCICLIENT] Security Board Configuration has failed \r\n");
        }
    }
    if (status == SystemP_SUCCESS)
    {
        /* Get SYSFW version and log the  version results to console */
        status = Sciclient_getVersionCheck(1);
    }
    if (status == SystemP_SUCCESS)
    {
        #if defined (SCISERVER_POPULATE_BOARDCFG)
        status = Sciclient_ccsSetBoardConfigHeader ();
        #endif
    }

    if (status == SystemP_SUCCESS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    return status;
}

#ifndef SOC_J722S
int32_t sciclient_load_sysfw(void)
{
    int32_t status = SystemP_FAILURE;

    /* Load FW if not already done */
    uint32_t size = SYSFW_SIZE_IN_BYTES;
    size = (size + 31U) & ~(31U);
    CacheP_wbInv((uint8_t *)SYSFW, size, CacheP_TYPE_ALL);
    status = Sciclient_loadFirmware((uint32_t *)SYSFW);

    return status;
}

int32_t app_system_init(void)
{
    int32_t status;
    Sciclient_ConfigPrms_t pCfgPrms;
    static uint8_t boardCfgLowPM[] = SCICLIENT_BOARDCFG_PM;

    pCfgPrms.inPmPrms.boardConfigLow = (uint32_t)boardCfgLowPM;
    pCfgPrms.inPmPrms.boardConfigHigh = 0U;
    pCfgPrms.inPmPrms.boardConfigSize = 0U;
    pCfgPrms.inPmPrms.devGrp = DEVGRP_ALL;

    static uint8_t boardCfgLowRM[] = SCICLIENT_BOARDCFG_RM;
    pCfgPrms.inRmPrms.boardConfigLow = (uint32_t)boardCfgLowRM;
    pCfgPrms.inRmPrms.boardConfigHigh = 0U;
    pCfgPrms.inRmPrms.boardConfigSize = SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES;
    pCfgPrms.inRmPrms.devGrp = DEVGRP_ALL;

    pCfgPrms.opModeFlag     = SCICLIENT_SERVICE_OPERATION_MODE_POLLED;
    pCfgPrms.pBoardCfgPrms  = NULL;
    pCfgPrms.isSecureMode   = 0U;
    pCfgPrms.c66xRatRegion  = 15U;
    pCfgPrms.skipLocalBoardCfgProcess = 0U;

    status = Sciclient_init(&pCfgPrms);
    if (status == SystemP_SUCCESS)
    {
        DebugP_log("Sciclient_init have passed!!\r\n");

        /* initialize PMU */
        CycleCounterP_init(SOC_getSelfCpuClk());

        PowerClock_init();
        /* Now we can do pinmux */
        Pinmux_init();
        /* finally we initialize all peripheral drivers */
        Drivers_uartInit();
    }

    return status;
}
#endif

#if defined (SCISERVER_POPULATE_BOARDCFG)
static int32_t Sciclient_ccsSetBoardConfigHeader ()
{
    int32_t status = SystemP_SUCCESS;
    const uint8_t boardCfgLowPm[] = SCICLIENT_BOARDCFG_PM;
    const uint8_t boardCfgLowRm[] = SCICLIENT_BOARDCFG_RM;
    uint32_t alignedOffset = ((sizeof(boardCfgLowPm) + 128U)/128U)*128U;
    Sciclient_BoardCfgPrms_t boardCfgPrms_pm =
    {
        .boardConfigLow = (uint32_t)SCISERVER_BOARDCONFIG_DATA_ADDR,
        .boardConfigHigh = 0,
        .boardConfigSize = SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES,
        .devGrp = DEVGRP_ALL
    };
    Sciclient_BoardCfgPrms_t boardCfgPrms_rm =
    {
        .boardConfigLow =
            (uint32_t) SCISERVER_BOARDCONFIG_DATA_ADDR + alignedOffset,
        .boardConfigHigh = 0,
        .boardConfigSize = SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES,
        .devGrp = DEVGRP_ALL
    };
    DebugP_log("SCISERVER Board Configuration header population... ");
    status = Sciclient_boardCfgPrepHeader (
        (uint8_t *) SCISERVER_COMMON_X509_HEADER_ADDR,
        (uint8_t *) SCISERVER_BOARDCONFIG_HEADER_ADDR,
        &boardCfgPrms_pm, &boardCfgPrms_rm);
    CacheP_wbInv((void*)SCISERVER_COMMON_X509_HEADER_ADDR, 0x500, CacheP_TYPE_ALL);
    CacheP_wbInv((void*)SCISERVER_BOARDCONFIG_HEADER_ADDR, 0x500, CacheP_TYPE_ALL);
    if (SystemP_SUCCESS == status)
    {
        DebugP_log("PASSED\n");
    }
    else
    {
        DebugP_log("FAILED\n");
    }
    memcpy((void *)boardCfgPrms_pm.boardConfigLow, (void *) boardCfgLowPm, sizeof(boardCfgLowPm));
    CacheP_wbInv((void*)boardCfgPrms_pm.boardConfigLow, sizeof(boardCfgLowPm), CacheP_TYPE_ALL);
    memcpy((void *)boardCfgPrms_rm.boardConfigLow, (void *) boardCfgLowRm, sizeof(boardCfgLowRm));
    CacheP_wbInv((void*)boardCfgPrms_rm.boardConfigLow, sizeof(boardCfgLowRm), CacheP_TYPE_ALL);
    return status;
}
#endif
