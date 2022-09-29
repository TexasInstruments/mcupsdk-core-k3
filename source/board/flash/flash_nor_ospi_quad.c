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


#include <board/flash.h>

#define FLASH_QSPI_ID_CODE_SIZE_MAX (8U)

static int32_t Flash_norQspiErase(Flash_Config *config, uint32_t blkNum);
static int32_t Flash_norQspiRead(Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len);
static int32_t Flash_norQspiWrite(Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len);
static int32_t Flash_norQspiOpen(Flash_Config *config, Flash_Params *params);
static void Flash_norQspiClose(Flash_Config *config);

/* Defualt value of command address length */
static uint8_t cmdAddrLen = 3;

/* NOR function table for NOR OSPI interface implementation */
Flash_Fxns gFlashNorQspiFxns = {

    .openFxn = Flash_norQspiOpen,
    .closeFxn = Flash_norQspiClose,
    .readFxn = Flash_norQspiRead,
    .writeFxn = Flash_norQspiWrite,
    .eraseFxn = Flash_norQspiErase,
};

static int32_t Flash_norQspiCmdWrite(Flash_Config *config, uint8_t cmd, uint32_t cmdAddr,
                                     uint8_t numAddrBytes, uint8_t *txBuf, uint32_t txLen)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);
    OSPI_WriteCmdParams wrParams;

    OSPI_WriteCmdParams_init(&wrParams);
    wrParams.cmd          = cmd;
    wrParams.cmdAddr      = cmdAddr;
    wrParams.numAddrBytes = numAddrBytes;
    wrParams.txDataBuf    = txBuf;
    wrParams.txDataLen    = txLen;

    status = OSPI_writeCmd(obj->ospiHandle, &wrParams);

    return status;
}

static int32_t Flash_norQspiCmdRead(Flash_Config *config, uint8_t cmd, uint32_t cmdAddr,
                            uint8_t numAddrBytes, uint8_t *rxBuf, uint32_t rxLen)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);
    OSPI_ReadCmdParams  rdParams;

    OSPI_ReadCmdParams_init(&rdParams);
    rdParams.cmd           = cmd;
    rdParams.cmdAddr       = cmdAddr;
    rdParams.numAddrBytes  = numAddrBytes;
    rdParams.rxDataBuf     = rxBuf;
    rdParams.rxDataLen     = rxLen;

    status = OSPI_readCmd(obj->ospiHandle, &rdParams);

    return status;
}

static int32_t Flash_norQspiWaitReady(Flash_Config *config, uint32_t timeOut)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;

    uint8_t  readStatus = 0;
    uint8_t  cmd, numAddrBytes;
    uint32_t cmdAddr;

    cmd           = devDefines->NOR_CMD_RDSR;
    numAddrBytes  = OSPI_CMD_INVALID_OPCODE;
    cmdAddr       = OSPI_CMD_INVALID_ADDR;

    status = Flash_norQspiCmdRead(config, cmd, cmdAddr, numAddrBytes, &readStatus, 1);

    while((status != SystemP_SUCCESS) || timeOut > 0)
    {
        status = Flash_norQspiCmdRead(config, cmd, cmdAddr, numAddrBytes, &readStatus, 1);

        if((status == SystemP_SUCCESS) && ((readStatus & devDefines->NOR_SR_WIP) == 0))
        {
            break;
        }

        timeOut--;
    }

    if((readStatus & devDefines->NOR_SR_WIP)==0)
    {
        status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t Flash_norQspiRegRead(Flash_Config *config, uint32_t regAddr, uint8_t *data)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t cmd;
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;

    cmd    = devDefines->NOR_CMD_RDREG;

    status = Flash_norQspiCmdRead(config, cmd, regAddr, cmdAddrLen, data, 1);

    return status;
}

static int32_t Flash_norQspiRegWrite(Flash_Config *config, uint32_t regAddr, uint8_t data)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t cmd, regData;
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;

    cmd    = devDefines->NOR_CMD_WREN;

    status = Flash_norQspiCmdWrite(config, cmd, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

    if(SystemP_SUCCESS == status)
    {
        status = Flash_norQspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
    }

    if(status == SystemP_SUCCESS)
    {
        cmd    = devDefines->NOR_CMD_WRREG;
        regData = data;

        status = Flash_norQspiCmdWrite(config, cmd, regAddr, cmdAddrLen, &regData, 1);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norQspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
    }

    return status;
}

static int32_t Flash_norQspiResetMemory(Flash_Config *config)
{
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;
    int32_t status;
    uint8_t cmd;

    /* Send Reset Enable command */
    cmd = devDefines->NOR_CMD_SRSTE;
    status = Flash_norQspiCmdWrite(config, cmd, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    if (status == SystemP_SUCCESS)
    {
        /* Send Reset Device Memory command */
        cmd = devDefines->NOR_CMD_SFRST;
        status = Flash_norQspiCmdWrite(config, cmd, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }
    return (status);
}

static int32_t Flash_norQspiSetAddrLen(Flash_Config *config, uint32_t AddrLen)
{
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);
    uint8_t  regData = 0;

    uint8_t  cmd;
    uint32_t   regAddr;
    int32_t status;

    status = Flash_norQspiRegRead(config, devDefines->NOR_CFG2_VREG_ADDR, &regData);

    if(status == SystemP_SUCCESS)
    {
        /* Send Write Enable command */
        status = Flash_norQspiCmdWrite(config, devDefines->NOR_CMD_WREN, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }

    if(status == SystemP_SUCCESS)
    {

        regAddr = devDefines->NOR_CFG2_VREG_ADDR;
        cmd    = devDefines->NOR_CMD_WRREG;

        /* Setting the address bytes */
        if(AddrLen == 4)
        {
            regData = regData | 0x80;
            status = Flash_norQspiCmdWrite(config, cmd, regAddr, cmdAddrLen, &regData, 1);
            cmdAddrLen = 4;
        }
        /* Set number of address bytes */
        OSPI_setNumAddrBytes(obj->ospiHandle, cmdAddrLen);
    }
    return status;
}

static int32_t Flash_norQspiSetQuadDataWidth(Flash_Config *config, uint8_t enable)
{
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;
    uint8_t  regData = 0;
    uint8_t  cmd;
    uint32_t regAddr;

    int32_t status;

    status = Flash_norQspiRegRead(config, devDefines->NOR_CFG2_VREG_ADDR, &regData);

    if(SystemP_SUCCESS == status)
    {
        if(enable == 1)
        {
            if((regData & 0x40) != 0)
            {
                /* Quad data width configuration is already in enabled state.
                   Setting data width to quad bits from OSPI Control
                   register */
                return SystemP_SUCCESS;
            }
            else
            {
                /* Enable Quad data width configuration */
                regData |= 0x40;
            }
        }
        else
        {
            if((regData & 0x40) == 0)
            {
                /* Quad data width configuration is already in disabled state */
                return SystemP_SUCCESS;
            }
            else
            {
                /* Disable Quad data width configuration */
                regData &= ~0x40;
            }
        }

        /* Send Write Enable command */
        status = Flash_norQspiCmdWrite(config, devDefines->NOR_CMD_WREN, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

        if(status == SystemP_SUCCESS)
        {
            status = Flash_norQspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
        }

         if(status == SystemP_SUCCESS)
        {

            regAddr = devDefines->NOR_CFG2_VREG_ADDR;
            cmd    = devDefines->NOR_CMD_WRREG;
            status = Flash_norQspiCmdWrite(config, cmd, regAddr, cmdAddrLen, &regData, 1);
        }

    }

    return status;
}

static int32_t Flash_norQspiHybridSectCfg(Flash_Config *config,
                                           uint8_t enable,
                                           uint32_t cfgFlag)
{
    int32_t status = 0;
    uint8_t regData = 0;

    /* Read configuration register3 */
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;

    status = Flash_norQspiRegRead(config, devDefines->NOR_CFG3_VREG_ADDR, &regData);

    if(status == SystemP_SUCCESS)
    {

        if(enable == 1)
        {
            if((regData & 0x8) == 0)
            {
                /* Hybrid sector configuration is already in enabled state.
                   No further action needed */
                return SystemP_SUCCESS;
            }
            else
            {
                /* Enable hybrid sector configuration */
                regData &= ~0x8;
            }
        }
        else
        {
            if((regData & 0x8) != 0)
            {
                /* Hybrid sector configuration is already in disabled state.
                   No further action needed */
                return SystemP_SUCCESS;
            }
            else
            {
                /* Disable hybrid sector configuration */
                regData |= 0x8;
            }
        }
    }
    /* Write configuration register3 */
    status = Flash_norQspiRegWrite(config, devDefines->NOR_CFG3_NVREG_ADDR, regData);

    return status;

}

static int32_t Flash_norQspiReadId(Flash_Config *config)
{
    int32_t  status;
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;
    uint8_t  idCode[FLASH_QSPI_ID_CODE_SIZE_MAX];
    uint8_t  cmd = OSPI_CMD_INVALID_OPCODE;
    uint32_t cmdAddr = OSPI_CMD_INVALID_ADDR;
    uint8_t  numAddrBytes = 0;

    DebugP_assert(FLASH_QSPI_ID_CODE_SIZE_MAX >= devDefines->NOR_RDID_NUM_BYTES);

    cmd     = devDefines->NOR_CMD_RDID;
    cmdAddr = OSPI_CMD_INVALID_ADDR;
    numAddrBytes = 0U;

    status = Flash_norQspiCmdRead(config, cmd, cmdAddr, numAddrBytes, idCode, devDefines->NOR_RDID_NUM_BYTES);
    if (status == SystemP_SUCCESS)
    {
        uint32_t manfID, devID;

        manfID = (uint32_t)idCode[0];
        devID = ((uint32_t)idCode[1] << 8) | ((uint32_t)idCode[2]);
        if ((manfID == devDefines->NOR_MANF_ID) && (devID == devDefines->NOR_DEVICE_ID))
        {
            config->attrs->manufacturerId = manfID;
            config->attrs->deviceId = devID;
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
    return (status);
}

static int32_t Flash_norQspiEnableDDR(Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);

    /* Disable DDR in OSPI controller CONFIG_REG */
    status = OSPI_enableSDR(obj->ospiHandle);

    if(status == SystemP_SUCCESS)
    {
        /* Enable DTR in INSTR_RD register for RD commands */
        status = OSPI_enableDdrRdCmds(obj->ospiHandle);
    }

    return status;
}

static int32_t Flash_norQspiEnableSDR(Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);

    /* Enable DDR in OSPI controller */
    status = OSPI_enableSDR(obj->ospiHandle);

    return status;
}

static int32_t Flash_norQspiSetDummyCycles(Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;
    uint32_t rdDummyCycles = 0U;
    uint32_t cmdDummyCycles = 0U;
    uint32_t latencyCode = 0U;

    if (obj->xferLines == OSPI_XFER_LINES_QUAD)
    {
        rdDummyCycles = devDefines->NOR_QUAD_READ_DUMMY_CYCLE;
        latencyCode = devDefines->NOR_QUAD_READ_DUMMY_CYCLE_LC;

        if(obj->dtrEnable)
        {
            cmdDummyCycles = devDefines->NOR_QUAD_DDR_CMD_READ_DUMMY_CYCLE;
        }
        else
        {
            cmdDummyCycles = devDefines->NOR_QUAD_SDR_CMD_READ_DUMMY_CYCLE;
        }
    }
    else
    {
        cmdDummyCycles = devDefines->NOR_SINGLE_CMD_READ_DUMMY_CYCLE;
    }

    OSPI_setReadDummyCycles(obj->ospiHandle, rdDummyCycles);
    OSPI_setCmdDummyCycles(obj->ospiHandle, cmdDummyCycles);

    if(obj->xferLines == OSPI_XFER_LINES_QUAD)
    {

        OSPI_rdModeBitSet(obj->ospiHandle, 1);

        uint8_t regData = 0U;

        /* Set the latency code in flash device corresponding the read dummy cycles set in OSPI */
        status = Flash_norQspiRegRead(config, devDefines->NOR_CFG2_VREG_ADDR, &regData);

        if(SystemP_SUCCESS == status)
        {
            /* Set the dummy cycle */
            regData = (regData & ~0xF) | latencyCode;

            /* Write configuration register 2 */
            status = Flash_norQspiRegWrite(config, devDefines->NOR_CFG2_VREG_ADDR, regData);
        }
    }

    return status;
}

static void Flash_norQspiSetOpcodes(Flash_Config *config)
{
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;
    uint32_t readCmd = OSPI_CMD_INVALID_OPCODE;
    uint32_t progCmd = OSPI_CMD_INVALID_OPCODE;

    if(obj->xferLines == OSPI_XFER_LINES_QUAD)
    {
        if(obj->dtrEnable == TRUE)
        {
            readCmd        = devDefines->NOR_CMD_QUAD_DDR_READ;
        }
        else
        {
            readCmd        = devDefines->NOR_CMD_QUAD_SDR_READ;
        }

        progCmd    = devDefines->NOR_CMD_QUAD_PROG;
    }
    else
    {
        /* Set to legacy SPI mode 1-1-1 if not Quad mode */
        readCmd    = devDefines->NOR_CMD_READ;
        progCmd    = devDefines->NOR_CMD_PAGE_PROG;
    }

    OSPI_setXferLines(obj->ospiHandle, obj->xferLines);
    OSPI_setXferOpCodes(obj->ospiHandle, readCmd, progCmd);

}

static int32_t Flash_norQspiSetMode1s1s4s(Flash_Config *config)
{
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;
    uint8_t  regData = 0;
    int32_t status = SystemP_SUCCESS;

    status = Flash_norQspiRegRead(config, devDefines->NOR_CFG1_VREG_ADDR, &regData);

    if(SystemP_SUCCESS == status)
    {
        if((regData & 0x02) == 0)
        {
            /* Enable Quad data width configuration */
            regData |= 0x02;
            /* Write NV configuration register1 */
            status = Flash_norQspiRegWrite(config, devDefines->NOR_CFG1_NVREG_ADDR, regData);
        }
    }

    return status;
}

static int32_t Flash_norQspiOpen(Flash_Config *config, Flash_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);
    Flash_Attrs *attrs = config->attrs;
    int32_t attackVectorStatus = SystemP_FAILURE;

    obj->ospiHandle = OSPI_getHandle(config->attrs->driverInstance);

    if(obj->ospiHandle==NULL)
    {
        status = SystemP_FAILURE;
    }
    if(status == SystemP_SUCCESS)
    {
        /* Set device size and addressing bytes */
        OSPI_setDeviceSize(obj->ospiHandle, attrs->pageSize, attrs->blockSize);

        /* Set command opcode extension type */
        OSPI_setCmdExtType(obj->ospiHandle, OSPI_CMD_EXT_TYPE_NONE);

        /* Get the transfer lines selected in SysConfig */
        obj->xferLines = OSPI_getXferLines(obj->ospiHandle);

        /* Check if DDR is enabled in SysConfig */
        obj->dtrEnable = OSPI_isDtrEnable(obj->ospiHandle);

        status = Flash_norQspiSetAddrLen(config, 4);

        /* Setting flash in 1S-1S-4S mode in Non-Volatile register
           which is required by RoM code */
        status = Flash_norQspiSetMode1s1s4s(config);

        if(status == SystemP_SUCCESS)
        {
            /* Set flash to 4-4-4 mode */
            status = Flash_norQspiSetQuadDataWidth(config, 1);
        }

        if (obj->xferLines == OSPI_XFER_LINES_QUAD)
        {
            /* Enable DDR or SDR mode for QUAD lines */
            if (obj->dtrEnable)
            {
                Flash_norQspiEnableDDR(config);
            }
            else
            {
                Flash_norQspiEnableSDR(config);
            }
        }
        else
        {
            /* Reset device memory for all the other lines */
            Flash_norQspiResetMemory(config);
        }

        if(status == SystemP_SUCCESS)
        {
            /* Set read/write opcodes */
            Flash_norQspiSetOpcodes(config);

            /* Set dummyCycles in OSPI controller and corresponding latencyCode to flash */
            Flash_norQspiSetDummyCycles(config);

            /* Disable hybrid sector configuration */
            status = Flash_norQspiHybridSectCfg(config, 0, 0);

            uint32_t readDataCapDelay = 4U;
            OSPI_setRdDataCaptureDelay(obj->ospiHandle, readDataCapDelay);
            status = Flash_norQspiReadId(config);

            while((status != SystemP_SUCCESS) && (readDataCapDelay >= 0U))
            {
                readDataCapDelay--;
                OSPI_setRdDataCaptureDelay(obj->ospiHandle, readDataCapDelay);
                status = Flash_norQspiReadId(config);
            }

            /* Enable PHY if attack vector present and PHY mode is enabled */
            uint32_t phyTuningOffset = Flash_getPhyTuningOffset(config);
            if(OSPI_isPhyEnable(obj->ospiHandle))
            {
                attackVectorStatus = OSPI_phyReadAttackVector(obj->ospiHandle, phyTuningOffset);

                if(attackVectorStatus != SystemP_SUCCESS)
                {
                    /* Flash the attack vector to the last block */
                    uint32_t blk = 0, page = 0;
                    uint32_t phyTuningData = 0,phyTuningDataSize = 0;
                    OSPI_phyGetTuningData(&phyTuningData, &phyTuningDataSize);
                    Flash_offsetToBlkPage(config, phyTuningOffset, &blk, &page);
                    Flash_norQspiErase(config, blk);
                    Flash_norQspiWrite(config, phyTuningOffset, (uint8_t *)phyTuningData, phyTuningDataSize);
                    attackVectorStatus = OSPI_phyReadAttackVector(obj->ospiHandle, phyTuningOffset);
                }

                if(attackVectorStatus == SystemP_SUCCESS)
                {
                    status += OSPI_phyTuneDDR(obj->ospiHandle, phyTuningOffset);
                    if(status == SystemP_SUCCESS)
                    {
                        obj->phyEnable = TRUE;
                        OSPI_setPhyEnableSuccess(obj->ospiHandle, TRUE);
                    }
                }
                else
                {
                    DebugP_logError("%s : PHY enabling failed!!! Continuing without PHY...\r\n", __func__);
                    obj->phyEnable = FALSE;
                    OSPI_setPhyEnableSuccess(obj->ospiHandle, FALSE);
                }
            }
            else
            {
                obj->phyEnable = FALSE;
            }
        }
    }
    return (status);
}

static void Flash_norQspiClose(Flash_Config *config)
{
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);

    obj->ospiHandle = NULL;

    /* OSPI Driver will be closed outside flash */

    return;
}

static int32_t Flash_norQspiRead(Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);
    Flash_Attrs *attrs = config->attrs;

    if(obj->phyEnable)
    {
        OSPI_enablePhy(obj->ospiHandle);
    }

    /* Validate address input */
    if ((offset + len) > (attrs->blockCount*attrs->pageCount*attrs->pageSize))
    {
        status = SystemP_FAILURE;
    }
    if (status == SystemP_SUCCESS)
    {
        OSPI_Transaction transaction;

        OSPI_Transaction_init(&transaction);
        transaction.addrOffset = offset;
        transaction.buf = (void *)buf;
        transaction.count = len;
        status = OSPI_readDirect(obj->ospiHandle, &transaction);
    }

    if(obj->phyEnable)
    {
        OSPI_disablePhy(obj->ospiHandle);
    }

    return status;
}

static int32_t Flash_norQspiWrite(Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiObject *obj = (Flash_NorQspiObject *)(config->object);
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;
    Flash_Attrs *attrs = config->attrs;

    /* Validate address input */
    if ((offset + len) > (attrs->blockCount*attrs->pageCount*attrs->pageSize))
    {
        status = SystemP_FAILURE;
    }
    /* Check offset alignment */
    if(0 != (offset % attrs->pageSize))
    {
        status = SystemP_FAILURE;
    }
    if(status == SystemP_SUCCESS)
    {
        uint32_t pageSize, chunkLen, actual;
        uint8_t cmdWren = devDefines->NOR_CMD_WREN;
        OSPI_Transaction transaction;

        pageSize = devDefines->NOR_PAGE_SIZE;
        chunkLen = pageSize;

        for (actual = 0; actual < len; actual += chunkLen)
        {
            status = Flash_norQspiCmdWrite(config, cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

            if(status == SystemP_SUCCESS)
            {
                status = Flash_norQspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
            }

            if(status == SystemP_SUCCESS)
            {
                /* Send Page Program command */
                if((len - actual) < (pageSize))
                {
                    chunkLen = (len - actual);
                }
                else
                {
                    chunkLen = pageSize;
                }

                OSPI_Transaction_init(&transaction);
                transaction.addrOffset = offset;
                transaction.buf = (void *)(buf + actual);
                transaction.count = chunkLen;
                /* Only indirect writes supported in this PHY */
                status = OSPI_writeIndirect(obj->ospiHandle, &transaction);
            }

            if(status == SystemP_SUCCESS)
            {
                status = Flash_norQspiWaitReady(config, devDefines->NOR_PAGE_PROG_TIMEOUT);
            }

            if(status == SystemP_SUCCESS)
            {
                offset += chunkLen;
            }
            else
            {
                break;
            }
        }
    }

    return status;
}

static int32_t Flash_norQspiErase(Flash_Config *config, uint32_t blkNum)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorQspiDevDefines *devDefines = (Flash_NorQspiDevDefines *)config->devDefines;

    uint8_t  cmd = OSPI_CMD_INVALID_OPCODE;
    uint32_t cmdAddr = OSPI_CMD_INVALID_ADDR;
    uint8_t  cmdWren = devDefines->NOR_CMD_WREN;

    if (blkNum == (uint32_t)(-1))
    {
        cmd    = devDefines->NOR_CMD_BULK_ERASE;
    }
    else
    {
        cmdAddr = blkNum * config->attrs->pageCount * config->attrs->pageSize;
        cmd = devDefines->NOR_CMD_BLOCK_ERASE;

        if (blkNum >= config->attrs->blockCount)
        {
            status = SystemP_FAILURE;
        }
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norQspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norQspiCmdWrite(config, cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norQspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norQspiCmdWrite(config, cmd, cmdAddr, cmdAddrLen, NULL, 0);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norQspiWaitReady(config, devDefines->NOR_BULK_ERASE_TIMEOUT);
    }

    return status;
}
