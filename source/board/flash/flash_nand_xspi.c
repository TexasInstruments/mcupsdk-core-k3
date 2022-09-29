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

#include <board/flash.h>
#include <kernel/dpl/CacheP.h>
#include <drivers/hw_include/cslr.h>



#define FLASH_PAGE_SPARE_ARRAY_SIZE_BYTES               128U

static int32_t Flash_nandXspiOpen (Flash_Config *config, Flash_Params *params);
static void Flash_nandXspiClose (Flash_Config *config);
static int32_t Flash_nandXspiRead (Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len);
static int32_t Flash_nandXspiWrite (Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len);
static int32_t Flash_nandXspiErase (Flash_Config *config, uint32_t blkNum);

static int32_t Flash_nandXspiDisableWriteProtection (Flash_Config *config);
static int32_t Flash_nandXspiSetDummyCycles (Flash_Config *config);
static int32_t Flash_nandXspiCmdRead (Flash_Config *config, uint8_t cmd, uint32_t cmdAddr,
                            uint8_t numAddrBytes, uint8_t *rxBuf, uint32_t rxLen);
static int32_t Flash_nandXspiCmdWrite (Flash_Config *config, uint8_t cmd, uint32_t cmdAddr,
                                     uint8_t numAddrBytes, uint8_t *txBuf, uint32_t txLen);
static int32_t Flash_nandXspiWaitReady (Flash_Config *config, uint32_t timeOut);
static int32_t Flash_nandXspiEnableDDR (Flash_Config *config);
static void Flash_nandXspiSetOpcodes (Flash_Config *config);
static int32_t Flash_NandXspiReadId (Flash_Config *config);
static int32_t Flash_NandXspiWriteDirect (Flash_Config *config, OSPI_Transaction *trans);
static int32_t Flash_NandXspiResetMemory (Flash_Config *config);

Flash_Fxns gFlashNandXspiFxns = {
    .openFxn = Flash_nandXspiOpen,
    .closeFxn = Flash_nandXspiClose,
    .readFxn = Flash_nandXspiRead,
    .writeFxn = Flash_nandXspiWrite,
    .eraseFxn = Flash_nandXspiErase,
};

static int32_t Flash_nandXspiOpen (Flash_Config *config, Flash_Params *params)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiObject *obj = (Flash_NandXspiObject *)(config->object);
    Flash_Attrs *attrs = config->attrs;

    obj->ospiHandle = OSPI_getHandle (attrs->driverInstance);

    if(obj->ospiHandle==NULL)
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        /* Set device size and addressing bytes */
        OSPI_setDeviceSize (obj->ospiHandle, attrs->pageSize, attrs->blockSize);

        /* Set command opcode extension type */
        OSPI_setCmdExtType (obj->ospiHandle, OSPI_CMD_EXT_TYPE_REPEAT);

        /* Get the transfer lines selected in SysConfig */
        obj->xferLines = OSPI_getXferLines (obj->ospiHandle);

        /* Check if DDR is enabled in SysConfig */
        obj->dtrEnable = OSPI_isDtrEnable (obj->ospiHandle);

        if (obj->xferLines == OSPI_XFER_LINES_OCTAL)
        {
            /* Disable Write protection */
            status = Flash_nandXspiDisableWriteProtection (config);

            /* Set read dummy cycles */
            if (status == SystemP_SUCCESS)
            {
                status = Flash_nandXspiSetDummyCycles (config);
            }

            if (status == SystemP_SUCCESS)
            {
                if (obj->dtrEnable)
                {
                    status = Flash_nandXspiEnableDDR (config);
                }
            }
        }
        else
        {
            status =  Flash_NandXspiResetMemory (config);

            if (status == SystemP_SUCCESS)
            {
                /* Disable Write protection */
                status = Flash_nandXspiDisableWriteProtection (config);
            }

            /* Set read dummy cycles */
            if (status == SystemP_SUCCESS)
            {
                status = Flash_nandXspiSetDummyCycles (config);
            }
        }
    }

    if (status == SystemP_SUCCESS)
    {

        Flash_nandXspiSetOpcodes (config);

        uint32_t readDataCapDelay = 4U;
        OSPI_setRdDataCaptureDelay (obj->ospiHandle, readDataCapDelay);
        status = Flash_NandXspiReadId (config);

        while((status != SystemP_SUCCESS) && (readDataCapDelay > 0U))
        {
            readDataCapDelay--;
            OSPI_setRdDataCaptureDelay (obj->ospiHandle, readDataCapDelay);
            status = Flash_NandXspiReadId (config);
        }

    }

    return status;
}

static void Flash_nandXspiClose (Flash_Config *config)
{
    Flash_NandXspiObject *obj = (Flash_NandXspiObject *)(config->object);

    /* Reset the flash such other modules can
    initialise the Flash config registers again*/

    (void)Flash_NandXspiResetMemory(config);

    obj->ospiHandle = NULL;

    /* OSPI Driver will be closed outside flash */

    return;
}

static int32_t Flash_nandXspiRead (Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiDeviceDefines *devDefines;
    Flash_NorXspiObject *obj;

    uint32_t pageSize;
    uint32_t numPages;
    uint32_t offsetFromPage;
    uint32_t pageNum;
    uint32_t readAddr;
    uint8_t cmd;
    uint8_t addrLen;

    if (config == NULL)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
        obj = (Flash_NorXspiObject *)(config->object);
    }

    if (status == SystemP_SUCCESS)
    {
        if (offset + len > config->attrs->flashSize)
        {
            status = SystemP_FAILURE;
        }
    }

    pageSize = config->attrs->pageSize;
    pageNum = offset / pageSize;
    offsetFromPage = offset % pageSize;
    numPages = (len + (pageSize - 1) + offsetFromPage)/pageSize;
    readAddr = offset;

    for (uint32_t i = 0; i < numPages; i++)
    {
        if (obj->xferLines == OSPI_XFER_LINES_OCTAL)
        {
            cmd = devDefines->NAND_CMD_PAGE_READ;
            addrLen = 2;
        }
        else
        {
            cmd = devDefines->NAND_CMD_PAGE_READ;
            addrLen = 3;
        }

        if (status == SystemP_SUCCESS)
        {
            OSPI_setCmdDummyCycles (obj->ospiHandle, 0x0U);
            status = Flash_nandXspiCmdWrite (config, cmd, pageNum, addrLen, NULL, 0);
        }

        if (status != SystemP_SUCCESS)
        {
            break;
        }

        if(status == SystemP_SUCCESS)
        {
            status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
        }

        if(status == SystemP_SUCCESS)
        {
            OSPI_Transaction transaction;

            OSPI_Transaction_init (&transaction);
            transaction.buf = (void *)buf + readAddr - offset;

            if (numPages == 1)
            {
                transaction.addrOffset = offsetFromPage;
                transaction.count = len;
            }
            else
            {
                if (i == 0)
                {
                    transaction.addrOffset = offsetFromPage;
                    transaction.count = pageSize - offsetFromPage;
                }
                else if (i < (numPages -1))
                {
                    transaction.addrOffset = 0;
                    transaction.count = pageSize;
                }
                else if (i == (numPages-1))
                {
                    transaction.addrOffset = 0;
                    transaction.count = (offsetFromPage + len ) % pageSize;
                }
            }

            status = OSPI_readDirect (obj->ospiHandle, &transaction);
        }

        if (readAddr % pageSize == 0)
        {
            readAddr += pageSize;
        }
        else
        {
            readAddr += (pageSize - (readAddr % pageSize));
        }

        if (status != SystemP_SUCCESS)
        {
            break;
        }

        pageNum++;

    }

    return status;
}

static int32_t Flash_nandXspiWrite (Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiObject *obj;
    Flash_NandXspiDeviceDefines *devDefines;
    Flash_Attrs *attrs = config->attrs;

    if (config != NULL)
    {
        obj = (Flash_NandXspiObject *)(config->object);
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    /* Validate address input */
    if ((offset + len) > (attrs->blockCount*attrs->pageCount*attrs->pageSize))
    {
        status = SystemP_FAILURE;
    }

    /* Check offset alignment */
    if (0 != (offset % attrs->pageSize))
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        uint32_t pageSize, chunkLen, actual;
        uint32_t byteAddr;
        uint8_t cmdWren    = devDefines->NAND_CMD_WREN;
        uint32_t pageAddr;
        uint32_t colmAddr;
        OSPI_Transaction transaction;

        pageSize = config->attrs->pageSize;

        byteAddr = offset & (pageSize - 1);

        for (actual = 0; actual < len; actual += chunkLen)
        {
            OSPI_setCmdDummyCycles (obj->ospiHandle, 0x00U);

            status = Flash_nandXspiCmdWrite (config, cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

            if (status == SystemP_SUCCESS)
            {
                status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
            }

            chunkLen = ((len - actual) < (pageSize - byteAddr) ?
                    (len - actual) : (pageSize - byteAddr));

            /* Split the page and column addresses */
            pageAddr = offset / pageSize;
            colmAddr = offset % pageSize;

            if (status == SystemP_SUCCESS)
            {
                /* Send Page Program command */
                if ((len - actual) < (pageSize))
                {
                    chunkLen = (len - actual);
                }
                else
                {
                    chunkLen = pageSize;
                }

                OSPI_Transaction_init (&transaction);
                transaction.addrOffset = colmAddr;
                transaction.buf = (void *)(buf + actual);
                transaction.count = chunkLen;
                /* Only indirect writes supported in this PHY */
                status = Flash_NandXspiWriteDirect (config, &transaction);
            }

            if (status == SystemP_SUCCESS)
            {
                status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
            }

            if (status == SystemP_SUCCESS)
            {
                OSPI_setCmdDummyCycles (obj->ospiHandle, 0x00U);

                if (OSPI_getDualOpCodeMode (obj->ospiHandle))
                {
                    status = Flash_nandXspiCmdWrite (config, devDefines->NAND_CMD_PAGE_PROG_EXECUTE, pageAddr, 2, NULL, 0);
                }
                else
                {
                    status = Flash_nandXspiCmdWrite (config, devDefines->NAND_CMD_PAGE_PROG_EXECUTE, pageAddr, 3, NULL, 0);
                }

                OSPI_setCmdDummyCycles (obj->ospiHandle, 0x08U);
            }

            if (status != SystemP_SUCCESS)
            {
                break;
            }

            if (status == SystemP_SUCCESS)
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

static int32_t Flash_nandXspiEnableDDR (Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiDeviceDefines *devDefines;
    Flash_NandXspiObject *obj;
    uint8_t txData;

    if (NULL != config)
    {
        obj = (Flash_NandXspiObject *)(config->object);
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    /* Send Write Enable Command */
    if (status == SystemP_SUCCESS)
    {
        status = Flash_nandXspiCmdWrite (config, devDefines->NAND_CMD_WREN,
                                OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }

    /* Check for busy bit of flash */
    if(status == SystemP_SUCCESS)
    {
        status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
    }

    /* send the dummy cycle value to reg addr 0x1 */
    if (status == SystemP_SUCCESS)
    {
        txData = 0xE7;

        OSPI_setCmdDummyCycles (obj->ospiHandle, 0x00u);
        status = Flash_nandXspiCmdWrite (config, devDefines->NAND_CMD_WRITE_VCR,
                                            0x00, 3, &txData, 1);
    }

    return status;
}

static int32_t Flash_nandXspiDisableWriteProtection (Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiDeviceDefines *devDefines;
    uint8_t txBuf = 0x00u;

    if(NULL != config)
    {
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        status = Flash_nandXspiCmdWrite (config, devDefines->NAND_CMD_WRITE_STATUS,
                                devDefines->NAND_R1_ADDR, 1, &txBuf, 1);
    }

    return status;
}

static int32_t Flash_nandXspiCmdWrite (Flash_Config *config, uint8_t cmd, uint32_t cmdAddr,
                                     uint8_t numAddrBytes, uint8_t *txBuf, uint32_t txLen)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiObject *obj;
    OSPI_WriteCmdParams wrParams;

    if (config !=  NULL)
    {
        obj = (Flash_NandXspiObject *)(config->object);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        OSPI_WriteCmdParams_init (&wrParams);
        wrParams.cmd          = cmd;
        wrParams.cmdAddr      = cmdAddr;
        wrParams.numAddrBytes = numAddrBytes;
        wrParams.txDataBuf    = txBuf;
        wrParams.txDataLen    = txLen;

        status = OSPI_writeCmd (obj->ospiHandle, &wrParams);
    }

    return status;
}

static int32_t Flash_nandXspiCmdRead (Flash_Config *config, uint8_t cmd, uint32_t cmdAddr,
                            uint8_t numAddrBytes, uint8_t *rxBuf, uint32_t rxLen)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiObject *obj;
    OSPI_ReadCmdParams  rdParams;

    if (config !=  NULL)
    {
        obj = (Flash_NandXspiObject *)(config->object);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        OSPI_ReadCmdParams_init (&rdParams);
        rdParams.cmd           = cmd;
        rdParams.cmdAddr       = cmdAddr;
        rdParams.numAddrBytes  = numAddrBytes;
        rdParams.rxDataBuf     = rxBuf;
        rdParams.rxDataLen     = rxLen;

        status = OSPI_readCmd (obj->ospiHandle, &rdParams);
    }

    return status;
}

static int32_t Flash_nandXspiSetDummyCycles (Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;

    Flash_NandXspiDeviceDefines *devDefines;
    Flash_NandXspiObject *obj;
    uint8_t txData;

    if (NULL != config)
    {
        obj = (Flash_NandXspiObject *)(config->object);
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    /* Send Write Enable Command */
    if (status == SystemP_SUCCESS)
    {
        status = Flash_nandXspiCmdWrite (config, devDefines->NAND_CMD_WREN,
                                OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }

    if (status == SystemP_SUCCESS)
    {
        status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
    }

    /* send the dummy cycle value to reg addr 0x1 */
    if (status == SystemP_SUCCESS)
    {
        /* Dummy Cycle Value */
        txData = 0x08;

        OSPI_setCmdDummyCycles (obj->ospiHandle, 0x00U);
        status = Flash_nandXspiCmdWrite (config, devDefines->NAND_CMD_WRITE_VCR,
                                            0x01, 3, &txData, 1);
    }

    return status;
}

static void Flash_nandXspiSetOpcodes (Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiObject *obj;
    Flash_NandXspiDeviceDefines *devDefines;
    OSPI_Handle handle;

    uint32_t readCmd = OSPI_CMD_INVALID_OPCODE;
    uint32_t progCmd = OSPI_CMD_INVALID_OPCODE;

    uint32_t readDummyCycles;
    uint32_t cmdDummyCycles;

    if (config != NULL)
    {
        obj = (Flash_NandXspiObject *)(config->object);
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        if(obj->xferLines == OSPI_XFER_LINES_OCTAL)
        {
            handle = obj->ospiHandle;
            OSPI_Config* config = (OSPI_Config *)handle;
            const OSPI_Attrs* attrs = config->attrs;
            if (attrs->dacEnable)
            {
                readDummyCycles = devDefines->NAND_OCTAL_READ_DUMMY_CYCLE;
            }
            else
            {
                readDummyCycles = devDefines->NAND_OCTAL_READ_DUMMY_CYCLE_INDAC;
            }

            if(obj->dtrEnable == TRUE)
            {
                readCmd    = devDefines->NAND_CMD_FAST_READ_DDR;
                progCmd    = devDefines->NAND_CMD_PAGE_PROG;
                cmdDummyCycles = devDefines->NAND_OCTAL_DDR_CMD_READ_DUMMY_CYCLE;
            }
            else
            {
                readCmd    = devDefines->NAND_CMD_OCTAL_IO_FAST_RD;
                progCmd    = devDefines->NAND_CMD_EXT_OCTAL_FAST_PROG;
                cmdDummyCycles = devDefines->NAND_OCTAL_SDR_CMD_READ_DUMMY_CYCLE;
            }
        }
        else
        {
            /* Set to legacy SPI mode 1-1-1 if not Octal mode */
            readCmd    = devDefines->NAND_CMD_READ;
            progCmd    = devDefines->NAND_CMD_PAGE_PROG;
            readDummyCycles = devDefines->NAND_SINGLE_READ_DUMMY_CYCLE;
            cmdDummyCycles = devDefines->NAND_SINGLE_CMD_READ_DUMMY_CYCLE;
        }

        OSPI_setCmdDummyCycles (obj->ospiHandle, cmdDummyCycles);
        OSPI_setReadDummyCycles (obj->ospiHandle, readDummyCycles);

        OSPI_setXferOpCodes (obj->ospiHandle, readCmd, progCmd);

        OSPI_setXferLines (obj->ospiHandle, obj->xferLines);

        OSPI_setDeviceSize (obj->ospiHandle, 256, 256*1024);
        OSPI_setNumAddrBytes (obj->ospiHandle, 2);

        if (obj->xferLines == OSPI_XFER_LINES_OCTAL)
        {
            OSPI_setXferLines (obj->ospiHandle, 0x3u);
            OSPI_setDualOpCodeMode (obj->ospiHandle);
            OSPI_enableDDR (obj->ospiHandle);
        }
        else
        {
            OSPI_setXferLines (obj->ospiHandle, 0x0u);
        }
    }
}

static int32_t Flash_NandXspiReadId (Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t readId[3];
    Flash_NandXspiDeviceDefines *devDefines;
    Flash_NandXspiObject *obj;

    if (NULL != config)
    {
        obj = (Flash_NandXspiObject *)(config->object);
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
    }
    else
    {
        status = SystemP_FAILURE;
    }


    if (status == SystemP_SUCCESS)
    {
        OSPI_setCmdDummyCycles (obj->ospiHandle, 0x08u);

        status = Flash_nandXspiCmdRead (config, devDefines->NAND_CMD_RDID,
                                            OSPI_CMD_INVALID_ADDR, 0, readId, 3);
    }

    if (status == SystemP_SUCCESS)
    {
        uint32_t manfID, devID;

        manfID = (uint32_t)readId[0];
        devID = ((uint32_t)readId[1] << 8) | ((uint32_t)readId[2]);
        if ((manfID == devDefines->NAND_MANF_ID) && (devID == devDefines->NAND_DEVICE_ID))
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

static int32_t Flash_nandXspiWaitReady (Flash_Config *config, uint32_t timeOut)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiDeviceDefines *devDefines;
    Flash_NandXspiObject *obj;

    uint8_t readStatus;
    uint8_t cmd, numAddrBytes, readBytes;
    uint32_t cmdAddr;

    if (config != NULL)
    {
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
        obj = (Flash_NandXspiObject *)(config->object);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        if (OSPI_getDualOpCodeMode (obj->ospiHandle))
        {
            OSPI_setCmdDummyCycles (obj->ospiHandle, 0x7);
            cmdAddr = devDefines->NAND_R3_ADDR << 8;
            numAddrBytes = 2;
            readBytes = 1;
        }
        else
        {
            OSPI_setCmdDummyCycles (obj->ospiHandle, 0x0);
            cmdAddr = devDefines->NAND_R3_ADDR;
            numAddrBytes = 1;
            readBytes = 1;
        }

        cmd = devDefines->NAND_CMD_RDSR;
        status = Flash_nandXspiCmdRead (config, cmd, cmdAddr, numAddrBytes, &readStatus, readBytes);
    }

    while ((status != SystemP_SUCCESS) || timeOut > 0)
    {
        status = Flash_nandXspiCmdRead (config, cmd, cmdAddr, numAddrBytes, &readStatus, 1);

        if((status == SystemP_SUCCESS) && ((readStatus & devDefines->NAND_SR_WIP) == 0))
        {
            break;
        }

        timeOut--;
    }

    if (status == SystemP_SUCCESS)
    {
        OSPI_setCmdDummyCycles (obj->ospiHandle, 0x8);

        if ((readStatus & devDefines->NAND_SR_WIP) == 0)
        {
            status = SystemP_SUCCESS;
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }

    return status;
}

static int32_t Flash_nandXspiErase (Flash_Config *config, uint32_t blkNum)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandXspiDeviceDefines *devDefines;
    Flash_NandXspiObject *obj;

    uint8_t cmd = OSPI_CMD_INVALID_OPCODE;
    uint32_t cmdAddr = OSPI_CMD_INVALID_ADDR;
    uint8_t cmdWren;

    if (config != NULL)
    {
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
        obj = (Flash_NandXspiObject *)(config->object);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        cmdWren = devDefines->NAND_CMD_WREN;
        cmdAddr = (blkNum * config->attrs->blockSize) / config->attrs->pageSize;
        cmd = devDefines->NAND_CMD_BLOCK_ERASE;
    }

    if (blkNum >= config->attrs->blockCount)
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
    }

    if (status == SystemP_SUCCESS)
    {
        OSPI_setCmdDummyCycles (obj->ospiHandle, 0x00U);
        status = Flash_nandXspiCmdWrite (config, cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }

    if(status == SystemP_SUCCESS)
    {
        status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
    }

    if(status == SystemP_SUCCESS)
    {
        OSPI_setCmdDummyCycles (obj->ospiHandle, 0x00U);
        if (OSPI_getDualOpCodeMode (obj->ospiHandle))
        {
            status = Flash_nandXspiCmdWrite(config, cmd, cmdAddr, 2, NULL, 0);
        }
        else
        {
            status = Flash_nandXspiCmdWrite(config, cmd, cmdAddr, 3, NULL, 0);
        }

    }

    if(status == SystemP_SUCCESS)
    {
        status = Flash_nandXspiWaitReady(config, devDefines->NAND_BULK_ERASE_TIMEOUT);
    }

    return status;
}

static int32_t Flash_NandXspiWriteDirect (Flash_Config *config, OSPI_Transaction *trans)
{
    int32_t status = SystemP_SUCCESS;

    Flash_NandXspiObject *obj;
    Flash_NandXspiDeviceDefines *devDefines;
    OSPI_Attrs *attrs;

    uint8_t *pSrc, *pDst, wrByte;
    uint32_t addrOffset, remainingSize, size, i, wrWord;

    if (config != NULL)
    {
        obj = (Flash_NandXspiObject *)(config->object);
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
        attrs = (OSPI_Attrs *)(((OSPI_Config *)obj->ospiHandle)->attrs);
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        addrOffset = trans->addrOffset;
        pSrc = trans->buf;

        pDst = (uint8_t *)(attrs->dataBaseAddr + addrOffset);
        remainingSize = (uint32_t)trans->count & 3U;
        size = (uint32_t)trans->count - remainingSize;

        /* Enable DAC Mode */
        OSPI_enableDacMode (obj->ospiHandle);

        /* Disable PHY pipeline mode */
        OSPI_disablePhyPipeline (obj->ospiHandle);

        /* Transfer the data in 32-bit size */
        for (i = 0U; i < size; i += 4U)
        {
            wrWord = CSL_REG32_RD(pSrc + i);
            CSL_REG32_WR(pDst + i, wrWord);
            status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
        }
    }

    if (status == SystemP_SUCCESS)
    {
        /* Transfer the remaining data in 8-bit size */
        for (i = 0; i < remainingSize; i++)
        {
            wrByte = CSL_REG8_RD(pSrc + size + i);
            CSL_REG8_WR (pDst + size + i, wrByte);
            status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
        }
    }

    if (status == SystemP_SUCCESS)
    {
        wrWord = 0xFFFFFFFF;
        pDst = (uint8_t*)(attrs->dataBaseAddr + config->attrs->pageSize);

        /* Transfer the remaining data in 8-bit size */
        for (i = 0; i < FLASH_PAGE_SPARE_ARRAY_SIZE_BYTES; i+=4U)
        {
            CSL_REG32_WR(pDst + i, wrWord);
            status = Flash_nandXspiWaitReady (config, devDefines->NAND_WRR_WRITE_TIMEOUT);
        }

    }

    CacheP_wbInv ((void *)(attrs->dataBaseAddr + addrOffset), trans->count, CacheP_TYPE_ALLD);

    return status;
}

static int32_t Flash_NandXspiResetMemory (Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t cmd;
    Flash_NandXspiDeviceDefines *devDefines;

    if (config != NULL)
    {
        devDefines = (Flash_NandXspiDeviceDefines *)config->devDefines;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        /* Send Reset Enable command */
        cmd = devDefines->NAND_CMD_RSTEN;
        status = Flash_nandXspiCmdWrite (config, cmd, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }

    if (status == SystemP_SUCCESS)
    {
        cmd = devDefines->NAND_CMD_RST_MEM;
        status = Flash_nandXspiCmdWrite (config, cmd, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }

    return status;
}
