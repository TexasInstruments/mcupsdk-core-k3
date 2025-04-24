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


#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/device_manager/sciclient.h>
#include <drivers/bootloader.h>
#include <drivers/bootloader/bootloader_xmodem.h>

#define BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS          (5)
#define BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH  (4) /* bytes */
#define BOOTLOADER_APP_IMAGE_LOADED                   (1)

#define SCRATCH_BUFFER_SIZE                           (0x2000U) /*Size of binary metadata*/

uint8_t gAppImageBuf[SCRATCH_BUFFER_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

uint8_t gEndOfFilesTransferWord[BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH] = {0x45,0x4F,0x46,0x54}; /* Contain Magic word Indicating End Of File Transfer(EOFT) */
uint8_t socCpuCores[CSL_CORE_ID_MAX]    = {0};
uint32_t coresPresentMap = 0U;

Bootloader_Handle bootHandle;
Bootloader_CpuInfo bootCpuInfo[CSL_CORE_ID_MAX];

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

void App_driversOpen()
{
    /* Open UART */
    gUartHandle[CONFIG_UART_SBL] = NULL;

    gUartHandle[CONFIG_UART_SBL] = UART_open(CONFIG_UART_SBL, &gUartParams[CONFIG_UART_SBL]);
    if(NULL == gUartHandle[CONFIG_UART_SBL])
    {
        DebugP_logError("UART open failed for instance %d !!!\r\n", CONFIG_UART_SBL);
    }
}

void App_driversClose()
{
    UART_close(gUartHandle[CONFIG_UART_SBL]);
    gUartHandle[CONFIG_UART_SBL] = NULL;
}


int32_t App_runCpus(Bootloader_Handle bootHandle,Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t cpuId;

    for(cpuId = 0; cpuId < CSL_CORE_ID_MAX; cpuId++)
    {
        if(coresPresentMap & (0x1<<cpuId))
        {
            bootCpuInfo[cpuId] = bootImageInfo->cpuInfo[cpuId];
            status = Bootloader_runCpu(bootHandle, &bootCpuInfo[cpuId]);

            if(status != SystemP_SUCCESS)
            {
                DebugP_logError("App_runCpus failed for %s !!!\r\n", Bootloader_socGetCoreName(cpuId));
            }
        }
        else
        {
            Bootloader_powerOffCpu(bootHandle, &bootCpuInfo[cpuId]);
        }
    }

    return status;
}

void App_bootMultipleCoreUart()
{
    int32_t status;
    uint32_t appImageSize = 0;
    bool    bEndOfTransfer = false;

    DebugP_log("\r\n");
    DebugP_log("Starting UART Bootloader ... \r\n");

    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        uint32_t fileSize;

        Bootloader_BootImageInfo bootImageInfo;
		Bootloader_Params bootParams;
        Bootloader_Handle bootHandle;

        Bootloader_BootImageInfo_init(&bootImageInfo);
        Bootloader_Params_init(&bootParams);
        bootParams.memArgsAppImageBaseAddr = (uint32_t)(&gAppImageBuf);
        bootParams.bufIoDeviceIndex = CONFIG_UART_SBL;
        bootHandle = Bootloader_open(CONFIG_BOOTLOADER_APP, &bootParams);

        /*Loop through all the files*/
        while(bEndOfTransfer == false)
        {
            /* Receive the image metadata */
            status = Bootloader_xmodemReceive(CONFIG_UART_SBL, gAppImageBuf, SCRATCH_BUFFER_SIZE, &fileSize);
            CacheP_wb((void*)gAppImageBuf, (uint32_t)SCRATCH_BUFFER_SIZE, CacheP_TYPE_ALL);

            /* Check the end of transfer is reached using receieved chunk*/
            if(SystemP_SUCCESS == status && memcmp(gAppImageBuf, gEndOfFilesTransferWord, BOOTLOADER_END_OF_FILES_TRANSFER_WORD_LENGTH) == 0)
            {
                bEndOfTransfer = true;

                /* Delay 5 seconds for the user to connect to UART before the CPUs start running */
                ClockP_sleep(BOOTLOADER_UART_CPU_RUN_WAIT_SECONDS);

                /* Run CPUs */
                status = App_runCpus(bootHandle, &bootImageInfo);
                Bootloader_close(bootHandle);
            }

            /* File transfer end is not reached*/
            else
            {
                if(SystemP_SUCCESS == status)
                {
                    /* Parse the received metadata ,requests program segment from host and load to load addresses */
                    Bootloader_UartParseAndLoadMultiCoreELF(bootHandle, &bootImageInfo);
                    appImageSize += Bootloader_getMulticoreImageSize(bootHandle);

                    coresPresentMap |= ((Bootloader_Config *)bootHandle)->coresPresentMap;
                }
            }

        }

        Bootloader_profileUpdateAppimageSize(appImageSize);
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_UART, 0);
        if(status == SystemP_SUCCESS)
        {
            Bootloader_profileAddProfilePoint("SBL End");

            /* Use CONFIG_UART_SBL (UART0) for SBL logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

            /* Print SBL log  */
            Bootloader_profilePrintProfileLog();

            DebugP_log("Image loading done, switching to application ...\r\n");
            UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);

            /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_APP);
        }
    }

    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Some tests have failed!!\r\n");
    }
}


void sbl_uart_main(void * args)
{
    App_bootMultipleCoreUart();

    vTaskDelete(NULL);
}