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
 *  \file pmic_trigger_watchdog_reset.c
 *
 *  \brief This is a PMIC watchdog example for trigger mode which will generate
 *         a reset when MCU fails to send a signal to the watchdog.
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

static int32_t PMICApp_isWdogResetDone(Pmic_CoreHandle_t *coreHandle);
static int32_t PMICApp_setTrigWdogPin(PMIC_Config pmicConfig);
static int32_t PMICApp_wdogTriggerModeReset(PMIC_Config pmicConfig);
static void PMICApp_checkForWdgErrors(Pmic_CoreHandle_t *coreHandle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* The address of GPIO instance used for sending the watchdog trigger signal
 * from the MCU core to the PMIC
 */
static uint32_t gGpioWdogTrigBaseAddr = (uint32_t) (GPIO_WDOG_TRIG_BASE_ADDR);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void pmic_trigger_watchdog_reset_main(void *args)
{
    uint32_t status = SystemP_FAILURE;
    uint32_t  trigGpioPinNum = GPIO_WDOG_TRIG_PIN;

    /* PMIC interface handle initialized by PMIC_open */
    PMIC_Config pmicConfig = gPmicConfig[CONFIG_PMIC0];
    DebugP_assert(NULL != pmicConfig.pmicCoreHandle);

    /* Check if the example has already run and core is reset due to watchdog
     * error warm reset. If yes, print the success message and exit the program.
     * Otherwise, continue executing the program to trigger a watchdog reset.
     * This check is for testing purpose, actual application may not require it.
     */

    if(PMICApp_isWdogResetDone(pmicConfig.pmicCoreHandle) == SystemP_SUCCESS)
    {
        DebugP_log("Warm reset has occurred due to watchdog failure!! \r\n");

        uint32_t pmicStatus;
        Pmic_WdgCfg_t tmpWdgCfg;
        Pmic_CoreHandle_t *coreHandle = pmicConfig.pmicCoreHandle;
        /* Set the PWRHOLD, so watchdog remains in long window */
        tmpWdgCfg.validParams = PMIC_CFG_WDG_PWRHOLD_VALID_SHIFT;
        tmpWdgCfg.pwrHold = true;
        pmicStatus = Pmic_wdgSetCfg(coreHandle, &tmpWdgCfg);
        if(pmicStatus == PMIC_ST_SUCCESS)
        {
            /* Clear WD_FAIL_INT and WD_RST_INT error bits */
            pmicStatus = Pmic_wdgClrErrStatus(coreHandle, PMIC_WDG_ERR_FAIL_INT);
            if(pmicStatus == PMIC_ST_SUCCESS)
            {
                pmicStatus = Pmic_wdgClrErrStatus(coreHandle, PMIC_WDG_ERR_RST_INT);
                if(pmicStatus == PMIC_ST_SUCCESS)
                {
                    status = SystemP_SUCCESS;
                }
            }
        }
    }
    else
    {
        DebugP_log("\r\n");
        DebugP_log("Starting trigger watchdog reset example !!\r\n");

        /* Set direction mode for the GPIO pin to send watchdog trigger signal */
        GPIO_setDirMode(gGpioWdogTrigBaseAddr, trigGpioPinNum, GPIO_WDOG_TRIG_DIR);

        /* Set the PMIC GPIO pin select as TRIG_WDOG */
        status = PMICApp_setTrigWdogPin(pmicConfig);
        if(SystemP_SUCCESS == status)
        {
            /* Configure the PMIC to start watchdog trigger mode and check
             * if warm reset occurs when trigger signal is not sent.
             */
            status = PMICApp_wdogTriggerModeReset(pmicConfig);
        }
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

static int32_t PMICApp_isWdogResetDone(Pmic_CoreHandle_t *coreHandle)
{
    int32_t        status = PMIC_ST_SUCCESS;
    int32_t        retVal = SystemP_FAILURE;
    Pmic_WdgErrStatus_t wdgErrStat =
    {
        .validParams = PMIC_CFG_WD_RST_INT_ERRSTAT_VALID_SHIFT
    };

    /* Check whether WD_RST_INT error is raised */
    status = Pmic_wdgGetErrorStatus(coreHandle, &wdgErrStat);
    if((status == PMIC_ST_SUCCESS) && (wdgErrStat.wdRstInt == true))
    {
        retVal = SystemP_SUCCESS;
    }

    return retVal;
}

static int32_t PMICApp_setTrigWdogPin(PMIC_Config pmicConfig)
{
    Pmic_CoreHandle_t *coreHandle = pmicConfig.pmicCoreHandle;
    int32_t        status = PMIC_ST_SUCCESS;
    int32_t        retVal = SystemP_FAILURE;

    const Pmic_GpioCfg_t trigGPIOCfg =
    {
        .validParams      = (PMIC_GPIO_CFG_DIR_VALID_SHIFT | \
                             PMIC_GPIO_CFG_PINFUNC_VALID_SHIFT | \
                             PMIC_GPIO_CFG_PULL_VALID_SHIFT    | \
                             PMIC_GPIO_CFG_DEGLITCH_VALID_SHIFT),
        .pinDir           = PMIC_GPIO_INPUT,
        .outputSignalType = 0U,
        .pullCtrl         = PMIC_GPIO_PULL_DOWN,
        .deglitchEnable   = PMIC_GPIO_DEGLITCH_ENABLE,
        .pinFunc          = pmicConfig.trigWdogPinFunc,
        .pinPolarity      = 0U,
    };

    /* Configure PMIC GPIO trigger watchdog pin */
    status = Pmic_gpioSetConfiguration(coreHandle, pmicConfig.trigWdogPin, trigGPIOCfg);
    if(status == PMIC_ST_SUCCESS)
    {
        DebugP_log("Configure GPIO trigger watchdog pin in the PMIC... DONE\r\n");
        retVal = SystemP_SUCCESS;
    }
    else
    {
        DebugP_logError("Configure GPIO trigger watchdog pin in the PMIC ... Failed !!\r\n");
    }

    return retVal;
}

static int32_t PMICApp_wdogTriggerModeReset(PMIC_Config pmicConfig)
{
    int32_t        status = PMIC_ST_SUCCESS;
    int32_t        retVal = SystemP_FAILURE;
    uint16_t      numSeqeunces = 0;
    bool    wdgEnabled = false;
    Pmic_CoreHandle_t *coreHandle = pmicConfig.pmicCoreHandle;
    Pmic_WdgCfg_t tmpWdgCfg;

    status = Pmic_wdgGetEnableState(coreHandle, &wdgEnabled);
    if (status == PMIC_ST_SUCCESS && !wdgEnabled)
    {
        status = Pmic_wdgEnable(coreHandle);
    }

    if(status == PMIC_ST_SUCCESS)
    {
        /* Configure watchdog for Trigger mode */
        status = Pmic_wdgSetCfg(coreHandle, &gPmicWdgCfg[CONFIG_PMIC0]);
        /* Clear all interrupts */
        status += Pmic_irqClrErrStatus(coreHandle, PMIC_IRQ_ALL);
    }

    if(status == PMIC_ST_SUCCESS)
    {
        DebugP_log("Configure PMIC watchdog in Trigger mode... DONE \r\n");
        /* Begin watchdog trigger sequence */
        status = Pmic_wdgBeginSequences(coreHandle, pmicConfig.wdogMode);
        if(status == PMIC_ST_SUCCESS)
        {
            /* Exit Long Window by sending a trigger pulse */
            GPIO_pinWriteHigh(gGpioWdogTrigBaseAddr, GPIO_WDOG_TRIG_PIN);
            /* The trigger pulse width has to be ~10us greater than deglitch time */
            ClockP_usleep(CONFIG_PMIC0_TRIG_DEGLITCH_TIME_US + 10U);
            GPIO_pinWriteLow(gGpioWdogTrigBaseAddr, GPIO_WDOG_TRIG_PIN);

            /* This check is not required in the actual application. This is to detect
             * watchdog errors if any, when changing the sysconfig watchdog configuration
             * during development.
             */
            PMICApp_checkForWdgErrors(coreHandle);

            DebugP_log("Started watchdog sequence... Sending watchdog trigger signal to the PMIC... \r\n");
            /* Send watchdog trigger signal for some iterations */
            for (numSeqeunces = 40; numSeqeunces != 0; numSeqeunces--)
            {
                /* Wait until Window-1 time elapses and enter Window-2 to send watchdog trigger */
                ClockP_usleep(gPmicWdgCfg[CONFIG_PMIC0].win1Duration_us + \
                              (gPmicWdgCfg[CONFIG_PMIC0].win2Duration_us / 4));
                GPIO_pinWriteHigh(gGpioWdogTrigBaseAddr, GPIO_WDOG_TRIG_PIN);
                /* The trigger pulse width has to be ~10us greater than deglitch time */
                ClockP_usleep(CONFIG_PMIC0_TRIG_DEGLITCH_TIME_US + 10U);
                GPIO_pinWriteLow(gGpioWdogTrigBaseAddr, GPIO_WDOG_TRIG_PIN);

                /* This check is not required in the actual application. This is to detect
                 * watchdog errors, if any when changing the sysconfig watchdog configuration
                 * during development.
                 */
                PMICApp_checkForWdgErrors(coreHandle);
            }
        }
    }

    if(status == PMIC_ST_SUCCESS)
    {
        DebugP_log("Stopped sending watchdog trigger signal... Waiting for the warm reset to occur... \r\n");
        /* Warm reset trigger time depends on threshold value configured in the sysconfig. Waiting for
         * watchdog failure to exceed fail and reset threshold values for the warm reset to occur.
         */
        ClockP_usleep((gPmicWdgCfg[CONFIG_PMIC0].failThreshold + gPmicWdgCfg[CONFIG_PMIC0].rstThreshold + 1U) * \
                      (gPmicWdgCfg[CONFIG_PMIC0].win1Duration_us + \
                      gPmicWdgCfg[CONFIG_PMIC0].win2Duration_us + \
                      ClockP_ticksToUsec(1)));
        /* Warm reset should occur and program should not reach this point. */
        DebugP_log("Warm reset is not triggered.. Watchdog reset failed !! \r\n");
        /* Set return to long window */
        tmpWdgCfg.validParams = PMIC_CFG_WDG_RETLONGWIN_VALID_SHIFT;
        tmpWdgCfg.retLongWin = true;
        status = Pmic_wdgSetCfg(coreHandle, &tmpWdgCfg);
        if(status == PMIC_ST_SUCCESS)
        {
            /* Wait for current watchdog sequence to end and enter long window */
            ClockP_usleep(gPmicWdgCfg[CONFIG_PMIC0].win1Duration_us + \
                          gPmicWdgCfg[CONFIG_PMIC0].win2Duration_us + \
                          ClockP_ticksToUsec(1));
            /* Set the PWRHOLD, so watchdog remains in long window */
            tmpWdgCfg.validParams = PMIC_CFG_WDG_PWRHOLD_VALID_SHIFT;
            tmpWdgCfg.pwrHold = true;
            status = Pmic_wdgSetCfg(coreHandle, &tmpWdgCfg);
        }
    }

    DebugP_logError("PMIC trigger watchdog reset mode test... Failed !!\r\n");

    return retVal;
}

static void PMICApp_checkForWdgErrors(Pmic_CoreHandle_t *coreHandle)
{
    int32_t       status = PMIC_ST_SUCCESS;

    Pmic_WdgErrStatus_t wdgErrStat =
    {
        .validParams = (PMIC_CFG_WD_FAIL_INT_ERRSTAT_VALID_SHIFT | \
                        PMIC_CFG_WD_LONGWIN_TIMEOUT_ERRSTAT_VALID_SHIFT | \
                        PMIC_CFG_WD_TRIG_EARLY_ERRSTAT_VALID_SHIFT | \
                        PMIC_CFG_WD_RST_INT_ERRSTAT_VALID_SHIFT | \
                        PMIC_CFG_WD_TIMEOUT_ERRSTAT_VALID_SHIFT),
    };

    status = Pmic_wdgGetErrorStatus(coreHandle, &wdgErrStat);
    DebugP_assert(status == PMIC_ST_SUCCESS && \
                  !(wdgErrStat.wdLongWinTimeout || \
                  wdgErrStat.wdTimeout || \
                  wdgErrStat.wdTrigEarly || \
                  wdgErrStat.wdFailInt || \
                  wdgErrStat.wdRstInt));

    return;
}
