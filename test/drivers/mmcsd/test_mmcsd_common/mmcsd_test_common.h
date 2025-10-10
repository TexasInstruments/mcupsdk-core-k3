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

#ifndef MMCSD_TEST_COMMON_H
#define MMCSD_TEST_COMMON_H

/**\file mmcsd_test_common.h
 *
 * \brief Common definitions and declarations for MMCSD fs and raw I/O tests.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <drivers/mmcsd.h>
#include <kernel/dpl/DebugP.h>
#if defined (ENABLE_FS_TESTS)
#include <kernel/dpl/SemaphoreP.h>
#endif
#include <kernel/dpl/ClockP.h>
#if defined (ENABLE_FS_TESTS)
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>
#endif
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define TEST_MMCSD_EMMC_START_BLK        (0x300000U) /* 1.5GB */
#define TEST_MMCSD_EMMC_START_BLK2       (0x180000) /* 0.75GB */
#define TEST_MMCSD_SD_START_BLK          (0x300000U) /* 1.5GB */
#if defined (ENABLE_FS_TESTS)
#define TEST_MMCSD_FILE_COUNT            (10)
#define TEST_MMCSD_BLOCK_COUNT           (10)
#define TEST_MMCSD_FAT_BLOCK_SIZE        (512)
#define TEST_MMCSD_SIZE_64K              (64 * 1024)
#define TEST_MMCSD_SIZE_40M              (40 * 1024 * 1024)
#endif

#if !defined (SOC_AM275X) && !defined (SOC_J722S)  && !defined (C7_CORE)
#define TEST_MMCSD_DATA_SIZE             (0x2800000U) /* has to be 256 B aligned */
#else
#if defined (ENABLE_FS_TESTS)
#define TEST_MMCSD_DATA_SIZE             (0x100000U) /* has to be 256 B aligned */
#else
#define TEST_MMCSD_DATA_SIZE             (0x20000U) /* has to be 256 B aligned */
#endif
#endif

#define TEST_MMCSD_FILE_LINE_CNT         (1024U * 1024U)
#define TEST_MMCSD_1KB_SIZE              (256U * 4U)
#define TEST_MMCSD_FAT_PARTITION_SIZE    (1024U * 1024U * 1024U) /* 1GB */

#if !defined (SOC_AM275X)  && !defined (C7_CORE)
#define TEST_MMCSD_PERF_TEST_DATA_COUNT  (5U)   /* Change this value as per testSizes list size */
#else
#define TEST_MMCSD_PERF_TEST_DATA_COUNT  (5U)   /* Change this value as per testSizes list size */
#endif

#define TEST_MMCSD_128KB_SIZE            (TEST_MMCSD_1KB_SIZE * 128)
#define TEST_MMCSD_1MB_SIZE              (TEST_MMCSD_1KB_SIZE * TEST_MMCSD_1KB_SIZE)
#define TEST_MMCSD_4MB_SIZE              (TEST_MMCSD_1MB_SIZE * 4U)
#define TEST_MMCSD_6MB_SIZE              (TEST_MMCSD_1MB_SIZE * 6U)
#define TEST_MMCSD_32MB_SIZE             (TEST_MMCSD_1MB_SIZE * 32U)
#define TEST_MMCSD_40MB_SIZE             (TEST_MMCSD_1MB_SIZE * 40U)

#if defined(SOC_AM275X) || defined(C7_CORE) || defined(SOC_J722S)
#define TEST_MMCSD_XFER_SIZE   TEST_MMCSD_128KB_SIZE
#else
#define TEST_MMCSD_XFER_SIZE   TEST_MMCSD_1MB_SIZE
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if defined (ENABLE_FS_TESTS)
extern uint8_t TestMMCSD_Wbuf[TEST_MMCSD_FAT_BLOCK_SIZE * TEST_MMCSD_BLOCK_COUNT];
extern uint8_t TestMMCSD_Rbuf[TEST_MMCSD_FAT_BLOCK_SIZE * TEST_MMCSD_BLOCK_COUNT];

/* Buffers for multithreading test cases */
extern uint8_t TestMMCSD_Task1Wbuf[TEST_MMCSD_SIZE_64K];
extern uint8_t TestMMCSD_Task1Rbuf[TEST_MMCSD_SIZE_64K];
extern uint8_t TestMMCSD_Task2Wbuf[TEST_MMCSD_SIZE_64K];
extern uint8_t TestMMCSD_Task2Rbuf[TEST_MMCSD_SIZE_64K];

/* Buffers for large file transfer */
#if !defined (SOC_AM275X) &&  !defined (C7_CORE)
extern uint8_t TestMMCSD_Wbuf40M[TEST_MMCSD_40MB_SIZE];
extern uint8_t TestMMCSD_Rbuf40M[TEST_MMCSD_40MB_SIZE];
#endif
#endif

#if defined (ENABLE_RAW_TESTS)
extern uint8_t TestMMCSD_TxBuf[TEST_MMCSD_DATA_SIZE];
extern uint8_t TestMMCSD_RxBuf[TEST_MMCSD_DATA_SIZE];
#endif

extern MMCSD_Attrs gMmcsdAttrs[CONFIG_MMCSD_NUM_INSTANCES];
extern MMCSD_Handle gMmcsdHandle[];

extern uint32_t TestMMCSD_Modes[];
extern const uint32_t TestMMCSD_ModesCount;
extern uint32_t TestMMCSD_SdModes[];
extern const uint32_t TestMMCSD_SdModesCount;

#if defined (ENABLE_RAW_TESTS)
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void Test_Mmcsd_FillBuffers(void);
#endif

/* ========================================================================== */
/*                                Typedefs                                    */
/* ========================================================================== */

/**
 * \brief Structure to hold MMC/SD mode settings for test cases.
 */
typedef struct Test_MmcModeSettings_t
{
    char*    cardType;
    char*    mode;
    uint32_t busWidth;
    uint32_t phyEnable;
    uint32_t dmaEnable;
} Test_MmcModeSettings;

#endif /* MMCSD_TEST_COMMON_H */

