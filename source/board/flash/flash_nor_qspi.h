/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef FLASH_NOR_QSPI_H_
#define FLASH_NOR_QSPI_H_

#ifdef __cplusplus
extern "C"
{
#endif


#include <drivers/qspi.h>

typedef struct {
    uint8_t NOR_CMD_RDID;
    uint8_t NOR_CMD_SINGLE_READ;
    uint8_t NOR_CMD_QUAD_READ;
    uint8_t NOR_PAGE_PROG;
    uint8_t NOR_CMD_RSTEN;
    uint8_t NOR_CMD_RST;
    uint8_t NOR_CMD_WREN;
    uint8_t NOR_CMD_WRSR;
    uint8_t NOR_CMD_RDSR1;
    uint8_t NOR_CMD_RDSR2;
    uint8_t NOR_RDID_NUM_BYTES;
    uint8_t NOR_MANF_ID;
    uint16_t NOR_DEVICE_ID;
    uint8_t NOR_CMD_SECTOR_ERASE;
    uint8_t NOR_CMD_BLOCK_ERASE;
    uint8_t  NOR_CMD_BULK_ERASE;
    uint16_t NOR_QUAD_READ_DUMMY_CYCLE;
    uint32_t NOR_WRR_WRITE_TIMEOUT;
    uint32_t NOR_BULK_ERASE_TIMEOUT;
    uint32_t NOR_PAGE_PROG_TIMEOUT;
    uint16_t NOR_PAGE_SIZE;
    uint8_t NOR_ADDR_NUM_BYTES;
} Flash_NorQspiDevDefines;

typedef struct {

    QSPI_Handle qspiHandle;
    uint8_t dtrEnable;
    uint8_t phyEnable;
    uint32_t xferLines;

} Flash_NorQspiObject;

/* FLash Device specific extern */
extern Flash_NorQspiDevDefines gFlashNorQspiDeviceDefines_GD25B64C;
extern Flash_Attrs gFlashNorQspiAttrs_GD25B64C;
extern Flash_NorQspiDevDefines gFlashNorQspiDeviceDefines_S25FL128SA;
extern Flash_Attrs gFlashNorQspiAttrs_S25FL128SA;

/* FLash specific externs */
extern Flash_Fxns gFlashNorQspiFxns;


#ifdef __cplusplus
}
#endif

#endif /* FLASH_NOR_QSPI_H_ */
