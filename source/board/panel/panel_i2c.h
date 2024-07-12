/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

#ifndef PANEL_I2C_H_
#define PANEL_I2C_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief APIs for Panel interface read write using I2C peripherial.
 * @{
 */

/**
 *  \brief  Writes registers from the Panel device using
 *   I2C interface. It takes slave address and I2C instance as input
 *   and writes the based in I2C instance selected.
 *
 * \param instanceIndex     [in] I2C instance.
 * \param i2cAddr           [in] I2C slave address.
 * \param regAddr           [in] Pointer to set of registers.
 * \param regVal            [in] Pointer to set of register values.
 * \param numRegs           [in] Number of registers.
 *
 * \return  Status of the write operation.
 *          - #SystemP_SUCCESS if the write operation is successful.
 *          - #SystemP_FAILURE if the write operation fails.
 */
int32_t Panel_i2cBridgeWrite(uint32_t instanceIndex, uint32_t i2cAddr,
                             const uint8_t *regAddr, const uint8_t* regVal,
                             uint32_t numRegs);

/**
 *  \brief  Reads registers from the Panel device using
 *   I2C interface. It takes slave address and I2C instance as input
 *   and reads the based in I2C instance selected.
 *
 * \param instanceIndex     [in] I2C instance.
 * \param i2cAddr           [in] I2C slave address.
 * \param regAddr           [in] Pointer to set of registers.
 * \param regVal            [in] Pointer to set of register values.
 * \param numRegs           [in] Number of registers.
 *
 * \return  Status of the read operation.
 *          - #SystemP_SUCCESS if the read operation is successful.
 *          - #SystemP_FAILURE if the read operation fails.
 */
int32_t Panel_i2cBridgeRead(uint32_t instanceIndex, uint32_t i2cAddr,
                            const uint8_t *regAddr, const uint8_t *regVal,
                            uint32_t numRegs);
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef PANEL_I2C_H_ */
