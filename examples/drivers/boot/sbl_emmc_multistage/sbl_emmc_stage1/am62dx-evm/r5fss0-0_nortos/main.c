/*
 *  Copyright (C) 2018-2024 Texas Instruments Incorporated
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
#include <string.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>

/*  In this sample bootloader, we load appimages for RTOS/Baremetal at different offset
    i.e the appimage for  RTOS/Baremetal (for R5, MCU_R5, A53) is flashed at different offset in eMMC

    Here at one eMMC offset, there is a multi-core .appimage that holds RPRC for MCU_R5 and R5
    and another .appimage that holds the RTOS/Baremetal binaries at another offset.

    When flashing make sure to flash images to below offset using the flash tool.

    RTOS/Baremetal appimage (MCU_R5) flash at offset 0x100000 of eMMC
     RTOS/Baremetal appimage (for A53) flash at offset 0xC00000 of eMMC
*/

/* This buffer needs to be defined for eMMC boot in case of HS device for
   image authentication
   The size of the buffer should be large enough to accomodate the appimage */
uint8_t gAppimage[0x800000] __attribute__ ((section (".app"), aligned (4096)));

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
            bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_R5FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_R5FSS0_0]));
        }
    }

    return status;
}

void App_driversOpen()
{
    gMmcsdHandle[CONFIG_MMCSD_SBL] = MMCSD_open(CONFIG_MMCSD_SBL, &gMmcsdParams[CONFIG_MMCSD_SBL]);
    if(NULL == gMmcsdHandle[CONFIG_MMCSD_SBL])
    {
        DebugP_logError("MMCSD open failed for instance %d !!!\r\n", CONFIG_MMCSD_SBL);
    }

    gUartHandle[CONFIG_UART_SBL] = UART_open(CONFIG_UART_SBL, &gUartParams[CONFIG_UART_SBL]);
    if(NULL == gUartHandle[CONFIG_UART_SBL])
    {
        DebugP_logError("UART open failed for instance %d !!!\r\n", CONFIG_UART_SBL);
    }
}

void App_driversClose()
{
    MMCSD_close(gMmcsdHandle[CONFIG_MMCSD_SBL]);
    gMmcsdHandle[CONFIG_MMCSD_SBL] = NULL;
    MMCSD_deinit();

    UART_close(gUartHandle[CONFIG_UART_SBL]);
    gUartHandle[CONFIG_UART_SBL] = NULL;
}

int main()
{
    int32_t status;

    Bootloader_profileReset();

    Bootloader_socWaitForFWBoot();
    status = Bootloader_socOpenFirewalls();

    DebugP_assertNoLog(status == SystemP_SUCCESS);

    System_init();
    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();
    Bootloader_profileAddProfilePoint("System_init");

    Board_init();
    Bootloader_profileAddProfilePoint("Board_init");

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("Board_driversOpen");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_BootImageInfo bootImageInfoDM;
		Bootloader_Params bootParamsDM;
        Bootloader_Handle bootHandleDM;

        Bootloader_Params_init(&bootParamsDM);

        Bootloader_BootImageInfo_init(&bootImageInfoDM);

        bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_EMMC_SBL, &bootParamsDM);

        if(SystemP_SUCCESS == status)
		{
            if(bootHandleDM != NULL)
            {
                ((Bootloader_Config *)bootHandleDM)->scratchMemPtr = gAppimage;
                status = App_loadSelfcoreImage(bootHandleDM, &bootImageInfoDM);
                Bootloader_profileAddProfilePoint("App_loadSelfcoreImage");
            }
        }

        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleDM));
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_EMMC, MMCSD_getInputClk(gMmcsdHandle[CONFIG_MMCSD_SBL]));

		if(SystemP_SUCCESS == status)
		{
			/* Print SBL log to the same UART port */
			Bootloader_profilePrintProfileLog();
			DebugP_log("Image loading done, switching to application ...\r\n");
			DebugP_log("Starting 2nd stage bootloader\r\n");
			UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);
		}

    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("SBL stage 1 failed!!\r\n");
    }

    Board_driversClose();
    App_driversClose();
    Drivers_close();
    Board_deinit();

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to Stage2*/
    Dpl_deinit();

    Bootloader_JumpSelfCpu();

    System_deinit();

    return 0;
}
