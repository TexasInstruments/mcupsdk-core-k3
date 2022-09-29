/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, LOSS OF USE,
 *  DATA, OR PROFITS, OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <board/flash.h>

Flash_NorOspiDevDefines gFlashNorOspiDeviceDefines_MX25LM25645G = {

    .NOR_CMD_RSTEN                       = 0x66U,
    .NOR_CMD_RST_MEM                     = 0x99U,
    .NOR_CMD_WREN                        = 0x06U,
    .NOR_CMD_WRDI                        = 0x04U,
    .NOR_CMD_RDCR                        = 0x15U,
    .NOR_CMD_WRCR                        = 0x01U,
    .NOR_CMD_RDCR2                       = 0x71U,
    .NOR_CMD_WRCR2                       = 0x72U,
    .NOR_CMD_BULK_ERASE                  = 0xC7U,
    .NOR_CMD_BLOCK_ERASE                 = 0xDCU,
    .NOR_CMD_SECTOR_ERASE                = 0x21U,
    .NOR_CMD_RDSR                        = 0x05U,
    .NOR_CMD_RDID                        = 0x9FU,
    .NOR_CMD_RDSFDP                      = 0x5AU,
    .NOR_CMD_READ                        = 0x13U,
    .NOR_CMD_OCTAL_READ_SDR              = 0xECU,
    .NOR_CMD_OCTAL_READ_DDR              = 0xEEU,
    .NOR_CMD_PAGE_PROG                   = 0x12U,
    .NOR_SR_WIP                          = (1U << 0U),
    .NOR_RDID_NUM_BYTES                  = 0x3U,
    .NOR_MANF_ID                         = 0xC2U,
    .NOR_DEVICE_ID                       = 0x8539,
    .NOR_SINGLE_CMD_READ_DUMMY_CYCLE     = 0U,
    .NOR_OCTAL_CMD_READ_DUMMY_CYCLE      = 4U,
    .NOR_OCTAL_READ_DUMMY_CYCLE          = 20U,
    .NOR_OCTAL_READ_LC                   = 0U,
    .NOR_DDR_EN_REG_ADDR                 = 0x00000000U,
    .NOR_DUMMY_CYCLE_PROG_REG_ADDR       = 0x00000300U,
    .NOR_WRR_WRITE_TIMEOUT               = (600U * 1000U),
    .NOR_BULK_ERASE_TIMEOUT              = (110U * 1000U * 1000U),
    .NOR_PAGE_PROG_TIMEOUT               = 400U,
    .NOR_PAGE_SIZE                       = 256U,
};

#define FLASH_SIZE                  (32U * 1024U * 1024U)
#define FLASH_BLOCK_SIZE            (64U * 1024U)
#define FLASH_SECTOR_SIZE           (4U * 1024U)
#define FLASH_PAGE_SIZE             (256U)
#define FLASH_NUM_BLOCKS            (FLASH_SIZE / FLASH_BLOCK_SIZE)
#define FLASH_NUM_PAGES_PER_BLOCK   (FLASH_BLOCK_SIZE / FLASH_PAGE_SIZE)
#define FLASH_NUM_SECTORS           (FLASH_SIZE / FLASH_SECTOR_SIZE)

Flash_Attrs gFlashNorOspiAttrs_MX25LM25645G = 
{
    .deviceId       = 0,  /* filled by Flash_open, after querying the flash */
    .manufacturerId = 0,  /* filled by Flash_open, after querying the flash */
    .driverInstance = 0,  /* filled by SysConfig */
    .flashSize      = FLASH_SIZE,
    .blockCount     = FLASH_NUM_BLOCKS,
    .blockSize      = FLASH_BLOCK_SIZE,
    .pageCount      = FLASH_NUM_PAGES_PER_BLOCK,
    .pageSize       = FLASH_PAGE_SIZE,
    .sectorSize     = FLASH_SECTOR_SIZE,
    .sectorCount    = FLASH_NUM_SECTORS,
};