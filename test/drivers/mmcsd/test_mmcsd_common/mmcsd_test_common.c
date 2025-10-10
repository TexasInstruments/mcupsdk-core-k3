/*
 * Copyright (C) 2021-2025 Texas Instruments Incorporated
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

/**\file mmcsd_test_common.c
 *
 * \brief Common test routines for MMCSD file I/O validation.
 *
 * This file contains test routines to validate file input/output functionality
 * using the MMCSD driver in the MCU+ SDK.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "mmcsd_test_common.h"

/* ========================================================================== */
/*                             Global Buffers                                 */
/* ========================================================================== */

/* Buffers for FS tests */
#if defined (ENABLE_FS_TESTS)
#if !defined (SOC_AM275X) && !defined(C7_CORE)
uint8_t TestMMCSD_Wbuf[TEST_MMCSD_FAT_BLOCK_SIZE * TEST_MMCSD_BLOCK_COUNT]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));
uint8_t TestMMCSD_Rbuf[TEST_MMCSD_FAT_BLOCK_SIZE * TEST_MMCSD_BLOCK_COUNT]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));

uint8_t TestMMCSD_Wbuf40M[TEST_MMCSD_40MB_SIZE]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));
uint8_t TestMMCSD_Rbuf40M[TEST_MMCSD_40MB_SIZE]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));

/* Threads for multithreading test cases */
uint8_t TestMMCSD_Task1Wbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));
uint8_t TestMMCSD_Task1Rbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));

uint8_t TestMMCSD_Task2Wbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));
uint8_t TestMMCSD_Task2Rbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));
#else
uint8_t TestMMCSD_Wbuf[TEST_MMCSD_FAT_BLOCK_SIZE * TEST_MMCSD_BLOCK_COUNT]
    __attribute__((aligned(128U)));
uint8_t TestMMCSD_Rbuf[TEST_MMCSD_FAT_BLOCK_SIZE * TEST_MMCSD_BLOCK_COUNT]
    __attribute__((aligned(128U)));

/* Threads for multithreading test cases */
uint8_t TestMMCSD_Task1Wbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U)));
uint8_t TestMMCSD_Task1Rbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U)));

uint8_t TestMMCSD_Task2Wbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U)));
uint8_t TestMMCSD_Task2Rbuf[TEST_MMCSD_SIZE_64K]
    __attribute__((aligned(128U)));
#endif
#endif

/* Buffers for RAW test */
#if defined (ENABLE_RAW_TESTS)
#if !defined (SOC_AM275X) && !defined (C7_CORE) && !defined (SOC_J722S)
uint8_t TestMMCSD_TxBuf[TEST_MMCSD_DATA_SIZE]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));
uint8_t TestMMCSD_RxBuf[TEST_MMCSD_DATA_SIZE]
    __attribute__((aligned(128U), section(".globalScratchBuffer")));
#else
uint8_t TestMMCSD_TxBuf[TEST_MMCSD_DATA_SIZE]
    __attribute__((aligned(128U)));
uint8_t TestMMCSD_RxBuf[TEST_MMCSD_DATA_SIZE]
    __attribute__((aligned(128U)));
#endif
#endif

uint32_t TestMMCSD_Modes[] =
{
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_SDR,
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS_DDR,
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS200,
#if defined (SOC_AM62PX) || defined (SOC_J722S)
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS400,
#endif
};

uint32_t TestMMCSD_SdModes[] =
{
    MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_SD_HS,
};

const uint32_t TestMMCSD_ModesCount = sizeof(TestMMCSD_Modes) / sizeof(TestMMCSD_Modes[0]);
const uint32_t TestMMCSD_SdModesCount = sizeof(TestMMCSD_SdModes) / sizeof(TestMMCSD_SdModes[0]);

#if defined (ENABLE_RAW_TESTS)
/* ========================================================================== */
/*                           Function Definitions                             */
/* ========================================================================== */

/**
 * \brief Fuction to fill buffers for test cases
 *
 * \param None.
 *
 * \return None.
 */
void Test_Mmcsd_FillBuffers(void)
{
    uint32_t i = 0;
    for (i = 0U; i < TEST_MMCSD_DATA_SIZE; i++)
    {
        TestMMCSD_TxBuf[i] = i % 256;
        TestMMCSD_RxBuf[i] = 0U;
    }
}
#endif

