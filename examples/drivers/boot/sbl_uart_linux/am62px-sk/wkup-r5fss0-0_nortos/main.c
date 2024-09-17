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
#include <string.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/bootloader.h>
#include <drivers/pinmux.h>
#include <drivers/gtc.h>
#include <drivers/bootloader/bootloader_xmodem.h>
#include <drivers/bootloader/bootloader_buf_io.h>

#define BOOTLOADER_UART_STATUS_LOAD_SUCCESS           (0x53554343) /* SUCC */
#define BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL          (0x4641494C) /* FAIL */
#define BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED (0x45584344) /* EXCD */
#define BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH  (4) /* bytes */

#define BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS (5)

#define BOOTLOADER_APPIMAGE_MAX_FILE_SIZE (0x2000000) /* Size of section DDR specified in linker.cmd */
uint8_t gAppImageBuf[BOOTLOADER_APPIMAGE_MAX_FILE_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

uint8_t gEndOfFilesTransferWord[BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH] = {0x45,0x4F,0x46,0x54}; /* Contain Magic word Indicating End Of File Transfer(EOFT) */

extern Bootloader_MemArgs gBootloader0Args;
extern Bootloader_MemArgs gBootloader1Args;
extern Bootloader_MemArgs gBootloader2Args;

/* Workaround to initialize MMC SD Pinmux (Later will be done in SPL) */
static Pinmux_PerCfg_t gPinMuxMMCSDCfg[] = {
            /* MMC1 pin config */
    /* MMC1_CLK -> MMC1_CLK (B22) */
    {
        PIN_MMC1_CLK,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_CMD -> MMC1_CMD (A21) */
    {
        PIN_MMC1_CMD,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_DAT0 -> MMC1_DAT0 (A22) */
    {
        PIN_MMC1_DAT0,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_DAT1 -> MMC1_DAT1 (B21) */
    {
        PIN_MMC1_DAT1,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_DAT2 -> MMC1_DAT2 (C21) */
    {
        PIN_MMC1_DAT2,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_DAT3 -> MMC1_DAT3 (D22) */
    {
        PIN_MMC1_DAT3,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },
    /* MMC1_SDCD -> MMC1_SDCD (D17) */
    {
        PIN_MMC1_SDCD,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE )
    },

    {PINMUX_END, PINMUX_END}
};

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
int32_t App_loadImages(Bootloader_LoadImageParams *bootLoadParams)
{
	int32_t status = SystemP_FAILURE;
    Bootloader_Config *bootConfig;

    if(bootLoadParams->bootHandle  != NULL)
    {
        bootConfig = (Bootloader_Config *)bootLoadParams->bootHandle;
        bootConfig->coresPresentMap = 0;
        status = Bootloader_parseMultiCoreAppImage(bootLoadParams->bootHandle, &bootLoadParams->bootImageInfo);

        /* Load CPUs */
        if((status == SystemP_SUCCESS) && Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_MCU_R5FSS0_0))
        {
            if(!Bootloader_socIsMCUResetIsoEnabled())
            {
                (&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);
                Bootloader_profileAddCore(CSL_CORE_ID_MCU_R5FSS0_0);
                status = Bootloader_loadCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                if(status == SystemP_SUCCESS)
                {
                    Bootloader_profileAddProfilePoint("MCU R5 Image Load");
                    bootLoadParams->coreId = CSL_CORE_ID_MCU_R5FSS0_0;
                    bootLoadParams->loadStatus = BOOTLOADER_IMAGE_LOADED;
                }
                else
                {
                    Bootloader_powerOffCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));
                }
            }
            return status;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_A53SS0_0)))
		{
			(&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_A53SS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_A53SS0_0);
			Bootloader_profileAddCore(CSL_CORE_ID_A53SS0_0);
            status = Bootloader_loadCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_A53SS0_0]));
            if(status == SystemP_SUCCESS)
            {
                Bootloader_profileAddProfilePoint("A53 Image Load");
                bootLoadParams->coreId  = CSL_CORE_ID_A53SS0_0;
                bootLoadParams->loadStatus  = BOOTLOADER_IMAGE_LOADED;
            }
            else
            {
                Bootloader_powerOffCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_A53SS0_0]));
            }
            return status;
        }

        if((SystemP_SUCCESS == status) && (TRUE == Bootloader_isCorePresent(bootLoadParams->bootHandle, CSL_CORE_ID_WKUP_R5FSS0_0)))
        {
            (&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_WKUP_R5FSS0_0);
            Bootloader_profileAddCore(CSL_CORE_ID_WKUP_R5FSS0_0);
            status = Bootloader_loadSelfCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_WKUP_R5FSS0_0]));
            if(status == SystemP_SUCCESS)
            {
                Bootloader_profileAddProfilePoint("DM R5 Image Load");
                bootLoadParams->coreId = CSL_CORE_ID_WKUP_R5FSS0_0;
                bootLoadParams->loadStatus = BOOTLOADER_IMAGE_LOADED;
            }
            return status;
        }
    }

    return SystemP_SUCCESS;
}

void App_runCpus(Bootloader_LoadImageParams *bootLoadParams)
{
	int32_t status = SystemP_FAILURE;
    int8_t coreId = bootLoadParams->coreId;

    if(coreId != CSL_CORE_ID_WKUP_R5FSS0_0)
    {
        if(bootLoadParams->loadStatus == BOOTLOADER_IMAGE_LOADED)
        {
            status = Bootloader_runCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[coreId]));
            if(status == SystemP_FAILURE)
            {
                Bootloader_powerOffCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[coreId]));
            }
        }
        Bootloader_close(bootLoadParams->bootHandle);
    }
}

int main()
{
    int32_t status;

    Bootloader_socWaitForFWBoot();
    status = Bootloader_socOpenFirewalls();

    DebugP_assertNoLog(status == SystemP_SUCCESS);
    System_init();
    Board_init();
    Drivers_open();

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);

    if(SystemP_SUCCESS == status)
    {
        uint32_t fileSize;
        uint32_t response = BOOTLOADER_UART_STATUS_LOAD_SUCCESS;
        Bootloader_LoadImageParams bootArray[CONFIG_BOOTLOADER_NUM_INSTANCES];

        for(uint8_t inst = 0; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
        {
            Bootloader_Params_init(&bootArray[inst].bootParams);
            Bootloader_BootImageInfo_init(&bootArray[inst].bootImageInfo);
            bootArray[inst].bootParams.bufIoTempBuf     = gAppImageBuf;
            bootArray[inst].bootParams.bufIoTempBufSize = BOOTLOADER_APPIMAGE_MAX_FILE_SIZE;
            bootArray[inst].bootParams.bufIoDeviceIndex = CONFIG_UART0;
            bootArray[inst].bootParams.memArgsAppImageBaseAddr = (uintptr_t)gAppImageBuf;
            bootArray[inst].bootHandle = Bootloader_open(inst, &bootArray[inst].bootParams);

            if(BOOTLOADER_MEDIA_MEM == Bootloader_getBootMedia(bootArray[inst].bootHandle))
            {
                /* Xmodem Receive */
                status = Bootloader_xmodemReceive(CONFIG_UART0, gAppImageBuf, BOOTLOADER_APPIMAGE_MAX_FILE_SIZE, &fileSize);

                if(SystemP_SUCCESS == status && fileSize == BOOTLOADER_APPIMAGE_MAX_FILE_SIZE)
                {
                    /* A file larger than 384 KB was sent, and xmodem probably dropped bytes */
                    status = SystemP_FAILURE;

                    /* Send response to the script that file size exceeded */
                    uint32_t response;
                    response = BOOTLOADER_UART_STATUS_APPIMAGE_SIZE_EXCEEDED;

                    Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
                }

                if(SystemP_SUCCESS == status)
                {
                    if(bootArray[inst].bootHandle != NULL)
                    {
                        status = App_loadImages(&bootArray[inst]);
                    }

                    if(status != SystemP_SUCCESS)
                    {
                        response = BOOTLOADER_UART_STATUS_LOAD_CPU_FAIL;
                    }

                    Bootloader_xmodemTransmit(CONFIG_UART0, (uint8_t *)&response, 4);
                }
            }
        }

        if(SystemP_SUCCESS == status)
        {
            /* Xmodem Receive */
            status = Bootloader_xmodemReceive(CONFIG_UART0, gAppImageBuf, BOOTLOADER_APPIMAGE_MAX_FILE_SIZE, &fileSize);

            if(SystemP_SUCCESS == status && memcmp(gAppImageBuf, gEndOfFilesTransferWord, BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH) == 0)
            {
                /* Delay 5 seconds for the user to connect to UART before the CPUs start running */
                ClockP_sleep(BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS);
            }

            /* Initialize GTC by enabling using Syscfg */

            /* Change the dev stat register to SD card bootmode so that SPL loads uBoot and linux kernel from SD card */
	        SOC_setDevStat(SOC_BOOTMODE_MMCSD);

            /* Enable pinmux for MMCSD (Workaround as MMC SD pinmux is not initialized in A53 SPL) */
            Pinmux_config(gPinMuxMMCSDCfg, PINMUX_DOMAIN_ID_MAIN);

            /* Unlock all the control MMRs. Linux/U-boot expects all the MMRs to be unlocked */
            SOC_unlockAllMMR();

            if(SystemP_SUCCESS == status && bootArray[CONFIG_BOOTLOADER_DM].loadStatus == BOOTLOADER_IMAGE_LOADED)
            {
                for(uint8_t inst = 0; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
                {
		            App_runCpus(&bootArray[inst]);
                }
            }
        }
    }

    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    /* Call DPL deinit to close the tick timer and disable interrupts before jumping to DM*/
    Dpl_deinit();

    Bootloader_JumpSelfCpu();

    Drivers_close();
    Board_deinit();
    System_deinit();

    return 0;
}

