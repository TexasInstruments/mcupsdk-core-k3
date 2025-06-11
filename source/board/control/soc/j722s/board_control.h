/*
 *  Copyright (C) 2023-2026 Texas Instruments Incorporated
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
 *  \defgroup BOARD_CONTROL_MODULE APIs for board control operation
 *  \ingroup BOARD_MODULE
 *
 *  This module contains APIs to control several board specific devices
 *  on the board
 *
 *  @{
 */

#ifndef BOARD_CONTROL_H_
#define BOARD_CONTROL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/i2c.h>
#include <board/ioexp/ioexp_tca6424.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief To send the MSB of a register offset address first
 */
#define BOARD_I2C_REG_ADDR_MSB_FIRST        (0x0U)

/**
 *  \brief Command to configure the HDMI transmitter on the board
 */
#define BOARD_CTRL_CMD_CFG_HDMI             (0)

/**
 *  \brief Command to enable the DSI to eDP bridge
 */
#define BOARD_CTRL_CMD_CFG_DSI2DP_BRIDGE    (1U)

/**
 *  \brief HDMI I2C instance
 */
#define BOARD_CTRL_HDMI_I2C_INSTANCE        (1U)

/**
 *  \brief HDMI I2C slave address
 */
#define BOARD_CTRL_HDMI_I2C_ADDR            (0x3BU)

/**
 *  \brief Macro to choose the HDMI resolution 1080p
 */
#define BOARD_CTRL_HDMI_RES_1080P           (0)

/**
 *  \brief Macro to choose the HDMI resolution 720p
 */
#define BOARD_CTRL_HDMI_RES_720P            (1U)

/**
 *  \brief Macro to choose the DSI2DP Bridge resolution 720p
 */
#define BOARD_CTRL_DSI_BRIDGE_720P          (0U)

/**
 *  \brief Macro to choose the DSI2DP Bridge resolution 1080p
 */
#define BOARD_CTRL_DSI_BRIDGE_1080P         (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Parameters passed during EEPROM_open()
 */
typedef struct BOARD_HdmiCfg_s
{
    uint32_t    resolution;
    /**< HDMI panel resolution */
    I2C_Handle      i2cHandle;
    /**< HDMI I2C instance handle */
    uint32_t    i2cInstance;
    /**< HDMI I2C instance */
} BOARD_HdmiCfg_t;

typedef struct
{
    uint32_t    resolution;
    /**< HDMI panel resolution */
    I2C_Handle      i2cHandle;
    /**< HDMI I2C instance handle */
    uint32_t    i2cInstance;
    /**< HDMI I2C instance */
} BOARD_DSI2DPBridgeCfg_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Board control function
 *
 * \param   cmd  [IN]  Board control command
 * \param   arg  [IN]  Control command argument.
 *                     Changes based on the command
 *
 * \return   0 if the given operation detected else -1.
 *
 */
int32_t Board_control(uint32_t cmd, void *arg);

void Board_fpdUb960GetI2CAddr(uint8_t *i2cAddr,
                              uint32_t csiInst);

void Board_fpdUb9702GetI2CAddr(uint8_t *i2cAddr,
                               uint32_t csiInst);

int32_t Board_i2c8BitRegWrSingle(void *handle,
                                 uint32_t slaveAddr,
                                 uint8_t *regData,
                                 uint32_t i2cTimeout);

int32_t Board_i2c8BitRegRdSingle(void *handle,
                                 uint32_t slaveAddr,
                                 uint8_t *regData,
                                 uint32_t i2cTimeout);

int32_t Board_i2c8BitRegWr(void *handle,
                           uint32_t slaveAddr,
                           uint8_t regAddr,
                           uint8_t *regData,
                           uint8_t numOfBytes,
                           uint32_t i2cTimeout);

int32_t Board_i2c8BitRegRd(void *handle,
                           uint32_t slaveAddr,
                           uint8_t regAddr,
                           uint8_t *regData,
                           uint8_t numOfBytes,
                           uint32_t i2cTimeout);

int32_t Board_i2c16BitRegWr(void *handle,
                            uint32_t slaveAddr,
                            uint16_t regAddr,
                            uint8_t *regData,
                            uint8_t numOfBytes,
                            uint8_t byteOrdSel,
                            uint32_t i2cTimeout);

int32_t Board_i2c16BitRegRd(void   *handle,
                            uint32_t slaveAddr,
                            uint16_t regAddr,
                            uint8_t *regData,
                            uint8_t numOfBytes,
                            uint8_t byteOrdSel,
                            uint32_t i2cTimeout);

int32_t Board_enableCSII2c(uint32_t i2cInstance);

void Board_DSIBridgeErrorRegRead(I2C_Handle i2cHandle);

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

#endif /* #ifndef EEPROM_H_ */

/** @} */
