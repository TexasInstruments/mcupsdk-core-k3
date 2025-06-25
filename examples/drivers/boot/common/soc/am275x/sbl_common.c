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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t App_loadImages(Bootloader_LoadImageParams *bootLoadParams)
{
	int32_t status = SystemP_FAILURE;
    Bootloader_Config *bootConfig;

    if(bootLoadParams->bootHandle  != NULL)
    {
        bootConfig = (Bootloader_Config *)bootLoadParams->bootHandle;
        bootConfig->coresPresentMap = 0;
        status = Bootloader_parseAndLoadMultiCoreELF(bootLoadParams->bootHandle, &bootLoadParams->bootImageInfo);

        if((status == SystemP_SUCCESS) && TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_HSM_M4FSS0_0))
        {
            Bootloader_profileAddProfilePoint("HSM Image Load");
            bootLoadParams->coreId  = CSL_CORE_ID_HSM_M4FSS0_0;
            bootLoadParams->loadStatus  = BOOTLOADER_IMAGE_LOADED;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_C75SS0_0)))
        {
            Bootloader_profileAddProfilePoint("DSP 0 Image Load");
            bootLoadParams->coreId  = CSL_CORE_ID_C75SS0_0;
            bootLoadParams->loadStatus  = BOOTLOADER_IMAGE_LOADED;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_C75SS1_0)) && 
           (Bootloader_socGetNumDspCores() == 2U))
        {
            Bootloader_profileAddProfilePoint("DSP 1 Image Load");
            bootLoadParams->coreId  = CSL_CORE_ID_C75SS1_0;
            bootLoadParams->loadStatus  = BOOTLOADER_IMAGE_LOADED;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS0_0)))
        {
            Bootloader_profileAddProfilePoint("R5FSS0_0 Image Load");
            bootLoadParams->coreId  = CSL_CORE_ID_R5FSS0_0;
            bootLoadParams->loadStatus  = BOOTLOADER_IMAGE_LOADED;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS0_1)))
        {
            Bootloader_profileAddProfilePoint("R5FSS0_1 Image Load");
            bootLoadParams->coreId  = CSL_CORE_ID_R5FSS0_1;
            bootLoadParams->loadStatus  = BOOTLOADER_IMAGE_LOADED;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS1_0)) && 
           (Bootloader_socGetNumMcuCores() > 2U))
        {
            Bootloader_profileAddProfilePoint("R5FSS1_0 Image Load");
            bootLoadParams->coreId  = CSL_CORE_ID_R5FSS1_0;
            bootLoadParams->loadStatus  = BOOTLOADER_IMAGE_LOADED;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS1_1)) && 
           (Bootloader_socGetNumMcuCores() > 3U))
        {
            Bootloader_profileAddProfilePoint("R5FSS1_1 Image Load");
            bootLoadParams->coreId  = CSL_CORE_ID_R5FSS1_1;
            bootLoadParams->loadStatus  = BOOTLOADER_IMAGE_LOADED;
        }
    }

    return status;
}

int32_t App_runCpus(Bootloader_LoadImageParams *bootLoadParams)
{
    int32_t status = SystemP_SUCCESS;

    if(bootLoadParams->bootHandle  != NULL)
    {
        if((status == SystemP_SUCCESS) && TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_HSM_M4FSS0_0))
        {
            status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0]));
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_C75SS0_0)))
        {
            status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_C75SS0_0]));
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_C75SS1_0))&& 
           (Bootloader_socGetNumDspCores() == 2U))
        {
            status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_C75SS1_0]));
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS0_0)))
        {
            status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS0_0]));
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS0_1)))
        {
            status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS0_1]));
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS1_0))&& 
           (Bootloader_socGetNumMcuCores() > 2U))
        {
            status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS1_0]));
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS1_1))&& 
           (Bootloader_socGetNumMcuCores() > 3U))
        {
            status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS1_1]));
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    Bootloader_close(bootLoadParams->bootHandle);

    return status;
}
