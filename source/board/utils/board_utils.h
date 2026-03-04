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
 *  \defgroup BOARD_UTILS_MODULE APIs for multiple board utility functions
 *  \ingroup BOARD_MODULE
 *
 *  This module contains multiple board utility functions
 *
 *  @{
 */

#ifndef _BOARD_UTILS_H_
#define _BOARD_UTILS_H_

/*****************************************************************************
 * Include Files                                                             *
 *****************************************************************************/

#include <drivers/i2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Board detect ID for EVM 
 */
#define BOARD_ID_EVM                                    (0x0U)

/**
 *  \brief Board detect ID for Fusion2 
 */
#define BOARD_ID_FUSION2                                (0x1U)

/**
 *  \brief Maximum number of supporting board IDs
 */
#define BOARD_ID_MAX_BOARDS                             (0x2U)

/**
 *  \brief Board eeprom address
 */
#define BOARD_EVM_EEPROM_TARGET_ADDR                    (0x51U)
#define BOARD_CSI2_EEPROM_TARGET_ADDR                   (0x52U)

/**
 *  \brief EEPROM board ID information
 */
#define BOARD_EEPROM_HEADER_FIELD_SIZE                  (7U)
#define BOARD_EEPROM_MAGIC_NUMBER                       (0xEE3355AAU)

/**
 *  \brief EEPROM board header offset
 */
#define BOARD_EEPROM_HEADER_ADDR                        (0U)

/**
 *  \brief EEPROM board information length
 */
#define BOARD_BOARD_NAME_LEN                            (16U)
#define BOARD_DESIGN_REV_LEN                            (2U)
#define BOARD_PROC_NUM_LEN                              (4U)
#define BOARD_VARIANT_LEN                               (2U)
#define BOARD_PCBREV_LEN                                (2U)
#define BOARD_SCHMBOM_REV_LEN                           (2U)
#define BOARD_SWREV_LEN                                 (2U)
#define BOARD_VENDORID_LEN                              (2U)
#define BOARD_BUILD_WEEK_LEN                            (2U)
#define BOARD_BUILD_YEAR_LEN                            (2U)
#define BOARD_BOARDID_LEN                               (6U)
#define BOARD_SERIAL_NUM_LEN                            (4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief This structure contains eeprom board information
 */
typedef struct Board_BoardInfo_s
{
    uint8_t  boardInfoStructType;
    /**< Board info structure type */
    uint16_t boardInfoLength;
    /**< Board info length */
    char     boardName[BOARD_BOARD_NAME_LEN];
    /**< Board name */
    char     designRev[BOARD_DESIGN_REV_LEN];
    /**< Board design revision */
    char     procNum[BOARD_PROC_NUM_LEN];
    /**< Board proc num */
    char     variant[BOARD_VARIANT_LEN];
    /**< Board variant */
    char     pcbRev[BOARD_PCBREV_LEN];
    /**< Board PCB revision */
    char     schbomRev[BOARD_SCHMBOM_REV_LEN];
    /**< Board schbom revision */
    char     swRev[BOARD_SWREV_LEN];
    /**< Board sw revision */
    char     vendorID[BOARD_VENDORID_LEN];
    /**< Board vendor ID */
    char     buildWeek[BOARD_BUILD_WEEK_LEN];
    /**< Board build week */
    char     buildYear[BOARD_BUILD_YEAR_LEN];
    /**< Board build year */
    char     boardID[BOARD_BOARDID_LEN];
    /**< Board ID */
    char     serialNum[BOARD_SERIAL_NUM_LEN];
    /**< Board serial Number */
} __attribute__((packed)) Board_BoardInfo_t;

/**
 * \brief This structure contains eeprom header information
 */
typedef struct Board_HeaderInfo_s
{
    uint32_t magicNumber;
    /**< Board magic number */
    uint8_t  headerStructType;
    /**< Header structure type */
    uint16_t payloadSize;
    /**< payload size */
} __attribute__((packed)) Board_HeaderInfo_t;

/**
 *  @brief This structure contains board specific information
 *
 */
typedef struct Board_IdInfo_s
{
    Board_HeaderInfo_t headerInfo;
    /**< Header info of the board */
    Board_BoardInfo_t boardInfo;
    /**< Board id Info of the board */
}  __attribute__((packed)) Board_IdInfo_t;

/**
 * \brief Structure to configure the board I2C parameters
 */
typedef struct Board_DetectCfg_s
{
    uint32_t targetAddress;
    /**< Board ID EEPROM address */
    char bName[20];
    /**< Board name */
} Board_DetectCfg_t;

/* ========================================================================== */
/*                          Function Declarations                             */
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
bool Board_detectBoard(uint32_t boardID, uint32_t i2cInstance);

/**
 * \brief Board ID read function
 *
 * \param   boardID     [IN]    ID of the board to be detected
 * \n                           BOARD_ID_EVM(0x0) - EVM Board
 * \n                           BOARD_ID_FUSION2(0x1) - Fusion2 Board
 * \param   i2cInstance [IN]    I2c instance of the board ID eeprom
 *
 * \return   SystemP_SUCCESS in case of success or appropriate error code.
 *
 */
int32_t Board_getBoardData(Board_IdInfo_t *info, uint32_t boardID, uint32_t i2cInstance);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* _BOARD_UTILS_H_ */
