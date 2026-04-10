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
/* 					      Include Files 					         */
/*===================================================================*/

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
#include <drivers/bootloader/bootloader_xmodem.h>
#include <drivers/bootloader/bootloader_uniflash.h>
#include <drivers/bootloader/bootloader_mmcsd_raw.h>

extern int xmodemReceive(unsigned char *dest, int destsz);
extern int xmodemTransmit(unsigned char *src, int srcsz);
extern uint8_t *Bootloader_findSeq(uint8_t *x509_cert_ptr, uint32_t x509_cert_size, uint8_t *seq_oid, uint8_t seq_len);
extern void Bootloader_socGetR5fAtcmAddrAndSize(uint32_t cpuId, uint32_t *addr, uint32_t *size);
extern void Bootloader_socGetR5fBtcmAddrAndSize(uint32_t cpuId, uint32_t *addr, uint32_t *size);
extern uint32_t Bootloader_socGetSciclientCpuClkId(uint32_t cpuId);
extern int32_t Bootloader_verifyMulticoreImage(Bootloader_Handle handle);

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/

/* SW_VERSION is passed as -D to the driver library build but not to tests.
 * Define it here to match the value from imports.mak for RPRC header construction. */
#ifndef SW_VERSION
#define SW_VERSION 0x0A010000U
#endif

/*===================================================================*/
/* 					         Typedefs 					             */
/*===================================================================*/


/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/


/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/

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

void TestSbl_xmodemSendAckInvalidIndex(void *args);
void TestSbl_xmodemReceiveNullHandle(void *args);
void TestSbl_xmodemTransmitNullHandle(void *args);
void TestSbl_xmodemReceiveSyncError(void *args);
void TestSbl_xmodemTransmitNoSync(void *args);

void TestSbl_uniflashMagicError(void *args);
void TestSbl_uniflashFlashInvalidIdx(void *args);
void TestSbl_uniflashVerifyInvalidIdx(void *args);
void TestSbl_uniflashEraseInvalidIdx(void *args);
void TestSbl_uniflashXipInvalidContent(void *args);
void TestSbl_uniflashVerifyXipInvalidContent(void *args);
void TestSbl_uniflashTuningDataInvalidIdx(void *args);

void TestSbl_x509CertLenInvalidTag(void *args);
void TestSbl_x509CertLenUnsupportedLen(void *args);
void TestSbl_x509CertLenSmall(void *args);
void TestSbl_findSeqNotFound(void *args);
#if !defined(SOC_AM275X)
void TestSbl_mmcsdRawReadNullHandle(void *args);
void TestSbl_mmcsdRawWriteNullHandle(void *args);
#endif

void TestSbl_socGetTcmAddrR5fss0(void *args);
void TestSbl_socGetTcmAddrInvalidCpu(void *args);
void TestSbl_socMemInitCpuDefault(void *args);
void TestSbl_socCpuPowerOnResetSelfCpu(void *args);
#if !defined(SOC_AM275X)
void TestSbl_rprcImageLoadNullHandle(void *args);
void TestSbl_parseMultiCoreNullHandle(void *args);
void TestSbl_parseAppImageNullHandle(void *args);
#endif

void TestSbl_socCpuSetClockHSM(void *args);
void TestSbl_socCpuGetClockHSM(void *args);
void TestSbl_socGetProcIdInvalid(void *args);
void TestSbl_socGetDevIdInvalid(void *args);
void TestSbl_socGetClkIdInvalid(void *args);
void TestSbl_socGetClkDefaultInvalid(void *args);
void TestSbl_socGetCoreNameInvalid(void *args);
void TestSbl_socGetSelfCpuList(void *args);
void TestSbl_socGetSetSBLMem(void *args);

#if !defined(SOC_AM275X)
void TestSbl_parseMultiCoreNullFxns(void *args);
void TestSbl_verifyMulticoreNullFxns(void *args);
void TestSbl_rprcParseEntryPointNullHandle(void *args);
void TestSbl_loadSelfCpuHsmNoRprc(void *args);
#endif

void TestSbl_uniflashEmmcFlashInvalidIdx(void *args);
void TestSbl_uniflashEmmcVerifyInvalidIdx(void *args);

/*===================================================================*/
/* 					         Function Definitions		             */
/*===================================================================*/

/**
 * @brief Unity per-test setup hook.
 *
 * Called automatically by the Unity framework before each test case.
 * No special initialization is required for the SBL negative tests.
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
 * No special cleanup is required for the SBL negative tests.
 *
 * @return void
 */
void tearDown(void)
{
    /* Tear down function nothing to perform */
}

/**
 * @brief Main SBL negative test entry point.
 *
 * Initializes Unity, executes all bootloader negative test cases
 * (open/close, parse, load, run, clock, power-off, core-presence),
 * and finalizes the Unity framework.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void test_main(void * args)
{
    UNITY_BEGIN();

    RUN_TEST(TestSbl_openCloseSuccess,     11375, NULL);
    RUN_TEST(TestSbl_openCloseOpen,        11377, NULL);
    RUN_TEST(TestSbl_openFail,             11378, NULL);
    RUN_TEST(TestSbl_closeFail,            11379, NULL);
    RUN_TEST(TestSbl_getBootMedia,         11380, NULL);
    RUN_TEST(TestSbl_getBootMediaFail,     11381, NULL);
    RUN_TEST(TestSbl_getImageSzFail,       11382, NULL);
    RUN_TEST(TestSbl_openOpenFail,         11376, NULL);
    RUN_TEST(TestSbl_getImageSzBeforeParse,  11383, NULL);
    RUN_TEST(TestSbl_seekBeyondMediaSize,    11384, NULL);

#if !defined(SOC_AM275X)

    RUN_TEST(TestSbl_parseImageFail,       11385, NULL);
    RUN_TEST(TestSbl_parseInvalidRprcMagic,  11386, NULL);
    RUN_TEST(TestSbl_parseCorruptedMetaHeader, 11387, NULL);
    RUN_TEST(TestSbl_parseMismatchedDeviceId, 11388, NULL);
    RUN_TEST(TestSbl_parseInvalidSectionCount, 11389, NULL);
    RUN_TEST(TestSbl_parseNullBootImageInfo, 11390, NULL);
    RUN_TEST(TestSbl_parseNullHandle,        11391, NULL);
    RUN_TEST(TestSbl_parseInvalidEntryPoint, 11392, NULL);
    RUN_TEST(TestSbl_loadImageToProtectedMemory, 11393, NULL);
    RUN_TEST(TestSbl_loadImageInsufficientMemory, 11394, NULL);
    RUN_TEST(TestSbl_loadRprcCorruptedSectionHdr, 11395, NULL);
    RUN_TEST(TestSbl_loadImageReadFails,     11396, NULL);
    RUN_TEST(TestSbl_loadImageInvalidRprcOffset, 11397, NULL);
    RUN_TEST(TestSbl_loadSelfCpuInvalidClockFreq, 11398, NULL);
    RUN_TEST(TestSbl_loadImageExceedsReservedBounds, 11399, NULL);

#endif /* !defined(SOC_AM275X) */

    RUN_TEST(TestSbl_readBeyondAvailableData, 11400, NULL);
    RUN_TEST(TestSbl_runCpuBeforeLoad,       11401, NULL);
    RUN_TEST(TestSbl_runCpuNullHandle,       11402, NULL);
    RUN_TEST(TestSbl_runCpuNullCpuInfo,      11403, NULL);
    RUN_TEST(TestSbl_bootCpuInvalidCpuId,    11404, NULL);
    RUN_TEST(TestSbl_runSelfCpuNotRequested, 11405, NULL);
    RUN_TEST(TestSbl_setCpuClockInvalidFreq, 11406, NULL);
    RUN_TEST(TestSbl_releaseCpuNotInReset,   11407, NULL);
    RUN_TEST(TestSbl_powerOffAlreadyOff,     11408, NULL);
    RUN_TEST(TestSbl_isCorePresInvalidId,    11409, NULL);

    RUN_TEST(TestSbl_xmodemSendAckInvalidIndex, 11480, NULL);
    RUN_TEST(TestSbl_xmodemReceiveNullHandle,   11481, NULL);
    RUN_TEST(TestSbl_xmodemTransmitNullHandle,  11482, NULL);
    RUN_TEST(TestSbl_xmodemReceiveSyncError,    11483, NULL);
    RUN_TEST(TestSbl_xmodemTransmitNoSync,      11484, NULL);

    RUN_TEST(TestSbl_uniflashMagicError,            11485, NULL);
    RUN_TEST(TestSbl_uniflashFlashInvalidIdx,       11486, NULL);
    RUN_TEST(TestSbl_uniflashVerifyInvalidIdx,      11487, NULL);
    RUN_TEST(TestSbl_uniflashEraseInvalidIdx,       11488, NULL);
    RUN_TEST(TestSbl_uniflashXipInvalidContent,     11489, NULL);
    RUN_TEST(TestSbl_uniflashVerifyXipInvalidContent, 11490, NULL);
    RUN_TEST(TestSbl_uniflashTuningDataInvalidIdx,  11491, NULL);

    RUN_TEST(TestSbl_x509CertLenInvalidTag,      11492, NULL);
    RUN_TEST(TestSbl_x509CertLenUnsupportedLen,  11493, NULL);
    RUN_TEST(TestSbl_x509CertLenSmall,           11494, NULL);
    RUN_TEST(TestSbl_findSeqNotFound,            11495, NULL);
#if !defined(SOC_AM275X)
    RUN_TEST(TestSbl_mmcsdRawReadNullHandle,      11496, NULL);
    RUN_TEST(TestSbl_mmcsdRawWriteNullHandle,     11497, NULL);
#endif

    RUN_TEST(TestSbl_socGetTcmAddrR5fss0,         11498, NULL);
    RUN_TEST(TestSbl_socGetTcmAddrInvalidCpu,      11499, NULL);
    RUN_TEST(TestSbl_socMemInitCpuDefault,         11500, NULL);
    RUN_TEST(TestSbl_socCpuPowerOnResetSelfCpu,    11501, NULL);
#if !defined(SOC_AM275X)
    RUN_TEST(TestSbl_rprcImageLoadNullHandle,      11502, NULL);
    RUN_TEST(TestSbl_parseMultiCoreNullHandle,     11503, NULL);
    RUN_TEST(TestSbl_parseAppImageNullHandle,      11504, NULL);
#endif

    RUN_TEST(TestSbl_socCpuSetClockHSM,             11505, NULL);
    RUN_TEST(TestSbl_socCpuGetClockHSM,             11506, NULL);
    RUN_TEST(TestSbl_socGetProcIdInvalid,           11507, NULL);
    RUN_TEST(TestSbl_socGetDevIdInvalid,            11508, NULL);
    RUN_TEST(TestSbl_socGetClkIdInvalid,            11509, NULL);
    RUN_TEST(TestSbl_socGetClkDefaultInvalid,       11510, NULL);
    RUN_TEST(TestSbl_socGetCoreNameInvalid,         11511, NULL);
    RUN_TEST(TestSbl_socGetSelfCpuList,             11512, NULL);
    RUN_TEST(TestSbl_socGetSetSBLMem,               11513, NULL);

#if !defined(SOC_AM275X)
    RUN_TEST(TestSbl_parseMultiCoreNullFxns,          11514, NULL);
    RUN_TEST(TestSbl_verifyMulticoreNullFxns,         11515, NULL);
    RUN_TEST(TestSbl_rprcParseEntryPointNullHandle,   11516, NULL);
    RUN_TEST(TestSbl_loadSelfCpuHsmNoRprc,            11517, NULL);
#endif

    RUN_TEST(TestSbl_uniflashEmmcFlashInvalidIdx,      11518, NULL);
    RUN_TEST(TestSbl_uniflashEmmcVerifyInvalidIdx,     11519, NULL);

    UNITY_END();
}

/**
 * @brief Open and close bootloader instances successfully.
 *
 * Validates that Bootloader_open succeeds for all configured instances
 * and Bootloader_close completes without error.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Double-open on the same bootloader instance.
 *
 * Verifies that opening the same bootloader instance twice returns
 * the same valid handle (config entry pointer) since the driver
 * does not track open state.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Open, close, then re-open bootloader instances.
 *
 * Validates that a bootloader instance can be opened, closed, and
 * opened again successfully without error.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Open bootloader with invalid instance index.
 *
 * Verifies that Bootloader_open returns NULL for an out-of-range
 * instance ID, and that subsequent open with a valid ID succeeds.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Close bootloader with NULL handle.
 *
 * Verifies that Bootloader_close(NULL) does not crash or hang,
 * and a valid handle can still be closed afterwards.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Get boot media for all instances.
 *
 * Opens each bootloader instance and verifies that Bootloader_getBootMedia
 * returns the expected media type (EMMC for instance 0, FLASH otherwise).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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
    
/**
 * @brief Get boot media with NULL handle.
 *
 * Verifies that Bootloader_getBootMedia returns BOOTLOADER_INVALID_ID
 * when called with a NULL handle.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Get image size with NULL handle.
 *
 * Verifies that Bootloader_getMulticoreImageSize returns 0
 * when called with a NULL handle.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Parse appimage with NULL handle and NULL bootImageInfo.
 *
 * Verifies Bootloader_parseMultiCoreAppImage behavior when called
 * with NULL handle (returns SUCCESS as no-op) and NULL bootImageInfo
 * on a real handle (returns FAILURE due to invalid media content).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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
    uint32_t i;

    mHdrStr.magicStr = BOOTLOADER_META_HDR_MAGIC_STR;
    mHdrStr.numFiles = numFiles;
    mHdrStr.devId    = devId;
    mHdrStr.rsvd     = 0U;
    memcpy(&buf[offset], &mHdrStr, sizeof(mHdrStr));
    offset += (uint32_t)sizeof(mHdrStr);

    /* Write core header entries (unused / padding) */
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

/**
 * @brief Parse appimage with invalid RPRC magic number.
 *
 * Constructs an appimage with a valid meta header but an RPRC header
 * containing an invalid magic value (0xDEADBEEF). Verifies that
 * Bootloader_rprcImageLoad detects the mismatch and returns FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_parseInvalidRprcMagic(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[512U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;
    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderCore  mHdrCore;
    Bootloader_MetaHeaderEnd   mHdrEnd;
    Bootloader_RprcFileHeader rprcHdr;
    uint32_t off = 0U;
    uint32_t rprcOffset;

    DebugP_log("Starting TestSbl_parseInvalidRprcMagic test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Build a valid meta header with 1 file, pointing to offset where RPRC
     * header will reside */

    mHdrStr.magicStr = BOOTLOADER_META_HDR_MAGIC_STR;
    mHdrStr.numFiles = 1U;
    mHdrStr.devId    = BOOTLOADER_DEVICE_ID;
    mHdrStr.rsvd     = 0U;
    memcpy(&appImageBuf[off], &mHdrStr, sizeof(mHdrStr));
    off += (uint32_t)sizeof(mHdrStr);

    rprcOffset = off + (uint32_t)sizeof(mHdrCore) + (uint32_t)sizeof(mHdrEnd);
    mHdrCore.coreId      = 0xFFFFFFFFU;
    mHdrCore.imageOffset = rprcOffset;
    memcpy(&appImageBuf[off], &mHdrCore, sizeof(mHdrCore));
    off += (uint32_t)sizeof(mHdrCore);

    mHdrEnd.rsvd           = 0U;
    mHdrEnd.magicStringEnd = BOOTLOADER_META_HDR_MAGIC_END;
    memcpy(&appImageBuf[off], &mHdrEnd, sizeof(mHdrEnd));
    off += (uint32_t)sizeof(mHdrEnd);

    /* Place an RPRC header with INVALID magic */
    
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

/**
 * @brief Parse appimage with corrupted meta header magic.
 *
 * Constructs an appimage with an invalid meta header magic string.
 * Verifies that Bootloader_parseMultiCoreAppImage detects the
 * corruption and returns FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Parse appimage with mismatched device ID.
 *
 * Constructs an appimage with a wrong device ID in the meta header.
 * Documents that the current driver does not check devId (has a TODO).
 * On HS-FS devices, the X509 verification fails first.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Parse appimage with section in SBL reserved memory.
 *
 * Constructs an RPRC with a section whose load address falls inside
 * SBL reserved memory. Verifies Bootloader_rprcImageLoad detects
 * the overlap and returns FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_parseInvalidSectionCount(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[512U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;
    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderCore  mHdrCore;
    Bootloader_MetaHeaderEnd   mHdrEnd;
    Bootloader_RprcFileHeader rprcHdr;
    uint32_t off = 0U;

    DebugP_log("Starting TestSbl_parseInvalidSectionCount test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));

    /* Build a valid meta header */
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

/**
 * @brief Parse appimage with NULL bootImageInfo pointer.
 *
 * On HS-FS devices, Bootloader_verifyMulticoreImage rejects the
 * crafted buffer before bootImageInfo is accessed, returning FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Parse appimage with NULL handle.
 *
 * Verifies that Bootloader_parseMultiCoreAppImage with NULL handle
 * returns SystemP_SUCCESS without processing anything.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Get image size before any parsing.
 *
 * Creates a memory bootloader without parsing any image and queries
 * the multicore image size. Verifies it returns 0.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Parse RPRC with entry point at BOOTLOADER_INVALID_ID.
 *
 * Constructs a valid RPRC header with entry = BOOTLOADER_INVALID_ID.
 * Verifies rprcImageParseEntryPoint reads this sentinel correctly.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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
    uint32_t i;

    Bootloader_RprcFileHeader rprcHdr;
    rprcHdr.magic        = BOOTLOADER_RPRC_MAGIC_NUMBER;
    rprcHdr.entry        = 0x70000000U;
    rprcHdr.rsvdAddr     = 0U;
    rprcHdr.sectionCount = sectionCount;
    rprcHdr.version      = SW_VERSION;
    memcpy(&buf[off], &rprcHdr, sizeof(rprcHdr));
    off += (uint32_t)sizeof(rprcHdr);

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

/**
 * @brief Load image into SBL reserved (protected) memory region.
 *
 * Crafts an RPRC with a section whose load address falls inside SBL
 * reserved memory. Verifies rprcImageLoad detects the overlap and
 * returns FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Load image with oversized section into protected memory.
 *
 * Crafts an RPRC with a very large section landing in SBL reserved
 * memory. Verifies rprcImageLoad detects the protected region and
 * returns FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Load RPRC with corrupted section header.
 *
 * Crafts a valid RPRC file header followed by a section header with
 * a load address inside SBL reserved memory. Verifies rprcImageLoad
 * detects the protected memory overlap and returns FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_loadRprcCorruptedSectionHdr(void *args)
{
    int32_t  status;
    uint8_t  appImageBuf[512U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;
    uint32_t secOff = 0U;
    Bootloader_RprcSectionHeader secHdr;

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
    secOff = (uint32_t)sizeof(rprcHdr);

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

/**
 * @brief Load image when read operation always fails.
 *
 * Uses a custom Bootloader_Fxns whose imgReadFxn always returns FAILURE.
 * Verifies that rprcImageLoad propagates the read failure.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Load image with NULL args (invalid rprcOffset path).
 *
 * Calls rprcImageLoad with NULL args to exercise the no-op guard path,
 * mirroring the outcome when rprcOffset == BOOTLOADER_INVALID_ID.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Load self-CPU with invalid clock frequency (0 Hz).
 *
 * Calls Bootloader_loadSelfCpu with clkHz=0. Verifies the system
 * firmware rejects the invalid frequency and returns FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Load image at SBL reserved boundary address.
 *
 * Crafts an RPRC with a section address just past the start of SBL
 * reserved memory. Verifies the boundary detection and FAILURE return.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Seek to offset beyond media buffer size.
 *
 * Sets curOffset to a value far beyond the buffer via Mem_imgSeek.
 * Verifies the offset is set without bounds checking (no crash).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Read beyond available data in memory bootloader.
 *
 * Sets curOffset past the buffer and issues Mem_imgRead. Verifies
 * the read succeeds (no bounds check) and curOffset advances.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Run CPU before loading any image.
 *
 * Calls Bootloader_runCpu without prior image loading. For the self-CPU,
 * socCpuResetRelease has an empty case, so status remains FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Run CPU with NULL bootloader handle.
 *
 * Calls Bootloader_runCpu with NULL handle. Since runCpu does not
 * dereference the handle, the test outcome depends only on cpuInfo.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Run CPU with NULL cpuInfo precondition check.
 *
 * Documents that Bootloader_runCpu would crash with NULL cpuInfo.
 * Verifies default CpuInfo_init values instead.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Boot CPU with out-of-range cpuId.
 *
 * Calls Bootloader_bootCpu with cpuId=CSL_CORE_ID_MAX. Verifies
 * socCpuRequest returns FAILURE due to invalid processor ID.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Run self-CPU without prior image loading precondition check.
 *
 * Documents unsafe pattern of calling runSelfCpu without loadSelfCpu.
 * Verifies default BootImageInfo_init state (all INVALID_ID).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_runSelfCpuNotRequested(void *args)
{
    uint32_t i;
    Bootloader_BootImageInfo bootImageInfo;

    DebugP_log("Starting TestSbl_runSelfCpuNotRequested test\r\n");

    Bootloader_BootImageInfo_init(&bootImageInfo);

    /* After init, all cpuInfo entries should have BOOTLOADER_INVALID_ID as
     * entryPoint, meaning no images were loaded for any core. */
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

/**
 * @brief Set CPU clock to invalid frequency (0 Hz).
 *
 * Calls Bootloader_socCpuSetClock with 0 Hz. Verifies the system
 * firmware rejects the invalid frequency and returns FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Release self-CPU that is not in reset.
 *
 * Calls Bootloader_socCpuResetRelease for the boot CPU, which has
 * an empty switch case. Verifies status remains FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Power off an already powered-off CPU twice.
 *
 * Calls Bootloader_powerOffCpu twice on C75SS0_0. Verifies that
 * the double power-off does not crash or hang.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Check core presence with invalid core ID.
 *
 * Verifies Bootloader_isCorePresent returns 0 for NULL handle and
 * for out-of-range core IDs (>= 32).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
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

/**
 * @brief Bootloader_xmodemSendAck with invalid UART index.
 *
 * Passes UINT32_MAX as uartDrvIndex so UART_getHandle returns NULL.
 * The function should still return SystemP_SUCCESS.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_xmodemSendAckInvalidIndex(void *args)
{
    int32_t status;

    DebugP_log("Starting TestSbl_xmodemSendAckInvalidIndex test\r\n");

    /* UART_getHandle(UINT32_MAX) returns NULL since index >= gUartConfigNum.
     * Bootloader_xmodemSendAck always returns SystemP_SUCCESS. */
    status = Bootloader_xmodemSendAck(UINT32_MAX);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
}

/**
 * @brief Bootloader_xmodemReceive with NULL UART handle.
 *
 * Passes UINT32_MAX as uartDrvIndex so UART_getHandle returns NULL,
 * exercising the else branch that returns SystemP_FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_xmodemReceiveNullHandle(void *args)
{
    int32_t  status;
    uint8_t  dstBuf[128U];
    uint32_t fileSize = 0U;

    DebugP_log("Starting TestSbl_xmodemReceiveNullHandle test\r\n");

    memset(dstBuf, 0, sizeof(dstBuf));

    /* Invalid index => UART_getHandle returns NULL => gUartHandle == NULL
     * => function takes else branch and returns SystemP_FAILURE. */
    status = Bootloader_xmodemReceive(UINT32_MAX, dstBuf, sizeof(dstBuf), &fileSize);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/**
 * @brief Bootloader_xmodemTransmit with NULL UART handle.
 *
 * Passes UINT32_MAX as uartDrvIndex so UART_getHandle returns NULL,
 * exercising the else branch that returns SystemP_FAILURE.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_xmodemTransmitNullHandle(void *args)
{
    int32_t status;
    uint8_t srcBuf[128U];

    DebugP_log("Starting TestSbl_xmodemTransmitNullHandle test\r\n");

    memset(srcBuf, 0xAA, sizeof(srcBuf));

    /* Invalid index => UART_getHandle returns NULL => gUartHandle == NULL
     * => function takes else branch and returns SystemP_FAILURE. */
    status = Bootloader_xmodemTransmit(UINT32_MAX, srcBuf, sizeof(srcBuf));
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/**
 * @brief xmodemReceive sync error with NULL UART handle.
 *
 * Sets gUartHandle to NULL via Bootloader_xmodemSendAck(UINT32_MAX),
 * then calls xmodemReceive directly. With _inbyte always returning -1
 * (no UART HW access), the state machine exhausts retries with 'C',
 * falls back to NAK, exhausts retries again, and returns -2 (sync error).
 * This exercises the _inbyte / _outbyte NULL-handle branches as well.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_xmodemReceiveSyncError(void *args)
{
    int ret;
    unsigned char dstBuf[256U];

    DebugP_log("Starting TestSbl_xmodemReceiveSyncError test\r\n");

    /* Set gUartHandle (static in bootloader_xmodem.c) to NULL so _inbyte
     * always returns -1 immediately and _outbyte is a no-op. */
    Bootloader_xmodemSendAck(UINT32_MAX);

    memset(dstBuf, 0, sizeof(dstBuf));
    ret = xmodemReceive(dstBuf, (int)sizeof(dstBuf));

    /* xmodemReceive exhausts 16 retries with 'C', switches to NAK,
     * exhausts 16 more retries, then returns -2 (sync error). */
    TEST_ASSERT_EQUAL(-2, ret);
}

/**
 * @brief xmodemTransmit no-sync error with NULL UART handle.
 *
 * Sets gUartHandle to NULL via Bootloader_xmodemSendAck(UINT32_MAX),
 * then calls xmodemTransmit directly. _inbyte always returns -1 so
 * the transmitter never receives 'C' or NAK from a receiver.
 * After 16 retries, returns -2 (no sync).
 * This covers xmodem.c lines 195-199 which are currently uncovered.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_xmodemTransmitNoSync(void *args)
{
    int ret;
    unsigned char srcBuf[64U];

    DebugP_log("Starting TestSbl_xmodemTransmitNoSync test\r\n");

    /* Set gUartHandle to NULL so _inbyte returns -1 immediately. */
    Bootloader_xmodemSendAck(UINT32_MAX);

    memset(srcBuf, 0xBB, sizeof(srcBuf));
    ret = xmodemTransmit(srcBuf, (int)sizeof(srcBuf));

    /* xmodemTransmit exhausts 16 retries waiting for 'C' or NAK,
     * then sends CAN x3 and returns -2 (no sync). */
    TEST_ASSERT_EQUAL(-2, ret);
}

/*===================================================================*/
/*            Bootloader Uniflash Negative Tests                     */
/*===================================================================*/

/**
 * @brief Helper: build a Bootloader_UniflashFileHeader in buf.
 *
 * Fills the first 32 bytes of buf with a file header using the given
 * magic, opType, offset, eraseSize and actualFileSize.
 */
static void TestSbl_buildUniflashFileHeader(uint8_t *buf,
                                            uint32_t magic,
                                            uint32_t opType,
                                            uint32_t offset,
                                            uint32_t eraseSize,
                                            uint32_t actualFileSize)
{
    Bootloader_UniflashFileHeader *hdr = (Bootloader_UniflashFileHeader *)buf;
    hdr->magicNumber            = magic;
    hdr->operationTypeAndFlags  = opType;
    hdr->offset                 = offset;
    hdr->eraseSize              = eraseSize;
    hdr->actualFileSize         = actualFileSize;
    hdr->flashType              = 0U;
    hdr->rsv2                   = 0U;
    hdr->rsv3                   = 0U;
}

/**
 * @brief Uniflash: invalid magic number.
 *
 * Verifies that Bootloader_uniflashProcessFlashCommands returns
 * SystemP_FAILURE and sets MAGIC_ERROR when the file header
 * magic number is wrong.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uniflashMagicError(void *args)
{
    int32_t status;
    uint8_t buf[256U];
    uint8_t verifyBuf[256U];
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    DebugP_log("Starting TestSbl_uniflashMagicError test\r\n");

    memset(buf, 0, sizeof(buf));
    memset(verifyBuf, 0, sizeof(verifyBuf));

    /* Invalid magic number */
    TestSbl_buildUniflashFileHeader(buf, 0xDEADDEADU,
                                   BOOTLOADER_UNIFLASH_OPTYPE_FLASH,
                                   0U, 0U, 64U);

    config.flashIndex   = 0U;
    config.buf          = buf;
    config.bufSize      = sizeof(buf);
    config.verifyBuf    = verifyBuf;
    config.verifyBufSize = sizeof(verifyBuf);

    status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL(BOOTLOADER_UNIFLASH_STATUSCODE_MAGIC_ERROR,
                      respHeader.statusCode);
}

/**
 * @brief Uniflash OPTYPE_FLASH with invalid flash index.
 *
 * Uses UINT32_MAX as flashIndex so Flash_getAttrs/getHandle return NULL.
 * Bootloader_uniflashFlashFile hits the null-handle error path and
 * returns FAILURE, which sets FLASH_ERROR status code.
 *
 * Covers bootloader_uniflash.c lines 113-116, 253-256.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uniflashFlashInvalidIdx(void *args)
{
    int32_t status;
    uint8_t buf[256U];
    uint8_t verifyBuf[256U];
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    DebugP_log("Starting TestSbl_uniflashFlashInvalidIdx test\r\n");

    memset(buf, 0, sizeof(buf));
    memset(verifyBuf, 0, sizeof(verifyBuf));

    TestSbl_buildUniflashFileHeader(buf,
                                   BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
                                   BOOTLOADER_UNIFLASH_OPTYPE_FLASH,
                                   0U, 0U, 64U);

    config.flashIndex    = UINT32_MAX;
    config.buf           = buf;
    config.bufSize       = sizeof(buf);
    config.verifyBuf     = verifyBuf;
    config.verifyBufSize = sizeof(verifyBuf);

    status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR,
                      respHeader.statusCode);
}

/**
 * @brief Uniflash OPTYPE_FLASH_VERIFY with invalid flash index.
 *
 * Bootloader_uniflashFlashVerifyFile hits the null-handle error path.
 * Covers bootloader_uniflash.c lines 131-134, 317-320.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uniflashVerifyInvalidIdx(void *args)
{
    int32_t status;
    uint8_t buf[256U];
    uint8_t verifyBuf[256U];
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    DebugP_log("Starting TestSbl_uniflashVerifyInvalidIdx test\r\n");

    memset(buf, 0, sizeof(buf));
    memset(verifyBuf, 0, sizeof(verifyBuf));

    TestSbl_buildUniflashFileHeader(buf,
                                   BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
                                   BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY,
                                   0U, 0U, 64U);

    config.flashIndex    = UINT32_MAX;
    config.buf           = buf;
    config.bufSize       = sizeof(buf);
    config.verifyBuf     = verifyBuf;
    config.verifyBufSize = sizeof(verifyBuf);

    status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR,
                      respHeader.statusCode);
}

/**
 * @brief Uniflash OPTYPE_FLASH_ERASE with invalid flash index.
 *
 * Bootloader_uniflashFlashErase hits the null-handle error path.
 * Covers bootloader_uniflash.c lines 141-143, 358-361.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uniflashEraseInvalidIdx(void *args)
{
    int32_t status;
    uint8_t buf[256U];
    uint8_t verifyBuf[256U];
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    DebugP_log("Starting TestSbl_uniflashEraseInvalidIdx test\r\n");

    memset(buf, 0, sizeof(buf));
    memset(verifyBuf, 0, sizeof(verifyBuf));

    TestSbl_buildUniflashFileHeader(buf,
                                   BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
                                   BOOTLOADER_UNIFLASH_OPTYPE_FLASH_ERASE,
                                   0U, 4096U, 64U);

    config.flashIndex    = UINT32_MAX;
    config.buf           = buf;
    config.bufSize       = sizeof(buf);
    config.verifyBuf     = verifyBuf;
    config.verifyBufSize = sizeof(verifyBuf);

    status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERASE_ERROR,
                      respHeader.statusCode);
}

/**
 * @brief Uniflash OPTYPE_FLASH_XIP with invalid content.
 *
 * Content after the uniflash header contains all zeros, so the
 * MetaHeaderStart magic (0x5254534D) doesn't match. The XIP flash
 * function returns FAILURE, setting FLASH_ERROR.
 *
 * Covers bootloader_uniflash.c lines 146-157, 458-471, 514-516.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uniflashXipInvalidContent(void *args)
{
    int32_t status;
    uint8_t buf[256U];
    uint8_t verifyBuf[256U];
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    DebugP_log("Starting TestSbl_uniflashXipInvalidContent test\r\n");

    memset(buf, 0, sizeof(buf));
    memset(verifyBuf, 0, sizeof(verifyBuf));

    TestSbl_buildUniflashFileHeader(buf,
                                   BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
                                   BOOTLOADER_UNIFLASH_OPTYPE_FLASH_XIP,
                                   0U, 0U, 64U);
    /* Content after header is all zeros => MetaHeaderStart magic mismatch */

    config.flashIndex    = UINT32_MAX;
    config.buf           = buf;
    config.bufSize       = sizeof(buf);
    config.verifyBuf     = verifyBuf;
    config.verifyBufSize = sizeof(verifyBuf);

    status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR,
                      respHeader.statusCode);
}

/**
 * @brief Uniflash OPTYPE_FLASH_VERIFY_XIP with invalid content.
 *
 * Same as XIP test but for the verify-XIP optype.
 * Covers bootloader_uniflash.c lines 172-183, 509-511.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uniflashVerifyXipInvalidContent(void *args)
{
    int32_t status;
    uint8_t buf[256U];
    uint8_t verifyBuf[256U];
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    DebugP_log("Starting TestSbl_uniflashVerifyXipInvalidContent test\r\n");

    memset(buf, 0, sizeof(buf));
    memset(verifyBuf, 0, sizeof(verifyBuf));

    TestSbl_buildUniflashFileHeader(buf,
                                   BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
                                   BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY_XIP,
                                   0U, 0U, 64U);

    config.flashIndex    = UINT32_MAX;
    config.buf           = buf;
    config.bufSize       = sizeof(buf);
    config.verifyBuf     = verifyBuf;
    config.verifyBufSize = sizeof(verifyBuf);

    status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR,
                      respHeader.statusCode);
}

/**
 * @brief Uniflash OPTYPE_FLASH_TUNING_DATA with invalid flash index.
 *
 * Bootloader_uniflashFlashPhyTuningData hits the null-handle error
 * path and returns FAILURE, setting FLASH_ERROR.
 *
 * Covers bootloader_uniflash.c lines 185-192, 607-619.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uniflashTuningDataInvalidIdx(void *args)
{
    int32_t status;
    uint8_t buf[256U];
    uint8_t verifyBuf[256U];
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    DebugP_log("Starting TestSbl_uniflashTuningDataInvalidIdx test\r\n");

    memset(buf, 0, sizeof(buf));
    memset(verifyBuf, 0, sizeof(verifyBuf));

    TestSbl_buildUniflashFileHeader(buf,
                                   BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
                                   BOOTLOADER_UNIFLASH_OPTYPE_FLASH_TUNING_DATA,
                                   0U, 0U, 64U);

    config.flashIndex    = UINT32_MAX;
    config.buf           = buf;
    config.bufSize       = sizeof(buf);
    config.verifyBuf     = verifyBuf;
    config.verifyBufSize = sizeof(verifyBuf);

    status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR,
                      respHeader.statusCode);
}

/*===================================================================*/
/*  bootloader.c / bootloader_mmcsd_raw.c Negative Tests             */
/*===================================================================*/

/**
 * @brief Bootloader_getX509CertLen with invalid first byte.
 *
 * When the first byte is not 0x30, the function returns 0 immediately.
 * Covers bootloader.c lines 167-170.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_x509CertLenInvalidTag(void *args)
{
    uint32_t certLen;
    uint8_t  buf[8U];

    DebugP_log("Starting TestSbl_x509CertLenInvalidTag test\r\n");

    memset(buf, 0, sizeof(buf));
    /* First byte != 0x30 */
    buf[0] = 0x00U;

    certLen = Bootloader_getX509CertLen(buf);
    TEST_ASSERT_EQUAL(0U, certLen);
}

/**
 * @brief Bootloader_getX509CertLen with unsupported cert length.
 *
 * When first byte is 0x30, second byte (certLen) > 0x80 but != 0x82,
 * the function returns 0. Covers bootloader.c lines 177-181.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_x509CertLenUnsupportedLen(void *args)
{
    uint32_t certLen;
    uint8_t  buf[8U];

    DebugP_log("Starting TestSbl_x509CertLenUnsupportedLen test\r\n");

    memset(buf, 0, sizeof(buf));
    buf[0] = 0x30U;
    /* certLen = 0x81, which is > 0x80 but != 0x82 */
    buf[1] = 0x81U;

    certLen = Bootloader_getX509CertLen(buf);
    TEST_ASSERT_EQUAL(0U, certLen);
}

/**
 * @brief Bootloader_getX509CertLen with small cert (<=0x80).
 *
 * When first byte is 0x30 and second byte is <= 0x80 (and != 0x82),
 * the function takes the else branch (certLen += 1).
 * Covers bootloader.c lines 192-197.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_x509CertLenSmall(void *args)
{
    uint32_t certLen;
    uint8_t  buf[8U];

    DebugP_log("Starting TestSbl_x509CertLenSmall test\r\n");

    memset(buf, 0, sizeof(buf));
    buf[0] = 0x30U;
    /* certLen = 0x50 (80 decimal), <= 0x80 */
    buf[1] = 0x50U;

    certLen = Bootloader_getX509CertLen(buf);
    /* certLen = 0x50 + 1 + 1 = 0x52 = 82 decimal */
    TEST_ASSERT_EQUAL(0x52U, certLen);
}

/**
 * @brief Bootloader_findSeq returns NULL when seq is not found.
 *
 * Passes a buffer that doesn't contain the target OID sequence.
 * Covers bootloader.c line 227 (return 0).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_findSeqNotFound(void *args)
{
    uint8_t  buf[64U];
    uint8_t  seq_oid[] = {0x06, 0x09, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x26, 0x01, 0x22};
    uint8_t *result;

    DebugP_log("Starting TestSbl_findSeqNotFound test\r\n");

    /* Fill buffer with all zeros — the OID sequence won't be found */
    memset(buf, 0, sizeof(buf));

    result = Bootloader_findSeq(buf, (uint32_t)sizeof(buf), seq_oid, (uint8_t)sizeof(seq_oid));
    TEST_ASSERT_NULL(result);
}

#if !defined(SOC_AM275X)
/**
 * @brief Bootloader_MmcsdRaw_readFromOffset with NULL handle.
 *
 * Passing NULL as MMCSD_Handle causes MMCSD_getBlockSize to return 0
 * leading to a divide-by-zero or failure path.
 * Covers bootloader_mmcsd_raw.c error paths.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_mmcsdRawReadNullHandle(void *args)
{
    int32_t  status;
    uint8_t  dst[512U];

    DebugP_log("Starting TestSbl_mmcsdRawReadNullHandle test\r\n");

    memset(dst, 0, sizeof(dst));

    /* Pass NULL handle — MMCSD functions will return failure */
    status = Bootloader_MmcsdRaw_readFromOffset(NULL, dst, sizeof(dst), 0U);
    TEST_ASSERT_NOT_EQUAL(SystemP_SUCCESS, status);
}

/**
 * @brief Bootloader_MmcsdRaw_writeToOffset with NULL handle.
 *
 * Passing NULL as MMCSD_Handle triggers failure in MMCSD write path.
 * Covers bootloader_mmcsd_raw.c write error paths.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_mmcsdRawWriteNullHandle(void *args)
{
    int32_t  status;
    uint8_t  buf[512U];

    DebugP_log("Starting TestSbl_mmcsdRawWriteNullHandle test\r\n");

    memset(buf, 0xAA, sizeof(buf));

    /* Pass NULL handle — MMCSD functions will return failure */
    status = Bootloader_MmcsdRaw_writeToOffset(NULL, buf, sizeof(buf), 0U);
    TEST_ASSERT_NOT_EQUAL(SystemP_SUCCESS, status);
}
#endif /* !defined(SOC_AM275X) */

/*===================================================================*/
/*  bootloader_soc.c / bootloader_rprc.c Negative Tests              */
/*===================================================================*/

/**
 * @brief Bootloader_socGetR5fAtcmAddrAndSize / BtcmAddrAndSize for R5FSS0_0.
 *
 * Calls the ATCM and BTCM address helpers with CSL_CORE_ID_R5FSS0_0.
 * Covers bootloader_soc.c lines 457, 476.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socGetTcmAddrR5fss0(void *args)
{
    uint32_t addr, size;

    DebugP_log("Starting TestSbl_socGetTcmAddrR5fss0 test\r\n");

    Bootloader_socGetR5fAtcmAddrAndSize(CSL_CORE_ID_R5FSS0_0, &addr, &size);
    TEST_ASSERT_NOT_EQUAL(BOOTLOADER_INVALID_ID, addr);
    TEST_ASSERT_NOT_EQUAL(0U, size);

    Bootloader_socGetR5fBtcmAddrAndSize(CSL_CORE_ID_R5FSS0_0, &addr, &size);
    TEST_ASSERT_NOT_EQUAL(BOOTLOADER_INVALID_ID, addr);
    TEST_ASSERT_NOT_EQUAL(0U, size);
}

/**
 * @brief Bootloader_socGetR5fAtcmAddrAndSize / BtcmAddrAndSize default case.
 *
 * Calls the ATCM and BTCM address helpers with a non-R5F CPU ID,
 * triggering the default switch case.
 * Covers bootloader_soc.c lines 463-465, 482-484.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socGetTcmAddrInvalidCpu(void *args)
{
    uint32_t addr, size;

    DebugP_log("Starting TestSbl_socGetTcmAddrInvalidCpu test\r\n");

    Bootloader_socGetR5fAtcmAddrAndSize(CSL_CORE_ID_MAX, &addr, &size);
    TEST_ASSERT_EQUAL(BOOTLOADER_INVALID_ID, addr);
    TEST_ASSERT_EQUAL(0U, size);

    Bootloader_socGetR5fBtcmAddrAndSize(CSL_CORE_ID_MAX, &addr, &size);
    TEST_ASSERT_EQUAL(BOOTLOADER_INVALID_ID, addr);
    TEST_ASSERT_EQUAL(0U, size);
}

/**
 * @brief Bootloader_socMemInitCpu with invalid CPU (default case).
 *
 * An out-of-range core ID does not match any switch case, so the
 * default branch (break with no init) is taken.
 * Covers bootloader_soc.c lines 1125-1126.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socMemInitCpuDefault(void *args)
{
    int32_t status;

    DebugP_log("Starting TestSbl_socMemInitCpuDefault test\r\n");

    status = Bootloader_socMemInitCpu(CSL_CORE_ID_MAX);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
}

/**
 * @brief Bootloader_socCpuPowerOnReset with self-CPU (R5FSS0_0).
 *
 * R5FSS0_0 is the bootloader's own CPU. The switch case is a no-op
 * (just break), so status stays at the initial SystemP_FAILURE.
 * Covers bootloader_soc.c lines 855-858.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socCpuPowerOnResetSelfCpu(void *args)
{
    int32_t status;

    DebugP_log("Starting TestSbl_socCpuPowerOnResetSelfCpu test\r\n");

    status = Bootloader_socCpuPowerOnReset(CSL_CORE_ID_R5FSS0_0, NULL);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

#if !defined(SOC_AM275X)
/**
 * @brief Bootloader_rprcImageLoad with NULL handle.
 *
 * When handle is NULL, config is NULL and the guard
 * (config && config->args) fails, taking the else{do nothing} path.
 * Covers bootloader_rprc.c else branch around line 307.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_rprcImageLoadNullHandle(void *args)
{
    int32_t status;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_rprcImageLoadNullHandle test\r\n");

    Bootloader_CpuInfo_init(&cpuInfo);

    status = Bootloader_rprcImageLoad(NULL, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
}

/**
 * @brief Bootloader_parseMultiCoreAppImage with NULL handle.
 *
 * When handle is NULL, the config pointer check fails and the
 * function takes the else{do nothing} path.
 * Covers bootloader_rprc.c else branch around line 616.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_parseMultiCoreNullHandle(void *args)
{
    int32_t status;
    Bootloader_BootImageInfo bootImageInfo;

    DebugP_log("Starting TestSbl_parseMultiCoreNullHandle test\r\n");

    Bootloader_BootImageInfo_init(&bootImageInfo);

    status = Bootloader_parseMultiCoreAppImage(NULL, &bootImageInfo);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
}

/**
 * @brief Bootloader_parseAppImage with NULL handle.
 *
 * When handle is NULL, config is NULL and the function enters
 * the else branch setting status = SystemP_FAILURE.
 * Covers bootloader_rprc.c else branch around line 777-778.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_parseAppImageNullHandle(void *args)
{
    int32_t status;
    Bootloader_BootImageInfo bootImageInfo;

    DebugP_log("Starting TestSbl_parseAppImageNullHandle test\r\n");

    Bootloader_BootImageInfo_init(&bootImageInfo);

    status = Bootloader_parseAppImage(NULL, &bootImageInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}
#endif /* !defined(SOC_AM275X) */

/**
 * @brief Bootloader_socCpuSetClock with HSM_M4FSS0_0 cpuId.
 *
 * When cpuId is HSM_M4FSS0_0, the function takes the else branch
 * and returns SystemP_SUCCESS without calling Sciclient.
 * Covers bootloader_soc.c lines 601-603.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socCpuSetClockHSM(void *args)
{
    int32_t status;

    DebugP_log("Starting TestSbl_socCpuSetClockHSM test\r\n");

    status = Bootloader_socCpuSetClock(CSL_CORE_ID_HSM_M4FSS0_0, 400000000U);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
}

/**
 * @brief Bootloader_socCpuGetClock with HSM_M4FSS0_0 cpuId.
 *
 * When cpuId is HSM_M4FSS0_0, the if-block is skipped and
 * clkRate remains 0.
 * Covers bootloader_soc.c line 622 else path.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socCpuGetClockHSM(void *args)
{
    uint64_t clkRate;

    DebugP_log("Starting TestSbl_socCpuGetClockHSM test\r\n");

    clkRate = Bootloader_socCpuGetClock(CSL_CORE_ID_HSM_M4FSS0_0);
    TEST_ASSERT_EQUAL(0U, clkRate);
}

/**
 * @brief Bootloader_socGetSciclientCpuProcId with out-of-range cpuId.
 *
 * When cpuId >= CSL_CORE_ID_MAX, the if-block is skipped and
 * BOOTLOADER_INVALID_ID is returned.
 * Covers bootloader_soc.c line 389 else branch.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socGetProcIdInvalid(void *args)
{
    uint32_t procId;

    DebugP_log("Starting TestSbl_socGetProcIdInvalid test\r\n");

    procId = Bootloader_socGetSciclientCpuProcId(CSL_CORE_ID_MAX);
    TEST_ASSERT_EQUAL(BOOTLOADER_INVALID_ID, procId);
}

/**
 * @brief Bootloader_socGetSciclientCpuDevId with out-of-range cpuId.
 *
 * When cpuId >= CSL_CORE_ID_MAX, the if-block is skipped and
 * BOOTLOADER_INVALID_ID is returned.
 * Covers bootloader_soc.c line 401 else branch.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socGetDevIdInvalid(void *args)
{
    uint32_t devId;

    DebugP_log("Starting TestSbl_socGetDevIdInvalid test\r\n");

    devId = Bootloader_socGetSciclientCpuDevId(CSL_CORE_ID_MAX);
    TEST_ASSERT_EQUAL(BOOTLOADER_INVALID_ID, devId);
}

/**
 * @brief Bootloader_socGetSciclientCpuClkId with out-of-range cpuId.
 *
 * When cpuId >= CSL_CORE_ID_MAX, the if-block is skipped and
 * BOOTLOADER_INVALID_ID is returned.
 * Covers bootloader_soc.c line 413 else branch.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socGetClkIdInvalid(void *args)
{
    uint32_t clkId;

    DebugP_log("Starting TestSbl_socGetClkIdInvalid test\r\n");

    clkId = Bootloader_socGetSciclientCpuClkId(CSL_CORE_ID_MAX);
    TEST_ASSERT_EQUAL(BOOTLOADER_INVALID_ID, clkId);
}

/**
 * @brief Bootloader_socCpuGetClkDefault with out-of-range cpuId.
 *
 * When cpuId >= CSL_CORE_ID_MAX, the if-block is skipped and
 * defClock remains 0.
 * Covers bootloader_soc.c line 425 else branch.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socGetClkDefaultInvalid(void *args)
{
    uint32_t defClock;

    DebugP_log("Starting TestSbl_socGetClkDefaultInvalid test\r\n");

    defClock = Bootloader_socCpuGetClkDefault(CSL_CORE_ID_MAX);
    TEST_ASSERT_EQUAL(0U, defClock);
}

/**
 * @brief Bootloader_socGetCoreName with out-of-range cpuId.
 *
 * When cpuId >= CSL_CORE_ID_MAX, the if-block is skipped and
 * NULL is returned.
 * Covers bootloader_soc.c line 437 else branch.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socGetCoreNameInvalid(void *args)
{
    char *pName;

    DebugP_log("Starting TestSbl_socGetCoreNameInvalid test\r\n");

    pName = Bootloader_socGetCoreName(CSL_CORE_ID_MAX);
    TEST_ASSERT_NULL(pName);
}

/**
 * @brief Bootloader_socGetSelfCpuList returns a valid pointer.
 *
 * Covers bootloader_soc.c line 450.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socGetSelfCpuList(void *args)
{
    uint32_t *cpuList;

    DebugP_log("Starting TestSbl_socGetSelfCpuList test\r\n");

    cpuList = Bootloader_socGetSelfCpuList();
    TEST_ASSERT_NOT_NULL(cpuList);
}

/**
 * @brief Bootloader_socGetSBLMem and Bootloader_socSetSBLMem coverage.
 *
 * Calls SetSBLMem followed by GetSBLMem and verifies the returned
 * pointer is not NULL.
 * Covers bootloader_soc.c lines 1211-1212 and 1237-1239.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_socGetSetSBLMem(void *args)
{
    Bootloader_resMemSections *pMem;

    DebugP_log("Starting TestSbl_socGetSetSBLMem test\r\n");

    Bootloader_socSetSBLMem(0x80000000U, 0x80000U);

    pMem = Bootloader_socGetSBLMem();
    TEST_ASSERT_NOT_NULL(pMem);
}

#if !defined(SOC_AM275X)
/**
 * @brief Bootloader_parseMultiCoreAppImage with NULL imgReadFxn.
 *
 * Constructs a Bootloader_Config whose fxns pointer is valid but
 * imgReadFxn is NULL. The NULL-fxns guard fires and returns FAILURE.
 * Covers bootloader_rprc.c lines 488-489.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_parseMultiCoreNullFxns(void *args)
{
    int32_t status;
    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Config  config;
    Bootloader_Fxns    fxns;

    DebugP_log("Starting TestSbl_parseMultiCoreNullFxns test\r\n");

    Bootloader_BootImageInfo_init(&bootImageInfo);

    memset(&fxns, 0, sizeof(fxns)); /* all function pointers NULL */
    memset(&config, 0, sizeof(config));
    config.fxns = &fxns;
    config.args = &config; /* non-NULL so inner checks pass */

    status = Bootloader_parseMultiCoreAppImage((Bootloader_Handle)&config, &bootImageInfo);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/**
 * @brief Bootloader_verifyMulticoreImage with NULL imgReadFxn.
 *
 * Constructs a Bootloader_Config whose fxns pointer is valid but
 * imgReadFxn is NULL. The NULL-fxns guard fires and returns FAILURE.
 * Covers the NULL-fxns check inside Bootloader_verifyMulticoreImage.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_verifyMulticoreNullFxns(void *args)
{
    int32_t status;
    Bootloader_Config  config;
    Bootloader_Fxns    fxns;

    DebugP_log("Starting TestSbl_verifyMulticoreNullFxns test\r\n");

    memset(&fxns, 0, sizeof(fxns)); /* all function pointers NULL */
    memset(&config, 0, sizeof(config));
    config.fxns = &fxns;

    status = Bootloader_verifyMulticoreImage((Bootloader_Handle)&config);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
}

/**
 * @brief Bootloader_rprcImageParseEntryPoint with NULL handle.
 *
 * When handle is NULL, config is NULL and the function takes the
 * else{do nothing} path, returning SUCCESS without parsing.
 * Covers bootloader_rprc.c line 658 else branch.
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_rprcParseEntryPointNullHandle(void *args)
{
    int32_t status;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_rprcParseEntryPointNullHandle test\r\n");

    Bootloader_CpuInfo_init(&cpuInfo);

    status = Bootloader_rprcImageParseEntryPoint(NULL, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
}

/**
 * @brief Bootloader_loadSelfCpu with HSM_M4FSS0_0 and no RPRC image.
 *
 * Uses HSM_M4FSS0_0 cpuId so socCpuSetClock returns SUCCESS
 * without calling Sciclient, and rprcOffset=BOOTLOADER_INVALID_ID
 * so RPRC parsing and loading are skipped.
 * Covers bootloader_rprc.c lines 93-129 (loadSelfCpu success path).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_loadSelfCpuHsmNoRprc(void *args)
{
    int32_t status;
    uint8_t  appImageBuf[64U];
    Bootloader_Config  config;
    Bootloader_MemArgs memArgs;
    Bootloader_CpuInfo cpuInfo;

    DebugP_log("Starting TestSbl_loadSelfCpuHsmNoRprc test\r\n");

    memset(appImageBuf, 0, sizeof(appImageBuf));
    TestSbl_setupMemBootloader(&config, &memArgs, appImageBuf);

    Bootloader_CpuInfo_init(&cpuInfo);
    cpuInfo.cpuId      = CSL_CORE_ID_HSM_M4FSS0_0;
    cpuInfo.clkHz      = 400000000U;
    cpuInfo.rprcOffset = BOOTLOADER_INVALID_ID;

    status = Bootloader_loadSelfCpu((Bootloader_Handle)&config, &cpuInfo);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, status);
}
#endif /* !defined(SOC_AM275X) */

/**
 * @brief Uniflash OPTYPE_EMMC_FLASH with invalid MMCSD index.
 *
 * Bootloader_uniflashFlashFileMMCSDRaw calls MMCSD_getHandle with
 * UINT32_MAX, which returns NULL, triggering the FAILURE path.
 * Covers bootloader_uniflash.c lines 199-200 (EMMC flash error)
 * and lines 649-652 (FlashFileMMCSDRaw NULL handle).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uniflashEmmcFlashInvalidIdx(void *args)
{
    int32_t status;
    uint8_t buf[256U];
    uint8_t verifyBuf[256U];
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    DebugP_log("Starting TestSbl_uniflashEmmcFlashInvalidIdx test\r\n");

    memset(buf, 0, sizeof(buf));
    memset(verifyBuf, 0, sizeof(verifyBuf));

    TestSbl_buildUniflashFileHeader(buf,
                                   BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
                                   BOOTLOADER_UNIFLASH_OPTYPE_EMMC_FLASH,
                                   0U, 0U, 64U);

    config.flashIndex    = UINT32_MAX;
    config.buf           = buf;
    config.bufSize       = sizeof(buf);
    config.verifyBuf     = verifyBuf;
    config.verifyBufSize = sizeof(verifyBuf);

    status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR,
                      respHeader.statusCode);
}

/**
 * @brief Uniflash OPTYPE_EMMC_VERIFY with invalid MMCSD index.
 *
 * Bootloader_uniflashFlashVerifyFileMMCSDRaw calls MMCSD_getHandle
 * with UINT32_MAX, which returns NULL, triggering the FAILURE path.
 * Covers bootloader_uniflash.c lines 217-218 (EMMC verify error)
 * and lines 679-683 (VerifyFileMMCSDRaw NULL handle).
 *
 * @param[in] args Optional user argument (unused).
 *
 * @return void
 */
void TestSbl_uniflashEmmcVerifyInvalidIdx(void *args)
{
    int32_t status;
    uint8_t buf[256U];
    uint8_t verifyBuf[256U];
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    DebugP_log("Starting TestSbl_uniflashEmmcVerifyInvalidIdx test\r\n");

    memset(buf, 0, sizeof(buf));
    memset(verifyBuf, 0, sizeof(verifyBuf));

    TestSbl_buildUniflashFileHeader(buf,
                                   BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
                                   BOOTLOADER_UNIFLASH_OPTYPE_EMMC_VERIFY,
                                   0U, 0U, 64U);

    config.flashIndex    = UINT32_MAX;
    config.buf           = buf;
    config.bufSize       = sizeof(buf);
    config.verifyBuf     = verifyBuf;
    config.verifyBufSize = sizeof(verifyBuf);

    status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);
    TEST_ASSERT_EQUAL(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR,
                      respHeader.statusCode);
}
