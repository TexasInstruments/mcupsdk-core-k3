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
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FLASH_NAND_XSPI_H_
#define FLASH_NAND_XSPI_H_

#include <drivers/ospi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {

    uint8_t NAND_CMD_RSTEN;
    uint8_t NAND_CMD_RST_MEM;
    uint8_t NAND_CMD_RDID;
    uint8_t NAND_CMD_RDSR;
    uint8_t NAND_CMD_WRITE_STATUS;
    uint8_t NAND_CMD_VCR_READ;
    uint8_t NAND_CMD_WRITE_VCR;
    uint8_t NAND_CMD_WREN;
    uint8_t NAND_CMD_WR_DISABLE;
    uint8_t NAND_CMD_BBM;
    uint8_t NAND_CMD_READ_BBM_LUT;
    uint8_t NAND_CMD_LAST_ECC_ADD;
    uint8_t NAND_CMD_BLOCK_ERASE;
    uint8_t NAND_CMD_PAGE_READ;
    uint8_t NAND_CMD_READ;
    uint8_t NAND_CMD_FAST_READ;
    uint8_t NAND_CMD_OCTAL_DDR_O_FAST_RD;
    uint8_t NAND_CMD_OCTAL_IO_FAST_RD;
    uint8_t NAND_CMD_FAST_READ_DDR;
    uint8_t NAND_CMD_PAGE_PROG;
    uint8_t NAND_CMD_PAGE_PROG_EXECUTE;
    uint8_t NAND_CMD_EXT_OCTAL_FAST_PROG;
    uint8_t NAND_CMD_OCTAL_FAST_PROG;


    uint8_t NAND_OCTAL_READ_DUMMY_CYCLE;
    uint8_t NAND_OCTAL_READ_DUMMY_CYCLE_LC;
    uint8_t NAND_OCTAL_READ_DUMMY_CYCLE_INDAC;
    uint8_t NAND_OCTAL_READ_DUMMY_CYCLE_INDAC_LC;
    uint8_t NAND_SINGLE_READ_DUMMY_CYCLE;
    uint8_t NAND_SINGLE_READ_DUMMY_CYCLE_LC;
    uint8_t NAND_OCTAL_DDR_CMD_READ_DUMMY_CYCLE;
    uint8_t NAND_OCTAL_SDR_CMD_READ_DUMMY_CYCLE;
    uint8_t NAND_SINGLE_CMD_READ_DUMMY_CYCLE;

    uint8_t NAND_RDID_NUM_BYTES;

    uint8_t NAND_SR_WIP;
    uint8_t NAND_R1_ADDR;
    uint8_t NAND_R2_ADDR;
    uint8_t NAND_R3_ADDR;

    uint32_t NAND_WRR_WRITE_TIMEOUT;
    uint32_t NAND_BULK_ERASE_TIMEOUT;

#if 1
    /* TODO: */
    uint8_t NAND_MANF_ID;
    uint16_t NAND_DEVICE_ID;
#endif
} Flash_NandXspiDeviceDefines;

typedef struct {

    OSPI_Handle ospiHandle;
    uint8_t dtrEnable;
    uint8_t phyEnable;
    uint32_t xferLines;

} Flash_NandXspiObject;

/* Flash Device specific extern */
extern Flash_NandXspiDeviceDefines gFlashNandXspiDeviceDefines_W35N01JWTBAG;
extern Flash_Attrs gFlashNandXspiAttrs_W35N01JWTBAG;

/* Flash specific externs */
extern Flash_Fxns gFlashNandXspiFxns;

#ifdef __cplusplus
}
#endif


#endif /* FLASH_NAND_XSPI_H_ */