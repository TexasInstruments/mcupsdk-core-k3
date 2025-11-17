/*
 *  Copyright (C) 2021-2026 Texas Instruments Incorporated
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

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <unity.h>

#include "system_test_utils.h"

/* ========================================================================== */
/*                           Macro  Defines                                   */
/* ========================================================================== */

#define TEST_MMCSD_FILE_LINE_CNT 5
#define TEST_MMCSD_FAT_PARTITION_SIZE    (128 * 1024U * 1024U)

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

extern MMCSD_Attrs gMmcsdAttrs[CONFIG_MMCSD_NUM_INSTANCES];
extern MMCSD_Handle gMmcsdHandle[];
uint32_t TestMMCSD_modes[] =
{
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS200
};

/* ========================================================================== */
/*                           Function declarations                            */
/* ========================================================================== */

static int32_t TestMmcsd_fileIo(char *fileName, char* fileData);
static uint32_t TestMmcsd_isFormatNeeded(uint32_t partitionSize, 
                    uint32_t freeSize);

/* ========================================================================== */
/*                           Function definitions                             */
/* ========================================================================== */

/**
 * \brief Validates emmc file IO using 
 * FreeRTOS+FAT and MMCSD driver.
 *
 * Test Category: Functionality
 *
 * This function tests filesystem operations on EMMC by
 * writing patterned data, reading it back, verifying contents, 
 * and cleaning up.If no partition exists, it creates, formats, 
 * and mounts one before running the file tests.
 *
 * \param args Pointer to test-specific configuration or
 * runtime parameters (unused in this function).
 *
 * \return None.
 */

int32_t TestMmcsd_emmc(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t formatNeeded = 0;

    gMmcsdAttrs[CONFIG_MMCSD_EMMC].supportedModes = TestMMCSD_modes[0];

    /* Create partition if not present */
    FF_Disk_t *pDisk = &gFFDisks[FF_PARTITION_EMMC0];
    FF_MMCSD_PartitionDetails partitionDetails;
    FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
    formatNeeded = TestMmcsd_isFormatNeeded(partitionDetails.partitionSize,
                        partitionDetails.partitionFreeSize);

    if (partitionDetails.sectorCount == 0U || (formatNeeded))
    {
        /* No partition found, create a `TEST_MMCSD_FAT_PARTITION_SIZE` partition */
        uint32_t blockSize = MMCSD_getBlockSize(gMmcsdHandle[CONFIG_MMCSD_EMMC]);
        uint32_t partSectorCount = TEST_MMCSD_FAT_PARTITION_SIZE / blockSize;

        FF_MMCSDCreateAndFormatPartition(pDisk, partSectorCount);

        /* Now mount the partition */
        FF_MMCSDMountPartition(pDisk, "/emmc0");

        /* Finally check the partition again */
        FF_MMCSDGetPartitionDetails(pDisk, &partitionDetails);
        if (partitionDetails.sectorCount == 0U)
        {
            return SystemP_FAILURE;
        }
    }
    char *fileName = (char*)"/emmc0/test.dat";
    char *fileData = (char*)"THIS IS A TEST FILE TO TEST EMMC CARD FILE IO\n";

    retVal = TestMmcsd_fileIo(fileName, fileData);

    if(SystemP_SUCCESS != retVal)
    {
        return  SystemP_FAILURE;
    }

    return SystemP_SUCCESS;
}

/* Checks if the existing partition needs to be formatted */
static uint32_t TestMmcsd_isFormatNeeded(uint32_t partitionSize, uint32_t freeSize)
{
    uint32_t retVal;

    /* If the free size is greater than original size or if there is
     * low space left in the FAT partition then a format is needed
     */
    if((freeSize > partitionSize) || ((partitionSize - freeSize) < 4 ))
    {
        retVal = 1;
    }
    else
    {
        retVal = 0;
    }
    return retVal;
}

/* Function to perform the actula file operation */
static int32_t TestMmcsd_fileIo(char *fileName, char* fileData)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t i;
    char buf[100];
    uint32_t fileDataLen;
    FF_FILE *testFp = NULL;

    /* Create file */
    testFp = ff_fopen(fileName, "w+");
    if(testFp == NULL)
    {
        return SystemP_FAILURE;   
    }

    /* Write file data `TEST_MMCSD_FILE_LINE_CNT` times */
    fileDataLen = strlen(fileData)+1;

    for (i = 0U; i < TEST_MMCSD_FILE_LINE_CNT; i++)
    {
        ff_fwrite(fileData, fileDataLen, 1, testFp);
    }

    /* Close file */
    ff_fclose(testFp);

    /* Re-open now for reading */
    testFp = ff_fopen(fileName, "r");
    if(testFp == NULL)
    {
        return SystemP_FAILURE;   
    }

    /* Now read the lines one by one and check with fileData */
    for (i = 0U; i < TEST_MMCSD_FILE_LINE_CNT; i++)
    {
        ff_fread(buf, fileDataLen, 1, testFp);
        retVal |= strncmp(fileData, buf, fileDataLen);
        if (retVal != 0U)
        {
            retVal = SystemP_FAILURE;
            break;
        }
    }

    /* Close file */
    ff_fclose(testFp);

    /* Delete file */
    ff_remove(fileName);

    return retVal;
}
