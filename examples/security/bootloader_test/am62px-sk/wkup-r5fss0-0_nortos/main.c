/*
 *  Copyright (C) 2024-2026 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Size of memory chunk to be read from Flash */
#define SECURITY_BOOTAPP_IMAGE_READ_SIZE                (2U*1024U*1024U)

/*
 * Timeout for the PBIST/LBIST completion
 */
#define SDL_BIST_MAX_TIMEOUT_VALUE       (10000000u)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                   External Function Declarations                           */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                   Internal Function Declarations                           */
/* ========================================================================== */

/*  In this sample bootloader, we load appimages for RTOS/Baremetal and A53 at different offset
 *   i.e the appimage for RTOS/Baremetal (for MCU R5) is flashed in flash
 *
 *   When flashing make sure to flash images to below offset using the flash tool.
 *
 *   RTOS/Baremetal appimage (MCU R5 cores) flash at offset 0x100000 of flash
 */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

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

int32_t App_readImageToDdr(Bootloader_Handle handle)
{
    int32_t status = SystemP_FAILURE;
    Bootloader_Config *config = (Bootloader_Config *)handle;
    Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)(config->args);

    /* Read image from flash to DDR memory */
    status = Flash_read(gFlashHandle[CONFIG_FLASH_SBL], flashArgs -> appImageOffset, gAppimage, SECURITY_BOOTAPP_IMAGE_READ_SIZE);

    return status;
}

int32_t App_loadImages(Bootloader_LoadImageParams *bootLoadParams)
{
	int32_t status = SystemP_FAILURE;
    Bootloader_Config *bootConfig;

    if(bootLoadParams->bootHandle != NULL)
    {
        bootConfig = (Bootloader_Config *)bootLoadParams->bootHandle;
        bootConfig->coresPresentMap = 0;

        (&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0].clkHz = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MCU_R5FSS0_0);

        status = Bootloader_loadCpu(bootLoadParams->bootHandle, &((&bootLoadParams->bootImageInfo)->cpuInfo[CSL_CORE_ID_MCU_R5FSS0_0]));

        if(status == SystemP_SUCCESS)
        {
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

int32_t App_runCpus(Bootloader_LoadImageParams *bootLoadParams)
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

    return status;
}

int32_t App_boardDriversOpen()
{
    int32_t status = SystemP_SUCCESS;

    gFlashHandle[CONFIG_FLASH_SBL] = Flash_open(CONFIG_FLASH_SBL, &gFlashParams[CONFIG_FLASH_SBL]);
    if(NULL == gFlashHandle[CONFIG_FLASH_SBL])
    {
        DebugP_logError("FLASH open failed for instance %d !!!\r\n", CONFIG_FLASH_SBL);
        status = SystemP_FAILURE;
    }

    return status;
}

void App_driversOpen()
{
    gOspiHandle[CONFIG_OSPI_SBL] = OSPI_open(CONFIG_OSPI_SBL, &gOspiParams[CONFIG_OSPI_SBL]);
    if(NULL == gOspiHandle[CONFIG_OSPI_SBL])
    {
        DebugP_logError("OSPI open failed for instance %d !!!\r\n", CONFIG_OSPI_SBL);
    }

    gUartHandle[CONFIG_UART_SBL] = UART_open(CONFIG_UART_SBL, &gUartParams[CONFIG_UART_SBL]);
    if(NULL == gUartHandle[CONFIG_UART_SBL])
    {
        DebugP_logError("UART open failed for instance %d !!!\r\n", CONFIG_UART_SBL);
    }
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

int main()
{
    int32_t status;

    Bootloader_socWaitForFWBoot();

    System_init();
    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    status = Bootloader_socOpenFirewalls();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    /* wait for PBIST completion */
    status = App_waitForMcuPbist();

    Board_init();

    Drivers_open();

    App_driversOpen();

    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);

    status = App_boardDriversOpen();
    DebugP_assert(status == SystemP_SUCCESS);

    if(SystemP_SUCCESS == status)
    {
        Bootloader_LoadImageParams bootArray;
        uint64_t imageAddress;

        Bootloader_Params_init(&bootArray.bootParams);
        Bootloader_BootImageInfo_init(&bootArray.bootImageInfo);
        bootArray.bootHandle = Bootloader_open(CONFIG_BOOTLOADER_FLASH_MCU, &bootArray.bootParams);

        if(bootArray.bootHandle != NULL)
        {
            uint32_t certLoadAddr = (uint32_t)gAppimage;
            /* Copy image to ddr, decryption can't be done in flash */
            status = App_readImageToDdr(bootArray.bootHandle);

            if(status != SystemP_SUCCESS)
            {
                DebugP_log("Failed to read image from Flash\r\n");
            }
            else
            {
                struct tisci_msg_proc_auth_boot_req authReq;
                struct tisci_msg_proc_auth_boot_resp authResp = {0};

                /* Request TIFS (SYSFW) to authenticate (and decrypt if mentioned in the x509 cert) the image */
                authReq.certificate_address_hi = 0U;
                authReq.certificate_address_lo = certLoadAddr;

                status = Sciclient_procBootAuthAndStart(&authReq, &authResp, SystemP_WAIT_FOREVER);
                /**
                 *  Image informations are obtained as a response from the Sciclient_procBootAuthAndStart api after the authentication and decryption
                 */
                imageAddress = ((authResp.image_address_hi << 31) | (authResp.image_address_lo));

                DebugP_log("Image residing at address: 0x%llx \r\n",imageAddress);
                DebugP_log("Image size: 0x%x \r\n",(authResp.image_size));

                if(status == SystemP_SUCCESS)
                {
                    ((Bootloader_Config *)bootArray.bootHandle)->scratchMemPtr = gAppimage;
                    status = Bootloader_parseAppImage(bootArray.bootHandle, &bootArray.bootImageInfo);

                    if(status != SystemP_SUCCESS )
                    {
                        DebugP_log("Failed to parse multicore app image!!\r\n");
                    }
                }
                else
                {
                    DebugP_log("Failed to authenticate image\r\n");
                }
            }
            if(status == SystemP_SUCCESS)
            {
                /* Load CPUs*/
                status = App_loadImages(&bootArray);

                if( status != SystemP_SUCCESS)
                {
                    DebugP_log("Image load failed!!\r\n");
                }
            }
            if( status == SystemP_SUCCESS)
            {
                /* Run CPUs*/
                status = App_runCpus(&bootArray);

                if( status != SystemP_SUCCESS)
                {
                    DebugP_log("CPU run failed!!\r\n");
                }
            }
        }
        else
        {
            status = SystemP_FAILURE;
            DebugP_log("Invalid  arguments!!!\r\n");
        }

    }

    if(status == SystemP_SUCCESS )
    {
        DebugP_log("Image load successful!!\r\n");
    }

    Board_driversClose();
    Drivers_close();

    return 0;
}
