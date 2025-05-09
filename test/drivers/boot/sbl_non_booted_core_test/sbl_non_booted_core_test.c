/*
 * Copyright (c) 2024-25, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file  sbl_non_booted_core_test.c
 *
 *  \brief SBL test to ensure non-booted cores are properly switched off
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/hw_include/csl_types.h>
#include <drivers/sciclient.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BOOT_MAX_CORE_ID                (9U)
#define SCICLIENT_SERVICE_WAIT_FOREVER  (0xFFFFFFFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct App_CoreInfo_s
{
    uint32_t deviceId;
    char* coreName;
} App_CoreInfo;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


App_CoreInfo coreInfo[] =
{
    /* A530-0 info */
    {
    TISCI_DEV_A53SS0_CORE_0,
    "a530-0"
    },
    /* A530-1 info */
    {
    TISCI_DEV_A53SS0_CORE_1,
    "a530-1"
    },
    /* A531-0 info */
    {
    TISCI_DEV_A53SS0_CORE_2,
    "a531-0"
    },
    /* A531-1 info */
    {
    TISCI_DEV_A53SS0_CORE_3,
    "a531-1"
    },
    /* MCU-R5F info */
    {
    TISCI_DEV_MCU_R5FSS0_CORE0,
    "mcu-r5f"
    },
    /* MAIN-R5F info */
    {
    TISCI_DEV_R5FSS0_CORE0,
    "main-r5f"
    },
    /* WKUP-R5F info */
    {
    TISCI_DEV_WKUP_R5FSS0_CORE0,
    "wkup-r5f"
    },
    /* C75SS0-0 info */
    {
    TISCI_DEV_C7X256V0_C7XV_CORE_0,
    "c75ss0-0"
    },
    /* C75SS1-0 info */
    {
    TISCI_DEV_C7X256V1_C7XV_CORE_0,
    "c75ss1-0"
    }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SblNonBootedCoreTest_main()
{
    int32_t                 retVal;
    uint32_t                moduleState = 0U;
    uint32_t                resetState = 0U;
    uint32_t                contextLossState = 0U;
    uint32_t                moduleId = 0U;
    int32_t                 result = 0;

    /* Open drivers to open the UART driver for console */
    Drivers_open();
    Board_driversOpen();

    for(int32_t coreId = 0; coreId < BOOT_MAX_CORE_ID; coreId++)
    {
        moduleId = (uint32_t) coreInfo[coreId].deviceId;

        if (moduleId == TISCI_DEV_WKUP_R5FSS0_CORE0)
        {
            /* Since this application is running on WKUP R5F, no need to check the
               power status of wkup-r5f */
            continue;
        }

        retVal = Sciclient_pmGetModuleState(moduleId,
                                            &moduleState,
                                            &resetState,
                                            &contextLossState,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
        if (CSL_PASS != retVal)
        {
            DebugP_log("Sciclient_pmGetModuleState Failed !!\r\n");
        }
        else
        {
            if (0U != moduleState)
            {
                DebugP_log("%s is powered ON !!\r\n", coreInfo[coreId].coreName);
                result += CSL_EFAIL;
            }
            else
            {
                DebugP_log("%s is powered OFF !!\r\n", coreInfo[coreId].coreName);
            }
        }

    }

    if (0U != result)
    {
        DebugP_log("Some tests have failed !!\r\n");
    }
    else
    {
        DebugP_log("All tests have passed\r\n");
    }

    Board_driversClose();
    Drivers_close();

    return;
}
