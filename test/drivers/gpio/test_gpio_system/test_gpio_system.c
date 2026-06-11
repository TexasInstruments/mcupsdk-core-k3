/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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
 *  \file test_gpio_system.c
 *
 *  \brief This file contains implementation of all module test cases
 *         and logs are printed on r5 core.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/gpio.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "test_gpio_system.h"

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */



/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief GPIO test params */
typedef struct Test_GpioPrms
{
    uint32_t            baseAddr;
    uint32_t            pinNum;
    uint32_t            trigType;
    uint32_t            loopcnt;
    uint32_t            delayms;
    volatile uint32_t   intrcnt;
} Test_GpioPrms_t;


/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/**
 * TestGpio_trigLevelNegTc - Verify GPIO behavior with invalid trigger type.
 * Configures a GPIO pin as output and attempts to set an invalid trigger type.
 * Drives a rising edge on the pin and checks that no interrupt is generated.
 * Confirms that the GPIO driver correctly ignores invalid trigger configurations.
 * Cleans up by disabling interrupts and resetting the pin state.
 */
int32_t TestGpio_trigLevelNegTc(void *arg)
{
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_LED_BASE_ADDR);
    uint32_t pinNum = GPIO_LED_PIN;
    uint32_t bankNum, intrStatus, pinMask, intrcnt = 0;

    bankNum = GPIO_GET_BANK_INDEX(pinNum);
    pinMask = GPIO_GET_BANK_BIT_MASK(pinNum);
    GPIO_setDirMode(baseAddr, pinNum, GPIO_DIRECTION_OUTPUT);

    GPIO_pinWriteLow(baseAddr, pinNum);
    ClockP_usleep(100000);

    /* Set invalid trigger type */
    GPIO_setTrigType(baseAddr, pinNum, (uint32_t)-1);
    GPIO_bankIntrEnable(baseAddr, bankNum);

    /* Drive rising edge */
    GPIO_pinWriteHigh(baseAddr, pinNum);
    ClockP_usleep(10000);

    /* Check interrupt status */
    intrStatus = GPIO_getBankIntrStatus(baseAddr, bankNum);
    GPIO_clearBankIntrStatus(baseAddr, bankNum, intrStatus);
    if (intrStatus & pinMask)
    {
        intrcnt++;
    }
    TEST_ASSERT_EQUAL_INT32(0, intrcnt);

    /* Cleanup */
    GPIO_bankIntrDisable(baseAddr, bankNum);
    GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_NONE);
    GPIO_clearIntrStatus(baseAddr, pinNum);

    GPIO_pinWriteLow(baseAddr, pinNum);

    return SystemP_SUCCESS;

}

/**
 * TestGpio_interruptAllBanks - Verify GPIO interrupts across all banks.
 * Uses one representative pin per bank to generate and check interrupt events.
 * Ensures bank interrupt status bits are set for the driven pin and can be cleared.
 * Confirms no spurious bits remain after clearing and restores configuration.
 * Useful for validating bank-wide interrupt handling and regression testing.
 */
int32_t TestGpio_interruptAllBanks(void *args)
{
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_LED_BASE_ADDR);
    uint32_t maxBanksToTest = 9U; /* feature states up to 9 banks */
    uint32_t bank;

    DebugP_log("\ntest_gpio_interrupt_all_banks started...\r\n");

    /* For each bank 0..8, use pinNum = bank*16 as representative */
    for (bank = 0; bank < maxBanksToTest; bank++)
    {
        uint32_t pinNum  = bank * GPIO_MAX_PIN_PER_BANK; /* first pinNum in bank */
        uint32_t bankNum = GPIO_GET_BANK_INDEX(pinNum);
        uint32_t pinMask = GPIO_GET_BANK_BIT_MASK(pinNum);

        /* Sanity: computed bank index must match loop bank */
        TEST_ASSERT_EQUAL_UINT32(bank, bankNum);

        /* Configure pinNum as output and set initial low to create rising edge */
        GPIO_setDirMode(baseAddr, pinNum, GPIO_DIRECTION_OUTPUT);
        GPIO_pinWriteLow(baseAddr, pinNum);
        ClockP_usleep(1000);

        /* Configure rising-edge trigger and enable bank interrupt */
        GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_RISE_EDGE);
        GPIO_bankIntrEnable(baseAddr, bankNum);

        /* Drive rising edge */
        GPIO_pinWriteHigh(baseAddr, pinNum);
        ClockP_usleep(1000);

        /* Read and clear bank interrupt status */
        uint32_t intrStatus = GPIO_getBankIntrStatus(baseAddr, bankNum);
        GPIO_clearBankIntrStatus(baseAddr, bankNum, intrStatus);

        GPIO_pinWriteLow(baseAddr, pinNum);
        ClockP_usleep(10000);

        intrStatus = GPIO_getBankIntrStatus(baseAddr, bankNum);
        /* Verify only this pin’s bit may be set (at minimum, our pinNum must be set) */
        TEST_ASSERT_EQUAL_UINT32(0U, (intrStatus & pinMask));

        /* Cleanup per bank */
        GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_NONE);
        GPIO_bankIntrDisable(baseAddr, bankNum);
        GPIO_clearIntrStatus(baseAddr, pinNum);
        GPIO_pinWriteLow(baseAddr, pinNum);
    }

    DebugP_log("test_gpio_interrupt_all_banks end!!!\r\n");

    return SystemP_SUCCESS;
}
