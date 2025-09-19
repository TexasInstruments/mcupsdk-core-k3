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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#ifndef CDCE_CTRL_H_
#define CDCE_CTRL_H_

#include <stdint.h>
#include <stdbool.h>
#include <drivers/i2c.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CDCE6214_NUM_REGISTER        (86)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct
{
    uint32_t magic;
    I2C_Handle i2cHandle;
    uint8_t devAddr;
    uint16_t regWs[CDCE6214_NUM_REGISTER];
    double inputCrystalFreqMhz;
    double currentPLLFreqMhz;
    uint16_t pll_integer;
    uint32_t pll_num;
    uint32_t pll_den;
    uint16_t dco_stepSize;
}CDCE6214_Obj, *CDCE6214_Handle;

typedef struct
{
    uint16_t reg;
    uint16_t val;
} CDCE6214_RegCfg;

typedef enum
{
    CDCE6214_REF_FREQ_INVALID=-1,
    CDCE6214_REF_FREQ_24_576MHZ=1,
}CDCE6214_RefFreq;

typedef enum
{
    CDCE6214_DCO_STEP_NEGDIR=-1,
    CDCE6214_DCO_NO_STEP=0,
    CDCE6214_DCO_STEP_POSDIR=1,
}CDCE6214_DcoStepDir;

enum {
    CDCE_REG_0 = 0,
    CDCE_REG_1,
    CDCE_REG_2,
    CDCE_REG_3,
    CDCE_REG_4,
    CDCE_REG_5,
    CDCE_REG_6,
    CDCE_REG_7,
    CDCE_REG_8,
    CDCE_REG_9,
    CDCE_REG_10,
    CDCE_REG_11,
    CDCE_REG_12,
    CDCE_REG_13,
    CDCE_REG_14,
    CDCE_REG_15,
    CDCE_REG_16,
    CDCE_REG_17,
    CDCE_REG_18,
    CDCE_REG_19,
    CDCE_REG_20,
    CDCE_REG_21,
    CDCE_REG_22,
    CDCE_REG_23,
    CDCE_REG_24,
    CDCE_REG_25,
    CDCE_REG_26,
    CDCE_REG_27,
    CDCE_REG_28,
    CDCE_REG_29,
    CDCE_REG_30,
    CDCE_REG_31,
    CDCE_REG_32,
    CDCE_REG_33,
    CDCE_REG_34,
    CDCE_REG_35,
    CDCE_REG_36,
    CDCE_REG_37,
    CDCE_REG_38,
    CDCE_REG_39,
    CDCE_REG_40,
    CDCE_REG_41,
    CDCE_REG_42,
    CDCE_REG_43,
    CDCE_REG_44,
    CDCE_REG_45,
    CDCE_REG_46,
    CDCE_REG_47,
    CDCE_REG_48,
    CDCE_REG_49,
    CDCE_REG_50,
    CDCE_REG_51,
    CDCE_REG_52,
    CDCE_REG_53,
    CDCE_REG_54,
    CDCE_REG_55,
    CDCE_REG_56,
    CDCE_REG_57,
    CDCE_REG_58,
    CDCE_REG_59,
    CDCE_REG_60,
    CDCE_REG_61,
    CDCE_REG_62,
    CDCE_REG_63,
    CDCE_REG_64,
    CDCE_REG_65,
    CDCE_REG_66,
    CDCE_REG_67,
    CDCE_REG_68,
    CDCE_REG_69,
    CDCE_REG_70,
    CDCE_REG_71,
    CDCE_REG_72,
    CDCE_REG_73,
    CDCE_REG_74,
    CDCE_REG_75,
    CDCE_REG_76,
    CDCE_REG_77,
    CDCE_REG_78,
    CDCE_REG_79,
    CDCE_REG_80,
    CDCE_REG_81,
    CDCE_REG_82,
    CDCE_REG_83,
    CDCE_REG_84,
    CDCE_REG_85,
};


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * @brief Initialize the CDCE6214 Driver
 *
 * Initializes the CDCE6214 Driver with the specified I2C handle, device address,
 * input frequency, and initial register configuration. Allocates and sets up
 * the internal workspace registers and PLL configuration.
 *
 * @param i2cHandle I2C handle to use for communication with the CDCE6214 device.
 * @param devAddr   I2C device address of the CDCE6214 device.
 * @param inputFreq Input crystal frequency selection (see @ref CDCE6214_RefFreq).
 * @param cdceConfig Pointer to an array of CDCE6214_RegCfg structures containing the initial register configuration.
 * @return Handle to the initialized CDCE6214 object, or NULL on failure.
 */
CDCE6214_Handle CDCE6214_open(I2C_Handle i2cHandle, uint8_t devAddr, CDCE6214_RefFreq inputFreq,
                              const CDCE6214_RegCfg cdceConfig[CDCE6214_NUM_REGISTER]);

/**
 * @brief Copy a configuration to the workspace registers.
 *
 * Copies the provided configuration array to the internal workspace registers of the CDCE6214 object.
 *
 * @param hCdce Handle to the CDCE6214 object.
 * @param cdceConfig Pointer to an array of CDCE6214_RegCfg structures containing the configuration to copy.
 * @return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t CDCE6214_copyConfigToWsr(CDCE6214_Handle hCdce, const CDCE6214_RegCfg cdceConfig[CDCE6214_NUM_REGISTER]);

/**
 * @brief Commit the workspace register values to the CDCE6214 device.
 *
 * Writes the current workspace register values to the CDCE6214 device over I2C.
 *
 * @param hCdce Handle to the CDCE6214 object.
 * @return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t CDCE6214_commitWsrToCdce(CDCE6214_Handle hCdce);

/**
 * @brief Get the PLL lock status from the CDCE6214 device.
 *
 * Reads the PLL lock status register from the CDCE6214 device to determine if the PLL is locked.
 *
 * @param hCdce Handle to the CDCE6214 object.
 * @return 1 if PLL is locked, 0 if not locked, SystemP_FAILURE on error.
 */
int32_t CDCE6214_getPllLockStatus(CDCE6214_Handle hCdce);

/**
 * @brief Set the PLL configuration in the workspace registers.
 *
 * Updates the workspace registers with the current PLL integer, numerator, and denominator values.
 *
 * @param hCdce Handle to the CDCE6214 object.
 * @return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t CDCE6214_setPllConfigWsr(CDCE6214_Handle hCdce);

/**
 * @brief Get the PLL configuration from the workspace registers.
 *
 * Reads the PLL integer, numerator, and denominator values from the workspace registers.
 *
 * @param hCdce Handle to the CDCE6214 object.
 * @return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t CDCE6214_getPllConfigWsr(CDCE6214_Handle hCdce);

/**
 * @brief Set the DCO (Digitally Controlled Oscillator) step size and direction.
 *
 * Adjusts the PLL numerator by the specified step size and direction for fine frequency tuning.
 *
 * @param hCdce    Handle to the CDCE6214 object.
 * @param stepSize Step size for DCO adjustment. If 0, the previous step size is used.
 * @param direction Direction of adjustment: CDCE6214_DCO_STEP_POSDIR to increase, CDCE6214_DCO_STEP_NEGDIR to decrease.
 * @return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t CDCE6214_setDco(CDCE6214_Handle hCdce, uint16_t stepSize, CDCE6214_DcoStepDir direction);

/**
 * @brief Fine tune the output frequency by a relative PPM value.
 *
 * Adjusts the PLL configuration to fine tune the output frequency by the specified relative PPM value.
 *
 * @param hCdce  Handle to the CDCE6214 object.
 * @param relppm Relative frequency adjustment in parts per million (PPM).
 * @return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t CDCE6214_fineTuneFrequency(CDCE6214_Handle hCdce, double relppm);

/**
 * @brief Deinitialize the CDCE6214 controller.
 *
 * Releases any resources and performs necessary cleanup for the specified CDCE6214 handle.
 *
 * @param hCdce Handle to the CDCE6214 to be deinitialized.
 * @return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t CDCE6214_close(CDCE6214_Handle hCdce);

#endif /* CDCE_CTRL_H_*/