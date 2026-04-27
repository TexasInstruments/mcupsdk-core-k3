/*
 *  Copyright (C) 2024-26 Texas Instruments Incorporated
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
#include <drivers/bootloader/bootloader_mcelf.h>
#include <drivers/hw_include/am275x/cslr_soc.h>
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

/**
 * \brief Reset the core tracking state
 *
 * This function resets the internal tracking of which cores have been run.
 * This can be useful in scenarios where the bootloader needs to be restarted
 * or when cores need to be re-run.
 */
void App_resetCoreTrackingState(void);

/**
 * \brief Load the SSO (Shared Static Object) image into shared memory
 *
 * Parses and loads all ELF segments from the SSO image to their physical
 * addresses in SSO_SHM.  Unlike App_loadImages, this function does NOT
 * track or boot any CPU core — the SSO contains shared code/data only.
 * Must be called before booting any per-core image that references SSO symbols.
 *
 * \param bootHandle  Bootloader handle already opened for the SSO instance
 * \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise
 */
int32_t App_loadSSOImage(Bootloader_Handle bootHandle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Static variable to track cores that have already been run */
static uint32_t gCoresAlreadyRun = 0U;

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
            /* Check if core has already been run */
            if(!(gCoresAlreadyRun & (1U << CSL_CORE_ID_HSM_M4FSS0_0)))
            {
                status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0]));
                if(status == SystemP_SUCCESS)
                {
                    /* Mark core as already run */
                    gCoresAlreadyRun |= (1U << CSL_CORE_ID_HSM_M4FSS0_0);
                }
            }
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_C75SS0_0)))
        {
            /* Check if core has already been run */
            if(!(gCoresAlreadyRun & (1U << CSL_CORE_ID_C75SS0_0)))
            {
                status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_C75SS0_0]));
                if(status == SystemP_SUCCESS)
                {
                    /* Mark core as already run */
                    gCoresAlreadyRun |= (1U << CSL_CORE_ID_C75SS0_0);
                }
            }
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_C75SS1_0))&& 
           (Bootloader_socGetNumDspCores() == 2U))
        {
            /* Check if core has already been run */
            if(!(gCoresAlreadyRun & (1U << CSL_CORE_ID_C75SS1_0)))
            {
                status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_C75SS1_0]));
                if(status == SystemP_SUCCESS)
                {
                    /* Mark core as already run */
                    gCoresAlreadyRun |= (1U << CSL_CORE_ID_C75SS1_0);
                }
            }
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS0_0)))
        {
            /* Check if core has already been run */
            if(!(gCoresAlreadyRun & (1U << CSL_CORE_ID_R5FSS0_0)))
            {
                status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS0_0]));
                if(status == SystemP_SUCCESS)
                {
                    /* Mark core as already run */
                    gCoresAlreadyRun |= (1U << CSL_CORE_ID_R5FSS0_0);
                }
            }
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS0_1)))
        {
            /* Check if core has already been run */
            if(!(gCoresAlreadyRun & (1U << CSL_CORE_ID_R5FSS0_1)))
            {
                status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS0_1]));
                if(status == SystemP_SUCCESS)
                {
                    /* Mark core as already run */
                    gCoresAlreadyRun |= (1U << CSL_CORE_ID_R5FSS0_1);
                }
            }
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS1_0))&& 
           (Bootloader_socGetNumMcuCores() > 2U))
        {
            /* Check if core has already been run */
            if(!(gCoresAlreadyRun & (1U << CSL_CORE_ID_R5FSS1_0)))
            {
                status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS1_0]));
                if(status == SystemP_SUCCESS)
                {
                    /* Mark core as already run */
                    gCoresAlreadyRun |= (1U << CSL_CORE_ID_R5FSS1_0);
                }
            }
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_R5FSS1_1))&& 
           (Bootloader_socGetNumMcuCores() > 3U))
        {
            /* Check if core has already been run */
            if(!(gCoresAlreadyRun & (1U << CSL_CORE_ID_R5FSS1_1)))
            {
                status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_R5FSS1_1]));
                if(status == SystemP_SUCCESS)
                {
                    /* Mark core as already run */
                    gCoresAlreadyRun |= (1U << CSL_CORE_ID_R5FSS1_1);
                }
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    Bootloader_close(bootLoadParams->bootHandle);

    return status;
}

void App_resetCoreTrackingState(void)
{
    gCoresAlreadyRun = 0U;
}

int32_t App_loadSSOImage(Bootloader_Handle bootHandle)
{
    int32_t status = SystemP_FAILURE;
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Config *bootConfig;

    if(bootHandle != NULL)
    {
        bootConfig = (Bootloader_Config *)bootHandle;
        bootConfig->coresPresentMap = 0;
        bootConfig->skipCpuInit     = 1U;
        Bootloader_BootImageInfo_init(&bootImageInfo);

        status = Bootloader_parseAndLoadMultiCoreELF(bootHandle, &bootImageInfo);
        if(SystemP_SUCCESS != status)
        {
            DebugP_logError("SSO image load failed !!!\r\n");
        }
    }

    return status;
}
