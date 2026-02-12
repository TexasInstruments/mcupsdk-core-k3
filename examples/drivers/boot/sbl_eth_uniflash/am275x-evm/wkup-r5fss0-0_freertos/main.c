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

/**
 *
 * This bootloader does SOC initializations in addition to providing an
 * option to receive an application image via UDP over ethernet and flashing
 * the received application image to 0x80000 location in the QSPI Flash and
 * attempts to boot the same multicore appimage present at 0x80000 location
 * in the QSPI Flash after successful completion of the image transferred
 * over ethernet.
 *
 */
#include <drivers/bootloader.h>
#include <drivers/device_manager/sciclient.h>
#include <drivers/device_manager/sciserver/sciserver_init.h>
#include <drivers/pinmux.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <kernel/dpl/DebugP.h>
#include "sbl_enet.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Task priority */
#define TASK_PRI_MAIN_THREAD  (configMAX_PRIORITIES-1)
#define TASK_PRI_BOOT_THREAD  (configMAX_PRIORITIES-1)

/* Task stack size */
#define TASK_SIZE (2*16384U/sizeof(configSTACK_DEPTH_TYPE))
#define SBL_OVER_ETHERNET 1U

/* Stack size allocated for the sciserver task */
#define SCISERVER_TASK_STACK_SIZE                   (2U*1024U)

/* Stack memory alignment requirement for the sciserver task */
#define SCISERVER_TASK_STACK_ALIGNMENT              (32)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t gGpioBaseAddr = ENET_TRANSFER_START_BTN_BASE_ADDR;
uint32_t pinNum = ENET_TRANSFER_START_BTN_PIN;

StackType_t gMainTaskStack[TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gMainTaskObj;
TaskHandle_t gMainTask;

StackType_t gBootTaskStack[TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gBootTaskObj;
TaskHandle_t gBootTask;

/* Stack buffers for user high and low priority tasks */
uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserHiTaskStack[SCISERVER_TASK_STACK_SIZE];
uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserLoTaskStack[SCISERVER_TASK_STACK_SIZE];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * This function will receive app image from enet_uniflash.py script over Ethernet
 */
uint32_t receiveAppImgOverEnet();

void sbl_eth_uniflash_main(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void main_thread(void *args)
{
    int32_t status = SystemP_SUCCESS;

    /* Configure sciserver task parameters */
    Sciserver_TirtosCfgPrms_t sciserverCfg = {0};
    sciserverCfg.hiTaskStack    =   gUserHiTaskStack;
    sciserverCfg.loTaskStack    =   gUserLoTaskStack;
    sciserverCfg.taskStackSize  =   SCISERVER_TASK_STACK_SIZE;

    Drivers_open();
    Bootloader_profileAddProfilePoint("Drivers_open");

    DebugP_log("\r\n");
    DebugP_log("Starting OSPI Bootloader ... \r\n");
    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);

    Bootloader_profileAddProfilePoint("Board_driversOpen");

    sciServer_init(&sciserverCfg);
    Bootloader_profileAddProfilePoint("sciServer_init");

    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    flashFixUpOspiBoot(gOspiHandle[CONFIG_OSPI_SBL], gFlashHandle[CONFIG_FLASH_SBL]);

    status = App_boardDriversOpen();
    DebugP_assertNoLog(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("SBL Board_driversOpen");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    /* Receive application image via UDP over ethernet */
    status = receiveAppImgOverEnet();

    if(status != SystemP_SUCCESS )
    {
        DebugP_log("Failed to Receive Image from Ethernet, Timeout!!!\r\n");
    }

    /* Close board and flash drivers */
    Board_driversClose();
    /* Close drivers */
    Drivers_close();

    vTaskDelete(NULL);
}

int main()
{
    int32_t status = SystemP_SUCCESS;

    Bootloader_profileReset();

    Bootloader_socWaitForFWBoot();
    status = Bootloader_socOpenFirewalls();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    Bootloader_profileAddProfilePoint("TIFS init");

    /* init SOC specific modules */
    System_init();
    Bootloader_profileAddProfilePoint("System_init");
    Board_init();
    Bootloader_profileAddProfilePoint("Board_init");

    gMainTask = xTaskCreateStatic( main_thread,   /* Pointer to the function that implements the task. */
                                  "main_thread", /* Text name for the task.  This is to facilitate debugging only. */
                                  TASK_SIZE,  /* Stack depth in units of StackType_t typically uint32_t on 32b CPUs */
                                  NULL,            /* We are not using the task parameter. */
                                  TASK_PRI_MAIN_THREAD,   /* task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest */
                                  gMainTaskStack,  /* pointer to stack base */
                                  &gMainTaskObj ); /* pointer to statically allocated task object memory */
    configASSERT(gMainTask != NULL);

    Bootloader_profileAddProfilePoint("FreeRtosTask Create");

    /* Start the scheduler to start the tasks executing. */
    vTaskStartScheduler();

    /* The following line should never be reached because vTaskStartScheduler()
    will only return if there was not enough FreeRTOS heap memory available to
    create the Idle and (if configured) Timer tasks.  Heap management, and
    techniques for trapping heap exhaustion, are described in the book text. */
    DebugP_assertNoLog(0);

    return 0;
}

/* SEND A UDP PACKET OVER ETHERNET */
uint32_t receiveAppImgOverEnet()
{
    int32_t status = SystemP_SUCCESS;
    uint8_t done = false;
    int32_t flashIteration = 0U;
    Bootloader_UniflashConfig uniflashConfig;
    Bootloader_UniflashResponseHeader respHeader;
    Bootloader_UniflashFileHeader *pktInfo;

    if(!done)
    {
        DebugP_log("\r\n[ ENETSBL ] Starting Ethernet Transfer ...\r\n");

        /* Initialize the C66x subsystem as the DSS_L3 memory is used to store the file to flash */
        Bootloader_socCpuPowerOnReset(CSL_CORE_ID_R5FSS0_0,NULL_PTR);

        /* Initialize sbl_enet config and setup ethernet peripheral */
        memset(&gEnetSBL_LLDObj, 0, sizeof(gEnetSBL_LLDObj));
        memset(&gEnetSBL_MetaObj, 0, sizeof(gEnetSBL_MetaObj));
        memset(&respHeader, 0, sizeof(respHeader));
        memset(&uniflashConfig, 0, sizeof(uniflashConfig));

        status = EnetSBL_setup();

        if(status == ENET_SOK)
        {
            /* Send ACK packet to let host know that EVM is linked up */
            respHeader.magicNumber = ENETSBL_HEADER_MGC_NUMBER;
            respHeader.statusCode = ENETSBL_HEADER_ACK;
            EnetSBL_txFlashResp(respHeader);
        }
        else if(status == ENET_ETIMEOUT)
        {
            DebugP_log("[ ENETSBL TIMEOUT ] Link Up Timeout. Please check ethernet cable connections.\r\n");
            done = true;
            status = SystemP_TIMEOUT;
        }

        while ((!done) && (flashIteration < ENETSBL_MAX_FILE_COUNT))
        {
            gFlashFileSize = 0U;
            flashIteration++;
            /* Run SBL application */
            status = EnetSBL_transferAppimage();
            if(gFlashFileSize >= BOOTLOADER_MAX_FILE_SIZE)
            {
                /* Possible overflow, send error to host side */
                status = SystemP_FAILURE;

                respHeader.magicNumber = BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER;
                respHeader.statusCode = BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR;

                EnetSBL_txFlashResp(respHeader);

                /* Exit due to possible error */
                done = 1U;
                DebugP_log("[ ENETSBL ERROR ] Overflow detected.\r\n");
                break;
            }

            if(status == ENET_SOK)
            {
                uniflashConfig.flashIndex = CONFIG_FLASH_SBL;
                uniflashConfig.buf = gFlashFileBuf;
                /* Actual fileSize will be parsed from the header */
                uniflashConfig.bufSize = 0;
                uniflashConfig.verifyBuf = gFlashVerifyBuf;
                uniflashConfig.verifyBufSize = BOOTLOADER_VERIFY_MAX_SIZE;

                /* Process the flash commands and return a response */
                status = Bootloader_uniflashProcessFlashCommands(&uniflashConfig, &respHeader);

                /* Exit if error or timeout; Send response to host */
                if (status != SystemP_SUCCESS)
                {
                    DebugP_log("[ ENETSBL ERROR ] Uniflash timeout error.\r\n");
                    done = 1U;
                    status = SystemP_FAILURE;
                }
                else
                {
                    DebugP_log("[ ENETSBL SUCCESS ] Ethernet Transfer Done.\r\n");

                    /* Print the Ethernet reception token */
                    pktInfo = (Bootloader_UniflashFileHeader*) &gFlashFileBuf;
                    status = EnetSBL_txFlashResp(respHeader);
                    DebugP_log("[ ENETSBL ] Packets Received   :  %d \r\n",ENET_SBL_PKT_CNT(pktInfo->rsv2));
                    DebugP_log("[ ENETSBL ] Total File Size    :  %d Bytes\r\n",pktInfo->actualFileSize);
                    DebugP_log("[ ENETSBL ] Flash Offset       :  0x%X\r\n\n",pktInfo->offset);
                    status = SystemP_SUCCESS;
                    if ((pktInfo->rsv2 >> 31) ==1U)
                    {
                        done = 1U;
                        break;
                    }
                }
            }
            else
            {
                DebugP_log("[ ENETSBL TIMEOUT ] Skipping enet transfer.\r\n");
                status = SystemP_FAILURE;
            }
        }

        /* Close */
        EnetSBL_destruct();
    }
    return status;
}
