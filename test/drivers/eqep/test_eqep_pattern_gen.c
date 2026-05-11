/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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

/*
 *  This file contains eQEP waveform generation.
 *  This generated the eQEP signal by toggling the gpio signals.
 */

#include <drivers/gpio.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "ti_drivers_config.h"
#include "test_eqep_pattern_gen.h"
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/DebugP.h>
#if defined(SOC_AM62AX) || defined(SOC_AM62X)
#include <board/ioexp/ioexp_tca6424.h>
#endif

/* ========================================================================== */
/*                          Macros And Typedefs                               */
/* ========================================================================== */
#define EQEP_A_GPIO_PIN             (CONFIG_GPIO0_PIN)
#define EQEP_B_GPIO_PIN             (CONFIG_GPIO1_PIN)
#define EQEP_S_GPIO_PIN             (CONFIG_GPIO2_PIN)
#define EQEP_I_GPIO_PIN             (CONFIG_GPIO3_PIN)

#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62X)
/* GPIO pins for EQEP1 instance pattern generation */
#define EQEP1_A_GPIO_PIN            (CONFIG_GPIO4_PIN)
#define EQEP1_B_GPIO_PIN            (CONFIG_GPIO5_PIN)
#define EQEP1_I_GPIO_PIN            (CONFIG_GPIO6_PIN)
#endif /* SOC_AM62AX || SOC_AM62DX || SOC_AM62X */

#if defined(SOC_AM62AX) || defined(SOC_AM62X)
/* The IO Expander chip (U92) and specific pin (P25) for UART1_FET_SEL */
#define BOARD_I2C_ADDRESS_IO_EXPANDER      0x22U
#define BOARD_I2C_IO_EXPANDER_PIN_NUM      0x15U

static TCA6424_Config ioExpConfig;
#endif

void App_eqepGeneratePattern(EqepAppPatternParams *patParam)
{
    uint32_t clockDelayCnt;
    uint32_t i, j;
    uint32_t gGpioBaseAddr;

    gGpioBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO0_BASE_ADDR);
    /* Configure all GPIO pins as output for generating EQEP Signals. */
    GPIO_setDirMode(gGpioBaseAddr, EQEP_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_S_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* delay required for each quadrature of the EQEP signal in usec. */
    clockDelayCnt = (1000000 / patParam->eqepClockFreq) / 4;

    for (i = 0; i< patParam->idxEvtCnt; i++)
    {
        for (j =0; j< patParam->loopCnt; j++)
        {
            if (patParam->direction == EQEP_DIR_CLOCKWISE)
            {
                /* Configure all EQEP A and B lines to generate clockwise
                 * rotation. */
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);
            }
            else
            {
                /* Configure all EQEP A and B lines to generate anti clockwise
                 * rotation. */
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);
            }
        }
        if (patParam->generateIdxPulse == TRUE)
        {
            /* Generate the Index pulse by toggling EQEP I signal. */
            GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_I_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
            GPIO_pinWriteLow(gGpioBaseAddr, EQEP_I_GPIO_PIN);
        }
    }
}

void App_eqepGenerateClockDirPattern(EqepAppPatternParams *patParam)
{
    uint32_t clockDelayCnt;
    uint32_t i, j;
    uint32_t gGpioBaseAddr;
    uint32_t directionBit;

    gGpioBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO0_BASE_ADDR);
    /* Configure all GPIO pins as output for generating EQEP Signals. */
    GPIO_setDirMode(gGpioBaseAddr, EQEP_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_S_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* delay required for each clock pulse in usec. */
    clockDelayCnt = (1000000 / patParam->eqepClockFreq) / 2;

    directionBit = (patParam->direction == EQEP_DIR_CLOCKWISE) ? 1U : 0U;

    /* Initialize QEPA to LOW for consistent edge counting */
    GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);

    for (i = 0; i < patParam->idxEvtCnt; i++)
    {
        for (j = 0; j < patParam->loopCnt; j++)
        {
            /* Set direction bit (stays constant during all clock pulses) */
            if (directionBit == 1U)
            {
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
            }
            else
            {
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
            }

            /* Generate clock pulse on QEPA */
            GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);

            GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
        }
        if (patParam->generateIdxPulse == TRUE)
        {
            /* Generate the Index pulse by toggling EQEP I signal. */
            GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_I_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
            GPIO_pinWriteLow(gGpioBaseAddr, EQEP_I_GPIO_PIN);
        }
    }
}

void App_eqepGenerateUpCountPattern(EqepAppPatternParams *patParam)
{
    uint32_t clockDelayCnt;
    uint32_t i, j;
    uint32_t gGpioBaseAddr;
    uint32_t countControlBit;

    gGpioBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO0_BASE_ADDR);
    /* Configure all GPIO pins as output for generating EQEP Signals. */
    GPIO_setDirMode(gGpioBaseAddr, EQEP_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_S_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* delay required for each count pulse in usec. */
    clockDelayCnt = (1000000 / patParam->eqepClockFreq) / 2;

    countControlBit = (patParam->direction == EQEP_DIR_CLOCKWISE) ? 1U : 0U;

    /* Initialize QEPA to LOW for consistent edge counting */
    GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);

    for (i = 0; i < patParam->idxEvtCnt; i++)
    {
        for (j = 0; j < patParam->loopCnt; j++)
        {
            /* Set count control bit on QEPB (HIGH = count up, LOW = count down) */
            if (countControlBit == 1U)
            {
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
            }
            else
            {
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
            }

            /* Generate counting pulse on QEPA */
            GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);

            GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
        }
        if (patParam->generateIdxPulse == TRUE)
        {
            /* Generate the Index pulse by toggling EQEP I signal. */
            GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_I_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
            GPIO_pinWriteLow(gGpioBaseAddr, EQEP_I_GPIO_PIN);
        }
    }
}

void App_eqepGenerateStrobePattern(EqepAppPatternParams *patParam)
{
    uint32_t clockDelayCnt;
    uint32_t i, j;
    uint32_t gGpioBaseAddr;

    gGpioBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO0_BASE_ADDR);
    /* Configure all GPIO pins as output for generating EQEP Signals. */
    GPIO_setDirMode(gGpioBaseAddr, EQEP_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_S_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* delay required for each quadrature of the EQEP signal in usec. */
    clockDelayCnt = (1000000 / patParam->eqepClockFreq) / 4;

    /* Initialize STROBE to LOW */
    GPIO_pinWriteLow(gGpioBaseAddr, EQEP_S_GPIO_PIN);

    for (i = 0; i < patParam->idxEvtCnt; i++)
    {
        for (j = 0; j < patParam->loopCnt; j++)
        {
            if (patParam->direction == EQEP_DIR_CLOCKWISE)
            {
                /* Generate clockwise quadrature pattern */
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);
            }
            else
            {
                /* Generate counter-clockwise quadrature pattern */
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);
            }
        }

        /* Generate STROBE pulse after quadrature pattern */
        GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_S_GPIO_PIN);
        ClockP_usleep(clockDelayCnt);
        GPIO_pinWriteLow(gGpioBaseAddr, EQEP_S_GPIO_PIN);

        if (patParam->generateIdxPulse == TRUE)
        {
            /* Generate the Index pulse by toggling EQEP I signal. */
            GPIO_pinWriteHigh(gGpioBaseAddr, EQEP_I_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
            GPIO_pinWriteLow(gGpioBaseAddr, EQEP_I_GPIO_PIN);
        }
    }
}

#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62X)
void App_eqepGeneratePatternEqep1(EqepAppPatternParams *patParam)
{
    uint32_t clockDelayCnt;
    uint32_t i, j;
    uint32_t gGpioBaseAddr;

    gGpioBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO4_BASE_ADDR);
    /* Configure GPIO pins as output for generating EQEP1 Signals. */
    GPIO_setDirMode(gGpioBaseAddr, EQEP1_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP1_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gGpioBaseAddr, EQEP1_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* delay required for each quadrature of the EQEP signal in usec. */
    clockDelayCnt = (1000000 / patParam->eqepClockFreq) / 4;

    for (i = 0; i< patParam->idxEvtCnt; i++)
    {
        for (j =0; j< patParam->loopCnt; j++)
        {
            if (patParam->direction == EQEP_DIR_CLOCKWISE)
            {
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteLow(gGpioBaseAddr, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);
            }
            else
            {
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteHigh(gGpioBaseAddr, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                GPIO_pinWriteLow(gGpioBaseAddr, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteLow(gGpioBaseAddr, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);
            }
        }
        if (patParam->generateIdxPulse == TRUE)
        {
            GPIO_pinWriteHigh(gGpioBaseAddr, EQEP1_I_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
            GPIO_pinWriteLow(gGpioBaseAddr, EQEP1_I_GPIO_PIN);
        }
    }
}

void App_eqepGenerateDualPattern(EqepAppPatternParams *patParam)
{
    uint32_t clockDelayCnt;
    uint32_t i, j;
    uint32_t gpioBaseAddr0, gpioBaseAddr1;

    gpioBaseAddr0 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO0_BASE_ADDR);
    gpioBaseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO4_BASE_ADDR);

    /* Configure GPIO pins for EQEP0 */
    GPIO_setDirMode(gpioBaseAddr0, EQEP_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr0, EQEP_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr0, EQEP_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* Configure GPIO pins for EQEP1 */
    GPIO_setDirMode(gpioBaseAddr1, EQEP1_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr1, EQEP1_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr1, EQEP1_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* delay required for each quadrature of the EQEP signal in usec. */
    clockDelayCnt = (1000000 / patParam->eqepClockFreq) / 4;

    for (i = 0; i < patParam->idxEvtCnt; i++)
    {
        for (j = 0; j < patParam->loopCnt; j++)
        {
            if (patParam->direction == EQEP_DIR_CLOCKWISE)
            {
                /* Phase 1: A=0, B=1 */
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                /* Phase 2: A=0, B=0 */
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                /* Phase 3: A=1, B=0 */
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                /* Phase 4: A=1, B=1 */
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);
            }
            else
            {
                /* Phase 1: A=0, B=1 */
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                /* Phase 2: A=1, B=1 */
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                /* Phase 3: A=1, B=0 */
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);

                /* Phase 4: A=0, B=0 */
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                ClockP_usleep(clockDelayCnt);
            }
        }
        if (patParam->generateIdxPulse == TRUE)
        {
            GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_I_GPIO_PIN);
            GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_I_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
            GPIO_pinWriteLow(gpioBaseAddr0, EQEP_I_GPIO_PIN);
            GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_I_GPIO_PIN);
        }
    }
}

void App_eqepGenerateDualClockDirPattern(EqepAppPatternParams *patParam)
{
    uint32_t clockDelayCnt;
    uint32_t i, j;
    uint32_t gpioBaseAddr0, gpioBaseAddr1;
    uint32_t directionBit;

    gpioBaseAddr0 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO0_BASE_ADDR);
    gpioBaseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO4_BASE_ADDR);

    /* Configure GPIO pins for EQEP0 */
    GPIO_setDirMode(gpioBaseAddr0, EQEP_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr0, EQEP_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr0, EQEP_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* Configure GPIO pins for EQEP1 */
    GPIO_setDirMode(gpioBaseAddr1, EQEP1_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr1, EQEP1_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr1, EQEP1_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* delay required for each clock pulse in usec. */
    clockDelayCnt = (1000000 / patParam->eqepClockFreq) / 2;

    directionBit = (patParam->direction == EQEP_DIR_CLOCKWISE) ? 1U : 0U;

    /* Initialize clock lines to LOW */
    GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
    GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);

    for (i = 0; i < patParam->idxEvtCnt; i++)
    {
        for (j = 0; j < patParam->loopCnt; j++)
        {
            /* Set direction bit on both instances */
            if (directionBit == 1U)
            {
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
            }
            else
            {
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
            }

            /* Generate clock pulse on both QEPA lines */
            GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
            GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);

            GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_A_GPIO_PIN);
            GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
        }
        if (patParam->generateIdxPulse == TRUE)
        {
            GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_I_GPIO_PIN);
            GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_I_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
            GPIO_pinWriteLow(gpioBaseAddr0, EQEP_I_GPIO_PIN);
            GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_I_GPIO_PIN);
        }
    }
}

void App_eqepGenerateDualQMAErrorPattern(EqepAppPatternParams *patParam,
                                         uint32_t glitchInterval)
{
    uint32_t clockDelayCnt;
    uint32_t i, j;
    uint32_t gpioBaseAddr0, gpioBaseAddr1;
    uint32_t directionBit;
    uint32_t glitchDelayCnt;

    gpioBaseAddr0 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO0_BASE_ADDR);
    gpioBaseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO4_BASE_ADDR);

    /* Configure GPIO pins for EQEP0 */
    GPIO_setDirMode(gpioBaseAddr0, EQEP_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr0, EQEP_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr0, EQEP_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* Configure GPIO pins for EQEP1 */
    GPIO_setDirMode(gpioBaseAddr1, EQEP1_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr1, EQEP1_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_setDirMode(gpioBaseAddr1, EQEP1_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    /* delay required for each clock pulse in usec. */
    clockDelayCnt = (1000000 / patParam->eqepClockFreq) / 2;
    /* Short glitch pulse width — much shorter than normal clock period */
    glitchDelayCnt = clockDelayCnt / 8;
    if (glitchDelayCnt == 0U)
    {
        glitchDelayCnt = 1U;
    }

    directionBit = (patParam->direction == EQEP_DIR_CLOCKWISE) ? 1U : 0U;

    /* Initialize clock lines to LOW on both instances */
    GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
    GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);

    for (i = 0; i < patParam->idxEvtCnt; i++)
    {
        for (j = 0; j < patParam->loopCnt; j++)
        {
            /* Set direction bit on both instances */
            if (directionBit == 1U)
            {
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
            }
            else
            {
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
            }

            /* Normal clock pulse on both instances */
            GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
            GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);

            GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_A_GPIO_PIN);
            GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);

            /*
             * Inject glitches on BOTH instances every glitchInterval cycles.
             * This creates erroneous transitions that:
             *  - QMA Mode 1 (EQEP0) should correct (filter out)
             *  - QMA Mode 2 (EQEP1) should detect and flag as QMA error
             *
             * Glitch sequence:
             *  1. Rapid spurious clock toggling on both instances
             *  2. Brief direction reversal + clock edge on both instances
             *     (creates illegal state transition in clock-dir mode)
             *  3. Restore correct direction on both instances
             */
            if ((glitchInterval > 0U) && ((j % glitchInterval) == 0U))
            {
                /* Glitch 1: Rapid clock toggling (spurious edges) on both */
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                ClockP_usleep(glitchDelayCnt);
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                ClockP_usleep(glitchDelayCnt);
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                ClockP_usleep(glitchDelayCnt);
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                ClockP_usleep(glitchDelayCnt);

                /* Glitch 2: Brief direction reversal on both instances */
                if (directionBit == 1U)
                {
                    GPIO_pinWriteLow(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                    GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                }
                else
                {
                    GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                    GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                }
                ClockP_usleep(glitchDelayCnt);

                /* Generate a clock edge during wrong direction on both */
                GPIO_pinWriteLow(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                ClockP_usleep(glitchDelayCnt);
                GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_A_GPIO_PIN);
                GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_A_GPIO_PIN);
                ClockP_usleep(glitchDelayCnt);

                /* Restore correct direction on both instances */
                if (directionBit == 1U)
                {
                    GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                    GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                }
                else
                {
                    GPIO_pinWriteLow(gpioBaseAddr0, EQEP_B_GPIO_PIN);
                    GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_B_GPIO_PIN);
                }
                ClockP_usleep(glitchDelayCnt);
            }
        }
        if (patParam->generateIdxPulse == TRUE)
        {
            GPIO_pinWriteHigh(gpioBaseAddr0, EQEP_I_GPIO_PIN);
            GPIO_pinWriteHigh(gpioBaseAddr1, EQEP1_I_GPIO_PIN);
            ClockP_usleep(clockDelayCnt);
            GPIO_pinWriteLow(gpioBaseAddr0, EQEP_I_GPIO_PIN);
            GPIO_pinWriteLow(gpioBaseAddr1, EQEP1_I_GPIO_PIN);
        }
    }
}
#endif /* SOC_AM62AX || SOC_AM62DX || SOC_AM62X */

void App_eqepReadPinValue(uint32_t *pEqepAPin,
                          uint32_t *pEqepBPin,
                          uint32_t *pEqepIPin,
                          uint32_t *pEqepSPin)
{
    uint32_t gGpioBaseAddr;

     gGpioBaseAddr = (uint32_t)AddrTranslateP_getLocalAddr(CONFIG_GPIO0_BASE_ADDR);

     /* Configure all GPIO pins as output for generating EQEP Signals. */
     GPIO_setDirMode(gGpioBaseAddr, EQEP_A_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
     GPIO_setDirMode(gGpioBaseAddr, EQEP_B_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
     GPIO_setDirMode(gGpioBaseAddr, EQEP_S_GPIO_PIN, GPIO_DIRECTION_OUTPUT);
     GPIO_setDirMode(gGpioBaseAddr, EQEP_I_GPIO_PIN, GPIO_DIRECTION_OUTPUT);

    *pEqepAPin = GPIO_pinOutValueRead(gGpioBaseAddr, EQEP_A_GPIO_PIN);
    *pEqepBPin = GPIO_pinOutValueRead(gGpioBaseAddr, EQEP_B_GPIO_PIN);
    *pEqepIPin = GPIO_pinOutValueRead(gGpioBaseAddr, EQEP_I_GPIO_PIN);
    *pEqepSPin = GPIO_pinOutValueRead(gGpioBaseAddr, EQEP_S_GPIO_PIN);
}

#if defined(SOC_AM62AX) || defined(SOC_AM62X)
void Board_userExpansionHeaderEnable(void)
{
    TCA6424_Params  tca6424Params;
    int32_t status = SystemP_SUCCESS;

    TCA6424_Params_init(&tca6424Params);
    tca6424Params.i2cInstance = CONFIG_I2C0;
    tca6424Params.i2cAddress  = BOARD_I2C_ADDRESS_IO_EXPANDER;

    status = TCA6424_open(&ioExpConfig, &tca6424Params);

    if(status == SystemP_SUCCESS)
    {
        /* Configure Pin P25 as an output */
        status += TCA6424_config(&ioExpConfig,
                                 BOARD_I2C_IO_EXPANDER_PIN_NUM,
                                 TCA6424_MODE_OUTPUT);

        /* Drive Pin P25 LOW to select B1 (Expansion Connector) */
        status += TCA6424_setOutput(&ioExpConfig,
                                    BOARD_I2C_IO_EXPANDER_PIN_NUM,
                                    TCA6424_OUT_STATE_LOW);
    }

    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("Expansion header routing FAILED!\r\n");
    }
    else
    {
        DebugP_log("U95 Switch flipped\r\n");
    }
}
#endif
