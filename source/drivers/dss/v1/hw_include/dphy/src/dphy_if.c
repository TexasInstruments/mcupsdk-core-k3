/******************************************************************************
 * Copyright (C) 2012-2026 Cadence Design Systems, Inc.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * This file contains DPHY PHY API implementation.
 *
 *****************************************************************************/

#include <drivers/dss/v1/hw_include/dphy/csl_dphy.h>

#include "dphy_if_sanity.h"

// parasoft-begin-suppress METRICS-36-3 "A function should not be called from more than 5 different functions"

/**
 * Returns 1U or 0U depending on a received flag in the type of bool.
 */
static inline uint32_t boolToVal(bool state) {
    return ((state == true) ? 1U : 0U);
}

/**
 * Returns true or false depending on a received uint32_t value.
 */
static inline bool valToBool(uint32_t value) {
    return ((value != 0U) ? (bool) true : (bool) false);
}

/**
 * Writes CmnDigTbit13 register.
 * @param[in] pD Pointer to driver's private data object.
 * @param[in] config Pointer to test register 13 data.
 * @return CDN_EINVAL If pD or PllCmnDigTbit13 is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DPHY_SetPllCmnDigTbit13(const DPHY_PrivateData *pD,
        const DPHY_PllCmnDigTbit13 *config) {
    uint32_t status = CDN_EOK;

    /* check params */
    if (DPHY_SetPllCmnDigTbit13SF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t regVal = 0U;

        /* build dphy settings register value */
        regVal = CPS_FLD_WRITE(DPHY__CMN0_CMN_DIG_TBIT13,
                O_ANA_PLL_FB_DIV_LOW_TM_SEL, regVal,
                boolToVal(config->fbDivLowEn));
        regVal = CPS_FLD_WRITE(DPHY__CMN0_CMN_DIG_TBIT13,
                O_ANA_PLL_FB_DIV_LOW_TM, regVal, config->fbDivLowVal);

        regVal = CPS_FLD_WRITE(DPHY__CMN0_CMN_DIG_TBIT13,
                O_ANA_PLL_FB_DIV_HIGH_TM_SEL, regVal,
                boolToVal(config->fbDivHighEn));
        regVal = CPS_FLD_WRITE(DPHY__CMN0_CMN_DIG_TBIT13,
                O_ANA_PLL_FB_DIV_HIGH_TM, regVal, config->fbDivHighVal);

        /* write value to register */
        CPS_REG_WRITE(&pD->regBase->CMN0_CMN_DIG_TBIT13, regVal);
    }
    return status;
}

/**
 * Reads CmnDigTbit13 register.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] config Pointer to test register 13 data.
 * @return CDN_EINVAL If pD or PllCmnDigTbit13 is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DPHY_GetPllCmnDigTbit13(const DPHY_PrivateData *pD,
        DPHY_PllCmnDigTbit13 *config) {
    uint32_t status = CDN_EOK;

    /* check params */
    if (DPHY_GetPllCmnDigTbit13SF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register value */
        uint32_t regVal = CPS_REG_READ(&pD->regBase->CMN0_CMN_DIG_TBIT13);

        /* split value to fields */
        config->fbDivLowEn = valToBool(
                CPS_FLD_READ(DPHY__CMN0_CMN_DIG_TBIT13,
                        O_ANA_PLL_FB_DIV_LOW_TM_SEL,
                        regVal));
        config->fbDivLowVal = CPS_FLD_READ(DPHY__CMN0_CMN_DIG_TBIT13,
                O_ANA_PLL_FB_DIV_LOW_TM, regVal);

        config->fbDivHighEn = valToBool(
                CPS_FLD_READ(DPHY__CMN0_CMN_DIG_TBIT13,
                        O_ANA_PLL_FB_DIV_HIGH_TM_SEL, regVal));

        config->fbDivHighVal = CPS_FLD_READ(DPHY__CMN0_CMN_DIG_TBIT13,
                O_ANA_PLL_FB_DIV_HIGH_TM, regVal);
    }
    return status;
}

/**
 * Writes CmnDigTbit14 register.
 * @param[in] pD Pointer to driver's private data object.
 * @param[in] config Pointer to test register 14 data.
 * @return CDN_EINVAL If pD or PllCmnDigTbit14 is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DPHY_SetPllCmnDigTbit14(const DPHY_PrivateData *pD,
        const DPHY_PllCmnDigTbit14 *config) {
    uint32_t status = CDN_EOK;

    /* check params */
    if (DPHY_SetPllCmnDigTbit14SF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        uint32_t regVal = 0U;

        /* build dphy settings register value */
        regVal = CPS_FLD_WRITE(DPHY__CMN0_CMN_DIG_TBIT14,
                O_ANA_PLL_OP_DIV_TM_SEL, regVal,
                boolToVal(config->outDivLowEn));
        regVal = CPS_FLD_WRITE(DPHY__CMN0_CMN_DIG_TBIT14, O_ANA_PLL_OP_DIV_TM,
                regVal, config->outDivLowVal);

        regVal = CPS_FLD_WRITE(DPHY__CMN0_CMN_DIG_TBIT14,
                O_ANA_PLL_IP_DIV_TM_SEL, regVal, boolToVal(config->inDivLowEn));
        regVal = CPS_FLD_WRITE(DPHY__CMN0_CMN_DIG_TBIT14, O_ANA_PLL_IP_DIV_TM,
                regVal, config->inDivLowVal);

        /* write value to register */
        CPS_REG_WRITE(&pD->regBase->CMN0_CMN_DIG_TBIT14, regVal);
    }
    return status;
}

/**
 * Reads CmnDigTbit14 register.
 * @param[in] pD Pointer to driver's private data object.
 * @param[out] config Pointer to test register 14 data.
 * @return CDN_EINVAL If pD or PllCmnDigTbit14 is NULL.
 * @return CDN_EOK On success.
 */
uint32_t DPHY_GetPllCmnDigTbit14(const DPHY_PrivateData *pD,
        DPHY_PllCmnDigTbit14 *config) {
    uint32_t status = CDN_EOK;

    /* check params */
    if (DPHY_GetPllCmnDigTbit14SF(pD, config) != CDN_EOK) {
        status = CDN_EINVAL;
    } else {
        /* read register value */
        uint32_t regVal = CPS_REG_READ(&pD->regBase->CMN0_CMN_DIG_TBIT14);

        /* split value to fields */
        config->outDivLowEn = valToBool(
                CPS_FLD_READ(DPHY__CMN0_CMN_DIG_TBIT14,
                        O_ANA_PLL_OP_DIV_TM_SEL,
                        regVal));
        config->outDivLowVal = CPS_FLD_READ(DPHY__CMN0_CMN_DIG_TBIT14,
                O_ANA_PLL_OP_DIV_TM, regVal);

        config->inDivLowEn = valToBool(
                CPS_FLD_READ(DPHY__CMN0_CMN_DIG_TBIT14, O_ANA_PLL_IP_DIV_TM_SEL,
                        regVal));
        config->inDivLowVal = CPS_FLD_READ(DPHY__CMN0_CMN_DIG_TBIT14,
                O_ANA_PLL_IP_DIV_TM, regVal);
    }
    return status;
}

// parasoft-end-suppress METRICS-36-3
