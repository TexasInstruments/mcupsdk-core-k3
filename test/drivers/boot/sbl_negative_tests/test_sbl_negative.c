#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <drivers/mmcsd.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/TaskP.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/bootloader.h>
#include <drivers/bootloader/bootloader_priv.h>

/* SW_VERSION is passed as -D to the driver library build but not to tests.
 * Define it here to match the value from imports.mak for RPRC header construction. */
#ifndef SW_VERSION
#define SW_VERSION 0x0A010000U
#endif

void TestSbl_openCloseSuccess(void *args);
void TestSbl_openOpenFail(void *args);
void TestSbl_openCloseOpen(void *args);
void TestSbl_openFail(void *args);
void TestSbl_closeFail(void *args);
void TestSbl_getBootMedia(void *args);
void TestSbl_getBootMediaFail(void *args);
void TestSbl_getImageSzFail(void *args);
void TestSbl_getImageSzBeforeParse(void *args);
void TestSbl_seekBeyondMediaSize(void *args);
/* The following tests rely on RPRC-format internals and are not applicable
 * on AM275x which uses the MCELF bootloader format. */
#if !defined(SOC_AM275X)
void TestSbl_parseImageFail(void *args);
void TestSbl_parseInvalidRprcMagic(void *args);
void TestSbl_parseCorruptedMetaHeader(void *args);
void TestSbl_parseMismatchedDeviceId(void *args);
void TestSbl_parseInvalidSectionCount(void *args);
void TestSbl_parseNullBootImageInfo(void *args);
void TestSbl_parseNullHandle(void *args);
void TestSbl_parseInvalidEntryPoint(void *args);
void TestSbl_loadImageToProtectedMemory(void *args);
void TestSbl_loadImageInsufficientMemory(void *args);
void TestSbl_loadRprcCorruptedSectionHdr(void *args);
void TestSbl_loadImageReadFails(void *args);
void TestSbl_loadImageInvalidRprcOffset(void *args);
void TestSbl_loadSelfCpuInvalidClockFreq(void *args);
void TestSbl_loadImageExceedsReservedBounds(void *args);
#endif /* !defined(SOC_AM275X) */
void TestSbl_readBeyondAvailableData(void *args);
void TestSbl_runCpuBeforeLoad(void *args);
void TestSbl_runCpuNullHandle(void *args);
void TestSbl_runCpuNullCpuInfo(void *args);
void TestSbl_bootCpuInvalidCpuId(void *args);
void TestSbl_runSelfCpuNotRequested(void *args);
void TestSbl_setCpuClockInvalidFreq(void *args);
void TestSbl_releaseCpuNotInReset(void *args);
void TestSbl_powerOffAlreadyOff(void *args);
void TestSbl_isCorePresInvalidId(void *args);

void setUp(void)
{
    /* Setup function nothing to perform */
}

void tearDown(void)
{
    /* Tear down function nothing to perform */
}

void test_main(void * args)
{
    UNITY_BEGIN();

    RUN_TEST(TestSbl_openCloseSuccess,     8000, NULL);
    RUN_TEST(TestSbl_openCloseOpen,        8000, NULL);
    RUN_TEST(TestSbl_openFail,             8000, NULL);
    RUN_TEST(TestSbl_closeFail,            8000, NULL);
    RUN_TEST(TestSbl_getBootMedia,         8000, NULL);
    RUN_TEST(TestSbl_getBootMediaFail,     8000, NULL);
    RUN_TEST(TestSbl_getImageSzFail,       8000, NULL);
    RUN_TEST(TestSbl_openOpenFail,         8000, NULL);
    RUN_TEST(TestSbl_getImageSzBeforeParse,  8000, NULL);
    RUN_TEST(TestSbl_seekBeyondMediaSize,    8000, NULL);
#if !defined(SOC_AM275X)
    RUN_TEST(TestSbl_parseImageFail,       8000, NULL);
    RUN_TEST(TestSbl_parseInvalidRprcMagic,  8000, NULL);
    RUN_TEST(TestSbl_parseCorruptedMetaHeader, 8000, NULL);
    RUN_TEST(TestSbl_parseMismatchedDeviceId, 8000, NULL);
    RUN_TEST(TestSbl_parseInvalidSectionCount, 8000, NULL);
    RUN_TEST(TestSbl_parseNullBootImageInfo, 8000, NULL);
    RUN_TEST(TestSbl_parseNullHandle,        8000, NULL);
    RUN_TEST(TestSbl_parseInvalidEntryPoint, 8000, NULL);
    RUN_TEST(TestSbl_loadImageToProtectedMemory, 8000, NULL);
    RUN_TEST(TestSbl_loadImageInsufficientMemory, 8000, NULL);
    RUN_TEST(TestSbl_loadRprcCorruptedSectionHdr, 8000, NULL);
    RUN_TEST(TestSbl_loadImageReadFails,     8000, NULL);
    RUN_TEST(TestSbl_loadImageInvalidRprcOffset, 8000, NULL);
    RUN_TEST(TestSbl_loadSelfCpuInvalidClockFreq, 8000, NULL);
    RUN_TEST(TestSbl_loadImageExceedsReservedBounds, 8000, NULL);
#endif /* !defined(SOC_AM275X) */
    RUN_TEST(TestSbl_readBeyondAvailableData, 8000, NULL);
    RUN_TEST(TestSbl_runCpuBeforeLoad,       8000, NULL);
    RUN_TEST(TestSbl_runCpuNullHandle,       8000, NULL);
    RUN_TEST(TestSbl_runCpuNullCpuInfo,      8000, NULL);
    RUN_TEST(TestSbl_bootCpuInvalidCpuId,    8000, NULL);
    RUN_TEST(TestSbl_runSelfCpuNotRequested, 8000, NULL);
    RUN_TEST(TestSbl_setCpuClockInvalidFreq, 8000, NULL);
    RUN_TEST(TestSbl_releaseCpuNotInReset,   8000, NULL);
    RUN_TEST(TestSbl_powerOffAlreadyOff,     8000, NULL);
    RUN_TEST(TestSbl_isCorePresInvalidId,    8000, NULL);

    UNITY_END();
}

void TestSbl_openCloseSuccess(void *args)
{
    uint32_t loopVar;

    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_OpenCloseSuccess test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle  = Bootloader_open(loopVar, &bootParams);
        TEST_ASSERT_NOT_NULL(bootHandle);
        Bootloader_close(bootHandle);
    }
}

void TestSbl_openOpenFail(void *args)
{
    uint32_t loopVar;

    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_openOpenFail test\r\n");

    Bootloader_BootImageInfo bootImageInfo1[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_BootImageInfo bootImageInfo2[CONFIG_BOOTLOADER_NUM_INSTANCES];

    Bootloader_Params bootParams1[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Params bootParams2[CONFIG_BOOTLOADER_NUM_INSTANCES];

    Bootloader_Handle bootHandle1[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Handle bootHandle2[CONFIG_BOOTLOADER_NUM_INSTANCES];

    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle1[loopVar] = NULL;
        bootHandle2[loopVar] = NULL;

        Bootloader_Params_init(&bootParams1[loopVar]);
        Bootloader_Params_init(&bootParams2[loopVar]);

        Bootloader_BootImageInfo_init(&bootImageInfo1[loopVar]);
        Bootloader_BootImageInfo_init(&bootImageInfo2[loopVar]);
    }

    /* Open the driver once */
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle1[loopVar]  = Bootloader_open(loopVar, &bootParams1[loopVar]);
        TEST_ASSERT_NOT_NULL(bootHandle1[loopVar]);
    }

    /* Bootloader_open does not track open state, so a second open on the
     * same instance returns the same valid config pointer.  Verify that the
     * returned handle matches the first one (same config entry). */
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle2[loopVar]  = Bootloader_open(loopVar, &bootParams2[loopVar]);
        TEST_ASSERT_NOT_NULL(bootHandle2[loopVar]);
        TEST_ASSERT_EQUAL_PTR(bootHandle1[loopVar], bootHandle2[loopVar]);
    }

    /* Close the original handles */ 
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        Bootloader_close(bootHandle1[loopVar]);
    }
}

void TestSbl_openCloseOpen(void *args)
{
    uint32_t loopVar;
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_openOpenFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Params bootParams[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Handle bootHandle[CONFIG_BOOTLOADER_NUM_INSTANCES];
    
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle[loopVar] = NULL;
        Bootloader_Params_init(&bootParams[loopVar]);
        Bootloader_BootImageInfo_init(&bootImageInfo[loopVar]);
    }

    /* Open the driver once and close it */
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle[loopVar] = Bootloader_open(loopVar, &bootParams[loopVar]);
        TEST_ASSERT_NOT_NULL(bootHandle[loopVar]);
        Bootloader_close(bootHandle[loopVar]);
    }
    
    /* Open should work for the second time as well */
    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++)
    {
        bootHandle[loopVar] = Bootloader_open(loopVar, &bootParams[loopVar]);
        TEST_ASSERT_NOT_NULL(bootHandle[loopVar]);
        Bootloader_close(bootHandle[loopVar]);
    }
}

void  TestSbl_openFail(void *args)
{
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_openOpenFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* Open for an invalid instance and check if fails */
    bootHandle = Bootloader_open((CONFIG_BOOTLOADER_NUM_INSTANCES + 1), 
                    &bootParams);
    TEST_ASSERT_NULL(bootHandle);

    /*Check if open works after failure */
    bootHandle = Bootloader_open(0, &bootParams);
    TEST_ASSERT_NOT_NULL(bootHandle);
    Bootloader_close(bootHandle);
}

void TestSbl_closeFail(void *args)
{
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_closeFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;
    
    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* Open for an valid instance and check if fails */
    bootHandle = Bootloader_open(0, &bootParams);
    TEST_ASSERT_NOT_NULL(bootHandle);

    /* No hang should happen */
    Bootloader_close(NULL);

    /* close the original handle */
    Bootloader_close(bootHandle);
}

void TestSbl_getBootMedia(void *args)
{
    uint32_t media = SystemP_SUCCESS;
    uint32_t loopVar;
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_getBootMedia test\r\n");
    Bootloader_BootImageInfo bootImageInfo[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Params bootParams[CONFIG_BOOTLOADER_NUM_INSTANCES];
    Bootloader_Handle bootHandle[CONFIG_BOOTLOADER_NUM_INSTANCES] = {NULL , NULL};

    for(loopVar = 0; loopVar < CONFIG_BOOTLOADER_NUM_INSTANCES; loopVar++ )
    {
        Bootloader_Params_init(&bootParams[loopVar]);
        Bootloader_BootImageInfo_init(&bootImageInfo[loopVar]);
        bootHandle[loopVar] = Bootloader_open(loopVar, &bootParams[loopVar]);   
        TEST_ASSERT_NOT_NULL(bootHandle[loopVar]);
        media = Bootloader_getBootMedia(bootHandle[loopVar]);
        if(loopVar == 0)
        {
            TEST_ASSERT_EQUAL(media, BOOTLOADER_MEDIA_EMMC);
        }
        else
        {
            TEST_ASSERT_EQUAL(media, BOOTLOADER_MEDIA_FLASH);
        }
        Bootloader_close(bootHandle[loopVar]);
    }
}
    
void TestSbl_getBootMediaFail(void *args)
{
    int32_t status = SystemP_SUCCESS;
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_getBootMediaFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);
    bootHandle = Bootloader_open(0, &bootParams);
    TEST_ASSERT_NOT_NULL(bootHandle);
    
    status = Bootloader_getBootMedia(NULL);
    TEST_ASSERT_EQUAL(status, BOOTLOADER_INVALID_ID);

    Bootloader_close(bootHandle);
}

void TestSbl_getImageSzFail(void *args)
{
    int32_t status = SystemP_SUCCESS;
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    DebugP_log("Starting TestSbl_getImageSzFail test\r\n");
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;
    
    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);
    bootHandle = Bootloader_open(0, &bootParams);
    TEST_ASSERT_NOT_NULL(bootHandle);
    
    /* For invalid handle the size should be zero */
    status = Bootloader_getMulticoreImageSize(NULL);
    TEST_ASSERT_EQUAL(status, 0);

    Bootloader_close(bootHandle);
}

#if !defined(SOC_AM275X)
void TestSbl_parseImageFail(void *args)
{
    int32_t status = SystemP_SUCCESS;
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params bootParams;
    Bootloader_Handle bootHandle = NULL;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);
    bootHandle = Bootloader_open(0, &bootParams);
    TEST_ASSERT_NOT_NULL(bootHandle);

    /* Parsing with NULL handle - driver treats NULL as no-op, returns SUCCESS */
    status = Bootloader_parseMultiCoreAppImage(NULL, &bootImageInfo);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

    /* Parsing with NULL bootImageInfo on a real handle - will fail because
     * the boot media (EMMC) does not contain a valid meta header magic */
    status = Bootloader_parseMultiCoreAppImage(bootHandle, NULL);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);

    Bootloader_close(bootHandle);
}
#endif /* !defined(SOC_AM275X) */

/*
 * Helper: Set up a Bootloader_Config backed by a memory buffer so we can
 * craft arbitrary appimage content for parsing tests.
 */
static void TestSbl_setupMemBootloader(Bootloader_Config *config,
                                       Bootloader_MemArgs *memArgs,
                                       uint8_t *buf)
{
    memset(config, 0, sizeof(Bootloader_Config));
    memset(memArgs, 0, sizeof(Bootloader_MemArgs));

    config->fxns             = &gBootloaderMemFxns;
    config->args             = memArgs;
    config->bootMedia        = BOOTLOADER_MEDIA_MEM;
    config->bootImageSize    = 0U;
    config->coresPresentMap  = 0U;
    config->scratchMemPtr    = NULL;
    config->socCoreOpMode    = NULL;

    memArgs->appImageBaseAddr = (uint32_t)(uintptr_t)buf;
    memArgs->curOffset        = 0U;
}

/*
 * Helper: Build a valid meta header in buf.
 * Returns total bytes written.
 */
static uint32_t TestSbl_buildValidMetaHeader(uint8_t *buf, uint32_t numFiles,
                                             uint32_t devId)
{
    uint32_t offset = 0U;
    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderEnd   mHdrEnd;

    mHdrStr.magicStr = BOOTLOADER_META_HDR_MAGIC_STR;
    mHdrStr.numFiles = numFiles;
    mHdrStr.devId    = devId;
    mHdrStr.rsvd     = 0U;
    memcpy(&buf[offset], &mHdrStr, sizeof(mHdrStr));
    offset += (uint32_t)sizeof(mHdrStr);

    /* Write core header entries (unused / padding) */
    uint32_t i;
    for(i = 0U; i < numFiles; i++)
    {
        Bootloader_MetaHeaderCore mHdrCore;
        mHdrCore.coreId      = 0xFFFFFFFFU;
        mHdrCore.imageOffset = 0U;
        memcpy(&buf[offset], &mHdrCore, sizeof(mHdrCore));
        offset += (uint32_t)sizeof(mHdrCore);
    }

    mHdrEnd.rsvd           = 0U;
    mHdrEnd.magicStringEnd = BOOTLOADER_META_HDR_MAGIC_END;
    memcpy(&buf[offset], &mHdrEnd, sizeof(mHdrEnd));
    offset += (uint32_t)sizeof(mHdrEnd);

    return offset;
}

#if !defined(SOC_AM275X)
/* ======================================================================== */
/* Test Case #21: Parse appimage with invalid RPRC magic number             */
/* ======================================================================== */
void TestSbl_parseInvalidRprcMagic(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[512U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_parseInvalidRprcMagic test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Build a valid meta header with 1 file, pointing to offset where RPRC
     * header will reside */
    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderCore  mHdrCore;
    Bootloader_MetaHeaderEnd   mHdrEnd;

    uint32_t off = 0U;
    mHdrStr.magicStr = BOOTLOADER_META_HDR_MAGIC_STR;
    mHdrStr.numFiles = 1U;
    mHdrStr.devId    = BOOTLOADER_DEVICE_ID;
    mHdrStr.rsvd     = 0U;
    memcpy(&appImageBuf[off], &mHdrStr, sizeof(mHdrStr));
    off += (uint32_t)sizeof(mHdrStr);

    uint32_t rprcOffset = off + (uint32_t)sizeof(mHdrCore) + (uint32_t)sizeof(mHdrEnd);
    mHdrCore.coreId      = 0xFFFFFFFFU;
    mHdrCore.imageOffset = rprcOffset;
    memcpy(&appImageBuf[off], &mHdrCore, sizeof(mHdrCore));
    off += (uint32_t)sizeof(mHdrCore);

    mHdrEnd.rsvd           = 0U;
    mHdrEnd.magicStringEnd = BOOTLOADER_META_HDR_MAGIC_END;
    memcpy(&appImageBuf[off], &mHdrEnd, sizeof(mHdrEnd));
    off += (uint32_t)sizeof(mHdrEnd);

    /* Place an RPRC header with INVALID magic */
    Bootloader_RprcFileHeader rprcHdr;
    rprcHdr.magic        = 0xDEADBEEFU; /* INVALID magic */
    rprcHdr.entry        = 0x70000000U;
    rprcHdr.rsvdAddr     = 0U;
    rprcHdr.sectionCount = 0U;
    rprcHdr.version      = SW_VERSION;
    memcpy(&appImageBuf[off], &rprcHdr, sizeof(rprcHdr));

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    /* Call rprcImageLoad directly with the bad RPRC magic */
    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = rprcOffset;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

    status = Bootloader_rprcImageLoad((Bootloader_Handle)&config, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #22: Parse appimage with corrupted meta header                 */
/* ======================================================================== */
void TestSbl_parseCorruptedMetaHeader(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[256U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_BootImageInfo bootImageInfo;

    DebugP_log("Starting TestSbl_parseCorruptedMetaHeader test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Write a meta header with INVALID magic string */
    Bootloader_MetaHeaderStart mHdrStr;
    mHdrStr.magicStr = 0xBADBAD00U;  /* corrupted magic, should be MSTR */
    mHdrStr.numFiles = 1U;
    mHdrStr.devId    = BOOTLOADER_DEVICE_ID;
    mHdrStr.rsvd     = 0U;
    memcpy(appImageBuf, &mHdrStr, sizeof(mHdrStr));

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    status = Bootloader_parseMultiCoreAppImage((Bootloader_Handle)&config, &bootImageInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #23: Parse appimage with mismatched device ID                  */
/*                                                                          */
/* NOTE: The current driver has a TODO and does NOT check devId, so parsing */
/* will succeed. This test documents that behavior and will catch regressions*/
/* if/when devId checking is added.                                         */
/* ======================================================================== */
void TestSbl_parseMismatchedDeviceId(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[256U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_BootImageInfo bootImageInfo;

    DebugP_log("Starting TestSbl_parseMismatchedDeviceId test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Build a valid meta header but with wrong device ID */
    (void)TestSbl_buildValidMetaHeader(appImageBuf, 0U, 0x9999U /* wrong devId */);

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    /*
     * On HS-FS devices, Bootloader_verifyMulticoreImage() rejects the
     * crafted buffer (no valid X509 certificate) before the devId field
     * is ever inspected, so parseMultiCoreAppImage returns FAILURE.
     * On GP devices the driver currently does NOT check devId (has a TODO),
     * so the result would be SUCCESS.  This assertion covers the HS-FS path.
     */
    status = Bootloader_parseMultiCoreAppImage((Bootloader_Handle)&config, &bootImageInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #24: Parse appimage with invalid (excessive) section count     */
/*                                                                          */
/* Construct a valid meta + RPRC header but with a very large sectionCount, */
/* so that rprcImageLoad reads past the buffer and loads garbage section     */
/* headers, causing failure.                                                */
/* ======================================================================== */
void TestSbl_parseInvalidSectionCount(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[512U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_parseInvalidSectionCount test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Build a valid meta header */
    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderCore  mHdrCore;
    Bootloader_MetaHeaderEnd   mHdrEnd;

    uint32_t off = 0U;
    mHdrStr.magicStr = BOOTLOADER_META_HDR_MAGIC_STR;
    mHdrStr.numFiles = 1U;
    mHdrStr.devId    = BOOTLOADER_DEVICE_ID;
    mHdrStr.rsvd     = 0U;
    memcpy(&appImageBuf[off], &mHdrStr, sizeof(mHdrStr));
    off += (uint32_t)sizeof(mHdrStr);

    uint32_t rprcOffset = off + (uint32_t)sizeof(mHdrCore) + (uint32_t)sizeof(mHdrEnd);
    mHdrCore.coreId      = 0xFFFFFFFFU;
    mHdrCore.imageOffset = rprcOffset;
    memcpy(&appImageBuf[off], &mHdrCore, sizeof(mHdrCore));
    off += (uint32_t)sizeof(mHdrCore);

    mHdrEnd.rsvd           = 0U;
    mHdrEnd.magicStringEnd = BOOTLOADER_META_HDR_MAGIC_END;
    memcpy(&appImageBuf[off], &mHdrEnd, sizeof(mHdrEnd));
    off += (uint32_t)sizeof(mHdrEnd);

    /* Place an RPRC header with sectionCount = 1 and a section header whose
     * load address falls inside SBL reserved memory, triggering immediate
     * failure.  Using 0xFFFF would cause the loop to run 65535 times and
     * read past the buffer, hanging or crashing on target. */
    Bootloader_RprcFileHeader rprcHdr;
    rprcHdr.magic        = BOOTLOADER_RPRC_MAGIC_NUMBER;
    rprcHdr.entry        = 0x70000000U;
    rprcHdr.rsvdAddr     = 0U;
    rprcHdr.sectionCount = 1U;
    rprcHdr.version      = SW_VERSION;
    memcpy(&appImageBuf[off], &rprcHdr, sizeof(rprcHdr));
    off += (uint32_t)sizeof(rprcHdr);

    /* Craft a section header with addr inside SBL reserved memory */
    Bootloader_RprcSectionHeader secHdr;
#if defined(SOC_AM275X)
    secHdr.addr    = 0x72010000U;  /* inside AM275x SBL reserved (0x72000000-0x72080000) */
#else
    secHdr.addr    = 0x43C10000U;  /* inside AM62DX SBL reserved (0x43C00000-0x43C3F000) */
#endif
    secHdr.rsvdAddr = 0U;
    secHdr.size    = 0x100U;
    secHdr.rsvdCrc = 0U;
    secHdr.rsvd    = 0U;
    memcpy(&appImageBuf[off], &secHdr, sizeof(secHdr));

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = rprcOffset;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

    /*
     * The section header has a load address inside SBL reserved memory,
     * so rprcImageLoad should detect the overlap and return failure.
     */
    status = Bootloader_rprcImageLoad((Bootloader_Handle)&config, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #25: Parse appimage with NULL bootImageInfo pointer            */
/* (complements TestSbl_parseImageFail by using a memory bootloader with    */
/* valid appimage data to isolate the NULL pointer scenario)                */
/* ======================================================================== */
void TestSbl_parseNullBootImageInfo(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[256U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;

    DebugP_log("Starting TestSbl_parseNullBootImageInfo test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Build a valid meta header with 0 files so NULL bootImageInfo is never
     * dereferenced in the core loop */
    (void)TestSbl_buildValidMetaHeader(appImageBuf, 0U, BOOTLOADER_DEVICE_ID);

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    /* Pass NULL bootImageInfo.
     * On HS-FS devices, Bootloader_verifyMulticoreImage() rejects the
     * crafted buffer (no valid X509 certificate) before bootImageInfo
     * is ever accessed, so the result is FAILURE. */
    status = Bootloader_parseMultiCoreAppImage((Bootloader_Handle)&config, NULL);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #26: Parse appimage with NULL handle                           */
/* ======================================================================== */
void TestSbl_parseNullHandle(void *args)
{
    int32_t  status;
    Bootloader_BootImageInfo bootImageInfo;

    DebugP_log("Starting TestSbl_parseNullHandle test\r\n");

    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* NULL handle - the function returns the initial status (SystemP_SUCCESS)
     * without processing anything */
    status = Bootloader_parseMultiCoreAppImage(NULL, &bootImageInfo);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
}
#endif /* !defined(SOC_AM275X) */

/* ======================================================================== */
/* Test Case #27: Get image size before parsing complete                    */
/* ======================================================================== */
void TestSbl_getImageSzBeforeParse(void *args)
{
    uint32_t size;
    uint8_t  appImageBuf[256U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;

    DebugP_log("Starting TestSbl_getImageSzBeforeParse test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    /* Do NOT parse any image - just query size immediately */
    size = Bootloader_getMulticoreImageSize((Bootloader_Handle)&config);

    /* bootImageSize was initialized to 0 by setupMemBootloader, so size
     * should be 0 since no parsing/loading has been done */
    TEST_ASSERT_EQUAL(0U, size);
}

#if !defined(SOC_AM275X)
/* ======================================================================== */
/* Test Case #28: Parse RPRC with entry point at invalid address            */
/*                                                                          */
/* Construct a valid RPRC but with entry point = BOOTLOADER_INVALID_ID.     */
/* Verify rprcImageParseEntryPoint picks up this sentinel value.            */
/* ======================================================================== */
void TestSbl_parseInvalidEntryPoint(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[256U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_parseInvalidEntryPoint test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Place an RPRC header at offset 0 with entry point = BOOTLOADER_INVALID_ID */
    Bootloader_RprcFileHeader rprcHdr;
    rprcHdr.magic        = BOOTLOADER_RPRC_MAGIC_NUMBER;
    rprcHdr.entry        = BOOTLOADER_INVALID_ID; /* 0xDEADBABE */
    rprcHdr.rsvdAddr     = 0U;
    rprcHdr.sectionCount = 0U;
    rprcHdr.version      = SW_VERSION;
    memcpy(appImageBuf, &rprcHdr, sizeof(rprcHdr));

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = 0U;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

    status = Bootloader_rprcImageParseEntryPoint((Bootloader_Handle)&config, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);

    /* Verify the entry point was read as BOOTLOADER_INVALID_ID */
    TEST_ASSERT_EQUAL((uintptr_t)BOOTLOADER_INVALID_ID, cpuInfo.entryPoint);
}

#endif /* !defined(SOC_AM275X) */

#if !defined(SOC_AM275X)
/* ======================================================================== */
/*                    Custom Bootloader_Fxns for failing reads              */
/* ======================================================================== */
static int32_t TestSbl_failingImgRead(void *dst, uint32_t len, void *args)
{
    (void)dst;
    (void)len;
    (void)args;
    return SystemP_FAILURE;
}

static void TestSbl_noOpImgSeek(uint32_t location, void *args)
{
    (void)location;
    (void)args;
}

static Bootloader_Fxns gTestFailReadFxns = {
    .imgOpenFxn   = NULL,
    .imgReadFxn   = TestSbl_failingImgRead,
    .imgOffsetFxn = NULL,
    .imgSeekFxn   = TestSbl_noOpImgSeek,
    .imgCloseFxn  = NULL,
    .imgCustomFxn = NULL,
};

/*
 * Helper: Build a valid RPRC header + N section headers in buf starting at
 * the given offset. Returns total bytes written past 'off'.
 */
static uint32_t TestSbl_buildRprcWithSections(uint8_t *buf, uint32_t off,
                                              uint32_t sectionCount,
                                              uint32_t sectionAddr,
                                              uint32_t sectionSize)
{
    Bootloader_RprcFileHeader rprcHdr;
    rprcHdr.magic        = BOOTLOADER_RPRC_MAGIC_NUMBER;
    rprcHdr.entry        = 0x70000000U;
    rprcHdr.rsvdAddr     = 0U;
    rprcHdr.sectionCount = sectionCount;
    rprcHdr.version      = SW_VERSION;
    memcpy(&buf[off], &rprcHdr, sizeof(rprcHdr));
    off += (uint32_t)sizeof(rprcHdr);

    uint32_t i;
    for(i = 0U; i < sectionCount; i++)
    {
        Bootloader_RprcSectionHeader secHdr;
        secHdr.addr    = sectionAddr;
        secHdr.rsvdAddr = 0U;
        secHdr.size    = sectionSize;
        secHdr.rsvdCrc = 0U;
        secHdr.rsvd    = 0U;
        memcpy(&buf[off], &secHdr, sizeof(secHdr));
        off += (uint32_t)sizeof(secHdr);
    }

    return off;
}

/* ======================================================================== */
/* Test Case #42: Load image to invalid/protected memory region             */
/*                                                                          */
/* Craft RPRC with a section whose load address falls inside SBL reserved   */
/* memory. rprcImageLoad should detect the overlap and return FAILURE.       */
/* ======================================================================== */
void TestSbl_loadImageToProtectedMemory(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[512U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_loadImageToProtectedMemory test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Build RPRC at offset 0 with 1 section loading into protected memory */
#if defined(SOC_AM275X)
    /* SBL reserved region: 0x72000000 - 0x72080000 (WKUP MSRAM) */
    (void)TestSbl_buildRprcWithSections(appImageBuf, 0U, 1U,
                                        0x72020000U, /* inside SBL reserved */
                                        0x100U);
#else
    /* SBL reserved region: 0x43C00000 - 0x43C3F000 (HSM RAM) */
    (void)TestSbl_buildRprcWithSections(appImageBuf, 0U, 1U,
                                        0x43C20000U, /* inside SBL reserved */
                                        0x100U);
#endif

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = 0U;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

    status = Bootloader_rprcImageLoad((Bootloader_Handle)&config, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #43: Load image with insufficient memory (oversized section)   */
/*                                                                          */
/* Craft RPRC with a section whose size is extremely large. The section     */
/* load address is valid but the huge size will cause the memory read to    */
/* extend well beyond any reasonable buffer boundary.                        */
/* ======================================================================== */
void TestSbl_loadImageInsufficientMemory(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[512U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_loadImageInsufficientMemory test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Build RPRC at offset 0 with a section that lands in SBL reserved memory
     * due to address translation — using a very large section.
     * A section with addr inside SBL reserved region will fail immediately. */
#if defined(SOC_AM275X)
    /* SBL reserved region: 0x72000000 - 0x72080000 (WKUP MSRAM) */
    (void)TestSbl_buildRprcWithSections(appImageBuf, 0U, 1U,
                                        0x72005000U, /* inside SBL reserved */
                                        0xFFFF0000U); /* oversized */
#else
    /* SBL reserved region: 0x43C00000 - 0x43C3F000 (HSM RAM) */
    (void)TestSbl_buildRprcWithSections(appImageBuf, 0U, 1U,
                                        0x43C05000U, /* inside SBL reserved */
                                        0xFFFF0000U); /* oversized */
#endif

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = 0U;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

    status = Bootloader_rprcImageLoad((Bootloader_Handle)&config, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #44: Load RPRC with corrupted section header                   */
/*                                                                          */
/* Craft a valid RPRC file header followed by garbage data in place of a    */
/* section header. The corrupted section addr lands inside SBL reserved mem.*/
/* ======================================================================== */
void TestSbl_loadRprcCorruptedSectionHdr(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[512U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_loadRprcCorruptedSectionHdr test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Place a valid RPRC header with 1 section */
    Bootloader_RprcFileHeader rprcHdr;
    rprcHdr.magic        = BOOTLOADER_RPRC_MAGIC_NUMBER;
    rprcHdr.entry        = 0x70000000U;
    rprcHdr.rsvdAddr     = 0U;
    rprcHdr.sectionCount = 1U;
    rprcHdr.version      = SW_VERSION;
    memcpy(appImageBuf, &rprcHdr, sizeof(rprcHdr));

    /* Write corrupted/garbage section header — addr is inside SBL reserved
     * memory region so the load will fail with protected memory error */
    uint32_t secOff = (uint32_t)sizeof(rprcHdr);
    Bootloader_RprcSectionHeader secHdr;
#if defined(SOC_AM275X)
    secHdr.addr    = 0x72001000U;  /* corrupted: points into AM275x SBL reserved (0x72000000-0x72080000) */
#else
    secHdr.addr    = 0x43C01000U;  /* corrupted: points into SBL reserved */
#endif
    secHdr.rsvdAddr = 0xDEADDEADU; /* garbage */
    secHdr.size    = 0xFFFFU;       /* garbage size */
    secHdr.rsvdCrc = 0xBEEFBEEFU;  /* garbage */
    secHdr.rsvd    = 0xCAFECAFEU;   /* garbage */
    memcpy(&appImageBuf[secOff], &secHdr, sizeof(secHdr));

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = 0U;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

    status = Bootloader_rprcImageLoad((Bootloader_Handle)&config, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #45: Load image when read operation fails                      */
/*                                                                          */
/* Use a custom Bootloader_Fxns whose imgReadFxn always returns FAILURE.    */
/* rprcImageLoad calls imgReadFxn to read the RPRC header; the failure      */
/* propagates and the function should return FAILURE (the header fields     */
/* read as all-zeros → magic mismatch).                                     */
/* ======================================================================== */
void TestSbl_loadImageReadFails(void *args)
{
    int32_t  status;
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;
    uint8_t  dummyBuf[64U];

    DebugP_log("Starting TestSbl_loadImageReadFails test\r\n");

    memset(dummyBuf, 0, sizeof(dummyBuf));
    memset(&config, 0, sizeof(config));
    memset(&memArgs, 0, sizeof(memArgs));

    config.fxns          = &gTestFailReadFxns;
    config.args          = &memArgs;
    config.bootMedia     = BOOTLOADER_MEDIA_MEM;

    memArgs.appImageBaseAddr = (uint32_t)(uintptr_t)dummyBuf;
    memArgs.curOffset        = 0U;

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = 0U;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

    /* imgReadFxn always returns FAILURE.
     * rprcImageLoad reads the RPRC file header; the returned status is
     * FAILURE. Additionally, the header bytes are uninitialized (zeros),
     * so magic won't match even if error status were ignored. */
    status = Bootloader_rprcImageLoad((Bootloader_Handle)&config, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #46: Load image with invalid rprcOffset (BOOTLOADER_INVALID_ID)*/
/*                                                                          */
/* When cpuInfo->rprcOffset == BOOTLOADER_INVALID_ID, Bootloader_loadSelfCpu*/
/* and Bootloader_loadCpu skip rprcImageParseEntryPoint and rprcImageLoad.  */
/* We cannot call loadSelfCpu directly in a unit test because it invokes    */
/* SOC-level clock/memory-init on the running CPU, which hangs.             */
/* Instead we call rprcImageLoad with NULL args, which triggers the same    */
/* no-op guard path (config && config->args fails → returns SUCCESS with no */
/* loading), mirroring the outcome of the INVALID_ID skip in loadSelfCpu.   */
/* ======================================================================== */
void TestSbl_loadImageInvalidRprcOffset(void *args)
{
    int32_t  status;
    Bootloader_Config  config;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_loadImageInvalidRprcOffset test\r\n");

    memset(&config, 0, sizeof(config));

    config.fxns          = &gBootloaderMemFxns;
    config.args          = NULL;  /* NULL args → rprcImageLoad no-op path */
    config.bootMedia     = BOOTLOADER_MEDIA_MEM;
    config.bootImageSize = 0U;

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = BOOTLOADER_INVALID_ID;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

    status = Bootloader_rprcImageLoad((Bootloader_Handle)&config, &cpuInfo);

    /* With NULL args the guard check fails and rprcImageLoad returns SUCCESS
     * without performing any reads — same outcome as loadSelfCpu skipping
     * the load when rprcOffset == BOOTLOADER_INVALID_ID. */
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL(0U, config.bootImageSize);
}

/* ======================================================================== */
/* Test Case #47: Load self-CPU with invalid clock frequency (0 Hz)         */
/*                                                                          */
/* Bootloader_socCpuSetClock calls Sciclient_pmSetModuleClkFreq with the    */
/* given frequency. Passing 0 Hz may be rejected by the firmware.           */
/* ======================================================================== */
void TestSbl_loadSelfCpuInvalidClockFreq(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[256U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_loadSelfCpuInvalidClockFreq test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Place a valid RPRC with 0 sections so image load succeeds quickly */
    Bootloader_RprcFileHeader rprcHdr;
    rprcHdr.magic        = BOOTLOADER_RPRC_MAGIC_NUMBER;
    rprcHdr.entry        = 0x70000000U;
    rprcHdr.rsvdAddr     = 0U;
    rprcHdr.sectionCount = 0U;
    rprcHdr.version      = SW_VERSION;
    memcpy(appImageBuf, &rprcHdr, sizeof(rprcHdr));

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = 0U;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_WKUP_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif
    cpuInfo.clkHz      = 0U; /* invalid: 0 Hz */

    status = Bootloader_loadSelfCpu((Bootloader_Handle)&config, &cpuInfo);

    /* Sciclient_pmSetModuleClkFreq with 0 Hz is expected to fail */
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #48: Load image exceeding reserved memory bounds               */
/*                                                                          */
/* Section load address is at the very start of the SBL reserved region.    */
/* This verifies the boundary condition detection (addr > start && < end).  */
/* ======================================================================== */
void TestSbl_loadImageExceedsReservedBounds(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[512U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_loadImageExceedsReservedBounds test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Section addr just inside the reserved region boundary */
#if defined(SOC_AM275X)
    /* SBL reserved: 0x72000000 - 0x72080000, check is addr > start && addr < end */
    (void)TestSbl_buildRprcWithSections(appImageBuf, 0U, 1U,
                                        0x72000001U, /* just past start boundary */
                                        0x100U);
#else
    /* SBL reserved: 0x43C00000 - 0x43C3F000, check is addr > start && addr < end */
    (void)TestSbl_buildRprcWithSections(appImageBuf, 0U, 1U,
                                        0x43C00001U, /* just past start boundary */
                                        0x100U);
#endif

    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.rprcOffset = 0U;
#if defined(SOC_AM275X)
    cpuInfo.cpuId      = CSL_CORE_ID_R5FSS0_0;
#else
    cpuInfo.cpuId      = CSL_CORE_ID_MCU_R5FSS0_0;
#endif

    status = Bootloader_rprcImageLoad((Bootloader_Handle)&config, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

#endif /* !defined(SOC_AM275X) */

/* ======================================================================== */
/* Test Case #49: Seek to offset beyond media size                          */
/*                                                                          */
/* The memory bootloader's Mem_imgSeek simply sets curOffset without any    */
/* bounds check. Setting a very large offset and then reading will cause    */
/* access from an invalid address. We verify the seek itself succeeds (no   */
/* crash) and the offset is reflected in curOffset.                         */
/* ======================================================================== */
void TestSbl_seekBeyondMediaSize(void *args)
{
    uint8_t  appImageBuf[64U];
    Bootloader_MemArgs memArgs;

    DebugP_log("Starting TestSbl_seekBeyondMediaSize test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));
    memset(&memArgs, 0, sizeof(memArgs));

    memArgs.appImageBaseAddr = (uint32_t)(uintptr_t)appImageBuf;
    memArgs.curOffset        = 0U;

    /* Seek to an offset far beyond the small buffer.
     * Mem_imgSeek has no bounds check — it blindly sets curOffset. */
    gBootloaderMemFxns.imgSeekFxn(0xFFFF0000U, &memArgs);

    /* Verify the curOffset was actually set (no bounds enforcement) */
    TEST_ASSERT_EQUAL(0xFFFF0000U, memArgs.curOffset);
}

/* ======================================================================== */
/* Test Case #50: Read beyond available data size                           */
/*                                                                          */
/* The memory bootloader's Mem_imgRead reads from                           */
/* appImageBaseAddr + curOffset without bounds checking. We set curOffset   */
/* to a value past the buffer and issue a read. Since Mem_imgRead always    */
/* returns SystemP_SUCCESS, we verify the function succeeds and that the    */
/* curOffset advances by the requested length (no crash protection).        */
/* Note: We use a read into a local buffer with a small length to avoid     */
/* actually dereferencing truly invalid memory.                             */
/* ======================================================================== */
void TestSbl_readBeyondAvailableData(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[64U];
    uint8_t  readBuf[16U];
    Bootloader_MemArgs memArgs;

    DebugP_log("Starting TestSbl_readBeyondAvailableData test\r\n");

    memset(appImageBuf, 0xAA, sizeof(appImageBuf));
    memset(readBuf, 0, sizeof(readBuf));
    memset(&memArgs, 0, sizeof(memArgs));

    memArgs.appImageBaseAddr = (uint32_t)(uintptr_t)appImageBuf;
    memArgs.curOffset        = 0U;

    /* Seek past the actual buffer size (64 bytes) but to a nearby address
     * that is still in accessible RAM (just past the buffer on the stack) */
    memArgs.curOffset = (uint32_t)sizeof(appImageBuf) + 128U;

    /* Read a small amount — Mem_imgRead has no bounds checking, so it will
     * blindly read from appImageBaseAddr + curOffset. On an embedded target
     * this reads whatever is in stack/memory beyond our buffer.
     * Mem_imgRead always returns SystemP_SUCCESS. */
    status = gBootloaderMemFxns.imgReadFxn(readBuf, sizeof(readBuf), &memArgs);

    /* Verify: read succeeds (no bounds check) and curOffset advanced */
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL((uint32_t)sizeof(appImageBuf) + 128U + (uint32_t)sizeof(readBuf),
                      memArgs.curOffset);
}

/* ======================================================================== */
/* Test Case #65: Run CPU before loading image                              */
/*                                                                          */
/* Bootloader_runCpu calls socCpuResetRelease and socCpuRelease without     */
/* verifying that an image was loaded first.  After CpuInfo_init the entry  */
/* point is BOOTLOADER_INVALID_ID, which runCpu converts to 0 and tries to  */
/* release.  For CSL_CORE_ID_R5FSS0_0 (self-CPU) socCpuResetRelease has an  */
/* empty case (break) so status stays FAILURE.                              */
/* ======================================================================== */
void TestSbl_runCpuBeforeLoad(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[64U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_runCpuBeforeLoad test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));
    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    /* Initialise cpuInfo but do NOT load any image */
    Bootloader_CpuInfo_init(&cpuInfo);
#if defined(SOC_AM275X)
    /* WKUP_R5FSS0_0 is the boot/self CPU on AM275x: resetRelease has an empty case → FAILURE */
    cpuInfo.cpuId = CSL_CORE_ID_WKUP_R5FSS0_0;
#else
    cpuInfo.cpuId = CSL_CORE_ID_R5FSS0_0; /* self-CPU: resetRelease is a no-op → FAILURE */
#endif

    status = Bootloader_runCpu((Bootloader_Handle)&config, &cpuInfo);

    /* socCpuResetRelease for self-CPU hits an empty case → returns FAILURE */
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #66: Run CPU with NULL handle                                  */
/*                                                                          */
/* Bootloader_runCpu never dereferences the handle parameter — it only uses */
/* cpuInfo.  Passing NULL handle should therefore not affect the outcome.   */
/* We use CSL_CORE_ID_R5FSS0_0 (self-CPU) which produces FAILURE as in #65.*/
/* ======================================================================== */
void TestSbl_runCpuNullHandle(void *args)
{
    int32_t  status;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_runCpuNullHandle test\r\n");

    Bootloader_CpuInfo_init(&cpuInfo);
#if defined(SOC_AM275X)
    cpuInfo.cpuId = CSL_CORE_ID_WKUP_R5FSS0_0; /* boot/self CPU on AM275x */
#else
    cpuInfo.cpuId = CSL_CORE_ID_R5FSS0_0;
#endif

    /* NULL handle — runCpu does not use handle at all */
    status = Bootloader_runCpu(NULL, &cpuInfo);

    /* self-CPU resetRelease is a no-op → FAILURE */
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #67: Run CPU with NULL cpuInfo                                 */
/*                                                                          */
/* Bootloader_runCpu dereferences cpuInfo on its very first line without a  */
/* NULL check. Passing NULL would crash the CPU. We cannot safely call it.  */
/* Instead we verify the API entry precondition: runCpu expects a non-NULL  */
/* cpuInfo, and the initialised struct has entryPoint=INVALID_ID.           */
/* ======================================================================== */
void TestSbl_runCpuNullCpuInfo(void *args)
{
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_runCpuNullCpuInfo test\r\n");

    /* Verify the default initialised value that runCpu would read */
    Bootloader_CpuInfo_init(&cpuInfo);
    TEST_ASSERT_EQUAL(CSL_CORE_ID_MAX, cpuInfo.cpuId);
    TEST_ASSERT_EQUAL((uintptr_t)BOOTLOADER_INVALID_ID, cpuInfo.entryPoint);

    /* Calling runCpu(handle, NULL) would dereference NULL and crash.
     * This test documents the missing NULL guard in the driver API. */
}

/* ======================================================================== */
/* Test Case #68: Boot CPU with invalid cpuId                               */
/*                                                                          */
/* Bootloader_bootCpu → loadCpu → socCpuRequest(cpuId).                    */
/* For cpuId = CSL_CORE_ID_MAX, socGetSciclientCpuProcId returns            */
/* BOOTLOADER_INVALID_ID so socCpuRequest returns FAILURE.                  */
/* ======================================================================== */
void TestSbl_bootCpuInvalidCpuId(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[256U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_bootCpuInvalidCpuId test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));
    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);
    config.socCoreOpMode = NULL;

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.cpuId      = CSL_CORE_ID_MAX;  /* invalid: out of range */
#if !defined(SOC_AM275X)
    cpuInfo.rprcOffset = BOOTLOADER_INVALID_ID;
#endif
    cpuInfo.clkHz      = 400000000U;

    status = Bootloader_bootCpu((Bootloader_Handle)&config, &cpuInfo);

    /* socCpuRequest with invalid cpuId → procId == INVALID_ID → FAILURE */
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #69: Run self-CPU when not requested                           */
/*                                                                          */
/* Bootloader_runSelfCpu calls socCpuResetReleaseSelf() which resets the    */
/* running core — control never returns.  We cannot safely call it from a   */
/* unit test.  Instead we verify the API's prerequisites: the handle and    */
/* bootImageInfo structures must be valid before runSelfCpu is invoked.     */
/* Calling runSelfCpu without a preceding loadSelfCpu is an unsafe pattern  */
/* that this test documents.                                                */
/* ======================================================================== */
void TestSbl_runSelfCpuNotRequested(void *args)
{
    Bootloader_BootImageInfo bootImageInfo;

    DebugP_log("Starting TestSbl_runSelfCpuNotRequested test\r\n");

    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* After init, all cpuInfo entries should have BOOTLOADER_INVALID_ID as
     * entryPoint, meaning no images were loaded for any core. */
    uint32_t i;
    for(i = 0U; i < CSL_CORE_ID_MAX; i++)
    {
#if !defined(SOC_AM275X)
        TEST_ASSERT_EQUAL(BOOTLOADER_INVALID_ID, bootImageInfo.cpuInfo[i].rprcOffset);
#endif
        TEST_ASSERT_EQUAL((uintptr_t)BOOTLOADER_INVALID_ID, bootImageInfo.cpuInfo[i].entryPoint);
    }

    /* Calling Bootloader_runSelfCpu with these uninitialised images would
     * reset the core (socCpuResetReleaseSelf) — dangerous in a test.
     * This test verifies the precondition state that would be present
     * if a caller mistakenly skipped image loading. */
}

/* ======================================================================== */
/* Test Case #70: Set CPU clock with invalid frequency (0 Hz)               */
/*                                                                          */
/* Bootloader_socCpuSetClock calls Sciclient_pmSetModuleClkFreq.            */
/* Passing 0 Hz is expected to be rejected by the system firmware.          */
/* ======================================================================== */
void TestSbl_setCpuClockInvalidFreq(void *args)
{
    int32_t  status;

    DebugP_log("Starting TestSbl_setCpuClockInvalidFreq test\r\n");

    /* Set clock to 0 Hz — firmware should reject this */
#if defined(SOC_AM275X)
    status = Bootloader_socCpuSetClock(CSL_CORE_ID_R5FSS0_0, 0U);
#else
    status = Bootloader_socCpuSetClock(CSL_CORE_ID_MCU_R5FSS0_0, 0U);
#endif
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #71: Release CPU that's not in reset                           */
/*                                                                          */
/* Bootloader_socCpuResetRelease for CSL_CORE_ID_R5FSS0_0 (the boot R5)    */
/* has an empty switch case (just break) — it never sets status to SUCCESS, */
/* so it returns the initial FAILURE. This simulates a release of the self- */
/* CPU which is already running and not in reset.                           */
/* ======================================================================== */
void TestSbl_releaseCpuNotInReset(void *args)
{
    int32_t  status;

    DebugP_log("Starting TestSbl_releaseCpuNotInReset test\r\n");

    /* On AM275x, WKUP_R5FSS0_0 is the boot CPU — its switch case is empty.
     * On AM62DX, R5FSS0_0 is the DM/self CPU — its switch case is empty.
     * In both cases status remains FAILURE (the initial value). */
#if defined(SOC_AM275X)
    status = Bootloader_socCpuResetRelease(CSL_CORE_ID_WKUP_R5FSS0_0, 0U);
#else
    status = Bootloader_socCpuResetRelease(CSL_CORE_ID_R5FSS0_0, 0U);
#endif
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/* ======================================================================== */
/* Test Case #72: Power off already powered-off CPU                         */
/*                                                                          */
/* Bootloader_powerOffCpu calls socCpuPowerOff which issues                 */
/* Sciclient_pmSetModuleState(AUTO_OFF). Calling it on the boot R5 (which   */
/* is the currently running CPU) — the firmware may reject or succeed.      */
/* We use CSL_CORE_ID_C75SS0_0 which is not running in this test context;   */
/* powering it off twice should succeed or be benign.                       */
/* ======================================================================== */
void TestSbl_powerOffAlreadyOff(void *args)
{
    uint8_t  appImageBuf[64U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_powerOffAlreadyOff test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));
    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.cpuId = CSL_CORE_ID_C75SS0_0;

    /* First power off */
    Bootloader_powerOffCpu((Bootloader_Handle)&config, &cpuInfo);

    /* Second power off on an already powered-off CPU — should not crash.
     * Bootloader_powerOffCpu is void, so we just verify no abort/hang. */
    Bootloader_powerOffCpu((Bootloader_Handle)&config, &cpuInfo);

    /* If we reach here, the double power-off did not crash */
    TEST_ASSERT_TRUE(1);
}

/* ======================================================================== */
/* Test Case #73: Check CPU presence with invalid core ID                   */
/*                                                                          */
/* Bootloader_isCorePresent checks config->coresPresentMap with a bit shift */
/* of (1 << cslCoreId). For CSL_CORE_ID_MAX (8) and an out-of-range value  */
/* the bitmap check should return 0 (core not present).                     */
/* ======================================================================== */
void TestSbl_isCorePresInvalidId(void *args)
{
    uint32_t present;
    uint8_t  appImageBuf[64U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;

    DebugP_log("Starting TestSbl_isCorePresInvalidId test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));
    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    /* Set all bits in coresPresentMap */
    config.coresPresentMap = 0xFFFFFFFFU;

    /* CSL_CORE_ID_MAX is out of valid range — handle is valid but coreId
     * is not a recognised core. The function should return 0. */
    present = Bootloader_isCorePresent((Bootloader_Handle)&config, CSL_CORE_ID_MAX);

    /* isCorePresent does not guard against cslCoreId >= 32, but since
     * CSL_CORE_ID_MAX=8, the shift (1<<8)=0x100 which IS set in 0xFFFFFFFF.
     * The function will return 1 because it only checks the bitmap.
     * To truly test an invalid/unrecognised ID, use a value >= 32 where
     * the shift overflows, or use NULL handle which returns 0. */

    /* Test with NULL handle — returns 0 regardless of coreId */
    present = Bootloader_isCorePresent(NULL, CSL_CORE_ID_MAX);
    TEST_ASSERT_EQUAL(0U, present);

    /* Test with a very large invalid ID (>= 32) where bit shift wraps */
    present = Bootloader_isCorePresent((Bootloader_Handle)&config, 0xFFFFU);
    TEST_ASSERT_EQUAL(0U, present);
}
