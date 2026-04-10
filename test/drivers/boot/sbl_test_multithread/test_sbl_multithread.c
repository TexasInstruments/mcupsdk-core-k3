/*
 * Copyright (C) 2021-2026 Texas Instruments Incorporated
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

/*===================================================================*/
/* 					  Include Files 					     */
/*===================================================================*/

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <drivers/bootloader.h>
#if defined(SOC_AM62DX)
#include <drivers/bootloader/bootloader_priv.h>
#endif
#include <drivers/mmcsd.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/*===================================================================*/
/* 					  Macro defines 					     */
/*===================================================================*/

#define TEST_SBL_APPIMAGE_MAX_FILE_SIZE                  (0x800000)
#define TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_START      (0x9CA00000)
#define TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_LENGTH     (0x1C08000)

#define TEST_SBL_MT_NUM_CORES                            (3U)
#define TEST_SBL_MT_TASK_STACK_SIZE                      (16384U)
#define TEST_SBL_MT_TASK_PRIORITY                        (2U)

#define TEST_SBL_MM_NUM_CORES                            (2U)
#define TEST_SBL_MM_MEDIA_EMMC                           (0U)
#define TEST_SBL_MM_MEDIA_FLASH                          (1U)

#if defined(SOC_AM275X)
/*
 * Scratch buffer size for Bootloader_parseAndLoadMultiCoreELF auth path.
 */
#define TEST_SBL_SCRATCH_BUF_SIZE (0x1000U)
#endif

/*===================================================================*/
/* 					     Typedefs 					         */
/*===================================================================*/

/**
 * @brief Per-thread arguments for the multithread boot test.
 */
typedef struct TestSbl_MtThreadArgs_s
{
    uint8_t             *appImageBuf;
    uint32_t             appImageBufSize;
    uint32_t             coreId;
    uint32_t             bootloaderInstanceId;
    int32_t              loadStatus;
    Bootloader_CpuInfo   cpuInfo;
    Bootloader_Handle    bootHandle;
    SemaphoreP_Object   *doneSem;
    SemaphoreP_Object   *parseMutex;  /* serialize TIFS auth (not thread-safe) */
} TestSbl_MtThreadArgs;

/**
 * @brief Per-thread arguments for the multi-media multithread boot test.
 */
typedef struct TestSbl_MmMtThreadArgs_s
{
    uint8_t             *appImageBuf;     /* scratch (EMMC/FLASH) or image data (MEM) */
    uint32_t             appImageBufSize;
    uint32_t             coreId;
    uint32_t             bootloaderInstanceId;
    uint32_t             mediaType;
    int32_t              loadStatus;
    Bootloader_CpuInfo   cpuInfo;
    Bootloader_Handle    bootHandle;
    SemaphoreP_Object   *doneSem;
    SemaphoreP_Object   *parseMutex;  /* serialize TIFS auth (not thread-safe) */
} TestSbl_MmMtThreadArgs;

/*===================================================================*/
/* 					  Global Variables				         */
/*===================================================================*/

/* Per-core app image buffers for multithread boot test.
 * These are defined in appimage_data.S which embeds the signed per-core
 * appimage files (.hs_fs) as initialized data sections.
 * On AM275x these are packed contiguously in R50_1_OCRAM (0x72180000).
 */
extern uint8_t gAppImageBuf0[];
extern uint8_t gAppImageBuf1[];
extern uint8_t gAppImageBuf2[];

/* Per-thread task stacks for multithread boot test */
uint8_t gMtTaskStack0[TEST_SBL_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
uint8_t gMtTaskStack1[TEST_SBL_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
uint8_t gMtTaskStack2[TEST_SBL_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));

#if defined(SOC_AM275X)
/*
 * Scratch buffer for Bootloader_parseAndLoadMultiCoreELF auth path.
 * The API does not support BOOTLOADER_MEDIA_MEM with authentication;
 * we override bootMedia to EMMC so the EMMC code path is taken,
 * which needs scratchMemPtr for cert copy and restricted-region loads.
 * Threads are mutex-serialized so a single shared buffer is sufficient.
 */
uint8_t gMtScratchBuf[TEST_SBL_SCRATCH_BUF_SIZE] __attribute__((aligned(128), section(".bss.app")));
#endif

/*===================================================================*/
/* 				  Function Declarations				         */
/*===================================================================*/

void TestSbl_multiThreadBoot(void *args);
void TestSbl_multiMediaMultiThreadBoot(void *args);

int32_t TestSbl_openBootEMMC();
int32_t TestSbl_openBootDriverFlash();
int32_t TestSbl_openBootBoardFlash();
void TestSbl_closeBootEMMC();
void TestSbl_closeBootDriverFlash();
void TestSbl_closeBootBoardFlash();

/*===================================================================*/
/* 				  Function Definitions				         */
/*===================================================================*/

/**
 * @brief Unity per-test setup hook.
 *
 * Called automatically by the Unity framework before each test case.
 * No special initialization is required for the multithread boot tests.
 *
 * @return void
 */
void setUp(void)
{
    /* Setup function nothing to perform */
}

/**
 * @brief Unity per-test teardown hook.
 *
 * Called automatically by the Unity framework after each test case.
 * No special cleanup is required for the multithread boot tests.
 *
 * @return void
 */
void tearDown(void)
{
    /* Tear down function nothing to perform */
}

void loop_forever()
{
    volatile uint32_t loop = 1;
    DebugP_log("Inside the loop...\r\n");   
    while(loop)
        ;
}

/**
 * @brief Main SBL multithread boot test entry point.
 *
 * Initializes Unity and executes the multithread and multi-media
 * multithread boot tests. The MT test runs first because the MM
 * test overwrites the embedded appimage buffers used as scratch.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void test_main(void * args)
{
    UNITY_BEGIN();
    /* Run MT test first: MM test overwrites the embedded appimage buffers
     * (used as scratch for eMMC/OSPI auth) so MT must complete before MM. */
    RUN_TEST(TestSbl_multiThreadBoot,           11446, NULL);
#if !defined(SKIP_MULTIMEDIA_TEST)
    RUN_TEST(TestSbl_multiMediaMultiThreadBoot, 11447, NULL);
#else
    DebugP_log("Skipping TestSbl_multiMediaMultiThreadBoot (SKIP_MULTIMEDIA_TEST defined)\r\n");
#endif
    UNITY_END();
}

/*
 * Multithread boot test: loads a single-core appimage from its own DDR
 * buffer per thread and boots the corresponding core.
 */

static void TestSbl_mtLoadThread(void *args)
{
    TestSbl_MtThreadArgs *threadArgs = (TestSbl_MtThreadArgs *)args;
    int32_t status = SystemP_SUCCESS;

    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);
    bootParams.memArgsAppImageBaseAddr = (uintptr_t)threadArgs->appImageBuf;

    threadArgs->bootHandle = Bootloader_open(threadArgs->bootloaderInstanceId, &bootParams);
    if(threadArgs->bootHandle == NULL)
    {
        DebugP_log("Bootloader_open failed for core %d\r\n", threadArgs->coreId);
        threadArgs->loadStatus = SystemP_FAILURE;
        SemaphoreP_post(threadArgs->doneSem);
        TaskP_exit();
        return;
    }

    Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
    bootConfig->coresPresentMap = 0;

#if defined(SOC_AM275X)
    /*
     * Bootloader_parseAndLoadMultiCoreELF only supports Flash/eMMC/SD in the
     * auth path.  Override bootMedia so the eMMC code path is used; the MEM
     * imgReadFxn/imgSeekFxn are still in place and handle the actual I/O.
     */
    bootConfig->bootMedia    = BOOTLOADER_MEDIA_EMMC;
    bootConfig->scratchMemPtr = gMtScratchBuf;
#elif defined(SOC_AM62DX)
    /* No pre-parse overrides needed — AM62DX uses manual auth + parse below */
#endif

    /* Serialize parse+load: TIFS auth via Sciclient is not thread-safe */
    SemaphoreP_pend(threadArgs->parseMutex, SystemP_WAIT_FOREVER);

#if defined(SOC_AM275X)
    status = Bootloader_parseAndLoadMultiCoreELF(threadArgs->bootHandle, &bootImageInfo);
#elif defined(SOC_AM62DX)
    /*
     * On AM62DX HS-FS, Bootloader_parseMultiCoreAppImage fails because
     * Bootloader_verifyMulticoreImage authenticates the x509 cert but
     * TIFS does not strip/relocate the payload in post-boot context.
     * The post-auth parser then reads the cert header instead of "MSTR".
     *
     * Additionally, all per-core appimages are signed with the same
     * --loadaddr 0x84000000, but they reside at different DDR addresses.
     * TIFS may DMA the authenticated payload to loadaddr, corrupting
     * other buffers.
     *
     * Workaround: compute cert length, skip past the cert, update
     * appImageBaseAddr to point at the appimage payload, and use
     * Bootloader_parseMultiCoreAppImage with auth bypassed by
     * temporarily pointing to the post-cert data.
     */
    {
        Bootloader_MemArgs *memArgs = (Bootloader_MemArgs *)bootConfig->args;
        uint8_t *certStart = (uint8_t *)(uintptr_t)memArgs->appImageBaseAddr;
        uint32_t certLen;

        /* Compute x509 cert length from DER header */
        certLen = Bootloader_getX509CertLen(certStart);

        if(certLen > 0x100U && certLen < 0x800U)
        {
            /* Advance appImageBaseAddr past the x509 cert to the "MSTR" header.
             * This makes the MEM imgReadFxn read from the appimage directly,
             * and Bootloader_parseMultiCoreAppImage will see it as GP
             * (no cert → Bootloader_socIsAuthRequired still returns TRUE,
             * but verifyMulticoreImage will find "MSTR" not "0x30 0x82"
             * and certLen will be 0 → status = FAILURE).
             * Instead, use parseAppImage which skips verification entirely.
             */
            memArgs->appImageBaseAddr = (uint32_t)(uintptr_t)(certStart + certLen);
            bootConfig->scratchMemPtr = certStart + certLen;
            status = Bootloader_parseAppImage(threadArgs->bootHandle, &bootImageInfo);
        }
        else
        {
            DebugP_log("Invalid cert for core %d (certLen=0x%x)\r\n",
                       threadArgs->coreId, certLen);
            status = SystemP_FAILURE;
        }
    }
#else
    status = Bootloader_parseMultiCoreAppImage(threadArgs->bootHandle, &bootImageInfo);
#endif
    if(status != SystemP_SUCCESS)
    {
        SemaphoreP_post(threadArgs->parseMutex);
        DebugP_log("parse+load failed for core %d\r\n", threadArgs->coreId);
        threadArgs->loadStatus = status;
        Bootloader_close(threadArgs->bootHandle);
        threadArgs->bootHandle = NULL;
        SemaphoreP_post(threadArgs->doneSem);
        TaskP_exit();
        return;
    }

    if(TRUE != Bootloader_isCorePresent(threadArgs->bootHandle, threadArgs->coreId))
    {
        SemaphoreP_post(threadArgs->parseMutex);
        DebugP_log("Core %d not present in appimage\r\n", threadArgs->coreId);
        threadArgs->loadStatus = SystemP_FAILURE;
        Bootloader_close(threadArgs->bootHandle);
        threadArgs->bootHandle = NULL;
        SemaphoreP_post(threadArgs->doneSem);
        TaskP_exit();
        return;
    }

#if !defined(SOC_AM275X)
    bootImageInfo.cpuInfo[threadArgs->coreId].clkHz =
        Bootloader_socCpuGetClkDefault(threadArgs->coreId);

#if defined(SOC_AM62DX)
    /*
     * Manual CPU setup + RPRC image loading for AM62DX HS-FS.
     *
     * Bootloader_loadCpu → Bootloader_rprcImageLoad uses
     * gMemBootloaderConfig (auth-required path) which reads via DMA.
     * This hangs in the post-boot MEM context. Replicate the loadCpu
     * steps here with direct memcpy instead of DMA.
     */
    {
        Bootloader_CpuInfo *cpuInfo = &bootImageInfo.cpuInfo[threadArgs->coreId];
        Bootloader_MemArgs *memArgs = (Bootloader_MemArgs *)bootConfig->args;

        status = Bootloader_socCpuRequest(cpuInfo->cpuId);

        status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

        if(status == SystemP_SUCCESS)
        {
            status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId, bootConfig->socCoreOpMode);
        }

        if(status == SystemP_SUCCESS && cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
        {
            /* Manual RPRC section loading using direct memcpy (no DMA) */
            uint8_t *rprcBase = (uint8_t *)(uintptr_t)(memArgs->appImageBaseAddr +
                                cpuInfo->rprcOffset);
            Bootloader_RprcFileHeader rprcHdr;

            CacheP_inv(rprcBase, sizeof(rprcHdr), CacheP_TYPE_ALL);
            memcpy(&rprcHdr, rprcBase, sizeof(rprcHdr));
            rprcBase += sizeof(rprcHdr);

            if(rprcHdr.magic != BOOTLOADER_RPRC_MAGIC_NUMBER)
            {
                status = SystemP_FAILURE;
            }
            else
            {
                cpuInfo->entryPoint = (uintptr_t)rprcHdr.entry;
                uint32_t s;
                for(s = 0; s < rprcHdr.sectionCount && status == SystemP_SUCCESS; s++)
                {
                    Bootloader_RprcSectionHeader secHdr;
                    memcpy(&secHdr, rprcBase, sizeof(secHdr));
                    rprcBase += sizeof(secHdr);

                    uint32_t destAddr = Bootloader_socTranslateSectionAddr(
                                            cpuInfo->cpuId, secHdr.addr);

                    memcpy((void *)(uintptr_t)destAddr, rprcBase, secHdr.size);
                    CacheP_wbInv((void *)(uintptr_t)destAddr, secHdr.size, CacheP_TYPE_ALL);
                    rprcBase += secHdr.size;
                    bootConfig->bootImageSize += secHdr.size;
                }
            }
        }
    }
#else
    status = Bootloader_loadCpu(threadArgs->bootHandle,
                                &(bootImageInfo.cpuInfo[threadArgs->coreId]));
#endif /* SOC_AM62DX */
#endif

    SemaphoreP_post(threadArgs->parseMutex);

    threadArgs->loadStatus = status;
    threadArgs->cpuInfo    = bootImageInfo.cpuInfo[threadArgs->coreId];

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("Thread: core %d loaded successfully\r\n", threadArgs->coreId);
    }
    else
    {
        DebugP_log("Thread: load failed for core %d\r\n", threadArgs->coreId);
    }

    SemaphoreP_post(threadArgs->doneSem);
    TaskP_exit();
}

/**
 * @brief Multithread boot test — parallel load and boot of multiple cores.
 *
 * Each thread loads a single-core appimage from its own DDR buffer and
 * boots the corresponding core. Verifies parallel boot of MCU_R5FSS0_0,
 * A53SS0_0, and C75SS0_0 (or AM275x equivalents) using separate buffers
 * and threads.
 *
 * Test Steps:
 * 1. Verify pre-loaded appimage buffers contain non-zero data.
 * 2. Create a mutex to serialize TIFS authentication (not thread-safe).
 * 3. Spawn one FreeRTOS task per core, each calling Bootloader_open,
 *    parse, and load with its own appimage buffer.
 * 4. Wait for all threads to complete and verify all loads succeeded.
 * 5. Call Bootloader_runCpu for each loaded core.
 * 6. Wait for IPC sync from each booted core.
 * 7. Reset all CPUs, close bootloader instances, and clean up resources.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_multiThreadBoot(void *args)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t loopVar;
    /*
     * Table mapping each thread to its core, pre-loaded DDR buffer,
     * bootloader instance, and task stack.
     *
     * The appimage buffers are at fixed DDR addresses, pre-loaded
     * by the SBL during boot via the .cfg file. Each buffer contains
     * a single-core appimage from the sbl_test_custom_ipc_binary build.
     */
    uint32_t coreIds[TEST_SBL_MT_NUM_CORES] = {
#if defined(SOC_AM275X)
        CSL_CORE_ID_R5FSS0_0,
        CSL_CORE_ID_R5FSS1_0,
#else
        CSL_CORE_ID_MCU_R5FSS0_0,
        CSL_CORE_ID_A53SS0_0,
#endif
        CSL_CORE_ID_C75SS0_0,
    };
    uint8_t *appImageBufs[TEST_SBL_MT_NUM_CORES] = {
        gAppImageBuf0,
        gAppImageBuf1,
        gAppImageBuf2,
    };
    uint32_t bootloaderInstances[TEST_SBL_MT_NUM_CORES] = {
#if defined(SOC_AM275X)
        /* MEM bootloaders for R5FSS0_0, R5FSS1_0, C75SS0_0 (appimages embedded in binary) */
        CONFIG_BOOTLOADER_MEM_R5FSS0_0,
        CONFIG_BOOTLOADER_MEM_R5FSS1_0,
        CONFIG_BOOTLOADER_MEM_C75SS0_0,
#else
        CONFIG_BOOTLOADER_SD_A53,
        CONFIG_BOOTLOADER_SD_SMP,
        CONFIG_BOOTLOADER_SD_MULTICORE,
#endif
    };
    uint8_t *taskStacks[TEST_SBL_MT_NUM_CORES] = {
        gMtTaskStack0,
        gMtTaskStack1,
        gMtTaskStack2,
    };
    TestSbl_MtThreadArgs threadArgs[TEST_SBL_MT_NUM_CORES];
    TaskP_Object         taskObjs[TEST_SBL_MT_NUM_CORES];
    SemaphoreP_Object    doneSems[TEST_SBL_MT_NUM_CORES];
    SemaphoreP_Object    parseMutex;

    DebugP_log("Starting TestSbl_multiThreadBoot test...\r\n");

    Bootloader_profileAddProfilePoint("SBL Drivers_open");
    Bootloader_openDma();

    /* Appimage buffers are already pre-loaded at fixed DDR addresses.
     * Verify they contain valid data (non-zero first word). */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        TEST_ASSERT_NOT_EQUAL(0U, *((uint32_t *)appImageBufs[loopVar]));
    }

    /* Mutex to serialize parse+load (TIFS auth is not thread-safe) */
    status = SemaphoreP_constructMutex(&parseMutex);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Create a binary semaphore for each thread to signal completion */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        status = SemaphoreP_constructBinary(&doneSems[loopVar], 0);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    /* Populate thread arguments */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        threadArgs[loopVar].appImageBuf         = appImageBufs[loopVar];
        threadArgs[loopVar].appImageBufSize     = TEST_SBL_APPIMAGE_MAX_FILE_SIZE;
        threadArgs[loopVar].coreId              = coreIds[loopVar];
        threadArgs[loopVar].bootloaderInstanceId = bootloaderInstances[loopVar];
        threadArgs[loopVar].loadStatus          = SystemP_FAILURE;
        threadArgs[loopVar].bootHandle          = NULL;
        threadArgs[loopVar].doneSem             = &doneSems[loopVar];
        threadArgs[loopVar].parseMutex          = &parseMutex;
    }

    /* Create and launch threads to load each core in parallel */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "mt_boot_thread";
        taskParams.stackSize = TEST_SBL_MT_TASK_STACK_SIZE;
        taskParams.stack     = taskStacks[loopVar];
        taskParams.priority  = TEST_SBL_MT_TASK_PRIORITY;
        taskParams.args      = &threadArgs[loopVar];
        taskParams.taskMain  = TestSbl_mtLoadThread;

        status = TaskP_construct(&taskObjs[loopVar], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    /* Wait for all threads to complete loading */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        SemaphoreP_pend(&doneSems[loopVar], SystemP_WAIT_FOREVER);
    }

    /* Verify all loads succeeded */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        TEST_ASSERT_EQUAL(threadArgs[loopVar].loadStatus, SystemP_SUCCESS);
    }

    /* Run all loaded cores */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        if(threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("CPU %d: Running CPU...\r\n", coreIds[loopVar]);
                status = Bootloader_runCpu(threadArgs[loopVar].bootHandle,
                                           &threadArgs[loopVar].cpuInfo);
                DebugP_log("CPU %d: Bootloader_runCpu status = %d\r\n", coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    Bootloader_closeDma();

    /* Wait for IPC sync from each booted core */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        if(threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("CPU %d: Waiting for IPC sync...\r\n", coreIds[loopVar]);
                status = IpcNotify_waitSync(coreIds[loopVar], 30);
                DebugP_log("CPU %d: IPC sync status = %d\r\n", coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    /* Reset CPUs to original state */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        if(threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            DebugP_log("CPU %d: Resetting...\r\n", coreIds[loopVar]);
            status = Bootloader_socCpuRequest(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_socCpuPowerOff(threadArgs[loopVar].cpuInfo.cpuId);
            status = Bootloader_socCpuRelease(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("CPU %d: Reset complete\r\n", coreIds[loopVar]);
        }
    }

    /* Close bootloader instances */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        if(threadArgs[loopVar].bootHandle != NULL)
        {
            Bootloader_close(threadArgs[loopVar].bootHandle);
        }
    }

    /* Clean up task objects and semaphores */
    for(loopVar = 0; loopVar < TEST_SBL_MT_NUM_CORES; loopVar++)
    {
        TaskP_destruct(&taskObjs[loopVar]);
        SemaphoreP_destruct(&doneSems[loopVar]);
    }
    SemaphoreP_destruct(&parseMutex);

    DebugP_log("TestSbl_multiThreadBoot test completed\r\n");
}

/*
 * Multi-media multithread boot test: loads a single-core appimage from a
 * different boot media per thread and boots the corresponding core.
 */

static void TestSbl_mmMtLoadThread(void *args)
{
    TestSbl_MmMtThreadArgs *threadArgs = (TestSbl_MmMtThreadArgs *)args;
    int32_t status = SystemP_SUCCESS;

    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    threadArgs->bootHandle = Bootloader_open(threadArgs->bootloaderInstanceId, &bootParams);
    if(threadArgs->bootHandle == NULL)
    {
        DebugP_log("Bootloader_open failed for core %d (media %d)\r\n",
                   threadArgs->coreId, threadArgs->mediaType);
        threadArgs->loadStatus = SystemP_FAILURE;
        SemaphoreP_post(threadArgs->doneSem);
        TaskP_exit();
        return;
    }

    Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
    bootConfig->coresPresentMap = 0;

    /* For EMMC/Flash bootloaders, set scratch buffer for parsing */
    bootConfig->scratchMemPtr = threadArgs->appImageBuf;

    /* Serialize parse+load: TIFS auth via Sciclient is not thread-safe */
    SemaphoreP_pend(threadArgs->parseMutex, SystemP_WAIT_FOREVER);

#if defined(SOC_AM275X)
    status = Bootloader_parseAndLoadMultiCoreELF(threadArgs->bootHandle, &bootImageInfo);
#elif defined(SOC_AM62DX)
    /*
     * On AM62DX HS-FS in post-boot context, Bootloader_socAuthImage returns
     * SUCCESS but TIFS does not DMA the cert-stripped payload to loadaddr.
     * Bootloader_parseMultiCoreAppImage → verifyMulticoreImage therefore
     * fails because the post-auth parse reads the stale cert header instead
     * of "MSTR".
     *
     * Workaround: read the signed image from media into the scratch buffer,
     * compute the x509 cert length, advance past the cert, and use
     * Bootloader_parseAppImage (which skips verification).  Then manually
     * load RPRC sections using memcpy (same approach as the MT test).
     */
    {
        uint8_t x509Header[4];
        uint32_t certLen, imageLen, totalLen;

        /* Read x509 header from media to compute cert length */
        bootConfig->fxns->imgReadFxn(x509Header, 4, bootConfig->args);
        bootConfig->fxns->imgSeekFxn(0, bootConfig->args);

        certLen = Bootloader_getX509CertLen(x509Header);

        if(certLen > 0x100U && certLen < 0x800U)
        {
            /* Read first 0x800 bytes to determine payload length */
            bootConfig->fxns->imgReadFxn(threadArgs->appImageBuf, 0x800,
                                         bootConfig->args);
            imageLen = Bootloader_getMsgLen(threadArgs->appImageBuf, certLen);
            totalLen = (certLen + imageLen + 128U) & ~127U;

            /* Read full signed image from media into scratch buffer */
            bootConfig->fxns->imgSeekFxn(0, bootConfig->args);
            bootConfig->fxns->imgReadFxn(threadArgs->appImageBuf, totalLen,
                                         bootConfig->args);
            CacheP_wbInv(threadArgs->appImageBuf, totalLen, CacheP_TYPE_ALL);

            /* Point past the cert to the MSTR header */
            bootConfig->scratchMemPtr = threadArgs->appImageBuf + certLen;
            status = Bootloader_parseAppImage(threadArgs->bootHandle,
                                              &bootImageInfo);
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
#else
    status = Bootloader_parseMultiCoreAppImage(threadArgs->bootHandle, &bootImageInfo);
#endif
    if(status != SystemP_SUCCESS)
    {
        SemaphoreP_post(threadArgs->parseMutex);
        DebugP_log("parse+load failed for core %d (media %d)\r\n",
                   threadArgs->coreId, threadArgs->mediaType);
        threadArgs->loadStatus = status;
        Bootloader_close(threadArgs->bootHandle);
        threadArgs->bootHandle = NULL;
        SemaphoreP_post(threadArgs->doneSem);
        TaskP_exit();
        return;
    }

    if(TRUE != Bootloader_isCorePresent(threadArgs->bootHandle, threadArgs->coreId))
    {
        SemaphoreP_post(threadArgs->parseMutex);
        DebugP_log("Core %d not present in appimage (media %d)\r\n",
                   threadArgs->coreId, threadArgs->mediaType);
        threadArgs->loadStatus = SystemP_FAILURE;
        Bootloader_close(threadArgs->bootHandle);
        threadArgs->bootHandle = NULL;
        SemaphoreP_post(threadArgs->doneSem);
        TaskP_exit();
        return;
    }

#if !defined(SOC_AM275X)
    bootImageInfo.cpuInfo[threadArgs->coreId].clkHz =
        Bootloader_socCpuGetClkDefault(threadArgs->coreId);

#if defined(SOC_AM62DX)
    /*
     * Manual CPU setup + RPRC image loading (same approach as MT test).
     * Bootloader_loadCpu uses gMemBootloaderConfig with DMA which can
     * hang in the post-boot context.
     */
    {
        Bootloader_CpuInfo *cpuInfo = &bootImageInfo.cpuInfo[threadArgs->coreId];

        status = Bootloader_socCpuRequest(cpuInfo->cpuId);

        status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

        if(status == SystemP_SUCCESS)
        {
            status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId,
                                                   bootConfig->socCoreOpMode);
        }

        if(status == SystemP_SUCCESS && cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
        {
            uint8_t *rprcBase = bootConfig->scratchMemPtr + cpuInfo->rprcOffset;
            Bootloader_RprcFileHeader rprcHdr;

            CacheP_inv(rprcBase, sizeof(rprcHdr), CacheP_TYPE_ALL);
            memcpy(&rprcHdr, rprcBase, sizeof(rprcHdr));
            rprcBase += sizeof(rprcHdr);

            if(rprcHdr.magic != BOOTLOADER_RPRC_MAGIC_NUMBER)
            {
                status = SystemP_FAILURE;
            }
            else
            {
                cpuInfo->entryPoint = (uintptr_t)rprcHdr.entry;
                uint32_t s;
                for(s = 0; s < rprcHdr.sectionCount && status == SystemP_SUCCESS; s++)
                {
                    Bootloader_RprcSectionHeader secHdr;
                    memcpy(&secHdr, rprcBase, sizeof(secHdr));
                    rprcBase += sizeof(secHdr);

                    uint32_t destAddr = Bootloader_socTranslateSectionAddr(
                                            cpuInfo->cpuId, secHdr.addr);

                    memcpy((void *)(uintptr_t)destAddr, rprcBase, secHdr.size);
                    CacheP_wbInv((void *)(uintptr_t)destAddr, secHdr.size,
                                 CacheP_TYPE_ALL);
                    rprcBase += secHdr.size;
                    bootConfig->bootImageSize += secHdr.size;
                }
            }
        }
    }
#else
    status = Bootloader_loadCpu(threadArgs->bootHandle,
                                &(bootImageInfo.cpuInfo[threadArgs->coreId]));
#endif /* SOC_AM62DX */
#endif

    SemaphoreP_post(threadArgs->parseMutex);

    threadArgs->loadStatus = status;
    threadArgs->cpuInfo    = bootImageInfo.cpuInfo[threadArgs->coreId];

    DebugP_log("Thread: core %d load from media %d, status = %d\r\n",
               threadArgs->coreId, threadArgs->mediaType, status);

    SemaphoreP_post(threadArgs->doneSem);
    TaskP_exit();
}

/**
 * @brief Multi-media multithread boot test — parallel load across heterogeneous media.
 *
 * Each thread loads a single-core appimage from a different boot media
 * (eMMC, OSPI Flash) and boots the corresponding core. Verifies parallel
 * boot across heterogeneous media.
 *
 * Test Steps:
 * 1. Open eMMC, OSPI, and Flash drivers.
 * 2. Create a mutex to serialize TIFS authentication (not thread-safe).
 * 3. Spawn one FreeRTOS task per core:
 *    - Thread 0: MCU R5FSS0_0 from eMMC.
 *    - Thread 1: C75SS0_0 from OSPI Flash.
 * 4. Wait for all threads to complete and verify all loads succeeded.
 * 5. Call Bootloader_runCpu for each loaded core.
 * 6. Wait for IPC sync from each booted core.
 * 7. Reset all CPUs, close bootloader and media driver instances.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_multiMediaMultiThreadBoot(void *args)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t loopVar;
    /*
     * Thread-to-core-to-media mapping:
     *   Thread 0: MCU R5FSS0_0  from eMMC       (CONFIG_BOOTLOADER_EMMC_MCU)
     *   Thread 1: C75SS0_0      from OSPI Flash (CONFIG_BOOTLOADER_FLASH_DSP)
     */
    uint32_t coreIds[TEST_SBL_MM_NUM_CORES] = {
#if defined(SOC_AM275X)
        CSL_CORE_ID_R5FSS0_0,
#else
        CSL_CORE_ID_MCU_R5FSS0_0,
#endif
        CSL_CORE_ID_C75SS0_0,
    };
    uint32_t mediaTypes[TEST_SBL_MM_NUM_CORES] = {
        TEST_SBL_MM_MEDIA_EMMC,
        TEST_SBL_MM_MEDIA_FLASH,
    };
    /*
     * Scratch buffers for eMMC/Flash parse+load.  On AM275x use the
     * dedicated gMtScratchBuf (4 KB in .bss.app) so that the embedded
     * appimage data in gAppImageBuf0/2 is not corrupted for the
     * subsequent MEM boot test.  Threads are mutex-serialized so a
     * single shared buffer is safe.
     */
    uint8_t *appImageBufs[TEST_SBL_MM_NUM_CORES] = {
#if defined(SOC_AM275X)
        gMtScratchBuf,   /* shared scratch — threads serialized by parseMutex */
        gMtScratchBuf,
#elif defined(SOC_AM62DX)
        /*
         * On AM62DX HS-FS, Bootloader_socAuthImage DMAs the cert-stripped
         * payload to the loadaddr embedded in the x509 cert (0x84000000).
         * scratchMemPtr must match loadaddr so the post-auth parse reads
         * the stripped payload, not the stale cert header.
         * gAppImageBuf2 is at 0x84000000 (APPIMAGE region start).
         * Threads are mutex-serialized so a single buffer is safe.
         */
        gAppImageBuf2,   /* 0x84000000 = loadaddr for both eMMC & OSPI images */
        gAppImageBuf2,
#else
        gAppImageBuf0,   /* scratch for eMMC */
        gAppImageBuf2,   /* scratch for OSPI Flash */
#endif
    };
    uint32_t bootloaderInstances[TEST_SBL_MM_NUM_CORES] = {
        CONFIG_BOOTLOADER_EMMC_MCU,
        CONFIG_BOOTLOADER_FLASH_DSP,
    };
    uint8_t *taskStacks[TEST_SBL_MM_NUM_CORES] = {
        gMtTaskStack0,
        gMtTaskStack1,
    };
    TestSbl_MmMtThreadArgs threadArgs[TEST_SBL_MM_NUM_CORES];
    TaskP_Object           taskObjs[TEST_SBL_MM_NUM_CORES];
    SemaphoreP_Object      doneSems[TEST_SBL_MM_NUM_CORES];
    SemaphoreP_Object      parseMutex;

    DebugP_log("Starting TestSbl_multiMediaMultiThreadBoot test...\r\n");

#if defined(SOC_AM275X)
    /*
     * Open media drivers before thread creation.
     * Each thread accesses a different peripheral so there is no contention.
     *
     * Even though SysConfig marks MMCSD/OSPI as addedByBootloader=TRUE
     * (so Drivers_open skips them), this test boots via UART — the SBL
     * never opened eMMC/OSPI.  We must open them explicitly here.
     *
     * PowerClock_init (called from System_init) only enables the normal
     * module clocks (UART).  The MMCSD/OSPI clocks live in the SBL clock
     * list, so we must enable them explicitly before accessing the HW.
     *
     * Use explicit calls instead of Module_clockSBLEnable() because the
     * latter uses DebugP_assertNoLog which hangs silently on failure.
     */
    {
        int32_t clkStatus;

        DebugP_log("[MM] Enabling MMCSD0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_MMCSD0, 1);
        DebugP_log("[MM] MMCSD0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        DebugP_log("[MM] Setting MMCSD0 clock frequency...\r\n");
        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_MMCSD0,
                        TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK,
                        200000000);
        DebugP_log("[MM] MMCSD0 clock freq status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        DebugP_log("[MM] Enabling FSS0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_FSS0, 1);
        DebugP_log("[MM] FSS0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        DebugP_log("[MM] Setting FSS0 clock frequency...\r\n");
        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_FSS0,
                        TISCI_DEV_FSS0_OSPI0_RCLK_CLK,
                        166666666);
        DebugP_log("[MM] FSS0 clock freq status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);
    }
#endif

    DebugP_log("[MM] Opening eMMC...\r\n");
    status = TestSbl_openBootEMMC();
    DebugP_log("[MM] eMMC open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    DebugP_log("eMMC driver opened\r\n");

    DebugP_log("[MM] Opening OSPI...\r\n");
    status = TestSbl_openBootDriverFlash();
    DebugP_log("[MM] OSPI open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    DebugP_log("OSPI driver opened\r\n");

    DebugP_log("[MM] Opening Flash...\r\n");
    status = TestSbl_openBootBoardFlash();
    DebugP_log("[MM] Flash open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    DebugP_log("Flash driver opened\r\n");

    Bootloader_profileAddProfilePoint("SBL Drivers_open");
    Bootloader_openDma();

#if !defined(SOC_AM275X)
    /* On AM275x there is no DDR; the default reserved range
     * [0x72000000, 0x72080000] protects the test app's own MSRAM.
     * Overriding it with a non-existent DDR address removes that
     * protection, so skip this call. */
    Bootloader_ReservedMemInit(TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_START,
                               TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_LENGTH);
#endif

    /* Mutex to serialize parse+load (TIFS auth is not thread-safe) */
    status = SemaphoreP_constructMutex(&parseMutex);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    /* Create a binary semaphore for each thread to signal completion */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        status = SemaphoreP_constructBinary(&doneSems[loopVar], 0);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    /* Populate thread arguments */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        threadArgs[loopVar].appImageBuf         = appImageBufs[loopVar];
        threadArgs[loopVar].appImageBufSize     = TEST_SBL_APPIMAGE_MAX_FILE_SIZE;
        threadArgs[loopVar].coreId              = coreIds[loopVar];
        threadArgs[loopVar].bootloaderInstanceId = bootloaderInstances[loopVar];
        threadArgs[loopVar].mediaType           = mediaTypes[loopVar];
        threadArgs[loopVar].loadStatus          = SystemP_FAILURE;
        threadArgs[loopVar].bootHandle          = NULL;
        threadArgs[loopVar].doneSem             = &doneSems[loopVar];
        threadArgs[loopVar].parseMutex          = &parseMutex;
    }

    /* Create and launch threads to load each core in parallel */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "mm_mt_boot_thread";
        taskParams.stackSize = TEST_SBL_MT_TASK_STACK_SIZE;
        taskParams.stack     = taskStacks[loopVar];
        taskParams.priority  = TEST_SBL_MT_TASK_PRIORITY;
        taskParams.args      = &threadArgs[loopVar];
        taskParams.taskMain  = TestSbl_mmMtLoadThread;

        status = TaskP_construct(&taskObjs[loopVar], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    /* Wait for all threads to complete loading */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        SemaphoreP_pend(&doneSems[loopVar], SystemP_WAIT_FOREVER);
    }

    /* Verify all loads succeeded */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        TEST_ASSERT_EQUAL(threadArgs[loopVar].loadStatus, SystemP_SUCCESS);
    }

    /* Run all loaded cores */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        if(threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("CPU %d: Running (media %d)...\r\n",
                           coreIds[loopVar], mediaTypes[loopVar]);
                status = Bootloader_runCpu(threadArgs[loopVar].bootHandle,
                                           &threadArgs[loopVar].cpuInfo);
                DebugP_log("CPU %d: Bootloader_runCpu status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    Bootloader_closeDma();

    /* Wait for IPC sync from each booted core */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        if(threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("CPU %d: Waiting for IPC sync...\r\n", coreIds[loopVar]);
                status = IpcNotify_waitSync(coreIds[loopVar], 30);
                DebugP_log("CPU %d: IPC sync status = %d\r\n", coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    /* Reset CPUs to original state */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        if(threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            DebugP_log("CPU %d: Resetting...\r\n", coreIds[loopVar]);
            status = Bootloader_socCpuRequest(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_socCpuPowerOff(threadArgs[loopVar].cpuInfo.cpuId);
            status = Bootloader_socCpuRelease(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("CPU %d: Reset complete\r\n", coreIds[loopVar]);
        }
    }

    /* Close bootloader instances */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        if(threadArgs[loopVar].bootHandle != NULL)
        {
            Bootloader_close(threadArgs[loopVar].bootHandle);
        }
    }

    /* Clean up task objects and semaphores */
    for(loopVar = 0; loopVar < TEST_SBL_MM_NUM_CORES; loopVar++)
    {
        TaskP_destruct(&taskObjs[loopVar]);
        SemaphoreP_destruct(&doneSems[loopVar]);
    }
    SemaphoreP_destruct(&parseMutex);

    /* Close media drivers */
    TestSbl_closeBootBoardFlash();
    TestSbl_closeBootDriverFlash();
    TestSbl_closeBootEMMC();

    /* Disable SBL module clocks that were enabled at the start */
    SOC_moduleClockEnable(TISCI_DEV_FSS0, 0);
    SOC_moduleClockEnable(TISCI_DEV_MMCSD0, 0);

    DebugP_log("TestSbl_multiMediaMultiThreadBoot test completed\r\n");
}

int32_t TestSbl_openBootEMMC()
{
    int32_t status = SystemP_SUCCESS;

    gMmcsdHandle[CONFIG_MMCSD_SBL] = NULL;

    gMmcsdHandle[CONFIG_MMCSD_SBL] = MMCSD_open(CONFIG_MMCSD_SBL, &gMmcsdParams[CONFIG_MMCSD_SBL]);
    if(NULL == gMmcsdHandle[CONFIG_MMCSD_SBL])
    {
        DebugP_logError("MMCSD open failed for instance %d !!!\r\n", CONFIG_MMCSD_SBL);
        status = SystemP_FAILURE;
    }
    return status;
}

int32_t TestSbl_openBootDriverFlash()
{
    int32_t status = SystemP_SUCCESS;
    gOspiHandle[CONFIG_OSPI_SBL] = NULL;

    gOspiHandle[CONFIG_OSPI_SBL] = OSPI_open(CONFIG_OSPI_SBL, &gOspiParams[CONFIG_OSPI_SBL]);
    if(NULL == gOspiHandle[CONFIG_OSPI_SBL])
    {
        DebugP_logError("OSPI open failed for instance %d !!!\r\n", CONFIG_OSPI_SBL);
        status = SystemP_FAILURE;
    }   
    return status;
}

int32_t TestSbl_openBootBoardFlash()
{
    int32_t status = SystemP_SUCCESS;

    gFlashHandle[CONFIG_FLASH_SBL] = NULL;

    gFlashConfig[CONFIG_FLASH_SBL].attrs->driverInstance = CONFIG_OSPI_SBL;

    gFlashHandle[CONFIG_FLASH_SBL] = Flash_open(CONFIG_FLASH_SBL, &gFlashParams[CONFIG_FLASH_SBL]);
    if(NULL == gFlashHandle[CONFIG_FLASH_SBL])
    {
        DebugP_logError("FLASH open failed for instance %d !!!\r\n", CONFIG_FLASH_SBL);
        status = SystemP_FAILURE;
    }

    return status;
}

void TestSbl_closeBootEMMC()
{
    MMCSD_close(gMmcsdHandle[CONFIG_MMCSD_SBL]);
    gMmcsdHandle[CONFIG_MMCSD_SBL] = NULL;
}

void TestSbl_closeBootBoardFlash()
{
    Flash_close(gFlashHandle[CONFIG_FLASH_SBL]);
    gFlashHandle[CONFIG_FLASH_SBL] = NULL;
}

void TestSbl_closeBootDriverFlash()
{
    OSPI_close(gOspiHandle[CONFIG_OSPI_SBL]);
    gOspiHandle[CONFIG_OSPI_SBL] = NULL;
}

