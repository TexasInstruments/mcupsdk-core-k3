/*
 * Copyright (C) 2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_FILEIO_FILE_LINE_CNT      (1024U * 1024U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Testcases */
static void test_fileio_main(void *args);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(test_fileio_main, 8672, NULL);

    UNITY_END();

    return;
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

/*
 * Testcases
 */
static void test_fileio_main(void *args)
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("[TEST_FILEIO] Starting...\r\n");

    FILE *fp;

    char *fileName = "file.dat";
    char *fileData = "This is a test string. Hello, World!";
    char buf[100];

    /* Create file */
    fp = fopen(fileName, "w+");

    /* Write file data `TEST_FILEIO_FILE_LINE_CNT` times */

    uint32_t fileDataLen = strlen(fileData)+1;
    uint32_t i;

    for(i = 0U; i < TEST_FILEIO_FILE_LINE_CNT; i++)
    {
        fwrite(fileData, fileDataLen, 1, fp);
    }

    /* Close file */
    fclose(fp);

    /* Re-open now for reading */
    fp = fopen(fileName, "r");

    /* Now read the lines one by one and check with fileData */
    for(i = 0U; i < TEST_FILEIO_FILE_LINE_CNT; i++)
    {
        fread(buf, fileDataLen, 1, fp);
        status |= strncmp(fileData, buf, fileDataLen);
        if(status != SystemP_SUCCESS)
        {
            status = SystemP_FAILURE;
            break;
        }
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_log("Some tests have failed!!\r\n");
    }

    /* Close file */
    fclose(fp);

    /* Delete file */
    remove(fileName);
}
