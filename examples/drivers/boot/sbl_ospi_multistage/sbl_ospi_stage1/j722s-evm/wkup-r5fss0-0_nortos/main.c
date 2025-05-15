/*
 *  Copyright (C) 2023-25 Texas Instruments Incorporated
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

#include <stdlib.h>
#include "ti_board_config.h"
#include "ti_board_open_close.h"
#include "ti_drivers_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * This buffer needs to be defined for OSPI NOR boot in case of HS device for
 * image authentication.
 * The size of the buffer should be large enough to accomodate the appimage.
 */
uint8_t gAppImage[0x80000U] __attribute__ ((section (".bss.app"), aligned (128U)));

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Call this API to stop the booting process and spin, so that you can connect a
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1U;
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
            bootImageInfo->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_WKUP_R5FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_WKUP_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootHandle, &(bootImageInfo->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0]));
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

    Board_init();
    Bootloader_profileAddProfilePoint("Board_init");

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");

    flashFixUpOspiBoot(gOspiHandle[CONFIG_OSPI_SBL], gFlashHandle[CONFIG_FLASH_SBL]);

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("Board_driversOpen");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_BootImageInfo bootImageInfoDM;
        Bootloader_Params bootParamsDM;
        Bootloader_Handle bootHandleDM;

        Bootloader_Params_init(&bootParamsDM);

        Bootloader_BootImageInfo_init(&bootImageInfoDM);

        bootHandleDM = Bootloader_open(CONFIG_BOOTLOADER_FLASH_SBL, &bootParamsDM);

        if(SystemP_SUCCESS == status)
        {
            if(bootHandleDM != NULL)
            {
                ((Bootloader_Config *)bootHandleDM)->scratchMemPtr = gAppImage;
                status = App_loadSelfcoreImage(bootHandleDM, &bootImageInfoDM);
                Bootloader_profileAddProfilePoint("App_loadSelfcoreImage");
            }
        }

        Bootloader_profileUpdateAppimageSize(Bootloader_getMulticoreImageSize(bootHandleDM));
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI_SBL]));

        if(SystemP_SUCCESS == status)
        {
            /* Print SBL log as Linux prints log to the same UART port */
            Bootloader_profilePrintProfileLog();
            DebugP_log("Image loading done, switching to application ...\r\n");
            DebugP_log("Starting 2nd stage bootloader\r\n");
            UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);
        }

    }

    if(status != SystemP_SUCCESS )
    {
        DebugP_logError("SBL stage 1 failed!!\r\n");
    }

    Board_driversClose();
    Drivers_close();

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to Stage2 */
    Dpl_deinit();

    Bootloader_socWriteSBLBootMagicNum();

    Board_deinit();

    Bootloader_JumpSelfCpu();

    /* Jump to CPU above it to prevent DDR clock disable in it. */
    System_deinit();

    return 0;
}

void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle)
{
    /*
     *  In Fast XSPI mode, reintialization is not required unless
     *  user configures it or PHY configuration failed
     */
    if(SystemP_SUCCESS != OSPI_skipTuning(oHandle))
    {
        OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(8,8,8,1));
        OSPI_enableDDR(oHandle);
        OSPI_setDualOpCodeMode(oHandle);
        Flash_reset(fHandle);
        OSPI_enableSDR(oHandle);
        OSPI_clearDualOpCodeMode(oHandle);
        OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(1,1,1,0));
    }

}
