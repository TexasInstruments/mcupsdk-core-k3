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


/*  In this sample bootloader, we load appimages for RTOS/Baremetal and Linux at different offset
    i.e the appimage for Linux (for A53) and RTOS/Baremetal (for R5, MCU R5) is flashed at different offset in flash

    Here at one flash offset, there is a multi-core .appimage that holds RPRC for MCU R5 and R5
    and another .appimage that holds the linux binaries(ATF, OPTEE, A53-SPL) at another offset.

    When flashing make sure to flash images to below offset using the flash tool.

    RTOS/Baremetal appimage (for R5, MCU R5 cores) flash at offset 0x80000 of flash
    Linux appimage (for A53) flash at offset 0x800000 of flash
*/
/* This buffer needs to be defined for OSPI nand boot in case of HS device for
   image authentication
   The size of the buffer should be large enough to accomodate the appimage */
uint8_t gAppimage[0x800000] __attribute__ ((section (".app"), aligned (128)));



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

int32_t App_loadSelfcoreImage(Bootloader_Handle bootHandle, Bootloader_BootImageInfo *bootImageInfo)
{
	int32_t status = SystemP_FAILURE;

    if(bootHandle != NULL)
    {
        status = Bootloader_parseMultiCoreAppImage(bootHandle, bootImageInfo);

        if(status == SystemP_SUCCESS)
        {
            /* Set clocks for self cluster */
            bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_R5FSS0_0);

            /* Reset self cluster, both Core0 and Core 1. Init RAMs and load the app  */
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0]));
        }
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

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");

    DebugP_log("\r\n");
    DebugP_log("Starting NULL Bootloader ... \r\n");

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

        bootHandle = Bootloader_open(CONFIG_BOOTLOADER0, &bootParams);
        bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_FLASH_DM, &bootParamsDM);

        if(bootHandle != NULL)
        {
            if(status == SystemP_SUCCESS)
            {
                if (!Bootloader_socIsMCUResetIsoEnabled())
                {
                    status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]);
                }
            }
            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_0]);
            }
            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS0_1]);
            }
            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_0]);
            }
            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_A53SS1_1]);
            }
            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_C75SS0_0]);
            }
            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_bootCpu(bootHandle, &bootImageInfo.cpuInfo[CSL_CORE_ID_HSM_M4FSS0_0]);
            }
        }

        if(SystemP_SUCCESS == status)
		{
            if(bootHandleDM != NULL)
            {
                ((Bootloader_Config *)bootHandleDM)->scratchMemPtr = gAppimage;
                status = App_loadSelfcoreImage(bootHandleDM, &bootImageInfoDM);
                Bootloader_profileAddProfilePoint("App_loadSelfcoreImage");
                Bootloader_profileAddCore(CSL_CORE_ID_R5FSS0_0);
            }
        }




        Bootloader_close(bootHandle);
    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    Board_driversClose();

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to DM*/
    Dpl_deinit();

    Bootloader_JumpSelfCpu();

    Drivers_close();
    System_deinit();

    return 0;
}
