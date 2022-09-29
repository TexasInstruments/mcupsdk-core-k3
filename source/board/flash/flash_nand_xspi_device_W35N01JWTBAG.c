/*
 *  Copyright (C) 2022 Texas Instruments Incorporated
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

Flash_NandXspiDeviceDefines gFlashNandXspiDeviceDefines_W35N01JWTBAG = {

    .NAND_CMD_RSTEN                                  = 0X66U,
    .NAND_CMD_RST_MEM                                = 0X99U,
    .NAND_CMD_RDID                                   = 0X9FU,
    .NAND_CMD_RDSR                                   = 0X0FU,
    .NAND_CMD_WRITE_STATUS                           = 0X1FU,
    .NAND_CMD_VCR_READ                               = 0X85U,
    .NAND_CMD_WRITE_VCR                              = 0X81U,
    .NAND_CMD_WREN                                   = 0X06U,
    .NAND_CMD_WR_DISABLE                             = 0X04U,
    .NAND_CMD_BBM                                    = 0XA1U,
    .NAND_CMD_READ_BBM_LUT                           = 0XA5U,
    .NAND_CMD_LAST_ECC_ADD                           = 0XA9U,
    .NAND_CMD_BLOCK_ERASE                            = 0XD8U,
    .NAND_CMD_PAGE_READ                              = 0X13U,
    .NAND_CMD_READ                                   = 0X03U,
    .NAND_CMD_FAST_READ                              = 0X0BU,
    .NAND_CMD_OCTAL_DDR_O_FAST_RD                    = 0X8BU,
    .NAND_CMD_OCTAL_IO_FAST_RD                       = 0XCBU,
    .NAND_CMD_FAST_READ_DDR                          = 0X9DU,
    .NAND_CMD_PAGE_PROG                              = 0X84U,
    .NAND_CMD_PAGE_PROG_EXECUTE                      = 0X10U,
    .NAND_CMD_EXT_OCTAL_FAST_PROG                    = 0X82U,
    .NAND_CMD_OCTAL_FAST_PROG                        = 0XC4U,

    .NAND_OCTAL_READ_DUMMY_CYCLE                     = 0X08U,
    .NAND_OCTAL_READ_DUMMY_CYCLE_LC                  = 0X08U,
    .NAND_OCTAL_READ_DUMMY_CYCLE_INDAC               = 0X08U,
    .NAND_OCTAL_READ_DUMMY_CYCLE_INDAC_LC            = 0X08U,
    .NAND_SINGLE_READ_DUMMY_CYCLE                    = 0X08U,
    .NAND_SINGLE_READ_DUMMY_CYCLE_LC                 = 0X08U,
    .NAND_OCTAL_DDR_CMD_READ_DUMMY_CYCLE             = 0X08U,
    .NAND_OCTAL_SDR_CMD_READ_DUMMY_CYCLE             = 0X08U,
    .NAND_SINGLE_CMD_READ_DUMMY_CYCLE                = 0X08U,

    .NAND_RDID_NUM_BYTES                             = 0x03U,

    /* WIP is Bit 0 for SR3 */
    .NAND_SR_WIP                                     = (1U << 0U),
    .NAND_R1_ADDR                                    = 0xA0U,
    .NAND_R2_ADDR                                    = 0xB0U,
    .NAND_R3_ADDR                                    = 0xC0U,

    .NAND_WRR_WRITE_TIMEOUT                          = 1000U,
    .NAND_BULK_ERASE_TIMEOUT                         = 1000U,

    .NAND_MANF_ID                                    = 0xEFU,
    .NAND_DEVICE_ID                                  = 0xDC21U,
};

#define FLASH_SIZE                  (128U * 1024U * 1024U)
#define FLASH_BLOCK_SIZE            (256 * 1024U)
#define FLASH_PAGE_SIZE             (4U * 1024U)
#define FLASH_NUM_BLOCKS            (FLASH_SIZE / FLASH_BLOCK_SIZE)
#define FLASH_NUM_PAGES_PER_BLOCK   (FLASH_BLOCK_SIZE / FLASH_PAGE_SIZE)


Flash_Attrs gFlashNandXspiAttrs_W35N01JWTBAG =
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
