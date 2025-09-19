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
#include <string.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/i2c.h>
#include "cdce6214_drv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CDCE6214_MAGIC_NUMBER      (0x1234ABCDu)
#define CDCE6214_REL_PPM_LIMIT     (100)
#define CDCE6214_DCO_STEP_LIMIT    (10000)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * @brief Writes a value to a specified CDCE register.
 *
 * @param hCdce   Handle to the CDCE controller.
 * @param regAddr Register address to write to.
 * @param regVal  Value to write to the register.
 * @return SystemP_SUCCESS on success, negative value on error.
 */
static int32_t CDCE6214_writeReg(CDCE6214_Handle hCdce, uint16_t regAddr, uint16_t regVal);

/**
 * @brief Reads a value from a specified CDCE register.
 *
 * @param hCdce   Handle to the CDCE controller.
 * @param regAddr Register address to read from.
 * @param val     Pointer to store the read value.
 * @return SystemP_SUCCESS on success, negative value on error.
 */
static int32_t CDCE6214_readReg(CDCE6214_Handle hCdce, uint16_t regAddr, uint16_t* val);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

CDCE6214_Obj gCDCE6214_Object;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

CDCE6214_Handle CDCE6214_open(I2C_Handle i2cHandle, uint8_t devAddr, CDCE6214_RefFreq inputFreq, \
                                    const CDCE6214_RegCfg cdceConfig[CDCE6214_NUM_REGISTER])
{
    /* Check I2C Handle. */
    CDCE6214_Handle hCdce = NULL;

    if ((i2cHandle != NULL) && \
        (inputFreq == CDCE6214_REF_FREQ_24_576MHZ) && \
        (gCDCE6214_Object.magic != CDCE6214_MAGIC_NUMBER))
    {
        hCdce = &gCDCE6214_Object;
        hCdce->magic     = CDCE6214_MAGIC_NUMBER;
        hCdce->i2cHandle = i2cHandle;
        hCdce->devAddr   = devAddr;
        hCdce->inputCrystalFreqMhz = 24.576;

        /* Copy the Default configuration to Workspace Registers. */
        CDCE6214_copyConfigToWsr(hCdce, cdceConfig);

        /* TODO: Copy the PLL and DCO configuration from Workspace Registers. */
        CDCE6214_getPllConfigWsr(hCdce);

        hCdce->currentPLLFreqMhz = hCdce->inputCrystalFreqMhz*((double)hCdce->pll_integer+\
                                                    ((double)hCdce->pll_num/(double)hCdce->pll_den));
    }

    return hCdce;
}

static int32_t CDCE6214_readReg(CDCE6214_Handle hCdce, uint16_t regAddr, uint16_t* val)
{
    I2C_Handle i2cHandle = hCdce->i2cHandle;
    int32_t status = SystemP_SUCCESS;
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[2];
    uint8_t rxBuffer[2];

    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = (uint8_t *)txBuffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf   = (uint8_t *)rxBuffer;
    i2cTransaction.readCount = 2;
    i2cTransaction.targetAddress = hCdce->devAddr;
    txBuffer[0] = (uint8_t)((regAddr >> 8) & (uint16_t)0xFF);
    txBuffer[1] = (uint8_t)(regAddr & (uint16_t)0xFF);
    status = I2C_transfer(i2cHandle, &i2cTransaction);

    if (status == SystemP_SUCCESS)
    {
        *val = ((uint16_t)rxBuffer[0] << 8) | rxBuffer[1];
    }

    return status;
}

static int32_t CDCE6214_writeReg(CDCE6214_Handle hCdce, uint16_t regAddr, uint16_t regVal)
{
    I2C_Handle i2cHandle = hCdce->i2cHandle;
    int32_t status = SystemP_SUCCESS;
    I2C_Transaction i2cTransaction;
    uint8_t txBuffer[4];

    I2C_Transaction_init(&i2cTransaction);
    i2cTransaction.writeBuf   = (uint8_t *)txBuffer;
    i2cTransaction.writeCount = 4;
    i2cTransaction.targetAddress = hCdce->devAddr;
    txBuffer[0] = (uint8_t)((regAddr >> 8) & (uint16_t)0xFF);
    txBuffer[1] = (uint8_t)(regAddr & (uint16_t)0xFF);
    txBuffer[2] = (uint8_t)((regVal >> 8) & (uint16_t)0xFF);
    txBuffer[3] = (uint8_t)(regVal & (uint16_t)0xFF);
    status = I2C_transfer(i2cHandle, &i2cTransaction);
    return status;
}

int32_t CDCE6214_copyConfigToWsr(CDCE6214_Handle hCdce, const CDCE6214_RegCfg cdceConfig[CDCE6214_NUM_REGISTER])
{
    int32_t retval = SystemP_FAILURE;
    if (hCdce != NULL)
    {
        /* Copy the Default configuration to Workspace Registers. */
        for (int i = 0; i < CDCE6214_NUM_REGISTER; i++)
        {
            hCdce->regWs[cdceConfig[i].reg] = cdceConfig[i].val;
        }
        retval = SystemP_SUCCESS;
    }
    return retval;
}

int32_t CDCE6214_commitWsrToCdce(CDCE6214_Handle hCdce)
{
    int32_t retval = SystemP_FAILURE;
    if (hCdce != NULL)
    {
        /* Need to Commit the registers in Reverse order. */
        for (int i = CDCE_REG_85; i >= CDCE_REG_0; i--)
        {
            retval = CDCE6214_writeReg(hCdce, (uint16_t)i, hCdce->regWs[i]);
            if (retval != SystemP_SUCCESS)
            {
                retval = SystemP_FAILURE;
                break;
            }
        }
    }
    return retval;
}

int32_t CDCE6214_getPllLockStatus(CDCE6214_Handle hCdce)
{
    int32_t retval = SystemP_FAILURE;
    if (hCdce != NULL)
    {
        uint16_t regVal = 0;
        retval = CDCE6214_readReg(hCdce, CDCE_REG_7, &regVal);
        if (retval == SystemP_SUCCESS)
        {
            retval = (regVal & (uint16_t)1);
        }
    }
    return retval;
}

int32_t CDCE6214_setPllConfigWsr(CDCE6214_Handle hCdce)
{
    int32_t retval = SystemP_FAILURE;
    if (hCdce != NULL)
    {
        hCdce->regWs[30] = hCdce->pll_integer;
        hCdce->regWs[31] = (uint16_t)(hCdce->pll_num & 0xFFFFu);
        hCdce->regWs[32] = (uint16_t)((hCdce->pll_num >> 16) & 0xFFu);
        hCdce->regWs[33] = (uint16_t)(hCdce->pll_den & 0xFFFFu);
        hCdce->regWs[34] = (uint16_t)((hCdce->pll_den >> 16) & 0xFFu);
        retval = SystemP_SUCCESS;
    }
    return retval;
}

int32_t CDCE6214_getPllConfigWsr(CDCE6214_Handle hCdce)
{
    int32_t retval = SystemP_FAILURE;
    if (hCdce != NULL)
    {
        hCdce->pll_integer = hCdce->regWs[30];
        hCdce->pll_num     = hCdce->regWs[31] | ((uint32_t)hCdce->regWs[32] << 16);
        hCdce->pll_den     = hCdce->regWs[33] | ((uint32_t)hCdce->regWs[34] << 16);
        retval = SystemP_SUCCESS;
    }
    return retval;
}

int32_t CDCE6214_setDco(CDCE6214_Handle hCdce, uint16_t stepSize, CDCE6214_DcoStepDir direction)
{
    int32_t retval = SystemP_FAILURE;

    if (hCdce != NULL)
    {
        if (stepSize > 0u)
        {
            hCdce->dco_stepSize = stepSize;
            /* Update step Size. */
            retval = CDCE6214_writeReg(hCdce, CDCE_REG_43, hCdce->dco_stepSize);
        }
    }

    if (retval == SystemP_SUCCESS)
    {
        /* Check if step size is greater than numerator and
          if the direction is negative, the numerator can underflow
          and the frequency will be incorrect. */
        if ((hCdce->dco_stepSize > hCdce->pll_num) && (direction == CDCE6214_DCO_STEP_NEGDIR))
        {
            /* Not Permitted, Reconfigure PLL
               if this criteria ever comes.*/
            DebugP_log("Numerator = %u, Neg Step = %u,"\
                       " Operation Not permitted\r\n", hCdce->pll_num, hCdce->dco_stepSize);
            retval = SystemP_FAILURE;
        }
    }

    if (retval == SystemP_SUCCESS)
    {
        if (direction == CDCE6214_DCO_NO_STEP)
        {
            retval = SystemP_SUCCESS;
        }
        else if (direction == CDCE6214_DCO_STEP_POSDIR)
        {
            /* Inc by Step Size. */
            retval =  CDCE6214_writeReg(hCdce, CDCE_REG_3, 0x38);
            retval += CDCE6214_writeReg(hCdce, CDCE_REG_3, 0x18);
            if (retval == SystemP_SUCCESS)
            {
                hCdce->pll_num += hCdce->dco_stepSize;
            }
        }
        else /* CDCE6214_DCO_STEP_NEGDIR */
        {
            /* Dec by Step Size. */
            retval =  CDCE6214_writeReg(hCdce, CDCE_REG_3, 0x58);
            retval += CDCE6214_writeReg(hCdce, CDCE_REG_3, 0x18);
            if (retval == SystemP_SUCCESS)
            {
                hCdce->pll_num -= hCdce->dco_stepSize;
            }
        }
    }
    return retval;
}

int32_t CDCE6214_fineTuneFrequency(CDCE6214_Handle hCdce, double relppm)
{
    double constrainedPpm = relppm;

    /* Limit PPM per Step. */
    if (constrainedPpm > (double)CDCE6214_REL_PPM_LIMIT)
    {
        constrainedPpm = CDCE6214_REL_PPM_LIMIT;
    }
    if (constrainedPpm < -(double)CDCE6214_REL_PPM_LIMIT)
    {
        constrainedPpm = -CDCE6214_REL_PPM_LIMIT;
    }
    double multiplier = ((double)hCdce->pll_integer + \
                        ((double)hCdce->pll_num/(double)hCdce->pll_den));
    double newMultiplier = ((1.0+(constrainedPpm/(double)1e6))*multiplier);
    double multiplierDiff = newMultiplier - multiplier;

    double incVal = multiplierDiff*(double)hCdce->pll_den;
    double absStepVal = (incVal>(double)0)?incVal:-incVal;
    int32_t polarity  =  (incVal>(double)0)?CDCE6214_DCO_STEP_POSDIR:CDCE6214_DCO_STEP_NEGDIR;

    uint16_t inputStepVal = 0;

    /* Limit Step Size for Frequency FineTuning. */
    if (absStepVal > (double)CDCE6214_DCO_STEP_LIMIT)
    {
        inputStepVal = (uint16_t)CDCE6214_DCO_STEP_LIMIT;
    }
    else
    {
        inputStepVal = (uint16_t)absStepVal;
    }

    return CDCE6214_setDco(hCdce, inputStepVal, polarity);
}

int32_t CDCE6214_close(CDCE6214_Handle hCdce)
{
    int32_t retval = SystemP_FAILURE;
    if ((hCdce != NULL) && (hCdce->magic == CDCE6214_MAGIC_NUMBER))
    {
        hCdce->magic = 0;
        hCdce->i2cHandle = NULL;
        hCdce->devAddr = 0;
        hCdce->inputCrystalFreqMhz = 0.0;
        hCdce->currentPLLFreqMhz = 0.0;
        hCdce->pll_integer = 0;
        hCdce->pll_num = 0;
        hCdce->pll_den = 0;
        hCdce->dco_stepSize = 0;
        memset(hCdce->regWs, 0, sizeof(hCdce->regWs));
        retval = SystemP_SUCCESS;
    }
    return retval;
}