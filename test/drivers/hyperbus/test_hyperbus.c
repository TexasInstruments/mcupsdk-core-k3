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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/hyperbus.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* HyperRAM base address as seen in the memory map */
#define TEST_HYPERBUS_HYPERRAM_BASE_ADDR    (0x68000000U)

/* Basic size aliases */
#define TEST_HYPERBUS_1KB_SIZE              (1024U)

/* Non-ECC region offsets (0 - 100KB, below ECC start) */
#define TEST_HYPERBUS_NONECCRW_OFFSET       (TEST_HYPERBUS_1KB_SIZE * 4U)    /* 4KB */
#define TEST_HYPERBUS_NONECCRW_SIZE         (TEST_HYPERBUS_1KB_SIZE * 4U)    /* 4KB */

/* Large R/W buffer size (non-ECC region) */
#define TEST_HYPERBUS_LARGE_RW_OFFSET       (TEST_HYPERBUS_1KB_SIZE * 4U)    /* 4KB */
#define TEST_HYPERBUS_LARGE_RW_SIZE         (TEST_HYPERBUS_1KB_SIZE * 32U)   /* 32KB */

/* ECC region offsets – must match syscfg eccstart0 / eccsize0 */
#define TEST_HYPERBUS_ECC_100KB_OFFSET      (TEST_HYPERBUS_1KB_SIZE * 100U)  /* 0x19000 */
#define TEST_HYPERBUS_ECC_124KB_OFFSET      (TEST_HYPERBUS_1KB_SIZE * 124U)
#define TEST_HYPERBUS_ECC_148KB_OFFSET      (TEST_HYPERBUS_1KB_SIZE * 148U)
#define TEST_HYPERBUS_ECC_172KB_OFFSET      (TEST_HYPERBUS_1KB_SIZE * 172U)
#define TEST_HYPERBUS_ECC_24KB_SIZE         (TEST_HYPERBUS_1KB_SIZE * 24U)
#define TEST_HYPERBUS_ECC_ZERO_SIZE         (0U)

/* An ECC region at 60MB + 24KB exceeds the 56.9MB effective device capacity */
#define TEST_HYPERBUS_ECC_60MB_OFFSET       (TEST_HYPERBUS_1KB_SIZE * 1024U * 60U)

/* ECC block geometry – mirrors private macros in hyperbus_v0.c */
#define TEST_HYPERBUS_ECC_BLOCK_SIZE        (32U)   /* bytes of data per ECC block  */
#define TEST_HYPERBUS_ECC_OVERHEAD_SIZE     (4U)    /* bytes of ECC  per data block  */

/* Offset within ECC region used for single/double bit error injection */
#define TEST_HYPERBUS_ECC_TEST_OFFSET       (0x80U)

/* Stress / repeat counts */
#define TEST_HYPERBUS_STRESS_OPEN_CLOSE_CNT (10U)
#define TEST_HYPERBUS_ECC_TOGGLE_CNT        (20U)

/* Semaphore pend timeout (10 ms) */
#define TEST_HYPERBUS_ECC_SEM_TIMEOUT_US    (10U * 1000U)

/* Free-running GTC counter (WKUP_GTC0_GTC_CFG1 base + CNTCV_LO @ 0x8).
 * Pointing the HyperRAM data base here makes every 64-byte read in
 * HYPERBUS_waitForMdllStabilization return a different value, which forces
 * the "DLL did not stabilize" failure branch. */
#define TEST_HYPERBUS_GTC_CNTCV_LO_ADDR     (0x00A90008U)

/* Alternate module input clock (not 166666666 Hz) used to exercise the else
 * branch of HYPERBUS_getInputClk. It doubles to ~333.33 MHz, matching the
 * normal X2 clock, so the driver still opens successfully. */
#define TEST_HYPERBUS_ALT_INPUT_CLK_FREQ    (166666667U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ECC callback state – written from ISR context */
static volatile uint8_t  gTestHyperbus_EccErrType   = 0xFFU;
static volatile uint32_t gTestHyperbus_EccCbkCount  = 0U;

/* Semaphore signalled by ECC callback */
static SemaphoreP_Object gTestHyperbus_EccSem;

/* Logical offset within HyperRAM currently being tested for ECC */
static volatile uint32_t gTestHyperbus_EccTestAddr  = 0U;

/* 32-byte working buffers for ECC error injection */
static uint8_t gTestHyperbus_EccBuf[TEST_HYPERBUS_ECC_BLOCK_SIZE];
static uint8_t gTestHyperbus_EccBufCheck[TEST_HYPERBUS_ECC_BLOCK_SIZE];

/* Large MSRAM scratch buffers for CPU / burst memory tests */
static uint8_t gTestHyperbus_WriteBuf[TEST_HYPERBUS_LARGE_RW_SIZE]
    __attribute__((section(".globalScratchBuffer"), aligned(128U)));
static uint8_t gTestHyperbus_ReadBuf[TEST_HYPERBUS_LARGE_RW_SIZE]
    __attribute__((section(".globalScratchBuffer"), aligned(128U)));

/* Fake FSS-SYSCFG register block used to force the INIT_DONE / MDLL_LOCK
 * wait-loop timeouts in HYPERBUS_open. Layout mirrors CSL_hyperbus_syscfgRegs:
 * [0] = REVISION_REG, [1] = DLL_STAT_REG (MDLL_LOCK = bit 0),
 * [2] = RAM_STAT_REG (INIT_DONE = bit 0). */
static volatile uint32_t gTestHyperbus_FakeSyscfg[3];

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/* ECC ISR callback – name must match ECCCallbackFxn in syscfg */
void TestHyperbus_hyperRamEccCallback(HYPERBUS_Handle handle, uint8_t errorType);

/* Helper: translate logical HyperRAM address to raw physical address */
static uintptr_t TestHyperbus_getTranslatedAddr(uintptr_t logicalAddr);

/* Helper: inject a 1-bit SEC error at the given logical offset */
static int32_t TestHyperbus_injectSecError(HYPERBUS_Handle handle, uint32_t offset);

/* Helper: inject a 2-bit DED error at the given logical offset */
static int32_t TestHyperbus_injectDedError(HYPERBUS_Handle handle, uint32_t offset);

/* Individual test functions */
static void TestHyperBus_GetHandleInvalidIndex(void *args);
static void TestHyperBus_GetDataBaseAddrNullHandle(void *args);
static void TestHyperBus_MemoryMappedReadWrite(void *args);
static void TestHyperBus_CpuByteReadWrite(void *args);
static void TestHyperBus_CpuHalfWordReadWrite(void *args);
static void TestHyperBus_CpuWordReadWrite(void *args);
static void TestHyperBus_WalkingOnesPattern(void *args);
static void TestHyperBus_AddressOffsetAccess(void *args);
static void TestHyperBus_BurstMaxLengthBoundary(void *args);
static void TestHyperBus_DataRetentionAfterDelay(void *args);
static void TestHyperBus_ECCEnableDisableToggle(void *args);
static void TestHyperBus_ECCClearAllErrors(void *args);
static void TestHyperBus_ECCConfigureAllRegions(void *args);
static void TestHyperBus_ECCRegionDisabledSkip(void *args);
static void TestHyperBus_ECCSecErrCallback(void *args);
static void TestHyperBus_ECCDedErrCallback(void *args);
static void TestHyperBus_BoundaryOpenInvalidIndex(void *args);
static void TestHyperBus_BoundarySetECCRegionInvalidIndex(void *args);
static void TestHyperBus_BoundaryECCNullFsasBase(void *args);
static void TestHyperBus_OpenClose(void *args);
static void TestHyperBus_OpenAlreadyOpen(void *args);
static void TestHyperBus_DeviceCfgNoneType(void *args);
static void TestHyperBus_StressOpenCloseRepeat(void *args);
static void TestHyperBus_StressECCToggleRepeat(void *args);
static void TestHyperBus_StressLargeMemoryAccess(void *args);
static void TestHyperBus_RamInitDoneTimeout(void *args);
static void TestHyperBus_MdllLockTimeout(void *args);
static void TestHyperBus_InputClkAlternate(void *args);

/* Coverage gap test functions */
static void TestHyperBus_FssEccDisabled(void *args);
static void TestHyperBus_FssOtfaEnabled(void *args);
static void TestHyperBus_LatencyCodeVariants(void *args);
static void TestHyperBus_DeviceCfgHyperFlash(void *args);
static void TestHyperBus_ECCWriteNonAlignErrCallback(void *args);
static void TestHyperBus_ECCRegionExceedsDeviceSize(void *args);
static void TestHyperBus_ECCNullRegionFailure(void *args);
static void TestHyperBus_ECCIntrRegistration(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_hyperbus_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(TestHyperBus_ECCClearAllErrors,            12244, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(TestHyperBus_ECCConfigureAllRegions,       12245, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(TestHyperBus_ECCRegionDisabledSkip,        12246, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(TestHyperBus_ECCSecErrCallback,            12247, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(TestHyperBus_ECCDedErrCallback,            12248, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(TestHyperBus_BoundaryECCNullFsasBase,           12249, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    RUN_TEST(TestHyperBus_OpenAlreadyOpen,              12251, NULL);

    Drivers_hyperbusOpen();
    Board_driversOpen();
    Board_hyperRamClose();
    Drivers_hyperbusClose();
    RUN_TEST(TestHyperBus_DeviceCfgNoneType,            12252, NULL);

    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(TestHyperBus_StressOpenCloseRepeat,        12253, NULL);

    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(TestHyperBus_StressECCToggleRepeat,        12254, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    RUN_TEST(TestHyperBus_OpenClose,                    12255, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    RUN_TEST(TestHyperBus_FssEccDisabled,                12256, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    RUN_TEST(TestHyperBus_FssOtfaEnabled,                12257, NULL);
    RUN_TEST(TestHyperBus_LatencyCodeVariants,            12258, NULL);
    RUN_TEST(TestHyperBus_DeviceCfgHyperFlash,           12259, NULL);
    RUN_TEST(TestHyperBus_RamInitDoneTimeout,            12260, NULL);
    RUN_TEST(TestHyperBus_MdllLockTimeout,               12261, NULL);
    RUN_TEST(TestHyperBus_InputClkAlternate,             12262, NULL);

    Board_hyperRamClose();
    Drivers_hyperbusClose();
    Drivers_hyperbusOpen();
    Board_driversOpen();
    RUN_TEST(TestHyperBus_StressLargeMemoryAccess,      12263, NULL);

    RUN_TEST(TestHyperBus_BoundaryOpenInvalidIndex,     12264, NULL);
    RUN_TEST(TestHyperBus_GetHandleInvalidIndex,        12265, NULL);
    RUN_TEST(TestHyperBus_GetDataBaseAddrNullHandle,    12266, NULL);
    RUN_TEST(TestHyperBus_MemoryMappedReadWrite,        12267, NULL);
    RUN_TEST(TestHyperBus_CpuByteReadWrite,             12268, NULL);
    RUN_TEST(TestHyperBus_CpuHalfWordReadWrite,         12269, NULL);
    RUN_TEST(TestHyperBus_CpuWordReadWrite,             12270, NULL);
    RUN_TEST(TestHyperBus_WalkingOnesPattern,           12271, NULL);
    RUN_TEST(TestHyperBus_AddressOffsetAccess,          12272, NULL);
    RUN_TEST(TestHyperBus_BurstMaxLengthBoundary,       12273, NULL);
    RUN_TEST(TestHyperBus_DataRetentionAfterDelay,      12274, NULL);
    RUN_TEST(TestHyperBus_ECCEnableDisableToggle,       12275, NULL);
    RUN_TEST(TestHyperBus_BoundarySetECCRegionInvalidIndex,  12276, NULL);
    RUN_TEST(TestHyperBus_ECCWriteNonAlignErrCallback,  12277, NULL);
    RUN_TEST(TestHyperBus_ECCRegionExceedsDeviceSize,   12278, NULL);
    RUN_TEST(TestHyperBus_ECCNullRegionFailure,          12279, NULL);
    RUN_TEST(TestHyperBus_ECCIntrRegistration,           12280, NULL);

    HYPERBUS_deinit();

    UNITY_END();

    return;
}

/*
 * Unity required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

/* ECC error callback handler for HyperBus HyperRAM memory tests.
 * This callback is invoked when an ECC error is detected during HyperRAM operations.
 * It records the error type and increments the error count for test validation.
 * The function restores the correct data to the affected memory location to clear the error.
 * It also invalidates the CPU cache to ensure data consistency after restoration.
 * Finally, it posts a semaphore to signal the waiting test that the error has been processed.
 */
void TestHyperbus_hyperRamEccCallback(HYPERBUS_Handle handle, uint8_t errorType)
{
    uint32_t baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);

    gTestHyperbus_EccErrType = errorType;
    gTestHyperbus_EccCbkCount++;

    /*
     * Restore correct data so the ECC error is cleared and the memory
     * location can be used again after the test.
     */
    memcpy((void *)(uintptr_t)(baseAddr + gTestHyperbus_EccTestAddr),
           gTestHyperbus_EccBufCheck,
           TEST_HYPERBUS_ECC_BLOCK_SIZE);
    CacheP_wb((void *)(uintptr_t)(baseAddr + gTestHyperbus_EccTestAddr),
              TEST_HYPERBUS_ECC_BLOCK_SIZE,
              CacheP_TYPE_ALLD);

    SemaphoreP_post(&gTestHyperbus_EccSem);
}

/* Helper function to translate logical addresses to physical addresses in hyperbus memory.
 * This function calculates the block index based on the logical address offset from the base.
 * It computes the ECC overhead adjustment based on whether the block index is even or odd.
 * Even block indices add overhead equal to blockIdx times the overhead size.
 * Odd block indices add overhead equal to (blockIdx + 1) times the overhead size.
 * Returns the translated physical address accounting for ECC overhead in the memory layout.
 */
static uintptr_t TestHyperbus_getTranslatedAddr(uintptr_t logicalAddr)
{
    uint32_t  blockIdx;
    uintptr_t translated;

    blockIdx = (uint32_t)((logicalAddr - (uintptr_t)TEST_HYPERBUS_HYPERRAM_BASE_ADDR)
                          / TEST_HYPERBUS_ECC_BLOCK_SIZE);

    if ((blockIdx & 0x1U) == 0U)
    {
        translated = logicalAddr + ((uintptr_t)blockIdx * TEST_HYPERBUS_ECC_OVERHEAD_SIZE);
    }
    else
    {
        translated = logicalAddr + ((uintptr_t)(blockIdx + 1U) * TEST_HYPERBUS_ECC_OVERHEAD_SIZE);
    }
    return translated;
}

/* Test case to verify HYPERBUS ECC single-bit error (SEC) injection and detection.
 * This test injects a single-bit error into hyperbus memory and verifies the ECC mechanism detects it.
 * It writes known data, flips 1 bit to create a correctable single-bit error, and triggers an ECC read.
 * The test disables ECC, corrupts the data, re-enables ECC, then reads to fire the ECC error ISR.
 * It validates that the error callback is invoked and the error type is properly identified.
 * This test ensures the ECC hardware correctly identifies and reports single-bit errors in hyperbus memory.
 */
static int32_t TestHyperbus_injectSecError(HYPERBUS_Handle handle, uint32_t offset)
{
    int32_t   status;
    uint32_t  baseAddr;
    uintptr_t logicalAddr;
    uintptr_t translatedAddr;

    baseAddr     = HYPERBUS_getHyperBusDataBaseAddr(handle);
    logicalAddr  = (uintptr_t)(baseAddr + offset);

    SemaphoreP_constructBinary(&gTestHyperbus_EccSem, 0U);
    gTestHyperbus_EccTestAddr = offset;
    gTestHyperbus_EccErrType  = 0xFFU;
    gTestHyperbus_EccCbkCount = 0U;

    /* Write known data and snapshot it */
    memset((void *)logicalAddr, 0xF8U, TEST_HYPERBUS_ECC_BLOCK_SIZE);
    CacheP_wbInv((void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE, CacheP_TYPE_ALLD);
    memcpy(gTestHyperbus_EccBuf,      (void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE);
    memcpy(gTestHyperbus_EccBufCheck, (void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE);

    /* Flip 1 bit to create a single-bit error */
    gTestHyperbus_EccBuf[0] ^= 0x01U;

    translatedAddr = TestHyperbus_getTranslatedAddr(logicalAddr);

    /* Disable ECC, inject corrupted data, re-enable ECC */
    HYPERBUS_enableECC(handle, HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_DISABLE);
    ClockP_usleep(10U);
    memcpy((void *)translatedAddr, gTestHyperbus_EccBuf, TEST_HYPERBUS_ECC_BLOCK_SIZE);
    CacheP_wb((void *)translatedAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE, CacheP_TYPE_ALL);
    HYPERBUS_enableECC(handle, HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_ENABLE);
    ClockP_usleep(10U);

    /* Invalidate cache and trigger a read to fire the ECC ISR */
    CacheP_inv((void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE, CacheP_TYPE_ALLD);
    memcpy(gTestHyperbus_EccBuf, (void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE);

    /* Wait for ISR to signal completion */
    status = SemaphoreP_pend(&gTestHyperbus_EccSem,
                             ClockP_usecToTicks(TEST_HYPERBUS_ECC_SEM_TIMEOUT_US));
    SemaphoreP_destruct(&gTestHyperbus_EccSem);
    return status;
}

/* Test case to verify HYPERBUS ECC double-bit error (DED) injection and detection.
 * This test injects a double-bit error into hyperbus memory and verifies the ECC mechanism detects it.
 * It writes known data, flips 2 bits to create a correctable double-bit error, and triggers an ECC read.
 * The test disables ECC, corrupts the data, re-enables ECC, then reads to fire the ECC error ISR.
 * It validates that the error callback is invoked and the error type is properly identified.
 * This test ensures the ECC hardware correctly identifies and reports double-bit errors in hyperbus memory.
 */
static int32_t TestHyperbus_injectDedError(HYPERBUS_Handle handle, uint32_t offset)
{
    int32_t   status;
    uint32_t  baseAddr;
    uintptr_t logicalAddr;
    uintptr_t translatedAddr;

    baseAddr     = HYPERBUS_getHyperBusDataBaseAddr(handle);
    logicalAddr  = (uintptr_t)(baseAddr + offset);

    SemaphoreP_constructBinary(&gTestHyperbus_EccSem, 0U);
    gTestHyperbus_EccTestAddr = offset;
    gTestHyperbus_EccErrType  = 0xFFU;
    gTestHyperbus_EccCbkCount = 0U;

    /* Write known data and snapshot it */
    memset((void *)logicalAddr, 0xF8U, TEST_HYPERBUS_ECC_BLOCK_SIZE);
    CacheP_wbInv((void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE, CacheP_TYPE_ALLD);
    memcpy(gTestHyperbus_EccBuf,      (void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE);
    memcpy(gTestHyperbus_EccBufCheck, (void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE);

    /* Flip 2 bits to create a double-bit error */
    gTestHyperbus_EccBuf[0] ^= 0x11U;

    translatedAddr = TestHyperbus_getTranslatedAddr(logicalAddr);

    /* Disable ECC, inject corrupted data, re-enable ECC */
    HYPERBUS_enableECC(handle, HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_DISABLE);
    ClockP_usleep(10U);
    memcpy((void *)translatedAddr, gTestHyperbus_EccBuf, TEST_HYPERBUS_ECC_BLOCK_SIZE);
    CacheP_wb((void *)translatedAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE, CacheP_TYPE_ALL);
    HYPERBUS_enableECC(handle, HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_ENABLE);
    ClockP_usleep(10U);

    /* Invalidate cache and trigger a read to fire the ECC ISR */
    CacheP_inv((void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE, CacheP_TYPE_ALLD);
    memcpy(gTestHyperbus_EccBuf, (void *)logicalAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE);

    /* Wait for ISR to signal completion */
    status = SemaphoreP_pend(&gTestHyperbus_EccSem,
                             ClockP_usecToTicks(TEST_HYPERBUS_ECC_SEM_TIMEOUT_US));
    SemaphoreP_destruct(&gTestHyperbus_EccSem);
    return status;
}

/* Test case to verify HYPERBUS_getHandle() returns NULL for invalid configuration indices.
 * This test validates that the API properly handles out-of-bounds and invalid index values.
 * It tests both invalid configuration number (gHyperBusConfigNum) and maximum uint32_t value.
 * The test ensures the driver performs proper bounds checking and validation of input parameters.
 * It verifies that invalid inputs do not cause crashes or undefined behavior in the driver.
 * This boundary condition test confirms robust error handling for invalid handle requests.
 */
static void TestHyperBus_GetHandleInvalidIndex(void *args)
{
    HYPERBUS_Handle handle;

    handle = HYPERBUS_getHandle(gHyperBusConfigNum);
    TEST_ASSERT_NULL(handle);

    handle = HYPERBUS_getHandle(0xFFFFFFFFU);
    TEST_ASSERT_NULL(handle);

    DebugP_log("[HYPERBUS] GetHandle invalid index: PASS\r\n");
}

/* Test case to verify HYPERBUS_getHyperBusDataBaseAddr() handles NULL handle gracefully.
 * This test validates that the API returns 0 when passed a NULL handle pointer.
 * It ensures proper error handling and null pointer checking in the driver implementation.
 * The test verifies that the function does not crash or exhibit undefined behavior when given invalid input.
 * This is a boundary condition test to ensure robustness of the HyperBus driver API.
 * The test confirms that invalid inputs are handled safely without side effects.
 */
static void TestHyperBus_GetDataBaseAddrNullHandle(void *args)
{
    uint32_t baseAddr = HYPERBUS_getHyperBusDataBaseAddr(NULL);

    TEST_ASSERT_EQUAL_UINT32(0U, baseAddr);

    DebugP_log("[HYPERBUS] GetDataBaseAddr NULL handle: PASS\r\n");
}

/* Test case to verify HyperBus memory-mapped read/write operations using bulk transfer.
 * This test validates that data can be written to and read from HyperBus memory using memcpy operations.
 * It initializes a write buffer with a repeating pattern, writes it to HyperRAM at a specific offset,
 * and verifies the data integrity by reading it back and comparing with the original buffer.
 * Cache synchronization is performed to ensure data consistency between CPU and HyperBus memory.
 * The test detects potential issues with memory-mapped I/O, cache coherency, or DMA operations.
 */
static void TestHyperBus_MemoryMappedReadWrite(void *args)
{
    HYPERBUS_Handle  handle  = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t         baseAddr;
    volatile uint8_t *memPtr;
    uint32_t          i;

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    TEST_ASSERT_NOT_EQUAL(0U, baseAddr);

    memPtr = (volatile uint8_t *)(uintptr_t)(baseAddr + TEST_HYPERBUS_NONECCRW_OFFSET);

    /* Fill write buffer */
    for (i = 0U; i < TEST_HYPERBUS_NONECCRW_SIZE; i++)
    {
        gTestHyperbus_WriteBuf[i] = (uint8_t)(i % 251U);
    }

    /* Write to HyperRAM */
    memcpy((void *)memPtr, gTestHyperbus_WriteBuf, TEST_HYPERBUS_NONECCRW_SIZE);
    CacheP_wbInv((void *)memPtr, TEST_HYPERBUS_NONECCRW_SIZE, CacheP_TYPE_ALLD);

    /* Read back */
    memcpy(gTestHyperbus_ReadBuf, (void *)memPtr, TEST_HYPERBUS_NONECCRW_SIZE);

    TEST_ASSERT_EQUAL_MEMORY(gTestHyperbus_WriteBuf, gTestHyperbus_ReadBuf,
                             TEST_HYPERBUS_NONECCRW_SIZE);

    DebugP_log("[HYPERBUS] MemoryMappedReadWrite: PASS\r\n");
}

/* Test case to verify HyperBus memory with 8-bit byte read/write operations.
 * This test validates that 8-bit values can be correctly written to and read from
 * HyperBus memory locations. It performs sequential write and read operations with
 * cache synchronization to ensure data consistency. The test uses a distinctive
 * pattern (0xA0 + offset) to verify proper data storage and retrieval across
 * multiple memory addresses, detecting potential alignment or access issues.
 */
static void TestHyperBus_CpuByteReadWrite(void *args)
{
    HYPERBUS_Handle   handle  = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t          baseAddr;
    volatile uint8_t *memPtr;
    uint32_t          i;

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    memPtr   = (volatile uint8_t *)(uintptr_t)(baseAddr + TEST_HYPERBUS_NONECCRW_OFFSET);

    for (i = 0U; i < 64U; i++)
    {
        memPtr[i] = (uint8_t)(0xA0U + i);
        CacheP_wbInv((void *)&memPtr[i], 1U, CacheP_TYPE_ALLD);
        TEST_ASSERT_EQUAL_UINT8((uint8_t)(0xA0U + i), memPtr[i]);
    }

    DebugP_log("[HYPERBUS] CpuByteReadWrite: PASS\r\n");
}

/* Test case to verify HyperBus memory with 16-bit half-word read/write operations.
 * This test validates that 16-bit values can be correctly written to and read from
 * HyperBus memory locations. It performs sequential write and read operations with
 * cache synchronization to ensure data consistency. The test uses a distinctive
 * pattern (0x1234 + offset) to verify proper data storage and retrieval across
 * multiple memory addresses, detecting potential alignment or access issues.
 */
static void TestHyperBus_CpuHalfWordReadWrite(void *args)
{
    HYPERBUS_Handle    handle  = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t           baseAddr;
    volatile uint16_t *memPtr;
    uint32_t           i;

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    memPtr   = (volatile uint16_t *)(uintptr_t)(baseAddr + TEST_HYPERBUS_NONECCRW_OFFSET);

    for (i = 0U; i < 32U; i++)
    {
        memPtr[i] = (uint16_t)(0x1234U + i);
        CacheP_wbInv((void *)&memPtr[i], 2U, CacheP_TYPE_ALLD);
        TEST_ASSERT_EQUAL_UINT16((uint16_t)(0x1234U + i), memPtr[i]);
    }

    DebugP_log("[HYPERBUS] CpuHalfWordReadWrite: PASS\r\n");
}

/* Test case to verify HyperBus memory with 32-bit word read/write operations.
 * This test validates that 32-bit values can be correctly written to and read from
 * HyperBus memory locations. It performs sequential write and read operations with
 * cache synchronization to ensure data consistency. The test uses a distinctive
 * pattern (0xDEAD0000 + offset) to verify proper data storage and retrieval across
 * multiple memory addresses, detecting potential alignment or access issues.
 */
static void TestHyperBus_CpuWordReadWrite(void *args)
{
    HYPERBUS_Handle    handle  = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t           baseAddr;
    volatile uint32_t *memPtr;
    uint32_t           i;

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    memPtr   = (volatile uint32_t *)(uintptr_t)(baseAddr + TEST_HYPERBUS_NONECCRW_OFFSET);

    for (i = 0U; i < 16U; i++)
    {
        memPtr[i] = 0xDEAD0000U + i;
        CacheP_wbInv((void *)&memPtr[i], 4U, CacheP_TYPE_ALLD);
        TEST_ASSERT_EQUAL_UINT32(0xDEAD0000U + i, memPtr[i]);
    }

    DebugP_log("[HYPERBUS] CpuWordReadWrite: PASS\r\n");
}

/* Test case to verify HyperBus memory with walking ones bit pattern.
 * This test validates that each bit position can be individually set and read
 * correctly across the accessible memory region. A walking ones pattern (where
 * only one bit is set at a time, shifting left through all positions) is written
 * and verified to ensure proper bit-level memory access and data integrity.
 * This pattern is effective at detecting address aliasing and bit-level faults.
 */
static void TestHyperBus_WalkingOnesPattern(void *args)
{
    HYPERBUS_Handle    handle  = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t           baseAddr;
    volatile uint32_t *memPtr;
    uint32_t           i;
    uint32_t           expected;

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    memPtr   = (volatile uint32_t *)(uintptr_t)(baseAddr + TEST_HYPERBUS_NONECCRW_OFFSET);

    for (i = 0U; i < 32U; i++)
    {
        memPtr[i] = (1U << i);
    }
    CacheP_wbInv((void *)memPtr, 32U * sizeof(uint32_t), CacheP_TYPE_ALLD);

    for (i = 0U; i < 32U; i++)
    {
        expected = (1U << i);
        TEST_ASSERT_EQUAL_UINT32(expected, memPtr[i]);
    }

    DebugP_log("[HYPERBUS] WalkingOnesPattern: PASS\r\n");
}

/* Test case to verify HyperBus memory access at different address offsets.
 * This test validates that the HyperBus controller correctly handles read/write
 * operations at multiple address offsets within the accessible memory region.
 * Three distinct offsets (0x0000, 0x8000, 0x10000) are tested to ensure data
 * integrity and proper address translation across the HyperBus address space.
 * Each offset is tested with unique data patterns to verify correct isolation.
 */
static void TestHyperBus_AddressOffsetAccess(void *args)
{
    HYPERBUS_Handle    handle   = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t           baseAddr;
    volatile uint32_t *ptr;
    /* Three offsets well below the 100 KB ECC region start */
    const uint32_t     offsets[3U] = { 0x0000U, 0x8000U, 0x10000U };
    uint32_t           i;

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);

    for (i = 0U; i < 3U; i++)
    {
        ptr    = (volatile uint32_t *)(uintptr_t)(baseAddr + offsets[i]);
        *ptr   = 0xBEEF0000U + offsets[i];
        CacheP_wbInv((void *)ptr, sizeof(uint32_t), CacheP_TYPE_ALLD);
        TEST_ASSERT_EQUAL_UINT32(0xBEEF0000U + offsets[i], *ptr);
    }

    DebugP_log("[HYPERBUS] AddressOffsetAccess: PASS\r\n");
}

/* Test case to verify HyperBus burst transfers at maximum length boundaries.
 * This test validates data integrity when performing read/write operations at
 * various boundary sizes (1 KB, 1025 B, 4 KB) to ensure the HyperBus controller
 * correctly handles burst transfers that cross or approach maximum length limits.
 * Data patterns are written to HyperBus memory, then read back and compared
 * to verify correctness at different transfer sizes and boundary conditions.
 */
static void TestHyperBus_BurstMaxLengthBoundary(void *args)
{
    HYPERBUS_Handle  handle  = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t         baseAddr;
    volatile uint8_t *memPtr;
    uint32_t          i;
    /* Transfer sizes to verify: 1 KB, 1025 B, 4 KB */
    const uint32_t sizes[3U] = { 1024U, 1025U, 4096U };

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    memPtr   = (volatile uint8_t *)(uintptr_t)(baseAddr + TEST_HYPERBUS_NONECCRW_OFFSET);

    for (i = 0U; i < 3U; i++)
    {
        uint32_t sz = sizes[i];
        uint32_t j;

        /* Fill write buffer */
        for (j = 0U; j < sz; j++)
        {
            gTestHyperbus_WriteBuf[j] = (uint8_t)(j % 199U);
        }

        memcpy((void *)memPtr, gTestHyperbus_WriteBuf, sz);
        CacheP_wbInv((void *)memPtr, sz, CacheP_TYPE_ALLD);
        memcpy(gTestHyperbus_ReadBuf, (void *)memPtr, sz);

        TEST_ASSERT_EQUAL_MEMORY(gTestHyperbus_WriteBuf, gTestHyperbus_ReadBuf, sz);

        DebugP_log("[HYPERBUS] BurstMaxLengthBoundary size=%u: PASS\r\n", (unsigned)sz);
    }
}

/* Test case to verify HyperBus data retention after a delay period.
 * This test writes a known pattern to HyperBus memory, then waits 100ms
 * to ensure data integrity is maintained over time. After the delay,
 * the data is read back and compared against the original pattern.
 * This validates that the HyperBus memory properly retains stored data
 * without corruption during idle periods.
 */
static void TestHyperBus_DataRetentionAfterDelay(void *args)
{
    HYPERBUS_Handle  handle  = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t         baseAddr;
    volatile uint8_t *memPtr;
    uint32_t          i;

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    memPtr   = (volatile uint8_t *)(uintptr_t)(baseAddr + TEST_HYPERBUS_NONECCRW_OFFSET);

    for (i = 0U; i < TEST_HYPERBUS_1KB_SIZE; i++)
    {
        gTestHyperbus_WriteBuf[i] = (uint8_t)(i ^ 0x5AU);
    }

    memcpy((void *)memPtr, gTestHyperbus_WriteBuf, TEST_HYPERBUS_1KB_SIZE);
    CacheP_wbInv((void *)memPtr, TEST_HYPERBUS_1KB_SIZE, CacheP_TYPE_ALLD);

    /* Wait 100 ms */
    ClockP_usleep(100U * 1000U);

    CacheP_inv((void *)memPtr, TEST_HYPERBUS_1KB_SIZE, CacheP_TYPE_ALLD);
    memcpy(gTestHyperbus_ReadBuf, (void *)memPtr, TEST_HYPERBUS_1KB_SIZE);

    TEST_ASSERT_EQUAL_MEMORY(gTestHyperbus_WriteBuf, gTestHyperbus_ReadBuf,
                             TEST_HYPERBUS_1KB_SIZE);

    DebugP_log("[HYPERBUS] DataRetentionAfterDelay: PASS\r\n");
}

/* Test case to verify HyperBus driver ECC enable/disable toggle functionality.
 * This test repeatedly toggles ECC between disabled and enabled states to validate
 * the robustness of ECC control mechanisms. It ensures that the HYPERBUS_enableECC
 * function correctly handles multiple transitions without errors. The test verifies
 * that ECC state changes are applied properly and the driver maintains integrity
 * across multiple enable/disable cycles.
 */
static void TestHyperBus_ECCEnableDisableToggle(void *args)
{
    HYPERBUS_Handle handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    int32_t         status;
    uint32_t        i;

    TEST_ASSERT_NOT_NULL(handle);

    for (i = 0U; i < TEST_HYPERBUS_ECC_TOGGLE_CNT; i++)
    {
        status = HYPERBUS_enableECC(handle, HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_DISABLE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        status = HYPERBUS_enableECC(handle, HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_ENABLE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    DebugP_log("[HYPERBUS] ECCEnableDisableToggle: PASS\r\n");
}

/* Test case to verify HyperBus driver ECC error clearing functionality.
 * This test clears all ECC error bits and validates that no error bits are asserted
 * immediately after the clear operation. It verifies both single-bit and double-bit
 * error registers are properly reset to zero. The test ensures that the HYPERBUS_clearECCError
 * and HYPERBUS_getECCErrorInfo functions work correctly. This validates proper ECC
 * error state management and recovery mechanisms in the driver.
 */
static void TestHyperBus_ECCClearAllErrors(void *args)
{
    HYPERBUS_Handle       handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    HYPERBUS_ECCErrorInfo info;
    int32_t               status;

    TEST_ASSERT_NOT_NULL(handle);

    status = HYPERBUS_clearECCError(handle, HYPERBUS_ECC_ERR_ALL);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = HYPERBUS_getECCErrorInfo(handle, &info);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* No error bits should be asserted immediately after a clear */
    TEST_ASSERT_EQUAL_UINT8(0U, info.singleBitError);
    TEST_ASSERT_EQUAL_UINT8(0U, info.doubleBitError);

    DebugP_log("[HYPERBUS] ECCClearAllErrors: PASS\r\n");
}

/* Test case to verify HyperBus driver ECC region configuration with multiple regions.
 * This test configures all four ECC regions with non-overlapping 24 KB areas within the
 * 100 KB – 196 KB logical address range, validating proper multi-region setup.
 * It verifies that the driver correctly handles all four regions simultaneously.
 * The test ensures that region configuration is applied successfully and without errors.
 * This validates comprehensive ECC protection across multiple memory regions.
 */
static void TestHyperBus_ECCConfigureAllRegions(void *args)
{
    HYPERBUS_Handle  handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    HYPERBUS_Config *cfg;
    int32_t          status;

    TEST_ASSERT_NOT_NULL(handle);

    cfg = (HYPERBUS_Config *)handle;

    /* Set four non-overlapping 24 KB ECC regions within the already-primed
     * 100 KB – 196 KB logical address range. */
    cfg->attrs->eccRegion->eccRegionStart0 = TEST_HYPERBUS_ECC_100KB_OFFSET;
    cfg->attrs->eccRegion->eccRegionSize0  = TEST_HYPERBUS_ECC_24KB_SIZE;
    cfg->attrs->eccRegion->eccRegionStart1 = TEST_HYPERBUS_ECC_124KB_OFFSET;
    cfg->attrs->eccRegion->eccRegionSize1  = TEST_HYPERBUS_ECC_24KB_SIZE;
    cfg->attrs->eccRegion->eccRegionStart2 = TEST_HYPERBUS_ECC_148KB_OFFSET;
    cfg->attrs->eccRegion->eccRegionSize2  = TEST_HYPERBUS_ECC_24KB_SIZE;
    cfg->attrs->eccRegion->eccRegionStart3 = TEST_HYPERBUS_ECC_172KB_OFFSET;
    cfg->attrs->eccRegion->eccRegionSize3  = TEST_HYPERBUS_ECC_24KB_SIZE;

    status = HYPERBUS_configureECC(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("[HYPERBUS] ECCConfigureAllRegions: PASS\r\n");
}

/* Test case to verify HyperBus driver ECC region disable functionality.
 * This test configures region 0 as active while disabling regions 1-3 by setting their sizes to zero.
 * It validates that the driver correctly handles disabled ECC regions and only processes active regions.
 * The test confirms that configuring regions with zero size does not cause errors or side effects.
 * It ensures the driver's ability to selectively enable/disable ECC regions as needed.
 * This validates proper ECC region management and selective protection of memory areas.
 */
static void TestHyperBus_ECCRegionDisabledSkip(void *args)
{
    HYPERBUS_Handle  handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    HYPERBUS_Config *cfg;
    int32_t          status;

    TEST_ASSERT_NOT_NULL(handle);

    cfg = (HYPERBUS_Config *)handle;

    /* Region 0 active, regions 1-3 disabled (size = 0) */
    cfg->attrs->eccRegion->eccRegionStart0 = TEST_HYPERBUS_ECC_100KB_OFFSET;
    cfg->attrs->eccRegion->eccRegionSize0  = TEST_HYPERBUS_ECC_24KB_SIZE;
    cfg->attrs->eccRegion->eccRegionStart1 = TEST_HYPERBUS_ECC_124KB_OFFSET;
    cfg->attrs->eccRegion->eccRegionSize1  = TEST_HYPERBUS_ECC_ZERO_SIZE;
    cfg->attrs->eccRegion->eccRegionStart2 = TEST_HYPERBUS_ECC_148KB_OFFSET;
    cfg->attrs->eccRegion->eccRegionSize2  = TEST_HYPERBUS_ECC_ZERO_SIZE;
    cfg->attrs->eccRegion->eccRegionStart3 = TEST_HYPERBUS_ECC_172KB_OFFSET;
    cfg->attrs->eccRegion->eccRegionSize3  = TEST_HYPERBUS_ECC_ZERO_SIZE;

    status = HYPERBUS_configureECC(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("[HYPERBUS] ECCRegionDisabledSkip: PASS\r\n");
}

/* Test case to verify HyperBus driver ECC single-bit error callback functionality.
 * This test injects a single-bit error in the ECC-protected memory region and validates
 * that the error is correctly detected and reported as a 1-bit error (SEC - Single Error Correct).
 * It confirms the ECC error callback is invoked and the error type is properly classified.
 * The test verifies the driver's ability to handle correctable errors and trigger callbacks.
 * This validates robust error detection and callback mechanism for memory fault handling.
 */
static void TestHyperBus_ECCSecErrCallback(void *args)
{
    HYPERBUS_Handle handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    int32_t         status;

    TEST_ASSERT_NOT_NULL(handle);

    /* The ECC region 0 (100 KB – 200 KB) is primed by Board_driversOpen() */
    status = TestHyperbus_injectSecError(handle,
                                         TEST_HYPERBUS_ECC_100KB_OFFSET + TEST_HYPERBUS_ECC_TEST_OFFSET);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT8(HYPERBUS_ECC_1B_ERROR, gTestHyperbus_EccErrType);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, gTestHyperbus_EccCbkCount);

    DebugP_log("[HYPERBUS] ECCSecErrCallback: PASS\r\n");
}

/* Test case to verify HyperBus driver ECC double-bit error callback functionality.
 * This test injects a double-bit error in the ECC-protected memory region and validates
 * that the error is correctly detected and reported as a 2-bit error (DED - Detectible Error).
 * It confirms the ECC error callback is invoked and the error type is properly classified.
 * The test verifies the driver's ability to handle uncorrectable errors and trigger callbacks.
 * This validates robust error detection and callback mechanism for critical memory faults.
 */
static void TestHyperBus_ECCDedErrCallback(void *args)
{
    HYPERBUS_Handle handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    int32_t         status;

    TEST_ASSERT_NOT_NULL(handle);

    status = TestHyperbus_injectDedError(handle,
                                          TEST_HYPERBUS_ECC_100KB_OFFSET + TEST_HYPERBUS_ECC_TEST_OFFSET);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT8(HYPERBUS_ECC_2B_ERROR, gTestHyperbus_EccErrType);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, gTestHyperbus_EccCbkCount);

    DebugP_log("[HYPERBUS] ECCDedErrCallback: PASS\r\n");
}

/* Test case to verify HyperBus driver open function boundary validation.
 * This test ensures that HYPERBUS_open() properly validates configuration indices.
 * It confirms that invalid indices return NULL while valid handles remain accessible.
 * The test covers index equal to driver count, extreme out-of-range values, and recovery.
 * It verifies the driver returns NULL for out-of-range parameters without corrupting state.
 * This validates robust error handling and prevents invalid driver instance access.
 */
static void TestHyperBus_BoundaryOpenInvalidIndex(void *args)
{
    HYPERBUS_Handle handle;

    /* Index equal to the driver count (one past the end) */
    handle = HYPERBUS_open(gHyperBusConfigNum);
    TEST_ASSERT_NULL(handle);

    /* Extreme out-of-range index */
    handle = HYPERBUS_open(0xFFFFFFFFU);
    TEST_ASSERT_NULL(handle);

    /* Existing handle must remain valid */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NOT_NULL(handle);

    DebugP_log("[HYPERBUS] BoundaryOpenInvalidIndex: PASS\r\n");
}

/* Test case to verify HyperBus ECC region index boundary validation.
 * This test ensures that setECCRegion() properly validates region indices.
 * It confirms that valid indices (0-3) are accepted while invalid indices fail.
 * The test covers the last valid region index, first invalid index, and saturated values.
 * It verifies the driver returns appropriate error status for out-of-range parameters.
 * This validates robust error handling and prevents invalid ECC region configurations.
 */
static void TestHyperBus_BoundarySetECCRegionInvalidIndex(void *args)
{
    HYPERBUS_Handle handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    int32_t         status;

    TEST_ASSERT_NOT_NULL(handle);

    /* Last valid region index */
    status = HYPERBUS_setECCRegion(handle, 3U);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* First invalid index */
    status = HYPERBUS_setECCRegion(handle, HYPERBUS_FSS_FSAS_NUM_ECC_REGIONS);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Saturated invalid index */
    status = HYPERBUS_setECCRegion(handle, 0xFFU);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    DebugP_log("[HYPERBUS] BoundarySetECCRegionInvalidIndex: PASS\r\n");
}

/* Test case to verify HyperBus ECC behavior with corrupted FSS-FSAS base address.
 * This test validates error handling when the FSS-FSAS base address is set to NULL.
 * It ensures that ECC operations fail gracefully with appropriate error status codes.
 * The test verifies enableECC, setECCRegion, clearECCError, and getECCErrorInfo functions.
 * It confirms the driver properly detects invalid base addresses and returns failures.
 * After testing, it restores the original base address to maintain device integrity.
 */
static void TestHyperBus_BoundaryECCNullFsasBase(void *args)
{
    HYPERBUS_Handle  handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    HYPERBUS_Config *cfg;
    HYPERBUS_Object *obj;
    uintptr_t        savedFsasBase;
    int32_t          status;
    HYPERBUS_ECCErrorInfo info;

    TEST_ASSERT_NOT_NULL(handle);

    cfg           = (HYPERBUS_Config *)handle;
    obj           = cfg->object;
    savedFsasBase = obj->fssHandle.fsas_base;

    /* Corrupt the FSS-FSAS base address */
    obj->fssHandle.fsas_base = (uintptr_t)NULL;

    status = HYPERBUS_enableECC(handle, HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_ENABLE);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = HYPERBUS_setECCRegion(handle, 0U);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = HYPERBUS_clearECCError(handle, HYPERBUS_ECC_ERR_ALL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = HYPERBUS_getECCErrorInfo(handle, &info);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Restore the base address */
    obj->fssHandle.fsas_base = savedFsasBase;

    DebugP_log("[HYPERBUS] BoundaryECCNullFsasBase: PASS\r\n");
}

/* Test case to verify HyperBus open and close behavior.
 * This test validates that a device can be successfully opened and closed.
 * It verifies that the device handle is initially NULL when closed.
 * Upon successful open, it confirms the handle is valid and accessible.
 * After closing, it verifies the handle becomes invalid again.
 * This ensures proper resource management and device lifecycle handling.
 */
static void TestHyperBus_OpenClose(void *args)
{
    HYPERBUS_Handle handle;

    /* Driver must be closed before this test */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    /* Open */
    handle = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NOT_NULL(handle);
    TEST_ASSERT_NOT_EQUAL(0U, HYPERBUS_getHyperBusDataBaseAddr(handle));

    /* Close */
    HYPERBUS_close(handle);

    /* Handle should no longer be valid */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    DebugP_log("[HYPERBUS] OpenClose: PASS\r\n");
}

/* Test case to verify HyperBus open behavior when already open.
 * This test validates that opening an already open device fails correctly.
 * It opens a device successfully, then attempts a second open which should fail.
 * The test verifies the first handle remains valid after the failed second open.
 * It confirms the base address is accessible through the valid handle.
 * Finally, it closes the device and verifies proper cleanup.
 */
static void TestHyperBus_OpenAlreadyOpen(void *args)
{
    HYPERBUS_Handle handle1;
    HYPERBUS_Handle handle2;

    /* Driver must be closed before this test */
    handle1 = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle1);

    handle1 = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NOT_NULL(handle1);

    /* Second open attempt must fail */
    handle2 = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle2);

    /* Original handle still valid */
    TEST_ASSERT_NOT_NULL(handle1);
    TEST_ASSERT_NOT_EQUAL(0U, HYPERBUS_getHyperBusDataBaseAddr(handle1));

    HYPERBUS_close(handle1);

    DebugP_log("[HYPERBUS] OpenAlreadyOpen: PASS\r\n");
}

/* Test case to verify HyperBus device configuration with NONE type.
 * This test validates that the driver rejects invalid device type configurations.
 * It saves the current device type, sets it to HYPERBUS_DEVICETYPE_NONE, and verifies the open fails.
 * The original device type is then restored to ensure proper driver state recovery.
 * After restoration, a normal open is attempted to confirm the driver works correctly again.
 * This test ensures proper validation and error handling of device type configurations.
 */
static void TestHyperBus_DeviceCfgNoneType(void *args)
{
    HYPERBUS_Handle  handle;
    HYPERBUS_Attrs  *mutableAttrs;
    uint32_t         savedType;

    /* Driver must be closed before this test */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    mutableAttrs = (HYPERBUS_Attrs *)gHyperBusConfig[CONFIG_HYPERBUS0].attrs;
    savedType    = mutableAttrs->deviceType;

    mutableAttrs->deviceType = (uint32_t)HYPERBUS_DEVICETYPE_NONE;

    handle = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    /* Restore deviceType */
    mutableAttrs->deviceType = savedType;

    /* Normal open must now succeed */
    handle = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NOT_NULL(handle);

    /* Close so that test_hyperbus_main can reopen with the full board stack */
    HYPERBUS_close(handle);

    DebugP_log("[HYPERBUS] DeviceCfgNoneType: PASS\r\n");
}

/* Test case to verify HyperBus open and close functionality under stress conditions.
 * This test repeatedly opens and closes the HyperBus driver in a loop.
 * It validates that handles are properly created and invalidated after each cycle.
 * The test ensures no resource leaks occur during repetitive open/close operations.
 * It verifies that the base address is correctly retrieved after each open.
 * Overall, it assesses the robustness and stability of driver lifecycle management.
 */
static void TestHyperBus_StressOpenCloseRepeat(void *args)
{
    HYPERBUS_Handle  handle;
    uint32_t         i;

    /* Drivers are open at entry; close before looping */
    Board_hyperRamClose();
    Drivers_hyperbusClose();

    for (i = 0U; i < TEST_HYPERBUS_STRESS_OPEN_CLOSE_CNT; i++)
    {
        handle = HYPERBUS_open(CONFIG_HYPERBUS0);
        TEST_ASSERT_NOT_NULL(handle);
        TEST_ASSERT_NOT_EQUAL(0U, HYPERBUS_getHyperBusDataBaseAddr(handle));

        HYPERBUS_close(handle);

        /* Verify handle is invalidated after close */
        handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
        TEST_ASSERT_NULL(handle);

        DebugP_log("[HYPERBUS] StressOpenClose cycle %u/%u\r\n",
                   (unsigned)(i + 1U),
                   (unsigned)TEST_HYPERBUS_STRESS_OPEN_CLOSE_CNT);
    }
    /* test_hyperbus_main will call Drivers_hyperbusOpen() + Board_driversOpen() */
    DebugP_log("[HYPERBUS] StressOpenCloseRepeat: PASS\r\n");
}

/* Test case to verify HyperBus ECC toggle functionality under stress conditions.
 * This test repeatedly enables and disables ECC, then clears any ECC errors.
 * It validates that ECC can be toggled without impacting driver stability.
 * The test ensures error state is properly cleared after each toggle cycle.
 * It verifies the robustness of ECC management APIs under repetitive operations.
 * Performance and reliability of the ECC subsystem are thoroughly assessed.
 */
static void TestHyperBus_StressECCToggleRepeat(void *args)
{
    HYPERBUS_Handle handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    int32_t         status;
    uint32_t        i;

    TEST_ASSERT_NOT_NULL(handle);

    for (i = 0U; i < TEST_HYPERBUS_ECC_TOGGLE_CNT; i++)
    {
        status = HYPERBUS_enableECC(handle, HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_DISABLE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        status = HYPERBUS_enableECC(handle, HYPERBUS_FSS_FSAS_GENREGS_SYSCONFIG_ECC_ENABLE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        status = HYPERBUS_clearECCError(handle, HYPERBUS_ECC_ERR_ALL);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    DebugP_log("[HYPERBUS] StressECCToggleRepeat: PASS\r\n");
}

/* Test case to verify HyperBus large memory access with stress conditions.
 * This test writes a pseudo-random pattern to a large memory region,
 * invalidates the cache, and reads back the data to verify correctness.
 * It ensures that no ECC errors are triggered during non-ECC region access.
 * The test validates data integrity and error reporting mechanisms.
 * Performance under large data transfer conditions is also assessed.
 */
static void TestHyperBus_StressLargeMemoryAccess(void *args)
{
    HYPERBUS_Handle       handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t              baseAddr;
    volatile uint8_t     *memPtr;
    HYPERBUS_ECCErrorInfo info;
    uint32_t              i;
    int32_t               status;

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr = HYPERBUS_getHyperBusDataBaseAddr(handle);
    memPtr   = (volatile uint8_t *)(uintptr_t)(baseAddr + TEST_HYPERBUS_LARGE_RW_OFFSET);

    /* Fill write buffer with a pseudo-random pattern */
    for (i = 0U; i < TEST_HYPERBUS_LARGE_RW_SIZE; i++)
    {
        gTestHyperbus_WriteBuf[i] = (uint8_t)((i * 31U + 7U) % 256U);
    }

    HYPERBUS_clearECCError(handle, HYPERBUS_ECC_ERR_ALL);

    memcpy((void *)memPtr, gTestHyperbus_WriteBuf, TEST_HYPERBUS_LARGE_RW_SIZE);
    CacheP_wbInv((void *)memPtr, TEST_HYPERBUS_LARGE_RW_SIZE, CacheP_TYPE_ALLD);
    memcpy(gTestHyperbus_ReadBuf, (void *)memPtr, TEST_HYPERBUS_LARGE_RW_SIZE);

    TEST_ASSERT_EQUAL_MEMORY(gTestHyperbus_WriteBuf, gTestHyperbus_ReadBuf,
                             TEST_HYPERBUS_LARGE_RW_SIZE);

    /* No ECC errors should have been triggered (non-ECC region access) */
    status = HYPERBUS_getECCErrorInfo(handle, &info);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT8(0U, info.singleBitError);
    TEST_ASSERT_EQUAL_UINT8(0U, info.doubleBitError);

    DebugP_log("[HYPERBUS] StressLargeMemoryAccess: PASS\r\n");
}

/* Test case to verify the ECC-disabled code path inside HYPERBUS_configureFss.
 * When enableEccFlag is set to CSL_FALSE in the driver attributes, the function
 * takes the else branch and calls HYPERBUS_enableECC with the DISABLE flag instead
 * of invoking HYPERBUS_configureECC. This test saves the original flag, overrides
 * it with CSL_FALSE, opens the driver so HYPERBUS_configureFss is reached, verifies
 * a valid handle is returned, then restores the original flag and closes the driver.
 * This covers the uncovered else branch at line 276 in HYPERBUS_configureFss.
 */
static void TestHyperBus_FssEccDisabled(void *args)
{
    HYPERBUS_Handle  handle;
    HYPERBUS_Attrs  *mutableAttrs;
    uint32_t         savedEccFlag;

    /* Driver must be closed before this test */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    mutableAttrs = (HYPERBUS_Attrs *)gHyperBusConfig[CONFIG_HYPERBUS0].attrs;
    savedEccFlag = mutableAttrs->enableEccFlag;

    /* Disable ECC flag to force the else branch in HYPERBUS_configureFss */
    mutableAttrs->enableEccFlag = (uint32_t)CSL_FALSE;

    handle = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NOT_NULL(handle);

    /* Restore enableEccFlag before closing */
    mutableAttrs->enableEccFlag = savedEccFlag;
    HYPERBUS_close(handle);

    DebugP_log("[HYPERBUS] FssEccDisabled: PASS\r\n");
}

/* Test case to verify the OTFA-enabled code path inside HYPERBUS_configureFss.
 * When OTFAEnable is set to CSL_TRUE in the driver attributes, the function enters
 * the if branch which contains only a comment (OTFA not supported) and falls through
 * without configuring OTFA. The default configuration has OTFAEnable = false, so
 * the if branch (lines 282-285) is never reached in normal operation. This test saves
 * the original OTFAEnable, sets it to CSL_TRUE, opens the driver so the branch is
 * taken, verifies the open succeeds, then restores the flag and closes the driver.
 * This covers the uncovered OTFA-enabled if branch at lines 282-285 in HYPERBUS_configureFss.
 */
static void TestHyperBus_FssOtfaEnabled(void *args)
{
    HYPERBUS_Handle  handle;
    HYPERBUS_Attrs  *mutableAttrs;
    uint32_t         savedOtfaEnable;

    /* Driver must be closed before this test */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    mutableAttrs    = (HYPERBUS_Attrs *)gHyperBusConfig[CONFIG_HYPERBUS0].attrs;
    savedOtfaEnable = mutableAttrs->OTFAEnable;

    /* Enable OTFA to force the if branch (no-op body) in HYPERBUS_configureFss */
    mutableAttrs->OTFAEnable = (uint32_t)CSL_TRUE;

    handle = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NOT_NULL(handle);

    /* Restore OTFAEnable before closing */
    mutableAttrs->OTFAEnable = savedOtfaEnable;
    HYPERBUS_close(handle);

    DebugP_log("[HYPERBUS] FssOtfaEnabled: PASS\r\n");
}

/* Test case to verify HYPERBUS_getLatencyCode covers all switch-case branches.
 * The static HYPERBUS_getLatencyCode() is called indirectly from HYPERBUS_setDeviceCfg
 * during HYPERBUS_open. The default configuration uses latency = 6 (case 6), leaving
 * cases 3, 4, 5, and the default (invalid) branch uncovered. This test iterates through
 * latency values 3, 4, 5 and 7 (invalid), opening and closing the driver for each value
 * to exercise every remaining branch of the switch statement (lines 385-400).
 * The original latency value is restored at the end of the test.
 */
static void TestHyperBus_LatencyCodeVariants(void *args)
{
    HYPERBUS_Handle  handle;
    HYPERBUS_Attrs  *mutableAttrs;
    uint32_t         savedLatency;
    /* Latency 3 → code 0xE, 4 → 0xF, 5 → 0x0, 7 → default (0x1) */
    const uint32_t   latencyVals[] = { 3U, 4U, 5U, 7U };
    uint32_t         i;

    /* Driver must be closed before this test */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    mutableAttrs = (HYPERBUS_Attrs *)gHyperBusConfig[CONFIG_HYPERBUS0].attrs;
    savedLatency = mutableAttrs->latency;

    for (i = 0U; i < (sizeof(latencyVals) / sizeof(latencyVals[0U])); i++)
    {
        mutableAttrs->latency = latencyVals[i];

        handle = HYPERBUS_open(CONFIG_HYPERBUS0);
        TEST_ASSERT_NOT_NULL(handle);

        HYPERBUS_close(handle);

        handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
        TEST_ASSERT_NULL(handle);

        DebugP_log("[HYPERBUS] LatencyCodeVariants latency=%u: PASS\r\n",
                   (unsigned)latencyVals[i]);
    }

    /* Restore original latency */
    mutableAttrs->latency = savedLatency;

    DebugP_log("[HYPERBUS] LatencyCodeVariants: PASS\r\n");
}

/* Test case to verify HYPERBUS_setDeviceCfg handles the HYPERFLASH device type.
 * When deviceType is set to HYPERBUS_DEVICETYPE_HYPERFLASH, HYPERBUS_setDeviceCfg
 * falls into the else branch (lines 653-656) which is a placeholder for future
 * device configuration and returns SystemP_SUCCESS without writing MCR/MTR/MBAR.
 * The default configuration uses HYPERRAM, so this else branch is never reached
 * in normal operation. Hardware registers retain their values from the previous
 * open, so the DLL lock and ECC configuration steps in HYPERBUS_open still succeed.
 * The test restores the original device type before closing the driver.
 * This covers the uncovered else branch at lines 653-656 in HYPERBUS_setDeviceCfg.
 */
static void TestHyperBus_DeviceCfgHyperFlash(void *args)
{
    HYPERBUS_Handle  handle;
    HYPERBUS_Attrs  *mutableAttrs;
    uint32_t         savedType;

    /* Driver must be closed before this test */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    mutableAttrs = (HYPERBUS_Attrs *)gHyperBusConfig[CONFIG_HYPERBUS0].attrs;
    savedType    = mutableAttrs->deviceType;

    mutableAttrs->deviceType = (uint32_t)HYPERBUS_DEVICETYPE_HYPERFLASH;

    handle = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NOT_NULL(handle);

    /* Restore deviceType before closing */
    mutableAttrs->deviceType = savedType;
    HYPERBUS_close(handle);

    DebugP_log("[HYPERBUS] DeviceCfgHyperFlash: PASS\r\n");
}

/* Test case to verify the write non-alignment error path in HYPERBUS_ECCisr.
 * A write non-alignment error (lines 687-689) is triggered when the FSS hardware
 * detects a write to the ECC-protected region that does not cover a full 32-byte
 * ECC block. This test seeds the target ECC block with known data, snapshots it
 * into gTestHyperbus_EccBufCheck so the shared callback can restore the memory,
 * then issues a single-byte write inside the ECC region to trigger the error.
 * After the write-back the test waits for the ISR callback to post the semaphore
 * and verifies that the reported error type is HYPERBUS_ECC_WRITE_NONALIGN_ERROR.
 * This covers the uncovered errorType assignment at lines 687-689 in HYPERBUS_ECCisr.
 */
static void TestHyperBus_ECCWriteNonAlignErrCallback(void *args)
{
    HYPERBUS_Handle   handle   = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    uint32_t          baseAddr;
    uintptr_t         blockAddr;
    volatile uint8_t *bytePtr;
    int32_t           status;

    TEST_ASSERT_NOT_NULL(handle);

    baseAddr  = HYPERBUS_getHyperBusDataBaseAddr(handle);
    /* Use a 32-byte-aligned offset within ECC region 0 */
    blockAddr = (uintptr_t)(baseAddr + TEST_HYPERBUS_ECC_100KB_OFFSET +
                            TEST_HYPERBUS_ECC_TEST_OFFSET);

    SemaphoreP_constructBinary(&gTestHyperbus_EccSem, 0U);
    gTestHyperbus_EccTestAddr = TEST_HYPERBUS_ECC_100KB_OFFSET + TEST_HYPERBUS_ECC_TEST_OFFSET;
    gTestHyperbus_EccErrType  = 0xFFU;
    gTestHyperbus_EccCbkCount = 0U;

    /* Seed the ECC block with valid data and snapshot it for the callback restore */
    memset((void *)blockAddr, 0xC3U, TEST_HYPERBUS_ECC_BLOCK_SIZE);
    CacheP_wbInv((void *)blockAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE, CacheP_TYPE_ALLD);
    memcpy(gTestHyperbus_EccBufCheck, (void *)blockAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE);

    /* Single-byte write to the ECC region triggers a write non-alignment error
     * because the write does not cover a full 32-byte ECC data block. A normal
     * cached store would be absorbed into the cache line and written back as a
     * full, aligned 32-byte block, so the FSS would never observe a partial
     * transaction. The data cache is therefore temporarily disabled so the
     * single-byte store reaches the FSS directly as a sub-block write. */
    bytePtr  = (volatile uint8_t *)blockAddr;
    CacheP_wbInv((void *)blockAddr, TEST_HYPERBUS_ECC_BLOCK_SIZE, CacheP_TYPE_ALLD);
    CacheP_disable(CacheP_TYPE_ALLD);
    *bytePtr = 0xAAU;
    CacheP_enable(CacheP_TYPE_ALLD);

    /* Wait for the ECC ISR to signal completion */
    status = SemaphoreP_pend(&gTestHyperbus_EccSem,
                             ClockP_usecToTicks(TEST_HYPERBUS_ECC_SEM_TIMEOUT_US));
    SemaphoreP_destruct(&gTestHyperbus_EccSem);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT8(HYPERBUS_ECC_WRITE_NONALIGN_ERROR, gTestHyperbus_EccErrType);
    TEST_ASSERT_GREATER_THAN_UINT32(0U, gTestHyperbus_EccCbkCount);

    DebugP_log("[HYPERBUS] ECCWriteNonAlignErrCallback: PASS\r\n");
}

/* Test case to verify HYPERBUS_configureECC returns failure when an ECC region
 * start address plus size exceeds the effective device capacity.
 * The effective capacity of a 64 MB HyperRAM device with ECC overhead is
 * approximately 56.9 MB (deviceSize * 32 / 36). Configuring region 0 at a
 * 60 MB start address places the region beyond this boundary, so the range
 * check inside HYPERBUS_configureECC must detect the overflow and return
 * SystemP_FAILURE without proceeding to the interrupt setup. This covers the
 * uncovered failure branch at lines 756-759 in HYPERBUS_configureECC.
 * The original region values are restored and ECC is reconfigured afterwards
 * so that subsequent tests can continue with a correctly configured ECC interrupt.
 */
static void TestHyperBus_ECCRegionExceedsDeviceSize(void *args)
{
    HYPERBUS_Handle  handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    HYPERBUS_Config *cfg;
    int32_t          status;
    uint32_t         savedStart0;
    uint32_t         savedSize0;

    TEST_ASSERT_NOT_NULL(handle);

    cfg         = (HYPERBUS_Config *)handle;
    savedStart0 = cfg->attrs->eccRegion->eccRegionStart0;
    savedSize0  = cfg->attrs->eccRegion->eccRegionSize0;

    /* 60 MB start + 24 KB size exceeds the ~56.9 MB effective device capacity */
    cfg->attrs->eccRegion->eccRegionStart0 = TEST_HYPERBUS_ECC_60MB_OFFSET;
    cfg->attrs->eccRegion->eccRegionSize0  = TEST_HYPERBUS_ECC_24KB_SIZE;

    status = HYPERBUS_configureECC(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Restore original ECC region configuration */
    cfg->attrs->eccRegion->eccRegionStart0 = savedStart0;
    cfg->attrs->eccRegion->eccRegionSize0  = savedSize0;

    /* Re-configure ECC to restore a valid interrupt-enabled state for subsequent tests */
    status = HYPERBUS_configureECC(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("[HYPERBUS] ECCRegionExceedsDeviceSize: PASS\r\n");
}

/* Test case to verify HYPERBUS_configureECC returns failure when the ECC regions
 * pointer in the driver attributes is NULL.
 * HYPERBUS_configureECC guards all region configuration with a NULL check on
 * attrs->eccRegion. When the pointer is NULL the function must return
 * SystemP_FAILURE immediately via the else branch at lines 801-804 without
 * accessing any region fields or enabling ECC. This test saves the original
 * eccRegion pointer, sets it to NULL, calls HYPERBUS_configureECC, asserts
 * the expected failure, restores the pointer, and then reconfigures ECC to
 * re-establish a valid interrupt-enabled state for subsequent tests.
 * This covers the uncovered else-branch at lines 801-804 in HYPERBUS_configureECC.
 */
static void TestHyperBus_ECCNullRegionFailure(void *args)
{
    HYPERBUS_Handle       handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    HYPERBUS_Config      *cfg;
    HYPERBUS_ECCRegions  *savedEccRegion;
    int32_t               status;

    TEST_ASSERT_NOT_NULL(handle);

    cfg            = (HYPERBUS_Config *)handle;
    savedEccRegion = (HYPERBUS_ECCRegions *)cfg->attrs->eccRegion;

    /* Set eccRegion to NULL to force the else-failure path */
    ((HYPERBUS_Attrs *)cfg->attrs)->eccRegion = NULL;

    status = HYPERBUS_configureECC(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Restore the original ECC region pointer */
    ((HYPERBUS_Attrs *)cfg->attrs)->eccRegion = savedEccRegion;

    /* Re-configure ECC to restore interrupt enable and valid region state */
    status = HYPERBUS_configureECC(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    DebugP_log("[HYPERBUS] ECCNullRegionFailure: PASS\r\n");
}

/* Test case to verify the HwiP interrupt registration block inside HYPERBUS_configureECC.
 * The block at lines 878-888 is entered only when ECCintrEnable is non-zero AND
 * ECCintrNum is not HYPERBUS_INVALID_INTERRUPT_NUMBER (0xFFFFFFFF). If the default
 * configuration has ECCintrEnable = 0 or ECCintrNum = HYPERBUS_INVALID_INTERRUPT_NUMBER
 * the block is never reached and those lines remain uncovered. This test saves the
 * original values of both fields, forces ECCintrEnable to 1 and keeps ECCintrNum
 * unchanged (or falls back to the known ECC interrupt number 181 if the stored value
 * is HYPERBUS_INVALID_INTERRUPT_NUMBER), then calls HYPERBUS_configureECC to execute
 * the HwiP_construct path. Both fields are restored before the function returns.
 * This covers the uncovered HwiP registration path at lines 878-888 in HYPERBUS_configureECC.
 */
static void TestHyperBus_ECCIntrRegistration(void *args)
{
    HYPERBUS_Handle  handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    HYPERBUS_Config *cfg;
    HYPERBUS_Attrs  *mutableAttrs;
    uint32_t         savedIntrEnable;
    uint32_t         savedIntrNum;
    int32_t          status;

    TEST_ASSERT_NOT_NULL(handle);

    cfg           = (HYPERBUS_Config *)handle;
    mutableAttrs  = (HYPERBUS_Attrs *)cfg->attrs;
    savedIntrEnable = mutableAttrs->ECCintrEnable;
    savedIntrNum    = mutableAttrs->ECCintrNum;

    /* Force a valid interrupt enable and number to enter the HwiP registration block */
    mutableAttrs->ECCintrEnable = 1U;
    if (mutableAttrs->ECCintrNum == 0xFFFFFFFFU)
    {
        /* Fall back to the reference ECC interrupt number from the platform config */
        mutableAttrs->ECCintrNum = 181U;
    }

    status = HYPERBUS_configureECC(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Restore original interrupt configuration */
    mutableAttrs->ECCintrEnable = savedIntrEnable;
    mutableAttrs->ECCintrNum    = savedIntrNum;

    DebugP_log("[HYPERBUS] ECCIntrRegistration: PASS\r\n");
}

/* Test case to verify the FIFO RAM auto-initialization timeout path in
 * HYPERBUS_open. After the clocks are enabled, HYPERBUS_open polls the
 * RAM_STAT_REG[INIT_DONE] bit until it reads 1, breaking out with a timeout if
 * the bit never sets within HYPERBUS_DEFAULT_REGISTER_READ_TIMEOUT_US. On real
 * hardware INIT_DONE is already set, so the wait loop and its timeout branch
 * (lines 477-487 in hyperbus_v0.c) never execute. This test points the
 * peripheral sys base (ssBaseAddr) at a fake SYSCFG register block whose
 * RAM_STAT_REG reads 0 (INIT_DONE = 0), so the loop spins until it times out.
 * It verifies HYPERBUS_open returns NULL, then restores the original base.
 * This covers the uncovered RAM-init wait loop and timeout at lines 477-487.
 */
static void TestHyperBus_RamInitDoneTimeout(void *args)
{
    HYPERBUS_Handle  handle;
    HYPERBUS_Attrs  *mutableAttrs;
    uint32_t         savedSsBase;

    /* Driver must be closed before this test */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    mutableAttrs = (HYPERBUS_Attrs *)gHyperBusConfig[CONFIG_HYPERBUS0].attrs;
    savedSsBase  = mutableAttrs->ssBaseAddr;

    /* Fake SYSCFG block with INIT_DONE = 0 so the RAM auto-init poll never
     * completes and exits through the timeout path. */
    gTestHyperbus_FakeSyscfg[0] = 0U;   /* REVISION_REG               */
    gTestHyperbus_FakeSyscfg[1] = 0U;   /* DLL_STAT_REG               */
    gTestHyperbus_FakeSyscfg[2] = 0U;   /* RAM_STAT_REG: INIT_DONE = 0 */

    mutableAttrs->ssBaseAddr = (uint32_t)(uintptr_t)&gTestHyperbus_FakeSyscfg[0];

    handle = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    /* Restore the original sys base address */
    mutableAttrs->ssBaseAddr = savedSsBase;

    DebugP_log("[HYPERBUS] RamInitDoneTimeout: PASS\r\n");
}

/* Test case to verify the Master DLL lock timeout path in HYPERBUS_open.
 * After HYPERBUS_setDeviceCfg the open polls the DLL_STAT_REG[MDLL_LOCK] bit
 * until it reads 1, breaking out with a timeout if the DLL never locks within
 * HYPERBUS_DEFAULT_REGISTER_READ_TIMEOUT_US. On real hardware the DLL locks, so
 * the wait loop and its timeout branch (lines 511-521 in hyperbus_v0.c) never
 * execute. This test points the peripheral sys base (ssBaseAddr) at a fake
 * SYSCFG register block whose RAM_STAT_REG reads 1 (so the earlier RAM-init
 * poll passes) but whose DLL_STAT_REG reads 0 (MDLL_LOCK = 0), so the DLL-lock
 * poll spins until it times out. It verifies HYPERBUS_open returns NULL, then
 * restores the original base. This covers the uncovered DLL-lock wait loop and
 * timeout at lines 511-521.
 */
static void TestHyperBus_MdllLockTimeout(void *args)
{
    HYPERBUS_Handle  handle;
    HYPERBUS_Attrs  *mutableAttrs;
    uint32_t         savedSsBase;

    /* Driver must be closed before this test */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    HYPERBUS_close(handle);

    mutableAttrs = (HYPERBUS_Attrs *)gHyperBusConfig[CONFIG_HYPERBUS0].attrs;
    savedSsBase  = mutableAttrs->ssBaseAddr;

    /* Fake SYSCFG block: INIT_DONE = 1 lets the RAM-init poll pass, while
     * MDLL_LOCK = 0 makes the DLL-lock poll spin until it times out. */
    gTestHyperbus_FakeSyscfg[0] = 0U;   /* REVISION_REG                */
    gTestHyperbus_FakeSyscfg[1] = 0U;   /* DLL_STAT_REG: MDLL_LOCK = 0 */
    gTestHyperbus_FakeSyscfg[2] = 1U;   /* RAM_STAT_REG: INIT_DONE = 1 */

    mutableAttrs->ssBaseAddr = (uint32_t)(uintptr_t)&gTestHyperbus_FakeSyscfg[0];

    handle = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    /* Restore the original sys base address */
    mutableAttrs->ssBaseAddr = savedSsBase;

    DebugP_log("[HYPERBUS] MdllLockTimeout: PASS\r\n");
}

/* Test case to verify the alternate input-clock branch of HYPERBUS_getInputClk
 * in hyperbus_soc.c. HYPERBUS_powerClockInit calls HYPERBUS_getInputClk during
 * HYPERBUS_open. When attrs->inputClkFreq equals 166666666 the function takes
 * the if branch (returns 333333333); for any other value it takes the else
 * branch and returns inputClkFreq * 2 (lines 64-67). The default configuration
 * uses 166666666, so the else branch is never reached in normal operation.
 * This test saves the original inputClkFreq, overrides it with a value that is
 * not 166666666 but doubles to ~333.33 MHz (so the X2 clock and hence the open
 * still succeed), opens the driver,opening the driver should fail that is why 
 * we are expecting a NULL. This covers the uncovered else branch at
 * lines 64-67 in hyperbus_soc.c.
 */
static void TestHyperBus_InputClkAlternate(void *args)
{
    HYPERBUS_Handle  handle;
    HYPERBUS_Attrs  *mutableAttrs;
    uint32_t         savedClkFreq;

    /* Driver must be closed before this test */
    handle = HYPERBUS_getHandle(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    HYPERBUS_close(handle);

    mutableAttrs = (HYPERBUS_Attrs *)gHyperBusConfig[CONFIG_HYPERBUS0].attrs;
    savedClkFreq = mutableAttrs->inputClkFreq;

    /* Force the else branch of HYPERBUS_getInputClk (retVal * 2) */
    mutableAttrs->inputClkFreq = TEST_HYPERBUS_ALT_INPUT_CLK_FREQ;

    handle = HYPERBUS_open(CONFIG_HYPERBUS0);
    TEST_ASSERT_NULL(handle);

    /* Restore the original input clock frequency before closing */
    mutableAttrs->inputClkFreq = savedClkFreq;
   

    DebugP_log("[HYPERBUS] InputClkAlternate: PASS\r\n");
}

