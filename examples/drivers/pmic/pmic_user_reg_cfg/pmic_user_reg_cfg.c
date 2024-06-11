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

/**
 *  \file pmic_user_reg_cfg.c
 *
 *  \brief An example to show the configuration of user space registers for
 *         various features in the PMIC IC.

 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <board/pmic.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

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

static int32_t PMICApp_configureADC(Pmic_CoreHandle_t *coreHandle);
static int32_t PMICApp_thermalMonitoring(Pmic_CoreHandle_t *coreHandle);
static int32_t PMICApp_voltageMonitoring(Pmic_CoreHandle_t *coreHandle);
static int32_t PMICApp_configureGPIO(Pmic_CoreHandle_t *coreHandle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void pmic_user_reg_cfg_main(void *args)
{
    uint32_t status = SystemP_FAILURE;

    /* PMIC interface handle initialized by PMIC_open */
    Pmic_CoreHandle_t *coreHandle = gPmicConfig[CONFIG_PMIC0].pmicCoreHandle;
    DebugP_assert(NULL != coreHandle);

    DebugP_log("\r\n");
    DebugP_log("Starting PMIC user space register configuration example !!\r\n\n");

    status = PMICApp_configureADC(coreHandle);
    if(SystemP_SUCCESS == status)
    {
        status = PMICApp_thermalMonitoring(coreHandle);
    }

    if(SystemP_SUCCESS == status)
    {
        status = PMICApp_voltageMonitoring(coreHandle);
    }

    if(SystemP_SUCCESS == status)
    {
        status = PMICApp_configureGPIO(coreHandle);
    }

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_logError ("Some tests have failed!!\r\n");
    }

    return;
}

static int32_t PMICApp_configureADC(Pmic_CoreHandle_t *coreHandle)
{
    int32_t        status = PMIC_ST_SUCCESS;
    int32_t        retVal = SystemP_FAILURE;
    bool          adcBusy = true;
    uint16_t      adcResultCode = 0;
    Pmic_adcCfg_t adcCfg =
    {
        .validParams = (PMIC_ADC_CFG_RDIV_EN_VALID_SHIFT | \
                            PMIC_ADC_CFG_THERMAL_SEL_VALID_SHIFT | \
                            PMIC_ADC_CFG_CONT_CONV_VALID_SHIFT),
        .rDivEn = PMIC_ADC_RESISTOR_DIVIDER_DISABLED,
        .thermalSel = PMIC_ADC_THERMAL_SEL_THERMAL_SENSOR,
        .contConv = PMIC_ADC_CONT_CONV_DISABLED,
    };

    /* Configure PMIC ADC */
    status = Pmic_ADCSetConfiguration(coreHandle, adcCfg);
    if(status == PMIC_ST_SUCCESS)
    {
        status = Pmic_ADCStartSingleConversionBlocking(coreHandle);
        while (adcBusy && (status == PMIC_ST_SUCCESS))
        {
            status = Pmic_ADCGetStatus(coreHandle, &adcBusy);
        }

        if(status == PMIC_ST_SUCCESS)
        {
            /* Get thermal sensor temperature ADC result code */
            status = Pmic_ADCGetResultCode(coreHandle, &adcResultCode);
        }
    }

    if(status == PMIC_ST_SUCCESS)
    {
        DebugP_log("ADC result code: %d \r\n", adcResultCode);
        DebugP_log("PMIC ADC configuration and get conversion result... DONE\r\n\n");
        retVal = SystemP_SUCCESS;
    }
    else
    {
        DebugP_logError("PMIC ADC configuration and get conversion result... Failed !!\r\n");
    }

    return retVal;
}

static int32_t PMICApp_thermalMonitoring(Pmic_CoreHandle_t *coreHandle)
{
    int32_t        status = PMIC_ST_SUCCESS;
    int32_t        retVal = SystemP_FAILURE;
    tps6522xThermalCfg_t thermalCfg =
    {
        .validParams = TPS6522X_TWARN_LEVEL_VALID_SHIFT | TPS6522X_TSD_ORD_LEVEL_VALID_SHIFT,
        .tsdOrdLvl   = TPS6522X_TSD_ORD_LVL_145C,
        .twarnLvl    = TPS6522X_TWARN_LVL_130C,
    };
    tps6522xThermalStat_t thermalStat =
    {
        .validParams = (PMIC_THERMAL_STAT_WARN_VALID | \
                        PMIC_THERMAL_STAT_ORD_SHTDWN_VALID | \
                        PMIC_THERMAL_STAT_IMM_SHTDWN_VALID),
        .twarnStat   = false,
        .tsdOrdStat  = false,
        .tsdImmStat  = false,
    };

    /* Set thermal configuration for Orderly TSD threshold and thermal warning threshold */
    status =  tps6522xSetThermalCfg(coreHandle, thermalCfg);
    if(status == PMIC_ST_SUCCESS)
    {
        /* Get the thermal statuses */
        status =  tps6522xGetThermalStat(coreHandle, &thermalStat);
    }

    if(status == PMIC_ST_SUCCESS)
    {
        DebugP_log("Thermal monitoring status:\r\n");
        DebugP_log("Thermal warning bit: %d\r\n", thermalStat.twarnStat);
        DebugP_log("Thermal orderly shutdown bit: %d\r\n", thermalStat.tsdOrdStat);
        DebugP_log("Thermal immediate shutdown bit: %d\r\n", thermalStat.tsdImmStat);
        DebugP_log("PMIC thermal monitoring configuration and get status... DONE\r\n\n");
        retVal = SystemP_SUCCESS;
    }
    else
    {
        DebugP_logError("PMIC thermal monitoring configuration and get status... Failed !!\r\n");
    }

    return retVal;
}

static int32_t PMICApp_voltageMonitoring(Pmic_CoreHandle_t *coreHandle)
{
    int32_t        status = PMIC_ST_SUCCESS;
    int32_t        retVal = SystemP_FAILURE;
    uint8_t pwrRsrcUVOVStat;
    bool underOverVoltageStat = false;

    /* Enable voltage monitors and set threshold for BUCK3, LDO2, VMON 1,2 and VCC VMON */
    tps6522xPwrRsrcCfg_t pwrRsrcCfg =
    {
        .validParams = (TPS6522X_BUCK3_VALID_SHIFT | \
                        TPS6522X_LDO2_VALID_SHIFT | \
                        TPS6522X_VMON1_VALID_SHIFT | \
                        TPS6522X_VCCA_VALID_SHIFT),
        .buckCfg[2].validParams = (TPS6522X_BUCK_VMON_EN_VALID_SHIFT | \
                                   TPS6522X_BUCK_VMON_THR_VALID_SHIFT),
        .buckCfg[2].buckVmonEn = TPS6522X_BUCK_VMON_ENABLE,
        .buckCfg[2].buckVmonThr = TPS6522X_BUCK_VMON_THR_4_PCT_OR_40_MV,
        .ldoCfg[1].validParams = (TPS6522X_LDO_VMON_EN_VALID_SHIFT | \
                                 TPS6522X_LDO_VMON_THR_VALID_SHIFT),
        .ldoCfg[1].ldoVmonEn = TPS6522X_LDO_VMON_ENABLE,
        .ldoCfg[1].ldoVmonThr = TPS6522X_LDO_VMON_THR_6_PCT,
        .vccaVmonCfg.validParams = (TPS6522X_VMON1_EN_VALID_SHIFT | \
                                    TPS6522X_VMON1_THR_VALID_SHIFT | \
                                    TPS6522X_VCCA_VMON_EN_VALID_SHIFT | \
                                    TPS6522X_VCCA_VMON_THR_VALID_SHIFT),
        .vccaVmonCfg.vmon1En = TPS6522X_VMON1_ENABLE,
        .vccaVmonCfg.vmon1Thr = TPS6522X_VMON1_THR_6_PCT_OR_60_MV,
        .vccaVmonCfg.vccaVmonEn = TPS6522X_VCCA_VMON_ENABLE,
        .vccaVmonCfg.vccaVmonThr = TPS6522X_VCCA_VMON_THR_4_PCT,
    };

    status = tps6522xSetPwrRsrcCfg(coreHandle, pwrRsrcCfg);
    if(status == PMIC_ST_SUCCESS)
    {
        /* Get the voltage monitoring status */
        pwrRsrcUVOVStat = TPS6522X_BUCK3_UVOV_STAT;
        status = tps6522xGetPwrRsrcStat(coreHandle, pwrRsrcUVOVStat, &underOverVoltageStat);
        if(status == PMIC_ST_SUCCESS)
        {
            DebugP_log("BUCK3 over-voltage/under-voltage status: %d\r\n", underOverVoltageStat);
            pwrRsrcUVOVStat = TPS6522X_LDO2_UVOV_STAT;
            status = tps6522xGetPwrRsrcStat(coreHandle, pwrRsrcUVOVStat, &underOverVoltageStat);
        }

        if(status == PMIC_ST_SUCCESS)
        {
            DebugP_log("LDO2 over-voltage/under-voltage status: %d\r\n", underOverVoltageStat);
            pwrRsrcUVOVStat = TPS6522X_VMON1_UVOV_STAT;
            status = tps6522xGetPwrRsrcStat(coreHandle, pwrRsrcUVOVStat, &underOverVoltageStat);
        }

        if(status == PMIC_ST_SUCCESS)
        {
            DebugP_log("VMON1 over-voltage/under-voltage status: %d\r\n", underOverVoltageStat);
            pwrRsrcUVOVStat = TPS6522X_VCCA_UVOV_STAT;
            status = tps6522xGetPwrRsrcStat(coreHandle, pwrRsrcUVOVStat, &underOverVoltageStat);
            if(status == PMIC_ST_SUCCESS)
            {
                DebugP_log("VCCA VMON over-voltage/under-voltage status: %d\r\n", underOverVoltageStat);
            }
        }
    }

    if(status == PMIC_ST_SUCCESS)
    {
        DebugP_log("PMIC voltage monitoring configuration and get status... DONE\r\n\n");
        retVal = SystemP_SUCCESS;
    }
    else
    {
        DebugP_logError("PMIC voltage monitoring configuration and get status... Failed !!\r\n");
    }

    return retVal;
}

static int32_t PMICApp_configureGPIO(Pmic_CoreHandle_t *coreHandle)
{
    int32_t        status = PMIC_ST_SUCCESS;
    int32_t        retVal = SystemP_FAILURE;

    /* Configure a GPIO pin in the PMIC */
    Pmic_GpioCfg_t gpioCfg =
    {
        .pinDir = PMIC_GPIO_INPUT,
        .pinFunc = PMIC_TPS6522X_GPIO_PINFUNC_GPIO6_NERR_MCU,
        .pullCtrl = PMIC_GPIO_PULL_DOWN,
        .deglitchEnable = PMIC_GPIO_DEGLITCH_ENABLE,
    };
    status = Pmic_gpioSetConfiguration(coreHandle, PMIC_TPS6522X_GPIO6_PIN, gpioCfg);
    if(status == PMIC_ST_SUCCESS)
    {
        DebugP_log("PMIC GPIO pin configuration... DONE\r\n\n");
        retVal = SystemP_SUCCESS;
    }
    else
    {
        DebugP_logError("PMIC GPIO pin configuration... Failed !!\r\n");
    }

    return retVal;
}
