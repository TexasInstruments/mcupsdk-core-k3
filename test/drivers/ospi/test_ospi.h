/*
 * Copyright (C) 2025-2026 Texas Instruments Incorporated
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

#ifndef OSPI_TEST_FILE_H
#define OSPI_TEST_FILE_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <board/flash.h>
#include <drivers/ospi.h>
#include <drivers/ospi/v0/ospi.h>
#include <drivers/ospi/v0/dma/ospi_dma.h>
#include <drivers/ospi/v0/vtm.h>
#include <drivers/soc.h>

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/CacheP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* For NOR_SPI_SFDP_* and NorSpi_SfdpHeader */
#include <board/flash/sfdp/nor_spi_sfdp.h>

/* ========================================================================== */
/*                           Macros Defines                                   */
/* ========================================================================== */

#define TEST_OSPI_FLASH_OFFSET_BASE        (0x200000U)
#define TEST_OSPI_FLASH_OFFSET_VERIFY      (0x400000U)
#define TEST_OSPI_FLASH_PHY_TUNING_OFFSET  (0x300000U)
#define TEST_OSPI_DATA_SIZE                (256U) /* has to be 256 B aligned */
#define TEST_OSPI_DATA_REPEAT_COUNT        (8U)
#define TEST_OSPI_RX_BUF_SIZE              (TEST_OSPI_DATA_SIZE * TEST_OSPI_DATA_REPEAT_COUNT)
#define TEST_OSPI_1KB_SIZE                 (256*4U)
#define TEST_OSPI_2KB_SIZE                 (TEST_OSPI_1KB_SIZE*2U)
#define TEST_OSPI_4KB_SIZE                 (TEST_OSPI_1KB_SIZE*4U)
#define TEST_OSPI_8KB_SIZE                 (TEST_OSPI_1KB_SIZE*8U)
#define TEST_OSPI_64KB_SIZE                (TEST_OSPI_1KB_SIZE*64U)
#define TEST_OSPI_128KB_SIZE               (TEST_OSPI_1KB_SIZE*128U)
#define TEST_OSPI_256KB_SIZE               (TEST_OSPI_1KB_SIZE*256U)
#define TEST_OSPI_512KB_SIZE               (TEST_OSPI_1KB_SIZE*512U)
#define TEST_OSPI_1MB_SIZE                 (TEST_OSPI_1KB_SIZE*TEST_OSPI_1KB_SIZE)
#define TEST_OSPI_2MB_SIZE                 (TEST_OSPI_1MB_SIZE*2U)
#define TEST_OSPI_5MB_SIZE                 (TEST_OSPI_1MB_SIZE*5U)
#define TEST_OSPI_10MB_SIZE                (TEST_OSPI_1MB_SIZE*10U)
#define TEST_OSPI_UNALIGNED_TEST_SIZE      (1000U)
#define TEST_OSPI_UNALIGNED_TEST_OFFSET    (5U)
#define TEST_OSPI_REPEAT_COUNT             (100U)
#define TEST_OSPI_MAX_CHUNK_SIZE           (TEST_OSPI_1KB_SIZE*16U)
#define TEST_OSPI_MIN_CHUNK_SIZE           (16U)
#define TEST_OSPI_TEST_FREQUENCY_50MHZ     (50000000U)
#define TEST_OSPI_SDR_BAUD_RATE_DIV        (4U)   /* Baud rate divisor for SDR mode */
#define TEST_OSPI_DDR_BAUD_RATE_DIV        (8U)   /* Baud rate divisor for DDR mode */

#if defined (SOC_AM275X) || defined(SOC_J722S)
#if defined(__C7504__) || defined(__C7524__)
#define TEST_OSPI_MAX_TEST_SIZE            (TEST_OSPI_1MB_SIZE)
#else
#define TEST_OSPI_MAX_TEST_SIZE            (TEST_OSPI_2MB_SIZE)
#endif
#else
#define TEST_OSPI_MAX_TEST_SIZE            (TEST_OSPI_10MB_SIZE)
#endif

#define TEST_OSPI_BLOCK_SIZE               (TEST_OSPI_1KB_SIZE*256U)
#define TEST_OSPI_READ_FRCOUNT             (10U)  /* Frequency of reading required for average time of read operation*/

#if defined (SOC_AM275X)
#if defined(__C7504__) || defined(__C7524__)
#define TEST_OSPI_PERF_TEST_DATA_COUNT     (1U)   /* Change this value as per testSizes list size */
#else
#define TEST_OSPI_PERF_TEST_DATA_COUNT     (2U)   /* Change this value as per testSizes list size */
#endif
#else
#define TEST_OSPI_PERF_TEST_DATA_COUNT     (3U)   /* Change this value as per testSizes list size */
#endif

#if (TEST_OSPI_UNALIGNED_TEST_OFFSET + TEST_OSPI_UNALIGNED_TEST_SIZE > TEST_OSPI_MAX_TEST_SIZE)
#error Increase the TEST_OSPI_MAX_TEST_SIZE.
#endif

#define TEST_OSPI_8S8S8S_SUPPORTED              (1U)

#define TEST_DEVICE_SIZE    (128U * 1024U * 1024U)  /* 128 MB */
#define TEST_PAGE_SIZE      (256U)                   /* 256 bytes */
#define TEST_BLOCK_SIZE     (256U * 1024U)           /* 256 KB */
#define TEST_INVALID_SIZE   (123U)                   /* Not power of 2 */

/* ========================================================================== */
/*                 Structure Declarations                                     */
/* ========================================================================== */

/* Structure to store mode settings */
typedef struct Test_FlashModeSettings_t
{
    uint32_t flashType;
    char* flashName;
    uint32_t cfgflashType;
    uint32_t flashProtocol;
    uint32_t phyEnable;
    uint32_t dmaEnable;
    uint32_t dacEnable;
    uint32_t phySkipTuning;
}Test_FlashModeSettings;

typedef struct TestData_SizesAttr_t
{
    uint32_t dataSize; //in MiB
    float writeSpeed;
    float readSpeed;
}TestData_SizesAttr;

/* ========================================================================== */
/*                      Function Declarations                                 */
/* ========================================================================== */
void test_ospi_multithread(void);

void TestOspi_multithreadWriteRead(void *args);
#ifndef SOC_AM62DX
void TestOspi_multithreadIntrMode(void *args);
#endif

void TestOspi_multithreadWrite(void *args);
void TestOspi_multithreadRead(void *args);

/* New multi-threaded test functions for OSPI functionalities */
void TestOspi_multithreadIOModes(void *args);
void TestOspi_multithreadDirectReadWrite(void *args);
void TestOspi_multithreadIndirectReadWrite(void *args);

/* Helper thread functions */
void TestOspi_dualQuadReadThread(void *args);
void TestOspi_dacModeReadThread(void *args);
void TestOspi_directWriteThread(void *args);
void TestOspi_directReadThread(void *args);
void TestOspi_indirectWriteThread(void *args);
void TestOspi_indirectReadThread(void *args);

#endif /* OSPI_TEST_FILE_H */
