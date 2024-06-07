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

#ifndef PMIC_I2C_H_
#define PMIC_I2C_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <board/pmic.h>
#include <board/pmic/pmic_lld/src/pmic_io_priv.h>
#include <drivers/i2c.h>

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
 * @brief  Reads a register from the PMIC device.
 * This function is passed as function pointer to the PMIC driver.
 * It performs a read operation on a specified register of the
 * PMIC device using the configured I2C communication. It utilizes
 * the I2C driver to execute the read transaction and updates the
 * received data in the provided buffer.
 *
 * @param pmicCorehandle  Pointer to the PMIC core handle.
 * @param instType        PMIC instance type.
 * @param regAddr         Register address to read.
 * @param pRxBuf          Pointer to the buffer to store the read data.
 * @param bufLen          Length of the buffer.
 * @return  Status of the register read operation.
 *          - #SystemP_SUCCESS if the read operation is successful.
 *          - #SystemP_FAILURE if the read operation fails.
 */
int32_t PMIC_i2cRead(Pmic_CoreHandle_t  *pmicCorehandle,
                                 uint8_t                    instType,
                                 uint16_t                   regAddr,
                                 uint8_t                   *pRxBuf,
                                 uint8_t                    bufLen);

/**
 * @brief  Writes data to a register in the PMIC device. This
 * function is passed as function pointer to the PMIC driver. This
 * function performs a write operation to a specified register
 * of the PMIC device using the configured I2C communication.
 * It utilizes the I2C driver to execute the write transaction
 * with the provided data.
 *
 * @param pmicCorehandle Pointer to the PMIC core handle.
 * @param instType       PMIC instance type.
 * @param regAddr        Register address to write.
 * @param pTxBuf         Pointer to the buffer containing the data to write.
 * @param bufLen         Length of the buffer.
 * @return  Status of the register write operation.
 *          - #SystemP_SUCCESS if the write operation is successful.
 *          - #SystemP_FAILURE if the write operation fails.
 */
int32_t PMIC_i2cWrite(Pmic_CoreHandle_t   *pmicCorehandle,
                                 uint8_t  instType,
                                 uint16_t regAddr,
                                 uint8_t  *pTxBuf,
                                 uint8_t  bufLen);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef PMIC_I2C_H_ */

/** @} */
