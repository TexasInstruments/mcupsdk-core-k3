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

#include <board/flash.h>

#define FLASH_OSPI_ID_CODE_SIZE_MAX (8U)

static int32_t Flash_norOspiErase(Flash_Config *config, uint32_t blkNum);
static int32_t Flash_norOspiRead(Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len);
static int32_t Flash_norOspiWrite(Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len);
static int32_t Flash_norOspiOpen(Flash_Config *config, Flash_Params *params);
static void Flash_norOspiClose(Flash_Config *config);

Flash_Fxns gFlashNorOspiFxns = {

    .openFxn = Flash_norOspiOpen,
    .closeFxn = Flash_norOspiClose,
    .readFxn = Flash_norOspiRead,
    .writeFxn = Flash_norOspiWrite,
    .eraseFxn = Flash_norOspiErase,
};

static int32_t Flash_norOspiCmdRead(Flash_Config *config, uint8_t cmd, uint32_t cmdAddr,
                            uint8_t numAddrBytes, uint8_t *rxBuf, uint32_t rxLen)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);
    OSPI_ReadCmdParams  rdParams;

    OSPI_ReadCmdParams_init(&rdParams);
    rdParams.cmd          = cmd;
    rdParams.cmdAddr      = cmdAddr;
    rdParams.numAddrBytes = numAddrBytes;
    rdParams.rxDataBuf    = rxBuf;
    rdParams.rxDataLen    = rxLen;
    
    status = OSPI_readCmd(obj->ospiHandle, &rdParams);

    return status;
}

static int32_t Flash_norOspiCmdWrite(Flash_Config *config, uint8_t cmd, uint32_t cmdAddr,
                            uint8_t numAddrBytes, uint8_t *txBuf, uint32_t txLen)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);
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

static int32_t Flash_norOspiWaitReady(Flash_Config *config, uint32_t timeOut)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;
    Flash_NorXspiObject *obj = (Flash_NorXspiObject *)(config->object);
    
    uint8_t readStatus = 0U;
    uint8_t cmd;
    uint32_t cmdAddr;
    uint8_t numAddrBytes;

    cmd = devDefines->NOR_CMD_RDSR;
    
    if(obj->xferLines == OSPI_XFER_LINES_OCTAL)
    {
        cmdAddr     = 0;
        numAddrBytes = 4;
    }
    else
    {
        cmdAddr = OSPI_CMD_INVALID_ADDR;
        numAddrBytes = 0;
    }

    status = Flash_norOspiCmdRead(config, cmd, cmdAddr, numAddrBytes, &readStatus, 1);

    while((status != SystemP_SUCCESS) || timeOut > 0)
    {
        status = Flash_norOspiCmdRead(config, cmd, cmdAddr, numAddrBytes, &readStatus, 1);

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

static int32_t Flash_norOspiRegRead(Flash_Config *config, uint32_t regAddr, uint8_t *data)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t cmd;
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;

    cmd     = devDefines->NOR_CMD_RDCR2;

    status = Flash_norOspiCmdRead(config, cmd, regAddr, 4, data, 1);

    return status;
}

static int32_t Flash_norOspiRegWrite(Flash_Config *config, uint32_t regAddr, uint8_t data)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t cmd, regData;
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;

    cmd    = devDefines->NOR_CMD_WREN;

    status = Flash_norOspiCmdWrite(config, cmd, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

    if(status == SystemP_SUCCESS)
    {
        status = Flash_norOspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
    }
    if(status == SystemP_SUCCESS)
    {
        cmd    = devDefines->NOR_CMD_WRCR2;
        regData = data;

        status = Flash_norOspiCmdWrite(config, cmd, regAddr, 4, &regData, 1);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norOspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
    }

    return status;
}

static int32_t Flash_norOspiResetMemory(Flash_Config *config)
{
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;
    int32_t status;
    uint8_t cmd;

    /* Send Reset Enable command */
    cmd = devDefines->NOR_CMD_RSTEN;
    status = Flash_norOspiCmdWrite(config, cmd, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    if (status == SystemP_SUCCESS)
    {
        /* Send Reset Device Memory command */
        cmd = devDefines->NOR_CMD_RST_MEM;
        status = Flash_norOspiCmdWrite(config, cmd, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }
    return (status);
}

static int32_t Flash_norOspiReadId(Flash_Config *config)
{
    int32_t  status;
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;
    Flash_NorXspiObject *obj = (Flash_NorXspiObject *)(config->object);
    uint8_t  idCode[FLASH_OSPI_ID_CODE_SIZE_MAX];
    uint8_t  cmd = OSPI_CMD_INVALID_OPCODE;
    uint32_t cmdAddr = OSPI_CMD_INVALID_ADDR;
    uint8_t  numAddrBytes = 0U;
    uint32_t numRdIdBytes = 0U;

    DebugP_assert(FLASH_OSPI_ID_CODE_SIZE_MAX >= devDefines->NOR_RDID_NUM_BYTES);

    cmd = devDefines->NOR_CMD_RDID;

    if(obj->xferLines == OSPI_XFER_LINES_OCTAL)
    {
        cmdAddr = 0U;
        numAddrBytes = 4U;
        numRdIdBytes = 2 * devDefines->NOR_RDID_NUM_BYTES - 1;
    }
    else
    {
        cmdAddr = OSPI_CMD_INVALID_ADDR;
        numAddrBytes = 0U;
        numRdIdBytes = devDefines->NOR_RDID_NUM_BYTES;
    }

    status = Flash_norOspiCmdRead(config, cmd, cmdAddr, numAddrBytes, idCode, numRdIdBytes);

    if (status == SystemP_SUCCESS)
    {
        uint32_t manfID, devID;

        manfID = (uint32_t)idCode[0];
        devID = ((uint32_t)idCode[2] << 8) | ((uint32_t)idCode[4]);
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

    return status;
}

static int32_t Flash_norOspiEnableDDR(Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;
    uint8_t regData = 0x02;

    /* Enable DDR in Flash */
    /* Send Write Enable command */
    status = Flash_norOspiCmdWrite(config, devDefines->NOR_CMD_WREN, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

    if(status == SystemP_SUCCESS)
    {
        status = Flash_norOspiCmdWrite(config, devDefines->NOR_CMD_WRCR2, devDefines->NOR_DDR_EN_REG_ADDR, 4, &regData, 1);
    }

    /* Enable DDR in OSPI controller */
    if(status == SystemP_SUCCESS)
    {
        status = OSPI_enableDDR(obj->ospiHandle);
    }

    return status;
}

static int32_t Flash_norOspiEnableSDR(Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;
    uint8_t regData = 0x01;

    /* Enable SDR in Flash */
    /* Send Write Enable command */
    status = Flash_norOspiCmdWrite(config, devDefines->NOR_CMD_WREN, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

    if(status == SystemP_SUCCESS)
    {
        status = Flash_norOspiCmdWrite(config, devDefines->NOR_CMD_WRCR2, devDefines->NOR_DDR_EN_REG_ADDR, 4, &regData, 1);
    }

    /* Enable SDR in OSPI controller */
    if(status == SystemP_SUCCESS)
    {
        status = OSPI_enableSDR(obj->ospiHandle);
    }

    return status;
}

static int32_t Flash_norOspiSetDummyCycles(Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;
    uint32_t rdDummyCycles = 0U;
    uint32_t cmdDummyCycles = 0U;
    uint32_t latencyCode = 0U;

    /* Set dummyCycles for cmd read and normal read in OSPI controller */
    if(obj->xferLines == OSPI_XFER_LINES_OCTAL)
    {
        rdDummyCycles = devDefines->NOR_OCTAL_READ_DUMMY_CYCLE;
        latencyCode = devDefines->NOR_OCTAL_READ_LC;

        if(obj->dtrEnable)
        {
            cmdDummyCycles = devDefines->NOR_OCTAL_CMD_READ_DUMMY_CYCLE;
        }
        else
        {
            cmdDummyCycles = devDefines->NOR_OCTAL_CMD_READ_DUMMY_CYCLE;
        }
    }
    else
    {
        cmdDummyCycles = devDefines->NOR_SINGLE_CMD_READ_DUMMY_CYCLE;
    }

    OSPI_setReadDummyCycles(obj->ospiHandle, rdDummyCycles);
    OSPI_setCmdDummyCycles(obj->ospiHandle, cmdDummyCycles);

    if(obj->xferLines == OSPI_XFER_LINES_OCTAL)
    {
        /* Set dual opcode mode */
        OSPI_setDualOpCodeMode(obj->ospiHandle);

        uint8_t regData = 0xFFU;

        /* Set the latency code in flash device corresponding the read dummy cycles set in OSPI */
        status = Flash_norOspiRegRead(config, 0x300, &regData);

        if(SystemP_SUCCESS == status)
        {
            /* Set the dummy cycle */
            regData = (regData & ~0xF) | latencyCode;

            /* Write configuration register 2 */
            status = Flash_norOspiRegWrite(config, 0x300, regData);
        }

        status = Flash_norOspiRegRead(config, 0x300, &regData);
    }    

    return status;
}

static void Flash_norOspiSetOpcodes(Flash_Config *config)
{
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;
    uint32_t readCmd = OSPI_CMD_INVALID_OPCODE;
    uint32_t progCmd = OSPI_CMD_INVALID_OPCODE;

    if(obj->xferLines == OSPI_XFER_LINES_OCTAL)
    {
        if(obj->dtrEnable == TRUE)
        {
            readCmd     = devDefines->NOR_CMD_OCTAL_READ_DDR;
        }
        else
        {
            readCmd     = devDefines->NOR_CMD_OCTAL_READ_SDR;
        }

        progCmd     = devDefines->NOR_CMD_PAGE_PROG;
    }
    else
    {   
        /* Set to legacy SPI mode 1-1-1 if not Octal mode */
        readCmd    = devDefines->NOR_CMD_READ;
        progCmd    = devDefines->NOR_CMD_PAGE_PROG;
    }

    OSPI_setXferLines(obj->ospiHandle, obj->xferLines);
    OSPI_setXferOpCodes(obj->ospiHandle, readCmd, progCmd);
}

static int32_t Flash_norOspiOpen(Flash_Config *config, Flash_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);
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
        OSPI_setCmdExtType(obj->ospiHandle, OSPI_CMD_EXT_TYPE_INVERSE);

        /* Check if DDR is enabled in SysConfig */
        obj->dtrEnable = OSPI_isDtrEnable(obj->ospiHandle);

        if (OSPI_getXferLines(obj->ospiHandle) == OSPI_XFER_LINES_OCTAL)
        {
            /* Enable DDR or SDR mode for Octal lines */
            if (obj->dtrEnable)
            {
                Flash_norOspiEnableDDR(config);

                /* Set number of address bytes */
                OSPI_setNumAddrBytes(obj->ospiHandle, 4);
            }
            else
            {
                Flash_norOspiEnableSDR(config);
            }

            obj->xferLines = OSPI_XFER_LINES_OCTAL;
        }
        else
        {
            /* Reset device memory for all the other lines */
            Flash_norOspiResetMemory(config);
        }

        /* Set read/write opcodes */
        Flash_norOspiSetOpcodes(config);

        /* Set dummyCycles in OSPI controller and corresponding latencyCode to flash */
        Flash_norOspiSetDummyCycles(config);
        
        uint32_t readDataCapDelay = 4U;
        OSPI_setRdDataCaptureDelay(obj->ospiHandle, readDataCapDelay);
        status = Flash_norOspiReadId(config);

        while((status != SystemP_SUCCESS) && (readDataCapDelay >= 0U))
        {
            readDataCapDelay--;
            OSPI_setRdDataCaptureDelay(obj->ospiHandle, readDataCapDelay);
            status = Flash_norOspiReadId(config);
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
                Flash_norOspiErase(config, blk);
                Flash_norOspiWrite(config, phyTuningOffset, (uint8_t *)phyTuningData, phyTuningDataSize);
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

    return (status);
}

static void Flash_norOspiClose(Flash_Config *config)
{
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);

    obj->ospiHandle = NULL;

    /* OSPI Driver will be closed outside flash */

    return;
}

static int32_t Flash_norOspiRead(Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);
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

static int32_t Flash_norOspiWrite(Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiObject *obj = (Flash_NorOspiObject *)(config->object);
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;
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
            status = Flash_norOspiCmdWrite(config, cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

            if(status == SystemP_SUCCESS)
            {
                status = Flash_norOspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
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
                status = Flash_norOspiWaitReady(config, devDefines->NOR_PAGE_PROG_TIMEOUT);
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

static int32_t Flash_norOspiErase(Flash_Config *config, uint32_t blkNum)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NorOspiDevDefines *devDefines = (Flash_NorOspiDevDefines *)config->devDefines;

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
        status = Flash_norOspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norOspiCmdWrite(config, cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norOspiWaitReady(config, devDefines->NOR_WRR_WRITE_TIMEOUT);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norOspiCmdWrite(config, cmd, cmdAddr, 4, NULL, 0);
    }
    if(status == SystemP_SUCCESS)
    {
        status = Flash_norOspiWaitReady(config, devDefines->NOR_BULK_ERASE_TIMEOUT);
    }
    return status;
}
