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
 *  \file nor_spi_sfdp.c
 *
 *  \brief File containing SFDP Driver APIs implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* This is needed for memset/memcpy */
#include <string.h>
#include <board/flash/sfdp/nor_spi_sfdp.h>
#include <drivers/hw_include/cslr.h>

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */

#define NOR_SPI_SFDP_GET_BITFIELD(val, start, end) ( (val >> start) & ((1U << (end-start+1))-1) )

/* ========================================================================== */
/*                       Internal Function Declarations                       */
/* ========================================================================== */

static void NorSpi_Sfdp_getEraseSizes(NorSpi_SfdpBasicFlashParamTable *bfpt, NorSpi_GenericDevDefines *norSpiDefines);
static uint8_t NorSpi_Sfdp_getDummyBitPattern(NorSpi_SfdpSCCRParamTable *sccr, uint32_t dummyClk);


/*===========================================================================*/
/*                            Structure Definitions                          */
/*===========================================================================*/

/* None */

/*===========================================================================*/
/*                            Global Variables                               */
/*===========================================================================*/

uint32_t gNorSpi_Sfdp_ParamTableIds[NOR_SPI_SFDP_NPH_MAX] = {
    NOR_SPI_SFDP_BASIC_PARAM_TABLE_ID,
    NOR_SPI_SFDP_SECTOR_MAP_TABLE_ID,
    NOR_SPI_SFDP_RPMC_TABLE_ID,
    NOR_SPI_SFDP_4BYTE_ADDR_INSTR_TABLE_ID,
    NOR_SPI_SFDP_PROFILE_TABLE_ID,
    NOR_SPI_SFDP_PROFILE_2_TABLE_ID,
    NOR_SPI_SFDP_SCCR_TABLE_ID,
    NOR_SPI_SFDP_SCCR_MULTISPI_OFFSETS_TABLE_ID,
    NOR_SPI_SFDP_SCCR_PROFILE_2_TABLE_ID,
    NOR_SPI_SFDP_OCTAL_CMD_SEQ_TABLE_ID,
    NOR_SPI_SFDP_LONG_LATENCY_NVM_MSP_TABLE_ID,
    NOR_SPI_SFDP_QUAD_IO_WITH_DS_TABLE_ID,
    NOR_SPI_SFDP_QUAD_CMD_SEQ_TABLE_ID,
};

char* gNorSpi_Sfdp_ParamTableNames[NOR_SPI_SFDP_NPH_MAX] = {
    "BASIC PARAMETER TABLE",
    "SECTOR MAP TABLE",
    "RPMC TABLE",
    "4 BYTE ADDRESSING MODE INSTRUCTIONS TABLE",
    "NOR SPI PROFILE TABLE ",
    "NOR SPI PROFILE 2.0 TABLE",
    "STATUS CONTROL AND CONFIGURATION REGISTER MAP TABLE",
    "STATUS CONTROL AND CONFIGURATION REGISTER MAP MULTISPI OFFSETS TABLE",
    "STATUS CONTROL AND CONFIGURATION REGISTER MAP NOR SPI PROFILE 2.0  TABLE",
    "OCTAL DDR MODE COMMAND SEQUENCE TABLE",
    "LONG LATENCY NVM MEDIA SPECIFIC PARAMETER TABLE",
    "QUAD IO WITH DS TABLE",
    "QUAD DDR MODE COMMAND SEQUENCE TABLE",
};


/*===========================================================================*/
/*                            Function Definitions                           */
/*===========================================================================*/
char* NorSpi_Sfdp_getParameterTableName(uint32_t paramTableId)
{
    uint32_t i, idx = NOR_SPI_SFDP_NPH_MAX;
    char *p = NULL;

    for(i = 0; i < NOR_SPI_SFDP_NPH_MAX; i++)
    {
        if(paramTableId == gNorSpi_Sfdp_ParamTableIds[i])
        {
            idx = i;
            break;
        }
    }

    if(idx == NOR_SPI_SFDP_NPH_MAX)
    {
        /* Unrecognized param table */
        p = NULL;
    }
    else
    {
        p = gNorSpi_Sfdp_ParamTableNames[idx];
    }

    return p;
}

uint32_t NorSpi_Sfdp_getPtp(NorSpi_SfdpParamHeader *paramHeader)
{
    uint32_t ptp = 0xFFFFFFFFU;

    if(paramHeader != NULL)
    {
        ptp = (uint32_t)(paramHeader->paramTablePtr[2] << 16) |
              (uint32_t)(paramHeader->paramTablePtr[1] << 8)  |
              (uint32_t)(paramHeader->paramTablePtr[0]);
    }

    return ptp;
}

int32_t NorSpi_Sfdp_parseBfpt(NorSpi_SfdpBasicFlashParamTable *bfpt, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords)
{
    int32_t status = SystemP_SUCCESS;

    /* Some NOR SPI standards */
    norSpiDefines->NOR_SPI_CMD_WREN = 0x06;
    norSpiDefines->NOR_SPI_CMD_RDSR = 0x05;
    norSpiDefines->NOR_SPI_CMD_RDID = 0x9F;
    norSpiDefines->NOR_SPI_CMD_READ = 0x03;
    norSpiDefines->NOR_SPI_CMD_PAGE_PROG_3B = 0x02;

    /* Always set this to 5. RDID will keep reading 5+1 ID bytes in 1s mode, this way no need to change with 8D/4D */
    norSpiDefines->NOR_SPI_RDID_NUM_BYTES = 5;

    /* Number of address bytes */
    norSpiDefines->addrByteSupport = NOR_SPI_SFDP_GET_BITFIELD(bfpt->dtrQFRNumAddr, 17, 18);

    /* DTR support */
    norSpiDefines->dtrSupport = NOR_SPI_SFDP_GET_BITFIELD(bfpt->dtrQFRNumAddr, 19, 19);

    /* Flash Size */
    norSpiDefines->NOR_SPI_FLASH_SIZE = 0U;

    if(NOR_SPI_SFDP_GET_BITFIELD(bfpt->memoryDensity, 31, 31) == 0)
    {
        norSpiDefines->NOR_SPI_FLASH_SIZE = NOR_SPI_SFDP_GET_BITFIELD(bfpt->memoryDensity, 0, 30) + 1;
    }
    else
    {
        uint32_t n = NOR_SPI_SFDP_GET_BITFIELD(bfpt->memoryDensity, 0, 30);

        if(n > 63)
        {
            DebugP_logError("Bad flash size read from SFDP !! \r\n");
            norSpiDefines->NOR_SPI_FLASH_SIZE = 0U;
        }
        else
        {
            norSpiDefines->NOR_SPI_FLASH_SIZE = 1U << n;
        }
    }
    /* Convert to bytes */
    norSpiDefines->NOR_SPI_FLASH_SIZE >>= 3;

    /* Check for 1-1-4 mode */
    norSpiDefines->NOR_SPI_CMD_114_READ = NOR_SPI_SFDP_GET_BITFIELD(bfpt->fastRead_114_144_WMI, 24, 31);

    if(norSpiDefines->NOR_SPI_CMD_114_READ != 0)
    {
        /* 1-1-4 mode is supported */
        norSpiDefines->NOR_SPI_114_READ_MODE_CLKS = NOR_SPI_SFDP_GET_BITFIELD(bfpt->fastRead_114_144_WMI, 21, 23);
        norSpiDefines->NOR_SPI_114_READ_DUMMY_CYCLES = NOR_SPI_SFDP_GET_BITFIELD(bfpt->fastRead_114_144_WMI, 16, 20);
    }
    else
    {
        norSpiDefines->NOR_SPI_114_READ_MODE_CLKS = 0;
        norSpiDefines->NOR_SPI_114_READ_DUMMY_CYCLES = 0;
    }

    /* Check for 4-4-4 mode */
    if(NOR_SPI_SFDP_GET_BITFIELD(bfpt->fastReadSupport_222_444, 4, 4) != 0)
    {
        norSpiDefines->NOR_SPI_CMD_444_SDR_READ = NOR_SPI_SFDP_GET_BITFIELD(bfpt->fastRead_444_WMI, 24, 31);
        norSpiDefines->NOR_SPI_444_READ_MODE_CLKS = NOR_SPI_SFDP_GET_BITFIELD(bfpt->fastRead_444_WMI, 21, 23);
        norSpiDefines->NOR_SPI_444_READ_DUMMY_CYCLES = NOR_SPI_SFDP_GET_BITFIELD(bfpt->fastRead_444_WMI, 16, 20);
    }
    else
    {
        norSpiDefines->NOR_SPI_CMD_444_SDR_READ = 0;
        norSpiDefines->NOR_SPI_444_READ_MODE_CLKS = 0;
        norSpiDefines->NOR_SPI_444_READ_DUMMY_CYCLES = 0;
    }

    /* QSPI flashes don't need dummy cycles for CMD reads in quad mode (yet) */
    norSpiDefines->NOR_SPI_QUAD_CMD_READ_DUMMY_CYCLES = 0U;

    /* Erase types : Of all the ones supported, smallest would be sector and largest would be block */
    /* This will set the erase command and type from BFPT. Will be updated with 4BAIT and SMPT parsing */
    NorSpi_Sfdp_getEraseSizes(bfpt, norSpiDefines);

    /* Check for JESD216A. That has only 9 DWORDS */
    if(numDwords > NOR_SPI_SFDP_BFPT_MAX_DWORDS_JESD216)
    {
        /* Page size and timeouts */
        uint32_t count = 0U;
        uint32_t unit = 0U; /* All time units in μs */

        /* Page size */
        norSpiDefines->NOR_SPI_PAGE_SIZE = (1 << (NOR_SPI_SFDP_GET_BITFIELD(bfpt->pageSizeTimes, 4, 7)));

        /* Page program timeout */
        if(NOR_SPI_SFDP_GET_BITFIELD(bfpt->pageSizeTimes, 13, 13) == 1)
        {
            unit = 64;
        }
        else
        {
            unit = 8;
        }

        count = NOR_SPI_SFDP_GET_BITFIELD(bfpt->pageSizeTimes, 8, 12);

        norSpiDefines->NOR_SPI_PAGE_PROG_TIMEOUT = (count+1)*unit;

        /* Chip Erase / Bulk Erase Timeout */
        switch(NOR_SPI_SFDP_GET_BITFIELD(bfpt->pageSizeTimes, 29, 30))
        {
            case 0:
                unit = 16 * 1000; /* 16 ms */
                break;

            case 1:
                unit = 256 * 1000; /* 256 ms */
                break;

            case 2:
                unit = 4 * 1000 * 1000; /* 4 s */
                break;

            case 3:
                unit = 64 * 1000 * 1000; /* 64 s */
                break;

            default:
                unit = 0U; /* Should not hit */
                break;
        }

        count = NOR_SPI_SFDP_GET_BITFIELD(bfpt->pageSizeTimes, 24, 28);

        norSpiDefines->NOR_SPI_BULK_ERASE_TIMEOUT = (count+1)*unit;
        norSpiDefines->NOR_SPI_WRR_WRITE_TIMEOUT = 10*norSpiDefines->NOR_SPI_PAGE_PROG_TIMEOUT;

        /* Quad Enable Requirement. TODO: Later change this to pickup a function pointer accordingly */
        norSpiDefines->qeType = NOR_SPI_SFDP_GET_BITFIELD(bfpt->holdResetQeXip, 20, 22);

        uint32_t bitPos = 0U;
        uint32_t field = NOR_SPI_SFDP_GET_BITFIELD(bfpt->holdResetQeXip, 4, 8);

        for(bitPos = 0U; bitPos < 5; bitPos++)
        {
            if(((field >> bitPos) & 0x01)==1)
            {
                norSpiDefines->seq444Enable[bitPos] = 1;
            }
            else
            {
                norSpiDefines->seq444Enable[bitPos] = 0;
            }
        }

        field = NOR_SPI_SFDP_GET_BITFIELD(bfpt->holdResetQeXip, 0, 3);

        for(bitPos = 0U; bitPos < 4; bitPos++)
        {
            if(((field >> bitPos) & 0x01)==1)
            {
                norSpiDefines->seq444Disable[bitPos] = 1;
            }
            else
            {
                norSpiDefines->seq444Disable[bitPos] = 0;
            }
        }

        /* Soft Reset check */
        if(NOR_SPI_SFDP_GET_BITFIELD(bfpt->fourByteAddressVNvStatusReg, 12, 12) == 1)
        {
            norSpiDefines->NOR_SPI_CMD_RSTEN = 0x66;
            norSpiDefines->NOR_SPI_CMD_RSTMEM = 0x99;
        }

        /* Check for JESD216B. That has only 16 DWORDS */
        if(numDwords > NOR_SPI_SFDP_BFPT_MAX_DWORDS_JESD216B)
        {
            /* Byte order */
            norSpiDefines->byteOrder = NOR_SPI_SFDP_GET_BITFIELD(bfpt->dqsByteOrderCmdExt, 31, 31);

            /* 8D mode command extension */
            uint32_t cmdExt = NOR_SPI_SFDP_GET_BITFIELD(bfpt->dqsByteOrderCmdExt, 29, 30);

            switch(cmdExt)
            {
                case 0x00:
                    norSpiDefines->cmdExtType = NOR_SPI_CMD_EXT_TYPE_REPEAT;
                    break;

                case 0x01:
                    norSpiDefines->cmdExtType = NOR_SPI_CMD_EXT_TYPE_INVERSE;
                    break;

                default:
                    norSpiDefines->cmdExtType = NOR_SPI_CMD_EXT_TYPE_NONE;
                    break;
            }

            /* TODO: Octal Enable Sequence */

        }
        else
        {
            /* JEDS216B, parsing stops here */
        }
    }
    else
    {
        /* JEDS216A, parsing stops here. */
    }

    return status;
}

/* Sector Map Parameter Table */
int32_t NorSpi_Sfdp_parseSmpt(NorSpi_SfdpSectorMapParamTable *smpt, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords)
{
    int32_t status = SystemP_SUCCESS;

    /* TODO: Complete region mapping according to sector map selection */

    return status;
}

/* Status, Control and Configuration Registers Table */
int32_t NorSpi_Sfdp_parseSccr(NorSpi_SfdpSCCRParamTable *sccr, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords)
{
    int32_t status = SystemP_SUCCESS;

    /* Address offset to volatile and non-volatile registers */
    norSpiDefines->NOR_SPI_VREG_OFFSET = sccr->dwords[0];
    norSpiDefines->NOR_SPI_NVREG_OFFSET = sccr->dwords[1];

    /* Bit location of WIP and WEL */
    norSpiDefines->NOR_SPI_SR_WIP = (1 << (NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[4], 24, 26)));
    norSpiDefines->NOR_SPI_SR_WEL = (1 << (NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[5], 24, 26)));

    /* Set CMDs for RDREG and WRREG */
    norSpiDefines->NOR_SPI_CMD_RDREG = 0x65;
    norSpiDefines->NOR_SPI_CMD_WRREG = 0x71;

    /* Set the dummy cycle and 8D, 4D mode register addresses */
    if(NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[8], 28, 28) == 1)
    {
        norSpiDefines->NOR_SPI_DUMMY_CYCLE_CFG_ADDR = NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[8], 16, 23);
    }

    /* QPI Mode */
    if(NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[13], 31, 31) == 1)
    {
        norSpiDefines->NOR_SPI_QUAD_MODE_CFG_ADDR = NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[13], 16, 23);
        norSpiDefines->NOR_SPI_QUAD_MODE_CFG_BIT_LOCATION = NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[13], 24, 26);
    }

    /* DDR Octal SPI Mode */
    if(NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[21], 31, 31) == 1)
    {
        norSpiDefines->NOR_SPI_DDR_OCTAL_MODE_CFG_ADDR = NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[21], 16, 23);
        norSpiDefines->NOR_SPI_DDR_OCTAL_MODE_CFG_BIT_LOCATION = NOR_SPI_SFDP_GET_BITFIELD(sccr->dwords[21], 24, 26);
    }

    /* Bit pattern for 444 mode read dummy cycle */
    norSpiDefines->NOR_SPI_444_READ_DUMMY_CYCLES_LC = NorSpi_Sfdp_getDummyBitPattern(sccr, norSpiDefines->NOR_SPI_444_READ_DUMMY_CYCLES);

    return status;
}

/* 4 Byte Addressing Instructions Table */
int32_t NorSpi_Sfdp_parse4bait(NorSpi_Sfdp4ByteAddressingParamTable *fourBait, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords)
{
    int32_t status = SystemP_SUCCESS;

    /* Erase CMDs for 4 byte addressing mode */
    uint8_t blkEraseCmd, sectEraseCmd;

    if(norSpiDefines->supportedEraseTypes[0] < 4)
    {
        sectEraseCmd = (fourBait->dwords[1] >> (norSpiDefines->supportedEraseTypes[0]*8)) & 0xFF;
    }
    else
    {
        sectEraseCmd = 0U;
    }

    if(norSpiDefines->supportedEraseTypes[1] < 4)
    {
        blkEraseCmd = (fourBait->dwords[1] >> (norSpiDefines->supportedEraseTypes[1]*8)) & 0xFF;
    }
    else
    {
        blkEraseCmd = 0U;
    }

    norSpiDefines->NOR_SPI_CMD_SECTOR_ERASE_4B = sectEraseCmd;
    norSpiDefines->NOR_SPI_CMD_BLOCK_ERASE_4B = blkEraseCmd;

    /* 4 Byte Page Program check */
    if(NOR_SPI_SFDP_GET_BITFIELD(fourBait->dwords[0], 6, 6) == 1)
    {
        norSpiDefines->NOR_SPI_CMD_PAGE_PROG_4B = 0x12;
    }
    else
    {
        norSpiDefines->NOR_SPI_CMD_PAGE_PROG_4B = 0x02;
    }

    return status;
}

/* NOR SPI Profile 1 Table */
int32_t NorSpi_Sfdp_parseXpt1(NorSpi_SfdpProfile1ParamTable *xpt1, NorSpi_GenericDevDefines *norSpiDefines, uint32_t numDwords)
{
    int32_t status = SystemP_SUCCESS;

    /* Get the fast read command for 8D-8D-8D mode */
    norSpiDefines->NOR_SPI_CMD_888_DDR_READ = NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[0], 8, 15);

    /* Address type for 8D SFDP, LSB 0 or MSB 0 */
    if(NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[0], 31, 31) == 0)
    {
        norSpiDefines->NOR_SPI_OCTAL_RDSFDP_ADDR_TYPE = NOR_SPI_SFDP_OCTAL_READ_ADDR_MSB_0;
    }
    else
    {
        norSpiDefines->NOR_SPI_OCTAL_RDSFDP_ADDR_TYPE = NOR_SPI_SFDP_OCTAL_READ_ADDR_LSB_0;
    }

    /* Dummy cycles for 8D SFDP */
    if(NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[0], 30, 30) == 0)
    {
        norSpiDefines->NOR_SPI_OCTAL_RDSFDP_DUMMY_CYCLE = 8;
    }
    else
    {
        norSpiDefines->NOR_SPI_OCTAL_RDSFDP_DUMMY_CYCLE = 20;
    }

    /* Dummy Cycles for RDSR and REG READ CMDs */
    if(NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[0], 28, 28) == 1)
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDSR_DUMMY_CYCLE = 8;
    }
    else
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDSR_DUMMY_CYCLE = 4;
    }

    if(NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[0], 26, 26) == 1)
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDVREG_DUMMY_CYCLE = 8;
    }
    else
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDVREG_DUMMY_CYCLE = 4;
    }

    if(NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[0], 25, 25) == 1)
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDNVREG_DUMMY_CYCLE = 8;
    }
    else
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDNVREG_DUMMY_CYCLE = 4;
    }

    /* Address bytes needed in 8D for RDSR and REG READ CMDs */
    if(NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[0], 29, 29) == 1)
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDSR_ADDR_BYTES = 4;
    }
    else
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDSR_ADDR_BYTES = 0;
    }

    if(NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[0], 27, 27) == 1)
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDREG_ADDR_BYTES = 4;
    }
    else
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_RDREG_ADDR_BYTES = 1;
    }

    if(NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[0], 23, 23) == 1)
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_WRREG_ADDR_BYTES = 4;
    }
    else
    {
        norSpiDefines->NOR_SPI_OCTAL_DDR_WRREG_ADDR_BYTES = 1;
    }

    /* Get dummy cycles for the fastest speed possible */
    uint32_t dummy = NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[3], 7, 11); /* 200 MHz */
    uint8_t lc = NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[3], 2, 6);

    if(dummy == 0)
    {
        dummy = NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[4], 27, 31); /* 166 MHz */
        lc = NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[4], 22, 26);
    }

    if(dummy == 0)
    {
        dummy = NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[4], 17, 21); /* 133 MHz */
        lc = NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[4], 12, 16);
    }

    if(dummy == 0)
    {
        dummy = NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[4], 7, 11); /* 100 MHz */
        lc = NOR_SPI_SFDP_GET_BITFIELD(xpt1->dwords[3], 2, 6);
    }

    if(dummy == 0)
    {
        DebugP_logError("No dummy cycle found from NOR SPI Profile 1.0 table !!!\r\n");
    }
    else
    {
        /* Timing can mess up if dummy cycle is odd */
        if(dummy % 2 != 0)
        {
            dummy += 1;
            if(lc < 31)
            {
                lc += 1;
            }
        }
        norSpiDefines->NOR_SPI_OCTAL_READ_DUMMY_CYCLE = dummy;
        norSpiDefines->NOR_SPI_OCTAL_READ_DUMMY_CYCLE_LC = lc;
    }

    return status;
}

static void NorSpi_Sfdp_getEraseSizes(NorSpi_SfdpBasicFlashParamTable *bfpt, NorSpi_GenericDevDefines *norSpiDefines)
{
    uint32_t i, blk = 0U, sector = 31U;
    uint32_t blkIdx = 4U;
    uint32_t sectorIdx = 4U;
    uint8_t eraseSizeN[4];
    uint8_t eraseCmd[4];

    eraseSizeN[0] = NOR_SPI_SFDP_GET_BITFIELD(bfpt->eraseType_1_2, 0, 7);
    eraseSizeN[1] = NOR_SPI_SFDP_GET_BITFIELD(bfpt->eraseType_1_2, 16, 23);
    eraseSizeN[2] = NOR_SPI_SFDP_GET_BITFIELD(bfpt->eraseType_3_4, 0, 7);
    eraseSizeN[3] = NOR_SPI_SFDP_GET_BITFIELD(bfpt->eraseType_3_4, 16, 23);

    eraseCmd[0] = NOR_SPI_SFDP_GET_BITFIELD(bfpt->eraseType_1_2, 8, 15);
    eraseCmd[1] = NOR_SPI_SFDP_GET_BITFIELD(bfpt->eraseType_1_2, 24, 31);
    eraseCmd[2] = NOR_SPI_SFDP_GET_BITFIELD(bfpt->eraseType_3_4, 8, 15);
    eraseCmd[3] = NOR_SPI_SFDP_GET_BITFIELD(bfpt->eraseType_3_4, 24, 31);

    for(i = 0; i < 4; i++)
    {
        if((eraseSizeN[i] != 0) && (blk < eraseSizeN[i]))
        {
            blk = eraseSizeN[i];
            blkIdx = i;
        }
    }

    for(i = 0; i < 4; i++)
    {
        if((eraseSizeN[i] != 0) && (sector > eraseSizeN[i]))
        {
            sector = eraseSizeN[i];
            sectorIdx = i;
        }
    }

    norSpiDefines->NOR_SPI_BLOCK_SIZE = (1 << blk);
    norSpiDefines->NOR_SPI_SECTOR_SIZE = (1 << sector);

    if(sectorIdx < 4)
    {
        norSpiDefines->NOR_SPI_CMD_SECTOR_ERASE_3B = eraseCmd[sectorIdx];
        norSpiDefines->NOR_SPI_CMD_SECTOR_ERASE_4B = eraseCmd[sectorIdx];
        norSpiDefines->supportedEraseTypes[0] = sectorIdx;
    }
    else
    {
        norSpiDefines->NOR_SPI_CMD_SECTOR_ERASE_3B = 0;
        norSpiDefines->NOR_SPI_CMD_SECTOR_ERASE_4B = 0;
        norSpiDefines->supportedEraseTypes[0] = 4;
    }

    if(blkIdx < 4)
    {
        norSpiDefines->NOR_SPI_CMD_BLOCK_ERASE_3B = eraseCmd[blkIdx];
        norSpiDefines->NOR_SPI_CMD_BLOCK_ERASE_4B = eraseCmd[blkIdx];

        norSpiDefines->supportedEraseTypes[1] = blkIdx;
    }
    else
    {
        norSpiDefines->NOR_SPI_CMD_BLOCK_ERASE_3B = 0;
        norSpiDefines->NOR_SPI_CMD_BLOCK_ERASE_4B = 0;

        norSpiDefines->supportedEraseTypes[1] = 4;
    }

    /* NOR SPI standard */
    norSpiDefines->NOR_SPI_CMD_BULK_ERASE = 0xC7;
}

static uint8_t NorSpi_Sfdp_getDummyBitPattern(NorSpi_SfdpSCCRParamTable *sccr, uint32_t dummyClk)
{
    uint8_t bitPattern = 0xFF;
    uint32_t dword, isDummy, subVal;

    /* Only support even dummy cycles */
    if((dummyClk % 2) != 0)
    {
        dummyClk += 1;
    }

    /* Find the right DWORD in SCCR */
    if((dummyClk) <= 30 && (dummyClk >= 22))
    {
        dword = sccr->dwords[10];
        subVal = 20;
    }
    else if((dummyClk) <= 20 && (dummyClk >= 12))
    {
        dword = sccr->dwords[11];
        subVal = 10;
    }
    else if((dummyClk) <= 10 && (dummyClk >= 2))
    {
        dword = sccr->dwords[12];
        subVal = 0;
    }
    else
    {
        dword = 0xFFFFFFFFU;
    }

    if(dword != 0xFFFFFFFFU)
    {
        uint32_t dummySupportBit = 3*(dummyClk-subVal)+1;
        isDummy = NOR_SPI_SFDP_GET_BITFIELD(dword, dummySupportBit, dummySupportBit);

        if(isDummy)
        {
            bitPattern = NOR_SPI_SFDP_GET_BITFIELD(dword, (dummySupportBit-5), (dummySupportBit-1));
        }
        else
        {
            bitPattern = 0xFF;
        }
    }

    return bitPattern;
}