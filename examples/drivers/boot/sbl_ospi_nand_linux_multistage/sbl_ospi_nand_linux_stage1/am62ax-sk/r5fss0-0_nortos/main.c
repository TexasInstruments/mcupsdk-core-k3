/*
 *  Copyright (C) 2018-2021 Texas Instruments Incorporated
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

#include <stdlib.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>
#include <drivers/pinmux.h>
#include <drivers/gtc.h>
#include <sdl/include/sdl_types.h>
#include <sdl/dpl/sdl_dpl.h>
#include <sdl/sdl_pbist.h>
#include <sdl/sdl_lbist.h>


/*  In this sample bootloader, we load appimages for RTOS/Baremetal and Linux at different offset
    i.e the appimage for Linux (for A53) and RTOS/Baremetal (for R5, MCU R5) is flashed at different offset in flash

    Here at one flash offset, there is a multi-core .appimage that holds RPRC for MCU R5 and R5
    and another .appimage that holds the linux binaries(ATF, OPTEE, A53-SPL) at another offset.

    When flashing make sure to flash images to below offset using the flash tool.

    RTOS/Baremetal appimage (MCU R5 cores) flash at offset 0x100000 of flash
    Linux appimage (for A53) flash at offset 0xC00000 of flash
*/

/*
 * Timeout for the PBIST/LBIST completion
 */
#define SDL_BIST_MAX_TIMEOUT_VALUE       (10000000u)

/* Enable/Disable MCU LBIST on SBL */
#define ENABLE_MCU_LBIST                 (0u)

void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle);

/* This buffer needs to be defined for OSPI nand boot in case of HS device for
   image authentication
   The size of the buffer should be large enough to accomodate the appimage */
uint8_t gAppimage[0x800000] __attribute__ ((section (".bss.app"), aligned (128)));

/* call this API to stop the booting process and spin, do that you can connect
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1;
    while(loop)
        ;
}

int32_t App_loadImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
        if (!Bootloader_socIsMCUResetIsoEnabled())
        {
            status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

            /* Load CPUs */
            if(status == SystemP_SUCCESS)
            {
                bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
            }
        }
        else
        {
            status = SystemP_SUCCESS;
        }
    }

    return status;
}

int32_t App_loadSelfcoreImage(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
        status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

        if(status == SystemP_SUCCESS)
        {
            bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_R5FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0]));
        }
    }

    return status;
}

int32_t App_loadLinuxImages(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
		status = Bootloader_parseAndLoadLinuxAppImage(bootHandle, bootImageInfo);

		if(status == SystemP_SUCCESS)
		{
			bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
			status = Bootloader_loadCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));
		}
	}

	return status;
}

int32_t App_runCpus(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if (!Bootloader_socIsMCUResetIsoEnabled())
    {
	    status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
    }
    else
    {
        status = SystemP_SUCCESS;
    }

	return status;
}

int32_t App_runLinuxCpu(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

	status = Bootloader_runCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_A53SS0_0]));

	return status;
}

int32_t App_waitForMcuPbist()
{
    int32_t status = SystemP_FAILURE;
    int32_t timeoutCount = 0;

    if (!Bootloader_socIsMCUResetIsoEnabled())
    {
        /* wait for the PBIST to be completed */
        while(timeoutCount < SDL_BIST_MAX_TIMEOUT_VALUE)
        {
            if(PBIST_DONE == SDL_SBL_PBIST_checkDone(SDL_PBIST_INST_MCU))
            {
                status = SystemP_SUCCESS;
                break;
            }
            timeoutCount++;
        }
    }
    else
    {
        status = SystemP_SUCCESS;
    }

    return status;
}

int32_t App_startMcuLbist()
{
    int32_t status = SystemP_FAILURE;

    /* Start LBIST if MCU reset isolation is not enabled */
    if (!Bootloader_socIsMCUResetIsoEnabled())
    {
        if (SDL_LBIST_selfTest(LBIST_MCU_R5F, SDL_LBIST_TEST) == SDL_PASS)
        {
            status = SystemP_SUCCESS;
        }
    }
    else
    {
        status = SystemP_SUCCESS;
    }
    return status;
}

int32_t App_waitForMcuLbist()
{
    int32_t status = SystemP_FAILURE;
    int32_t timeoutCount = 0;

    if (!Bootloader_socIsMCUResetIsoEnabled())
    {
        /* wait for the LBIST to be completed */
        while(timeoutCount < SDL_BIST_MAX_TIMEOUT_VALUE)
        {
            if(LBIST_DONE == SDL_LBIST_checkDone(LBIST_MCU_R5F))
            {
                status = SystemP_SUCCESS;
                break;
            }
            timeoutCount++;
        }

        if (status == SystemP_SUCCESS)
        {
            status = SDL_LBIST_selfTest(LBIST_MCU_R5F, SDL_LBIST_TEST_RELEASE);
        }
        timeoutCount = 0;

        while(timeoutCount < SDL_BIST_MAX_TIMEOUT_VALUE)
        {
            if(LBIST_DONE == SDL_LBIST_checkDone(LBIST_MCU_R5F))
            {
                status = SystemP_SUCCESS;
                break;
            }
            timeoutCount++;
        }
    }
    else
    {
        status = SystemP_SUCCESS;
    }

    return status;
}


int main()
{
    int32_t status;

    Bootloader_profileReset();

    Bootloader_socWaitForFWBoot();
    status = Bootloader_socOpenFirewalls();

    DebugP_assertNoLog(status == SystemP_SUCCESS);

    System_init();
    Bootloader_profileAddProfilePoint("System_init");

    Board_init();
    Bootloader_profileAddProfilePoint("Board_init");

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");

    flashFixUpOspiBoot(gOspiHandle[CONFIG_OSPI0], gFlashHandle[CONFIG_FLASH0]);

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("Board_driversOpen");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_BootImageInfo bootImageInfo;
		Bootloader_Params bootParams;
        Bootloader_Handle bootHandle;

        Bootloader_BootImageInfo bootImageInfoDM;
		Bootloader_Params bootParamsDM;
        Bootloader_Handle bootHandleDM;

        Bootloader_Params_init(&bootParams);
        Bootloader_Params_init(&bootParamsDM);

		Bootloader_BootImageInfo_init(&bootImageInfo);
        Bootloader_BootImageInfo_init(&bootImageInfoDM);

        bootHandle = Bootloader_open(CONFIG_BOOTLOADER_FLASH_MCU, &bootParams);
        bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_FLASH_SBL, &bootParamsDM);

        /* wait for PBIST completion */
        status = App_waitForMcuPbist();
        Bootloader_profileAddProfilePoint("App_waitForMcuPbist");

#if (ENABLE_MCU_LBIST == 1u)
        /* start MCU LBIST*/
        status = App_startMcuLbist();

        /* wait for LBIST completion */
        status = App_waitForMcuLbist();
        Bootloader_profileAddProfilePoint("App_waitForMcuLbist");
#endif

        if(SystemP_SUCCESS == status)
        {
            if(bootHandle != NULL)
            {
                ((Bootloader_Config *)bootHandle)->scratchMemPtr = gAppimage;
                status = App_loadImages(bootHandle, &bootImageInfo);
                Bootloader_profileAddProfilePoint("App_loadImages");
            }
        }

        if(SystemP_SUCCESS == status)
		{
            if(bootHandleDM != NULL)
            {
                ((Bootloader_Config *)bootHandleDM)->scratchMemPtr = gAppimage;
                status = App_loadSelfcoreImage(bootHandleDM, &bootImageInfoDM);
                Bootloader_profileAddProfilePoint("App_loadSelfcoreImage");
            }
        }

        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleDM) \
                                            + Bootloader_getMulticoreImageSize(bootHandle));
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI0]));

		if(SystemP_SUCCESS == status)
		{
			/* Print SBL log as Linux prints log to the same UART port */
			Bootloader_profilePrintProfileLog();
			DebugP_log("Image loading done, switching to application ...\r\n");
			DebugP_log("Starting MCU-r5f and 2nd stage bootloader\r\n");
			UART_flushTxFifo(gUartHandle[CONFIG_UART0]);
		}

        if(SystemP_SUCCESS == status)
		{
			status = App_runCpus(bootHandle, &bootImageInfo);
		}

        Bootloader_close(bootHandle);
    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to Stage2*/
    Dpl_deinit();

    Bootloader_JumpSelfCpu();

    Board_driversClose();
    Drivers_close();

    Board_deinit();
    System_deinit();

    return 0;
}

void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle)
{
    OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(1,1,8,0));
    OSPI_enableSDR(oHandle);
    OSPI_clearDualOpCodeMode(oHandle);
    Flash_reset(fHandle);
    OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(1,1,1,0));
}