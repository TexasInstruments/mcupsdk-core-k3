/*
 *  Copyright (C) 2025-2026 Texas Instruments Incorporated
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "ti_drivers_config.h"
#include <drivers/bootloader.h>
#include <drivers/bootloader/bootloader_uniflash.h>
#include <drivers/device_manager/sciclient.h>
#include <drivers/device_manager/sciserver/sciserver_init.h>
#include <drivers/pinmux.h>
#include "FreeRTOS.h"
#include "task.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Task priority */
#define TASK_PRI_MAIN_THREAD  (configMAX_PRIORITIES-1)
/* Task stack size */
#define TASK_SIZE (16384U/sizeof(configSTACK_DEPTH_TYPE))

/* Stack size allocated for the sciserver task */
#define SCISERVER_TASK_STACK_SIZE                   (2U*1024U)

/* Stack memory alignment requirement for the sciserver task */
#define SCISERVER_TASK_STACK_ALIGNMENT              (32)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


StackType_t gMainTaskStack[TASK_SIZE] __attribute__((aligned(32)));
StaticTask_t gMainTaskObj;
TaskHandle_t gMainTask;

/* Stack buffers for user high and low priority tasks */
uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserHiTaskStack[SCISERVER_TASK_STACK_SIZE];
uint8_t __attribute__((aligned(SCISERVER_TASK_STACK_ALIGNMENT))) gUserLoTaskStack[SCISERVER_TASK_STACK_SIZE];

#define FILE_MAX_SIZE  (0x200000)
uint8_t gFileBuf[FILE_MAX_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

#define VERIFY_BUF_MAX_SIZE (0x200000)
uint8_t gVerifyBuf[VERIFY_BUF_MAX_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));

#define INPUT_STR_MAX_LEN   (16u)
static char inputStr[INPUT_STR_MAX_LEN];

#define FILE_NAME_MAX_LEN   (384u)
static char filename[FILE_NAME_MAX_LEN];

char gMainMenu[] = {
    " \r\n"
    " \r\n"
    " ==================\r\n"
    " JTAG Uniflash Menu\r\n"
    " ==================\r\n"
    " \r\n"
    " 1: Erase Complete Flash\r\n"
    " 2: Write File to Flash and Verify\r\n"
    " 3: Verify file in Flash\r\n"
    " \r\n"
    " x: Exit\r\n"
    " \r\n"
    " Enter Choice: "
};

void app_main(void);
extern int32_t sciclient_set_boardcfg(void);
extern int32_t sciclient_load_sysfw(void);
extern int32_t app_system_init(void);

int32_t sbl_jtag_uniflash_load_file(char optype)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t offset;
    uint32_t fileSize;
    uint32_t eraseBlkSize;
    uint32_t flashSize;
    FILE *fp;

    DebugP_log("\r\n");
    DebugP_log(" Enter file name along with path to write or verify : ");
    gets(filename);
    fp = fopen(filename, "rb");
    if(fp == NULL)
    {   /* if file not present then exit */
        DebugP_log(" [FLASH WRITER] Unable to open file %s !!!\r\n", filename);
        status = SystemP_FAILURE;
    }
    if(status==SystemP_SUCCESS)
    {   /* if file size > buffer size then exit, we will load the file in one shot so
         * so file size has to be < buffer size
         */
        fseek(fp, 0, SEEK_END);
        fileSize = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        fclose(fp);

        if(fileSize > FILE_MAX_SIZE)
        {
            DebugP_log(" [FLASH WRITER] File is too large to flash !!!\r\n");
            status = SystemP_FAILURE;
        }
    }
    if(status==SystemP_SUCCESS)
    {
        DebugP_log(" Enter flash offset (in hex format) : ");
        gets(inputStr);
        offset = strtol(inputStr, NULL, INPUT_STR_MAX_LEN);
    }
    if(status==SystemP_SUCCESS)
    {
        Flash_Attrs *flashAttrs;
        flashAttrs = Flash_getAttrs(CONFIG_FLASH0);
        if(flashAttrs == NULL)
        {
            status=SystemP_FAILURE;
            DebugP_log(" [FLASH WRITER] Flash attributes are invalid !!!\r\n");
        }
        else
        {
            eraseBlkSize = flashAttrs->blockSize;
            flashSize = flashAttrs->flashSize;

            if( (offset % eraseBlkSize) != 0)
            {
                DebugP_log(" [FLASH WRITER] Flash offset MUST be multiple of erase block size of 0x%08x !!!\r\n",
                    eraseBlkSize
                    );
                status = SystemP_FAILURE;
            }
            if( (offset+fileSize) > flashSize)
            {
                DebugP_log(" [FLASH WRITER] Flash offset + file size MUST be <= flash size of %d bytes !!!\r\n",
                    flashSize
                    );
                status = SystemP_FAILURE;
            }
        }
    }
    if(status==SystemP_SUCCESS)
    {
        /* load file via CCS scripting console, since otherwise it is very slow */
        { /* convert \\ to / */
            uint32_t i = 0;
            while(filename[i]!=0)
            {
                if(filename[i]=='\\')
                    filename[i]='/';
                i++;
            }
        }
        /* clear buffer to reset stale data if any */
        memset(gFileBuf, 0, FILE_MAX_SIZE);

        /* Construct the header depending on the option provided so that Bootloader_uniflashProcessCommands can be used */
        Bootloader_UniflashFileHeader uniflashHeader;

        uniflashHeader.magicNumber = BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER;
        uniflashHeader.offset = offset;
        uniflashHeader.actualFileSize = fileSize;

        if(optype == '2')
        {
            /* Operation is FLASH */
            uniflashHeader.operationTypeAndFlags = BOOTLOADER_UNIFLASH_OPTYPE_FLASH;
        }
        else if(optype == '3')
        {
            /* Operation is FLASH VERIFY */
            uniflashHeader.operationTypeAndFlags = BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY;
        }
        else
        {
            /* Operation is invalid */
            uniflashHeader.operationTypeAndFlags = 0U;
        }

        if(uniflashHeader.operationTypeAndFlags == 0U)
        {
            status = SystemP_FAILURE;
        }
        else
        {
            /* Load the image after the header */
            memcpy(gFileBuf, (void *)&uniflashHeader, sizeof(uniflashHeader));

            DebugP_log(" Enter below command in CCS scripting console to load the file data to memory.\r\n");
            DebugP_log(" AFTER the file load is done, enter '1' to continue ...\r\n");
            DebugP_log("\r\n");
            DebugP_log(" loadRaw(0x%08x, 0, \"%s\", 32, false);",
                gFileBuf + sizeof(uniflashHeader), filename);
            DebugP_log("\r\n");

            /* wait for user input */
            do {
                gets(inputStr);
            } while(inputStr[0]!='1');

            /* Process the buffer */
            Bootloader_UniflashConfig uniflashConfig;
            Bootloader_UniflashResponseHeader respHeader;

            uniflashConfig.flashIndex = CONFIG_FLASH0;
            uniflashConfig.buf = gFileBuf;
            uniflashConfig.bufSize = 0U; /* Actual filesize is part of the header */
            uniflashConfig.verifyBuf = gVerifyBuf;
            uniflashConfig.verifyBufSize = VERIFY_BUF_MAX_SIZE;

            /* Process the flash commands and return a response */
            Bootloader_uniflashProcessFlashCommands(&uniflashConfig, &respHeader);

            if(respHeader.statusCode == BOOTLOADER_UNIFLASH_STATUSCODE_SUCCESS)
            {
                if(optype == '2')
                {
                    DebugP_log(" [FLASH WRITER] Flashing success!!... \r\n");
                }
                else if(optype == '3')
                {
                    DebugP_log(" [FLASH WRITER] Verifying success!!... \r\n");
                }
                status = SystemP_SUCCESS;
            }
            else
            {
                status = SystemP_FAILURE;
            }
        }
    }

    return status;
}

void sbl_jtag_uniflash_erase_all(void)
{
    int32_t status;
    DebugP_log(" [FLASH WRITER] Erasing complete flash ... \r\n");
    DebugP_log(" [FLASH WRITER] This can take few minutes, so please wait ... \r\n");

    status = Flash_eraseBlk(gFlashHandle[CONFIG_FLASH0], (uint32_t)-1);

    if(status!=SystemP_SUCCESS)
    {
        DebugP_log(" [FLASH WRITER] Erasing complete flash ... ERROR !!!\r\n");
    }
    else
    {
        DebugP_log(" [FLASH WRITER] Erasing complete flash ... SUCCESS !!!\r\n");
    }
}

void app_main(void)
{
    int32_t status = SystemP_SUCCESS;
    char ch[16];

    while(1)
    {
        DebugP_log(gMainMenu);

        gets(ch);

        switch(ch[0])
        {
            case '1':
                sbl_jtag_uniflash_erase_all();
                break;
            case '2':
            case '3':
                status = sbl_jtag_uniflash_load_file(ch[0]);
                if(status != SystemP_SUCCESS)
                {
                    if (ch[0] == '2')
                    {
                        DebugP_log(" [FLASH WRITER] Write Failed !!!\r\n");
                    }
                    else if (ch[0] == '3')
                    {
                        DebugP_log(" [FLASH WRITER] Verify Failed !!!\r\n");
                    }
                }
                break;
            case 'x':
            break;
            default:
                DebugP_log(" Enter valid option !!!\r\n");
            break;
        }
        if(ch[0] == 'x')
            break;
    }

    if(status != SystemP_SUCCESS)
    {
        DebugP_log("Some tests have failed!!\r\n");
    }
    else
    {
        DebugP_log("\r\n");
        DebugP_log(" [FLASH WRITER] Application exited !!!\r\n");
        DebugP_log("All tests have passed!!\r\n");
    }

}

void main_thread(void *args)
{

    int32_t status = SystemP_SUCCESS;

    /* Configure sciserver task parameters */
    Sciserver_TirtosCfgPrms_t sciserverCfg = {0};
    sciserverCfg.hiTaskStack    =   gUserHiTaskStack;
    sciserverCfg.loTaskStack    =   gUserLoTaskStack;
    sciserverCfg.taskStackSize  =   SCISERVER_TASK_STACK_SIZE;

    /* Open drivers */
    Drivers_open();

    /* Open flash and board drivers */
    status = Board_driversOpen();
    DebugP_assert(status==SystemP_SUCCESS);

    sciServer_init(&sciserverCfg);
    app_main();

    /* Close board and flash drivers */
    Board_driversClose();
    /* Close drivers */
    Drivers_close();

    vTaskDelete(NULL);
}

int main(void)
{
   int32_t status = SystemP_SUCCESS;

    status = sciclient_load_sysfw();
    DebugP_assert(status == SystemP_SUCCESS);

    Dpl_init();

    status = sciclient_set_boardcfg();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    /* init SOC specific modules */

    status = app_system_init();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    status = Bootloader_socOpenFirewalls();
    DebugP_assertNoLog(status == SystemP_SUCCESS);

    gMainTask = xTaskCreateStatic( main_thread,   /* Pointer to the function that implements the task. */
                                  "main_thread", /* Text name for the task.  This is to facilitate debugging only. */
                                  TASK_SIZE,  /* Stack depth in units of StackType_t typically uint32_t on 32b CPUs */
                                  NULL,            /* We are not using the task parameter. */
                                  TASK_PRI_MAIN_THREAD,   /* task priority, 0 is lowest priority, configMAX_PRIORITIES-1 is highest */
                                  gMainTaskStack,  /* pointer to stack base */
                                  &gMainTaskObj ); /* pointer to statically allocated task object memory */
    configASSERT(gMainTask != NULL);

    /* Start the scheduler to start the tasks executing. */
    vTaskStartScheduler();

    /* The following line should never be reached because vTaskStartScheduler()
    will only return if there was not enough FreeRTOS heap memory available to
    create the Idle and (if configured) Timer tasks.  Heap management, and
    techniques for trapping heap exhaustion, are described in the book text. */
    DebugP_assertNoLog(0);

    return 0;

}


