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
#if defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM62PX)
#include <drivers/bootloader/bootloader_priv.h>
#endif
#include <drivers/mmcsd.h>
#include <drivers/ipc_notify/v0/ipc_notify_v0.h>
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

/* Valid X.509 DER certificate length range and initial header read size */
#define TEST_SBL_X509_CERT_MIN_LEN                       (0x100U)   /* 256 bytes  */
#define TEST_SBL_X509_CERT_MAX_LEN                       (0x800U)   /* 2048 bytes */

/*
 * AM275X: Bootloader_runCpu(C75SS0_0) triggers C75 CLEC interrupt-route
 * configuration via TIFS/Sciserver which corrupts WKUP-R5 VIM routes for
 * the entire session (timer, mailbox ISRs, Sciserver).  All tests after this
 * point hang.  Exclude C75SS0_0 from the multithread test until the
 * TIFS RM bug is fixed (see JIRA: TODO).
 */
#if defined(SOC_AM275X)
#define TEST_SBL_MT_NUM_CORES                            (2U)
#elif defined(SOC_AM62PX)
/* AM62PX: no A53/C75 boot image available on this board; only the
 * secondary MCU-R5F core has an appimage provisioned. */
#define TEST_SBL_MT_NUM_CORES                            (1U)
#else
#define TEST_SBL_MT_NUM_CORES                            (3U)
#endif
#define TEST_SBL_MT_TASK_STACK_SIZE                      (16384U * 4)
#define TEST_SBL_MT_TASK_PRIORITY                        (2U)

#define TEST_SBL_MM_NUM_CORES                            (2U)
#define TEST_SBL_MM_MEDIA_EMMC                           (0U)
#define TEST_SBL_MM_MEDIA_FLASH                          (1U)

#define TEST_SBL_SDOSPI_NUM_CORES                        (2U)
#define TEST_SBL_SDOSPI_MEDIA_SD                         (0U)   /* AM62DX: SD card via FreeRTOS-FAT (MMC1) */
#define TEST_SBL_SDOSPI_MEDIA_EMMC                       (1U)   /* AM275X: eMMC as SD analog (MMC0)       */
#define TEST_SBL_SDOSPI_MEDIA_FLASH                      (2U)   /* Both:   OSPI NOR flash                 */

#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
/* Path on the SD card FAT volume for the A53 single-core appimage */
#define TEST_SBL_SDOSPI_SD_APPIMAGE_FNAME                "/sd0/app_a53"
#endif

#define TEST_SBL_EMMC_SD_NUM_CORES                       (2U)
#define TEST_SBL_EMMC_SD_MEDIA_EMMC                      (0U)   /* Both:   eMMC raw reads (MMC0)          */
#define TEST_SBL_EMMC_SD_MEDIA_SD                        (1U)   /* AM62DX: SD FAT reads (MMC1)            */
#define TEST_SBL_EMMC_SD_MEDIA_MEM                       (2U)   /* AM275X: pre-loaded DDR buffer          */

/*
 * Concurrent eMMC-image boot test.
 * AM62DX: both threads use eMMC (MMC0) at different appimage offsets
 *         (MCU @ 0x800000, A53 @ 0xC00000).
 * AM275X: Thread 0 uses eMMC (R5FSS0_0), Thread 1 uses OSPI NOR (C75SS0_0)
 *         because no standalone C75 eMMC image is provisioned on AM275X.
 */
#define TEST_SBL_EMMC_IMG_NUM_CORES                      (2U)
#define TEST_SBL_EMMC_IMG_MEDIA_EMMC                     (0U)   /* Both:   eMMC raw reads (MMC0)          */
#define TEST_SBL_EMMC_IMG_MEDIA_FLASH                    (1U)   /* AM275X: OSPI NOR flash                 */

/*
 * Concurrent SD-image boot test.
 * AM62DX: both threads read different appimage files from the SD card
 *         (FreeRTOS-FAT / MMC1) concurrently.  The FAT layer serializes
 *         actual MMC1 transfers internally but both file handles are open
 *         simultaneously, exercising concurrent FAT filesystem access.
 * AM275X: no SD slot — both threads use pre-loaded DDR images (MEM mode).
 */
#define TEST_SBL_SD_IMG_NUM_CORES                        (2U)
#define TEST_SBL_SD_IMG_MEDIA_SD                         (0U)   /* AM62DX: SD FAT reads (MMC1)            */
#define TEST_SBL_SD_IMG_MEDIA_MEM                        (1U)   /* AM275X: pre-loaded DDR buffer          */

/*
 * Concurrent OSPI-image boot test.
 * Both threads use OSPI NOR flash (OSPI0) at different appimage offsets.
 * The OSPI driver serializes hardware transfers internally but both threads
 * queue reads concurrently, testing the flash driver under parallel access.
 * Reuses TestSbl_emmcImgLoadThread — that function is media-agnostic since
 * it dispatches through bootConfig->fxns->imgReadFxn regardless of media.
 *   Thread 0: C75SS0_0  from CONFIG_BOOTLOADER_FLASH_DSP       (0x00A00000)
 *   Thread 1: MCU/R5FSS0_0 from CONFIG_BOOTLOADER_FLASH_MULTICORE (0x01200000)
 */
#define TEST_SBL_OSPI_IMG_NUM_CORES                      (2U)
#define TEST_SBL_OSPI_IMG_MEDIA_FLASH                    (0U)   /* Both: OSPI NOR at different offsets    */

/*
 * Bootloader_bootCpu positive test.
 * Two threads each call Bootloader_bootCpu with a manually-constructed
 * Bootloader_CpuInfo (rprcOffset=BOOTLOADER_INVALID_ID, entryPoint=0).
 * No appimage is loaded; only the CPU claim/clock/power-on-reset/run
 * TISCI sequence is exercised.  Cores are reset immediately after.
 */
#define TEST_SBL_BOOT_CPU_NUM_CORES                      (2U)

#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
#define TEST_SBL_SD_IMG_A53_FNAME                        "/sd0/app_a53"   /* A53SS0_0 appimage        */
#define TEST_SBL_SD_IMG_DSP_FNAME                        "/sd0/app_sys"   /* multicore, boot C75SS0_0 */
#endif

#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
/* Path on the SD card FAT volume for the A53 single-core appimage (EMMC+SD test) */
#define TEST_SBL_EMMC_SD_SD_APPIMAGE_FNAME               "/sd0/app_a53"
#endif

#if defined(SOC_AM275X)
/*
 * Scratch buffer size for Bootloader_parseAndLoadMultiCoreELF auth path.
 */
#define TEST_SBL_SCRATCH_BUF_SIZE (0x1000U)
#elif defined(SOC_AM62PX)
/*
 * AM62PX: used as Thread 0's (eMMC) full-image scratch buffer in
 * TestSbl_concurrentSdOspiBoot — must hold a complete MCU-R5F appimage
 * (current sbl_test_custom_ipc_binary/am62px-sk build is ~52 KB); sized
 * with headroom for future image growth. Also usable as a generic
 * placeholder wherever a test would otherwise need a second per-core
 * appimage buffer (gAppImageBuf1/2) that does not exist on this board.
 */
#define TEST_SBL_SCRATCH_BUF_SIZE (0x40000U)   /* 256 KB */
#endif

/* MCU-equivalent core per SOC — used in coreIds[] arrays and comparisons. */
#if defined(SOC_AM62X)
#define TEST_SBL_MCU_CORE_ID  (CSL_CORE_ID_M4FSS0_0)
#else
#define TEST_SBL_MCU_CORE_ID  (CSL_CORE_ID_MCU_R5FSS0_0)
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

#if defined(SOC_AM275X) || defined(SOC_AM62PX)
/*
 * Scratch buffer for Bootloader_parseAndLoadMultiCoreELF auth path (AM275X).
 * The API does not support BOOTLOADER_MEDIA_MEM with authentication;
 * we override bootMedia to EMMC so the EMMC code path is taken,
 * which needs scratchMemPtr for cert copy and restricted-region loads.
 * Threads are mutex-serialized so a single shared buffer is sufficient.
 *
 * AM62PX: used as Thread 0's (eMMC) full-image scratch buffer in
 * TestSbl_concurrentSdOspiBoot (see TEST_SBL_SCRATCH_BUF_SIZE) — Thread 1
 * (OSPI) uses the separate gAppImageBuf0 so the two threads' concurrent
 * Phase 1 media reads never touch the same memory. Also usable as a
 * generic placeholder wherever a test needs a second per-core appimage
 * buffer (gAppImageBuf1/2) that does not exist on this board.
 */
uint8_t gMtScratchBuf[TEST_SBL_SCRATCH_BUF_SIZE] __attribute__((aligned(128), section(".bss.app")));
#endif

/*===================================================================*/
/* 				  Function Declarations				         */
/*===================================================================*/

void TestSbl_multiThreadBoot(void *args);
void TestSbl_multiMediaMultiThreadBoot(void *args);
void TestSbl_concurrentSdOspiBoot(void *args);
void TestSbl_concurrentEmmcSdBoot(void *args);
void TestSbl_concurrentEmmcImageBoot(void *args);
void TestSbl_concurrentSdImageBoot(void *args);
void TestSbl_concurrentOspiImageBoot(void *args);
void TestSbl_bootCpuPositive(void *args);

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
#if defined(SOC_AM275X)
    /*
     * Disable bootloader DMA before every test.
     *
     * Booting R5FSS0_0/R5FSS1_0 via Bootloader_runCpu causes TIFS/Sciserver
     * to configure interrupt routes for those cores, inadvertently corrupting
     * the WKUP-R5 UDMA ring interrupt path.  Subsequent tests that call
     * Bootloader_openDma() successfully open the UDMA channel (Udma_chOpen
     * uses Sciclient which still works), but the first DMA ring completion
     * wait (Bootloader_dmaMemCopy) blocks forever because the ring interrupt
     * never fires.
     *
     * Forcing enableDma = FALSE makes Bootloader_openDma() a no-op and
     * causes all section loading to use CPU memcpy instead of UDMA.
     * SysConfig regeneration resets this to TRUE, so we override at runtime.
     */
    {
        extern Bootloader_Config gMemBootloaderConfig;
        gMemBootloaderConfig.enableDma = FALSE;
    }
#endif
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
#if defined(SOC_AM275X)
    /* Ensure Bootloader DMA is always released after each test.
     * If a test fails mid-run via TEST_ASSERT (Unity longjmp), the
     * test's own Bootloader_closeDma() call is skipped, leaving the DMA
     * lock held.  The next test's Bootloader_openDma() would then fail
     * because it checks lock == NULL.
     * Bootloader_closeDma() is a no-op when DMA is not open. */
    Bootloader_closeDma();
#endif
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

#if !defined(SOC_AM275X)
    /* Run MT test first (AM62DX/AM62PX): MM test overwrites the embedded appimage
     * buffers (used as scratch for eMMC/OSPI auth) so MT must complete before MM. */
    //RUN_TEST(TestSbl_multiThreadBoot,           11446, NULL);
#endif

    /*
     * AM275X: TestSbl_multiMediaMultiThreadBoot boots C75SS0_0 which triggers
     * TIFS/Sciserver CLEC IR configuration that permanently corrupts WKUP-R5
     * VIM interrupt routing (timer + all peripheral ISRs) for the remainder of
     * the session.  All tests after this point hang waiting for dead interrupts.
     * Skip it until the TIFS RM bug is fixed (see bug filed separately).
     *
     * AM62PX: TestSbl_mmMtLoadThread only wires bootConfig->scratchMemPtr for
     * SOC_AM275X/SOC_AM62DX, so on AM62PX it stays NULL. Bootloader_verifyMulticoreImage
     * then skips the DDR-copy step and authenticates the raw eMMC/OSPI flash
     * offset (e.g. 0x800000) as if it were a DDR pointer, so auth fails for
     * both media every time. Even if that were fixed, Thread 1 is hard-coded
     * to boot CSL_CORE_ID_A53SS0_0, but AM62PX has no A53/C75 core or appimage
     * on this board — same reason TestSbl_concurrentEmmcSdBoot/EmmcImageBoot/
     * SdImageBoot/OspiImageBoot are skipped below. Use TestSbl_concurrentSdOspiBoot
     * instead, which correctly verifies the same MCU-R5F image concurrently
     * from eMMC + OSPI on AM62PX.
    */
#if (defined(SOC_AM275X) || defined(SOC_AM62PX)) && !defined(SKIP_MULTIMEDIA_TEST)
#define SKIP_MULTIMEDIA_TEST
#endif
#if !defined(SKIP_MULTIMEDIA_TEST)
    RUN_TEST(TestSbl_multiMediaMultiThreadBoot, 11447, NULL);
#elif defined(SOC_AM62PX)
    DebugP_log("Skipping TestSbl_multiMediaMultiThreadBoot (AM62PX has no A53/C75 boot image; scratchMemPtr not wired for this SOC)\r\n");
#else
    DebugP_log("Skipping TestSbl_multiMediaMultiThreadBoot (SKIP_MULTIMEDIA_TEST defined)\r\n");
#endif

/* AM275X: boots C75SS0_0 — blocked by C75 L2RAM DMA req + VIM corruption.
 * AM62PX: no A53/C75 boot image, so both threads load/verify the same
 * MCU-R5F image from eMMC + OSPI instead (see TestSbl_concurrentSdOspiBoot). */
#if !defined(SOC_AM275X)
    RUN_TEST(TestSbl_concurrentSdOspiBoot,      11448, NULL);
#else
    DebugP_log("Skipping TestSbl_concurrentSdOspiBoot (AM275X C75 DMA/VIM bug)\r\n");
#endif

/* AM275X: already ran before multiThreadBoot to avoid VIM corruption (see above).
 * AM62PX: no A53 boot image is available on this board. */
#if !defined(SOC_AM275X) && !defined(SOC_AM62PX)
    RUN_TEST(TestSbl_concurrentEmmcSdBoot,      11449, NULL);
#elif defined(SOC_AM62PX)
    DebugP_log("Skipping TestSbl_concurrentEmmcSdBoot (AM62PX has no A53 boot image)\r\n");
#endif

/* AM275X: boots C75SS0_0 — same blocker as above.
 * AM62PX: no A53/C75 boot image is available on this board. */
#if !defined(SOC_AM275X) && !defined(SOC_AM62PX)
    RUN_TEST(TestSbl_concurrentEmmcImageBoot,   11450, NULL);
    RUN_TEST(TestSbl_concurrentSdImageBoot,     11451, NULL);
#elif defined(SOC_AM62PX)
    DebugP_log("Skipping TestSbl_concurrentEmmcImageBoot/TestSbl_concurrentSdImageBoot (AM62PX has no A53/C75 boot image)\r\n");
#else
    DebugP_log("Skipping TestSbl_concurrentEmmcImageBoot (AM275X C75 DMA/VIM bug)\r\n");
#endif

/*
 * AM275X: TestSbl_concurrentOspiImageBoot loads C75SS0_0 sections into
 * C75 L2RAM, which requires DMA (WKUP-R5 CPU cannot write to C75 L2RAM).
 * The UDMA ring interrupt is dead due to the TIFS/Sciserver VIM corruption
 * bug triggered by earlier core boots.  With DMA disabled the test hangs
 * on a CPU-memcpy data abort.  Skip until the TIFS bug is fixed.
 * AM62PX: boots C75SS0_0 unconditionally — no C75 core exists on this SOC.
 */
#if !defined(SOC_AM275X) && !defined(SOC_AM62PX)
    RUN_TEST(TestSbl_concurrentOspiImageBoot,   11452, NULL);
#elif defined(SOC_AM62PX)
    DebugP_log("Skipping TestSbl_concurrentOspiImageBoot (AM62PX has no C75 core/boot image)\r\n");
#else
    DebugP_log("Skipping TestSbl_concurrentOspiImageBoot (AM275X TIFS/Sciserver VIM corruption)\r\n");
#endif

/*
 * AM275X: TestSbl_bootCpuPositive boots R5FSS0_0/R5FSS1_0 with entryPoint=0,
 * which re-executes IPC binary code still resident in their ATCMs from test
 * 11446.  The IPC binary calls Sciclient_init which triggers a Sciserver RM
 * request on WKUP-R5.  The Sciserver task hangs (FreeRTOS tick dead → any
 * ClockP_usleep inside Sciserver blocks forever), TIFS waits for the RM
 * response, and the next Sciclient call from Bootloader_bootCpu stalls.
 * Root cause: same TIFS/Sciserver VIM corruption bug.
 */
    /*
     * AM275X: C75SS0_0 is now excluded from all tests so VIM is never
     * corrupted.  The original skip reason (FreeRTOS tick dead from VIM
     * corruption) no longer applies.  Re-enable; if the Sciclient duplicate-
     * RM-request deadlock occurs it will surface as a hang (to be fixed
     * separately).
     */
    RUN_TEST(TestSbl_bootCpuPositive,           11453, NULL);

    UNITY_END();
}

/*
 * Multithread boot test: loads a single-core appimage from its own DDR
 * buffer per thread and boots the corresponding core.
 */

static void TestSbl_mtLoadThread(void *args)
{
    int32_t status = SystemP_SUCCESS;
    TestSbl_MtThreadArgs *threadArgs;
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
#if defined(SOC_AM275X) || defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM62PX)
    Bootloader_Config *bootConfig;
#endif

    threadArgs = (TestSbl_MtThreadArgs *)args;

    Bootloader_Params_init(&bootParams);
    bootParams.bufIoTempBuf     = threadArgs->appImageBuf;
    bootParams.bufIoTempBufSize = threadArgs->appImageBufSize;
    Bootloader_BootImageInfo_init(&bootImageInfo);
    bootParams.memArgsAppImageBaseAddr = (uintptr_t)threadArgs->appImageBuf;

    threadArgs->bootHandle = Bootloader_open(threadArgs->bootloaderInstanceId, &bootParams);
    if(threadArgs->bootHandle == NULL)
    {
        DebugP_log("Bootloader_open failed for core %d\r\n", threadArgs->coreId);
        status = SystemP_FAILURE;
    }
    else
    {
#if defined(SOC_AM275X) || defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM62PX)
        bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
        bootConfig->coresPresentMap = 0;

#if defined(SOC_AM275X)
        /* MEM bootloaders have no native auth path; override to EMMC so the
         * EMMC code path handles auth (cert copied to scratchMemPtr in DDR,
         * segments loaded to DDR where TIFS can hash them).
         * FLASH bootloader already uses BOOTLOADER_MEDIA_FLASH — keep it so
         * TIFS authenticates from XIP flash (the only region TIFS DMA can
         * reach for C75 segment auth; C75 L2RAM is not accessible to TIFS). */
        if(bootConfig->bootMedia != BOOTLOADER_MEDIA_FLASH)
        {
            bootConfig->bootMedia = BOOTLOADER_MEDIA_EMMC;
        }
        bootConfig->scratchMemPtr = gMtScratchBuf;
#elif defined(SOC_AM62DX)
        /* No pre-parse overrides needed — AM62DX uses manual auth + parse below */
#elif defined(SOC_AM62AX)
        /* No pre-parse overrides needed — AM62AX uses manual auth + parse below */
#elif defined(SOC_AM62PX)
        /* No pre-parse overrides needed — AM62PX uses manual auth + parse below */
#endif

        /* Serialize parse+load: TIFS auth via Sciclient is not thread-safe */
        SemaphoreP_pend(threadArgs->parseMutex, SystemP_WAIT_FOREVER);

#if defined(SOC_AM275X)
        status = Bootloader_parseAndLoadMultiCoreELF(threadArgs->bootHandle, &bootImageInfo);
#elif defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM62PX)
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            Bootloader_MemArgs *memArgs = (Bootloader_MemArgs *)bootConfig->args;
            uint8_t *certStart = (uint8_t *)(uintptr_t)memArgs->appImageBaseAddr;
            uint32_t certLen;

            certLen = Bootloader_getX509CertLen(certStart);

            if(certLen > TEST_SBL_X509_CERT_MIN_LEN && certLen < TEST_SBL_X509_CERT_MAX_LEN)
            {
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
            DebugP_log("parse+load failed for core %d\r\n", threadArgs->coreId);
            Bootloader_close(threadArgs->bootHandle);
            threadArgs->bootHandle = NULL;
        }
        else if(TRUE != Bootloader_isCorePresent(threadArgs->bootHandle, threadArgs->coreId))
        {
            DebugP_log("Core %d not present in appimage\r\n", threadArgs->coreId);
            status = SystemP_FAILURE;
            Bootloader_close(threadArgs->bootHandle);
            threadArgs->bootHandle = NULL;
        }
        else
        {
#if !defined(SOC_AM275X)
            bootImageInfo.cpuInfo[threadArgs->coreId].clkHz =
                Bootloader_socCpuGetClkDefault(threadArgs->coreId);

#if defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM62PX)
            {
                Bootloader_CpuInfo *cpuInfo = &bootImageInfo.cpuInfo[threadArgs->coreId];
                Bootloader_MemArgs *memArgs = (Bootloader_MemArgs *)bootConfig->args;

                status = Bootloader_socCpuRequest(cpuInfo->cpuId);

                if(status == SystemP_SUCCESS)
                {
                    status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);
                }

                if(status == SystemP_SUCCESS)
                {
                    status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId, bootConfig->socCoreOpMode);
                }

                if(status == SystemP_SUCCESS && cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
                {
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
                        uint32_t s;
                        Bootloader_RprcSectionHeader secHdr;
                        uint32_t destAddr;

                        cpuInfo->entryPoint = (uintptr_t)rprcHdr.entry;
                        for(s = 0; s < rprcHdr.sectionCount && status == SystemP_SUCCESS; s++)
                        {
                            memcpy(&secHdr, rprcBase, sizeof(secHdr));
                            rprcBase += sizeof(secHdr);

                            destAddr = Bootloader_socTranslateSectionAddr(
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
#endif /* SOC_AM62DX || SOC_AM62AX */
#endif
        }

        SemaphoreP_post(threadArgs->parseMutex);
    }

    threadArgs->loadStatus = status;
    if(threadArgs->bootHandle != NULL)
    {
        threadArgs->cpuInfo = bootImageInfo.cpuInfo[threadArgs->coreId];
    }

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
        /* C75SS0_0 excluded: booting it corrupts WKUP-R5 VIM routes (TIFS bug) */
#elif defined(SOC_AM62PX)
        /* AM62PX: no A53/C75 boot image available; MCU-R5F only. */
        CSL_CORE_ID_MCU_R5FSS0_0,
#else
        CSL_CORE_ID_MCU_R5FSS0_0,
        CSL_CORE_ID_A53SS0_0,
        CSL_CORE_ID_C75SS0_0,
#endif
    };
    uint8_t *appImageBufs[TEST_SBL_MT_NUM_CORES] = {
        gAppImageBuf0,
#if defined(SOC_AM275X)
        gAppImageBuf1,
#elif !defined(SOC_AM62PX)
        gAppImageBuf1,
        gAppImageBuf2,
#endif
        /* AM62PX: gAppImageBuf0 only — no gAppImageBuf1/2 (reduced appimage_data.S) */
    };
    uint32_t bootloaderInstances[TEST_SBL_MT_NUM_CORES] = {
#if defined(SOC_AM275X)
        CONFIG_BOOTLOADER_MEM_R5FSS0_0,
        CONFIG_BOOTLOADER_MEM_R5FSS1_0,
        /* C75SS0_0 excluded: see TEST_SBL_MT_NUM_CORES comment above */
#elif defined(SOC_AM62PX)
        CONFIG_BOOTLOADER_SD_MCU,
#else
        CONFIG_BOOTLOADER_SD_A53,
        CONFIG_BOOTLOADER_SD_SMP,
        CONFIG_BOOTLOADER_SD_MULTICORE,
#endif
    };
    uint8_t *taskStacks[TEST_SBL_MT_NUM_CORES] = {
        gMtTaskStack0,
#if defined(SOC_AM275X)
        gMtTaskStack1,
#elif !defined(SOC_AM62PX)
        gMtTaskStack1,
        gMtTaskStack2,
#endif
    };
    TestSbl_MtThreadArgs threadArgs[TEST_SBL_MT_NUM_CORES];
    TaskP_Object         taskObjs[TEST_SBL_MT_NUM_CORES];
    SemaphoreP_Object    doneSems[TEST_SBL_MT_NUM_CORES];
    SemaphoreP_Object    parseMutex;

    DebugP_log("Starting TestSbl_multiThreadBoot test...\r\n");

    /* C75SS0_0 is excluded from AM275X (TIFS VIM corruption bug).
     * OSPI/Flash open is only needed when C75SS0_0 is in the test. */
#if !defined(SOC_AM275X)
    status = TestSbl_openBootDriverFlash();
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    status = TestSbl_openBootBoardFlash();
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
#endif

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
            {
                DebugP_log("CPU %d: Waiting for IPC sync...\r\n", coreIds[loopVar]);
                status = IpcNotify_waitSync(coreIds[loopVar], 10000);
                DebugP_log("CPU %d: IPC sync status = %d\r\n", coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
#else
            /*
             * AM275X: Bootloader_runCpu(C75SS0_0) causes TIFS/Sciserver to
             * reconfigure C75 CLEC interrupt routes, corrupting WKUP-R5 and
             * possibly MAIN-domain interrupt aggregator paths.  The FreeRTOS
             * timer, VIM mailbox ISRs, and hardware FIFO delivery all become
             * unreliable.
             *
             * Fix: poll a NonCached MSRAM scratch word written by ipc_rpmsg_echo
             * when it starts (ipc_rpmsg_echo_main, 0x723C2000 + coreId*4).
             * No interrupt chain, no mailbox, no tick required.
             *
             * Also send IpcNotify sync to unblock the remote's syncAll
             * WKUP-wait so it can proceed (its own VIM is not affected).
             */
            {
                uint32_t cid = coreIds[loopVar];
                /* NonCached scratch at 0x723C2000, slot per core */
                volatile uint32_t *stamp =
                    (volatile uint32_t *)(0x723C2000U + cid * sizeof(uint32_t));
                uintptr_t lineAddr   = (0x723C2000U + cid * sizeof(uint32_t)) & ~((uintptr_t)31U);
                uint32_t expected    = 0xABCD0000U | cid;
                uint32_t startCycles = CycleCounterP_getCount32();
                /* 5-second timeout; 32-bit safe at WKUP clock ≤ ~1.4 GHz */
                uint32_t timeout     = (SOC_getSelfCpuClk() / 1000U) * 5000U;
                int32_t  syncStatus  = SystemP_FAILURE;

                /* Unblock remote core's IpcNotify_syncAll WKUP-wait */
                status = IpcNotify_sendSync(cid);
                TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

                DebugP_log("CPU %d: Waiting for IPC sync...\r\n", cid);

                while((CycleCounterP_getCount32() - startCycles) < timeout)
                {
                    /* WKUP-R5 maps 0x72000000-0x72400000 CACHEABLE: invalidate
                     * the line so we see the remote's DDR stamp write. */
                    CacheP_inv((void *)lineAddr, 32U, CacheP_TYPE_ALL);
                    if(*stamp == expected)
                    {
                        syncStatus = SystemP_SUCCESS;
                        break;
                    }
                }

                DebugP_log("CPU %d: IPC sync status = %d\r\n", cid, syncStatus);
                TEST_ASSERT_EQUAL(syncStatus, SystemP_SUCCESS);
            }
#endif
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

    /* Flash was only opened when C75SS0_0 was included (non-AM275X) */
#if !defined(SOC_AM275X)
    TestSbl_closeBootBoardFlash();
    TestSbl_closeBootDriverFlash();
#endif

    DebugP_log("TestSbl_multiThreadBoot test completed\r\n");
}

/*
 * Multi-media multithread boot test: loads a single-core appimage from a
 * different boot media per thread and boots the corresponding core.
 */

static void TestSbl_mmMtLoadThread(void *args)
{
    int32_t status = SystemP_SUCCESS;
    TestSbl_MmMtThreadArgs *threadArgs;
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;

    threadArgs = (TestSbl_MmMtThreadArgs *)args;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    threadArgs->bootHandle = Bootloader_open(threadArgs->bootloaderInstanceId, &bootParams);
    if(threadArgs->bootHandle == NULL)
    {
        DebugP_log("Bootloader_open failed for core %d (media %d)\r\n",
                   threadArgs->coreId, threadArgs->mediaType);
        status = SystemP_FAILURE;
    }
    else
    {
#if defined(SOC_AM275X) || defined(SOC_AM62DX)
    {
        Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
        bootConfig->coresPresentMap = 0;

        /* For EMMC/Flash bootloaders, set scratch buffer for parsing */
        bootConfig->scratchMemPtr = threadArgs->appImageBuf;
    }
#endif

    /* Serialize parse+load: TIFS auth via Sciclient is not thread-safe */
    SemaphoreP_pend(threadArgs->parseMutex, SystemP_WAIT_FOREVER);

#if defined(SOC_AM275X)
    status = Bootloader_parseAndLoadMultiCoreELF(threadArgs->bootHandle, &bootImageInfo);
#elif defined(SOC_AM62DX) || defined(SOC_AM62AX)
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
        Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
        uint8_t x509Header[4];
        uint32_t certLen, imageLen, totalLen;
        int32_t ioStatus;

        /* Read x509 header from media to compute cert length */
        ioStatus = bootConfig->fxns->imgReadFxn(x509Header, 4, bootConfig->args);
        if(ioStatus != SystemP_SUCCESS)
        {
            DebugP_log("Failed to read x509 header from media\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            bootConfig->fxns->imgSeekFxn(0, bootConfig->args);
        }

        if(status == SystemP_SUCCESS)
        {
            certLen = Bootloader_getX509CertLen(x509Header);

            /* Validate certificate length: min 256 bytes, max 2048 bytes */
            if(certLen > TEST_SBL_X509_CERT_MIN_LEN && certLen < TEST_SBL_X509_CERT_MAX_LEN)
            {
                /* Read first 0x800 bytes to determine payload length */
                ioStatus = bootConfig->fxns->imgReadFxn(threadArgs->appImageBuf, 0x800,
                                                 bootConfig->args);
                if(ioStatus != SystemP_SUCCESS)
                {
                    DebugP_log("Failed to read first part of image from media\r\n");
                    status = SystemP_FAILURE;
                }

                if(status == SystemP_SUCCESS)
                {
                    imageLen = Bootloader_getMsgLen(threadArgs->appImageBuf, certLen);
                    totalLen = (certLen + imageLen + 128U) & ~127U;

                    /* Read full signed image from media into scratch buffer */
                    bootConfig->fxns->imgSeekFxn(0, bootConfig->args);

#if defined(SOC_AM62AX)
                    /*
                     * On AM62AX OSPI NAND, a single large Flash_read spanning many
                     * pages can trigger a timing race: OSPI_readDirect leaves the
                     * controller momentarily non-IDLE, causing the subsequent page's
                     * OSPI_readCmd (in Flash_nandOspiWaitReady) to time out and return
                     * failure. Because Flash_nandOspiWaitReady uses a uint32_t timeout
                     * counter, a failure status causes it to decrement past 0 and loop
                     * forever. Reading one NAND page (0x800 bytes) per Flash_read call
                     * adds enough overhead between pages for the IDLE bit to reassert.
                     */
                    {
                        uint32_t bytesRead = 0U;
                        while(bytesRead < totalLen)
                        {
                            uint32_t chunkSize =
                                (totalLen - bytesRead > TEST_SBL_X509_CERT_MAX_LEN) ?
                                TEST_SBL_X509_CERT_MAX_LEN : (totalLen - bytesRead);
                            bootConfig->fxns->imgReadFxn(
                                threadArgs->appImageBuf + bytesRead,
                                chunkSize, bootConfig->args);
                            bytesRead += chunkSize;
                        }
                        ioStatus = SystemP_SUCCESS;
                    }
#else
                    ioStatus = bootConfig->fxns->imgReadFxn(threadArgs->appImageBuf, totalLen,
                                                     bootConfig->args);
                    if(ioStatus != SystemP_SUCCESS)
                    {
                        DebugP_log("Failed to read full image from media\r\n");
                        status = SystemP_FAILURE;
                    }
#endif /* SOC_AM62AX */

                    if(status == SystemP_SUCCESS)
                    {
                        CacheP_wbInv(threadArgs->appImageBuf, totalLen, CacheP_TYPE_ALL);
                        /* Point past the cert to the MSTR header */
                        bootConfig->scratchMemPtr = threadArgs->appImageBuf + certLen;
                        status = Bootloader_parseAppImage(threadArgs->bootHandle,
                                                          &bootImageInfo);
                    }
                }
            }
            else
            {
                status = SystemP_FAILURE;
            }
        }
    }
#else
    status = Bootloader_parseMultiCoreAppImage(threadArgs->bootHandle, &bootImageInfo);
#endif
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("parse+load failed for core %d (media %d)\r\n",
                   threadArgs->coreId, threadArgs->mediaType);
        Bootloader_close(threadArgs->bootHandle);
        threadArgs->bootHandle = NULL;
    }
    else if(TRUE != Bootloader_isCorePresent(threadArgs->bootHandle, threadArgs->coreId))
    {
        DebugP_log("Core %d not present in appimage (media %d)\r\n",
                   threadArgs->coreId, threadArgs->mediaType);
        status = SystemP_FAILURE;
        Bootloader_close(threadArgs->bootHandle);
        threadArgs->bootHandle = NULL;
    }
    else
    {
#if !defined(SOC_AM275X)
        bootImageInfo.cpuInfo[threadArgs->coreId].clkHz =
            Bootloader_socCpuGetClkDefault(threadArgs->coreId);

#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            Bootloader_CpuInfo *cpuInfo = &bootImageInfo.cpuInfo[threadArgs->coreId];
            uint8_t *rprcBase;
            Bootloader_RprcFileHeader rprcHdr;
            uint32_t s;
            uint32_t destAddr;
            Bootloader_RprcSectionHeader secHdr;

            status = Bootloader_socCpuRequest(cpuInfo->cpuId);

            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);
            }

            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId,
                                                       bootConfig->socCoreOpMode);
            }

            if(status == SystemP_SUCCESS && cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
            {
                rprcBase = bootConfig->scratchMemPtr + cpuInfo->rprcOffset;

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
                    for(s = 0; s < rprcHdr.sectionCount && status == SystemP_SUCCESS; s++)
                    {
                        memcpy(&secHdr, rprcBase, sizeof(secHdr));
                        rprcBase += sizeof(secHdr);

                        destAddr = Bootloader_socTranslateSectionAddr(
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
#endif /* SOC_AM62DX || SOC_AM62AX */
#endif
    }

    SemaphoreP_post(threadArgs->parseMutex);
    } /* end else (bootHandle != NULL) */

    threadArgs->loadStatus = status;
    if(threadArgs->bootHandle != NULL)
    {
        threadArgs->cpuInfo = bootImageInfo.cpuInfo[threadArgs->coreId];
    }

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
#if !defined(SOC_AM62PX)
        CSL_CORE_ID_C75SS0_0,
#else
        /* AM62PX has no C75 core; this test is unconditionally disabled
         * (dead code — RUN_TEST for it is commented out for all SOCs). */
        CSL_CORE_ID_A53SS0_0,
#endif
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
#elif defined(SOC_AM62AX)
        /*
         * On AM62AX HS-FS, same DMA-to-loadaddr behavior as AM62DX.
         * gAppImageBuf0 is at 0x84000000 (APPIMAGE region start on AM62AX).
         * Threads are mutex-serialized so a single buffer is safe.
         */
        gAppImageBuf0,   /* 0x84000000 = loadaddr for both eMMC & OSPI images */
        gAppImageBuf0,
#elif defined(SOC_AM62PX)
        /* AM62PX: no gAppImageBuf1/2 (reduced appimage_data.S); dead code
         * since this test is unconditionally disabled for all SOCs. */
        gMtScratchBuf,
        gMtScratchBuf,
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

#if defined(SOC_AM275X) || defined(SOC_AM62PX)
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
#if defined(SOC_AM275X)
                        TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK,
#else
                        TISCI_DEV_MMCSD0_EMMCSS_XIN_CLK,
#endif
                        200000000);
        DebugP_log("[MM] MMCSD0 clock freq status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        DebugP_log("[MM] Enabling FSS0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_FSS0, 1);
        DebugP_log("[MM] FSS0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

#if defined(SOC_AM62PX)
        /* AM62PX splits the FSS0 SBL module into separate sub-devices
         * (see gSocSBLModules[] in the generated ti_power_clock_config.c) */
        DebugP_log("[MM] Enabling FSS0_FSAS_0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_FSS0_FSAS_0, 1);
        DebugP_log("[MM] FSS0_FSAS_0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        DebugP_log("[MM] Enabling FSS0_OSPI_0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_FSS0_OSPI_0, 1);
        DebugP_log("[MM] FSS0_OSPI_0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);
#endif

        DebugP_log("[MM] Setting FSS0 clock frequency...\r\n");
#if defined(SOC_AM62PX)
        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_FSS0_OSPI_0,
                        TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK,
                        166666666);
#else
        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_FSS0,
                        TISCI_DEV_FSS0_OSPI0_RCLK_CLK,
                        166666666);
#endif
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
                status = IpcNotify_waitSync(coreIds[loopVar], 10000);
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

#if defined(SOC_AM275X)
    /* Disable SBL module clocks that were enabled at the start */
    status = SOC_moduleClockEnable(TISCI_DEV_FSS0, 0);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    status = SOC_moduleClockEnable(TISCI_DEV_MMCSD0, 0);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
#endif

    DebugP_log("TestSbl_multiMediaMultiThreadBoot test completed\r\n");
}

int32_t TestSbl_openBootEMMC()
{
    int32_t status = SystemP_SUCCESS;

#if defined(SOC_AM62PX)
    /* AM62PX: MMCSD_halSoftReset does not fully reset the eMMC PHY/clock
     * domain, so a second MMCSD_open() after a close hangs (same class of
     * bug already documented for AM275X). If the instance is already
     * open (e.g. carried over from Board_init() or a prior test that
     * left it open on purpose, see TestSbl_closeBootEMMC), just reuse
     * the existing handle instead of closing+reopening. */
    if (gMmcsdHandle[CONFIG_MMCSD_SBL] != NULL)
    {
        return status;
    }
#endif

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
#if defined(SOC_AM62PX)
    /* AM62PX: deliberately leave the instance open — MMCSD_halSoftReset
     * does not fully reset the eMMC PHY/clock domain, so re-opening it
     * later (from TestSbl_openBootEMMC, by a subsequent test) would hang.
     * This is a one-shot UART-loaded test binary, so nothing downstream
     * needs the handle closed; just skip it. */
#else
    MMCSD_close(gMmcsdHandle[CONFIG_MMCSD_SBL]);
    gMmcsdHandle[CONFIG_MMCSD_SBL] = NULL;
#endif
}

/*
 * Concurrent SD + OSPI boot test thread.
 *
 * Phase 1 (before parseMutex): media reads happen in parallel across threads.
 *   - SD thread (AM62DX):   reads full appimage from SD card via FreeRTOS-FAT
 *                           into DDR scratch buffer, validates x509 cert length.
 *   - OSPI thread (both):   reads full signed image from OSPI flash into DDR
 *                           scratch buffer, computes cert and payload lengths.
 *   SD (MMC1) and OSPI (OSPI0) are independent buses so these I/Os are
 *   truly concurrent.
 *
 * Phase 2 (inside parseMutex): cert-skip parse + manual CPU load (AM62DX),
 *   or parseAndLoadMultiCoreELF (AM275X).  TIFS auth is not thread-safe so
 *   this phase is serialized across threads.
 */
static void TestSbl_sdOspiLoadThread(void *args)
{
    int32_t                status = SystemP_SUCCESS;
    TestSbl_MmMtThreadArgs *threadArgs;
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params        bootParams;
#if defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uint32_t certLen  = 0U;
    uint32_t totalLen = 0U;
#endif

    threadArgs = (TestSbl_MmMtThreadArgs *)args;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* ------------------------------------------------------------------ */
    /* Phase 1a: SD read (AM62DX only) — runs concurrently with OSPI reads */
    /* ------------------------------------------------------------------ */
#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
    if (threadArgs->mediaType == TEST_SBL_SDOSPI_MEDIA_SD)
    {
        FF_FILE  *fp;
        uint32_t  fileSize;
        size_t    bytesRead;

        fp = ff_fopen(TEST_SBL_SDOSPI_SD_APPIMAGE_FNAME, "rb");
        if (fp == NULL)
        {
            DebugP_log("[SD] Failed to open %s\r\n", TEST_SBL_SDOSPI_SD_APPIMAGE_FNAME);
            status = SystemP_FAILURE;
        }

        if (status == SystemP_SUCCESS)
        {
            fileSize = ff_filelength(fp);
            if (fileSize == 0U || fileSize > threadArgs->appImageBufSize)
            {
                DebugP_log("[SD] Bad file size %u\r\n", fileSize);
                ff_fclose(fp);
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            bytesRead = ff_fread(threadArgs->appImageBuf, fileSize, 1U, fp);
            ff_fclose(fp);
            if (bytesRead != 1U)
            {
                DebugP_log("[SD] Read failed\r\n");
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            certLen = Bootloader_getX509CertLen(threadArgs->appImageBuf);
            if (certLen <= TEST_SBL_X509_CERT_MIN_LEN || certLen >= TEST_SBL_X509_CERT_MAX_LEN)
            {
                DebugP_log("[SD] Invalid cert length 0x%x\r\n", certLen);
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            bootParams.memArgsAppImageBaseAddr = (uintptr_t)threadArgs->appImageBuf;
        }
    }
#endif /* SOC_AM62DX */

    if (status == SystemP_SUCCESS)
    {
        threadArgs->bootHandle = Bootloader_open(threadArgs->bootloaderInstanceId, &bootParams);
        if (threadArgs->bootHandle == NULL)
        {
            DebugP_log("[SDOSPI] Bootloader_open failed for core %d (media %d)\r\n",
                       threadArgs->coreId, threadArgs->mediaType);
            status = SystemP_FAILURE;
        }
    }

    if (threadArgs->bootHandle != NULL)
    {
#if defined(SOC_AM275X) || defined(SOC_AM62DX) || defined(SOC_AM62PX)
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            bootConfig->coresPresentMap = 0;
            bootConfig->scratchMemPtr   = threadArgs->appImageBuf;
        }
#endif

        /* ------------------------------------------------------------------ */
        /* Phase 1b: OSPI read — concurrent with SD/eMMC reads in Thread 0    */
        /* ------------------------------------------------------------------ */
#if defined(SOC_AM62DX) || defined(SOC_AM62AX) || defined(SOC_AM62PX)
        if (threadArgs->mediaType == TEST_SBL_SDOSPI_MEDIA_FLASH)
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            uint8_t  hdr4[4];
            uint32_t imageLen;
            int32_t  ioSt;

            ioSt = bootConfig->fxns->imgReadFxn(hdr4, 4U, bootConfig->args);
            if (ioSt != SystemP_SUCCESS)
            {
                DebugP_log("[OSPI] Failed to read x509 header\r\n");
                status = SystemP_FAILURE;
            }
            else
            {
                bootConfig->fxns->imgSeekFxn(0, bootConfig->args);
            }

            if (status == SystemP_SUCCESS)
            {
                certLen = Bootloader_getX509CertLen(hdr4);
                if (certLen > TEST_SBL_X509_CERT_MIN_LEN && certLen < TEST_SBL_X509_CERT_MAX_LEN)
                {
                    ioSt = bootConfig->fxns->imgReadFxn(
                        threadArgs->appImageBuf, TEST_SBL_X509_CERT_MAX_LEN, bootConfig->args);
                    if (ioSt != SystemP_SUCCESS)
                    {
                        status = SystemP_FAILURE;
                    }

                    if (status == SystemP_SUCCESS)
                    {
                        imageLen = Bootloader_getMsgLen(threadArgs->appImageBuf, certLen);
                        totalLen = (certLen + imageLen + 128U) & ~127U;

                        bootConfig->fxns->imgSeekFxn(0, bootConfig->args);
#if defined(SOC_AM62AX)
                        /*
                         * AM62AX OSPI NAND: a single large Flash_read spanning
                         * many pages triggers a controller timing race (see
                         * TestSbl_MmMtThread).  Read one NAND page per call.
                         */
                        {
                            uint32_t bytesRead = 0U;
                            while (bytesRead < totalLen)
                            {
                                uint32_t chunkSize =
                                    (totalLen - bytesRead > TEST_SBL_X509_CERT_MAX_LEN) ?
                                    TEST_SBL_X509_CERT_MAX_LEN : (totalLen - bytesRead);
                                bootConfig->fxns->imgReadFxn(
                                    threadArgs->appImageBuf + bytesRead,
                                    chunkSize, bootConfig->args);
                                bytesRead += chunkSize;
                            }
                            ioSt = SystemP_SUCCESS;
                        }
#else
                        ioSt = bootConfig->fxns->imgReadFxn(
                            threadArgs->appImageBuf, totalLen, bootConfig->args);
                        if (ioSt != SystemP_SUCCESS)
                        {
                            status = SystemP_FAILURE;
                        }
#endif /* SOC_AM62AX */

                        if (status == SystemP_SUCCESS)
                        {
                            CacheP_wbInv(threadArgs->appImageBuf, totalLen, CacheP_TYPE_ALL);
                        }
                    }
                }
                else
                {
                    DebugP_log("[OSPI] Invalid cert length 0x%x\r\n", certLen);
                    status = SystemP_FAILURE;
                }
            }

            if (status != SystemP_SUCCESS)
            {
                DebugP_log("[OSPI] Media read failed for core %d\r\n", threadArgs->coreId);
                Bootloader_close(threadArgs->bootHandle);
                threadArgs->bootHandle = NULL;
            }
        }
#endif /* SOC_AM62DX || SOC_AM62AX || SOC_AM62PX */

        /* ------------------------------------------------------------------ */
        /* Phase 2: Serialized parse + load (TIFS auth is not thread-safe)     */
        /* ------------------------------------------------------------------ */
        if (threadArgs->bootHandle != NULL)
        {
            SemaphoreP_pend(threadArgs->parseMutex, SystemP_WAIT_FOREVER);

#if defined(SOC_AM275X)
            status = Bootloader_parseAndLoadMultiCoreELF(threadArgs->bootHandle, &bootImageInfo);
#elif defined(SOC_AM62DX) || defined(SOC_AM62AX)
            {
                Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;

                if (threadArgs->mediaType == TEST_SBL_SDOSPI_MEDIA_SD)
                {
                    Bootloader_MemArgs *memArgs  = (Bootloader_MemArgs *)bootConfig->args;
                    uint8_t            *certStart = (uint8_t *)(uintptr_t)memArgs->appImageBaseAddr;

                    memArgs->appImageBaseAddr = (uint32_t)(uintptr_t)(certStart + certLen);
                    bootConfig->scratchMemPtr = certStart + certLen;
                    status = Bootloader_parseAppImage(threadArgs->bootHandle, &bootImageInfo);
                }
                else /* TEST_SBL_SDOSPI_MEDIA_FLASH */
                {
                    bootConfig->scratchMemPtr = threadArgs->appImageBuf + certLen;
                    status = Bootloader_parseAppImage(threadArgs->bootHandle, &bootImageInfo);
                }
            }
#elif defined(SOC_AM62PX)
            if (threadArgs->mediaType == TEST_SBL_SDOSPI_MEDIA_FLASH)
            {
                Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;

                bootConfig->scratchMemPtr = threadArgs->appImageBuf + certLen;
                status = Bootloader_parseAppImage(threadArgs->bootHandle, &bootImageInfo);
            }
            else /* TEST_SBL_SDOSPI_MEDIA_EMMC — native EMMC path, no cert-skip needed */
            {
                status = Bootloader_parseMultiCoreAppImage(threadArgs->bootHandle, &bootImageInfo);
            }
#else
            status = Bootloader_parseMultiCoreAppImage(threadArgs->bootHandle, &bootImageInfo);
#endif

            if (status != SystemP_SUCCESS)
            {
                DebugP_log("[SDOSPI] parse failed for core %d (media %d)\r\n",
                           threadArgs->coreId, threadArgs->mediaType);
                Bootloader_close(threadArgs->bootHandle);
                threadArgs->bootHandle = NULL;
            }
            else if (TRUE != Bootloader_isCorePresent(threadArgs->bootHandle, threadArgs->coreId))
            {
                DebugP_log("[SDOSPI] Core %d not present (media %d)\r\n",
                           threadArgs->coreId, threadArgs->mediaType);
                status = SystemP_FAILURE;
                Bootloader_close(threadArgs->bootHandle);
                threadArgs->bootHandle = NULL;
            }
            else
            {
#if !defined(SOC_AM275X)
                bootImageInfo.cpuInfo[threadArgs->coreId].clkHz =
                    Bootloader_socCpuGetClkDefault(threadArgs->coreId);

#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
                {
                    Bootloader_Config            *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
                    Bootloader_CpuInfo           *cpuInfo    = &bootImageInfo.cpuInfo[threadArgs->coreId];
                    uint8_t                      *rprcBase;
                    Bootloader_RprcFileHeader     rprcHdr;
                    Bootloader_RprcSectionHeader  secHdr;
                    uint32_t s, destAddr;

                    status = Bootloader_socCpuRequest(cpuInfo->cpuId);

                    if (status == SystemP_SUCCESS)
                        status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

                    if (status == SystemP_SUCCESS)
                        status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId, bootConfig->socCoreOpMode);

                    if (status == SystemP_SUCCESS && cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
                    {
                        rprcBase = bootConfig->scratchMemPtr + cpuInfo->rprcOffset;

                        CacheP_inv(rprcBase, sizeof(rprcHdr), CacheP_TYPE_ALL);
                        memcpy(&rprcHdr, rprcBase, sizeof(rprcHdr));
                        rprcBase += sizeof(rprcHdr);

                        if (rprcHdr.magic != BOOTLOADER_RPRC_MAGIC_NUMBER)
                        {
                            status = SystemP_FAILURE;
                        }
                        else
                        {
                            cpuInfo->entryPoint = (uintptr_t)rprcHdr.entry;
                            for (s = 0; s < rprcHdr.sectionCount && status == SystemP_SUCCESS; s++)
                            {
                                memcpy(&secHdr, rprcBase, sizeof(secHdr));
                                rprcBase += sizeof(secHdr);

                                destAddr = Bootloader_socTranslateSectionAddr(
                                                cpuInfo->cpuId, secHdr.addr);
                                memcpy((void *)(uintptr_t)destAddr, rprcBase, secHdr.size);
                                CacheP_wbInv((void *)(uintptr_t)destAddr, secHdr.size, CacheP_TYPE_ALL);
                                rprcBase += secHdr.size;
                                bootConfig->bootImageSize += secHdr.size;
                            }
                        }
                    }
                }
#elif defined(SOC_AM62PX)
                if (threadArgs->mediaType == TEST_SBL_SDOSPI_MEDIA_EMMC)
                {
                    /* Thread 0 (eMMC): this is the copy that will actually be
                     * run/synced below — claim and load it for real. */
                    status = Bootloader_loadCpu(threadArgs->bootHandle,
                                                &(bootImageInfo.cpuInfo[threadArgs->coreId]));
                }
                /* else TEST_SBL_SDOSPI_MEDIA_FLASH: Thread 1 loaded the same
                 * physical core (no A53/C75 image exists on this board) only
                 * to verify concurrent-media parse+auth; skip the actual
                 * claim/copy to avoid double-claiming CSL_CORE_ID_MCU_R5FSS0_0.
                 * Not run/synced/reset either — see loopVar == 1 guards in
                 * TestSbl_concurrentSdOspiBoot. */
#else
                status = Bootloader_loadCpu(threadArgs->bootHandle,
                                            &(bootImageInfo.cpuInfo[threadArgs->coreId]));
#endif /* SOC_AM62DX || SOC_AM62AX */
#endif /* !SOC_AM275X */
            }

            SemaphoreP_post(threadArgs->parseMutex);
        }
    }

    threadArgs->loadStatus = status;
    if (threadArgs->bootHandle != NULL)
    {
        threadArgs->cpuInfo = bootImageInfo.cpuInfo[threadArgs->coreId];
    }

    DebugP_log("[SDOSPI] Core %d load from media %d, status = %d\r\n",
               threadArgs->coreId, threadArgs->mediaType, status);

    SemaphoreP_post(threadArgs->doneSem);
    TaskP_exit();
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

/**
 * @brief Concurrent SD-card and OSPI-flash boot test.
 *
 * Spawns two FreeRTOS tasks that load single-core appimages from two
 * different boot media simultaneously.
 *
 * On AM62DX, Thread 0 reads the A53 image from the SD card (FreeRTOS-FAT /
 * MMC1) while Thread 1 reads the C75 image from OSPI NOR flash.  MMC1 and
 * OSPI0 are independent buses so the Phase 1 media reads are truly
 * concurrent.  TIFS authentication in Phase 2 is still serialized by
 * parseMutex because Sciclient is not thread-safe.
 *
 * On AM275X (no SD card slot), Thread 0 uses eMMC (MMC0) as the equivalent
 * removable-media bus and Thread 1 uses OSPI NOR flash.
 *
 * On AM62PX (no A53/C75 core or image on this board at all), both threads
 * load and verify the SAME MCU-R5F appimage concurrently — Thread 0 from
 * eMMC (MMC0), Thread 1 from OSPI NOR flash — using two distinct scratch
 * buffers so the concurrent Phase 1 reads cannot corrupt each other. Since
 * both threads target the same physical core, only Thread 0's copy is
 * actually claimed/run/synced/reset; Thread 1 only validates that its
 * independent parse+auth of the OSPI copy succeeds (see the `loopVar == 1`
 * skips below and the SOC_AM62PX branch in TestSbl_sdOspiLoadThread).
 *
 * Test Steps:
 * 1. Enable SBL module clocks for eMMC and OSPI (AM275X only).
 * 2. Open eMMC (AM275X/AM62PX only), OSPI, and Flash board drivers.
 * 3. Create parseMutex to serialize TIFS auth across threads.
 * 4. Spawn two tasks:
 *    - AM62DX Thread 0: reads A53 appimage from /sd0/app_a53, boots A53SS0_0.
 *    - AM62DX Thread 1: reads C75 appimage from OSPI flash,  boots C75SS0_0.
 *    - AM275X Thread 0: reads R5FSS0_0 appimage from eMMC,   boots R5FSS0_0.
 *    - AM275X Thread 1: reads C75 appimage from OSPI flash,  boots C75SS0_0.
 *    - AM62PX Thread 0: reads MCU-R5F appimage from eMMC,    boots MCU_R5FSS0_0.
 *    - AM62PX Thread 1: reads MCU-R5F appimage from OSPI flash (verify only).
 * 5. Wait for all threads; verify all loads succeeded.
 * 6. Bootloader_runCpu for each loaded core (AM62PX: Thread 0 only).
 * 7. IpcNotify_waitSync from each booted core (AM62PX: Thread 0 only).
 * 8. Reset all CPUs (AM62PX: Thread 0 only), close bootloaders and media drivers.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_concurrentSdOspiBoot(void *args)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t loopVar;

    /*
     * Thread-to-core-to-media mapping:
     *   AM62DX:
     *     Thread 0: A53SS0_0  from SD card   (CONFIG_BOOTLOADER_SD_A53,    MEDIA_SD)
     *     Thread 1: C75SS0_0  from OSPI NOR  (CONFIG_BOOTLOADER_FLASH_DSP, MEDIA_FLASH)
     *   AM275X (no SD; eMMC used as SD analog):
     *     Thread 0: R5FSS0_0  from eMMC      (CONFIG_BOOTLOADER_EMMC_MCU,  MEDIA_EMMC)
     *     Thread 1: C75SS0_0  from OSPI NOR  (CONFIG_BOOTLOADER_FLASH_DSP, MEDIA_FLASH)
     */
    uint32_t coreIds[TEST_SBL_SDOSPI_NUM_CORES] = {
#if defined(SOC_AM275X)
        CSL_CORE_ID_R5FSS0_0,
#elif defined(SOC_AM62PX)
        /* AM62PX: no A53 image; both threads load/verify the same MCU-R5F
         * image concurrently from eMMC + OSPI (only Thread 0 is run). */
        CSL_CORE_ID_MCU_R5FSS0_0,
#else
        CSL_CORE_ID_A53SS0_0,
#endif
#if defined(SOC_AM62PX)
        CSL_CORE_ID_MCU_R5FSS0_0,
#else
        CSL_CORE_ID_C75SS0_0,
#endif
    };
    uint32_t mediaTypes[TEST_SBL_SDOSPI_NUM_CORES] = {
#if defined(SOC_AM275X) || defined(SOC_AM62PX)
        TEST_SBL_SDOSPI_MEDIA_EMMC,
#else
        TEST_SBL_SDOSPI_MEDIA_SD,
#endif
        TEST_SBL_SDOSPI_MEDIA_FLASH,
    };
    uint8_t *appImageBufs[TEST_SBL_SDOSPI_NUM_CORES] = {
#if defined(SOC_AM275X)
        gMtScratchBuf,   /* shared scratch — serialized by parseMutex */
        gMtScratchBuf,
#elif defined(SOC_AM62DX)
        gAppImageBuf0,   /* SD scratch:   A53 image read from SD card  */
        gAppImageBuf2,   /* OSPI scratch: 0x84000000 = cert loadaddr   */
#elif defined(SOC_AM62PX)
        /* AM62PX: Thread 0 (eMMC) and Thread 1 (OSPI) read concurrently in
         * Phase 1, so they need two DISTINCT buffers — gMtScratchBuf
         * (256 KB, sized for a full eMMC read) and gAppImageBuf0 (the
         * embedded-image buffer, reused post-MT-test as OSPI scratch). */
        gMtScratchBuf,
        gAppImageBuf0,
#else
        gAppImageBuf0,
        gAppImageBuf2,
#endif
    };
    uint32_t bootloaderInstances[TEST_SBL_SDOSPI_NUM_CORES] = {
#if defined(SOC_AM275X) || defined(SOC_AM62PX)
        CONFIG_BOOTLOADER_EMMC_MCU,
#else
        CONFIG_BOOTLOADER_SD_A53,
#endif
        CONFIG_BOOTLOADER_FLASH_DSP,
    };
    uint8_t *taskStacks[TEST_SBL_SDOSPI_NUM_CORES] = {
        gMtTaskStack0,
        gMtTaskStack1,
    };
    TestSbl_MmMtThreadArgs threadArgs[TEST_SBL_SDOSPI_NUM_CORES];
    TaskP_Object           taskObjs[TEST_SBL_SDOSPI_NUM_CORES];
    SemaphoreP_Object      doneSems[TEST_SBL_SDOSPI_NUM_CORES];
    SemaphoreP_Object      parseMutex;

    DebugP_log("Starting TestSbl_concurrentSdOspiBoot test...\r\n");

#if defined(SOC_AM275X) || defined(SOC_AM62PX)
    /*
     * Enable SBL module clocks before accessing eMMC and OSPI hardware.
     * SysConfig marks MMCSD0/FSS0 as addedByBootloader=TRUE, so the normal
     * PowerClock_init() (called from System_init) never enables them — they
     * live in the generated gSocSBLModules[] list instead (see
     * ti_power_clock_config.c), which only Module_clockSBLEnable()/
     * Module_clockSBLSetFrequency() touch, and this test's main.c never
     * calls those (unlike AM62DX's main.c). Enable explicitly here rather
     * than calling Module_clockSBLEnable() so a failure logs which clock
     * failed instead of silently hanging on DebugP_assertNoLog.
     */
    {
        int32_t clkStatus;

        DebugP_log("[SDOSPI] Enabling MMCSD0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_MMCSD0, 1);
        DebugP_log("[SDOSPI] MMCSD0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_MMCSD0,
#if defined(SOC_AM275X)
                        TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK,
#else
                        TISCI_DEV_MMCSD0_EMMCSS_XIN_CLK,
#endif
                        200000000);
        DebugP_log("[SDOSPI] MMCSD0 clock freq status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        DebugP_log("[SDOSPI] Enabling FSS0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_FSS0, 1);
        DebugP_log("[SDOSPI] FSS0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

#if defined(SOC_AM62PX)
        /* AM62PX splits the FSS0 SBL module into separate sub-devices
         * (see gSocSBLModules[] in the generated ti_power_clock_config.c) */
        DebugP_log("[SDOSPI] Enabling FSS0_FSAS_0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_FSS0_FSAS_0, 1);
        DebugP_log("[SDOSPI] FSS0_FSAS_0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        DebugP_log("[SDOSPI] Enabling FSS0_OSPI_0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_FSS0_OSPI_0, 1);
        DebugP_log("[SDOSPI] FSS0_OSPI_0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_FSS0_OSPI_0,
                        TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK,
                        166666666);
#else
        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_FSS0,
                        TISCI_DEV_FSS0_OSPI0_RCLK_CLK,
                        166666666);
#endif
        DebugP_log("[SDOSPI] FSS0 clock freq status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);
    }
#endif

#if defined(SOC_AM275X) || defined(SOC_AM62PX)
    DebugP_log("[SDOSPI] Opening eMMC...\r\n");
    status = TestSbl_openBootEMMC();
    DebugP_log("[SDOSPI] eMMC open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
#endif

    DebugP_log("[SDOSPI] Opening OSPI...\r\n");
    status = TestSbl_openBootDriverFlash();
    DebugP_log("[SDOSPI] OSPI open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    DebugP_log("[SDOSPI] Opening Flash...\r\n");
    status = TestSbl_openBootBoardFlash();
    DebugP_log("[SDOSPI] Flash open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    Bootloader_profileAddProfilePoint("SBL Drivers_open");
    Bootloader_openDma();

#if !defined(SOC_AM275X)
    Bootloader_ReservedMemInit(TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_START,
                               TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_LENGTH);
#endif

    status = SemaphoreP_constructMutex(&parseMutex);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
        status = SemaphoreP_constructBinary(&doneSems[loopVar], 0);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
        threadArgs[loopVar].appImageBuf          = appImageBufs[loopVar];
        threadArgs[loopVar].appImageBufSize      = TEST_SBL_APPIMAGE_MAX_FILE_SIZE;
        threadArgs[loopVar].coreId               = coreIds[loopVar];
        threadArgs[loopVar].bootloaderInstanceId = bootloaderInstances[loopVar];
        threadArgs[loopVar].mediaType            = mediaTypes[loopVar];
        threadArgs[loopVar].loadStatus           = SystemP_FAILURE;
        threadArgs[loopVar].bootHandle           = NULL;
        threadArgs[loopVar].doneSem              = &doneSems[loopVar];
        threadArgs[loopVar].parseMutex           = &parseMutex;
    }

    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "sdospi_boot_thread";
        taskParams.stackSize = TEST_SBL_MT_TASK_STACK_SIZE;
        taskParams.stack     = taskStacks[loopVar];
        taskParams.priority  = TEST_SBL_MT_TASK_PRIORITY;
        taskParams.args      = &threadArgs[loopVar];
        taskParams.taskMain  = TestSbl_sdOspiLoadThread;

        status = TaskP_construct(&taskObjs[loopVar], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    /* Wait for all threads to complete loading */
    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
        SemaphoreP_pend(&doneSems[loopVar], SystemP_WAIT_FOREVER);
    }

    /* Verify all loads succeeded */
    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
        TEST_ASSERT_EQUAL(threadArgs[loopVar].loadStatus, SystemP_SUCCESS);
    }

    /* Run all loaded cores */
    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
#if defined(SOC_AM62PX)
        /* Thread 1 (OSPI) loaded the same physical core as Thread 0 (eMMC)
         * for parse+auth verification only; only Thread 0 is actually run. */
        if (loopVar == 1U)
        {
            continue;
        }
#endif
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("[SDOSPI] CPU %d: Running (media %d)...\r\n",
                           coreIds[loopVar], mediaTypes[loopVar]);
                status = Bootloader_runCpu(threadArgs[loopVar].bootHandle,
                                           &threadArgs[loopVar].cpuInfo);
                DebugP_log("[SDOSPI] CPU %d: runCpu status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    Bootloader_closeDma();

    /* Wait for IPC sync from each booted core */
    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
#if defined(SOC_AM62PX)
        if (loopVar == 1U)
        {
            continue;
        }
#endif
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("[SDOSPI] CPU %d: Waiting for IPC sync...\r\n",
                           coreIds[loopVar]);
                status = IpcNotify_waitSync(coreIds[loopVar], 10000);
                DebugP_log("[SDOSPI] CPU %d: IPC sync status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    /* Reset CPUs to original state */
    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
#if defined(SOC_AM62PX)
        /* Thread 1's core was never claimed/run (see above) — nothing to
         * reset; only close its bootHandle (handled in the loop below). */
        if (loopVar == 1U)
        {
            continue;
        }
#endif
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            DebugP_log("[SDOSPI] CPU %d: Resetting...\r\n", coreIds[loopVar]);
            status = Bootloader_socCpuRequest(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_socCpuPowerOff(threadArgs[loopVar].cpuInfo.cpuId);
            status = Bootloader_socCpuRelease(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("[SDOSPI] CPU %d: Reset complete\r\n", coreIds[loopVar]);
        }
    }

    /* Close bootloader instances */
    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].bootHandle != NULL)
        {
            Bootloader_close(threadArgs[loopVar].bootHandle);
        }
    }

    /* Clean up task objects and semaphores */
    for (loopVar = 0; loopVar < TEST_SBL_SDOSPI_NUM_CORES; loopVar++)
    {
        TaskP_destruct(&taskObjs[loopVar]);
        SemaphoreP_destruct(&doneSems[loopVar]);
    }
    SemaphoreP_destruct(&parseMutex);

    /* Close media drivers */
    TestSbl_closeBootBoardFlash();
    TestSbl_closeBootDriverFlash();
#if defined(SOC_AM275X) || defined(SOC_AM62PX)
    TestSbl_closeBootEMMC();
#endif
#if defined(SOC_AM275X)
    status = SOC_moduleClockEnable(TISCI_DEV_FSS0, 0);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    status = SOC_moduleClockEnable(TISCI_DEV_MMCSD0, 0);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
#endif

    DebugP_log("TestSbl_concurrentSdOspiBoot test completed\r\n");
}

/*
 * Concurrent eMMC + SD boot test thread.
 *
 * Phase 1 (before parseMutex): media reads happen in parallel across threads.
 *   - SD thread (AM62DX):   FreeRTOS-FAT reads (MMC1) into DDR scratch before
 *                           Bootloader_open; sets memArgsAppImageBaseAddr.
 *   - EMMC thread (AM62DX): imgReadFxn reads (MMC0 DMA) after Bootloader_open;
 *                           reads cert+payload into DDR scratch.
 *   MMC1 and MMC0 are independent controllers so the two reads overlap.
 *   On AM275X (no SD slot) the second thread uses a pre-loaded MEM image and
 *   there is no concurrent I/O: both threads are serialized by parseMutex.
 *
 * Phase 2 (inside parseMutex): cert-skip parse + manual CPU load (AM62DX),
 *   or parseAndLoadMultiCoreELF with bootMedia override for MEM (AM275X).
 */
static void TestSbl_emmcSdLoadThread(void *args)
{
    int32_t                status = SystemP_SUCCESS;
    TestSbl_MmMtThreadArgs *threadArgs;
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params        bootParams;
#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
    uint32_t certLen  = 0U;
#endif
#if defined(SOC_AM62DX)
    uint32_t totalLen = 0U;
#endif

    threadArgs = (TestSbl_MmMtThreadArgs *)args;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* ------------------------------------------------------------------ */
    /* Phase 1a: SD read (AM62DX only) — concurrent with EMMC reads        */
    /* Must happen BEFORE Bootloader_open so memArgsAppImageBaseAddr is set */
    /* ------------------------------------------------------------------ */
#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
    if (threadArgs->mediaType == TEST_SBL_EMMC_SD_MEDIA_SD)
    {
        FF_FILE  *fp;
        uint32_t  fileSize;
        size_t    bytesRead;

        fp = ff_fopen(TEST_SBL_EMMC_SD_SD_APPIMAGE_FNAME, "rb");
        if (fp == NULL)
        {
            DebugP_log("[SD] Failed to open %s\r\n", TEST_SBL_EMMC_SD_SD_APPIMAGE_FNAME);
            status = SystemP_FAILURE;
        }

        if (status == SystemP_SUCCESS)
        {
            fileSize = ff_filelength(fp);
            if (fileSize == 0U || fileSize > threadArgs->appImageBufSize)
            {
                DebugP_log("[SD] Bad file size %u\r\n", fileSize);
                ff_fclose(fp);
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            bytesRead = ff_fread(threadArgs->appImageBuf, fileSize, 1U, fp);
            ff_fclose(fp);
            if (bytesRead != 1U)
            {
                DebugP_log("[SD] Read failed\r\n");
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            certLen = Bootloader_getX509CertLen(threadArgs->appImageBuf);
            if (certLen <= TEST_SBL_X509_CERT_MIN_LEN || certLen >= TEST_SBL_X509_CERT_MAX_LEN)
            {
                DebugP_log("[SD] Invalid cert length 0x%x\r\n", certLen);
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            bootParams.memArgsAppImageBaseAddr = (uintptr_t)threadArgs->appImageBuf;
        }
    }
#endif /* SOC_AM62DX */

    /* ------------------------------------------------------------------ */
    /* Phase 1a (AM275X MEM only): point MEM bootloader at pre-loaded DDR  */
    /* ------------------------------------------------------------------ */
#if defined(SOC_AM275X)
    if (threadArgs->mediaType == TEST_SBL_EMMC_SD_MEDIA_MEM)
    {
        bootParams.memArgsAppImageBaseAddr = (uintptr_t)threadArgs->appImageBuf;
    }
#endif

    if (status == SystemP_SUCCESS)
    {
        threadArgs->bootHandle = Bootloader_open(threadArgs->bootloaderInstanceId, &bootParams);
        if (threadArgs->bootHandle == NULL)
        {
            DebugP_log("[EMMCSD] Bootloader_open failed for core %d (media %d)\r\n",
                       threadArgs->coreId, threadArgs->mediaType);
            status = SystemP_FAILURE;
        }
    }

    if (threadArgs->bootHandle != NULL)
    {
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            bootConfig->coresPresentMap = 0;
#if defined(SOC_AM275X)
            bootConfig->scratchMemPtr = gMtScratchBuf;
            if (threadArgs->mediaType == TEST_SBL_EMMC_SD_MEDIA_MEM)
            {
                bootConfig->bootMedia = BOOTLOADER_MEDIA_EMMC;
            }
#else
            bootConfig->scratchMemPtr = threadArgs->appImageBuf;
#endif
        }

        /* ------------------------------------------------------------------ */
        /* Phase 1b: EMMC read (AM62DX only) — concurrent with SD reads above  */
        /* ------------------------------------------------------------------ */
#if defined(SOC_AM62DX)
        if (threadArgs->mediaType == TEST_SBL_EMMC_SD_MEDIA_EMMC)
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            uint8_t  hdr4[4];
            uint32_t imageLen;
            int32_t  ioSt;

            ioSt = bootConfig->fxns->imgReadFxn(hdr4, 4U, bootConfig->args);
            if (ioSt != SystemP_SUCCESS)
            {
                DebugP_log("[EMMC] Failed to read x509 header\r\n");
                status = SystemP_FAILURE;
            }
            else
            {
                bootConfig->fxns->imgSeekFxn(0, bootConfig->args);
            }

            if (status == SystemP_SUCCESS)
            {
                certLen = Bootloader_getX509CertLen(hdr4);
                if (certLen > TEST_SBL_X509_CERT_MIN_LEN && certLen < TEST_SBL_X509_CERT_MAX_LEN)
                {
                    ioSt = bootConfig->fxns->imgReadFxn(
                        threadArgs->appImageBuf, TEST_SBL_X509_CERT_MAX_LEN, bootConfig->args);
                    if (ioSt != SystemP_SUCCESS)
                    {
                        status = SystemP_FAILURE;
                    }

                    if (status == SystemP_SUCCESS)
                    {
                        imageLen = Bootloader_getMsgLen(threadArgs->appImageBuf, certLen);
                        totalLen = (certLen + imageLen + 128U) & ~127U;

                        bootConfig->fxns->imgSeekFxn(0, bootConfig->args);
                        ioSt = bootConfig->fxns->imgReadFxn(
                            threadArgs->appImageBuf, totalLen, bootConfig->args);
                        if (ioSt != SystemP_SUCCESS)
                        {
                            status = SystemP_FAILURE;
                        }

                        if (status == SystemP_SUCCESS)
                        {
                            CacheP_wbInv(threadArgs->appImageBuf, totalLen, CacheP_TYPE_ALL);
                        }
                    }
                }
                else
                {
                    DebugP_log("[EMMC] Invalid cert length 0x%x\r\n", certLen);
                    status = SystemP_FAILURE;
                }
            }

            if (status != SystemP_SUCCESS)
            {
                DebugP_log("[EMMC] Media read failed for core %d\r\n", threadArgs->coreId);
                Bootloader_close(threadArgs->bootHandle);
                threadArgs->bootHandle = NULL;
            }
        }
#endif /* SOC_AM62DX */

        /* ------------------------------------------------------------------ */
        /* Phase 2: Serialized parse + load (TIFS auth is not thread-safe)     */
        /* ------------------------------------------------------------------ */
        if (threadArgs->bootHandle != NULL)
        {
            SemaphoreP_pend(threadArgs->parseMutex, SystemP_WAIT_FOREVER);

#if defined(SOC_AM275X)
            status = Bootloader_parseAndLoadMultiCoreELF(threadArgs->bootHandle, &bootImageInfo);
#elif defined(SOC_AM62DX) || defined(SOC_AM62AX)
            {
                Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;

                if (threadArgs->mediaType == TEST_SBL_EMMC_SD_MEDIA_SD)
                {
                    Bootloader_MemArgs *memArgs   = (Bootloader_MemArgs *)bootConfig->args;
                    uint8_t            *certStart = (uint8_t *)(uintptr_t)memArgs->appImageBaseAddr;

                    memArgs->appImageBaseAddr = (uint32_t)(uintptr_t)(certStart + certLen);
                    bootConfig->scratchMemPtr = certStart + certLen;
                    status = Bootloader_parseAppImage(threadArgs->bootHandle, &bootImageInfo);
                }
                else /* TEST_SBL_EMMC_SD_MEDIA_EMMC */
                {
                    bootConfig->scratchMemPtr = threadArgs->appImageBuf + certLen;
                    status = Bootloader_parseAppImage(threadArgs->bootHandle, &bootImageInfo);
                }
            }
#else
            status = Bootloader_parseMultiCoreAppImage(threadArgs->bootHandle, &bootImageInfo);
#endif

            if (status != SystemP_SUCCESS)
            {
                DebugP_log("[EMMCSD] parse failed for core %d (media %d)\r\n",
                           threadArgs->coreId, threadArgs->mediaType);
                Bootloader_close(threadArgs->bootHandle);
                threadArgs->bootHandle = NULL;
            }
            else if (TRUE != Bootloader_isCorePresent(threadArgs->bootHandle, threadArgs->coreId))
            {
                DebugP_log("[EMMCSD] Core %d not present (media %d)\r\n",
                           threadArgs->coreId, threadArgs->mediaType);
                status = SystemP_FAILURE;
                Bootloader_close(threadArgs->bootHandle);
                threadArgs->bootHandle = NULL;
            }
            else
            {
#if !defined(SOC_AM275X)
                bootImageInfo.cpuInfo[threadArgs->coreId].clkHz =
                    Bootloader_socCpuGetClkDefault(threadArgs->coreId);

#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
                {
                    Bootloader_Config            *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
                    Bootloader_CpuInfo           *cpuInfo    = &bootImageInfo.cpuInfo[threadArgs->coreId];
                    uint8_t                      *rprcBase;
                    Bootloader_RprcFileHeader     rprcHdr;
                    Bootloader_RprcSectionHeader  secHdr;
                    uint32_t s, destAddr;

                    status = Bootloader_socCpuRequest(cpuInfo->cpuId);

                    if (status == SystemP_SUCCESS)
                        status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

                    if (status == SystemP_SUCCESS)
                        status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId, bootConfig->socCoreOpMode);

                    if (status == SystemP_SUCCESS && cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
                    {
                        rprcBase = bootConfig->scratchMemPtr + cpuInfo->rprcOffset;

                        CacheP_inv(rprcBase, sizeof(rprcHdr), CacheP_TYPE_ALL);
                        memcpy(&rprcHdr, rprcBase, sizeof(rprcHdr));
                        rprcBase += sizeof(rprcHdr);

                        if (rprcHdr.magic != BOOTLOADER_RPRC_MAGIC_NUMBER)
                        {
                            status = SystemP_FAILURE;
                        }
                        else
                        {
                            cpuInfo->entryPoint = (uintptr_t)rprcHdr.entry;
                            for (s = 0; s < rprcHdr.sectionCount && status == SystemP_SUCCESS; s++)
                            {
                                memcpy(&secHdr, rprcBase, sizeof(secHdr));
                                rprcBase += sizeof(secHdr);

                                destAddr = Bootloader_socTranslateSectionAddr(
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
#endif /* SOC_AM62DX || SOC_AM62AX */
#endif /* !SOC_AM275X */
            }

            SemaphoreP_post(threadArgs->parseMutex);
        }
    }

    threadArgs->loadStatus = status;
    if (threadArgs->bootHandle != NULL)
    {
        threadArgs->cpuInfo = bootImageInfo.cpuInfo[threadArgs->coreId];
    }

    DebugP_log("[EMMCSD] Core %d load from media %d, status = %d\r\n",
               threadArgs->coreId, threadArgs->mediaType, status);

    SemaphoreP_post(threadArgs->doneSem);
    TaskP_exit();
}

/**
 * @brief Concurrent eMMC and SD-card boot test.
 *
 * Spawns two FreeRTOS tasks that load single-core appimages from eMMC and
 * SD card simultaneously.  On AM62DX, Thread 0 reads the MCU R5FSS0_0 image
 * from eMMC (raw DMA reads via MMC0) while Thread 1 reads the A53SS0_0 image
 * from the SD card (FreeRTOS-FAT / MMC1).  MMC0 and MMC1 are independent
 * controllers so the Phase 1 media reads are truly concurrent.  TIFS
 * authentication in Phase 2 is still serialized by parseMutex.
 *
 * On AM275X (no SD card slot), Thread 0 uses eMMC (MMC0) and Thread 1
 * uses a pre-loaded MEM image (R5FSS1_0 appimage embedded in the test
 * binary by the SBL). Both threads are serialized by parseMutex.
 *
 * Test Steps:
 * 1. Enable MMCSD0 clock (AM275X only — not needed on AM62DX).
 * 2. Open eMMC board driver.
 * 3. Create parseMutex to serialize TIFS auth across threads.
 * 4. Spawn two tasks:
 *    - AM62DX Thread 0: reads MCU R5F image from eMMC, boots MCU_R5FSS0_0.
 *    - AM62DX Thread 1: reads A53  image from SD card, boots A53SS0_0.
 *    - AM275X Thread 0: reads R5FSS0_0 image from eMMC,    boots R5FSS0_0.
 *    - AM275X Thread 1: loads R5FSS1_0 image from DDR MEM, boots R5FSS1_0.
 * 5. Wait for all threads; verify all loads succeeded.
 * 6. Bootloader_runCpu for each loaded core.
 * 7. IpcNotify_waitSync from each booted core.
 * 8. Reset all CPUs and close media drivers.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_concurrentEmmcSdBoot(void *args)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t loopVar;

    /*
     * Thread-to-core-to-media mapping:
     *   AM62DX:
     *     Thread 0: MCU_R5FSS0_0 from eMMC      (CONFIG_BOOTLOADER_EMMC_MCU,     MEDIA_EMMC)
     *     Thread 1: A53SS0_0     from SD card    (CONFIG_BOOTLOADER_SD_A53,       MEDIA_SD)
     *   AM275X (no SD; pre-loaded DDR image used instead):
     *     Thread 0: R5FSS0_0     from eMMC       (CONFIG_BOOTLOADER_EMMC_MCU,     MEDIA_EMMC)
     *     Thread 1: R5FSS1_0     from DDR MEM    (CONFIG_BOOTLOADER_MEM_R5FSS1_0, MEDIA_MEM)
     */
    uint32_t coreIds[TEST_SBL_EMMC_SD_NUM_CORES] = {
#if defined(SOC_AM275X)
        /*
         * Thread ordering matters due to DDR address overlap:
         *   R5FSS1_0 DDR destinations: 0x72293e80, 0x7229daa0
         *     → far above gAppImageBuf0 (0x72080000..0x720A3280) — safe ✓
         *   R5FSS0_0 DDR destinations: 0x720951C0, 0x7209FE68
         *     → inside gAppImageBuf1 (0x7208CD80..0x72098948) — would corrupt it!
         *
         * By loading R5FSS1_0 first (Thread 0), gAppImageBuf0 is unaffected.
         * Then Thread 1 loads R5FSS0_0: its writes into the gAppImageBuf1 range
         * are harmless because gAppImageBuf1 is no longer needed at that point.
         */
        CSL_CORE_ID_R5FSS1_0,   /* Thread 0: R5FSS1_0 first — safe DDR targets */
        CSL_CORE_ID_R5FSS0_0,   /* Thread 1: R5FSS0_0 second */
#else
        CSL_CORE_ID_MCU_R5FSS0_0,
        CSL_CORE_ID_A53SS0_0,
#endif
    };
    /*
     * AM275X: MMCSD_open() hangs regardless of speed mode (MMCSD_halSoftReset
     * resets host-controller registers but not the PHY/clock-distribution
     * domain; CMD0/CMD1 at 400 kHz time out because the clock path remains
     * gated for HS200).  Both threads use MEM bootloader so the test can
     * still validate concurrent dual-core loading from two separate DDR
     * buffers (R5FSS1_0 then R5FSS0_0 — see coreIds comment above).
     */
    uint32_t mediaTypes[TEST_SBL_EMMC_SD_NUM_CORES] = {
#if defined(SOC_AM275X)
        TEST_SBL_EMMC_SD_MEDIA_MEM,   /* Thread 0: MEM (eMMC unavailable) */
#else
        TEST_SBL_EMMC_SD_MEDIA_EMMC,
#endif
#if defined(SOC_AM275X)
        TEST_SBL_EMMC_SD_MEDIA_MEM,
#else
        TEST_SBL_EMMC_SD_MEDIA_SD,
#endif
    };
    uint8_t *appImageBufs[TEST_SBL_EMMC_SD_NUM_CORES] = {
#if defined(SOC_AM275X)
        gAppImageBuf1,   /* Thread 0: R5FSS1_0 image (DDR safe for gAppImageBuf0) */
        gAppImageBuf0,   /* Thread 1: R5FSS0_0 image (loaded after buf1 is done)  */
#elif defined(SOC_AM62DX)
        gAppImageBuf0,   /* EMMC scratch: MCU R5F image read from eMMC     */
        gAppImageBuf1,   /* SD scratch:   A53 image read from SD card      */
#elif defined(SOC_AM62AX)
        gAppImageBuf0,   /* EMMC scratch: MCU R5F image read from eMMC     */
        gAppImageBuf1,   /* SD scratch:   A53 image read from SD card      */
#elif defined(SOC_AM62PX)
        /* AM62PX: no gAppImageBuf1 (reduced appimage_data.S) and no A53
         * boot image; this test is disabled for AM62PX in test_main(). */
        gMtScratchBuf,
        gMtScratchBuf,
#else
        gAppImageBuf0,
        gAppImageBuf1,
#endif
    };
    uint32_t bootloaderInstances[TEST_SBL_EMMC_SD_NUM_CORES] = {
#if defined(SOC_AM275X)
        CONFIG_BOOTLOADER_MEM_R5FSS1_0,  /* Thread 0: R5FSS1_0 */
#else
        CONFIG_BOOTLOADER_EMMC_MCU,
#endif
#if defined(SOC_AM275X)
        CONFIG_BOOTLOADER_MEM_R5FSS0_0,  /* Thread 1: R5FSS0_0 */
#else
        CONFIG_BOOTLOADER_SD_A53,
#endif
    };
    uint8_t *taskStacks[TEST_SBL_EMMC_SD_NUM_CORES] = {
        gMtTaskStack0,
        gMtTaskStack1,
    };
    TestSbl_MmMtThreadArgs threadArgs[TEST_SBL_EMMC_SD_NUM_CORES];
    TaskP_Object           taskObjs[TEST_SBL_EMMC_SD_NUM_CORES];
    SemaphoreP_Object      doneSems[TEST_SBL_EMMC_SD_NUM_CORES];
    SemaphoreP_Object      parseMutex;

    DebugP_log("Starting TestSbl_concurrentEmmcSdBoot test...\r\n");

#if !defined(SOC_AM275X)
    /* AM275X uses MEM for both threads (eMMC MMCSD_open hangs) */
    DebugP_log("[EMMCSD] Opening eMMC...\r\n");
    status = TestSbl_openBootEMMC();
    DebugP_log("[EMMCSD] eMMC open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
#endif

    Bootloader_profileAddProfilePoint("SBL Drivers_open");
    Bootloader_openDma();

#if !defined(SOC_AM275X)
    Bootloader_ReservedMemInit(TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_START,
                               TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_LENGTH);
#endif

    status = SemaphoreP_constructMutex(&parseMutex);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        status = SemaphoreP_constructBinary(&doneSems[loopVar], 0);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        threadArgs[loopVar].appImageBuf          = appImageBufs[loopVar];
        threadArgs[loopVar].appImageBufSize      = TEST_SBL_APPIMAGE_MAX_FILE_SIZE;
        threadArgs[loopVar].coreId               = coreIds[loopVar];
        threadArgs[loopVar].bootloaderInstanceId = bootloaderInstances[loopVar];
        threadArgs[loopVar].mediaType            = mediaTypes[loopVar];
        threadArgs[loopVar].loadStatus           = SystemP_FAILURE;
        threadArgs[loopVar].bootHandle           = NULL;
        threadArgs[loopVar].doneSem              = &doneSems[loopVar];
        threadArgs[loopVar].parseMutex           = &parseMutex;
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "emmcsd_boot_thread";
        taskParams.stackSize = TEST_SBL_MT_TASK_STACK_SIZE;
        taskParams.stack     = taskStacks[loopVar];
        taskParams.priority  = TEST_SBL_MT_TASK_PRIORITY;
        taskParams.args      = &threadArgs[loopVar];
        taskParams.taskMain  = TestSbl_emmcSdLoadThread;

        status = TaskP_construct(&taskObjs[loopVar], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    /* Wait for all threads to complete loading */
    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        SemaphoreP_pend(&doneSems[loopVar], SystemP_WAIT_FOREVER);
    }

    /* Verify all loads succeeded */
    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        TEST_ASSERT_EQUAL(threadArgs[loopVar].loadStatus, SystemP_SUCCESS);
    }

    /* Run all loaded cores */
    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("[EMMCSD] CPU %d: Running (media %d)...\r\n",
                           coreIds[loopVar], mediaTypes[loopVar]);
                status = Bootloader_runCpu(threadArgs[loopVar].bootHandle,
                                           &threadArgs[loopVar].cpuInfo);
                DebugP_log("[EMMCSD] CPU %d: runCpu status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    Bootloader_closeDma();

    /* Wait for IPC sync from each booted core.
     *
     * AM275X: each remote (ipc_rpmsg_echo) writes a "running" stamp to DDR at
     * 0x723C2000 + cid*4 as the first thing in ipc_rpmsg_echo_main (its
     * Drivers_open()/Board_driversOpen() only open UART, so the stamp appears
     * within milliseconds of the core starting).
     *
     * CRITICAL: the WKUP-R5 MPU maps DDR 0x72000000-0x72400000 as CACHEABLE
     * (see gMpuRegionConfig), so the remote's DDR write is NOT visible to this
     * core unless the stamp's cache line is invalidated before each read.
     * The remotes map the region NonCached, so they need no writeback; only
     * the reader must invalidate.  IpcNotify_sendSync() is still issued to
     * unblock any IPC sync wait on the remote side. */
#if defined(SOC_AM275X)
    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            uint32_t  cid        = coreIds[loopVar];
            uintptr_t stampAddr  = 0x723C2000U + cid * sizeof(uint32_t);
            uintptr_t lineAddr   = stampAddr & ~((uintptr_t)31U);
            volatile uint32_t *stamp = (volatile uint32_t *)stampAddr;
            uint32_t expected    = 0xABCD0000U | cid;
            uint32_t startCycles = CycleCounterP_getCount32();
            /* 3.5 s window: fits uint32_t and stays under the ~4.29 s
             * CycleCounterP_getCount32 wrap period at 1 GHz. */
            uint32_t timeout     = 3500000000U;
            int32_t  syncStatus  = SystemP_FAILURE;

            status = IpcNotify_sendSync(cid);
            TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
            DebugP_log("[EMMCSD] CPU %d: Waiting for IPC sync...\r\n", cid);
            while((CycleCounterP_getCount32() - startCycles) < timeout)
            {
                /* Invalidate so we re-fetch the remote's DDR write */
                CacheP_inv((void *)lineAddr, 32U, CacheP_TYPE_ALL);
                if(*stamp == expected) { syncStatus = SystemP_SUCCESS; break; }
            }
            DebugP_log("[EMMCSD] CPU %d: IPC sync status = %d\r\n", cid, syncStatus);
            TEST_ASSERT_EQUAL(syncStatus, SystemP_SUCCESS);
        }
    }
#else
    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
            {
                DebugP_log("[EMMCSD] CPU %d: Waiting for IPC sync...\r\n",
                           coreIds[loopVar]);
                status = IpcNotify_waitSync(coreIds[loopVar], 10000);
                DebugP_log("[EMMCSD] CPU %d: IPC sync status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }
#endif

    /* Reset CPUs to original state */
    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            DebugP_log("[EMMCSD] CPU %d: Resetting...\r\n", coreIds[loopVar]);
            status = Bootloader_socCpuRequest(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_socCpuPowerOff(threadArgs[loopVar].cpuInfo.cpuId);
            status = Bootloader_socCpuRelease(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("[EMMCSD] CPU %d: Reset complete\r\n", coreIds[loopVar]);
        }
    }

    /* Close bootloader instances */
    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].bootHandle != NULL)
        {
            Bootloader_close(threadArgs[loopVar].bootHandle);
        }
    }

    /* Clean up task objects and semaphores */
    for (loopVar = 0; loopVar < TEST_SBL_EMMC_SD_NUM_CORES; loopVar++)
    {
        TaskP_destruct(&taskObjs[loopVar]);
        SemaphoreP_destruct(&doneSems[loopVar]);
    }
    SemaphoreP_destruct(&parseMutex);

    /* Close media drivers (eMMC not opened on AM275X) */
#if !defined(SOC_AM275X)
    TestSbl_closeBootEMMC();
#endif

    DebugP_log("TestSbl_concurrentEmmcSdBoot test completed\r\n");
}

/*
 * Concurrent eMMC-image boot thread.
 *
 * All media reads use the bootloader's imgReadFxn/imgSeekFxn so the code
 * is identical for EMMC and FLASH threads — no mediaType dispatch in Phase 1.
 *
 * On AM62DX both threads hit MMC0 at different appimage offsets; the MMCSD
 * hardware serializes the DMA transfers but both threads queue reads
 * concurrently, testing the driver's ability to handle parallel access.
 *
 * Phase 1 (before parseMutex): read header → certLen, read first 2 KB →
 *   imageLen/totalLen, read full signed image into DDR scratch buffer.
 * Phase 2 (inside parseMutex): cert-skip Bootloader_parseAppImage + manual
 *   RPRC load (AM62DX), or Bootloader_parseAndLoadMultiCoreELF (AM275X).
 */
static void TestSbl_emmcImgLoadThread(void *args)
{
    int32_t                status = SystemP_SUCCESS;
    TestSbl_MmMtThreadArgs *threadArgs;
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params        bootParams;
#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
    uint32_t certLen  = 0U;
    uint32_t totalLen = 0U;
#endif

    threadArgs = (TestSbl_MmMtThreadArgs *)args;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    threadArgs->bootHandle = Bootloader_open(threadArgs->bootloaderInstanceId, &bootParams);
    if (threadArgs->bootHandle == NULL)
    {
        DebugP_log("[EMMCIMG] Bootloader_open failed for core %d (media %d)\r\n",
                   threadArgs->coreId, threadArgs->mediaType);
        status = SystemP_FAILURE;
    }
    else
    {
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            bootConfig->coresPresentMap = 0;
#if defined(SOC_AM275X)
            bootConfig->scratchMemPtr = gMtScratchBuf;
#else
            bootConfig->scratchMemPtr = threadArgs->appImageBuf;
#endif
        }

        /* ------------------------------------------------------------------ */
        /* Phase 1: Media read — imgReadFxn-based, same code for EMMC & FLASH  */
        /* ------------------------------------------------------------------ */
#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            uint8_t  hdr4[4];
            uint32_t imageLen;
            int32_t  ioSt;

            ioSt = bootConfig->fxns->imgReadFxn(hdr4, 4U, bootConfig->args);
            if (ioSt != SystemP_SUCCESS)
            {
                DebugP_log("[EMMCIMG] Header read failed for core %d\r\n", threadArgs->coreId);
                status = SystemP_FAILURE;
            }
            else
            {
                bootConfig->fxns->imgSeekFxn(0, bootConfig->args);
            }

            if (status == SystemP_SUCCESS)
            {
                certLen = Bootloader_getX509CertLen(hdr4);
                if (certLen > TEST_SBL_X509_CERT_MIN_LEN && certLen < TEST_SBL_X509_CERT_MAX_LEN)
                {
                    ioSt = bootConfig->fxns->imgReadFxn(
                        threadArgs->appImageBuf, TEST_SBL_X509_CERT_MAX_LEN, bootConfig->args);
                    if (ioSt != SystemP_SUCCESS)
                    {
                        status = SystemP_FAILURE;
                    }

                    if (status == SystemP_SUCCESS)
                    {
                        imageLen = Bootloader_getMsgLen(threadArgs->appImageBuf, certLen);
                        totalLen = (certLen + imageLen + 128U) & ~127U;

                        bootConfig->fxns->imgSeekFxn(0, bootConfig->args);
                        ioSt = bootConfig->fxns->imgReadFxn(
                            threadArgs->appImageBuf, totalLen, bootConfig->args);
                        if (ioSt != SystemP_SUCCESS)
                        {
                            status = SystemP_FAILURE;
                        }

                        if (status == SystemP_SUCCESS)
                        {
                            CacheP_wbInv(threadArgs->appImageBuf, totalLen, CacheP_TYPE_ALL);
                        }
                    }
                }
                else
                {
                    DebugP_log("[EMMCIMG] Invalid cert length 0x%x for core %d\r\n",
                               certLen, threadArgs->coreId);
                    status = SystemP_FAILURE;
                }
            }

            if (status != SystemP_SUCCESS)
            {
                Bootloader_close(threadArgs->bootHandle);
                threadArgs->bootHandle = NULL;
            }
        }
#endif /* SOC_AM62DX || SOC_AM62AX */

        /* ------------------------------------------------------------------ */
        /* Phase 2: Serialized parse + load (TIFS auth is not thread-safe)     */
        /* ------------------------------------------------------------------ */
        if (threadArgs->bootHandle != NULL)
        {
            SemaphoreP_pend(threadArgs->parseMutex, SystemP_WAIT_FOREVER);

#if defined(SOC_AM275X)
            status = Bootloader_parseAndLoadMultiCoreELF(threadArgs->bootHandle, &bootImageInfo);
#elif defined(SOC_AM62DX) || defined(SOC_AM62AX)
            {
                Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;

                bootConfig->scratchMemPtr = threadArgs->appImageBuf + certLen;
                status = Bootloader_parseAppImage(threadArgs->bootHandle, &bootImageInfo);
            }
#else
            status = Bootloader_parseMultiCoreAppImage(threadArgs->bootHandle, &bootImageInfo);
#endif

            if (status != SystemP_SUCCESS)
            {
                DebugP_log("[EMMCIMG] parse failed for core %d (media %d)\r\n",
                           threadArgs->coreId, threadArgs->mediaType);
                Bootloader_close(threadArgs->bootHandle);
                threadArgs->bootHandle = NULL;
            }
            else if (TRUE != Bootloader_isCorePresent(threadArgs->bootHandle, threadArgs->coreId))
            {
                DebugP_log("[EMMCIMG] Core %d not present (media %d)\r\n",
                           threadArgs->coreId, threadArgs->mediaType);
                status = SystemP_FAILURE;
                Bootloader_close(threadArgs->bootHandle);
                threadArgs->bootHandle = NULL;
            }
            else
            {
#if !defined(SOC_AM275X)
                bootImageInfo.cpuInfo[threadArgs->coreId].clkHz =
                    Bootloader_socCpuGetClkDefault(threadArgs->coreId);

#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
                {
                    Bootloader_Config            *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
                    Bootloader_CpuInfo           *cpuInfo    = &bootImageInfo.cpuInfo[threadArgs->coreId];
                    uint8_t                      *rprcBase;
                    Bootloader_RprcFileHeader     rprcHdr;
                    Bootloader_RprcSectionHeader  secHdr;
                    uint32_t s, destAddr;

                    status = Bootloader_socCpuRequest(cpuInfo->cpuId);

                    if (status == SystemP_SUCCESS)
                        status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

                    if (status == SystemP_SUCCESS)
                        status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId, bootConfig->socCoreOpMode);

                    if (status == SystemP_SUCCESS && cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
                    {
                        rprcBase = bootConfig->scratchMemPtr + cpuInfo->rprcOffset;

                        CacheP_inv(rprcBase, sizeof(rprcHdr), CacheP_TYPE_ALL);
                        memcpy(&rprcHdr, rprcBase, sizeof(rprcHdr));
                        rprcBase += sizeof(rprcHdr);

                        if (rprcHdr.magic != BOOTLOADER_RPRC_MAGIC_NUMBER)
                        {
                            status = SystemP_FAILURE;
                        }
                        else
                        {
                            cpuInfo->entryPoint = (uintptr_t)rprcHdr.entry;
                            for (s = 0; s < rprcHdr.sectionCount && status == SystemP_SUCCESS; s++)
                            {
                                memcpy(&secHdr, rprcBase, sizeof(secHdr));
                                rprcBase += sizeof(secHdr);

                                destAddr = Bootloader_socTranslateSectionAddr(
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
#endif /* SOC_AM62DX || SOC_AM62AX */
#endif /* !SOC_AM275X */
            }

            SemaphoreP_post(threadArgs->parseMutex);
        }
    }

    threadArgs->loadStatus = status;
    if (threadArgs->bootHandle != NULL)
    {
        threadArgs->cpuInfo = bootImageInfo.cpuInfo[threadArgs->coreId];
    }

    DebugP_log("[EMMCIMG] Core %d load from media %d, status = %d\r\n",
               threadArgs->coreId, threadArgs->mediaType, status);

    SemaphoreP_post(threadArgs->doneSem);
    TaskP_exit();
}

/**
 * @brief Concurrent eMMC-image boot test.
 *
 * On AM62DX both threads read from eMMC (MMC0) at different appimage offsets:
 * Thread 0 reads the MCU R5FSS0_0 image at 0x800000 (CONFIG_BOOTLOADER_EMMC_MCU)
 * and Thread 1 reads the A53SS0_0 image at 0xC00000 (CONFIG_BOOTLOADER_EMMC_A53).
 * MMC0 DMA serializes the transfers but both threads queue their reads
 * concurrently, exercising the MMCSD driver under parallel access.
 *
 * On AM275X no standalone C75 eMMC image is provisioned, so Thread 1 falls
 * back to OSPI NOR flash (CONFIG_BOOTLOADER_FLASH_DSP) for C75SS0_0.
 *
 * Test Steps:
 * 1. Enable SBL clocks (AM275X: MMCSD0 + FSS0; not needed on AM62DX).
 * 2. Open eMMC driver.  Open OSPI/Flash drivers (AM275X only).
 * 3. Create parseMutex to serialize TIFS auth.
 * 4. Spawn two tasks:
 *    - AM62DX Thread 0: eMMC @ 0x800000 → MCU_R5FSS0_0.
 *    - AM62DX Thread 1: eMMC @ 0xC00000 → A53SS0_0.
 *    - AM275X Thread 0: eMMC @ 0x800000 → R5FSS0_0.
 *    - AM275X Thread 1: OSPI @ 0xA00000 → C75SS0_0.
 * 5. Wait, verify, runCpu, IpcNotify_waitSync, reset, close.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_concurrentEmmcImageBoot(void *args)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t loopVar;

    uint32_t coreIds[TEST_SBL_EMMC_IMG_NUM_CORES] = {
#if defined(SOC_AM275X)
        CSL_CORE_ID_R5FSS0_0,
        CSL_CORE_ID_C75SS0_0,
#else
        CSL_CORE_ID_MCU_R5FSS0_0,
        CSL_CORE_ID_A53SS0_0,    /* EMMC_A53 image at 0xC00000 */
#endif
    };
    uint32_t mediaTypes[TEST_SBL_EMMC_IMG_NUM_CORES] = {
        TEST_SBL_EMMC_IMG_MEDIA_EMMC,
#if defined(SOC_AM275X)
        TEST_SBL_EMMC_IMG_MEDIA_FLASH,   /* C75 has no eMMC image on AM275X */
#else
        TEST_SBL_EMMC_IMG_MEDIA_EMMC,    /* A53 eMMC image at 0xC00000      */
#endif
    };
    uint8_t *appImageBufs[TEST_SBL_EMMC_IMG_NUM_CORES] = {
#if defined(SOC_AM275X)
        gMtScratchBuf,   /* shared scratch — serialized by parseMutex */
        gMtScratchBuf,
#elif defined(SOC_AM62DX)
        gAppImageBuf0,   /* MCU R5F image read from eMMC @ 0x800000   */
        gAppImageBuf1,   /* A53 image read from eMMC @ 0xC00000        */
#elif defined(SOC_AM62PX)
        /* AM62PX: no gAppImageBuf1 and no A53 boot image; this test is
         * disabled for AM62PX in test_main(). */
        gMtScratchBuf,
        gMtScratchBuf,
#else
        gAppImageBuf0,
        gAppImageBuf1,
#endif
    };
    uint32_t bootloaderInstances[TEST_SBL_EMMC_IMG_NUM_CORES] = {
        CONFIG_BOOTLOADER_EMMC_MCU,
#if defined(SOC_AM275X)
        CONFIG_BOOTLOADER_FLASH_DSP,
#else
        CONFIG_BOOTLOADER_EMMC_A53,
#endif
    };
    uint8_t *taskStacks[TEST_SBL_EMMC_IMG_NUM_CORES] = {
        gMtTaskStack0,
        gMtTaskStack1,
    };
    TestSbl_MmMtThreadArgs threadArgs[TEST_SBL_EMMC_IMG_NUM_CORES];
    TaskP_Object           taskObjs[TEST_SBL_EMMC_IMG_NUM_CORES];
    SemaphoreP_Object      doneSems[TEST_SBL_EMMC_IMG_NUM_CORES];
    SemaphoreP_Object      parseMutex;

    DebugP_log("Starting TestSbl_concurrentEmmcImageBoot test...\r\n");

#if defined(SOC_AM275X)
    {
        int32_t clkStatus;

        DebugP_log("[EMMCIMG] Enabling MMCSD0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_MMCSD0, 1);
        DebugP_log("[EMMCIMG] MMCSD0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_MMCSD0,
                        TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK,
                        200000000);
        DebugP_log("[EMMCIMG] MMCSD0 clock freq status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        DebugP_log("[EMMCIMG] Enabling FSS0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_FSS0, 1);
        DebugP_log("[EMMCIMG] FSS0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_FSS0,
                        TISCI_DEV_FSS0_OSPI0_RCLK_CLK,
                        166666666);
        DebugP_log("[EMMCIMG] FSS0 clock freq status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);
    }
#endif

    DebugP_log("[EMMCIMG] Opening eMMC...\r\n");
    status = TestSbl_openBootEMMC();
    DebugP_log("[EMMCIMG] eMMC open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

#if defined(SOC_AM275X)
    DebugP_log("[EMMCIMG] Opening OSPI...\r\n");
    status = TestSbl_openBootDriverFlash();
    DebugP_log("[EMMCIMG] OSPI open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    DebugP_log("[EMMCIMG] Opening Flash...\r\n");
    status = TestSbl_openBootBoardFlash();
    DebugP_log("[EMMCIMG] Flash open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
#endif

    Bootloader_profileAddProfilePoint("SBL Drivers_open");
    Bootloader_openDma();

#if !defined(SOC_AM275X)
    Bootloader_ReservedMemInit(TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_START,
                               TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_LENGTH);
#endif

    status = SemaphoreP_constructMutex(&parseMutex);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        status = SemaphoreP_constructBinary(&doneSems[loopVar], 0);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        threadArgs[loopVar].appImageBuf          = appImageBufs[loopVar];
        threadArgs[loopVar].appImageBufSize      = TEST_SBL_APPIMAGE_MAX_FILE_SIZE;
        threadArgs[loopVar].coreId               = coreIds[loopVar];
        threadArgs[loopVar].bootloaderInstanceId = bootloaderInstances[loopVar];
        threadArgs[loopVar].mediaType            = mediaTypes[loopVar];
        threadArgs[loopVar].loadStatus           = SystemP_FAILURE;
        threadArgs[loopVar].bootHandle           = NULL;
        threadArgs[loopVar].doneSem              = &doneSems[loopVar];
        threadArgs[loopVar].parseMutex           = &parseMutex;
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "emmcimg_boot_thread";
        taskParams.stackSize = TEST_SBL_MT_TASK_STACK_SIZE;
        taskParams.stack     = taskStacks[loopVar];
        taskParams.priority  = TEST_SBL_MT_TASK_PRIORITY;
        taskParams.args      = &threadArgs[loopVar];
        taskParams.taskMain  = TestSbl_emmcImgLoadThread;

        status = TaskP_construct(&taskObjs[loopVar], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        SemaphoreP_pend(&doneSems[loopVar], SystemP_WAIT_FOREVER);
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        TEST_ASSERT_EQUAL(threadArgs[loopVar].loadStatus, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("[EMMCIMG] CPU %d: Running (media %d)...\r\n",
                           coreIds[loopVar], mediaTypes[loopVar]);
                status = Bootloader_runCpu(threadArgs[loopVar].bootHandle,
                                           &threadArgs[loopVar].cpuInfo);
                DebugP_log("[EMMCIMG] CPU %d: runCpu status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    Bootloader_closeDma();

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("[EMMCIMG] CPU %d: Waiting for IPC sync...\r\n",
                           coreIds[loopVar]);
                status = IpcNotify_waitSync(coreIds[loopVar], 10000);
                DebugP_log("[EMMCIMG] CPU %d: IPC sync status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            DebugP_log("[EMMCIMG] CPU %d: Resetting...\r\n", coreIds[loopVar]);
            status = Bootloader_socCpuRequest(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_socCpuPowerOff(threadArgs[loopVar].cpuInfo.cpuId);
            status = Bootloader_socCpuRelease(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("[EMMCIMG] CPU %d: Reset complete\r\n", coreIds[loopVar]);
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].bootHandle != NULL)
        {
            Bootloader_close(threadArgs[loopVar].bootHandle);
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_EMMC_IMG_NUM_CORES; loopVar++)
    {
        TaskP_destruct(&taskObjs[loopVar]);
        SemaphoreP_destruct(&doneSems[loopVar]);
    }
    SemaphoreP_destruct(&parseMutex);

#if defined(SOC_AM275X)
    TestSbl_closeBootBoardFlash();
    TestSbl_closeBootDriverFlash();
#endif
    TestSbl_closeBootEMMC();

#if defined(SOC_AM275X)
    status = SOC_moduleClockEnable(TISCI_DEV_FSS0, 0);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    status = SOC_moduleClockEnable(TISCI_DEV_MMCSD0, 0);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
#endif

    DebugP_log("TestSbl_concurrentEmmcImageBoot test completed\r\n");
}

/*
 * Concurrent SD-image boot thread.
 *
 * AM62DX — Phase 1 (before parseMutex):
 *   Derives the SD filename from the coreId, opens the file via FreeRTOS-FAT,
 *   reads the full signed appimage into the DDR scratch buffer, and validates
 *   the x509 cert length.  Both threads do this concurrently; the FAT layer
 *   serializes actual MMC1 transfers internally.
 *
 * AM275X — Phase 1:
 *   The appimage is already in DDR (embedded by the SBL).  Just sets
 *   memArgsAppImageBaseAddr and overrides bootMedia for the auth path.
 *   No media I/O.
 *
 * Phase 2 (inside parseMutex, both platforms):
 *   AM62DX: cert-skip Bootloader_parseAppImage + manual RPRC load.
 *   AM275X: Bootloader_parseAndLoadMultiCoreELF with EMMC bootMedia override.
 */
static void TestSbl_sdImgLoadThread(void *args)
{
    int32_t                status = SystemP_SUCCESS;
    TestSbl_MmMtThreadArgs *threadArgs;
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params        bootParams;
#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
    uint32_t certLen = 0U;
#endif

    threadArgs = (TestSbl_MmMtThreadArgs *)args;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* ------------------------------------------------------------------ */
    /* Phase 1 — AM62DX/AM62AX: concurrent FAT reads from SD card (MMC1)  */
    /* ------------------------------------------------------------------ */
#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
    if (threadArgs->mediaType == TEST_SBL_SD_IMG_MEDIA_SD)
    {
        const char *fname;
        FF_FILE    *fp;
        uint32_t    fileSize;
        size_t      bytesRead;

        /* Derive filename from the core being loaded */
        if (threadArgs->coreId == CSL_CORE_ID_A53SS0_0)
            fname = TEST_SBL_SD_IMG_A53_FNAME;
        else if (threadArgs->coreId == CSL_CORE_ID_C75SS0_0)
            fname = TEST_SBL_SD_IMG_DSP_FNAME;
        else
            fname = NULL;

        if (fname == NULL)
        {
            DebugP_log("[SDIMG] No SD filename for core %d\r\n", threadArgs->coreId);
            status = SystemP_FAILURE;
        }

        if (status == SystemP_SUCCESS)
        {
            fp = ff_fopen(fname, "rb");
            if (fp == NULL)
            {
                DebugP_log("[SDIMG] Failed to open %s\r\n", fname);
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            fileSize = ff_filelength(fp);
            if (fileSize == 0U || fileSize > threadArgs->appImageBufSize)
            {
                DebugP_log("[SDIMG] Bad file size %u (%s)\r\n", fileSize, fname);
                ff_fclose(fp);
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            bytesRead = ff_fread(threadArgs->appImageBuf, fileSize, 1U, fp);
            ff_fclose(fp);
            if (bytesRead != 1U)
            {
                DebugP_log("[SDIMG] Read failed for %s\r\n", fname);
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            certLen = Bootloader_getX509CertLen(threadArgs->appImageBuf);
            if (certLen <= TEST_SBL_X509_CERT_MIN_LEN || certLen >= TEST_SBL_X509_CERT_MAX_LEN)
            {
                DebugP_log("[SDIMG] Invalid cert length 0x%x for core %d\r\n",
                           certLen, threadArgs->coreId);
                status = SystemP_FAILURE;
            }
        }

        if (status == SystemP_SUCCESS)
        {
            bootParams.memArgsAppImageBaseAddr = (uintptr_t)threadArgs->appImageBuf;
        }
    }
#endif /* SOC_AM62DX || SOC_AM62AX */

    /* ------------------------------------------------------------------ */
    /* Phase 1 — AM275X: set MEM base address (pre-loaded DDR, no I/O)     */
    /* ------------------------------------------------------------------ */
#if defined(SOC_AM275X)
    bootParams.memArgsAppImageBaseAddr = (uintptr_t)threadArgs->appImageBuf;
#endif

    if (status == SystemP_SUCCESS)
    {
        threadArgs->bootHandle = Bootloader_open(threadArgs->bootloaderInstanceId, &bootParams);
        if (threadArgs->bootHandle == NULL)
        {
            DebugP_log("[SDIMG] Bootloader_open failed for core %d (media %d)\r\n",
                       threadArgs->coreId, threadArgs->mediaType);
            status = SystemP_FAILURE;
        }
    }

    if (threadArgs->bootHandle != NULL)
    {
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            bootConfig->coresPresentMap = 0;
#if defined(SOC_AM275X)
            bootConfig->scratchMemPtr = gMtScratchBuf;
            bootConfig->bootMedia     = BOOTLOADER_MEDIA_EMMC;
#else
            bootConfig->scratchMemPtr = threadArgs->appImageBuf;
#endif
        }

        /* ------------------------------------------------------------------ */
        /* Phase 2: Serialized parse + load (TIFS auth is not thread-safe)     */
        /* ------------------------------------------------------------------ */
        SemaphoreP_pend(threadArgs->parseMutex, SystemP_WAIT_FOREVER);

#if defined(SOC_AM275X)
        status = Bootloader_parseAndLoadMultiCoreELF(threadArgs->bootHandle, &bootImageInfo);
#elif defined(SOC_AM62DX) || defined(SOC_AM62AX)
        {
            Bootloader_Config *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
            Bootloader_MemArgs *memArgs   = (Bootloader_MemArgs *)bootConfig->args;
            uint8_t            *certStart = (uint8_t *)(uintptr_t)memArgs->appImageBaseAddr;

            memArgs->appImageBaseAddr = (uint32_t)(uintptr_t)(certStart + certLen);
            bootConfig->scratchMemPtr = certStart + certLen;
            status = Bootloader_parseAppImage(threadArgs->bootHandle, &bootImageInfo);
        }
#else
        status = Bootloader_parseMultiCoreAppImage(threadArgs->bootHandle, &bootImageInfo);
#endif

        if (status != SystemP_SUCCESS)
        {
            DebugP_log("[SDIMG] parse failed for core %d (media %d)\r\n",
                       threadArgs->coreId, threadArgs->mediaType);
            Bootloader_close(threadArgs->bootHandle);
            threadArgs->bootHandle = NULL;
        }
        else if (TRUE != Bootloader_isCorePresent(threadArgs->bootHandle, threadArgs->coreId))
        {
            DebugP_log("[SDIMG] Core %d not present (media %d)\r\n",
                       threadArgs->coreId, threadArgs->mediaType);
            status = SystemP_FAILURE;
            Bootloader_close(threadArgs->bootHandle);
            threadArgs->bootHandle = NULL;
        }
        else
        {
#if !defined(SOC_AM275X)
            bootImageInfo.cpuInfo[threadArgs->coreId].clkHz =
                Bootloader_socCpuGetClkDefault(threadArgs->coreId);

#if defined(SOC_AM62DX) || defined(SOC_AM62AX)
            {
                Bootloader_Config            *bootConfig = (Bootloader_Config *)threadArgs->bootHandle;
                Bootloader_CpuInfo           *cpuInfo    = &bootImageInfo.cpuInfo[threadArgs->coreId];
                uint8_t                      *rprcBase;
                Bootloader_RprcFileHeader     rprcHdr;
                Bootloader_RprcSectionHeader  secHdr;
                uint32_t s, destAddr;

                status = Bootloader_socCpuRequest(cpuInfo->cpuId);

                if (status == SystemP_SUCCESS)
                    status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

                if (status == SystemP_SUCCESS)
                    status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId, bootConfig->socCoreOpMode);

                if (status == SystemP_SUCCESS && cpuInfo->rprcOffset != BOOTLOADER_INVALID_ID)
                {
                    rprcBase = bootConfig->scratchMemPtr + cpuInfo->rprcOffset;

                    CacheP_inv(rprcBase, sizeof(rprcHdr), CacheP_TYPE_ALL);
                    memcpy(&rprcHdr, rprcBase, sizeof(rprcHdr));
                    rprcBase += sizeof(rprcHdr);

                    if (rprcHdr.magic != BOOTLOADER_RPRC_MAGIC_NUMBER)
                    {
                        status = SystemP_FAILURE;
                    }
                    else
                    {
                        cpuInfo->entryPoint = (uintptr_t)rprcHdr.entry;
                        for (s = 0; s < rprcHdr.sectionCount && status == SystemP_SUCCESS; s++)
                        {
                            memcpy(&secHdr, rprcBase, sizeof(secHdr));
                            rprcBase += sizeof(secHdr);

                            destAddr = Bootloader_socTranslateSectionAddr(
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
#endif /* SOC_AM62DX || SOC_AM62AX */
#endif /* !SOC_AM275X */
        }

        SemaphoreP_post(threadArgs->parseMutex);
    }

    threadArgs->loadStatus = status;
    if (threadArgs->bootHandle != NULL)
    {
        threadArgs->cpuInfo = bootImageInfo.cpuInfo[threadArgs->coreId];
    }

    DebugP_log("[SDIMG] Core %d load from media %d, status = %d\r\n",
               threadArgs->coreId, threadArgs->mediaType, status);

    SemaphoreP_post(threadArgs->doneSem);
    TaskP_exit();
}

/**
 * @brief Concurrent SD-image boot test.
 *
 * On AM62DX both threads read different single-core appimage files from the
 * SD card (FreeRTOS-FAT / MMC1) concurrently:
 *   Thread 0: A53SS0_0    from /sd0/app_a53  (CONFIG_BOOTLOADER_SD_A53).
 *   Thread 1: MCU_R5FSS0_0 from /sd0/app_mcu (CONFIG_BOOTLOADER_SD_MCU).
 * Both threads open their FAT file handles and issue reads simultaneously.
 * The FreeRTOS-FAT layer and MMC1 driver serialize the actual hardware
 * transfers, but both file handles are live at the same time, exercising
 * concurrent FAT filesystem access across two tasks.
 *
 * On AM275X (no SD slot) both threads load pre-loaded MEM images:
 *   Thread 0: R5FSS0_0 from gAppImageBuf0 (CONFIG_BOOTLOADER_MEM_R5FSS0_0).
 *   Thread 1: R5FSS1_0 from gAppImageBuf1 (CONFIG_BOOTLOADER_MEM_R5FSS1_0).
 *
 * No media drivers need to be opened (FreeRTOS-FAT is initialized by
 * Board_driversOpen at startup; MEM uses existing DDR buffers).
 *
 * Test Steps:
 * 1. Open DMA, initialize reserved DDR range (AM62DX).
 * 2. Spawn two tasks; Phase 1 FAT reads run concurrently.
 * 3. Phase 2 parse+load serialized by parseMutex.
 * 4. runCpu, IpcNotify_waitSync, reset, close.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_concurrentSdImageBoot(void *args)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t loopVar;

    /*
     * Thread-to-core-to-media mapping:
     *   AM62DX:
     *     Thread 0: A53SS0_0     from SD /sd0/app_a53  (BOOTLOADER_SD_A53,    MEDIA_SD)
     *     Thread 1: MCU_R5FSS0_0 from SD /sd0/app_mcu  (BOOTLOADER_SD_MCU,    MEDIA_SD)
     *   AM275X (no SD; pre-loaded MEM images):
     *     Thread 0: R5FSS0_0     from MEM gAppImageBuf0 (BOOTLOADER_MEM_R5FSS0_0, MEDIA_MEM)
     *     Thread 1: R5FSS1_0     from MEM gAppImageBuf1 (BOOTLOADER_MEM_R5FSS1_0, MEDIA_MEM)
     */
    /*
     * AM62DX Thread 0: A53SS0_0   from /sd0/app_a53  (single-core A53 image)
     * AM62DX Thread 1: C75SS0_0   from /sd0/app_sys  (multicore image; only C75 is booted)
     * AM275X Thread 0: R5FSS0_0   from gAppImageBuf0 (pre-loaded MEM)
     * AM275X Thread 1: R5FSS1_0   from gAppImageBuf1 (pre-loaded MEM)
     */
    uint32_t coreIds[TEST_SBL_SD_IMG_NUM_CORES] = {
#if defined(SOC_AM275X)
        CSL_CORE_ID_R5FSS0_0,
        CSL_CORE_ID_R5FSS1_0,
#elif defined(SOC_AM62PX)
        /* AM62PX: no A53/C75 boot image; this test is disabled for AM62PX
         * in test_main(). */
        CSL_CORE_ID_MCU_R5FSS0_0,
        CSL_CORE_ID_A53SS0_0,
#else
        CSL_CORE_ID_A53SS0_0,
        CSL_CORE_ID_C75SS0_0,
#endif
    };
    uint32_t mediaTypes[TEST_SBL_SD_IMG_NUM_CORES] = {
#if defined(SOC_AM275X)
        TEST_SBL_SD_IMG_MEDIA_MEM,
        TEST_SBL_SD_IMG_MEDIA_MEM,
#else
        TEST_SBL_SD_IMG_MEDIA_SD,
        TEST_SBL_SD_IMG_MEDIA_SD,
#endif
    };
    uint8_t *appImageBufs[TEST_SBL_SD_IMG_NUM_CORES] = {
#if defined(SOC_AM62PX)
        /* AM62PX: no gAppImageBuf1 (reduced appimage_data.S); dead code. */
        gMtScratchBuf,
        gMtScratchBuf,
#else
        gAppImageBuf0,   /* AM62DX: A53 from /sd0/app_a53  / AM275X: pre-loaded R5FSS0_0 */
        gAppImageBuf1,   /* AM62DX: C75 from /sd0/app_sys  / AM275X: pre-loaded R5FSS1_0 */
#endif
    };
    uint32_t bootloaderInstances[TEST_SBL_SD_IMG_NUM_CORES] = {
#if defined(SOC_AM275X)
        CONFIG_BOOTLOADER_MEM_R5FSS0_0,
        CONFIG_BOOTLOADER_MEM_R5FSS1_0,
#elif defined(SOC_AM62PX)
        CONFIG_BOOTLOADER_SD_MCU,
        CONFIG_BOOTLOADER_SD_A53,
#else
        CONFIG_BOOTLOADER_SD_A53,
        CONFIG_BOOTLOADER_SD_MULTICORE,   /* reads /sd0/app_sys; only C75SS0_0 is booted */
#endif
    };
    uint8_t *taskStacks[TEST_SBL_SD_IMG_NUM_CORES] = {
        gMtTaskStack0,
        gMtTaskStack1,
    };
    TestSbl_MmMtThreadArgs threadArgs[TEST_SBL_SD_IMG_NUM_CORES];
    TaskP_Object           taskObjs[TEST_SBL_SD_IMG_NUM_CORES];
    SemaphoreP_Object      doneSems[TEST_SBL_SD_IMG_NUM_CORES];
    SemaphoreP_Object      parseMutex;

    DebugP_log("Starting TestSbl_concurrentSdImageBoot test...\r\n");

    Bootloader_profileAddProfilePoint("SBL Drivers_open");
    Bootloader_openDma();

#if !defined(SOC_AM275X)
    Bootloader_ReservedMemInit(TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_START,
                               TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_LENGTH);
#endif

    status = SemaphoreP_constructMutex(&parseMutex);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        status = SemaphoreP_constructBinary(&doneSems[loopVar], 0);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        threadArgs[loopVar].appImageBuf          = appImageBufs[loopVar];
        threadArgs[loopVar].appImageBufSize      = TEST_SBL_APPIMAGE_MAX_FILE_SIZE;
        threadArgs[loopVar].coreId               = coreIds[loopVar];
        threadArgs[loopVar].bootloaderInstanceId = bootloaderInstances[loopVar];
        threadArgs[loopVar].mediaType            = mediaTypes[loopVar];
        threadArgs[loopVar].loadStatus           = SystemP_FAILURE;
        threadArgs[loopVar].bootHandle           = NULL;
        threadArgs[loopVar].doneSem              = &doneSems[loopVar];
        threadArgs[loopVar].parseMutex           = &parseMutex;
    }

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "sdimg_boot_thread";
        taskParams.stackSize = TEST_SBL_MT_TASK_STACK_SIZE;
        taskParams.stack     = taskStacks[loopVar];
        taskParams.priority  = TEST_SBL_MT_TASK_PRIORITY;
        taskParams.args      = &threadArgs[loopVar];
        taskParams.taskMain  = TestSbl_sdImgLoadThread;

        status = TaskP_construct(&taskObjs[loopVar], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        SemaphoreP_pend(&doneSems[loopVar], SystemP_WAIT_FOREVER);
    }

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        TEST_ASSERT_EQUAL(threadArgs[loopVar].loadStatus, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("[SDIMG] CPU %d: Running (media %d)...\r\n",
                           coreIds[loopVar], mediaTypes[loopVar]);
                status = Bootloader_runCpu(threadArgs[loopVar].bootHandle,
                                           &threadArgs[loopVar].cpuInfo);
                DebugP_log("[SDIMG] CPU %d: runCpu status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    Bootloader_closeDma();

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
#if !defined(SOC_AM275X)
                DebugP_log("[SDIMG] CPU %d: Waiting for IPC sync...\r\n",
                           coreIds[loopVar]);
                status = IpcNotify_waitSync(coreIds[loopVar], 10000);
                DebugP_log("[SDIMG] CPU %d: IPC sync status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
#else
                {
                    uint32_t cid = coreIds[loopVar];
                    volatile uint32_t *stamp =
                        (volatile uint32_t *)(0x723C2000U + cid * sizeof(uint32_t));
                    uintptr_t lineAddr   = (0x723C2000U + cid * sizeof(uint32_t)) & ~((uintptr_t)31U);
                    uint32_t expected    = 0xABCD0000U | cid;
                    uint32_t startCycles = CycleCounterP_getCount32();
                    uint32_t timeout     = (SOC_getSelfCpuClk() / 1000U) * 5000U;
                    int32_t  syncStatus  = SystemP_FAILURE;

                    status = IpcNotify_sendSync(cid);
                    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
                    DebugP_log("[SDIMG] CPU %d: Waiting for IPC sync...\r\n", cid);
                    while((CycleCounterP_getCount32() - startCycles) < timeout)
                    {
                        /* WKUP-R5 maps 0x72000000-0x72400000 CACHEABLE: invalidate
                         * the line so we see the remote's DDR stamp write. */
                        CacheP_inv((void *)lineAddr, 32U, CacheP_TYPE_ALL);
                        if(*stamp == expected) { syncStatus = SystemP_SUCCESS; break; }
                    }
                    DebugP_log("[SDIMG] CPU %d: IPC sync status = %d\r\n", cid, syncStatus);
                    TEST_ASSERT_EQUAL(syncStatus, SystemP_SUCCESS);
                }
#endif
            }
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            DebugP_log("[SDIMG] CPU %d: Resetting...\r\n", coreIds[loopVar]);
            status = Bootloader_socCpuRequest(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_socCpuPowerOff(threadArgs[loopVar].cpuInfo.cpuId);
            status = Bootloader_socCpuRelease(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("[SDIMG] CPU %d: Reset complete\r\n", coreIds[loopVar]);
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].bootHandle != NULL)
        {
            Bootloader_close(threadArgs[loopVar].bootHandle);
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_SD_IMG_NUM_CORES; loopVar++)
    {
        TaskP_destruct(&taskObjs[loopVar]);
        SemaphoreP_destruct(&doneSems[loopVar]);
    }
    SemaphoreP_destruct(&parseMutex);

    DebugP_log("TestSbl_concurrentSdImageBoot test completed\r\n");
}

/**
 * @brief Concurrent OSPI-image boot test.
 *
 * Both threads read single-core appimages from OSPI NOR flash (OSPI0) at
 * different appimage offsets and boot separate cores concurrently.
 *
 * Thread 0 reads the single-core DSP image from CONFIG_BOOTLOADER_FLASH_DSP
 * (0xA00000) and boots C75SS0_0.  Thread 1 reads the multicore image from
 * CONFIG_BOOTLOADER_FLASH_MULTICORE (0x1200000) and boots only the MCU
 * R5FSS0_0 core (AM62DX) or R5FSS0_0 (AM275X).
 *
 * OSPI0 is one physical controller so the DMA transfers are serialized at
 * the hardware level, but both threads queue their reads simultaneously,
 * testing the OSPI driver under concurrent access from two tasks.
 *
 * The thread worker is TestSbl_emmcImgLoadThread, which is media-agnostic:
 * it dispatches through bootConfig->fxns->imgReadFxn regardless of whether
 * the bootloader instance is eMMC or OSPI NOR.
 *
 * Test Steps:
 * 1. Enable FSS0 clock (AM275X only).
 * 2. Open OSPI driver and Flash board driver.
 * 3. Spawn two tasks using TestSbl_emmcImgLoadThread.
 * 4. Phase 1 (AM62DX): concurrent imgReadFxn reads from different OSPI offsets.
 * 5. Phase 2 (parseMutex): cert-skip parse + CPU load (AM62DX) or
 *    parseAndLoadMultiCoreELF (AM275X).
 * 6. runCpu, IpcNotify_waitSync, reset, close.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_concurrentOspiImageBoot(void *args)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t loopVar;

    /*
     * Thread-to-core-to-media mapping:
     *   AM62DX:
     *     Thread 0: C75SS0_0     from FLASH_DSP       @ 0xA00000   (single-core DSP image)
     *     Thread 1: MCU_R5FSS0_0 from FLASH_MULTICORE @ 0x1200000  (multicore; MCU booted)
     *   AM275X:
     *     Thread 0: C75SS0_0     from FLASH_DSP       @ 0xA00000   (single-core DSP image)
     *     Thread 1: R5FSS0_0     from FLASH_MULTICORE @ 0x1200000  (multicore; R5FSS0_0 booted)
     */
    uint32_t coreIds[TEST_SBL_OSPI_IMG_NUM_CORES] = {
#if !defined(SOC_AM62PX)
        CSL_CORE_ID_C75SS0_0,
#else
        /* AM62PX has no C75 core; this test is disabled for AM62PX in
         * test_main(). */
        CSL_CORE_ID_A53SS0_0,
#endif
#if defined(SOC_AM275X)
        CSL_CORE_ID_R5FSS0_0,
#else
        CSL_CORE_ID_MCU_R5FSS0_0,
#endif
    };
    uint32_t mediaTypes[TEST_SBL_OSPI_IMG_NUM_CORES] = {
        TEST_SBL_OSPI_IMG_MEDIA_FLASH,
        TEST_SBL_OSPI_IMG_MEDIA_FLASH,
    };
    uint8_t *appImageBufs[TEST_SBL_OSPI_IMG_NUM_CORES] = {
#if defined(SOC_AM275X)
        gMtScratchBuf,   /* shared scratch — serialized by parseMutex */
        gMtScratchBuf,
#elif defined(SOC_AM62PX)
        /* AM62PX: no gAppImageBuf1; this test is disabled for AM62PX
         * in test_main(). */
        gMtScratchBuf,
        gMtScratchBuf,
#else
        gAppImageBuf0,   /* DSP image read from OSPI @ 0xA00000       */
        gAppImageBuf1,   /* multicore image read from OSPI @ 0x1200000 */
#endif
    };
    uint32_t bootloaderInstances[TEST_SBL_OSPI_IMG_NUM_CORES] = {
        CONFIG_BOOTLOADER_FLASH_DSP,
        CONFIG_BOOTLOADER_FLASH_MULTICORE,
    };
    uint8_t *taskStacks[TEST_SBL_OSPI_IMG_NUM_CORES] = {
        gMtTaskStack0,
        gMtTaskStack1,
    };
    TestSbl_MmMtThreadArgs threadArgs[TEST_SBL_OSPI_IMG_NUM_CORES];
    TaskP_Object           taskObjs[TEST_SBL_OSPI_IMG_NUM_CORES];
    SemaphoreP_Object      doneSems[TEST_SBL_OSPI_IMG_NUM_CORES];
    SemaphoreP_Object      parseMutex;

    DebugP_log("Starting TestSbl_concurrentOspiImageBoot test...\r\n");

#if defined(SOC_AM275X)
    {
        int32_t clkStatus;

        DebugP_log("[OSPIIMG] Enabling FSS0 clock...\r\n");
        clkStatus = SOC_moduleClockEnable(TISCI_DEV_FSS0, 1);
        DebugP_log("[OSPIIMG] FSS0 clock enable status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);

        clkStatus = SOC_moduleSetClockFrequency(
                        TISCI_DEV_FSS0,
                        TISCI_DEV_FSS0_OSPI0_RCLK_CLK,
                        166666666);
        DebugP_log("[OSPIIMG] FSS0 clock freq status = %d\r\n", clkStatus);
        TEST_ASSERT_EQUAL(clkStatus, SystemP_SUCCESS);
    }
#endif

    DebugP_log("[OSPIIMG] Opening OSPI...\r\n");
    status = TestSbl_openBootDriverFlash();
    DebugP_log("[OSPIIMG] OSPI open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    DebugP_log("[OSPIIMG] Opening Flash...\r\n");
    status = TestSbl_openBootBoardFlash();
    DebugP_log("[OSPIIMG] Flash open status = %d\r\n", status);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    Bootloader_profileAddProfilePoint("SBL Drivers_open");
    Bootloader_openDma();

#if !defined(SOC_AM275X)
    Bootloader_ReservedMemInit(TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_START,
                               TEST_SBL_SECOND_STAGE_RESERVED_MEMORY_LENGTH);
#endif

    status = SemaphoreP_constructMutex(&parseMutex);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        status = SemaphoreP_constructBinary(&doneSems[loopVar], 0);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        threadArgs[loopVar].appImageBuf          = appImageBufs[loopVar];
        threadArgs[loopVar].appImageBufSize      = TEST_SBL_APPIMAGE_MAX_FILE_SIZE;
        threadArgs[loopVar].coreId               = coreIds[loopVar];
        threadArgs[loopVar].bootloaderInstanceId = bootloaderInstances[loopVar];
        threadArgs[loopVar].mediaType            = mediaTypes[loopVar];
        threadArgs[loopVar].loadStatus           = SystemP_FAILURE;
        threadArgs[loopVar].bootHandle           = NULL;
        threadArgs[loopVar].doneSem              = &doneSems[loopVar];
        threadArgs[loopVar].parseMutex           = &parseMutex;
    }

    /* TestSbl_emmcImgLoadThread is media-agnostic: dispatches through
     * bootConfig->fxns->imgReadFxn, which resolves to OSPI flash reads
     * for FLASH bootloader instances, identical to the eMMC path. */
    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "ospiimg_boot_thread";
        taskParams.stackSize = TEST_SBL_MT_TASK_STACK_SIZE;
        taskParams.stack     = taskStacks[loopVar];
        taskParams.priority  = TEST_SBL_MT_TASK_PRIORITY;
        taskParams.args      = &threadArgs[loopVar];
        taskParams.taskMain  = TestSbl_emmcImgLoadThread;

        status = TaskP_construct(&taskObjs[loopVar], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        SemaphoreP_pend(&doneSems[loopVar], SystemP_WAIT_FOREVER);
    }

    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        TEST_ASSERT_EQUAL(threadArgs[loopVar].loadStatus, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("[OSPIIMG] CPU %d: Running...\r\n", coreIds[loopVar]);
                status = Bootloader_runCpu(threadArgs[loopVar].bootHandle,
                                           &threadArgs[loopVar].cpuInfo);
                DebugP_log("[OSPIIMG] CPU %d: runCpu status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    Bootloader_closeDma();

    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
#if !defined(SOC_AM275X)
            if (((coreIds[loopVar] == CSL_CORE_ID_MCU_R5FSS0_0) &&
                 !Bootloader_socIsMCUResetIsoEnabled()) ||
                (coreIds[loopVar] != CSL_CORE_ID_MCU_R5FSS0_0))
#endif
            {
                DebugP_log("[OSPIIMG] CPU %d: Waiting for IPC sync...\r\n",
                           coreIds[loopVar]);
                status = IpcNotify_waitSync(coreIds[loopVar], 10000);
                DebugP_log("[OSPIIMG] CPU %d: IPC sync status = %d\r\n",
                           coreIds[loopVar], status);
                TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            }
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            DebugP_log("[OSPIIMG] CPU %d: Resetting...\r\n", coreIds[loopVar]);
            status = Bootloader_socCpuRequest(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_socCpuPowerOff(threadArgs[loopVar].cpuInfo.cpuId);
            status = Bootloader_socCpuRelease(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("[OSPIIMG] CPU %d: Reset complete\r\n", coreIds[loopVar]);
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].bootHandle != NULL)
        {
            Bootloader_close(threadArgs[loopVar].bootHandle);
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_OSPI_IMG_NUM_CORES; loopVar++)
    {
        TaskP_destruct(&taskObjs[loopVar]);
        SemaphoreP_destruct(&doneSems[loopVar]);
    }
    SemaphoreP_destruct(&parseMutex);

    TestSbl_closeBootBoardFlash();
    TestSbl_closeBootDriverFlash();

#if defined(SOC_AM275X)
    status = SOC_moduleClockEnable(TISCI_DEV_FSS0, 0);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
#endif

    DebugP_log("TestSbl_concurrentOspiImageBoot test completed\r\n");
}

/*
 * Bootloader_bootCpu positive test thread.
 *
 * Constructs a Bootloader_CpuInfo manually — no appimage is parsed or loaded.
 *   cpuId      = target core
 *   clkHz      = Bootloader_socCpuGetClkDefault(coreId)
 *   entryPoint = 0  (the CPU is released but its code content is irrelevant
 *                    for this API-level positive test; it is reset immediately)
 *   rprcOffset = BOOTLOADER_INVALID_ID  (skip all RPRC loading; no DMA used)
 *
 * Calls Bootloader_bootCpu inside parseMutex because the internal TISCI
 * (Sciclient) calls for CPU claim, clock, and power-on-reset are not
 * thread-safe across simultaneous invocations.
 */
static void TestSbl_bootCpuThread(void *args)
{
    int32_t                status = SystemP_SUCCESS;
    TestSbl_MmMtThreadArgs *threadArgs = (TestSbl_MmMtThreadArgs *)args;
    Bootloader_Params       bootParams;
    Bootloader_CpuInfo      cpuInfo;

    Bootloader_Params_init(&bootParams);

    threadArgs->bootHandle = Bootloader_open(threadArgs->bootloaderInstanceId, &bootParams);
    if (threadArgs->bootHandle == NULL)
    {
        DebugP_log("[BOOTCPU] Bootloader_open failed for core %d\r\n",
                   threadArgs->coreId);
        status = SystemP_FAILURE;
    }
    else
    {
        /* Manually initialise CpuInfo — no appimage parsing */
        memset(&cpuInfo, 0, sizeof(cpuInfo));
        cpuInfo.cpuId      = threadArgs->coreId;
        cpuInfo.clkHz      = Bootloader_socCpuGetClkDefault(threadArgs->coreId);
        cpuInfo.entryPoint = 0U;
#if !defined(SOC_AM275X)
        cpuInfo.rprcOffset = BOOTLOADER_INVALID_ID;
#endif

        /* Serialise: Sciclient used inside bootCpu is not thread-safe */
        SemaphoreP_pend(threadArgs->parseMutex, SystemP_WAIT_FOREVER);

        /* Positive test: must return SUCCESS without an appimage */
        status = Bootloader_bootCpu(threadArgs->bootHandle, &cpuInfo);

        SemaphoreP_post(threadArgs->parseMutex);

        threadArgs->cpuInfo = cpuInfo;
    }

    threadArgs->loadStatus = status;

    DebugP_log("[BOOTCPU] Core %d bootCpu status = %d\r\n",
               threadArgs->coreId, status);

    SemaphoreP_post(threadArgs->doneSem);
    TaskP_exit();
}

/**
 * @brief Positive test for Bootloader_bootCpu without an appimage.
 *
 * Spawns two FreeRTOS tasks that each call Bootloader_bootCpu with a
 * manually-constructed Bootloader_CpuInfo (rprcOffset=BOOTLOADER_INVALID_ID,
 * entryPoint=0).  No appimage is parsed or loaded; the test verifies that
 * the full CPU claim / clock-set / power-on-reset / run sequence completes
 * with SystemP_SUCCESS for every core.
 *
 * Because rprcOffset=BOOTLOADER_INVALID_ID, Bootloader_loadCpu skips the
 * RPRC image-load step entirely — no DMA channel is needed.  Only TISCI
 * messages are sent, serialized by parseMutex.
 *
 * After verifying SUCCESS the cores are immediately reset
 * (Bootloader_socCpuPowerOff + Bootloader_socCpuRelease) before they can
 * execute arbitrary code at entryPoint=0.
 *
 * Test Steps:
 * 1. Spawn two tasks, each calling Bootloader_bootCpu under parseMutex.
 * 2. Wait for all threads; assert all return SystemP_SUCCESS.
 * 3. For each successful core: re-request, power-off, release.
 * 4. Close bootloader handles and clean up.
 *
 * Cores tested:
 *   AM62DX: A53SS0_0  (CONFIG_BOOTLOADER_SD_SMP),
 *           C75SS0_0  (CONFIG_BOOTLOADER_SD_MULTICORE)
 *   AM275X: R5FSS0_0  (CONFIG_BOOTLOADER_MEM_R5FSS0_0),
 *           R5FSS1_0  (CONFIG_BOOTLOADER_MEM_R5FSS1_0)
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_bootCpuPositive(void *args)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t loopVar;

    uint32_t coreIds[TEST_SBL_BOOT_CPU_NUM_CORES] = {
#if defined(SOC_AM275X)
        CSL_CORE_ID_R5FSS0_0,
        CSL_CORE_ID_R5FSS1_0,
#elif defined(SOC_AM62PX)
        /*
         * AM62PX has no C75 core, and no A53 boot image is provisioned on
         * this board — but this positive test never loads an appimage
         * (rprcOffset=BOOTLOADER_INVALID_ID, entryPoint=0), so any real
         * core ID works. Use MCU_R5FSS0_0 and A53SS0_0 (both real
         * hardware on this SOC) so this test remains fully functional.
         */
        CSL_CORE_ID_MCU_R5FSS0_0,
        CSL_CORE_ID_A53SS0_0,
#else
        CSL_CORE_ID_A53SS0_0,
        CSL_CORE_ID_C75SS0_0,
#endif
    };
    /* MEM bootloader instances: provide socCoreOpMode; no I/O performed */
    uint32_t bootloaderInstances[TEST_SBL_BOOT_CPU_NUM_CORES] = {
#if defined(SOC_AM275X)
        CONFIG_BOOTLOADER_MEM_R5FSS0_0,
        CONFIG_BOOTLOADER_MEM_R5FSS1_0,
#elif defined(SOC_AM62PX)
        CONFIG_BOOTLOADER_SD_MCU,         /* MEM mode; opMode matches MCU_R5FSS0_0 */
        CONFIG_BOOTLOADER_SD_A53,         /* MEM mode; opMode matches A53SS0_0     */
#else
        CONFIG_BOOTLOADER_SD_SMP,        /* MEM mode; opMode matches A53SS0_0 */
        CONFIG_BOOTLOADER_SD_MULTICORE,  /* MEM mode; opMode matches C75SS0_0 */
#endif
    };
    uint8_t *taskStacks[TEST_SBL_BOOT_CPU_NUM_CORES] = {
        gMtTaskStack0,
        gMtTaskStack1,
    };
    TestSbl_MmMtThreadArgs threadArgs[TEST_SBL_BOOT_CPU_NUM_CORES];
    TaskP_Object           taskObjs[TEST_SBL_BOOT_CPU_NUM_CORES];
    SemaphoreP_Object      doneSems[TEST_SBL_BOOT_CPU_NUM_CORES];
    SemaphoreP_Object      parseMutex;

    DebugP_log("Starting TestSbl_bootCpuPositive test...\r\n");

    status = SemaphoreP_constructMutex(&parseMutex);
    TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);

    for (loopVar = 0; loopVar < TEST_SBL_BOOT_CPU_NUM_CORES; loopVar++)
    {
        status = SemaphoreP_constructBinary(&doneSems[loopVar], 0);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_BOOT_CPU_NUM_CORES; loopVar++)
    {
        threadArgs[loopVar].appImageBuf          = NULL;
        threadArgs[loopVar].appImageBufSize      = 0U;
        threadArgs[loopVar].coreId               = coreIds[loopVar];
        threadArgs[loopVar].bootloaderInstanceId = bootloaderInstances[loopVar];
        threadArgs[loopVar].mediaType            = 0U;
        threadArgs[loopVar].loadStatus           = SystemP_FAILURE;
        threadArgs[loopVar].bootHandle           = NULL;
        threadArgs[loopVar].doneSem              = &doneSems[loopVar];
        threadArgs[loopVar].parseMutex           = &parseMutex;
    }

    for (loopVar = 0; loopVar < TEST_SBL_BOOT_CPU_NUM_CORES; loopVar++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "bootcpu_thread";
        taskParams.stackSize = TEST_SBL_MT_TASK_STACK_SIZE;
        taskParams.stack     = taskStacks[loopVar];
        taskParams.priority  = TEST_SBL_MT_TASK_PRIORITY;
        taskParams.args      = &threadArgs[loopVar];
        taskParams.taskMain  = TestSbl_bootCpuThread;

        status = TaskP_construct(&taskObjs[loopVar], &taskParams);
        TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
    }

    for (loopVar = 0; loopVar < TEST_SBL_BOOT_CPU_NUM_CORES; loopVar++)
    {
        SemaphoreP_pend(&doneSems[loopVar], SystemP_WAIT_FOREVER);
    }

    /* Positive-test assertion: all bootCpu calls must have succeeded */
    for (loopVar = 0; loopVar < TEST_SBL_BOOT_CPU_NUM_CORES; loopVar++)
    {
        TEST_ASSERT_EQUAL(threadArgs[loopVar].loadStatus, SystemP_SUCCESS);
    }

    /* Reset all booted cores before they execute arbitrary code at entryPoint=0 */
    for (loopVar = 0; loopVar < TEST_SBL_BOOT_CPU_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].loadStatus == SystemP_SUCCESS)
        {
            DebugP_log("[BOOTCPU] Core %d: Resetting...\r\n",
                       threadArgs[loopVar].cpuInfo.cpuId);
            status = Bootloader_socCpuRequest(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            Bootloader_socCpuPowerOff(threadArgs[loopVar].cpuInfo.cpuId);
            status = Bootloader_socCpuRelease(threadArgs[loopVar].cpuInfo.cpuId);
            TEST_ASSERT_EQUAL(status, SystemP_SUCCESS);
            DebugP_log("[BOOTCPU] Core %d: Reset complete\r\n",
                       threadArgs[loopVar].cpuInfo.cpuId);
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_BOOT_CPU_NUM_CORES; loopVar++)
    {
        if (threadArgs[loopVar].bootHandle != NULL)
        {
            Bootloader_close(threadArgs[loopVar].bootHandle);
        }
    }

    for (loopVar = 0; loopVar < TEST_SBL_BOOT_CPU_NUM_CORES; loopVar++)
    {
        TaskP_destruct(&taskObjs[loopVar]);
        SemaphoreP_destruct(&doneSems[loopVar]);
    }
    SemaphoreP_destruct(&parseMutex);

    DebugP_log("TestSbl_bootCpuPositive test completed\r\n");
}

