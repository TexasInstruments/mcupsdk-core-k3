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

Flash_NorXspiDevDefines gFlashNorXspiDeviceDefines_S28HS512T = {

    .NOR_CMD_SRSTE                       = 0x66U,
    .NOR_CMD_SFRST                       = 0x99U,
    .NOR_CMD_WREN                        = 0x06U,
    .NOR_CMD_WRREG                       = 0x71U,
    .NOR_CMD_BULK_ERASE                  = 0xC7U,
    .NOR_CMD_BLOCK_ERASE                 = 0xDCU,
    .NOR_CMD_RDSR                        = 0x05U,
    .NOR_CMD_RDID                        = 0x9FU,
    .NOR_CMD_WRITE_VCR                   = 0x71U,
    .NOR_CMD_OCTAL_READ                  = 0xECU,
    .NOR_CMD_READ                        = 0x03U,
    .NOR_CMD_PAGE_PROG                   = 0x02U,
    .NOR_CMD_RDREG                       = 0x65U,
    .NOR_CMD_OCTAL_PROG                  = 0x12U,
    .NOR_CMD_OCTAL_DDR_READ              = 0xEEU,
    .NOR_SR_WIP                          = (1U << 0U),
    .NOR_RDID_NUM_BYTES                  = 0x3U,
    .NOR_MANF_ID                         = 0x34U,
    .NOR_DEVICE_ID                       = 0x5B1A,
    .NOR_SINGLE_CMD_READ_DUMMY_CYCLE     = 1U,
    .NOR_OCTAL_READ_DUMMY_CYCLE          = 24U,
    .NOR_OCTAL_READ_DUMMY_CYCLE_LC       = 0xBU,
    .NOR_OCTAL_READ_DUMMY_CYCLE_INDAC    = 20U,
    .NOR_OCTAL_READ_DUMMY_CYCLE_LC_INDAC = 0x8U,
    .NOR_OCTAL_DDR_CMD_READ_DUMMY_CYCLE  = 4U,
    .NOR_OCTAL_SDR_CMD_READ_DUMMY_CYCLE  = 3U,
    .NOR_WRR_WRITE_TIMEOUT               = (600U * 1000U),
    .NOR_BULK_ERASE_TIMEOUT              = (110U * 1000U * 1000U),
    .NOR_PAGE_PROG_TIMEOUT               = 400U,
    .NOR_VREG_ADDR                       = 0x800000U,
    .NOR_CFG2_VREG_ADDR                  = 0x800003U,
    .NOR_CFG3_VREG_ADDR                  = 0x800004U,
    .NOR_CFG3_NVREG_ADDR                 = 0x04U,
    .NOR_PAGE_SIZE                       = 256U,
};

#define FLASH_SIZE                  (64U * 1024U * 1024U)
#define FLASH_BLOCK_SIZE            (256U * 1024U)
#define FLASH_PAGE_SIZE             (256U)
#define FLASH_NUM_BLOCKS            (FLASH_SIZE / FLASH_BLOCK_SIZE)
#define FLASH_NUM_PAGES_PER_BLOCK   (FLASH_BLOCK_SIZE / FLASH_PAGE_SIZE)

Flash_Attrs gFlashNorXspiAttrs_S28HS512T = 
{
    .deviceId       = 0,  /* filled by Flash_open, after querying the flash */
    .manufacturerId = 0,  /* filled by Flash_open, after querying the flash */
    .driverInstance = 0,  /* filled by SysConfig */
    .flashSize      = FLASH_SIZE,
    .blockCount     = FLASH_NUM_BLOCKS,
    .blockSize      = FLASH_BLOCK_SIZE,
    .pageCount      = FLASH_NUM_PAGES_PER_BLOCK,
    .pageSize       = FLASH_PAGE_SIZE,
    .sectorSize     = 0,  /* NOT USED */
    .sectorCount    = 0,  /* NOT USED */
};