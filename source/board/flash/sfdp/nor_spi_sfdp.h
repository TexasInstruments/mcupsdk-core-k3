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

/**
 *  \ingroup BOARD_MODULE
 *  \defgroup DRV_SFDP_API_MODULE SFDP API for single pin mode
 *
 *   These APIs are used to parse various SFDP parameter tables read from a NOR SPI flash
 *
 *  @{
 */

/**
 *  \file nor_spi_sfdp.h
 *
 *  \brief SFDP API/interface file.
 */

#ifndef NOR_SPI_SFDP_H_
#define NOR_SPI_SFDP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/hw_include/csl_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SFDP Signature DWORD */
#define NOR_SPI_SFDP_SIGNATURE     (0x50444653U)

/* SFDP Revisions */
#define NOR_SPI_SFDP_JESD216_MAJOR     (1U)
#define NOR_SPI_SFDP_JESD216_MINOR     (0U)
#define NOR_SPI_SFDP_JESD216A_MINOR    (5U)
#define NOR_SPI_SFDP_JESD216B_MINOR    (6U)
#define NOR_SPI_SFDP_JESD216C_MINOR    (7U)
#define NOR_SPI_SFDP_JESD216D_MINOR    (8U)

/* SFDP Maximum numbers of parameter headers (only JEDEC ones included)*/
#define NOR_SPI_SFDP_NPH_MAX       (13U)

/* SFDP offsets */
#define NOR_SPI_SFDP_HEADER_START_OFFSET        (0x00U)
#define NOR_SPI_SFDP_FIRST_PARAM_HEADER_OFFSET  (0x08U)
#define NOR_SPI_SFDP_SECOND_PARAM_HEADER_OFFSET (0x10U)

/* SFDP Parameter table IDs supported by JEDEC*/
#define NOR_SPI_SFDP_BASIC_PARAM_TABLE_ID            (0xFF00)
#define NOR_SPI_SFDP_SECTOR_MAP_TABLE_ID             (0xFF81)
#define NOR_SPI_SFDP_RPMC_TABLE_ID                   (0xFF03)
#define NOR_SPI_SFDP_4BYTE_ADDR_INSTR_TABLE_ID       (0xFF84)
#define NOR_SPI_SFDP_PROFILE_TABLE_ID           (0xFF05)
#define NOR_SPI_SFDP_PROFILE_2_TABLE_ID         (0xFF06)
#define NOR_SPI_SFDP_SCCR_TABLE_ID                   (0xFF87)
#define NOR_SPI_SFDP_SCCR_MULTISPI_OFFSETS_TABLE_ID  (0xFF88)
#define NOR_SPI_SFDP_SCCR_PROFILE_2_TABLE_ID    (0xFF09)
#define NOR_SPI_SFDP_OCTAL_CMD_SEQ_TABLE_ID          (0xFF0A)
#define NOR_SPI_SFDP_LONG_LATENCY_NVM_MSP_TABLE_ID   (0xFF8B)
#define NOR_SPI_SFDP_QUAD_IO_WITH_DS_TABLE_ID        (0xFF0C)
#define NOR_SPI_SFDP_QUAD_CMD_SEQ_TABLE_ID           (0xFF8D)

/* SFDP Number of DWORDS in BFPT for different revisions */
#define NOR_SPI_SFDP_BFPT_MAX_DWORDS_JESD216         (9)
#define NOR_SPI_SFDP_BFPT_MAX_DWORDS_JESD216B        (16)

/* SFDP read command address type in 8D */
#define NOR_SPI_SFDP_OCTAL_READ_ADDR_MSB_0           (0)
#define NOR_SPI_SFDP_OCTAL_READ_ADDR_LSB_0           (1)

#define NOR_SPI_CMD_EXT_TYPE_REPEAT  (0x00U)
#define NOR_SPI_CMD_EXT_TYPE_INVERSE (0x01U)
#define NOR_SPI_CMD_EXT_TYPE_NONE    (0x02U)

typedef struct NorSpi_SfdpMainHeader_s
{
    uint32_t signature;
    /*  SFDP Signature. "SFDP" in ASCII */

    uint8_t minorRev;
    /* SFDP minor revision number */

    uint8_t majorRev;
    /* SFDP minor revision number */

    uint8_t numParamHeaders;
    /* Number of param headers. Zero-based. 0 means 1 param header */

    uint8_t accessProtocol;
    /* SFDP Access Protocol */

} NorSpi_SfdpMainHeader;

typedef struct NorSpi_SfdpParamHeader_s
{
    uint8_t paramIdLsb;
    /* LSB of parameter ID */

    uint8_t paramTableMinorRev;
    /* Minor revision number of parameter table */

    uint8_t paramTableMajorRev;
    /* Major revision number of parameter table */

    uint8_t paramTableLength;
    /* Number of DWORDs in the parameter table. One based field. So 1 means 1 DWORD */

    uint8_t paramTablePtr[3];
    /* Start of parameter header's corresponding table. This address should be DWORD aligned */

    uint8_t paramIdMsb;
    /* MSB of parameter ID */

} NorSpi_SfdpParamHeader;

typedef struct NorSpi_SfdpBasicFlashParamTable_s
{
    uint32_t dtrQFRNumAddr;
    /* 1st DWORD - has info about DTR support, number of address bytes and Quad and Dual Fast read support */

    uint32_t memoryDensity;
    /* 2nd DWORD - flash size. If b31 is 0, 30:0 is size in bits. If b31 is 1, 30:0 is N, where 2^N is size in bits */

    uint32_t fastRead_114_144_WMI;
    /* 3rd DWORD - 1-1-4 and 1-4-4 fast read wait states, mode bit clocks and instruction */

    uint32_t fastRead_112_122_WMI;
    /* 4th DWORD - 1-1-2 and 1-2-2 fast read wait states, mode bit clocks and instruction */

    uint32_t fastReadSupport_222_444;
    /* 5th DWORD - has info on whether 2-2-2 and 4-4-4 mode are supported */

    uint32_t fastRead_222_WMI;
    /* 6th DWORD - 2-2-2 fast read wait states, mode bit clocks and instruction */

    uint32_t fastRead_444_WMI;
    /* 7th DWORD - 4-4-4 fast read wait states, mode bit clocks and instruction */

    uint32_t eraseType_1_2;
    /* 8th DWORD - erase types 1 and 2 : Sizes and their instructions */

    uint32_t eraseType_3_4;
    /* 9th DWORD - erase types 3 and 4 : Sizes and their instructions */

    uint32_t eraseTimes;
    /* 10th DWORD - erase times for all 4 types of erases */

    uint32_t pageSizeTimes;
    /* 11th DWORD - pageSize, chip erase time, page program time, byte program time */

    uint32_t suspendResumeSupport;
    /* 12th DWORD - suspend/resume support, intervals, latency etc */

    uint32_t suspendResumeInstr;
    /* 13th DWORD - suspend/resume instructions */

    uint32_t deepPdStatusPoll;
    /* 14th DWORD - Deep power down support, instructions, status polling supported modes */

    uint32_t holdResetQeXip;
    /* 15th DWORD - hold and reset details, quad enable requirements, 0-4-4 and 4-4-4 mode enabling */

    uint32_t fourByteAddressVNvStatusReg;
    /* 16th DWORD - 4 byte addressing mode entry/exit, support, soft reset sequences, volatile and non-volatile status register support */

    uint32_t fastRead_118_188_WMI;
    /* 17th DWORD - 1-1-8 and 1-8-8 fast read wait states, mode bit clocks and instruction */

    uint32_t dqsByteOrderCmdExt;
    /* 18th DWORD - DQS support, byte order, command extension type in 8D mode */

    uint32_t OeXip;
    /* 19th DWORD - Octal enable requirements, 0-8-8 mode support, entry and exit, 8-8-8 enable disable sequence */

    uint32_t maxClocks;
    /* 20th DWORD - Maximum operational speed for 4-4-4 and 8-8-8 modes */

} NorSpi_SfdpBasicFlashParamTable;

typedef struct {

    /* Data and CMDs */

    uint8_t  NOR_SPI_CMD_RSTEN;
    uint8_t  NOR_SPI_CMD_RSTMEM;
    uint8_t  NOR_SPI_CMD_WREN;
    uint8_t  NOR_SPI_CMD_WRREG;
    uint8_t  NOR_SPI_CMD_BULK_ERASE;
    uint8_t  NOR_SPI_CMD_SECTOR_ERASE_3B;
    uint8_t  NOR_SPI_CMD_SECTOR_ERASE_4B;
    uint8_t  NOR_SPI_CMD_BLOCK_ERASE_3B;
    uint8_t  NOR_SPI_CMD_BLOCK_ERASE_4B;
    uint8_t  NOR_SPI_CMD_PAGE_PROG_3B;
    uint8_t  NOR_SPI_CMD_PAGE_PROG_4B;
    uint8_t  NOR_SPI_CMD_RDSR;
    uint8_t  NOR_SPI_CMD_RDREG;
    uint8_t  NOR_SPI_CMD_RDID;
    uint8_t  NOR_SPI_CMD_READ;
    uint8_t  NOR_SPI_CMD_888_SDR_READ;
    uint8_t  NOR_SPI_CMD_888_DDR_READ;
    uint8_t  NOR_SPI_CMD_444_SDR_READ;
    uint8_t  NOR_SPI_CMD_444_DDR_READ;
    uint8_t  NOR_SPI_CMD_114_READ;
    uint32_t NOR_SPI_SR_WIP;
    uint32_t NOR_SPI_SR_WEL;
    uint8_t  NOR_SPI_RDID_NUM_BYTES;
    uint8_t  NOR_SPI_MANF_ID;
    uint16_t NOR_SPI_DEVICE_ID;
    uint16_t NOR_SPI_114_READ_MODE_CLKS;
    uint16_t NOR_SPI_114_READ_DUMMY_CYCLES;
    uint16_t NOR_SPI_114_READ_DUMMY_CYCLES_LC;
    uint16_t NOR_SPI_444_READ_MODE_CLKS;
    uint16_t NOR_SPI_444_READ_DUMMY_CYCLES;
    uint16_t NOR_SPI_444_READ_DUMMY_CYCLES_LC;
    uint16_t NOR_SPI_QUAD_CMD_READ_DUMMY_CYCLES;
    uint16_t NOR_SPI_OCTAL_READ_DUMMY_CYCLE;
    uint16_t NOR_SPI_OCTAL_READ_DUMMY_CYCLE_LC;
    uint16_t NOR_SPI_OCTAL_DDR_RDSR_DUMMY_CYCLE;
    uint16_t NOR_SPI_OCTAL_DDR_RDSR_ADDR_BYTES;
    uint16_t NOR_SPI_OCTAL_DDR_RDREG_ADDR_BYTES;
    uint16_t NOR_SPI_OCTAL_DDR_WRREG_ADDR_BYTES;
    uint16_t NOR_SPI_OCTAL_DDR_RDVREG_DUMMY_CYCLE;
    uint16_t NOR_SPI_OCTAL_DDR_RDNVREG_DUMMY_CYCLE;
    uint16_t NOR_SPI_OCTAL_RDSFDP_DUMMY_CYCLE;
    uint8_t  NOR_SPI_OCTAL_RDSFDP_ADDR_TYPE;
    uint32_t NOR_SPI_WRR_WRITE_TIMEOUT;
    uint32_t NOR_SPI_BULK_ERASE_TIMEOUT;
    uint32_t NOR_SPI_PAGE_PROG_TIMEOUT;
    uint32_t NOR_SPI_VREG_OFFSET;
    uint32_t NOR_SPI_NVREG_OFFSET;
    uint32_t NOR_SPI_QUAD_MODE_CFG_ADDR;
    uint32_t NOR_SPI_QUAD_MODE_CFG_BIT_LOCATION;
    uint32_t NOR_SPI_DDR_OCTAL_MODE_CFG_ADDR;
    uint32_t NOR_SPI_DDR_OCTAL_MODE_CFG_BIT_LOCATION;
    uint32_t NOR_SPI_DUMMY_CYCLE_CFG_ADDR;
    uint64_t NOR_SPI_FLASH_SIZE;
    uint16_t NOR_SPI_PAGE_SIZE;
    uint32_t NOR_SPI_BLOCK_SIZE;
    uint32_t NOR_SPI_SECTOR_SIZE;

    /* Settings and flags */
    uint8_t addrByteSupport;
    /* Number of address bytes supported. 3 or 4 or both */

    uint8_t dtrSupport;
    /* Supports DTR clocking or not */

    uint8_t qeType;
    /* Quad Enable Requirements Type */

    uint8_t seq444Enable[5];
    /* Sequence numbers to enable 4-4-4 mode */

    uint8_t seq444Disable[4];
    /* Sequence numbers to disable 4-4-4 mode */

    uint8_t oeType;
    /* Octal Enable Requirements Type */

    uint8_t cmdExtType;
    /* Command Extension supported by the flash in 8D mode */

    uint8_t byteOrder;
    /* Byte order of the flash data out in 8D mode */

    uint8_t supportedEraseTypes[2];
    /* Indexed array of 2 selected supported erase types. [0] will be sect, [1] will be block */

} NorSpi_GenericDevDefines;

typedef struct NorSpi_SfdpProfile1ParamTable_s
{
    uint32_t dwords[5];

} NorSpi_SfdpProfile1ParamTable;

typedef struct NorSpi_SfdpSectorMapParamTable_s
{
    uint32_t dwords[2];

} NorSpi_SfdpSectorMapParamTable;

typedef struct NorSpi_SfdpSCCRParamTable_s
{
    uint32_t dwords[28];

} NorSpi_SfdpSCCRParamTable;

typedef struct NorSpi_Sfdp4ByteAddressingParamTable_s
{
    uint32_t dwords[2];

} NorSpi_Sfdp4ByteAddressingParamTable;

/**
 *  \brief NOR SPI SFDP Structure
 */

typedef struct NorSpi_SfdpHeader_s
{
    NorSpi_SfdpMainHeader      sfdpHeader;
    /* The SFDP header */

    NorSpi_SfdpParamHeader firstParamHeader;
    /* First and mandatory parameter table header */

} NorSpi_SfdpHeader;

/* ========================================================================== */
/*                             Function Definitions                           */
/* ========================================================================== */

/**
 *  \brief  This function returns the name of the parameter table given the table ID
 *
 *  \param  paramTableId 16 bit ID of the parameter table
 *
 *  \return The name of the parameter table as a string
 */
char* NorSpi_Sfdp_getParameterTableName(uint32_t paramTableId);

/**
 *  \brief  This function returns the Parameter Table Pointer (PTP) of the parameter table given the parameter header
 *
 *  \param  paramHeader Parameter header for the table
 *
 *  \return PTP as a uint32_t address
 */
uint32_t NorSpi_Sfdp_getPtp(NorSpi_SfdpParamHeader *paramHeader);

/**
 *  \brief  This function parses the Basic Flash Parameter Table (BFPT) and fills the norSpiDevDefines structure with the parsed information
 *
 *  \param  bfpt           Pointer to the BFPT (allocated by user)
 *  \param  norSpiDefines  Pointer to the generic xSPI device definitions structure (allocated by user)
 *  \param  numDwords      Number of double words actually present in the table (this has to be read from the param header and passed)
 *
 *  \return SystemP_SUCCESS if parsing is successful, otherwise failure.
 */
int32_t NorSpi_Sfdp_parseBfpt(NorSpi_SfdpBasicFlashParamTable *bfpt, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords);

/**
 *  \brief  This function parses the xSPI Flash Profile 1.0 Table and fills the norSpiDevDefines structure with the parsed information
 *
 *  \param  xpt1           Pointer to the xSPI Flash Profile 1.0 Table (allocated by user)
 *  \param  norSpiDefines  Pointer to the generic xSPI device definitions structure (allocated by user)
 *  \param  numDwords      Number of double words actually present in the table (this has to be read from the param header and passed)
 *
 *  \return SystemP_SUCCESS if parsing is successful, otherwise failure.
 */
int32_t NorSpi_Sfdp_parseXpt1(NorSpi_SfdpProfile1ParamTable *xpt1, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords);

/**
 *  \brief  This function parses the 4 Byte Addressing Information Table (4BAIT) and fills the norSpiDevDefines structure with the parsed information
 *
 *  \param  fourBait       Pointer to the 4BAIT (allocated by user)
 *  \param  norSpiDefines  Pointer to the generic xSPI device definitions structure (allocated by user)
 *  \param  numDwords      Number of double words actually present in the table (this has to be read from the param header and passed)
 *
 *  \return SystemP_SUCCESS if parsing is successful, otherwise failure.
 */
int32_t NorSpi_Sfdp_parse4bait(NorSpi_Sfdp4ByteAddressingParamTable *fourBait, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords);

/**
 *  \brief  This function parses the Status, Control and Configuration Registers (SCCR) Table and fills the norSpiDevDefines structure with the parsed information
 *
 *  \param  sccr           Pointer to the SCCR Table (allocated by user)
 *  \param  norSpiDefines  Pointer to the generic xSPI device definitions structure (allocated by user)
 *  \param  numDwords      Number of double words actually present in the table (this has to be read from the param header and passed)
 *
 *  \return SystemP_SUCCESS if parsing is successful, otherwise failure.
 */
int32_t NorSpi_Sfdp_parseSccr(NorSpi_SfdpSCCRParamTable *sccr, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords);

/**
 *  \brief  This function parses the Sector Map Parameter Table (SMPT) and fills the norSpiDevDefines structure with the parsed information
 *
 *  \param  smpt           Pointer to the SMPT (allocated by user)
 *  \param  norSpiDefines  Pointer to the generic xSPI device definitions structure (allocated by user)
 *  \param  numDwords      Number of double words actually present in the table (this has to be read from the param header and passed)
 *
 *  \return SystemP_SUCCESS if parsing is successful, otherwise failure.
 */
int32_t NorSpi_Sfdp_parseSmpt(NorSpi_SfdpSectorMapParamTable *smpt, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords);

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* NOR_SPI_SFDP_H_ */