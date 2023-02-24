/*
 *  Copyright (C) 2022-2023 Texas Instruments Incorporated
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
#include "flash_nand_gpmc.h"

Flash_DevConfig gFlashNandGpmcDeviceDefines_MT29F8G08ADAFAH4 = {
    .idCfg = {
        .cmd =0x90,
        .numBytes = 3,
    },
    .cmdPageLoadCyc1 = 0x00,
    .cmdPageLoadCyc2 = 0x30,
    .pageLoadColAddrCyc = 0x02U,
    .pageLoadRowAddrCyc = 0x03U,

};

#if 0
Flash_NandGpmcDeviceDefines gFlashNandGpmcDeviceDefines_MT29F8G08ADAFAH4 = {

    .NAND_CMD_RST = 0xFFU,
    .NAND_CMD_RDID = 0x90U,
    .NAND_CMD_RDPRPG = 0xECU,
    .NAND_CMD_RDIDUN = 0xEDU,
    .NAND_CMD_GET_FEAT = 0xEEU,
    .NAND_CMD_SET_FEAT = 0xEFU,
    .NAND_CMD_RD_STATUS = 0x70U,
    .NAND_CMD_RD_ENHANCED = 0x78U,
    .NAND_CMD_RD_DATA_RANDOM = 0x05U,
    .NAND_CMD_RD_DATA_RANDOM_CYC2 = 0xE0U,
    .NAND_CMD_DATA_IN_RANDOM = 0x85U,
    .NAND_CMD_IN_DATA_MV = 0x85U,
    .NAND_CMD_RD_MODE = 0x00U,
    .NAND_CMD_RD_PAGE = 0x00U,
    .NAND_CMD_RD_PAGE_CYC2 = 0x30U,
    .NAND_CMD_RD_PAGE_CACHE_SEQUEN = 0x31U,
    .NAND_CMD_RD_PAGE_CACHE_RANDOM = 0x00U,
    .NAND_CMD_RD_PAGE_CACHE_RANDOM_CYC2 = 0x31U,
    .NAND_CMD_RD_PAGE_CACHE_LAST = 0x3FU,
    .NAND_CMD_PROG_PAGE = 0x80U,
    .NAND_CMD_PAGE_PROG_CYC2 = 0x10U,
    .NAND_CMD_PAGE_PROG_CACHE = 0x80U,
    .NAND_CMD_PAGE_PROG_CACHE_CYC2 = 0x15U,
    .NAND_CMD_ERASE_BLK = 0x60U,
    .NAND_CMD_ERASE_BLK_CYC2 = 0xD0U,
    .NAND_RDID_NUM_BYTES = 0x05U,
    .NAND_NUM_BYTES_CLMN_ADDR = 0x02U,
    .NAND_NUM_BYTES_ROW_ADDR = 0x03U,
    .NAND_MANF_ID = 0x2CU,
    .NAND_DEVICE_ID = 0xD3D0U,


};
#endif
#define FLASH_NAND_READ_ID_ADDRESS          (0U)

/** \brief FLASH device specific items (note: sizes are in bytes) */
#define FLASH_SIZE                          (1024U * 1024U * 1024U)
#define FLASH_BLOCK_SIZE                    (256 * 1024U)
#define FLASH_PAGE_SIZE                     (4U * 1024U)
#define FLASH_NUM_BLOCKS                    (FLASH_SIZE / FLASH_BLOCK_SIZE)
#define FLASH_NUM_PAGES_PER_BLOCK           (FLASH_BLOCK_SIZE / FLASH_PAGE_SIZE)
#define FLASH_SPARE_AREA_SIZE               (256U)


Flash_Attrs gFlashNandGpmcAttrs_MT29F8G08ADAFAH4 =
{
    .deviceId = 0xD3D0U,
    .manufacturerId = 0x2CU,
    .driverInstance = 0, /* filled by SysConfig */
    .flashSize = FLASH_SIZE,
    .blockCount = FLASH_NUM_BLOCKS,
    .blockSize = FLASH_BLOCK_SIZE,
    .pageCount = FLASH_NUM_PAGES_PER_BLOCK,
    .pageSize = FLASH_PAGE_SIZE,
    .sectorSize = 0,  /* NOT USED */
    .sectorCount = 0, /* NOT USED */
};
