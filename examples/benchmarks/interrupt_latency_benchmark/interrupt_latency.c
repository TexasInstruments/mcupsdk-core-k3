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

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

#include <kernel/dpl/CycleCounterP.h>
#include <kernel/dpl/TimerP.h>
#include <drivers/gpio.h>
#include <drivers/epwm.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Output channel - A or B */
#define APP_EPWM_OUTPUT_CH              (EPWM_OUTPUT_CH_A)
/* Duty Cycle of PWM output signal in % - give value from 0 to 100 */
#define APP_EPWM_DUTY_CYCLE             (50U)
/* Frequency of PWM output signal in Hz - 1 KHz is selected */
#define APP_EPWM_OUTPUT_FREQ            (1U * 1000U)
/* APP run time in seconds */
#define APP_EPWM_RUN_TIME               (60U)

/* TB frequency in Hz - so that /4 divider is used */
#define APP_EPWM_TB_FREQ                (CONFIG_EPWM0_FCLK / 4U)
/*
 *  PRD value - this determines the period
 *  PRD = (TBCLK/PWM FREQ) / 2
 *  /2 is added becasue up&down counter is selected. So period is 2 times
 */
#define APP_EPWM_PRD_VAL                ((APP_EPWM_TB_FREQ / APP_EPWM_OUTPUT_FREQ) / 2U)
/*
 *  COMPA value - this determines the duty cycle
 *  COMPA = (PRD - ((dutycycle * PRD) / 100)
 */
#define APP_EPWM_COMPA_VAL              (APP_EPWM_PRD_VAL - ((APP_EPWM_DUTY_CYCLE * \
                                            APP_EPWM_PRD_VAL) / 100U))

#ifndef SOC_AM62LX
#define TIMER_BASE_ADDR     (CSL_TIMER6_CFG_BASE)
#else
#define TIMER_BASE_ADDR     (CSL_TIMER0_CFG_BASE)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                   Internal Function Declarations                           */
/* ========================================================================== */

static void App_epwmIntrISR(void *handle);
static void App_epwmConfig(uint32_t epwmBaseAddr,
                           uint32_t epwmCh,
                           uint32_t epwmFuncClk);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* variable to hold base address of EPWM that is used */
uint32_t gEpwmBaseAddr;

/* Global variables and objects */
static HwiP_Object       gEpwmHwiObject;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void interrupt_latency_main(void *args)
{
    int32_t             status;
    HwiP_Params         hwiPrms;

    /* Address translate */
    gEpwmBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_EPWM0_BASE_ADDR);

    DebugP_log("Interrupt latency benchmark example started...\r\n");

    /* Register & enable interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = CONFIG_EPWM0_INTR;
    hwiPrms.eventId     = CONFIG_EPWM0_EVENT_ID;
    hwiPrms.callback    = &App_epwmIntrISR;
    hwiPrms.isPulse     = CONFIG_EPWM0_INTR_IS_PULSE;
    status              = HwiP_construct(&gEpwmHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

#ifdef SOC_AM62LX
    /* Connfigure the GPIO Expander Mux */
    GPIO_pinWriteHigh(CONFIG_GPIO_MUX_BASE_ADDR, CONFIG_GPIO_MUX_PIN);
#endif

    /* Configure PWM */
    App_epwmConfig(gEpwmBaseAddr, APP_EPWM_OUTPUT_CH, CONFIG_EPWM0_FCLK);

    DebugP_log("\r\nPlease observe pin (GPIO %d) ", CONFIG_GPIO0_PIN);
    DebugP_log("\r\n   If toggling         -> Background loop running");
    DebugP_log("\r\n   If gap/no toggling  -> Background loop interrupted. Interrupt routine running");
    DebugP_log("\r\nWaiting for few seconds... ");

    /* Blocking the timer interrupt*/
    TimerP_stop(TIMER_BASE_ADDR);

    /* Toggle the Gpio continuously */
    for(uint32_t i= 0; i < 200000000; i++)
    {
        GPIO_pinWriteHigh(CONFIG_GPIO0_BASE_ADDR, CONFIG_GPIO0_PIN);
        GPIO_pinWriteLow(CONFIG_GPIO0_BASE_ADDR, CONFIG_GPIO0_PIN);
    }

    TimerP_start(TIMER_BASE_ADDR);

    DebugP_log("Done.\n\r");
    DebugP_log("Interrupt latency benchmark example completed...\r\n");
    EPWM_etIntrDisable(gEpwmBaseAddr);
    EPWM_etIntrClear(gEpwmBaseAddr);     /* Clear any pending interrupts if any */
    HwiP_destruct(&gEpwmHwiObject);

}

static void App_epwmIntrISR(void *handle)
{
    HW_WR_FIELD16((gEpwmBaseAddr + PWMSS_EPWM_ETCLR),
        PWMSS_EPWM_ETCLR_INT, (uint16_t)PWMSS_EPWM_ETCLR_INT_CLEAR);
}

static void App_epwmConfig(uint32_t epwmBaseAddr,
                           uint32_t epwmCh,
                           uint32_t epwmFuncClk)
{

    /* Configure Time base submodule */
    EPWM_tbTimebaseClkCfg(epwmBaseAddr, APP_EPWM_TB_FREQ, epwmFuncClk);
    EPWM_tbPwmFreqCfg(epwmBaseAddr, APP_EPWM_TB_FREQ, APP_EPWM_OUTPUT_FREQ,
        EPWM_TB_COUNTER_DIR_UP_DOWN,
            EPWM_SHADOW_REG_CTRL_ENABLE);


    /* Configure counter compare submodule */
    EPWM_counterComparatorCfg(epwmBaseAddr, EPWM_CC_CMP_A,
        APP_EPWM_COMPA_VAL, EPWM_SHADOW_REG_CTRL_ENABLE,
            EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);

    /* Configure event trigger Submodule */
    EPWM_etIntrCfg(epwmBaseAddr, EPWM_ET_INTR_EVT_CNT_EQ_ZRO,
        EPWM_ET_INTR_PERIOD_FIRST_EVT);
    EPWM_etIntrEnable(epwmBaseAddr);
}
