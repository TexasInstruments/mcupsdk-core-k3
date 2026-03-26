/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \file   board_utils.c
 *
 *  \brief  Implements multiple board utility functions
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include "board_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Board_DetectCfg_t gBoardDetCfg[BOARD_ID_MAX_BOARDS];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * \brief Board detect function
 *
 *  Checks if the board with given 'boardID' is connected to the
 *  base board.
 *
 *  \n Note: Board ID EEPROM should be programmed for this function
 *           to work properly.
 *  \n       I2C2 mux should be enbaled and I2C switch should be configured
 *  \n       for both the CSI ports before calling this function for proper
 *  \n       detection of Fusion2 board.
 *
 * \param   boardID     [IN]    ID of the board to be detected
 * \n                           BOARD_ID_EVM(0x0) - EVM Board
 * \n                           BOARD_ID_FUSION2(0x1) - Fusion2 Board
 * \param   i2cInstance [IN]    I2c instance of the board ID eeprom
 *
 * \return   BTRUE if the given board is detected else BFALSE.
 *
 */
bool Board_detectBoard(uint32_t boardID, uint32_t i2cInstance)
{
    Board_IdInfo_t info;
    int32_t status;
    bool bDet = BFALSE;

    memset(&info, 0, sizeof(info));

    if(BOARD_ID_FUSION2 >= boardID)
    {
        status = Board_getBoardData(&info, boardID, i2cInstance);
        if(SystemP_SUCCESS == status)
        {
            if(!(strncmp(info.boardInfo.boardName,
                         gBoardDetCfg[boardID].bName,
                         BOARD_BOARD_NAME_LEN)))
            {
                bDet = BTRUE;
            }
        }
    }

    return bDet;
}

/**
 * \brief Board ID read function
 *
 * \param   info        [IN]    Board info structure
 * \param   boardID     [IN]    ID of the board to be detected
 * \n                           BOARD_ID_EVM(0x0) - EVM Board
 * \n                           BOARD_ID_FUSION2(0x1) - Fusion2 Board
 * \param   i2cInstance [IN]    I2c instance of the board ID eeprom
 *
 * \return   SystemP_SUCCESS in case of success or appropriate error code.
 *
 */
int32_t Board_getBoardData(Board_IdInfo_t *info, uint32_t boardID, uint32_t i2cInstance)
{
    int32_t status = SystemP_SUCCESS;
    I2C_Transaction i2cTransaction;
    I2C_Handle handle = NULL;
    Board_HeaderInfo_t headerInfo;
    uint16_t offsetAddress = BOARD_EEPROM_HEADER_ADDR;
    char txBuf[2] = {0x00, 0x00};

    I2C_Transaction_init(&i2cTransaction);

    handle = I2C_getHandle(i2cInstance);
    if(handle == NULL)
    {
        status = I2C_STS_ERR;
    }

    i2cTransaction.targetAddress = gBoardDetCfg[boardID].targetAddress;
    i2cTransaction.writeBuf      = (uint8_t *)&txBuf[0];
    i2cTransaction.writeCount    = 2;

    /* Get header info */
    txBuf[0] = (char)(((uint32_t) 0xFF00 & offsetAddress)>>8);
    txBuf[1] = (char)((uint32_t) 0xFF & offsetAddress);
    i2cTransaction.readBuf   = &headerInfo;
    i2cTransaction.readCount = BOARD_EEPROM_HEADER_FIELD_SIZE;

    status = I2C_transfer(handle, &i2cTransaction);
    if (SystemP_SUCCESS != status)
    {
        status = I2C_STS_ERR;
    }

    if (status == I2C_STS_SUCCESS)
    {
        /* Checking whether the board contents are flashed or not */
        if (headerInfo.magicNumber == BOARD_EEPROM_MAGIC_NUMBER)
        {
            txBuf[0] = (char)(((uint32_t) 0xFF00 & offsetAddress) >> 8);
            txBuf[1] = (char)((uint32_t) 0xFF & offsetAddress);
            i2cTransaction.readBuf   = info;
            i2cTransaction.readCount = headerInfo.payloadSize +
                                    BOARD_EEPROM_HEADER_FIELD_SIZE;
            status = I2C_transfer(handle, &i2cTransaction);
            if (SystemP_SUCCESS != status)
            {
                status = I2C_STS_ERR;
            }
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }

    return status;
}
