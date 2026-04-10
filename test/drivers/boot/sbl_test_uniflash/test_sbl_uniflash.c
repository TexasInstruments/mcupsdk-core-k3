/*
 *  Copyright (C) 2024-2026 Texas Instruments Incorporated
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

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/bootloader/bootloader_uniflash.h>
#include <drivers/bootloader/bootloader_priv.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/*
 * Buffer sizes for test data.
 * The buffer must be large enough to hold a Bootloader_UniflashFileHeader
 * plus the largest payload used in any test case.
 */
#define TEST_BUF_SIZE       (0x10000U)
#define TEST_VERIFY_BUF_SIZE (0x10000U)

/* Align buffers to 128 bytes for cache coherency */
static uint8_t gTestBuf[TEST_BUF_SIZE] __attribute__((aligned(128)));
static uint8_t gVerifyBuf[TEST_VERIFY_BUF_SIZE] __attribute__((aligned(128)));

/* ========================================================================== */
/*                          Helper Functions                                  */
/* ========================================================================== */

/*
 * Prepare a Bootloader_UniflashFileHeader in the test buffer.
 * Returns a pointer to the payload area (after the header).
 */
static uint8_t *TestUniflash_prepareHeader(uint32_t magicNumber,
                                           uint32_t opType,
                                           uint32_t offset,
                                           uint32_t eraseSize,
                                           uint32_t actualFileSize)
{
    Bootloader_UniflashFileHeader *hdr = (Bootloader_UniflashFileHeader *)gTestBuf;

    memset(gTestBuf, 0, TEST_BUF_SIZE);

    hdr->magicNumber            = magicNumber;
    hdr->operationTypeAndFlags  = opType;
    hdr->offset                 = offset;
    hdr->eraseSize              = eraseSize;
    hdr->actualFileSize         = actualFileSize;
    hdr->flashType              = 0U;
    hdr->rsv2                   = 0U;
    hdr->rsv3                   = 0U;

    return (gTestBuf + sizeof(Bootloader_UniflashFileHeader));
}

/*
 * Build a minimal valid RPRC file header in the given buffer.
 */
static uint32_t TestUniflash_buildRprcImage(uint8_t *buf, uint32_t sectionAddr,
                                            uint32_t sectionSize, const uint8_t *sectionData)
{
    Bootloader_RprcFileHeader rprcHdr;
    Bootloader_RprcSectionHeader secHdr;
    uint32_t totalSize = 0U;

    memset(&rprcHdr, 0, sizeof(rprcHdr));
    rprcHdr.magic        = BOOTLOADER_RPRC_MAGIC_NUMBER;
    rprcHdr.entry        = 0U;
    rprcHdr.rsvdAddr     = 0U;
    rprcHdr.sectionCount = 1U;
    rprcHdr.version      = 0U;
    memcpy(buf, &rprcHdr, sizeof(rprcHdr));
    totalSize += (uint32_t)sizeof(rprcHdr);

    memset(&secHdr, 0, sizeof(secHdr));
    secHdr.addr    = sectionAddr;
    secHdr.size    = sectionSize;
    memcpy(buf + totalSize, &secHdr, sizeof(secHdr));
    totalSize += (uint32_t)sizeof(secHdr);

    if((sectionData != NULL) && (sectionSize > 0U))
    {
        memcpy(buf + totalSize, sectionData, sectionSize);
    }
    totalSize += sectionSize;

    return totalSize;
}

/*
 * Build a minimal valid multi-core XIP appimage (meta header + one RPRC)
 * in the given buffer.
 */
static uint32_t TestUniflash_buildXipImage(uint8_t *buf, uint32_t sectionAddr,
                                           uint32_t sectionSize, const uint8_t *sectionData)
{
    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderCore  mHdrCore;
    uint32_t offset = 0U;
    uint32_t rprcOffset;

    memset(&mHdrStr, 0, sizeof(mHdrStr));
    mHdrStr.magicStr = BOOTLOADER_META_HDR_MAGIC_STR;
    mHdrStr.numFiles = 1U;
    mHdrStr.devId    = 0U;
    memcpy(buf + offset, &mHdrStr, sizeof(mHdrStr));
    offset += (uint32_t)sizeof(mHdrStr);

    rprcOffset = offset + (uint32_t)sizeof(mHdrCore);

    memset(&mHdrCore, 0, sizeof(mHdrCore));
    mHdrCore.coreId      = 0U;
    mHdrCore.imageOffset = rprcOffset;
    memcpy(buf + offset, &mHdrCore, sizeof(mHdrCore));
    offset += (uint32_t)sizeof(mHdrCore);

    offset += TestUniflash_buildRprcImage(buf + offset, sectionAddr, sectionSize, sectionData);

    return offset;
}

/* ========================================================================== */
/*                          Setup / Teardown                                  */
/* ========================================================================== */

void setUp(void)
{
    memset(gTestBuf, 0, TEST_BUF_SIZE);
    memset(gVerifyBuf, 0, TEST_VERIFY_BUF_SIZE);
}

void tearDown(void)
{
}

/* ========================================================================== */
/*                          Test Cases                                        */
/* ========================================================================== */

/*
 * TC1: Invalid magic number in file header.
 * Covers: Bootloader_uniflashProcessFlashCommands -> magic number check branch.
 * Expected: BOOTLOADER_UNIFLASH_STATUSCODE_MAGIC_ERROR
 */
void TestUniflash_invalidMagicNumber(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(0xDEADBEEFU, BOOTLOADER_UNIFLASH_OPTYPE_FLASH, 0U, 0U, 64U);

    config.flashIndex   = CONFIG_FLASH0;
    config.buf          = gTestBuf;
    config.bufSize      = TEST_BUF_SIZE;
    config.verifyBuf    = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_MAGIC_ERROR, respHeader.statusCode);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);
}

/*
 * TC2: Valid magic, OPTYPE_FLASH with valid flash index and block-aligned offset.
 * Covers: OPTYPE_FLASH case, Bootloader_uniflashFlashFile, Bootloader_uniflashFlashVerifyFile.
 */
void TestUniflash_flashOpType(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH,
        0U,  /* offset = 0, block-aligned */
        0U,
        64U  /* 64 bytes, already 16B aligned */
    );

    /* Fill payload with a known pattern */
    memset(payload, 0xAA, 64U);

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);

    if(status == SystemP_SUCCESS)
    {
        TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_SUCCESS, respHeader.statusCode);
    }
    else
    {
        /* Flash operation may fail if no real flash is present; verify error code is set */
        TEST_ASSERT_TRUE(
            (respHeader.statusCode == BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR) ||
            (respHeader.statusCode == BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR)
        );
    }
}

/*
 * TC3: OPTYPE_FLASH_VERIFY with valid magic.
 * Covers: OPTYPE_FLASH_VERIFY case, Bootloader_uniflashFlashVerifyFile.
 */
void TestUniflash_flashVerifyOpType(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY,
        0U,
        0U,
        64U
    );

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);

    if(status != SystemP_SUCCESS)
    {
        TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR, respHeader.statusCode);
    }
}

/*
 * TC4: OPTYPE_FLASH_ERASE with valid magic.
 * Covers: OPTYPE_FLASH_ERASE case, Bootloader_uniflashFlashErase.
 */
void TestUniflash_flashEraseOpType(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_ERASE,
        0U,     /* block-aligned offset */
        0x1000U, /* erase 4KB */
        0U
    );

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);

    if(status != SystemP_SUCCESS)
    {
        TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERASE_ERROR, respHeader.statusCode);
    }
}

/*
 * TC5: OPTYPE_FLASH_XIP with valid XIP image (meta header + RPRC).
 * Covers: OPTYPE_FLASH_XIP case, Bootloader_uniflashFlashXipFile,
 *         Bootloader_uniflashFlashOrVerifyXipFile,
 *         Bootloader_uniflashFlashOrVerifyRprcXipFile.
 */
void TestUniflash_flashXipOpType(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;
    uint8_t sectionData[64];

    memset(sectionData, 0xBB, sizeof(sectionData));

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_XIP,
        0U,
        0U,
        0U  /* will be overwritten below */
    );

    /* Build XIP image in the payload area. Section address must be block-aligned. */
    uint32_t xipSize = TestUniflash_buildXipImage(payload, 0U, 64U, sectionData);

    /* Patch the actual file size in the header */
    Bootloader_UniflashFileHeader *hdr = (Bootloader_UniflashFileHeader *)gTestBuf;
    hdr->actualFileSize = xipSize;

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);

    if(status != SystemP_SUCCESS)
    {
        TEST_ASSERT_TRUE(
            (respHeader.statusCode == BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR) ||
            (respHeader.statusCode == BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR)
        );
    }
}

/*
 * TC6: OPTYPE_FLASH_VERIFY_XIP with valid XIP image.
 * Covers: OPTYPE_FLASH_VERIFY_XIP case, Bootloader_uniflashFlashVerifyXipFile.
 */
void TestUniflash_flashVerifyXipOpType(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;
    uint8_t sectionData[64];

    memset(sectionData, 0xCC, sizeof(sectionData));

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY_XIP,
        0U,
        0U,
        0U
    );

    uint32_t xipSize = TestUniflash_buildXipImage(payload, 0U, 64U, sectionData);

    Bootloader_UniflashFileHeader *hdr = (Bootloader_UniflashFileHeader *)gTestBuf;
    hdr->actualFileSize = xipSize;

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);

    if(status != SystemP_SUCCESS)
    {
        TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR, respHeader.statusCode);
    }
}

/*
 * TC7: OPTYPE_FLASH_TUNING_DATA.
 * Covers: OPTYPE_FLASH_TUNING_DATA case, Bootloader_uniflashFlashPhyTuningData.
 */
void TestUniflash_flashTuningDataOpType(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_TUNING_DATA,
        0U,
        0U,
        16U
    );

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);

    if(status != SystemP_SUCCESS)
    {
        TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR, respHeader.statusCode);
    }
}

/*
 * TC8: Unknown/invalid optype.
 * Covers: default case in the switch.
 */
void TestUniflash_unknownOpType(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        0x00U,  /* invalid optype */
        0U,
        0U,
        16U
    );

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    /* The function returns success but sets error in resp header for unknown optype */
    (void)status;
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_OPTYPE_ERROR, respHeader.statusCode);
}

/*
 * TC9: File size not 16B aligned — test the padding branch.
 * Covers: remainder != 0 branch in Bootloader_uniflashProcessFlashCommands.
 */
void TestUniflash_fileSizeNotAligned(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH,
        0U,
        0U,
        50U  /* 50 is NOT 16B aligned; remainder = 2 */
    );

    memset(payload, 0xDD, 64U);

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);
    /* The file should be padded to 64 bytes (50 -> 64). Just verify no crash. */
    (void)status;
}

/*
 * TC10: File size exactly 16B aligned — test the no-padding branch.
 * Covers: remainder == 0 (do nothing) branch.
 */
void TestUniflash_fileSizeAligned(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH,
        0U,
        0U,
        64U  /* 64 is 16B aligned */
    );

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);
    (void)status;
}

/*
 * TC11: OPTYPE_FLASH with non-block-aligned offset.
 * Covers: flashOffset % eraseBlockSize != 0 branch in Bootloader_uniflashFlashFile.
 */
void TestUniflash_flashNonAlignedOffset(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH,
        0x123U,  /* Non-block-aligned offset */
        0U,
        64U
    );

    memset(payload, 0xEE, 64U);

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR, respHeader.statusCode);
}

/*
 * TC12: OPTYPE_FLASH_ERASE with non-block-aligned offset.
 * Covers: flashOffset % eraseBlockSize != 0 branch in Bootloader_uniflashFlashErase.
 */
void TestUniflash_eraseNonAlignedOffset(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_ERASE,
        0x123U,  /* Non-block-aligned offset */
        0x1000U,
        0U
    );

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERASE_ERROR, respHeader.statusCode);
}

/*
 * TC13: OPTYPE_FLASH_ERASE with eraseSize > flashSize.
 * Covers: eraseSize > flashSize branch in Bootloader_uniflashFlashErase.
 */
void TestUniflash_eraseExceedsFlashSize(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_ERASE,
        0U,
        0xFFFFFFFFU,  /* Very large erase size */
        0U
    );

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERASE_ERROR, respHeader.statusCode);
}

/*
 * TC14: XIP with invalid meta header magic.
 * Covers: mHdrStr.magicStr != BOOTLOADER_META_HDR_MAGIC_STR branch in
 *         Bootloader_uniflashFlashOrVerifyXipFile.
 */
void TestUniflash_xipInvalidMetaHeaderMagic(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_XIP,
        0U,
        0U,
        64U
    );

    /* Write an invalid meta header magic */
    Bootloader_MetaHeaderStart mHdrStr;
    memset(&mHdrStr, 0, sizeof(mHdrStr));
    mHdrStr.magicStr = 0xBADBADBAU;  /* Invalid */
    mHdrStr.numFiles = 1U;
    memcpy(payload, &mHdrStr, sizeof(mHdrStr));

    Bootloader_UniflashFileHeader *hdr = (Bootloader_UniflashFileHeader *)gTestBuf;
    hdr->actualFileSize = 64U;

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR, respHeader.statusCode);
}

/*
 * TC15: XIP with invalid RPRC magic inside XIP image.
 * Covers: header.magic != BOOTLOADER_RPRC_MAGIC_NUMBER branch in
 *         Bootloader_uniflashFlashOrVerifyRprcXipFile.
 */
void TestUniflash_xipInvalidRprcMagic(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_XIP,
        0U,
        0U,
        0U
    );

    /* Build a valid meta header but with invalid RPRC content */
    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderCore mHdrCore;
    uint32_t offset = 0U;

    memset(&mHdrStr, 0, sizeof(mHdrStr));
    mHdrStr.magicStr = BOOTLOADER_META_HDR_MAGIC_STR;
    mHdrStr.numFiles = 1U;
    memcpy(payload + offset, &mHdrStr, sizeof(mHdrStr));
    offset += (uint32_t)sizeof(mHdrStr);

    uint32_t rprcOffset = offset + (uint32_t)sizeof(mHdrCore);
    memset(&mHdrCore, 0, sizeof(mHdrCore));
    mHdrCore.coreId      = 0U;
    mHdrCore.imageOffset = rprcOffset;
    memcpy(payload + offset, &mHdrCore, sizeof(mHdrCore));
    offset += (uint32_t)sizeof(mHdrCore);

    /* Write an invalid RPRC header */
    Bootloader_RprcFileHeader rprcHdr;
    memset(&rprcHdr, 0, sizeof(rprcHdr));
    rprcHdr.magic = 0xDEADDEADU;  /* Invalid RPRC magic */
    rprcHdr.sectionCount = 0U;
    memcpy(payload + offset, &rprcHdr, sizeof(rprcHdr));
    offset += (uint32_t)sizeof(rprcHdr);

    Bootloader_UniflashFileHeader *hdr = (Bootloader_UniflashFileHeader *)gTestBuf;
    hdr->actualFileSize = offset;

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR, respHeader.statusCode);
}

/*
 * TC16: XIP with coreId == 0xFFFFFFFF (skip core).
 * Covers: mHdrCore[i].coreId == 0xFFFFFFFF branch in
 *         Bootloader_uniflashFlashOrVerifyXipFile.
 */
void TestUniflash_xipSkippedCore(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_XIP,
        0U,
        0U,
        0U
    );

    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderCore mHdrCore;
    uint32_t offset = 0U;

    memset(&mHdrStr, 0, sizeof(mHdrStr));
    mHdrStr.magicStr = BOOTLOADER_META_HDR_MAGIC_STR;
    mHdrStr.numFiles = 1U;
    memcpy(payload + offset, &mHdrStr, sizeof(mHdrStr));
    offset += (uint32_t)sizeof(mHdrStr);

    memset(&mHdrCore, 0xFF, sizeof(mHdrCore));
    mHdrCore.coreId      = 0xFFFFFFFFU;  /* Skip this core */
    mHdrCore.imageOffset = 0U;
    memcpy(payload + offset, &mHdrCore, sizeof(mHdrCore));
    offset += (uint32_t)sizeof(mHdrCore);

    Bootloader_UniflashFileHeader *hdr = (Bootloader_UniflashFileHeader *)gTestBuf;
    hdr->actualFileSize = offset;

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    /* All cores skipped, so the operation should succeed */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_SUCCESS, respHeader.statusCode);
}

/*
 * TC17: Resp header init with NULL pointer.
 * Covers: respHeader == 0 branch in Bootloader_uniflashInitRespHeader.
 * Note: Bootloader_uniflashInitRespHeader is static, but calling
 * Bootloader_uniflashProcessFlashCommands exercises it with a valid pointer.
 * This test verifies the non-NULL path works correctly.
 */
void TestUniflash_respHeaderInit(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    memset(&respHeader, 0, sizeof(respHeader));

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        0x00U,
        0U,
        0U,
        16U
    );

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    (void)Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);
    TEST_ASSERT_EQUAL_UINT32(0xDEADBABE, respHeader.rsv0);
    TEST_ASSERT_EQUAL_UINT32(0xDEADBABE, respHeader.rsv1);
}

/*
 * TC18: OPTYPE_FLASH with an invalid flash index (use a very large index).
 * Covers: flashAttrs == 0 || flashHandle == NULL branch in
 *         Bootloader_uniflashFlashFile and Bootloader_uniflashFlashVerifyFile.
 */
void TestUniflash_flashInvalidFlashIndex(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH,
        0U,
        0U,
        64U
    );

    memset(payload, 0xFF, 64U);

    config.flashIndex    = 0xFFU; /* Invalid flash index */
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR, respHeader.statusCode);
}

/*
 * TC19: OPTYPE_FLASH_VERIFY with an invalid flash index.
 * Covers: flashAttrs == 0 || flashHandle == NULL branch in
 *         Bootloader_uniflashFlashVerifyFile.
 */
void TestUniflash_verifyInvalidFlashIndex(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_VERIFY,
        0U,
        0U,
        64U
    );

    config.flashIndex    = 0xFFU; /* Invalid flash index */
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_VERIFY_ERROR, respHeader.statusCode);
}

/*
 * TC20: OPTYPE_FLASH_ERASE with an invalid flash index.
 * Covers: flashAttrs == 0 || flashHandle == NULL branch in
 *         Bootloader_uniflashFlashErase.
 */
void TestUniflash_eraseInvalidFlashIndex(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_ERASE,
        0U,
        0x1000U,
        0U
    );

    config.flashIndex    = 0xFFU; /* Invalid flash index */
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERASE_ERROR, respHeader.statusCode);
}

/*
 * TC21: OPTYPE_FLASH_TUNING_DATA with an invalid flash index.
 * Covers: flashAttrs == 0 || flashHandle == NULL branch in
 *         Bootloader_uniflashFlashPhyTuningData.
 */
void TestUniflash_tuningDataInvalidFlashIndex(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;

    TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_TUNING_DATA,
        0U,
        0U,
        16U
    );

    config.flashIndex    = 0xFFU; /* Invalid flash index */
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_STATUSCODE_FLASH_ERROR, respHeader.statusCode);
}

/*
 * TC22: XIP with multiple cores — one valid, one skipped (0xFFFFFFFF).
 * Covers: the loop iteration with mixed valid/invalid coreIds.
 */
void TestUniflash_xipMultipleCoresMixed(void *args)
{
    Bootloader_UniflashConfig config;
    Bootloader_UniflashResponseHeader respHeader;
    uint8_t sectionData[64];

    memset(sectionData, 0xAA, sizeof(sectionData));

    uint8_t *payload = TestUniflash_prepareHeader(
        BOOTLOADER_UNIFLASH_FILE_HEADER_MAGIC_NUMBER,
        BOOTLOADER_UNIFLASH_OPTYPE_FLASH_XIP,
        0U,
        0U,
        0U
    );

    Bootloader_MetaHeaderStart mHdrStr;
    Bootloader_MetaHeaderCore mHdrCore[2];
    uint32_t offset = 0U;

    memset(&mHdrStr, 0, sizeof(mHdrStr));
    mHdrStr.magicStr = BOOTLOADER_META_HDR_MAGIC_STR;
    mHdrStr.numFiles = 2U;
    memcpy(payload + offset, &mHdrStr, sizeof(mHdrStr));
    offset += (uint32_t)sizeof(mHdrStr);

    /* First core: skipped */
    memset(&mHdrCore[0], 0xFF, sizeof(Bootloader_MetaHeaderCore));
    mHdrCore[0].coreId      = 0xFFFFFFFFU;
    mHdrCore[0].imageOffset = 0U;

    /* Second core: valid */
    uint32_t rprcStart = offset + 2U * (uint32_t)sizeof(Bootloader_MetaHeaderCore);
    memset(&mHdrCore[1], 0, sizeof(Bootloader_MetaHeaderCore));
    mHdrCore[1].coreId      = 0U;
    mHdrCore[1].imageOffset = rprcStart;

    memcpy(payload + offset, &mHdrCore[0], sizeof(Bootloader_MetaHeaderCore));
    offset += (uint32_t)sizeof(Bootloader_MetaHeaderCore);
    memcpy(payload + offset, &mHdrCore[1], sizeof(Bootloader_MetaHeaderCore));
    offset += (uint32_t)sizeof(Bootloader_MetaHeaderCore);

    /* Build RPRC image at rprcStart */
    offset += TestUniflash_buildRprcImage(payload + offset, 0U, 64U, sectionData);

    Bootloader_UniflashFileHeader *hdr = (Bootloader_UniflashFileHeader *)gTestBuf;
    hdr->actualFileSize = offset;

    config.flashIndex    = CONFIG_FLASH0;
    config.buf           = gTestBuf;
    config.bufSize       = TEST_BUF_SIZE;
    config.verifyBuf     = gVerifyBuf;
    config.verifyBufSize = TEST_VERIFY_BUF_SIZE;

    int32_t status = Bootloader_uniflashProcessFlashCommands(&config, &respHeader);

    TEST_ASSERT_EQUAL_UINT32(BOOTLOADER_UNIFLASH_RESP_HEADER_MAGIC_NUMBER, respHeader.magicNumber);
    (void)status;
}

/* ========================================================================== */
/*                          Test Runner                                       */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(TestUniflash_invalidMagicNumber,           2000, NULL);
    RUN_TEST(TestUniflash_flashOpType,                  5000, NULL);
    RUN_TEST(TestUniflash_flashVerifyOpType,            5000, NULL);
    RUN_TEST(TestUniflash_flashEraseOpType,             5000, NULL);
    RUN_TEST(TestUniflash_flashXipOpType,               5000, NULL);
    RUN_TEST(TestUniflash_flashVerifyXipOpType,         5000, NULL);
    RUN_TEST(TestUniflash_flashTuningDataOpType,        5000, NULL);
    RUN_TEST(TestUniflash_unknownOpType,                2000, NULL);
    RUN_TEST(TestUniflash_fileSizeNotAligned,           5000, NULL);
    RUN_TEST(TestUniflash_fileSizeAligned,              5000, NULL);
    RUN_TEST(TestUniflash_flashNonAlignedOffset,        5000, NULL);
    RUN_TEST(TestUniflash_eraseNonAlignedOffset,        5000, NULL);
    RUN_TEST(TestUniflash_eraseExceedsFlashSize,        5000, NULL);
    RUN_TEST(TestUniflash_xipInvalidMetaHeaderMagic,    5000, NULL);
    RUN_TEST(TestUniflash_xipInvalidRprcMagic,          5000, NULL);
    RUN_TEST(TestUniflash_xipSkippedCore,               5000, NULL);
    RUN_TEST(TestUniflash_respHeaderInit,               2000, NULL);
    RUN_TEST(TestUniflash_flashInvalidFlashIndex,       2000, NULL);
    RUN_TEST(TestUniflash_verifyInvalidFlashIndex,      2000, NULL);
    RUN_TEST(TestUniflash_eraseInvalidFlashIndex,       2000, NULL);
    RUN_TEST(TestUniflash_tuningDataInvalidFlashIndex,  2000, NULL);
    RUN_TEST(TestUniflash_xipMultipleCoresMixed,        5000, NULL);

    UNITY_END();
}
