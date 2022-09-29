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
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FLASH_NOR_OSPI_H_
#define FLASH_NOR_OSPI_H_

#ifdef __cplusplus
extern "C"
{
#endif


#include <drivers/ospi.h>

typedef struct {

    uint8_t  NOR_CMD_RSTEN;
    uint8_t  NOR_CMD_RST_MEM;
    uint8_t  NOR_CMD_WREN;
    uint8_t  NOR_CMD_WRDI;
    uint8_t  NOR_CMD_RDCR;
    uint8_t  NOR_CMD_WRCR;
    uint8_t  NOR_CMD_RDCR2;
    uint8_t  NOR_CMD_WRCR2;
    uint8_t  NOR_CMD_BULK_ERASE;
    uint8_t  NOR_CMD_BLOCK_ERASE;
    uint8_t  NOR_CMD_SECTOR_ERASE;
    uint8_t  NOR_CMD_RDSR;
    uint8_t  NOR_CMD_RDID;
    uint8_t  NOR_CMD_RDSFDP;
    uint8_t  NOR_CMD_READ;
    uint8_t  NOR_CMD_OCTAL_READ_SDR;
    uint8_t  NOR_CMD_OCTAL_READ_DDR;
    uint8_t  NOR_CMD_PAGE_PROG;
    uint8_t  NOR_SR_WIP;
    uint8_t  NOR_RDID_NUM_BYTES;
    uint8_t  NOR_MANF_ID;
    uint16_t NOR_DEVICE_ID;
    uint16_t NOR_SINGLE_CMD_READ_DUMMY_CYCLE;
    uint16_t NOR_OCTAL_CMD_READ_DUMMY_CYCLE;
    uint16_t NOR_OCTAL_READ_DUMMY_CYCLE;
    uint16_t NOR_OCTAL_READ_LC;
    uint32_t NOR_DDR_EN_REG_ADDR;
    uint32_t NOR_DUMMY_CYCLE_PROG_REG_ADDR;
    uint32_t NOR_WRR_WRITE_TIMEOUT;
    uint32_t NOR_BULK_ERASE_TIMEOUT;
    uint32_t NOR_PAGE_PROG_TIMEOUT;
    uint32_t NOR_PAGE_SIZE;
    
} Flash_NorOspiDevDefines;

typedef struct {

    OSPI_Handle ospiHandle;
    uint8_t dtrEnable;
    uint8_t phyEnable;
    uint32_t xferLines;
    
} Flash_NorOspiObject;

/* FLash Device specific extern */
extern Flash_NorOspiDevDefines gFlashNorOspiDeviceDefines_MX25LM25645G;
extern Flash_Attrs gFlashNorOspiAttrs_MX25LM25645G;

/* FLash specific externs */
extern Flash_Fxns gFlashNorOspiFxns;


#ifdef __cplusplus
}
#endif

#endif /* FLASH_NOR_OSPI_H_ */
