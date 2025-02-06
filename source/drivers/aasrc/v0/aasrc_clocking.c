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

#include <math.h>
#include "aasrc.h"
#include <drivers/soc.h>
#include <drivers/hw_include/cslr_aasrc.h>
#include <drivers/hw_include/cslr_aasrc_data_r0.h>
#include <drivers/hw_include/cslr_aasrc_data_r1.h>

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      API Function Definitions                              */
/* ========================================================================== */

int32_t AASRC_ClkZoneRxConfig(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = NULL;
    AASRC_Handle drvHandle =  NULL;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *object = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint8_t clkZone;
    AASRC_ClockZoneConfig *clkZoneCfg = NULL;
    const CSL_aasrc_cfgRegs *pReg = NULL;

    if( NULL == chHandle)
    {
        status = AASRC_EBADARGS;
    }
    else
    {
        chObj = (AASRC_ChObj *)chHandle;
        clkZone = chObj->chCfg.inClkZone;
        drvHandle =  chObj->drvHandle;

        if (clkZone >= AASRC_INPUT_CLOCK_ZONE_COUNT)
        {
            status = AASRC_EINVALID_PARAMS;
        }
        if((NULL != drvHandle) && (AASRC_SOK == status))
        {
            drvCfg = (AASRC_Config *)drvHandle;
            object = drvCfg->object;
            attrs = drvCfg->attrs;
            clkZoneCfg = &(object->openParams.rxClkZoneCfg[clkZone]);
            pReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
        }
    }

    if (AASRC_SOK == status)
    {
        if (NULL == clkZoneCfg)
        {
            status = AASRC_EFAIL;
        }
        else
        {
            if (clkZoneCfg->syncPin >= AASRC_RXSYNC_PIN_COUNT)
            {
                status = AASRC_EINVALID_PARAMS;
            }
        }
    }

    if (AASRC_SOK == status)
    {
        switch (clkZone)
        {
            case AASRC_INPUT_CLOCK_ZONE0_IDX:
                /* ----- Input clock zone 0 settings ----- */
                /* connecting the selected rxsync pin to clock zone 0 */
                CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_0,
                                AASRC_CFG_INPUT_CLOCKZONE_CONTROL_0_INPUT_CLOCK_ZONE_CLOCK_SOURCE_SELECT, clkZoneCfg->syncPin);
                /* setting the clock divider for clock zone 0 */
                if (clkZoneCfg->clkZoneDiv < AASRC_INTERNAL_CLOCK_DIVISOR_MAX_VAL)
                {
                    /* set clock divider value for clock zone 0 */
                    CSL_REG32_FINS(&pReg->INPUT_CLOCK_ZONE_DIVIDER,
                                    AASRC_CFG_INPUT_CLOCK_ZONE_DIVIDER_CLOCK_ZONE0_DIVIDE, clkZoneCfg->clkZoneDiv);
                    /* enable clock divider for clock zone 0 */
                    CSL_REG32_FINS(&pReg->INPUT_CLOCK_ZONE_DIVIDER,
                                    AASRC_CFG_INPUT_CLOCK_ZONE_DIVIDER_CLOCK_ZONE0_DIVIDE_EN, clkZoneCfg->isClkZoneDivEnable);
                }
                else
                {
                    status = AASRC_EINVALID_PARAMS;
                }
                /* override clock settle signal for clock zone 0 */
                if (clkZoneCfg->overrideClkSettle)
                {
                    CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_0,
                                    AASRC_CFG_INPUT_CLOCKZONE_CONTROL_0_OVERRIDE_SETTLE, clkZoneCfg->overrideClkSettle);

                    /* if override is enabled, override clock settle value is defaulted to 1 for clock zone 0 */
                    CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_0,
                                    AASRC_CFG_INPUT_CLOCKZONE_CONTROL_0_OVERRIDE_SETTLE_VALUE, 1);
                }
                break;
            case AASRC_INPUT_CLOCK_ZONE1_IDX:
                /* ----- Input clock zone 1 settings ----- */
                /* connecting the selected rxsync pin to clock zone 1 */
                CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_1,
                                AASRC_CFG_INPUT_CLOCKZONE_CONTROL_1_INPUT_CLOCK_ZONE_CLOCK_SOURCE_SELECT, clkZoneCfg->syncPin);
                /* setting the clock divider for clock zone 1 */
                if (clkZoneCfg->clkZoneDiv < AASRC_INTERNAL_CLOCK_DIVISOR_MAX_VAL)
                {
                    /* set clock divider value for clock zone 1 */
                    CSL_REG32_FINS(&pReg->INPUT_CLOCK_ZONE_DIVIDER,
                                    AASRC_CFG_INPUT_CLOCK_ZONE_DIVIDER_CLOCK_ZONE1_DIVIDE, clkZoneCfg->clkZoneDiv);
                    /* enable clock divider for clock zone 1 */
                    CSL_REG32_FINS(&pReg->INPUT_CLOCK_ZONE_DIVIDER,
                                    AASRC_CFG_INPUT_CLOCK_ZONE_DIVIDER_CLOCK_ZONE1_DIVIDE_EN, clkZoneCfg->isClkZoneDivEnable);
                }
                else
                {
                    status = AASRC_EINVALID_PARAMS;
                }
                /* override clock settle signal for clock zone 1 */
                if (clkZoneCfg->overrideClkSettle)
                {
                    CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_1,
                                    AASRC_CFG_INPUT_CLOCKZONE_CONTROL_1_OVERRIDE_SETTLE, clkZoneCfg->overrideClkSettle);

                    /* if override is enabled, override clock settle value is defaulted to 1 for clock zone 1 */
                    CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_1,
                                    AASRC_CFG_INPUT_CLOCKZONE_CONTROL_1_OVERRIDE_SETTLE_VALUE, 1);
                }
                break;
            case AASRC_INPUT_CLOCK_ZONE2_IDX:
                /* ----- Input clock zone 2 settings ----- */
                /* connecting the selected rxsync pin to clock zone 2 */
                CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_2,
                                AASRC_CFG_INPUT_CLOCKZONE_CONTROL_2_INPUT_CLOCK_ZONE_CLOCK_SOURCE_SELECT, clkZoneCfg->syncPin);
                /* override clock settle signal for clock zone 2 */
                if (clkZoneCfg->overrideClkSettle)
                {
                    CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_2,
                                    AASRC_CFG_INPUT_CLOCKZONE_CONTROL_2_OVERRIDE_SETTLE, clkZoneCfg->overrideClkSettle);

                    /* if override is enabled, override clock settle value is defaulted to 1 for clock zone 2 */
                    CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_2,
                                    AASRC_CFG_INPUT_CLOCKZONE_CONTROL_2_OVERRIDE_SETTLE_VALUE, 1);
                }
                /* checking if the the clock divider is enabled for input clock zone 2 */
                if (clkZoneCfg->isClkZoneDivEnable)
                {
                    status = AASRC_EINVALID_PARAMS;
                }
                break;
            case AASRC_INPUT_CLOCK_ZONE3_IDX:
                /* ----- Input clock zone 3 settings ----- */
                /* connecting the selected rxsync pin to clock zone 3 */
                CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_3,
                                AASRC_CFG_INPUT_CLOCKZONE_CONTROL_3_INPUT_CLOCK_ZONE_CLOCK_SOURCE_SELECT, clkZoneCfg->syncPin);
                if (clkZoneCfg->overrideClkSettle)
                {
                    /* override clock settle signal for clock zone 3 */
                    CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_3,
                                   AASRC_CFG_INPUT_CLOCKZONE_CONTROL_3_OVERRIDE_SETTLE, clkZoneCfg->overrideClkSettle);

                    /* if override is enabled, override clock settle value is defaulted to 1 for clock zone 3 */
                    CSL_REG32_FINS(&pReg->INPUT_CLOCKZONE_CONTROL_3,
                                    AASRC_CFG_INPUT_CLOCKZONE_CONTROL_3_OVERRIDE_SETTLE_VALUE, 1U);
                }
                /* checking if the the clock divider is enabled for input clock zone 3 */
                if (clkZoneCfg->isClkZoneDivEnable)
                {
                    status = AASRC_EINVALID_PARAMS;
                }
                break;
            default:
                status = AASRC_EINVALID_PARAMS;
                break;
        }
    }

    return status;
}

int32_t AASRC_ClkZoneTxConfig(AASRC_ChHandle chHandle)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = NULL;
    AASRC_Handle drvHandle =  NULL;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *object = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint8_t clkZone;
    AASRC_ClockZoneConfig *clkZoneCfg = NULL;
    const CSL_aasrc_cfgRegs *pReg = NULL;

    if( NULL == chHandle)
    {
        status = AASRC_EBADARGS;
    }
    else
    {
        chObj = (AASRC_ChObj *)chHandle;
        clkZone = chObj->chCfg.outClkZone;
        drvHandle =  chObj->drvHandle;

        if (clkZone >= AASRC_OUTPUT_CLOCK_ZONE_COUNT)
        {
            status = AASRC_EINVALID_PARAMS;
        }

        if((NULL != drvHandle) && (AASRC_SOK == status))
        {
            drvCfg = (AASRC_Config *)drvHandle;
            object = drvCfg->object;
            attrs = drvCfg->attrs;
            clkZoneCfg = &(object->openParams.txClkZoneCfg[clkZone]);
            pReg = (const CSL_aasrc_cfgRegs *)attrs->baseAddr;
        }
    }

    if (AASRC_SOK == status)
    {
        if (NULL == clkZoneCfg)
        {
            status = AASRC_EFAIL;
        }
        else
        {
            if (clkZoneCfg->syncPin >= AASRC_TXSYNC_PIN_COUNT)
            {
                status = AASRC_EINVALID_PARAMS;
            }
        }
    }

    if (AASRC_SOK == status)
    {
        switch (clkZone)
        {
            case AASRC_OUTPUT_CLOCK_ZONE0_IDX:
                /* ----- Output clock zone 0 settings ----- */
                /* connecting the selected txsync pin to clock zone 0 */
                CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_0,
                                AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_0_OUTPUT_CLOCK_ZONE_CLOCK_SOURCE_SELECT, clkZoneCfg->syncPin);
                /* setting the clock divider for clock zone 0 */
                if (clkZoneCfg->clkZoneDiv < AASRC_INTERNAL_CLOCK_DIVISOR_MAX_VAL)
                {
                    /* set clock divider value for clock zone 0 */
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCK_ZONE_DIVIDER,
                                    AASRC_CFG_OUTPUT_CLOCK_ZONE_DIVIDER_CLOCK_ZONE0_DIVIDE, clkZoneCfg->clkZoneDiv);
                    /* enable clock divider for clock zone 0 */
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCK_ZONE_DIVIDER,
                                    AASRC_CFG_OUTPUT_CLOCK_ZONE_DIVIDER_CLOCK_ZONE0_DIVIDE_EN, clkZoneCfg->isClkZoneDivEnable);
                }
                else
                {
                    status = AASRC_EINVALID_PARAMS;
                }
                /* override clock settle signal for clock zone 0 */
                if (clkZoneCfg->overrideClkSettle)
                {
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_0,
                                    AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_0_OVERRIDE_SETTLE, clkZoneCfg->overrideClkSettle);

                    /* if override is enabled, override clock settle value is defaulted to 1 for clock zone 0 */
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_0,
                                    AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_0_OVERRIDE_SETTLE_VALUE, 1);
                }
                break;
            case AASRC_OUTPUT_CLOCK_ZONE1_IDX:
                /* ----- Output clock zone 1 settings ----- */
                /* connecting the selected txsync pin to clock zone 1 */
                CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_1,
                                AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_1_OUTPUT_CLOCK_ZONE_CLOCK_SOURCE_SELECT, clkZoneCfg->syncPin);
                /* setting the clock divider for clock zone 1 */
                if (clkZoneCfg->clkZoneDiv < AASRC_INTERNAL_CLOCK_DIVISOR_MAX_VAL)
                {
                    /* set clock divider value for clock zone 1 */
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCK_ZONE_DIVIDER,
                                    AASRC_CFG_OUTPUT_CLOCK_ZONE_DIVIDER_CLOCK_ZONE1_DIVIDE, clkZoneCfg->clkZoneDiv);
                    /* enable clock divider for clock zone 1 */
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCK_ZONE_DIVIDER,
                                    AASRC_CFG_OUTPUT_CLOCK_ZONE_DIVIDER_CLOCK_ZONE1_DIVIDE_EN, clkZoneCfg->isClkZoneDivEnable);
                }
                else
                {
                    status = AASRC_EINVALID_PARAMS;
                }
                /* override clock settle signal for clock zone 1 */
                if (clkZoneCfg->overrideClkSettle)
                {
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_1,
                                    AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_1_OVERRIDE_SETTLE, clkZoneCfg->overrideClkSettle);

                    /* if override is enabled, override clock settle value is defaulted to 1 for clock zone 1 */
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_1,
                                    AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_1_OVERRIDE_SETTLE_VALUE, 1);
                }
                break;
            case AASRC_OUTPUT_CLOCK_ZONE2_IDX:
                /* ----- Output clock zone 2 settings ----- */
                /* connecting the selected txsync pin to clock zone 2 */
                CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_2,
                                AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_2_OUTPUT_CLOCK_ZONE_CLOCK_SOURCE_SELECT, clkZoneCfg->syncPin);
                /* override clock settle signal for clock zone 2 */
                CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_2,
                                AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_2_OVERRIDE_SETTLE, clkZoneCfg->overrideClkSettle);
                if (clkZoneCfg->overrideClkSettle)
                {
                    /* if override is enabled, override clock settle value is defaulted to 1 for clock zone 2 */
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_2,
                                    AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_2_OVERRIDE_SETTLE_VALUE, 1);
                }
                /* checking if the the clock divider is enabled for output clock zone 2 */
                if (clkZoneCfg->isClkZoneDivEnable)
                {
                    status = AASRC_EINVALID_PARAMS;
                }
                break;
            case AASRC_OUTPUT_CLOCK_ZONE3_IDX:
                /* ----- Output clock zone 3 settings ----- */
                /* connecting the selected txsync pin to clock zone 3 */
                CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_3,
                                AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_3_OUTPUT_CLOCK_ZONE_CLOCK_SOURCE_SELECT, clkZoneCfg->syncPin);
                if (clkZoneCfg->overrideClkSettle)
                {
                /* override clock settle signal for clock zone 3 */
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_3,
                                    AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_3_OVERRIDE_SETTLE, clkZoneCfg->overrideClkSettle);

                    /* if override is enabled, override clock settle value is defaulted to 1 for clock zone 3 */
                    CSL_REG32_FINS(&pReg->OUTPUT_CLOCKZONE_CONTROL_3,
                                    AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_3_OVERRIDE_SETTLE_VALUE, 1U);
                }
                /* checking if the the clock divider is enabled for output clock zone 3 */
                if (clkZoneCfg->isClkZoneDivEnable)
                {
                    status = AASRC_EINVALID_PARAMS;
                }
                break;
            default:
                status = AASRC_EINVALID_PARAMS;
                break;
        }
    }

    return status;
}

int32_t AASRC_IsClockZoneRxSettled(AASRC_ChHandle chHandle, bool *isClkSettled)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = NULL;
    AASRC_Handle drvHandle =  NULL;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *object = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint8_t clkZone;
    AASRC_ClockZoneConfig *clkZoneCfg = NULL;
    uint32_t baseAddr;
    uint32_t regVal;

    if( NULL == chHandle)
    {
        status = AASRC_EBADARGS;
    }
    else
    {
        chObj = (AASRC_ChObj *)chHandle;
        clkZone = chObj->chCfg.inClkZone;
        drvHandle =  chObj->drvHandle;

        if (clkZone >= AASRC_INPUT_CLOCK_ZONE_COUNT)
        {
            status = AASRC_EINVALID_PARAMS;
        }
        if((NULL != drvHandle) && (AASRC_SOK == status))
        {
            drvCfg = (AASRC_Config *)drvHandle;
            object = drvCfg->object;
            attrs = drvCfg->attrs;
            clkZoneCfg = &(object->openParams.rxClkZoneCfg[clkZone]);
            baseAddr = (uint32_t)attrs->baseAddr;
        }
    }

    if (NULL == clkZoneCfg)
    {
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
        {
            regVal = CSL_REG32_FEXT(baseAddr + AASRC_INPUT_CLOCKZONE_CONTROL(clkZone),
                                    AASRC_CFG_INPUT_CLOCKZONE_CONTROL_0_SETTLE);
            if (regVal > 1U)
            {
                *isClkSettled = false;
                status = AASRC_EFAIL;
            }
            else if (regVal == 1U)
            {
                *isClkSettled = true;
            }
            else
            {
                *isClkSettled = false;
        }
    }

    return status;
}

int32_t AASRC_IsClockZoneTxSettled(AASRC_ChHandle chHandle, bool *isClkSettled)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = NULL;
    AASRC_Handle drvHandle =  NULL;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *object = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint8_t clkZone;
    AASRC_ClockZoneConfig *clkZoneCfg = NULL;
    uint32_t baseAddr;
    uint32_t regVal;

    if( NULL == chHandle)
    {
        status = AASRC_EBADARGS;
    }
    else
    {
        chObj = (AASRC_ChObj *)chHandle;
        clkZone = chObj->chCfg.outClkZone;
        drvHandle =  chObj->drvHandle;

        if (clkZone >= AASRC_OUTPUT_CLOCK_ZONE_COUNT)
        {
            status = AASRC_EINVALID_PARAMS;
        }
        if((NULL != drvHandle) && (AASRC_SOK == status))
        {
            drvCfg = (AASRC_Config *)drvHandle;
            object = drvCfg->object;
            attrs = drvCfg->attrs;
            clkZoneCfg = &(object->openParams.txClkZoneCfg[clkZone]);
            baseAddr = (uint32_t)attrs->baseAddr;
        }
    }

    if (NULL == clkZoneCfg)
    {
        status = AASRC_EFAIL;
    }

    if (AASRC_SOK == status)
        {
            regVal = CSL_REG32_FEXT(baseAddr + AASRC_OUTPUT_CLOCKZONE_CONTROL(clkZone),
                                    AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_0_SETTLE);
            if (regVal > 1U)
            {
                *isClkSettled = false;
                status = AASRC_EFAIL;
            }
            else if (regVal == 1U)
            {
                *isClkSettled = true;
            }
            else
            {
                *isClkSettled = false;
        }
    }

    return status;
}

int32_t AASRC_GetClkZoneRxFrequency(AASRC_ChHandle chHandle,float *clkFrequency)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = NULL;
    AASRC_Handle drvHandle =  NULL;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *object = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint8_t clkZone;
    AASRC_ClockZoneConfig *clkZoneCfg = NULL;
    uint32_t baseAddr;
    uint32_t regValLo, regValHi;
    uint32_t intPart, fracPart;
    float recoverLoopRate;
    uint32_t isClkSettled = 0U;
    uint32_t timeout = 0U;
    uint64_t sysClkRate = 0U;

    if( NULL == chHandle)
    {
        status = AASRC_EBADARGS;
    }
    else
    {
        chObj = (AASRC_ChObj *)chHandle;
        clkZone = chObj->chCfg.inClkZone;
        drvHandle =  chObj->drvHandle;

        if (clkZone >= AASRC_INPUT_CLOCK_ZONE_COUNT)
        {
            status = AASRC_EINVALID_PARAMS;
        }
        if((NULL != drvHandle) && (AASRC_SOK == status))
        {
            drvCfg = (AASRC_Config *)drvHandle;
            object = drvCfg->object;
            attrs = drvCfg->attrs;
            clkZoneCfg = &(object->openParams.rxClkZoneCfg[clkZone]);
            baseAddr = (uint32_t)attrs->baseAddr;
        }
    }

    if (NULL == clkZoneCfg)
    {
        status = AASRC_EFAIL;
    }

    *clkFrequency = 0.0;

    if (AASRC_SOK == status)
    {
        isClkSettled = false;
        timeout = 0U;
        while( (true != isClkSettled) && (timeout < 0xFFFFFFU) )
        {
            isClkSettled = CSL_REG32_FEXT(baseAddr + AASRC_INPUT_CLOCKZONE_CONTROL(clkZone),
                                                    AASRC_CFG_INPUT_CLOCKZONE_CONTROL_0_SETTLE);
            timeout++;
        }
        if (isClkSettled == 0U)
        {
            status = AASRC_EFAIL;
        }
    }
    if (AASRC_SOK == status)
    {
        regValLo = CSL_REG32_RD(baseAddr + AASRC_INPUT_CLOCK_RECOVERY_LOOP_RATE_LO(clkZone));
        regValHi = CSL_REG32_RD(baseAddr + AASRC_INPUT_CLOCK_RECOVERY_LOOP_RATE_HI(clkZone));

        fracPart = (regValLo & CSL_AASRC_CFG_INPUT_CLOCK_RECOVERY_LOOP_RATE_LO_0_FRACTIONAL_STAMP_MASK);
        intPart  = ((regValHi & CSL_AASRC_CFG_INPUT_CLOCK_RECOVERY_LOOP_RATE_HI_0_RATE_INT_HI_MASK) << 8) +
                   ((regValLo & CSL_AASRC_CFG_INPUT_CLOCK_RECOVERY_LOOP_RATE_LO_0_RATE_INT_LO_MASK) >> \
                     CSL_AASRC_CFG_INPUT_CLOCK_RECOVERY_LOOP_RATE_LO_0_RATE_INT_LO_SHIFT);

        recoverLoopRate = (float)intPart + (fracPart / (float)(pow(10, 8)));

        if (attrs->instNum == AASRC0)
        {
            status = SOC_moduleGetClockFrequency(TISCI_DEV_AASRC0,
                                                 TISCI_DEV_AASRC0_SYS_CLK,
                                                 &sysClkRate);
        }
        else if (attrs->instNum == AASRC1)
        {
            status = SOC_moduleGetClockFrequency(TISCI_DEV_AASRC1,
                                                 TISCI_DEV_AASRC1_SYS_CLK,
                                                 &sysClkRate);
        }
        DebugP_assertNoLog(status == SystemP_SUCCESS);

        if(recoverLoopRate != 0U)
        {
            *clkFrequency = (float)sysClkRate / (float)(recoverLoopRate * pow(10,3));
        }
        else
        {
            status = AASRC_EFAIL;
        }

    }

    return status;
}

int32_t AASRC_GetClkZoneTxFrequency(AASRC_ChHandle chHandle,float *clkFrequency)
{
    int32_t status = AASRC_SOK;
    AASRC_ChObj *chObj = NULL;
    AASRC_Handle drvHandle =  NULL;
    AASRC_Config *drvCfg = NULL;
    AASRC_Object *object = NULL;
    const AASRC_Attrs *attrs = NULL;
    uint8_t clkZone;
    AASRC_ClockZoneConfig *clkZoneCfg = NULL;
    uint32_t baseAddr;
    uint32_t regValLo, regValHi;
    uint32_t intPart, fracPart;
    float recoverLoopRate;
    uint32_t isClkSettled = 0U;
    uint32_t timeout = 0U;
    uint64_t sysClkRate = 0U;

    if( NULL == chHandle)
    {
        status = AASRC_EBADARGS;
    }
    else
    {
        chObj = (AASRC_ChObj *)chHandle;
        clkZone = chObj->chCfg.outClkZone;
        drvHandle =  chObj->drvHandle;

        if (clkZone >= AASRC_OUTPUT_CLOCK_ZONE_COUNT)
        {
            status = AASRC_EINVALID_PARAMS;
        }
        if((NULL != drvHandle) && (AASRC_SOK == status))
        {
            drvCfg = (AASRC_Config *)drvHandle;
            object = drvCfg->object;
            attrs = drvCfg->attrs;
            clkZoneCfg = &(object->openParams.txClkZoneCfg[clkZone]);
            baseAddr = (uint32_t)attrs->baseAddr;
        }
    }

    if (NULL == clkZoneCfg)
    {
        status = AASRC_EFAIL;
    }

    *clkFrequency = 0.0;

    if (AASRC_SOK == status)
    {
        isClkSettled = false;
        timeout = 0U;
        while( (true != isClkSettled) && (timeout < 0xFFFFFFU) )
        {
            isClkSettled = CSL_REG32_FEXT(baseAddr + AASRC_OUTPUT_CLOCKZONE_CONTROL(clkZone),
                                                  AASRC_CFG_OUTPUT_CLOCKZONE_CONTROL_0_SETTLE);
            timeout++;
        }
        if (isClkSettled == 0U)
        {
            status = AASRC_EFAIL;
        }
    }
    if (AASRC_SOK == status)
    {
        regValLo = CSL_REG32_RD(baseAddr + AASRC_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_LO(clkZone));
        regValHi = CSL_REG32_RD(baseAddr + AASRC_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_HI(clkZone));

        fracPart = (regValLo & CSL_AASRC_CFG_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_LO_0_FRACTIONAL_STAMP_MASK);
        intPart  = ((regValHi & CSL_AASRC_CFG_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_HI_0_RATE_INT_HI_MASK) << 8) +
                   ((regValLo & CSL_AASRC_CFG_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_LO_0_RATE_INT_LO_MASK) >> \
                     CSL_AASRC_CFG_OUTPUT_CLOCK_RECOVERY_LOOP_RATE_LO_0_RATE_INT_LO_SHIFT);

        recoverLoopRate = (float)intPart + (fracPart / (float)(pow(10, 8)));

        if (attrs->instNum == AASRC0)
        {
            status = SOC_moduleGetClockFrequency(TISCI_DEV_AASRC0,
                                                 TISCI_DEV_AASRC0_SYS_CLK,
                                                 &sysClkRate);
        }
        else if (attrs->instNum == AASRC1)
        {
            status = SOC_moduleGetClockFrequency(TISCI_DEV_AASRC1,
                                                 TISCI_DEV_AASRC1_SYS_CLK,
                                                 &sysClkRate);
        }
        DebugP_assertNoLog(status == SystemP_SUCCESS);

        if(recoverLoopRate != 0U)
        {
            *clkFrequency = (float)sysClkRate / (float)(recoverLoopRate * pow(10,3));
        }
        else
        {
            status = AASRC_EFAIL;
        }
    }

    return status;
}
