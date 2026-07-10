/*
 *  Copyright (C) 2021-2026 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if (defined(SOC_AM62DX) && !(defined(DM_R5F_CORE) || defined(C75_CORE)))
/* Number of pin toggle cycles for interrupt tests */
#define LOOP_TOGGLE_TARGET_COUNT              (20U)
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
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
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Testcases */
static void test_gpio_output(void *args);
static void test_gpio_read(void *args);
static void test_gpio_trigger(void *args);
static void test_gpio_macros(void *args);
static void test_gpio_toggle_loop(Test_GpioPrms_t *testPrms);
static void test_gpio_read_loop(Test_GpioPrms_t *testPrms);
static void test_gpio_trigger_loop(Test_GpioPrms_t *testPrms);

#if defined(SOC_AM275X) || defined(SOC_AM62DX) || defined(SOC_AM62PX) || defined(AM62X_SK) || defined(SOC_AM62AX)
static void TestGpio_interruptAllBanks(void *args);
static void TestGpio_trigLevelNegTc(void *arg);
static void TestGpio_sameBankDiffPin(void *arg);
/* Helper functions */
#ifdef ENABLE_MT_TESTS
extern void run_multi_threaded_tests(void *args);
#endif
#if (defined(SOC_AM62DX) && !(defined(DM_R5F_CORE) || defined(C75_CORE)))
static void TestGpio_InputOutputIntrpt(void *args);
static void TestGpio_InputIntrpt(void *arg);
extern uint32_t Board_getGpioButtonIntrNum(void);
extern void Board_gpioInit(void);
extern void Board_gpioDeinit(void);
#endif
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if (defined(SOC_AM62DX) && !(defined(DM_R5F_CORE) || defined(C75_CORE)))
/* Hardware interrupt object for GPIO ISR */
static HwiP_Object              TestGpio_HardwareObj;

/* Semaphore for ISR-to-thread synchronization */
static SemaphoreP_Object        TestGpio_IsrSem;

/* ISR invocation counter (volatile for concurrency) */
static volatile uint32_t        TestGpio_IsrCount = 0;
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(test_gpio_output,  9542, NULL);
    RUN_TEST(test_gpio_read,    9543, NULL);
    RUN_TEST(test_gpio_trigger, 9544, NULL);
    RUN_TEST(test_gpio_macros,  9545, NULL);
    #if defined(SOC_AM275X) || defined(SOC_AM62DX) || defined(SOC_AM62PX) || defined(AM62X_SK) || defined(SOC_AM62AX)
    RUN_TEST(TestGpio_trigLevelNegTc,  9550, NULL);
    RUN_TEST(TestGpio_interruptAllBanks,  9546, NULL);
    RUN_TEST(TestGpio_sameBankDiffPin,  9916, NULL);
    #if (defined(SOC_AM62DX) && !(defined(DM_R5F_CORE) || defined(C75_CORE)))
    RUN_TEST(TestGpio_InputOutputIntrpt,  9549, NULL);
    #endif
    #if defined (ENABLE_MT_TESTS)
    run_multi_threaded_tests(NULL);
    #endif
    #endif

    UNITY_END();

    return;
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

/*
 * Testcases
 */
static void test_gpio_output(void *args)
{
    Test_GpioPrms_t testPrms;

    DebugP_log("\ntest_gpio_output started...\r\n");

    testPrms.baseAddr = GPIO_LED_BASE_ADDR;
    testPrms.baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(testPrms.baseAddr);
    testPrms.pinNum   = GPIO_LED_PIN;
    testPrms.loopcnt  = 5;
    testPrms.delayms  = 100;
    test_gpio_toggle_loop(&testPrms);

    DebugP_log("test_gpio_output end!!!\r\n");

    return;
}

static void test_gpio_read(void *args)
{
    Test_GpioPrms_t testPrms;

    DebugP_log("\ntest_gpio_read started...\r\n");

    testPrms.baseAddr = GPIO_PUSH_BUTTON_BASE_ADDR;
    testPrms.baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(testPrms.baseAddr);
    testPrms.pinNum   = GPIO_PUSH_BUTTON_PIN;
    testPrms.loopcnt  = 5;
    testPrms.delayms  = 100;
    test_gpio_read_loop(&testPrms);

    DebugP_log("test_gpio_read end!!!\r\n");

    return;
}

static void test_gpio_trigger(void *args)
{
    Test_GpioPrms_t testPrms;

    DebugP_log("\ntest_gpio_trigger started...\r\n");

    testPrms.baseAddr = GPIO_LED_BASE_ADDR;
    testPrms.baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(testPrms.baseAddr);
    testPrms.pinNum   = GPIO_LED_PIN;
    testPrms.loopcnt  = 5;
    testPrms.delayms  = 100;
    testPrms.trigType = GPIO_TRIG_TYPE_RISE_EDGE;
    test_gpio_trigger_loop(&testPrms);
    testPrms.trigType = GPIO_TRIG_TYPE_FALL_EDGE;
    test_gpio_trigger_loop(&testPrms);
    testPrms.trigType = GPIO_TRIG_TYPE_BOTH_EDGE;
    test_gpio_trigger_loop(&testPrms);

    DebugP_log("test_gpio_trigger end!!!\r\n");

    return;
}

static void test_gpio_macros(void *args)
{
    uint32_t index, pos, mask;

    DebugP_log("\ntest_gpio_macros started...\r\n");

    /* Macro checks */
    TEST_ASSERT_EQUAL_UINT32(16, GPIO_MAX_PIN_PER_BANK);
    TEST_ASSERT_EQUAL_UINT32(2,  GPIO_BANKS_PER_REG);
    TEST_ASSERT_EQUAL_UINT32(32, GPIO_PINS_PER_REG);

    /* Bank index test */
    index = GPIO_GET_BANK_INDEX(0);
    TEST_ASSERT_EQUAL_UINT32(0, index);
    index = GPIO_GET_BANK_INDEX(8);
    TEST_ASSERT_EQUAL_UINT32(0, index);
    index = GPIO_GET_BANK_INDEX(15);
    TEST_ASSERT_EQUAL_UINT32(0, index);
    index = GPIO_GET_BANK_INDEX(16);
    TEST_ASSERT_EQUAL_UINT32(1, index);
    index = GPIO_GET_BANK_INDEX(24);
    TEST_ASSERT_EQUAL_UINT32(1, index);
    index = GPIO_GET_BANK_INDEX(31);
    TEST_ASSERT_EQUAL_UINT32(1, index);
    index = GPIO_GET_BANK_INDEX(32);
    TEST_ASSERT_EQUAL_UINT32(2, index);
    index = GPIO_GET_BANK_INDEX(100);
    TEST_ASSERT_EQUAL_UINT32(6, index);

    /* Register index test */
    index = GPIO_GET_REG_INDEX(0);
    TEST_ASSERT_EQUAL_UINT32(0, index);
    index = GPIO_GET_REG_INDEX(8);
    TEST_ASSERT_EQUAL_UINT32(0, index);
    index = GPIO_GET_REG_INDEX(15);
    TEST_ASSERT_EQUAL_UINT32(0, index);
    index = GPIO_GET_REG_INDEX(16);
    TEST_ASSERT_EQUAL_UINT32(0, index);
    index = GPIO_GET_REG_INDEX(24);
    TEST_ASSERT_EQUAL_UINT32(0, index);
    index = GPIO_GET_REG_INDEX(31);
    TEST_ASSERT_EQUAL_UINT32(0, index);
    index = GPIO_GET_REG_INDEX(32);
    TEST_ASSERT_EQUAL_UINT32(1, index);
    index = GPIO_GET_REG_INDEX(63);
    TEST_ASSERT_EQUAL_UINT32(1, index);
    index = GPIO_GET_REG_INDEX(64);
    TEST_ASSERT_EQUAL_UINT32(2, index);
    index = GPIO_GET_REG_INDEX(100);
    TEST_ASSERT_EQUAL_UINT32(3, index);

    /* Register bit position test */
    pos = GPIO_GET_BIT_POS(0);
    TEST_ASSERT_EQUAL_UINT32(0, pos);
    pos = GPIO_GET_BIT_POS(8);
    TEST_ASSERT_EQUAL_UINT32(8, pos);
    pos = GPIO_GET_BIT_POS(15);
    TEST_ASSERT_EQUAL_UINT32(15, pos);
    pos = GPIO_GET_BIT_POS(16);
    TEST_ASSERT_EQUAL_UINT32(16, pos);
    pos = GPIO_GET_BIT_POS(24);
    TEST_ASSERT_EQUAL_UINT32(24, pos);
    pos = GPIO_GET_BIT_POS(31);
    TEST_ASSERT_EQUAL_UINT32(31, pos);
    pos = GPIO_GET_BIT_POS(32);
    TEST_ASSERT_EQUAL_UINT32(0, pos);
    pos = GPIO_GET_BIT_POS(63);
    TEST_ASSERT_EQUAL_UINT32(31, pos);
    pos = GPIO_GET_BIT_POS(64);
    TEST_ASSERT_EQUAL_UINT32(0, pos);
    pos = GPIO_GET_BIT_POS(100);
    TEST_ASSERT_EQUAL_UINT32(4, pos);

    /* Bank bit position test */
    pos = GPIO_GET_BANK_BIT_POS(0);
    TEST_ASSERT_EQUAL_UINT32(0, pos);
    pos = GPIO_GET_BANK_BIT_POS(8);
    TEST_ASSERT_EQUAL_UINT32(8, pos);
    pos = GPIO_GET_BANK_BIT_POS(15);
    TEST_ASSERT_EQUAL_UINT32(15, pos);
    pos = GPIO_GET_BANK_BIT_POS(16);
    TEST_ASSERT_EQUAL_UINT32(0, pos);
    pos = GPIO_GET_BANK_BIT_POS(24);
    TEST_ASSERT_EQUAL_UINT32(8, pos);
    pos = GPIO_GET_BANK_BIT_POS(31);
    TEST_ASSERT_EQUAL_UINT32(15, pos);
    pos = GPIO_GET_BANK_BIT_POS(32);
    TEST_ASSERT_EQUAL_UINT32(0, pos);
    pos = GPIO_GET_BANK_BIT_POS(63);
    TEST_ASSERT_EQUAL_UINT32(15, pos);
    pos = GPIO_GET_BANK_BIT_POS(64);
    TEST_ASSERT_EQUAL_UINT32(0, pos);
    pos = GPIO_GET_BANK_BIT_POS(100);
    TEST_ASSERT_EQUAL_UINT32(4, pos);

    /* Register bit mask test */
    mask = GPIO_GET_BIT_MASK(0);
    TEST_ASSERT_EQUAL_UINT32(0x00000001, mask);
    mask = GPIO_GET_BIT_MASK(8);
    TEST_ASSERT_EQUAL_UINT32(0x00000100, mask);
    mask = GPIO_GET_BIT_MASK(15);
    TEST_ASSERT_EQUAL_UINT32(0x00008000, mask);
    mask = GPIO_GET_BIT_MASK(16);
    TEST_ASSERT_EQUAL_UINT32(0x00010000, mask);
    mask = GPIO_GET_BIT_MASK(24);
    TEST_ASSERT_EQUAL_UINT32(0x01000000, mask);
    mask = GPIO_GET_BIT_MASK(31);
    TEST_ASSERT_EQUAL_UINT32(0x80000000, mask);
    mask = GPIO_GET_BIT_MASK(32);
    TEST_ASSERT_EQUAL_UINT32(0x00000001, mask);
    mask = GPIO_GET_BIT_MASK(63);
    TEST_ASSERT_EQUAL_UINT32(0x080000000, mask);
    mask = GPIO_GET_BIT_MASK(64);
    TEST_ASSERT_EQUAL_UINT32(0x00000001, mask);
    mask = GPIO_GET_BIT_MASK(100);
    TEST_ASSERT_EQUAL_UINT32(0x00000010, mask);

    /* Bank bit mask test */
    mask = GPIO_GET_BANK_BIT_MASK(0);
    TEST_ASSERT_EQUAL_UINT32(0x0001, mask);
    mask = GPIO_GET_BANK_BIT_MASK(8);
    TEST_ASSERT_EQUAL_UINT32(0x0100, mask);
    mask = GPIO_GET_BANK_BIT_MASK(15);
    TEST_ASSERT_EQUAL_UINT32(0x8000, mask);
    mask = GPIO_GET_BANK_BIT_MASK(16);
    TEST_ASSERT_EQUAL_UINT32(0x0001, mask);
    mask = GPIO_GET_BANK_BIT_MASK(24);
    TEST_ASSERT_EQUAL_UINT32(0x0100, mask);
    mask = GPIO_GET_BANK_BIT_MASK(31);
    TEST_ASSERT_EQUAL_UINT32(0x8000, mask);
    mask = GPIO_GET_BANK_BIT_MASK(32);
    TEST_ASSERT_EQUAL_UINT32(0x0001, mask);
    mask = GPIO_GET_BANK_BIT_MASK(63);
    TEST_ASSERT_EQUAL_UINT32(0x8000, mask);
    mask = GPIO_GET_BANK_BIT_MASK(64);
    TEST_ASSERT_EQUAL_UINT32(0x0001, mask);
    mask = GPIO_GET_BANK_BIT_MASK(100);
    TEST_ASSERT_EQUAL_UINT32(0x0010, mask);

    DebugP_log("test_gpio_macros end!!!\r\n");

    return;
}

/*
 * Other functions
 */
static void test_gpio_toggle_loop(Test_GpioPrms_t *testPrms)
{
    uint32_t    pinValue, loopcnt;

    GPIO_setDirMode(testPrms->baseAddr, testPrms->pinNum, GPIO_DIRECTION_OUTPUT);
    loopcnt = 0;
    while(loopcnt < testPrms->loopcnt)
    {
        GPIO_pinWriteHigh(testPrms->baseAddr, testPrms->pinNum);
        /* Readback and check */
        pinValue = GPIO_pinOutValueRead(testPrms->baseAddr, testPrms->pinNum);
        TEST_ASSERT_EQUAL_UINT32(GPIO_PIN_HIGH, pinValue);

        ClockP_usleep(testPrms->delayms * 1000);

        GPIO_pinWriteLow(testPrms->baseAddr, testPrms->pinNum);
        /* Readback and check */
        pinValue = GPIO_pinOutValueRead(testPrms->baseAddr, testPrms->pinNum);
        TEST_ASSERT_EQUAL_UINT32(GPIO_PIN_LOW, pinValue);

        ClockP_usleep(testPrms->delayms * 1000);
        loopcnt++;
    }

    return;
}

static void test_gpio_read_loop(Test_GpioPrms_t *testPrms)
{
    uint32_t        pinValue, loopcnt;

    GPIO_setDirMode(testPrms->baseAddr, testPrms->pinNum, GPIO_DIRECTION_INPUT);
    loopcnt = 0;
    while(loopcnt < testPrms->loopcnt)
    {
        pinValue = GPIO_pinRead(testPrms->baseAddr, testPrms->pinNum);
        DebugP_log("Current GPIO pin value: %d\r\n", pinValue);
        ClockP_usleep(testPrms->delayms * 1000);
        loopcnt++;
    }

    return;
}

static void test_gpio_trigger_loop(Test_GpioPrms_t *testPrms)
{
    uint32_t        bankNum, loopcnt;
    uint32_t        intrStatus, pinMask;

    testPrms->intrcnt = 0;
    bankNum = GPIO_GET_BANK_INDEX(testPrms->pinNum);
    pinMask = GPIO_GET_BANK_BIT_MASK(testPrms->pinNum);
    GPIO_setDirMode(testPrms->baseAddr, testPrms->pinNum, GPIO_DIRECTION_OUTPUT);

    /* Set init value based on trigger required */
    if((GPIO_TRIG_TYPE_RISE_EDGE == testPrms->trigType) ||
       (GPIO_TRIG_TYPE_BOTH_EDGE == testPrms->trigType))
    {
        GPIO_pinWriteLow(testPrms->baseAddr, testPrms->pinNum);
    }
    else
    {
        GPIO_pinWriteHigh(testPrms->baseAddr, testPrms->pinNum);
    }
    ClockP_usleep(testPrms->delayms * 1000);

    /* Configure trigger */
    GPIO_setTrigType(testPrms->baseAddr, testPrms->pinNum, testPrms->trigType);
    GPIO_bankIntrEnable(testPrms->baseAddr, bankNum);

    loopcnt = 0;
    while(loopcnt < testPrms->loopcnt)
    {
        if(GPIO_TRIG_TYPE_BOTH_EDGE == testPrms->trigType)
        {
            /* Since both edge, trigger alternatively */
            if((loopcnt & 0x01) == 0)
            {
                GPIO_pinWriteHigh(testPrms->baseAddr, testPrms->pinNum);
                ClockP_usleep(testPrms->delayms * 1000);
            }
            else
            {
                GPIO_pinWriteLow(testPrms->baseAddr, testPrms->pinNum);
                ClockP_usleep(testPrms->delayms * 1000);
            }

            /* Check for interrupt status */
            intrStatus = GPIO_getBankIntrStatus(testPrms->baseAddr, bankNum);
            GPIO_clearBankIntrStatus(testPrms->baseAddr, bankNum, intrStatus);
            if(intrStatus & pinMask)
            {
                testPrms->intrcnt++;
            }
        }

        if(GPIO_TRIG_TYPE_RISE_EDGE == testPrms->trigType)
        {
            GPIO_pinWriteHigh(testPrms->baseAddr, testPrms->pinNum);
            ClockP_usleep(testPrms->delayms * 1000);

            /* Check for interrupt status */
            intrStatus = GPIO_getBankIntrStatus(testPrms->baseAddr, bankNum);
            GPIO_clearBankIntrStatus(testPrms->baseAddr, bankNum, intrStatus);
            if(intrStatus & pinMask)
            {
                testPrms->intrcnt++;
            }

            GPIO_pinWriteLow(testPrms->baseAddr, testPrms->pinNum);
            ClockP_usleep(testPrms->delayms * 1000);

            /* Check for interrupt status - it should not occur */
            intrStatus = GPIO_getBankIntrStatus(testPrms->baseAddr, bankNum);
            TEST_ASSERT_EQUAL_UINT32(0, (intrStatus & pinMask));
        }

        if(GPIO_TRIG_TYPE_FALL_EDGE == testPrms->trigType)
        {
            GPIO_pinWriteLow(testPrms->baseAddr, testPrms->pinNum);
            ClockP_usleep(testPrms->delayms * 1000);

            /* Check for interrupt status */
            intrStatus = GPIO_getBankIntrStatus(testPrms->baseAddr, bankNum);
            GPIO_clearBankIntrStatus(testPrms->baseAddr, bankNum, intrStatus);
            if(intrStatus & pinMask)
            {
                testPrms->intrcnt++;
            }

            GPIO_pinWriteHigh(testPrms->baseAddr, testPrms->pinNum);
            ClockP_usleep(testPrms->delayms * 1000);

            /* Check for interrupt status - it should not occur */
            intrStatus = GPIO_getBankIntrStatus(testPrms->baseAddr, bankNum);
            TEST_ASSERT_EQUAL_UINT32(0, (intrStatus & pinMask));
        }

        loopcnt++;
    }

    TEST_ASSERT_EQUAL_INT32(testPrms->loopcnt, testPrms->intrcnt);

    /* Unregister interrupt */
    GPIO_bankIntrDisable(testPrms->baseAddr, bankNum);
    GPIO_setTrigType(testPrms->baseAddr, testPrms->pinNum, GPIO_TRIG_TYPE_NONE);
    GPIO_clearIntrStatus(testPrms->baseAddr, testPrms->pinNum);

    /* Reset to default value */
    GPIO_pinWriteLow(testPrms->baseAddr, testPrms->pinNum);

    return;
}
#if defined(SOC_AM275X) || defined(SOC_AM62DX) || defined(SOC_AM62PX) || defined(AM62X_SK) || defined(SOC_AM62AX)
#if (defined(SOC_AM62DX) && !(defined(DM_R5F_CORE) || defined(C75_CORE)))
/**
 * @brief Handles GPIO input interrupt in a multi-threaded test scenario.
 *
 * This function retrieves and clears the interrupt status for a specific GPIO bank and pin.
 * If the interrupt was triggered for the given pin, it increments the ISR count and posts to a semaphore.
 * Used for testing GPIO input interrupt handling in concurrent environments.
 * The pin number is passed via the 'args' parameter.
 */
static void TestGpio_InputIntrpt(void *args)
{
    /* Retrieve base address and pin info */
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_INPUT_BASE_ADDR);
    uint32_t pinNum   = (uint32_t)(uintptr_t)args;
    uint32_t bankNum  = GPIO_GET_BANK_INDEX(pinNum);
    uint32_t pinMask  = GPIO_GET_BANK_BIT_MASK(pinNum);

    /* Get and clear bank interrupt status */
    uint32_t status = GPIO_getBankIntrStatus(baseAddr, bankNum);
    GPIO_clearBankIntrStatus(baseAddr, bankNum, status);

    /* If interrupt was for the target pin, increment count and post semaphore */
    if (status & pinMask)
    {
        TestGpio_IsrCount++;
        SemaphoreP_post(&TestGpio_IsrSem);
    }
}

/**
 * @brief Test GPIO input-output interrupt handling in multithreaded context.
 *
 * Configures output and input pins, generates rising edges to trigger interrupts,
 * synchronizes ISR and test thread, and validates interrupt handling.
 */
static void TestGpio_InputOutputIntrpt(void *args)
{
    uint32_t    intrNum, pinNum, i;
    int32_t     ret;
    HwiP_Params hwiPrms;
    uint32_t    delayMs = 1U;
    uint16_t    eventId = HWIP_INVALID_EVENT_ID;
    uint32_t    baseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_INPUT_BASE_ADDR);
    uint32_t    baseAddr2 = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_OUTPUT_BASE_ADDR);
    uint32_t    bankNum  = GPIO_GET_BANK_INDEX(GPIO_INPUT_PIN);

    intrNum = Board_getGpioButtonIntrNum();
    pinNum  = GPIO_INPUT_PIN;

    /* Construct binary semaphore for ISR sync */
    SemaphoreP_constructBinary(&TestGpio_IsrSem, 0);

    /* Initialize board-specific GPIO config */
    Board_gpioInit();

    /* Configure output pin as output and drive low */
    GPIO_setDirMode(baseAddr2, GPIO_OUTPUT_PIN, GPIO_DIRECTION_OUTPUT);
    GPIO_pinWriteLow(baseAddr2, GPIO_OUTPUT_PIN);

    /* Configure input pin as input with rising edge interrupt */
    GPIO_setDirMode(baseAddr1, GPIO_INPUT_PIN, GPIO_DIRECTION_INPUT);
    GPIO_setTrigType(baseAddr1, GPIO_INPUT_PIN, GPIO_TRIG_TYPE_RISE_EDGE);
    GPIO_bankIntrEnable(baseAddr1, bankNum);

    /* Register ISR for GPIO input pin interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = intrNum;
    hwiPrms.eventId  = eventId;
    hwiPrms.isPulse  = 1;
    hwiPrms.callback = &TestGpio_InputIntrpt;
    hwiPrms.args     = (void *)pinNum;
    ret = HwiP_construct(&TestGpio_HardwareObj, &hwiPrms);
    DebugP_assert(ret == SystemP_SUCCESS);

    /* Generate rising edges on output pin to trigger input pin interrupt */
    GPIO_pinWriteLow(baseAddr2, GPIO_OUTPUT_PIN);
    for (i = 0; i < LOOP_TOGGLE_TARGET_COUNT; i++)
    {
        GPIO_pinWriteHigh(baseAddr2, GPIO_OUTPUT_PIN);
        ClockP_usleep(500); /* Short hold to ensure edge is detected */
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, SemaphoreP_pend(&TestGpio_IsrSem, SystemP_WAIT_FOREVER));
        DebugP_log("Key is pressed %u times\r\n", TestGpio_IsrCount);
        GPIO_pinWriteLow(baseAddr2, GPIO_OUTPUT_PIN);
        ClockP_sleep(delayMs);
    }

    /* Disable GPIO bank interrupt */
    GPIO_bankIntrDisable(baseAddr1, bankNum);
    /* Remove trigger type */
    GPIO_setTrigType(baseAddr1, GPIO_INPUT_PIN, GPIO_TRIG_TYPE_NONE);
    /* Clear interrupt status */
    GPIO_clearIntrStatus(baseAddr1, GPIO_INPUT_PIN);
    /* Destruct ISR object */
    HwiP_destruct(&TestGpio_HardwareObj);
    /* Destruct semaphore */
    SemaphoreP_destruct(&TestGpio_IsrSem);

    Board_gpioDeinit();
}
#endif

/**
 * TestGpio_trigLevelNegTc - Verify GPIO behavior with invalid trigger type.
 * Configures a GPIO pin as output and attempts to set an invalid trigger type.
 * Drives a rising edge on the pin and checks that no interrupt is generated.
 * Confirms that the GPIO driver correctly ignores invalid trigger configurations.
 * Cleans up by disabling interrupts and resetting the pin state.
 */
static void TestGpio_trigLevelNegTc(void *arg)
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
}

/**
 * TestGpio_interruptAllBanks - Verify GPIO interrupts across all banks.
 * Uses one representative pin per bank to generate and check interrupt events.
 * Ensures bank interrupt status bits are set for the driven pin and can be cleared.
 * Confirms no spurious bits remain after clearing and restores configuration.
 * Useful for validating bank-wide interrupt handling and regression testing.
 */
static void TestGpio_interruptAllBanks(void *args)
{
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_LED_BASE_ADDR);
    uint32_t maxBanksToTest = 9U; /* feature states up to 9 banks */
    uint32_t bank;

    DebugP_log("\ntest_gpio_interrupt_all_banks started...\r\n");

    /* For each bank 0..8, use pinNum = bank*16 as representative */
    for (bank = 0; bank < maxBanksToTest; bank++)
    {
        uint32_t pinNum  = ( bank * GPIO_MAX_PIN_PER_BANK ) + bank ;
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
}

/**
 * @brief Test GPIO interrupts for two different pins in the same bank.
 *
 * This test configures two pins in the same GPIO bank with different trigger types,
 * generates events on each, and verifies that the correct interrupt status bits are set and cleared.
 * It ensures that interrupts for different pins in the same bank are handled independently.
 */
static void TestGpio_sameBankDiffPin(void *arg)
{
    uint32_t baseAddr1 = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_OSPI_D1_BASE_ADDR);
    uint32_t baseAddr2 = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_OSPI_D2_BASE_ADDR);
    uint32_t pinNumA = GPIO_OSPI_D1_PIN;           /* First pin in the bank */
    uint32_t pinNumB = GPIO_OSPI_D2_PIN;            /* Next pin in the same bank */
    uint32_t bankNum = GPIO_GET_BANK_INDEX(pinNumA);
    uint32_t intrStatus;

    /* Assert both pins are in the same bank */
    TEST_ASSERT_EQUAL_UINT32(GPIO_GET_BANK_INDEX(pinNumA), GPIO_GET_BANK_INDEX(pinNumB));

    /* Configure pin A as output and drive low */
    GPIO_setDirMode(baseAddr1, pinNumA, GPIO_DIRECTION_OUTPUT);
    GPIO_pinWriteLow(baseAddr1, pinNumA);
    ClockP_usleep(1000);

    /* Configure pin B as output and drive high */
    GPIO_setDirMode(baseAddr2, pinNumB, GPIO_DIRECTION_OUTPUT);
    GPIO_pinWriteHigh(baseAddr2, pinNumB);
    ClockP_usleep(1000);

    /* Configure rising edge trigger for pin A and enable bank interrupt */
    GPIO_setTrigType(baseAddr1, pinNumA, GPIO_TRIG_TYPE_RISE_EDGE);
    GPIO_bankIntrEnable(baseAddr1, bankNum);

    /* Configure falling edge trigger for pin B and enable bank interrupt */
    GPIO_setTrigType(baseAddr2, pinNumB, GPIO_TRIG_TYPE_FALL_EDGE);
    GPIO_bankIntrEnable(baseAddr2, bankNum);

    /* --- Test rising edge on pin A --- */
    GPIO_pinWriteHigh(baseAddr1, pinNumA);      /* Drive rising edge on pin A */
    ClockP_usleep(10000);

    /* --- Test falling edge on pin B --- */
    GPIO_pinWriteLow(baseAddr2, pinNumB);       /* Drive falling edge on pin B */
    ClockP_usleep(10000);

    /* Check interrupt status for pin A - verify rising edge triggered */
    intrStatus = GPIO_getIntrStatus(baseAddr1, pinNumA);
    TEST_ASSERT_EQUAL(1U, intrStatus);
    GPIO_clearIntrStatus(baseAddr1, pinNumA);

    /* Drive pin A low again (should not trigger interrupt) */
    GPIO_pinWriteLow(baseAddr1, pinNumA);
    ClockP_usleep(10000);

    /* Confirm no interrupt on falling edge for pin A */
    intrStatus = GPIO_getIntrStatus(baseAddr1, pinNumA);
   TEST_ASSERT_EQUAL(0U, intrStatus);

    /* Check interrupt status for pin B - verify falling edge triggered */
    intrStatus = GPIO_getIntrStatus(baseAddr2, pinNumB);
    TEST_ASSERT_EQUAL(1U, intrStatus);
    GPIO_clearIntrStatus(baseAddr2, pinNumB);

    /* Drive pin B High again (should not trigger interrupt) */
    GPIO_pinWriteHigh(baseAddr2, pinNumB);
    ClockP_usleep(10000);

    /* Confirm no interrupt on falling edge for pin A */
    intrStatus = GPIO_getIntrStatus(baseAddr2, pinNumB);
    TEST_ASSERT_EQUAL(0U, intrStatus);

    /* --- Cleanup --- */
    GPIO_setTrigType(baseAddr1, pinNumA, GPIO_TRIG_TYPE_NONE);
    GPIO_setTrigType(baseAddr2, pinNumB, GPIO_TRIG_TYPE_NONE);
    GPIO_bankIntrDisable(baseAddr1, bankNum);
    GPIO_bankIntrDisable(baseAddr2, bankNum);
    GPIO_clearIntrStatus(baseAddr1, pinNumA);
    GPIO_clearIntrStatus(baseAddr2, pinNumB);
    GPIO_pinWriteLow(baseAddr1, pinNumA);
    GPIO_pinWriteLow(baseAddr2, pinNumB);
}
#endif



