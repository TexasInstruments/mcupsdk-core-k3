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
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <board/flash.h>
#include <drivers/hw_include/cslr.h>
#include "flash_nand_gpmc.h"

static int32_t Flash_nandGpmcOpen (Flash_Config *config, Flash_Params *params);
static void Flash_nandGpmcClose (Flash_Config *config);
static int32_t Flash_nandGpmcRead (Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len);
//static int32_t Flash_nandGpmcWrite (Flash_Config *config, uint32_t offset, uint8_t *buf, uint32_t len);
//static int32_t Flash_nandGpmcErase (Flash_Config *config, uint32_t blkNum);


static int32_t Flash_nandGpmcReadPage(Flash_Config *config, uint32_t blockNum,
                                uint32_t    pageNum,
                                uint8_t    *buf);
static int32_t Flash_nandGpmcResetMemory(Flash_Config *config);
static int32_t Flash_nandGpmcReadId (Flash_Config *config);
static int32_t Flash_nandGpmcCheckBadBlock(Flash_Config *config, uint32_t blockNum);
static int32_t Flash_gpmcConfigureEccBCH(Flash_Config *config);
//static int32_t Flash_gpmcDeviceStatus(Flash_Config *config);
static int32_t Flash_gpmcBchEccCheckAndCorrect(Flash_Config *config,
                                                  uint8_t    *pEccRead,
                                                  uint8_t    *pData);
static int32_t Flash_gpmcEccCheckAndCorrect(Flash_Config *config,
                                               uint8_t    *pEccRead,
                                               uint8_t    *pData);
//static void Flash_gpmcEccCalculate(Flash_Config *config, uint8_t *pEccData);




Flash_Fxns gFlashNandGpmcFxns = {
    .openFxn = Flash_nandGpmcOpen,
    .closeFxn = Flash_nandGpmcClose,
    .readFxn = Flash_nandGpmcRead,
    .writeFxn = NULL,
    .eraseFxn = NULL,
};


static int32_t Flash_nandGpmcResetMemory(Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandGpmcObject *object = NULL;
    GPMC_nandCmdParams params;

    if (config != NULL)
    {
        object = (Flash_NandGpmcObject *)config->object;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        GPMC_writeNandCommandParamsInit(&params);
        params.cmdCycle1 = 0xFF;
        params.waitTimeout = NAND_DEVICE_RESET_TIMEOUT;

        status += GPMC_writeNandCommand(object->gpmcHandle, &params);
    }

    return status;

}
static int32_t Flash_nandGpmcReadId (Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    Flash_DevConfig *devConfig = NULL;
    Flash_NandGpmcObject *object = NULL;
    GPMC_nandCmdParams params;

    if (config != NULL)
    {
        object = (Flash_NandGpmcObject *)(config->object);
        devConfig = (Flash_DevConfig *)config->devConfig;
        uint8_t readId[devConfig->idCfg.numBytes];

        GPMC_writeNandCommandParamsInit(&params);
        params.cmdCycle1 = devConfig->idCfg.cmd;
        params.numColAddrCycles  = 1;
        params.colAddress = 0;
        params.waitTimeout = NAND_DEVICE_RESET_TIMEOUT;
        params.checkReadypin = FALSE;

        status += GPMC_writeNandCommand(object->gpmcHandle, &params);

        if (status == SystemP_SUCCESS)
        {
            GPMC_Transaction trans;
            GPMC_transactionInit(&trans);
            trans.Buf = readId;
            trans.count = devConfig->idCfg.numBytes;
            trans.transType = GPMC_TRANSACTION_TYPE_READ;
            if(GPMC_nandReadData(object->gpmcHandle, &trans) == SystemP_SUCCESS)
            {
                uint32_t manfID = 0, devID = 0;
                manfID = (uint32_t)readId[0];
                devID = ((uint32_t)readId[1] << 8) | ((uint32_t)readId[2]);
                if(!(manfID == config->attrs->manufacturerId && devID == config->attrs->deviceId))
                {
                    status = SystemP_FAILURE;
                }
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}


static int32_t Flash_nandGpmcCheckBadBlock(Flash_Config *config, uint32_t blockNum)
{
    int32_t status = SystemP_SUCCESS;

    // uint8_t     badBlkMark[2];
    // uint32_t    columnAddr;
    // uint32_t    pageNum = 0U;

    // columnAddr = NAND_PAGE_SIZE + NAND_BAD_BLK_OFFSET;

    // /* Adjust column address for 16 bit address. */
    // if (NAND_BUSWIDTH_16BITS == Flash_gpmcInfo.busWidth)
    // {
    //     columnAddr /= 2;
    // }

    // /* Read the spare area of 1st, 2nd and last page of the block. */
    // for(pageNum = 0; pageNum < 3; pageNum++)
    // {
    //     if (2U == pageNum)
    //     {
    //         pageNum = (NAND_NUM_PAGES_PER_BLOCK - 1U);
    //     }

    //     if (NAND_TIMEOUT == Flash_gpmcSendPageReadCmd(handle, blockNum,
    //                                                  pageNum, columnAddr))
    //     {
    //         return NAND_TIMEOUT;
    //     }

    //     /* Read the ECC Data from the spare area */
    //     Flash_gpmcReadData(handle, badBlkMark, 2);

    //     /* Check for Bad Block Marker */
    //     if (badBlkMark[0] != NAND_BLK_GOOD_MARK)
    //     {
    //         return NAND_BLOCK_BAD;
    //     }
    //     if ((NAND_BUSWIDTH_16BITS == Flash_gpmcInfo.busWidth) &&
    //         (badBlkMark[1] != NAND_BLK_GOOD_MARK))
    //     {
    //         return NAND_BLOCK_BAD;
    //     }
    // }

    return status;
}

// static void Flash_gpmcGetBBlist(GPMC_Handle handle, uint8_t *bbList)
// {
//     NAND_STATUS status;
//     uint32_t    count;

//     for (count = 0; count < NAND_NUM_BLOCKS; count++)
//     {
// 		status = Flash_gpmcCheckBadBlock(handle, count);
// 		if (status == NAND_BLOCK_BAD)
//         {
//             bbList[count] = NAND_BAD_BLOCK;
//         }
//         else
//         {
//             bbList[count] = NAND_GOOD_BLOCK;
//         }
//     }
// }

static int32_t Flash_gpmcConfigureEccBCH(Flash_Config *config)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t lengthProtected = NAND_ECC_BCH_8BIT_NIBBLECNT;
    uint32_t lengthUnused = NAND_ECC_BCH_8BIT_UNUSED_NIBBLECNT; // (26+6=32, 32/2=16 bytes, 16/4 = 4words)

    if(config != NULL)
    {
        Flash_NandGpmcObject *object = (Flash_NandGpmcObject *)config->object;

        status +=GPMC_nandBCHEccConfig(object->gpmcHandle);

        if(status == SystemP_SUCCESS)
        {
            status += GPMC_ECCSizeValSet(object->gpmcHandle, GPMC_ECC_SIZE_0, lengthProtected);
            status += GPMC_ECCSizeValSet(object->gpmcHandle, GPMC_ECC_SIZE_1, lengthUnused);
        }

        if(status == SystemP_SUCCESS)
        {
            status += GPMC_BCHECCconfigureELM(object->gpmcHandle);
        }

        if(status == SystemP_SUCCESS)
        {
            status += GPMC_ECCengineEnable(object->gpmcHandle);
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t Flash_nandGpmcOpen(Flash_Config *config, Flash_Params *params)
{

    int32_t status = SystemP_SUCCESS;
    Flash_NandGpmcObject *object = (Flash_NandGpmcObject *)config->object;
    Flash_Attrs *attrs = config->attrs;

    object->gpmcHandle = GPMC_getHandle(attrs->driverInstance);

    if(object->gpmcHandle == NULL)
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        status +=GPMC_SetDeviceType(object->gpmcHandle, object->attrs.deviceType);

        if(status == SystemP_SUCCESS)
        {
            status += GPMC_SetDeviceSize(object->gpmcHandle, object->attrs.busWidth);
        }

        if(status == SystemP_SUCCESS)
        {
            status += GPMC_configureTimingParameters(object->gpmcHandle);
        }

        if(status ==  SystemP_SUCCESS )
        {
            object->attrs.eccOffset = attrs->pageSize + NAND_ECC_BCH_8BIT_OOB_OFFSET;
            object->attrs.eccByteCount = NAND_ECC_BCH_8BIT_BYTECNT;

            status += Flash_gpmcConfigureEccBCH(config);
        }
        else
        {
            /* Only BCH 8 bit supported for now.*/
            status = SystemP_FAILURE;
        }

        if(status == SystemP_SUCCESS)
        {
            if(Flash_nandGpmcResetMemory(config) == SystemP_SUCCESS)
            {
                status += Flash_nandGpmcReadId(config);
            }
        }

    }

    return status;
}

static void Flash_nandGpmcClose(Flash_Config *config)
{
    Flash_NandGpmcObject *object = ( Flash_NandGpmcObject *)config->object;

    /* Reset the flash such that other modules can initialise
        the flash config registers later */

    (void)Flash_nandGpmcResetMemory(config);

    object->gpmcHandle = NULL;
}

// static int32_t Flash_gpmcDeviceStatus(Flash_Config *config)
// {
//     int32_t status = SystemP_SUCCESS;
//     // NAND_STATUS      status = NAND_PASS;
//     // uint8_t          nandDevStatus;

//     // Flash_gpmcSetCmd(handle, NAND_CMD_READ_STATUS);

//     // Flash_delay(10U);

//     // Flash_gpmcReadData(handle, &nandDevStatus, 1U);

//     // if(nandDevStatus & NAND_READ_STATUS_FAIL_MASK)
//     // {
//     //     status = NAND_FAIL;
//     // }

//     // if(!(nandDevStatus & NAND_READ_STATUS_DEVRDY_MASK))
//     // {
//     //     status = NAND_DEV_BUSY;
//     // }

//     // if(!(nandDevStatus & NAND_READ_STATUS_WRPROT_MASK))
//     // {
//     //     status = NAND_DEV_PROTECTED;
//     // }

//     return status;
// }


// static void Flash_gpmcBchEccCalculate(GPMC_Handle handle,
//                                      uint8_t    *pEccData)
// {
//     uint32_t eccRes;


//     if (NAND_ECC_ALGO_BCH_8BIT == Flash_gpmcInfo.eccAlgo)
//     {
//         eccRes = Flash_gpmcGetEccBchResult(handle, 3);
//         pEccData[0] = (eccRes & 0xFF);
//         eccRes = Flash_gpmcGetEccBchResult(handle, 2);
//         pEccData[1] = ((eccRes >> 24) & 0xFF);
//         pEccData[2] = ((eccRes >> 16) & 0xFF);
//         pEccData[3] = ((eccRes >> 8) & 0xFF);
//         pEccData[4] = (eccRes & 0xFF);
//         eccRes = Flash_gpmcGetEccBchResult(handle, 1);
//         pEccData[5] = ((eccRes >> 24) & 0xFF);
//         pEccData[6] = ((eccRes >> 16) & 0xFF);
//         pEccData[7] = ((eccRes >> 8) & 0xFF);
//         pEccData[8] = (eccRes & 0xFF);
//         eccRes = Flash_gpmcGetEccBchResult(handle, 0);
//         pEccData[9] = ((eccRes >> 24) & 0xFF);
//         pEccData[10] = ((eccRes >> 16) & 0xFF);
//         pEccData[11] = ((eccRes >> 8) & 0xFF);
//         pEccData[12] = (eccRes & 0xFF);

//     }
//     else
//     {
//        /* Not Supported */
//     }
// }


static int32_t Flash_gpmcBchEccCheckAndCorrect(Flash_Config *config,
                                                  uint8_t    *pEccRead,
                                                  uint8_t    *pData)
{
    int32_t status  = SystemP_SUCCESS;
    uint32_t bchData[NAND_MAX_ECC_WORDS_PER_TRANFS] ={0};
    uint32_t errCount = 0;
    uint32_t errLoc[NAND_ERROR_BIT_PER_SECTOR_MAX] = {0};
    Flash_NandGpmcObject *object = NULL;
    uint32_t lastEccBitNum = (NAND_ECC_BCH_8BIT_NIBBLECNT * 4U) - 1U; // BCH8 value is 104 bits wide - from 0 to 103
    uint32_t errBytePos;
    uint8_t errBitMask;
    uint8_t eccCheckflag = FALSE;


    if(config != NULL)
    {
        object = (Flash_NandGpmcObject *)config->object;

        /* Check whether the sector is an erased sector*/
        for(int count = 0; count < (object->attrs.eccByteCount - 1 ) && !eccCheckflag; count++)
        {
            if(*(pEccRead + count) != 0xFF)
            {
                eccCheckflag = TRUE;
            }
        }

        if(!eccCheckflag)
        {
            return SystemP_SUCCESS;
        }

        status += GPMC_BCHECCcheckError(object->gpmcHandle, bchData, &errCount, errLoc);

        if(status == SystemP_SUCCESS)
        {
            for(uint32_t count =0; count< errCount; count++)
            {
                //
                // We only care about errors in the data area
                //
                if (errLoc[count] > lastEccBitNum)
                {
                    //
                    // Calulate bit num that has error from
                    // start of BCH data block
                    //
                    errLoc[count] -= (lastEccBitNum + 1U);

                    //
                    // Locate the faulty byte and the faulty bit in the byte
                    // Then flip it
                    //
                    errBytePos = NAND_SECTOR_SIZE_BYTES - (errLoc[count] / 8) -1;
                    errBitMask = 0x01U << (errLoc[count] % 8U);

                    pData[errBytePos] ^= errBitMask;
                }

            }
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }


    return status;

}

// static void Flash_gpmcEccCalculate(Flash_Config *config,
//                                   uint8_t *pEccData)
// {
//     // if(Flash_gpmcInfo.eccAlgo == NAND_ECC_ALGO_HAMMING_1BIT)
//     // {
//     //     Flash_gpmcHammingCodeEccCalculate(handle, 1, pEccData);
//     // }
//     // else if((Flash_gpmcInfo.eccAlgo == NAND_ECC_ALGO_BCH_4BIT) ||
//     //         (Flash_gpmcInfo.eccAlgo == NAND_ECC_ALGO_BCH_8BIT))
//     // {
//     //     Flash_gpmcBchEccCalculate(handle, pEccData);
//     // }
// }

static int32_t Flash_gpmcEccCheckAndCorrect(Flash_Config *config,
                                               uint8_t    *pEccRead,
                                               uint8_t    *pData)
{
    int32_t status = SystemP_SUCCESS;
    Flash_NandGpmcObject *object = NULL;

    if(config != NULL)
    {
        object = (Flash_NandGpmcObject *)(config->object);

        if(object->attrs.eccAlgo == GPMC_NAND_ECC_ALGO_BCH_8BIT)
        {
            status += Flash_gpmcBchEccCheckAndCorrect(config, pEccRead, pData);
        }
        else
        {
            /*not supported*/
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t Flash_nandGpmcReadPage(Flash_Config *config, uint32_t blockNum,
                                uint32_t    pageNum,
                                uint8_t    *buf)
{
    int32_t status = SystemP_SUCCESS;
    Flash_DevConfig *devConfig = NULL;
    Flash_NandGpmcObject *object = NULL;
    GPMC_Transaction  trans;
    GPMC_nandCmdParams params;
    uint8_t           eccData[256] = {0};
    uint32_t          xferCount;
    uint8_t          *pEccData = eccData;

    if(config != NULL)
    {
        object = (Flash_NandGpmcObject *)(config->object);
        devConfig = (Flash_DevConfig *)config->devConfig;

        status += GPMC_ECCengineEnable(object->gpmcHandle);

        if(status == SystemP_SUCCESS)
        {
            GPMC_ECCResultRegisterClear(object->gpmcHandle);

            GPMC_writeNandCommandParamsInit(&params);
            params.cmdCycle1 = devConfig->cmdPageLoadCyc1;
            params.cmdCycle2 = devConfig->cmdPageLoadCyc2;
            params.numColAddrCycles  = devConfig->pageLoadColAddrCyc;
            params.numRowAddrCycles = devConfig->pageLoadRowAddrCyc;
            params.colAddress = 0;
            params.rowAddress = (blockNum * (config->attrs->blockSize / config->attrs->pageSize)) + pageNum;
            params.waitTimeout = NAND_DEVICE_BUSY_TIMEOUT;

            status += GPMC_writeNandCommand(object->gpmcHandle, &params);
        }

        if(status == SystemP_SUCCESS)
        {
            for(xferCount = 0; xferCount < (config->attrs->pageSize/
                NAND_SECTOR_SIZE_BYTES); xferCount++)
            {

                GPMC_transactionInit(&trans);
                trans.Buf = buf;
                trans.count = NAND_SECTOR_SIZE_BYTES;
                trans.transType = GPMC_TRANSACTION_TYPE_READ;

                status += GPMC_nandReadData(object->gpmcHandle, &trans);

                if(status == SystemP_SUCCESS && object->attrs.eccAlgo != GPMC_NAND_ECC_ALGO_NONE)
                {

                    GPMC_writeNandCommandParamsInit(&params);
                    params.cmdCycle1 = devConfig->cmdPageLoadCyc1;
                    params.cmdCycle2 = devConfig->cmdPageLoadCyc2;
                    params.numColAddrCycles  = devConfig->pageLoadColAddrCyc;
                    params.numRowAddrCycles = devConfig->pageLoadRowAddrCyc;
                    params.colAddress = object->attrs.eccOffset + (xferCount * object->attrs.eccByteCount);
                    params.rowAddress = (blockNum * (config->attrs->blockSize / config->attrs->pageSize)) + pageNum;
                    params.waitTimeout = NAND_DEVICE_BUSY_TIMEOUT;

                    status += GPMC_writeNandCommand(object->gpmcHandle, &params);

                    if(status == SystemP_SUCCESS)
                    {
                        /* Read ECC data from the Spare area. */

                        GPMC_transactionInit(&trans);
                        trans.Buf = pEccData;
                        trans.count = object->attrs.eccByteCount - 1;
                        trans.transType = GPMC_TRANSACTION_TYPE_READ;
                        status += GPMC_nandReadData(object->gpmcHandle, &trans);

                        status = Flash_gpmcEccCheckAndCorrect(config, pEccData, buf);

                        if(status != SystemP_SUCCESS)
                        {
                                break;
                        }
                    }

                    if(status == SystemP_SUCCESS)
                    {

                        GPMC_ECCResultRegisterClear(object->gpmcHandle);

                        GPMC_writeNandCommandParamsInit(&params);
                        params.cmdCycle1 = devConfig->cmdPageLoadCyc1;
                        params.cmdCycle2 = devConfig->cmdPageLoadCyc2;
                        params.numColAddrCycles  = devConfig->pageLoadColAddrCyc;
                        params.numRowAddrCycles = devConfig->pageLoadRowAddrCyc;
                        params.colAddress = ((xferCount + 1) * (NAND_SECTOR_SIZE_BYTES));
                        params.rowAddress = (blockNum * (config->attrs->blockSize / config->attrs->pageSize)) + pageNum;
                        params.waitTimeout = NAND_DEVICE_BUSY_TIMEOUT;

                        status += GPMC_writeNandCommand(object->gpmcHandle, &params);

                        if(status != SystemP_SUCCESS)
                        {
                            break;
                        }

                    }
                        pEccData += object->attrs.eccByteCount;
                }

                buf += NAND_SECTOR_SIZE_BYTES;
            }
        }

    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t Flash_nandGpmcRead(Flash_Config *config, uint32_t offset, uint8_t *buf ,uint32_t len)
{
    int32_t status = SystemP_SUCCESS;

    if(config != NULL)
    {
        Flash_NandGpmcObject *object = (Flash_NandGpmcObject *)config->object;
        uint32_t bytesLeft = 0;
        uint32_t numBytesCopy = 0;
        uint32_t totalLength = len;
        uint8_t  *destAddr = buf;

        uint32_t blockNum = (offset / config->attrs->blockSize);
        uint32_t pageNum = (offset - (blockNum * config->attrs->blockSize)) / config->attrs->pageSize;
        uint32_t pageOffset = offset % config->attrs->pageSize;

        if(pageOffset > 0)
        {
            status += Flash_nandGpmcReadPage(config,blockNum,pageNum,object->memScratch);

            if(status == SystemP_SUCCESS)
            {
                bytesLeft = config->attrs->pageSize - pageOffset;
                numBytesCopy = (bytesLeft >= totalLength) ? totalLength : bytesLeft;
                memcpy((void*)destAddr, (void*)(object->memScratch + pageOffset), numBytesCopy);
                destAddr += numBytesCopy;
                totalLength -=numBytesCopy;
                pageNum++;
            }
        }

        while(totalLength > 0)
        {
            if(pageNum >= config->attrs->pageCount)
            {
                blockNum++;
                pageNum = 0;
            }

            if(totalLength >= config->attrs->pageSize)
            {
                numBytesCopy = config->attrs->pageSize;
                status += Flash_nandGpmcReadPage(config,blockNum,pageNum,destAddr);

                if(status != SystemP_SUCCESS)
                {
                    break;
                }
            }
            else
            {
                numBytesCopy = totalLength;
                status += Flash_nandGpmcReadPage(config,blockNum,pageNum,object->memScratch);

                if(status == SystemP_SUCCESS)
                {
                    memcpy((void*)destAddr, (void*)object->memScratch, numBytesCopy);
                }
                else
                {
                    break;
                }
            }

            totalLength -= numBytesCopy;
            destAddr += numBytesCopy;
            pageNum++;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

// static void Flash_gpmcStartPageWriteCmd(GPMC_Handle handle,
//                                        uint32_t    blockNum,
//                                        uint32_t    pageNum,
//                                        uint32_t    columnAddr)
// {
//     uint32_t colAddr = columnAddr;
//     uint32_t pageAddr;
//     uint32_t count;

//     Flash_gpmcSetCmd(handle, NAND_CMD_PROG_PAGE);

//     /* Write 2 Bytes of column address. */
//     for (count = 0; count < NAND_NUM_BYTES_COLUMN_ADDR; count++)
//     {
//         Flash_gpmcSetAddr(handle, colAddr & 0xFF);
//         colAddr = colAddr >> 0x8;
//     }

//     /* Write the 4 bytes of row address. */
//     pageAddr = blockNum * NAND_NUM_PAGES_PER_BLOCK + pageNum;
//     for (count = 0; count < NAND_NUM_BYTES_ROW_ADDR; count++)
//     {
//         Flash_gpmcSetAddr(handle, pageAddr & 0xFF);
//         pageAddr = pageAddr >> 0x8;
//     }
// }

// static NAND_STATUS Flash_gpmcEndPageWriteCmd(GPMC_Handle handle)
// {
//     NAND_STATUS status = NAND_PASS;

//     Flash_gpmcSetCmd(handle, NAND_CMD_PROG_PAGE_CYC2);

//     status = Flash_gpmcWaitPinStatus(handle, NAND_TIMEOUT_VAL);
//     if(NAND_TIMEOUT == NAND_PASS)
//     {
//         status = Flash_gpmcDeviceStatus(handle);
//     }

//     return status;
// }

// static int32_t Flash_nandGpmcWritePage(Flash_Config *config,
//                                       uint32_t    blockNum,
//                                       uint32_t    pageNum,
//                                       uint8_t    *pTxData)
// {
//     int32_t status = SystemP_SUCCESS;

//     // NAND_STATUS      status = NAND_PASS;
//     // GPMC_Transaction transaction;
//     // uint32_t         columnAddr = 0U;
//     // uint8_t          eccData[256] = {0, };
//     // uint8_t         *pEccData = eccData;
//     // uint32_t         xferCount, count;

//     //     GPMC_v1_HwAttrs const *hwAttrs = NULL;

//     //     hwAttrs = (GPMC_v1_HwAttrs const *)handle->hwAttrs;

//     // Flash_gpmcEccEnable(handle);

//     // Flash_gpmcStartPageWriteCmd(handle, blockNum, pageNum, columnAddr);

//     // // if(NAND_ECC_ALGO_NONE != Flash_gpmcInfo.eccAlgo)
//     // // {
//     // //     Flash_gpmcEccWriteSizeSet(handle);
//     // //     Flash_gpmcEccDisable(handle);
//     // // }
//     // for(xferCount = 0U; xferCount < (NAND_PAGE_SIZE / NAND_BYTES_PER_XFER);
//     //     xferCount++)
//     // {
//     //     // if(NAND_ECC_ALGO_NONE != Flash_gpmcInfo.eccAlgo)
//     //     // {
//     //     //     Flash_gpmcEccEnable(handle);
//     //     // }

//     //     GPMCECCResultRegClear(hwAttrs->gpmcBaseAddr);
//     //     GPMCECCResultRegSelect(hwAttrs->gpmcBaseAddr,GPMC_ECCPOINTER_RESULT_1);

//     //     transaction.txBuf = (void *)pTxData;
//     //     transaction.rxBuf = NULL;
//     //     transaction.count = NAND_BYTES_PER_XFER;

//     //     if (false == GPMC_transfer(handle, &transaction))
//     //     {
//     //         return NAND_FAIL;
//     //     }

//     //     if(NAND_ECC_ALGO_NONE != Flash_gpmcInfo.eccAlgo)
//     //     {
//     //         //Flash_gpmcEccDisable(handle);
//     //         Flash_gpmcEccCalculate(handle, pEccData);
//     //         pEccData += Flash_gpmcInfo.eccByteCount;
//     //     }
//     //     pTxData += NAND_BYTES_PER_XFER;
//     // }
//     // if(NAND_PASS == status)
//     // {
//     //     if(NAND_ECC_ALGO_NONE != Flash_gpmcInfo.eccAlgo)
//     //     {
//     //         if(status == NAND_PASS)
//     //         {
//     //             columnAddr = Flash_gpmcInfo.eccOffset;
//     //             if(Flash_gpmcInfo.busWidth == NAND_BUSWIDTH_16BITS)
//     //             {
//     //                 columnAddr = columnAddr / 2;
//     //             }
//     //             Flash_gpmcSetCmd(handle, NAND_CMD_INPUT_RANDOM);

//     //             /* Write 2 Bytes of column address. */
//     //             for (count = 0; count < NAND_NUM_BYTES_COLUMN_ADDR; count++)
//     //             {
//     //                 Flash_gpmcSetAddr(handle, columnAddr & 0xFF);
//     //                 columnAddr = columnAddr >> 8U;
//     //             }

//     //             Flash_gpmcWriteData(handle, &eccData[0],
//     //                                Flash_gpmcInfo.eccByteCount * //todo: make a chunk of 16 bytes chunck and total write but the ECC matches for linux write also, 14 bytes write.
//     //                                (NAND_PAGE_SIZE/NAND_BYTES_PER_XFER));
//     //         }
//     //     }
//     //     status = Flash_gpmcEndPageWriteCmd(handle);
//     // }

//     return status;
// }

// static int32_t Flash_nandGpmcWrite(NAND_HANDLE handle, uint32_t addr,
//                                   uint32_t len, uint8_t *buf)
// {
//     int32_t status = SystemP_SUCCESS;

//     // NAND_STATUS       status = NAND_PASS;
//     // NAND_Info        *nandGpmcInfo;
//     // uint32_t          blockNum;
//     // uint32_t          pageNum;
//     // uint32_t          numPages;
//     // uint32_t          count;
//     // uint8_t          *txData = (uint8_t *)buf;

//     // if (!handle)
//     // {
//     //     return NAND_INVALID_PARAM;
//     // }

//     // nandGpmcInfo = (NAND_Info *)handle;
//     // if (!nandGpmcInfo->hwHandle)
//     // {
//     //     return NAND_FAIL;
//     // }

//     // /* Validate address input */
//     // if ((addr + len) > NAND_SIZE)
//     // {
//     //     return NAND_INVALID_PARAM;
//     // }

//     // blockNum = addr / NAND_BLOCK_SIZE;
//     // pageNum = (addr % NAND_BLOCK_SIZE) / NAND_PAGE_SIZE;
//     // numPages = len / NAND_PAGE_SIZE;

//     // for (count = 0; count < numPages; count++)
//     // {
//     //     status = Flash_gpmcWritePage((GPMC_Handle)nandGpmcInfo->hwHandle, blockNum,
//     //                                 pageNum, txData);
//     //     if (status != NAND_PASS)
//     //     {
//     //        return status;
//     //     }
//     //     txData += NAND_PAGE_SIZE;
//     // }

//     return status;
// }

// static int32_t  Flash_gpmcMarkBlockAsBad(Flash_Config *config, uint32_t blockNum)
// {
//     int32_t status = SystemP_SUCCESS;
//     // uint32_t    pageNum = 0U;
//     // uint32_t    columnAddr = 0U;
//     // uint8_t     badBlkMark[2];

//     // columnAddr = NAND_PAGE_SIZE + NAND_BAD_BLK_OFFSET;

//     // /* Adjust column address for 16 bit address. */
//     // if (NAND_BUSWIDTH_16BITS == Flash_gpmcInfo.busWidth)
//     // {
//     //     columnAddr /= 2;
//     // }

//     // /* Read the spare area of 1st, 2nd and last page of the block */
//     // for(pageNum = 0; pageNum < 3; pageNum++)
//     // {
//     //     /* Last page number of the block */
//     //     if(pageNum == 2)
//     //     {
//     //         pageNum = NAND_NUM_PAGES_PER_BLOCK - 1U;
//     //     }

//     //     Flash_gpmcStartPageWriteCmd(handle, blockNum, pageNum, columnAddr);

//     //     badBlkMark[0] = NAND_BLK_BAD_MARK;
//     //     Flash_gpmcWriteData(handle, badBlkMark, 2);

//     //     status = Flash_gpmcEndPageWriteCmd(handle);
//     //     if(NAND_PASS != status)
//     //     {
//     //         break;
//     //     }
//     // }

//     return status;
// }

// static int32_t Flash_nandGpmcErase (Flash_Config *config, uint32_t blkNum);
// {
//     int32_t status = SystemP_SUCCESS;

//     // NAND_Info       *nandGpmcInfo;
//     // GPMC_Handle      gpmcHandle;
//     // uint32_t         firstPageAddr;
//     // uint32_t         count;
//     // NAND_STATUS      status;

//     // if (!handle)
//     // {
//     //     return NAND_INVALID_PARAM;
//     // }

//     // nandGpmcInfo = (NAND_Info *)handle;
//     // if (!nandGpmcInfo->hwHandle)
//     // {
//     //     return NAND_FAIL;
//     // }
//     // gpmcHandle = (GPMC_Handle)nandGpmcInfo->hwHandle;

//     // if (blockNum >= NAND_NUM_BLOCKS)
//     // {
//     //     return NAND_INVALID_PARAM;
//     // }

//     // // if (Flash_gpmcBBlist[blockNum] == NAND_BAD_BLOCK)
//     // // {
//     // //     return NAND_BLOCK_BAD;
//     // // }
//     //     GPMC_v1_HwAttrs const *hwAttrs = NULL;

//     //     hwAttrs = (GPMC_v1_HwAttrs const *)gpmcHandle->hwAttrs;

//     // GPMCIntStatusClear(hwAttrs->gpmcBaseAddr, GPMC_WAIT0EDGEDETECTION_STATUS);

//     // Flash_gpmcSetCmd(gpmcHandle, NAND_CMD_ERASE);

//     // /* Calculate linear page number of the first page of the block. */
//     // firstPageAddr = blockNum * NAND_NUM_PAGES_PER_BLOCK;

//     // /* Write the Row address. */
//     // for(count = 0; count < NAND_NUM_BYTES_ROW_ADDR; count++)
//     // {
//     //     Flash_gpmcSetAddr(gpmcHandle, (uint8_t)firstPageAddr);
//     //     firstPageAddr = firstPageAddr >> 8U;
//     // }

//     // Flash_gpmcSetCmd(gpmcHandle, NAND_CMD_ERASE_CYC2);

//     // status = Flash_gpmcWaitPinStatus(gpmcHandle, NAND_TIMEOUT_VAL);
//     // if(NAND_PASS == status)
//     // {
//     //     status = Flash_gpmcDeviceStatus(gpmcHandle);
//     // }

//     // // if ((status != NAND_PASS) && (status != NAND_DEV_PROTECTED))
//     // // {
// 	// // 	if (Flash_gpmcMarkBlockAsBad(gpmcHandle, blockNum) == NAND_PASS)
//     // //     {
//     // //         Flash_gpmcBBlist[blockNum] = NAND_BAD_BLOCK;
//     // //         return NAND_BLOCK_BAD;
//     // //     }
//     // // }
//     return status;
// }

