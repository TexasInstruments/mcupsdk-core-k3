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
 *  \file test_dpl.c
 *
 *  \brief dpl test application listing all test cases.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/HeapP.h>
#include <kernel/dpl/CycleCounterP.h>
#include <kernel/dpl/EventP.h>
#include <kernel/dpl/QueueP.h>
#include <kernel/dpl/MailboxP.h>
#include <drivers/soc.h>
#include <unity.h>
#include "ti_drivers_open_close.h"

#if defined(OS_NORTOS)
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/nortos/dpl/common/ClockP_nortos_priv.h>
#if defined(__ARM_ARCH_7R__)
#include <kernel/nortos/dpl/r5/UtilsP_armv7r.h>
#include <kernel/nortos/dpl/r5/MpuP_armv7r.h>
#include <kernel/nortos/dpl/r5/CpuId_armv7r.h>
#include <kernel/nortos/dpl/r5/CacheP_armv7r.h>
#include <kernel/nortos/dpl/r5/HwiP_armv7r_vim.h>
#endif /* if defined (__ARM_ARCH_7R__) */
#endif /* if defined (OS_NORTOS) */

#if defined(OS_FREERTOS) && defined(BUILD_C75X)
#include "kernel/nortos/dpl/c75/csl_clec.h"
#include "kernel/nortos/dpl/c75/MmuP_c75.h"
#include "kernel/nortos/dpl/c75/CacheP_c75.h"
#include "kernel/nortos/dpl/c75/Exception_c75.h"
#endif /* if defined (OS_FREERTOS) && (BUILD_C75X) */

#if defined(OS_SAFERTOS)
#include "kernel/safertos/dpl/common/ClockP_safertos_priv.h"
#include "kernel/nortos/dpl/c75/csl_clec.h"
#include "ti_board_open_close.h"
#endif /* if defined (OS_SAFERTOS) */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Memory size macros */
#define TEST_DPL_MIN_EVER_FREE_HEAP_SIZE                     (256U)
#define TEST_DPL_TASK_STACK_SIZE                             (4 * 1024U)
#define TEST_DPL_HEAP_MEM_SIZE                               (2 * 1024U)
#define TEST_DPL_MMU_REG_SIZE                                (0x80000000U)

/* Address macros */
#define TEST_DPL_ADDR_TRANS_CFG_LOC_ADDR                     (0x35000000UL)
#define TEST_DPL_ADDR_TRANS_CFG_SYS_ADDR                     (0x000100000000UL)
#define TEST_DPL_LOCAL_ADDR_OUT_1                            (0x35000400UL)
#define TEST_DPL_LOCAL_ADDR_OUT_2                            (0x10040000UL)
#define TEST_DPL_SYS_ADDR_IN_1                               (0x000100000400UL)
#define TEST_DPL_SYS_ADDR_IN_2                               (0x100010040000UL)
#define TEST_DPL_MMU_REG_VIR_ADDR                            (0x80000000U)
#define TEST_DPL_MMU_REG_PHY_ADDR                            (0x80000000U)

/* Positive test macros */
#define TEST_DPL_ENABLE                                      (1U)
#define TEST_DPL_DISABLE                                     (0U)
#define TEST_DPL_NUM_ALLOCS                                  (8U)
#define TEST_DPL_HEAP_STAT_CHECK                             (1U)
#define TEST_DPL_CLOCK_TIMEOUT_1                             (5U)
#define TEST_DPL_CLOCK_TIMEOUT_2                             (2U)
#define TEST_DPL_CLOCK_PERIOD                                (1U)
#define TEST_DPL_DEFAULT_TIMEOUT                             (0U)
#define TEST_DPL_INIT_WAIT                                   (0U)
#define TEST_DPL_MAX_WAIT                                    (10000U)
#define TEST_DPL_INIT_CLOCK_OBJECT                           (0U)
#define TEST_DPL_LAST_CLOCK_OBJECT                           (4U)
#define TEST_DPL_CLOCK_START                                 (1U)
#define TEST_DPL_TIMER_PRE_SCALAR                            (2U)
#define TEST_DPL_EVENT_TASK_PRI                              (14U)
#define TEST_DPL_EVENT_WAIT_TICK                             (1U)
#define TEST_DPL_INIT_TASK_OBJECT                            (0U)
#define TEST_DPL_LAST_TASK_OBJECT                            (2U)
#define TEST_DPL_EVENT_BIT_PING                              (0x000001u)
#define TEST_DPL_EVENT_BIT_PONG                              (0x000002u)
#define TEST_DPL_EVENT_BIT_FROM_ISR                          (0x100000u)
#define TEST_DPL_EVENT_BIT2_FROM_ISR                         (0x200000u)
#define TEST_DPL_INT_NUM                                     (20U)
#define TEST_DPL_HWI_LEVEL                                   (0U)
#define TEST_DPL_HWI_PULSE                                   (1U)
#define TEST_DPL_SYSTEM_MODE                                 (0U)
#define TEST_DPL_HWI_ENABLED                                 (1U)
#define TEST_DPL_HWI_DISABLED                                (0U)
#define TEST_DPL_INIT_HWI_OBJECT                             (0U)
#define TEST_DPL_LAST_HWI_OBJECT                             (2U)
#define TEST_DPL_EVENT_BIT                                   (0x10U)
#define TEST_DPL_DEFAULT_EVENT_BIT                           (0x0U)
#define TEST_DPL_CLOCK_SLEEP_IN_SEC                          (1U)
#define TEST_DPL_CLOCK_SLEEP_IN_USEC                         (1000U)
#define TEST_DPL_PERIOD_IN_NANO_SEC                          (1000U * 1000U)
#define TEST_DPL_EVENT_NUM                                   (256U)
#define TEST_DPL_CACHE_BLOK_BYTE_CNT                         (1300U)

/* Negative test macros */
#define TEST_DPL_NO_OVERFLOW                                 (0U)
#define TEST_DPL_NO_SLEEP                                    (0U)
#define TEST_DPL_INVALID_CLOCK_TIMEOUT                       (0U)
#define TEST_DPL_INVALID_EVENT_BIT                           (0U)
#define TEST_DPL_INVALID_CLEAR_ON_EXIT                       (3U)
#define TEST_DPL_INVALID_WAIT_FOR_ALL                        (3U)
#define TEST_DPL_INVALID_TASK_PRIORITY                       (16U)
#define TEST_DPL_INVALID_INIT_COUNT                          (2U)
#define TEST_DPL_INVALID_MAX_COUNT                           (0U)
#define TEST_DPL_HWI_FAIL                                    (1U)
#define TEST_DPL_INVALID_INT_NUM                             (64U)
#define TEST_DPL_INVALID_VEC_ID                              (64U)
#define TEST_DPL_INVALID_ADDR_TRANS_REG_SIZE                 (35U)
#define TEST_DPL_INVALID_ADDR_TRANS_NUM_REGIONS              (20U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* NONE */

/* ========================================================================== */
/*                      Private Function Declarations                        */
/* ========================================================================== */

/* Test case */
void test_dpl_dynamic_coverage(void *args);

/* Helper functions */
#if defined(OS_NORTOS) || defined(OS_SAFERTOS)
static void dpl_heapInternal(void *args);

#if defined(__ARM_ARCH_7R__)
static void dpl_clockpArmv7r(void *args);
#endif /* if defined (__ARM_ARCH_7R__) */

#if defined(OS_NORTOS)
static void dpl_eventNortos(void *args);
static void dpl_taskNortos(void *args);
static void dpl_timerNortos(void *args);
static void dpl_addrTranslateNortos(void *args);
static void dpl_queueNortos(void *args);
static void dpl_debugNortos(void *args);
static void dpl_clockNortos(void *args);
static void dpl_semaphoreNortos(void *args);
#if defined(__ARM_ARCH_7R__)
static void dpl_hwipArmv7rNortos(void *args);
static void dpl_cpuidArmv7r(void *args);
static void dpl_pmupArmv7r(void *args);
static void dpl_cachepArmv7r(void *args);
static void dpl_mpupArmv7r(void *args);
#endif /* if defined (__ARM_ARCH_7R__) */
#endif /* if defined (OS_NORTOS) */

#if defined(OS_SAFERTOS)
static void dpl_taskSafertos(void *args);
static void dpl_clockSafertos(void *args);
extern int _DebugP_log(char *format, ...);
static void dpl_debugSafertos(void *args);
static void dpl_eventSafertos(void *args);
#if defined(__ARM_ARCH_7R__)
static void dpl_hwipArmv7rSafertos(void *args);
#endif /* if defined (__ARM_ARCH_7R__) */
#endif /* if defined (OS_SAFERTOS) */
#endif /* if defined (OS_NORTOS) || (OS_SAFERTOS) */

#if defined(BUILD_C75X)
#if defined(OS_FREERTOS)
static void dpl_cacheC75(void *args);
static void dpl_exceptionC75(void *args);
static void dpl_mmupC75(void *args);
static void dpl_hwiC75(void *args);
static void dpl_cslClec(void *args);
#endif /* if defined (OS_FREERTOS) */

#if defined(OS_SAFERTOS)
static void dpl_clockpC75(void *args);
static void dpl_hwipC75(void *args);
#endif /* if defined (OS_SAFERTOS) */
#endif /* if defined (BUILD_C75X) */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if (defined(OS_NORTOS) || defined(OS_SAFERTOS)) || (defined(OS_FREERTOS) && defined(BUILD_C75X))
static uint32_t gISR = 0U;
#endif /* if defined ((OS_NORTOS) || (OS_SAFERTOS)) || ((OS_FREERTOS) && (BUILD_C75X)) */

#if defined(OS_NORTOS) || (defined(OS_FREERTOS) && defined(BUILD_C75X))
/* Cache buffer to include in test */
static uint32_t cacheTestBuf[256];
#endif /* if defined (OS_NORTOS) || ((OS_FREERTOS) && (BUILD_C75X)) */

#if defined(OS_NORTOS) || defined(OS_SAFERTOS)
static uint32_t gInISR = 0U;
static EventP_Object gEvent;
static ClockP_Object gClock;
static uint8_t gHeapMem[TEST_DPL_HEAP_MEM_SIZE] __attribute__((aligned(HeapP_BYTE_ALIGNMENT)));

#if defined(OS_NORTOS)
extern MpuP_Config gMpuConfig;
static SemaphoreP_Object gDoneSem;
#endif /* if defined (OS_NORTOS) */

#if defined(OS_SAFERTOS)
static uint32_t gIsrEventBits = TEST_DPL_DEFAULT_EVENT_BIT;

#if defined(__ARM_ARCH_7R__)
#if !defined(BUILD_WKUP_R5)
static TaskP_Object gEventTask;
static int32_t gEventSetStatusFromISR = SystemP_FAILURE;
static int32_t gEventSet2StatusFromISR = SystemP_FAILURE;
static int32_t gEventClearStatusFromISR = SystemP_FAILURE;
static int32_t gEventGetBitsStatusFromISR = SystemP_FAILURE;
static uint32_t gEventGetBitsFromISR = TEST_DPL_DEFAULT_EVENT_BIT;
#endif /* if !defined (BUILD_WKUP_R5) */
static uint8_t gTaskStack[TEST_DPL_LAST_TASK_OBJECT][TEST_DPL_TASK_STACK_SIZE] __attribute__((aligned(TEST_DPL_TASK_STACK_SIZE)));
#endif /* if defined (__ARM_ARCH_7R__) */
#endif /* if defined (OS_SAFERTOS) */

#endif /* if defined (OS_NORTOS) || (OS_SAFERTOS) */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    UNITY_BEGIN();

    DebugP_log("\r\nDPL dynamic coverage test...\r\n");
    RUN_TEST(test_dpl_dynamic_coverage, 19188, NULL);
    DebugP_log("\r\nDPL dynamic coverage test : PASS\r\n");

    UNITY_END();
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

void test_dpl_dynamic_coverage(void *args)
{
    #if defined(OS_NORTOS) || defined(OS_SAFERTOS)
        /* Common file coverage function */
        dpl_heapInternal(args);

    #if defined(OS_NORTOS)
        /* Nortos common files coverage functions */
        dpl_eventNortos(args);
        dpl_taskNortos(args);
        dpl_timerNortos(args);
        dpl_addrTranslateNortos(args);
        dpl_queueNortos(args);
        dpl_debugNortos(args);
        dpl_clockNortos(args);
        dpl_semaphoreNortos(args);

    #if defined(__ARM_ARCH_7R__)
        /* Nortos R5 files coverage functions */
        dpl_hwipArmv7rNortos(args);
        dpl_cpuidArmv7r(args);
        dpl_pmupArmv7r(args);
        dpl_cachepArmv7r(args);
        dpl_mpupArmv7r(args);
    #endif /* if defined (__ARM_ARCH_7R__) */
    #endif /* if defined (OS_NORTOS) */

    #if defined(OS_SAFERTOS)
        /* Safertos common files coverage functions */
        dpl_taskSafertos(args);
        dpl_clockSafertos(args);
        dpl_debugSafertos(args);
        dpl_eventSafertos(args);

    #if defined(__ARM_ARCH_7R__)
        /* Safertos R5 file coverage function */
        dpl_hwipArmv7rSafertos(args);
    #endif /* if defined (__ARM_ARCH_7R__) */

    #if defined(BUILD_C75X)
        /* Safertos C75 files coverage functions */
        dpl_clockpC75(args);
        dpl_hwipC75(args);
    #endif /* if defined (BUILD_C75X) */
    #endif /* if defined (OS_SAFERTOS) */

    #if defined(__ARM_ARCH_7R__)
        /* Common R5 file coverage function */
        dpl_clockpArmv7r(args);
    #endif /* if defined (__ARM_ARCH_7R__) */
    #endif /* if defined (OS_NORTOS) || defined (OS_SAFERTOS) */

    #if defined(OS_FREERTOS) && defined(BUILD_C75X)
        /* Nortos C75 files coverage functions */
        dpl_cacheC75(args);
        dpl_exceptionC75(args);
        dpl_mmupC75(args);
        dpl_hwiC75(args);
        dpl_cslClec(args);
    #endif /* if defined (OS_FREERTOS) && (BUILD_C75X) */
}

/**
 * \brief  Test function for DPL heap internal APIs.
 *
 * The test constructs a heap and alloc blocks in heap, gets heap
 * stat and free the blocks in heap with provided parameters
 * for positive and possible negative test cases.
 */
#if defined(OS_NORTOS) || defined(OS_SAFERTOS)
static void dpl_heapInternal(void *args)
{
    static HeapP_Object heapObj;
    HeapP_MemStats heapMemStat;
    /* To create heap memory with unaligned address */
    void *heapMem = (char *)gHeapMem + 1U;
    /* Provided heap size to allocate heap space */
    uint32_t size[TEST_DPL_NUM_ALLOCS] = {15, 31, 64, 255, 127, 7, 232, 255};
    /* Pointer variable to collect heap block addresses, one extra pointer to use for fail conditions */
    void *ptr[TEST_DPL_NUM_ALLOCS + 1U];
    size_t minEvrFreeSize;
    size_t wantedSize;
    int32_t i;

    /* Getting heap stat before heap construct */
    HeapP_getHeapStats(&heapObj, &heapMemStat);

    /* Create heap */
    HeapP_construct(&heapObj, heapMem, TEST_DPL_HEAP_MEM_SIZE);

    /* Allocate space in heap memory */
    for (i = 0U; i < TEST_DPL_NUM_ALLOCS; i++)
    {
        ptr[i] = HeapP_alloc(&heapObj, size[i]);
        TEST_ASSERT_NOT_NULL(ptr[i]);
    }

    /* Passing wantedSize of HeapP_alloc with top bit set */
    wantedSize = ((size_t) 1 ) << ((sizeof(size_t) * (size_t)8) - 1U);
    ptr[i] = HeapP_alloc(&heapObj, wantedSize);
    TEST_ASSERT_NULL(ptr[i]);

    /* Freed a pointer with NULL */
    HeapP_free(&heapObj, ptr[i]);

    /* Passing wantedSize of heap alloc as 0U */
    wantedSize = 0U;
    ptr[i] = HeapP_alloc(&heapObj, wantedSize);
    TEST_ASSERT_NULL(ptr[i]);

    /* Get min ever free heap size available in heap */
    minEvrFreeSize = HeapP_getMinimumEverFreeHeapSize(&heapObj);
    TEST_ASSERT_EQUAL_size_t(TEST_DPL_MIN_EVER_FREE_HEAP_SIZE, minEvrFreeSize);

    /* Free allocated heap memory */
    for(i = 0U; i < TEST_DPL_NUM_ALLOCS; i++)
    {
        HeapP_free(&heapObj, ptr[i]);

        if(i == TEST_DPL_HEAP_STAT_CHECK)
        {
            /* Get stats of heap memory */
            HeapP_getHeapStats(&heapObj, &heapMemStat);

            /* Allocating size greater than available free blocks size */
            wantedSize = 320U;
            ptr[i] = HeapP_alloc(&heapObj, wantedSize);
            TEST_ASSERT_NULL(ptr[i]);
        }
    }

    /* Destruct heap */
    HeapP_destruct(&heapObj);
}

/* Dummy Hwip callback function */
static void dpl_hwipCallback(void *args)
{
    gISR++;
    if(HwiP_inISR())
    {
        gInISR++;
    }
    return;
}

/* Dummy clock callback function */
static void dpl_clockCallback(ClockP_Object *obj, void *args)
{
    gISR++;
    return;
}

/**
 * \brief  Test function for DPL clock APIs.
 *
 * The test to get clock timer count value and compare
 * to value of timer get count.
 * Both values should be equal before starting the timer.
 */
#if defined(__ARM_ARCH_7R__)
static void dpl_clockpArmv7r(void *args)
{
    #if defined(BUILD_WKUP_R5)
    uint32_t timerBaseAddr = CSL_WKUP_TIMER1_CFG_BASE;
    #elif defined(BUILD_MCU_R5)
    uint32_t timerBaseAddr = CSL_MCU_TIMER1_CFG_BASE;
    #elif defined(BUILD_MAIN_R5)
    uint32_t timerBaseAddr = CSL_TIMER1_CFG_BASE;
    #endif
    uint32_t timerCount;

    /* Get timer count value from clock getTimerCount and timer getCount, both should be same */
    timerCount = ClockP_getTimerCount(timerBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(TimerP_getCount(timerBaseAddr), timerCount);
}
#endif /* if defined (__ARM_ARCH_7R__) */
#endif /* if defined (OS_NORTOS) || (OS_SAFERTOS) */

/**
 * \brief  Test function for DPL event APIs.
 *
 * The test to construct an event and set bits, get bits, clear bits
 * and wait for bits to be set in an event with provided parameters
 * for positive and possible negative test cases.
 */
#if defined(OS_NORTOS)
static void dpl_eventNortos(void *args)
{
    uint32_t eventBits;
    int32_t status;
    uint8_t clearOnExit;
    uint8_t waitForAll;
    uint32_t timeToWaitInTicks;

    /* Create event */
    status = EventP_construct(&gEvent);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* clearOnExit enabled, waitForAll disabled to wait for any one bit to set */
    clearOnExit = TEST_DPL_ENABLE;
    waitForAll = TEST_DPL_DISABLE;
    status = EventP_waitBits(&gEvent, TEST_DPL_EVENT_BIT, clearOnExit, waitForAll, SystemP_NO_WAIT, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* clearOnExit disabled, waitForAll enabled and timeToWaitInTicks given SystemP_NO_WAIT*/
    clearOnExit = TEST_DPL_DISABLE;
    waitForAll = TEST_DPL_ENABLE;
    status = EventP_waitBits(&gEvent, TEST_DPL_EVENT_BIT, clearOnExit, waitForAll, SystemP_NO_WAIT, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT, status);

    /* To set bits for the event */
    status = EventP_setBits(&gEvent, TEST_DPL_EVENT_BIT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* timeToWaitInTicks given SystemP_WAIT_FOREVER */
    clearOnExit = TEST_DPL_DISABLE;
    waitForAll = TEST_DPL_ENABLE;
    status = EventP_waitBits(&gEvent, TEST_DPL_EVENT_BIT, clearOnExit, waitForAll, SystemP_WAIT_FOREVER, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* timeToWaitInTicks given enabled to start the clock */
    clearOnExit = TEST_DPL_DISABLE;
    waitForAll = TEST_DPL_ENABLE;
    timeToWaitInTicks = TEST_DPL_EVENT_WAIT_TICK;
    status = EventP_waitBits(&gEvent, TEST_DPL_EVENT_BIT, clearOnExit, waitForAll, timeToWaitInTicks, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Get bits from the event */
    status = EventP_getBits(&gEvent, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Clear the bits in the event */
    status = EventP_clearBits(&gEvent, TEST_DPL_EVENT_BIT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Destruct event */
    EventP_destruct(&gEvent);
}

/**
 * \brief  Test function for DPL task APIs.
 *
 * Task is not applicable in NORTOS, these are empty functions.
 */

static void dpl_taskNortos(void *args)
{
    uint32_t key;

    TaskP_yield();

    key = TaskP_disable();

    TaskP_restore(key);

    /* Asserting task disable return outside critical section */
    TEST_ASSERT_EQUAL_UINT32(SystemP_SUCCESS, key);
}

/**
 * \brief  Test function for DPL timer APIs.
 *
 * The test to initialize and setup a timer in one shot mode,
 * start it, check for overflow, stop it and clear overflow.
 */
static void dpl_timerNortos(void *args)
{
    TimerP_Params timerParams;
    #if defined(BUILD_WKUP_R5)
    uint32_t timerBaseAddr = CSL_WKUP_TIMER1_CFG_BASE;
    #elif defined(BUILD_MCU_R5)
    uint32_t timerBaseAddr = CSL_MCU_TIMER1_CFG_BASE;
    #elif defined(BUILD_MAIN_R5)
    uint32_t timerBaseAddr = CSL_TIMER1_CFG_BASE;
    #endif
    uint32_t isOverflowed;
    uint32_t reloadCount;

    TimerP_Params_init(&timerParams);

    /* Provided valid parameters to timerSetup for oneshot mode */
    timerParams.oneshotMode = TEST_DPL_ENABLE;
    timerParams.periodInUsec = TEST_DPL_DISABLE;
    timerParams.periodInNsec = TEST_DPL_PERIOD_IN_NANO_SEC;
    timerParams.enableOverflowInt = TEST_DPL_DISABLE;
    TimerP_setup(timerBaseAddr, &timerParams);

    /* Initializing timer params with default values and passing timer prescalar value as greater than 1U */
    TimerP_Params_init(&timerParams);
    timerParams.inputPreScaler = TEST_DPL_TIMER_PRE_SCALAR;
    TimerP_setup(timerBaseAddr, &timerParams);

    /* Before starting the timer, timer reload count and timer count will be equal */
    reloadCount = TimerP_getReloadCount(timerBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(reloadCount, TimerP_getCount(timerBaseAddr));

    /* Start timer */
    TimerP_start(timerBaseAddr);

    /* To get overflow bit value before overflow */
    isOverflowed = TimerP_isOverflowed(timerBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(TEST_DPL_NO_OVERFLOW, isOverflowed);

    /* Stop timer */
    TimerP_stop(timerBaseAddr);

    /* Clear overflow bit */
    TimerP_clearOverflowInt(timerBaseAddr);
}

/**
 * \brief  Test function for DPL addr translate APIs.
 *
 * The test to initialize a addr translate region and translate
 * the system address to local address with provided parameters
 * for positive and possible negative test cases.
 */
static void dpl_addrTranslateNortos(void *args)
{
    int32_t status;
    AddrTranslateP_Params addrParam;
    AddrTranslateP_RegionConfig addrRegCfg;
    void *result;

    /* Assigning values for region config params */
    addrRegCfg.systemAddr = TEST_DPL_ADDR_TRANS_CFG_SYS_ADDR;
    addrRegCfg.localAddr = TEST_DPL_ADDR_TRANS_CFG_LOC_ADDR;
    addrRegCfg.size = AddrTranslateP_RegionSize_32K;

    /* Initialize addrParam with default values */
    AddrTranslateP_Params_init(&addrParam);

    /* Passing valid parameters for address translate init */
    #if defined(BUILD_WKUP_R5)
    addrParam.ratBaseAddr = CSL_WKUP_R5FSS0_RAT_CFG_BASE;
    #elif defined(BUILD_MCU_R5)
    addrParam.ratBaseAddr = CSL_MCU_R5FSS0_RAT_CFG_BASE;
    #elif defined(BUILD_MAIN_R5)
    addrParam.ratBaseAddr = CSL_R5FSS0_RAT_CFG_BASE;
    #endif
    addrParam.numRegions = 1U;
    addrParam.regionConfig = &addrRegCfg;
    status = AddrTranslateP_init(&addrParam);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Given a system address inside config systemAddr range and config size to get Local addr */
    result = AddrTranslateP_getLocalAddr(TEST_DPL_SYS_ADDR_IN_1);
    TEST_ASSERT_EQUAL_PTR(TEST_DPL_LOCAL_ADDR_OUT_1, result);

    /* Given a system address outside config systemAddr range, returns 32b of input systemAddr as localAddr */
    result = AddrTranslateP_getLocalAddr(TEST_DPL_SYS_ADDR_IN_2);
    TEST_ASSERT_EQUAL_PTR(TEST_DPL_LOCAL_ADDR_OUT_2, result);

    /* Negative test - Passing invalid region config size */
    addrRegCfg.size = TEST_DPL_INVALID_ADDR_TRANS_REG_SIZE;
    status = AddrTranslateP_init(&addrParam);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Negative test - Passing invalid number of regions */
    addrParam.numRegions = TEST_DPL_INVALID_ADDR_TRANS_NUM_REGIONS;
    status = AddrTranslateP_init(&addrParam);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Negative test - Passing NULL to addr translate init */
    status = AddrTranslateP_init(NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}

/**
 * \brief  Test function for DPL queue APIs.
 *
 * The test to create a queue, put an element, check for empty
 * queue and delete the queue with provided parameters
 * for positive and possible negative test cases.
 */
static void dpl_queueNortos(void *args)
{
    QueueP_Handle   handle;
    QueueP_Object   qObj;
    QueueP_Elem     buf;
    int32_t         status;

    handle = QueueP_create(&qObj);
    TEST_ASSERT_NOT_NULL(handle);

    /* Queue push */
    status = QueueP_put(handle, &buf);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Passing queue element as NULL */
    status = QueueP_put(handle, (QueueP_Elem *)NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Check queue is not empty */
    TEST_ASSERT_EQUAL_UINT32(QueueP_NOTEMPTY, QueueP_isEmpty(handle));

    /* Delete queue */
    status = QueueP_delete(handle);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * \brief  Test function for DPL debug API.
 *
 * The test to debug assert for a true condition without a log.
 */
static void dpl_debugNortos(void *args)
{
    /* To cover DebugP_assertNoLog for true condition */
    DebugP_assertNoLog(true);
}

/**
 * \brief  Test function for DPL clock APIs.
 *
 * The test to initialize and create clocks, start, set timeout,
 * get timeout, stop and delete a clock with provided parameters
 * for positive and possible negative test cases.
 */
static void dpl_clockNortos(void *args)
{
    ClockP_Object clockObj[TEST_DPL_LAST_CLOCK_OBJECT];
    uint32_t timeout[TEST_DPL_LAST_CLOCK_OBJECT] = {14, 8, 10, 12};
    ClockP_Params clockParams;
    uint32_t status;
    uint8_t i;

    ClockP_Params_init(&clockParams);

    /* Passing valid parameters to clock construct to start clock in construct as oneshot */
    clockParams.period = TEST_DPL_DISABLE;
    clockParams.start = TEST_DPL_CLOCK_START;
    status = ClockP_construct(&gClock, &clockParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Setting a different timeout to the clock object */
    ClockP_setTimeout(&gClock, TEST_DPL_CLOCK_TIMEOUT_1);

    /* Starting clock to change the timeout */
    ClockP_start(&gClock);

    /* Checking for the timeout change */
    status = ClockP_getTimeout(&gClock);
    TEST_ASSERT_EQUAL_INT32(TEST_DPL_CLOCK_TIMEOUT_1, status);

    /* Passing in 0U as a parameter */
    ClockP_sleep(TEST_DPL_NO_SLEEP);
    ClockP_destruct(&gClock);

    /* Initializing with default clock parameters */
    ClockP_Params_init(&clockParams);

    /* Trying to stop, when global clock list is empty */
    ClockP_stop(&clockObj[TEST_DPL_INIT_CLOCK_OBJECT]);
    /* Trying to destruct, when global clock list is empty */
    ClockP_destruct(&clockObj[TEST_DPL_INIT_CLOCK_OBJECT]);

    /* Passing valid parameters to create clock objects */
    for(i = TEST_DPL_INIT_CLOCK_OBJECT; i < TEST_DPL_LAST_CLOCK_OBJECT; i++)
    {
        clockParams.timeout = timeout[i];
        clockParams.period = TEST_DPL_CLOCK_PERIOD;
        clockParams.callback = (ClockP_FxnCallback) dpl_clockCallback;
        status = ClockP_construct(&clockObj[i], &clockParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* To get timeout before timer start */
    status = ClockP_getTimeout(&clockObj[TEST_DPL_INIT_CLOCK_OBJECT]);
    TEST_ASSERT_EQUAL_INT32(timeout[TEST_DPL_INIT_CLOCK_OBJECT], status);

    /* Start all the clock objects */
    for(i = TEST_DPL_INIT_CLOCK_OBJECT; i < TEST_DPL_LAST_CLOCK_OBJECT; i++)
    {
        ClockP_start(&clockObj[i]);
    }

    /* Stopping clocks in global clock list */
    for (i = TEST_DPL_INIT_CLOCK_OBJECT; i < TEST_DPL_LAST_CLOCK_OBJECT - 2U; i++)
    {
        ClockP_stop(&clockObj[i]);
    }

    /* Stopping unavailable clock to traverse through global clock list and return */
    ClockP_stop(&clockObj[TEST_DPL_INIT_CLOCK_OBJECT]);

    /* Destructing unavailable clock to traverse through global clock list and return */
    ClockP_destruct(&clockObj[TEST_DPL_INIT_CLOCK_OBJECT]);

    /* Stopping a clock removes it from global clock list, so destruct remaining clocks in global clock list */
    for (i = TEST_DPL_LAST_CLOCK_OBJECT - 1U; i > TEST_DPL_INIT_CLOCK_OBJECT + 1U; i--)
    {
        ClockP_destruct(&clockObj[i]);
    }
}

/**
 * \brief  Test function for DPL semaphore APIs.
 *
 * The test to create, post and delete counting and mutex semaphores
 * with provided parameters for positive and possible negative test cases.
 */
static void dpl_semaphoreNortos(void *args)
{
    int32_t status;
    uint32_t initCount;
    uint32_t maxCount;

    /* Passing invalid initcount and maxcount to semaphore construct, to be resetted internally */
    initCount = TEST_DPL_INVALID_INIT_COUNT;
    maxCount = TEST_DPL_INVALID_MAX_COUNT;
    status = SemaphoreP_constructCounting(&gDoneSem, initCount, maxCount);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Destruct the counting semaphore */
    SemaphoreP_destruct(&gDoneSem);

    /* Construct a mutex semaphore */
    status = SemaphoreP_constructMutex(&gDoneSem);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Post the mutex semaphore */
    SemaphoreP_post(&gDoneSem);

    /* Destruct the mutex semaphore */
    SemaphoreP_destruct(&gDoneSem);
}

/**
 * \brief  Test function for DPL Hardware interrupt(HWI) APIs.
 *
 * The test to initialize and create a HWI, post, set args,
 * disable int, enable int, restore int and delete the HWI
 * with provided parameters for possible test cases.
 */
#if defined(__ARM_ARCH_7R__)
static void dpl_hwipArmv7rNortos(void *args)
{
    HwiP_Params HwiParams;
    HwiP_Object HwiObject;
    int32_t status;
    uint32_t oldIntState;
    gISR = 0;
    gInISR = 0;

    /* Initialize hwi params to default */
    HwiP_Params_init(&HwiParams);

    /* Setup interrupt as FIQ and in pulse mode */
    HwiParams.intNum = TEST_DPL_INT_NUM;
    HwiParams.callback = dpl_hwipCallback;
    HwiParams.isFIQ = TEST_DPL_ENABLE;
    HwiParams.isPulse = TEST_DPL_HWI_PULSE;
    status = HwiP_construct(&HwiObject, &HwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Posted interrupt to call dpl_hwipCallback */
    HwiP_post(HwiParams.intNum);

    /* Check for callback execution */
    TEST_ASSERT_EQUAL_UINT32(1U, gISR);

    /* Check for interrupt in ISR */
    TEST_ASSERT_EQUAL_UINT32(1U, gInISR);

    /* Destructing HwiP_Object */
    HwiP_destruct(&HwiObject);

    /* Setup interrupt as FIQ and in level mode */
    HwiP_Params_init(&HwiParams);
    HwiParams.intNum = TEST_DPL_INT_NUM;
    HwiParams.callback = dpl_hwipCallback;
    HwiParams.args = (void *)args;
    HwiParams.isFIQ = TEST_DPL_ENABLE;
    HwiParams.isPulse = TEST_DPL_HWI_LEVEL;
    status = HwiP_construct(&HwiObject, &HwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Set args to pass to hwi callback function */
    status = HwiP_setArgs(&HwiObject, args);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Posted interrupt to call dpl_hwipCallback */
    HwiP_post(HwiParams.intNum);

    /* Check for callback execution */
    TEST_ASSERT_EQUAL_UINT32(2U, gISR);

    /* Check for interrupt in ISR */
    TEST_ASSERT_EQUAL_UINT32(2U, gInISR);

    /* Disable interrupt, returns interrupt's last state */
    oldIntState = HwiP_disableInt(HwiParams.intNum);
    TEST_ASSERT_EQUAL_UINT32(TEST_DPL_HWI_ENABLED, oldIntState);

    /* Interrupt already disabled, disabling it again */
    TEST_ASSERT_EQUAL_UINT32(TEST_DPL_HWI_DISABLED, HwiP_disableInt(HwiParams.intNum));

    /* Restoring interrupt with TEST_DPL_HWI_DISABLED */
    HwiP_restoreInt(HwiParams.intNum, HwiP_disableInt(HwiParams.intNum));

    /* Restoring interrupt with old interrupt state */
    HwiP_restoreInt(HwiParams.intNum, oldIntState);

    /* Destructing HwiP_Object */
    HwiP_destruct(&HwiObject);
}

/**
 * \brief  Test function for DPL cpu Id API.
 *
 * The test to get ARM5 cpu Id with provided parameters
 * for positive and possible negative test cases.
 */
static void dpl_cpuidArmv7r(void *args)
{
    CSL_ArmR5CPUInfo cpuInfo;

    /* Get CPU ID and group ID of R5 */
    CSL_armR5GetCpuID(&cpuInfo);

    /* Providing input as NULL */
    CSL_armR5GetCpuID(NULL);
}

/**
 * \brief  Test function for DPL PMU API.
 *
 * The test to convert nano seconds to ticks
 * with provided parameters for possible test cases.
 */
static void dpl_pmupArmv7r(void *args)
{
    /* To convert nanoseconds to system ticks */
    uint64_t nanosecs = 2 * TIME_IN_NANO_SECONDS;
    CycleCounterP_nsToTicks(nanosecs);
}

/**
 * \brief  Test function for DPL cache APIs.
 *
 * The test to enable, invalidate and disable cache memory
 * with provided parameters for possible test cases.
 */
static void dpl_cachepArmv7r(void *args)
{
    /* Cache enable type L1D and L1P */
    CacheP_enable(CacheP_TYPE_L1D);
    CacheP_enable(CacheP_TYPE_L1P);

    /* Cache invalidate type L1D and L1P */
    CacheP_inv((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_L1D);
    CacheP_inv((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_L1P);

    /* Cache disable type L1D and L1P */
    CacheP_disable(CacheP_TYPE_L1D);
    CacheP_disable(CacheP_TYPE_L1P);
}

/**
 * \brief  Test function for DPL MPU APIs.
 *
 * The test to initialize region attributes and set, enable and
 * verify MPU region with provided parameters for possible test cases.
 */
static void dpl_mpupArmv7r(void *args)
{
    uint32_t mpuBaseAddr;
    MpuP_RegionAttrs regionParams;
    uint32_t regionNum;
    int32_t status;
    uint32_t regEnable;

    CacheP_disable(CacheP_TYPE_ALL);

    MpuP_RegionAttrs_init(&regionParams);
    regionNum = gMpuConfig.numRegions;
    mpuBaseAddr = CSL_MCU_MSRAM_256K1_RAM_BASE;
    regionParams.isEnable = TEST_DPL_ENABLE;           /* MPU region enable */
    regionParams.isCacheable = TEST_DPL_ENABLE;        /* is cacheable */
    regionParams.isBufferable = TEST_DPL_ENABLE;       /* is bufferable */
    regionParams.isSharable = TEST_DPL_DISABLE;        /* not a shared memory */
    regionParams.isExecuteNever = TEST_DPL_DISABLE;    /* not executable */
    regionParams.tex = TEST_DPL_ENABLE;
    MpuP_setRegion(regionNum, (void *)mpuBaseAddr, MpuP_RegionSize_256K, &regionParams);

    MpuP_enable();
    CacheP_enable(CacheP_TYPE_L1);

    /* To verify MPU region is enabled or not */
    regEnable = TEST_DPL_ENABLE;
    status = MpuP_VerifyEnableRegion(regionNum, regEnable);
    TEST_ASSERT_EQUAL_INT32(CSL_PASS, status);

    /* Disabling the MPU region */
    regEnable = TEST_DPL_DISABLE;
    MpuP_EnableRegion(regionNum, regEnable);

    /* After disabling the MPU region verify should return CSL_EFAIL */
    regEnable = TEST_DPL_ENABLE;
    status = MpuP_VerifyEnableRegion(regionNum, regEnable);
    TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, status);

    /* Reset the MPU region */
    MpuP_resetRegion(regionNum);
}
#endif /* if defined (__ARM_ARCH_7R__) */
#endif /* if defined (OS_NORTOS) */

/**
 * \brief  Test function for DPL cache APIs.
 *
 * The test to enable, invalidate, write back, write through,
 * write back all, invalidate all and disable cache memory
 * with provided parameters for possible test cases.
 */
#if defined(OS_FREERTOS) && defined(BUILD_C75X)
static void dpl_cacheC75(void *args)
{
    CacheP_Size size;

    /* Enable cache type CacheP_TYPE_L1P */
    CacheP_enable(CacheP_TYPE_L1P);

    /* Enable write back for cache type CacheP_TYPE_L1P */
    CacheP_enableWB(CacheP_TYPE_L1P);

    /* Enable write through for cache type CacheP_TYPE_L1D*/
    CacheP_enableWT(CacheP_TYPE_L1D);
    /* Enable write through for cache type CacheP_TYPE_L1P */
    CacheP_enableWT(CacheP_TYPE_L1P);

    /* To get cache size */
    CacheP_getSize(&size);

    /* Perform global write back for cache type CacheP_TYPE_L1D*/
    CacheP_wbAll(CacheP_TYPE_L1D);
    /* Perform global write back for cache type CacheP_TYPE_L1P */
    CacheP_wbAll(CacheP_TYPE_L1P);

    /* To write back and invalidate all in data cache */
    Cache_wbInvL1dAll();

    /* Perform global write back and invalidate cache type CacheP_TYPE_L1D*/
    CacheP_wbInvAll(CacheP_TYPE_L1D);
    /* Perform global write back and invalidate cache type CacheP_TYPE_L1P */
    CacheP_wbInvAll(CacheP_TYPE_L1P);

    /* To invalidate all in data cache */
    CacheP_invL1dAll();

    /* To invalidate a cache block with byte count < 1280 */
    CacheP_inv((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_ALL);
    /* To invalidate a cache block with byte count > 1280 */
    CacheP_inv((void *)cacheTestBuf, TEST_DPL_CACHE_BLOK_BYTE_CNT, CacheP_TYPE_ALL);

    /* To write back a cache block with byte count < 1280 */
    CacheP_wb((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_ALL);
    /* To write back a cache block with byte count > 1280 */
    CacheP_wb((void *)cacheTestBuf, TEST_DPL_CACHE_BLOK_BYTE_CNT, CacheP_TYPE_ALL);

    /* To write back and invalidate a cache block with byte count < 1280 */
    CacheP_wbInv((void *)cacheTestBuf, sizeof(cacheTestBuf), CacheP_TYPE_ALL);
    /* To write back and invalidate a cache block with byte count > 1280 */
    CacheP_wbInv((void *)cacheTestBuf, TEST_DPL_CACHE_BLOK_BYTE_CNT, CacheP_TYPE_ALL);

    /* Disable cache type CacheP_TYPE_L1D*/
    CacheP_disable(CacheP_TYPE_L1D);
    /* Disable cache type CacheP_TYPE_L1P */
    CacheP_disable(CacheP_TYPE_L1P);
}

/* Dummy exception function */
static void dpl_excepFunx(void)
{
    return;
}

/**
 * \brief  Test function for DPL exception APIs.
 *
 * The test to set return pointer for exception and
 * get last status and clear last status of execption
 * with provided parameters for possible test cases.
 */
static void dpl_exceptionC75(void *args)
{
    Exception_FuncPtr newFunx, oldFunx;
    Exception_Status status;

    newFunx = (Exception_FuncPtr)dpl_excepFunx;
    /* Set return pointer to exception, returns old return pointer */
    oldFunx = Exception_setReturnPtr(newFunx);
    TEST_ASSERT_NULL(oldFunx);

    /* To get last exception status */
    Exception_getLastStatus(&status);

    /* To clear last exception status */
    Exception_clearLastStatus();
}

/**
 * \brief  Test function for DPL MMU APIs.
 *
 * The test to initialize MMU region attributes and MMU map region
 * with provided parameters for possible test cases.
 */
static void dpl_mmupC75(void *args)
{
    MmuP_MapAttrs mapAttrs;
    int32_t status;

    CacheP_disable(CacheP_TYPE_ALL);
    /* Mmup already enabled, enabling it again so returns doing nothing */
    MmuP_enable();
    /* Disable Mmu before mapping Mmu region */
    MmuP_disable();

    /* make memory region as outer and inner writeback cacheable */
    MmuP_MapAttrs_init(&mapAttrs);
    mapAttrs.accessPerm = MMUP_ACCESS_PERM_PRIV_RW_USER_NONE;
    mapAttrs.privExecute = TEST_DPL_ENABLE;
    mapAttrs.userExecute = TEST_DPL_DISABLE;
    mapAttrs.shareable = MMUP_SHARABLE_OUTER;
    mapAttrs.attrIndx = MMUP_ATTRINDX_MAIR7;
    mapAttrs.global = TEST_DPL_ENABLE;
    status = MmuP_map(TEST_DPL_MMU_REG_VIR_ADDR, TEST_DPL_MMU_REG_PHY_ADDR, TEST_DPL_MMU_REG_SIZE, &mapAttrs);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Enable Mmu after mapping Mmu region */
    MmuP_enable();
    CacheP_enable(CacheP_TYPE_ALL);
}

/* Dummy hwi callback function */
static void dpl_hwiCallback(unsigned int arg)
{
    gISR++;
    return;
}

/**
 * \brief  Test function for DPL Hardware interrupt(HWI) APIs.
 *
 * The test to initialize and create a HWI, disable int, enable int,
 * restore int ,clear, dispatch and delete the HWI with provided
 * parameters for positive and possible negative test cases.
 */
static void dpl_hwiC75(void *args)
{
    HwiC7x_Struct hwiObj;
    Hwi_Params hwiParams;
    Hwi_StackInfo stkInfo;
    unsigned long mask, result;
    uint32_t key;
    int32_t status;
    int eventId;

    /* Initialize hwi params */
    Hwi_Params_init(&hwiParams);

    /* Construct hwi object with invalid intNum */
    status = Hwi_construct(&hwiObj, TEST_DPL_INVALID_INT_NUM, dpl_hwiCallback, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(TEST_DPL_HWI_FAIL, status);

    /* Passing Hwi_MaskingOption_NONE to maskSetting and callback func as NULL */
    hwiParams.maskSetting = Hwi_MaskingOption_NONE;
    status = Hwi_construct(&hwiObj, TEST_DPL_INT_NUM, NULL, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Construct hwi object, passing already enabled intNum */
    status = Hwi_construct(&hwiObj, TEST_DPL_INT_NUM, NULL, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(TEST_DPL_HWI_FAIL, status);

    /* Negative case : Dispatch hwi with TEST_DPL_INT_NUM and NULL callback */
    Hwi_dispatchCore(TEST_DPL_INT_NUM);

    /* Clear interrupt */
    HwiP_clearInt(TEST_DPL_INT_NUM);

    /* Passing Hwi_MaskingOption_ALL to maskSetting */
    hwiParams.maskSetting = Hwi_MaskingOption_ALL;
    /* Construct hwi object with TEST_DPL_INT_NUM + 1U */
    status = Hwi_construct(&hwiObj, TEST_DPL_INT_NUM + 1U, dpl_hwiCallback, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Destruct hwi object with TEST_DPL_INT_NUM + 1U */
    Hwi_destruct(TEST_DPL_INT_NUM + 1U);

    /* Passing Hwi_MaskingOption_BITMASK to maskSetting */
    hwiParams.maskSetting = Hwi_MaskingOption_BITMASK;
    /* Construct hwi object with TEST_DPL_INT_NUM + 2U and NULL hwi object */
    status = Hwi_construct(NULL, TEST_DPL_INT_NUM + 2U, dpl_hwiCallback, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Negative case : Dispatch hwi with TEST_DPL_INT_NUM + 2U */
    Hwi_dispatchCore(TEST_DPL_INT_NUM + 2U);

    /* Destruct hwi object with TEST_DPL_INT_NUM + 2U */
    Hwi_destruct(TEST_DPL_INT_NUM + 2U);

    /* Map an event to hwi vector, provided invalid vectId */
    eventId = 0;
    Hwi_eventMap(TEST_DPL_INVALID_VEC_ID, eventId);

    /* Provided invalid vectId */
    status = Hwi_getEventId(TEST_DPL_INVALID_VEC_ID);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    mask = 1L << (TEST_DPL_INT_NUM + 1U);
    /* Restore interrupt, return last state before restoring */
    result = Hwi_restoreIER(mask);
    TEST_ASSERT_EQUAL( (result | mask) , Hwi_restoreIER(mask));

    /* Disable interrupt, returns last state of interrupt */
    key = HwiP_disableInt(TEST_DPL_INT_NUM);
    TEST_ASSERT_EQUAL_UINT32(TEST_DPL_HWI_ENABLED, key);

    /* Restore interrupt, here HwiP_disableInt gives 0U as interrupt is already disabled */
    HwiP_restoreInt(TEST_DPL_INT_NUM, HwiP_disableInt(TEST_DPL_INT_NUM));
    /* Restore interrupt, key has last int state */
    HwiP_restoreInt(TEST_DPL_INT_NUM, key);

    /* Passing status as 1U in Hwi instance finalize */
    status = 1;
    Hwi_Instance_finalize(TEST_DPL_INT_NUM, status);
    /* Passing status as 2U in Hwi instance finalize */
    status = 2;
    Hwi_Instance_finalize(TEST_DPL_INT_NUM, status);

    /* Destruct hwi object with TEST_DPL_INT_NUM */
    Hwi_destruct(TEST_DPL_INT_NUM);

    /* Get stack info, passing computeStackDepth as true to get stack depth */
    status = Hwi_getCoreStackInfo(&stkInfo, true, CSL_CORE_ID_C75SS0_0);
    TEST_ASSERT_EQUAL_INT32((int32_t) false, status);

    /* Get stack info, passing computeStackDepth as false */
    status = Hwi_getCoreStackInfo(&stkInfo, false, CSL_CORE_ID_C75SS0_0);
    TEST_ASSERT_EQUAL_INT32((int32_t) false, status);
}

/**
 * \brief  Test function for DPL CSL Compute cluster Event Controller APIs.
 *
 * The test to CSL CLEC config event and event level, send and clear event with
 * provided parameters for positive and possible negative test cases.
 */
static void dpl_cslClec(void *args)
{
    CSL_CLEC_EVTRegs pRegs;
    CSL_ClecEventConfig evtCfg;
    int32_t status;
    uint32_t is_level;

    /* Providing NULL parameter */
    status = CSL_clecConfigEvent(NULL, CSL_CLEC_MAX_EVT_IN, &evtCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing NULL parameter */
    status = CSL_clecConfigEvent(&pRegs, CSL_CLEC_MAX_EVT_IN, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing CSL_CLEC_MAX_EVT_IN to evtNum */
    status = CSL_clecConfigEvent(&pRegs, CSL_CLEC_MAX_EVT_IN, &evtCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing CSL_CLEC_MAX_EXT_EVT_OUT to evtCfg.extEvtNum */
    evtCfg.extEvtNum = CSL_CLEC_MAX_EXT_EVT_OUT;
    status = CSL_clecConfigEvent(&pRegs, TEST_DPL_EVENT_NUM, &evtCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing CSL_CLEC_MAX_C7X_EVT_OUT to evtCfg.c7xEvtNum */
    evtCfg.c7xEvtNum = CSL_CLEC_MAX_C7X_EVT_OUT;
    status = CSL_clecConfigEvent(&pRegs, TEST_DPL_EVENT_NUM, &evtCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing 1U to is_level */
    is_level = 1U;
    status = CSL_clecConfigEventLevel(&pRegs, TEST_DPL_EVENT_NUM, is_level);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Providing NULL parameter */
    is_level = 0U;
    status = CSL_clecConfigEventLevel(NULL, CSL_CLEC_MAX_EVT_IN, is_level);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing CSL_CLEC_MAX_EVT_IN to evtNum */
    is_level = 0U;
    status = CSL_clecConfigEventLevel(&pRegs, CSL_CLEC_MAX_EVT_IN, is_level);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing valid parameters to CSL_clecSendEvent */
    status = CSL_clecSendEvent(&pRegs, TEST_DPL_EVENT_NUM);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Providing NULL parameter */
    status = CSL_clecSendEvent(NULL, CSL_CLEC_MAX_EVT_IN);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing CSL_CLEC_MAX_EVT_IN to evtNum */
    status = CSL_clecSendEvent(&pRegs, CSL_CLEC_MAX_EVT_IN);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing NULL parameter */
    status = CSL_clecClearEvent(NULL, CSL_CLEC_MAX_EVT_IN);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Providing CSL_CLEC_MAX_EVT_IN to evtNum */
    status = CSL_clecClearEvent(&pRegs, CSL_CLEC_MAX_EVT_IN);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}
#endif /* if defined (OS_FREERTOS) && (BUILD_C75X) */

#if defined(OS_SAFERTOS)

#if defined(__ARM_ARCH_7R__)
/* Dummy task main function */
static void dpl_taskMain(void *args)
{
    return;
}
#endif /* if defined (__ARM_ARCH_7R__) */

/**
 * \brief  Test function for DPL Hardware interrupt(HWI) APIs.
 *
 * The test to initialize and create a task, get task handle,
 * yield, disable, restore and delete task with provided
 * parameters for possible test cases.
 */
static void dpl_taskSafertos(void *args)
{
    TaskP_Object taskObj[TEST_DPL_LAST_TASK_OBJECT] = {0};
    uint32_t status;
    void *handle;
    uint32_t key;

    #if defined(__ARM_ARCH_7R__)
    TaskP_Params taskParams;
    TaskP_Load taskLoad;
    uint8_t i;
    
    for(i = TEST_DPL_INIT_TASK_OBJECT; i < TEST_DPL_LAST_TASK_OBJECT; i++)
    {
        /* Initializing task parameters */
        TaskP_Params_init(&taskParams);
        
        /* Create task */
        taskParams.stackSize = TEST_DPL_TASK_STACK_SIZE;
        taskParams.stack = gTaskStack[i];
        taskParams.priority = i;
        taskParams.taskMain = dpl_taskMain;
        status = TaskP_construct(&taskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_UINT32(SystemP_SUCCESS, status);
    }

    /* To get handle of task object */
    handle = TaskP_getHndl(&taskObj[TEST_DPL_INIT_TASK_OBJECT]);
    TEST_ASSERT_NOT_NULL(handle);

    /* To get task load statistics, not implemented in safertos */
    TaskP_loadGet(&taskObj[TEST_DPL_INIT_TASK_OBJECT], &taskLoad);

    for(i = TEST_DPL_INIT_TASK_OBJECT; i < TEST_DPL_LAST_TASK_OBJECT; i++)
    {
        /* Destroying task object */
        TaskP_destruct(&taskObj[i]);
    }

    /* Negative testing of task create with invalid priority */
    taskParams.stackSize = TEST_DPL_TASK_STACK_SIZE;
    taskParams.stack = gTaskStack[TEST_DPL_INIT_TASK_OBJECT];
    taskParams.priority = TEST_DPL_INVALID_TASK_PRIORITY;
    taskParams.taskMain = dpl_taskMain;
    status = TaskP_construct(&taskObj[TEST_DPL_INIT_TASK_OBJECT], &taskParams);
    TEST_ASSERT_EQUAL_UINT32(SystemP_FAILURE, status);

    /* Destroying unavailable task object to traverse task list and return */
    TaskP_destruct(&taskObj[TEST_DPL_INIT_TASK_OBJECT]);
    #endif /* if defined (__ARM_ARCH_7R__) */

    /* To get handle of task object */
    handle = TaskP_getHndl(&taskObj[TEST_DPL_INIT_TASK_OBJECT]);
    TEST_ASSERT_NULL(handle);

    /* Yield current task */
    TaskP_yield();

    /* Disable task */
    key = TaskP_disable();

    /* Restore task */
    TaskP_restore(key);

    /* Asserting task disable return outside critical section */
    TEST_ASSERT_EQUAL_UINT32(SystemP_SUCCESS, key);

    /* Passing NULL object to task destruct */
    TaskP_destruct(NULL);

    /* To get cpu load of all tasks, not implemented in safertos */
    status = TaskP_loadGetTotalCpuLoad();
    TEST_ASSERT_EQUAL_UINT32(SystemP_SUCCESS, status);

    /* Reset load statistics, not implemented in safertos */
    TaskP_loadResetAll();

    /* Update load statistics of all tasks, not implemented in safertos */
    TaskP_loadUpdateAll();
}

/* Safertos clock ISR function */
static void dpl_safertosClockIsr(void *args)
{
    /* Called clock setTimeout, start and stop from ISR */
    ClockP_setTimeout(&gClock, TEST_DPL_CLOCK_TIMEOUT_2);

    /* Start clock */
    ClockP_start(&gClock);

    /* Stop clock */
    ClockP_stop(&gClock);
}

/**
 * \brief  Test function for DPL clock APIs.
 *
 * The test to initialize and create a clock, get timeout,
 * start, stop and delete the clock with provided parameters
 * for positive and possible negative test cases.
 */
static void dpl_clockSafertos(void *args)
{
    ClockP_Params clockParams;
    HwiP_Object hwiObj;
    HwiP_Params hwiParams;
    uint32_t status;
    uint8_t once = TEST_DPL_ENABLE;
    uint16_t wait;
    uint32_t curTicks;
    uint64_t curTime;
    uint32_t timeout;
    gISR = 0;

    /* Invalid input to clockParams.timeout*/
    ClockP_Params_init(&clockParams);
    clockParams.timeout = TEST_DPL_INVALID_CLOCK_TIMEOUT;
    status = ClockP_construct(&gClock, &clockParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Initialize clock params with default values */
    ClockP_Params_init(&clockParams);

    /* Passing valid params for clock construct */
    clockParams.timeout = TEST_DPL_CLOCK_TIMEOUT_1;
    clockParams.callback = dpl_clockCallback;
    clockParams.args = args;
    /* To start clock inside ClockP_construct */
    clockParams.start = TEST_DPL_CLOCK_START;
    status = ClockP_construct(&gClock, &clockParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* An API is missing in clock get timeout, returns only default value */
    timeout = ClockP_getTimeout(&gClock);
    TEST_ASSERT_EQUAL_INT32(TEST_DPL_DEFAULT_TIMEOUT, timeout);

    /* test ticks to usec conversions */
    curTicks = ClockP_getTicks();
    curTime = ClockP_ticksToUsec(curTicks);
    TEST_ASSERT_EQUAL_UINT32(ClockP_usecToTicks(curTime), curTicks);

    /* Setting a new timeout to clock object */
    ClockP_setTimeout(&gClock, TEST_DPL_CLOCK_TIMEOUT_2);

    /* Start clock */
    ClockP_start(&gClock);

    /* Delay to wait for the clock to timeout and call ClockP_timerCallbackFunction */
    ClockP_usleep(3U * TEST_DPL_CLOCK_SLEEP_IN_USEC);

    /* Stop clock */
    ClockP_stop(&gClock);

    /* Check for callback execution */
    TEST_ASSERT_EQUAL_UINT32(1U, gISR);

    /* Destruct clock */
    ClockP_destruct(&gClock);

    ClockP_sleep(TEST_DPL_CLOCK_SLEEP_IN_SEC);

    /* Initialize clock params with default values */
    ClockP_Params_init(&clockParams);

    /* Passing valid params for clock construct */
    clockParams.timeout = TEST_DPL_CLOCK_TIMEOUT_2;
    clockParams.callback = dpl_clockCallback;
    clockParams.args = args;
    clockParams.start = TEST_DPL_CLOCK_START;
    clockParams.period = TEST_DPL_CLOCK_TIMEOUT_2;
    status = ClockP_construct(&gClock, &clockParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Delay to wait for the clock to timeout and call ClockP_timerCallbackFunction */
    wait = TEST_DPL_INIT_WAIT;
    while(wait < TEST_DPL_MAX_WAIT)
    {
        /* Check for clock is active */
        status = ClockP_isActive(&gClock);
        if(status && once)
        {
            /* Clock get timeout when clock is active */
            timeout = ClockP_getTimeout(&gClock);
            TEST_ASSERT_EQUAL_INT32(TEST_DPL_DEFAULT_TIMEOUT, timeout);

            once = TEST_DPL_DISABLE;
        }
        wait++;
    }

    /* Stop clock */
    ClockP_stop(&gClock);

    /* Destruct clock */
    ClockP_destruct(&gClock);

    ClockP_sleep(TEST_DPL_CLOCK_SLEEP_IN_SEC);

    /* Initialize clock params with default values */
    ClockP_Params_init(&clockParams);

    /* Passing valid params for clock construct */
    clockParams.timeout = TEST_DPL_CLOCK_TIMEOUT_2;
    clockParams.callback = NULL;
    clockParams.args = args;
    status = ClockP_construct(&gClock, &clockParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* To create an interrupt */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum = TEST_DPL_INT_NUM;
    hwiParams.callback = dpl_safertosClockIsr;
    hwiParams.args = NULL;
    hwiParams.eventId = HWIP_INVALID_EVENT_ID;
    status = HwiP_construct(&hwiObj, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* To trigger interrupt and call dpl_safertosClockIsr */
    HwiP_post(hwiParams.intNum);

    /* Delay to wait for ISR to execute */
    ClockP_usleep(TEST_DPL_CLOCK_SLEEP_IN_USEC / 2U);

    /* Destruct interrupt */
    HwiP_destruct(&hwiObj);

    /* Destruct clock */
    ClockP_destruct(&gClock);
}

/* Safertos debug ISR function */
static void dpl_safertosDebugIsr(void *args)
{
    char format[] = {"\r\nSample log for _DebugP_log\r\n"};
    int status;

    /* Negative testing of _DebugP_log in ISR, won't cause any failure and doesn't log anything */
    status = _DebugP_log(format);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    /* Negative testing of DebugP_log in ISR, won't cause any failure and doesn't log anything */
    DebugP_log(format);
}

/**
 * \brief  Test function for DPL debug API.
 *
 * The test to print debug log with provided
 * parameters for possible test cases.
 */
static void dpl_debugSafertos(void *args)
{
    char format[] = {"\r\nSample log to test Debug log\r\n"};
    int status;

    HwiP_Params hwiParams;
    HwiP_Object hwiObj;

    /* Log will printed, as not in ISR */
    status = _DebugP_log(format);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    /* Debug log call not from ISR */
    DebugP_log(format);

    /* To create an interrupt */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum = TEST_DPL_INT_NUM;
    hwiParams.callback = dpl_safertosDebugIsr;
    hwiParams.args = NULL;
    hwiParams.eventId = HWIP_INVALID_EVENT_ID;
    status = HwiP_construct(&hwiObj, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* To trigger an interrupt and call dpl_safertosDebugIsr */
    HwiP_post(hwiParams.intNum);

    /* Delay to wait for ISR to execute */
    ClockP_usleep(TEST_DPL_CLOCK_SLEEP_IN_USEC);

    HwiP_destruct(&hwiObj);
}

/* Safertos event ISR function */
static void dpl_safertosEventIsr(void *args)
{
    int32_t status;

    /* Negative testing of event setBits, clearBits and getBits from ISR */
    status = EventP_setBits(&gEvent, TEST_DPL_EVENT_BIT);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = EventP_clearBits(&gEvent, TEST_DPL_EVENT_BIT);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    status = EventP_getBits(&gEvent, &gIsrEventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}

#if defined(__ARM_ARCH_7R__) && !defined(BUILD_WKUP_R5)
/* Safertos event task ISR function */
static void dpl_eventTaskIsr(void *args)
{
    /* Set, clear and get event bits from ISR */
    gEventGetBitsStatusFromISR = EventP_getBits(&gEvent, &gEventGetBitsFromISR);
    gEventSet2StatusFromISR = EventP_setBits(&gEvent, TEST_DPL_EVENT_BIT2_FROM_ISR);
    gEventClearStatusFromISR = EventP_clearBits(&gEvent, TEST_DPL_EVENT_BIT2_FROM_ISR);
    gEventSetStatusFromISR = EventP_setBits(&gEvent, TEST_DPL_EVENT_BIT_FROM_ISR);
}

/* Safertos event task main function */
static void dpl_eventTaskMain(void *args)
{
    uint32_t eventBits;
    HwiP_Params hwiParams;
    HwiP_Object hwiObj;
    int32_t status;
    int8_t clearOnExit;
    int8_t waitForAll;

    /* Wait for event bits */
    clearOnExit = TEST_DPL_DISABLE;
    waitForAll = TEST_DPL_ENABLE;
    status = EventP_waitBits(&gEvent, TEST_DPL_EVENT_BIT_PING, clearOnExit, waitForAll, SystemP_WAIT_FOREVER, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_INT32(TEST_DPL_EVENT_BIT_PING, eventBits);

    /* Get event bits */
    status = EventP_getBits(&gEvent, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_INT32(TEST_DPL_EVENT_BIT_PING, eventBits);

    /* Set event bits */
    status = EventP_setBits(&gEvent, TEST_DPL_EVENT_BIT_PONG);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Initialize and construct interrupt */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum = TEST_DPL_INT_NUM;
    hwiParams.callback = dpl_eventTaskIsr;
    hwiParams.args = NULL;
    hwiParams.eventId = HWIP_INVALID_EVENT_ID;
    status = HwiP_construct(&hwiObj, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Post an interrupt to call dpl_eventTaskIsr */
    HwiP_post(hwiParams.intNum);

    /* Delay to wait for ISR to execute */
    ClockP_usleep(TEST_DPL_CLOCK_SLEEP_IN_USEC);

    /* Destruct interrupt */
    HwiP_destruct(&hwiObj);

    /* Task exit will destruct last created task */
    TaskP_exit();
}
#endif /* if defined (__ARM_ARCH_7R__) && !(BUILD_WKUP_R5)*/

/**
 * \brief  Test function for DPL event APIs.
 *
 * The test to construct an event and set bits, get bits,
 * clear bits and wait for bits to be set in an event with
 * provided parameters for negative test cases.
 */
static void dpl_eventSafertos(void *args)
{
    uint32_t eventBits;
    HwiP_Object hwiObj;
    HwiP_Params hwiParams;
    int32_t status;
    int8_t clearOnExit;
    int8_t waitForAll;

    #if defined(__ARM_ARCH_7R__) && !defined(BUILD_WKUP_R5)
    TaskP_Params taskParams;

    /* Construct event */
    status = EventP_construct(&gEvent);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Initialize task params */
    TaskP_Params_init(&taskParams);
    taskParams.name = "EVENT_TASK";
    taskParams.stackSize = TEST_DPL_TASK_STACK_SIZE;
    taskParams.stack = gTaskStack[TEST_DPL_INIT_TASK_OBJECT];
    taskParams.priority = TEST_DPL_EVENT_TASK_PRI;
    taskParams.args = NULL;
    taskParams.taskMain = dpl_eventTaskMain;

    /* Construct task */
    status = TaskP_construct(&gEventTask, &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Set event bits */
    status = EventP_setBits(&gEvent, TEST_DPL_EVENT_BIT_PING);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Get event bits */
    status = EventP_getBits(&gEvent, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_INT32(TEST_DPL_EVENT_BIT_PING, eventBits);

    /* Wait for event bits */
    status = EventP_waitBits(&gEvent, (TEST_DPL_EVENT_BIT_PING | TEST_DPL_EVENT_BIT_PONG | TEST_DPL_EVENT_BIT_FROM_ISR), 0, 1, SystemP_WAIT_FOREVER, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_INT32((TEST_DPL_EVENT_BIT_PING | TEST_DPL_EVENT_BIT_PONG | TEST_DPL_EVENT_BIT_FROM_ISR), eventBits);

    /* Clear event bits */
    status = EventP_clearBits(&gEvent, (TEST_DPL_EVENT_BIT_PING | TEST_DPL_EVENT_BIT_PONG | TEST_DPL_EVENT_BIT_FROM_ISR));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Assert global return variables from task and ISR */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, gEventSetStatusFromISR);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, gEventSet2StatusFromISR);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, gEventClearStatusFromISR);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, gEventGetBitsStatusFromISR);
    TEST_ASSERT_EQUAL_INT32((TEST_DPL_EVENT_BIT_PING | TEST_DPL_EVENT_BIT_PONG), gEventGetBitsFromISR);

    /* Destruct event */
    EventP_destruct(&gEvent);
    #endif /* if defined (__ARM_ARCH_7R__) && !(BUILD_WKUP_R5) */

    /* NULL param to event object get error returning SystemP_FAILURE */
    status = EventP_setBits(NULL, TEST_DPL_EVENT_BIT);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* NULL param to eventBits get error returning SystemP_FAILURE */
    status = EventP_getBits(&gEvent, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* NULL param to event object get error returning SystemP_FAILURE */
    status = EventP_getBits(NULL, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* NULL param to event object get error returning SystemP_FAILURE */
    status = EventP_clearBits(NULL, TEST_DPL_EVENT_BIT);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* NULL param to eventBits get error returning SystemP_FAILURE */
    clearOnExit = TEST_DPL_ENABLE;
    waitForAll = TEST_DPL_ENABLE;
    status = EventP_waitBits(&gEvent, TEST_DPL_EVENT_BIT, clearOnExit, waitForAll, SystemP_WAIT_FOREVER, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Invalid input given for bitsToWaitFor */
    clearOnExit = TEST_DPL_ENABLE;
    waitForAll = TEST_DPL_ENABLE;
    status = EventP_waitBits(&gEvent, TEST_DPL_INVALID_EVENT_BIT, clearOnExit, waitForAll, SystemP_WAIT_FOREVER, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Invalid input given for clearOnExit */
    clearOnExit = TEST_DPL_INVALID_CLEAR_ON_EXIT;
    waitForAll = TEST_DPL_ENABLE;
    status = EventP_waitBits(&gEvent, TEST_DPL_EVENT_BIT, clearOnExit, waitForAll, SystemP_WAIT_FOREVER, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Invalid input given for waitForAll */
    clearOnExit = TEST_DPL_ENABLE;
    waitForAll = TEST_DPL_INVALID_WAIT_FOR_ALL;
    status = EventP_waitBits(&gEvent, TEST_DPL_EVENT_BIT, clearOnExit, waitForAll, SystemP_WAIT_FOREVER, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* NULL param to event object get error returning SystemP_FAILURE */
    clearOnExit = TEST_DPL_ENABLE;
    waitForAll = TEST_DPL_ENABLE;
    status = EventP_waitBits(NULL, TEST_DPL_EVENT_BIT, clearOnExit, waitForAll, SystemP_WAIT_FOREVER, &eventBits);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* To create an interrupt */
    HwiP_Params_init(&hwiParams);
    hwiParams.intNum = TEST_DPL_INT_NUM;
    hwiParams.callback = dpl_safertosEventIsr;
    hwiParams.args = NULL;
    hwiParams.eventId = HWIP_INVALID_EVENT_ID;
    status = HwiP_construct(&hwiObj, &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* To trigger an interrupt and call dpl_safertosEventIsr */
    HwiP_post(hwiParams.intNum);

    /* Delay to wait for ISR to execute */
    ClockP_usleep(TEST_DPL_CLOCK_SLEEP_IN_USEC);

    /* Destruct interrupt */
    HwiP_destruct(&hwiObj);

    /* NULL param to event object for negative condition */
    EventP_destruct(NULL);
}

/**
 * \brief  Test function for DPL Hardware interrupt(HWI) APIs.
 *
 * The test to initialize and create a HWI, post, set args,
 * disable int, enable int, restore int and delete the HWI
 * with provided parameters for possible test cases.
 */
#if defined(__ARM_ARCH_7R__)
static void dpl_hwipArmv7rSafertos(void *args)
{
    HwiP_Params HwiParams;
    HwiP_Object HwiObject;
    int32_t status;
    uint32_t oldIntState;
    gISR = 0;
    gInISR = 0;

    /* Setup interrupt and enable it */
    HwiP_Params_init(&HwiParams);

    /* Passing valid parameters for HwiP_construct */
    HwiParams.intNum = TEST_DPL_INT_NUM;
    HwiParams.callback = dpl_hwipCallback;
    HwiParams.isFIQ = TEST_DPL_DISABLE;
    HwiParams.isPulse = TEST_DPL_HWI_PULSE;
    status = HwiP_construct(&HwiObject, &HwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Posted interrupt to call dpl_hwipCallback */
    HwiP_post(HwiParams.intNum);

    /* Check for callback execution */
    TEST_ASSERT_EQUAL_UINT32(1U, gISR);

    /* Check for interrupt in ISR */
    TEST_ASSERT_EQUAL_UINT32(1U, gInISR);

    /* Destructing HwiP_Object */
    HwiP_destruct(&HwiObject);

    /* Setup interrupt and enable it */
    HwiP_Params_init(&HwiParams);

    /* Passing valid parameters for HwiP_construct */
    HwiParams.intNum = TEST_DPL_INT_NUM;
    HwiParams.callback = dpl_hwipCallback;
    HwiParams.isFIQ = TEST_DPL_DISABLE;
    HwiParams.isPulse = TEST_DPL_HWI_LEVEL;
    status = HwiP_construct(&HwiObject, &HwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Set args to pass to the callback function */
    status = HwiP_setArgs(&HwiObject, args);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Posted interrupt to call dpl_hwipCallback */
    HwiP_post(HwiParams.intNum);

    /* Check for callback execution */
    TEST_ASSERT_EQUAL_UINT32(2U, gISR);

    /* Check for interrupt in ISR */
    TEST_ASSERT_EQUAL_UINT32(2U, gInISR);

    /* Disables interrupt and returns interrupt's last state */
    oldIntState = HwiP_disableInt(HwiParams.intNum);
    TEST_ASSERT_EQUAL_UINT32(TEST_DPL_HWI_ENABLED, oldIntState);

    /* Interrupt already disabled, disabling it again */
    TEST_ASSERT_EQUAL_UINT32(TEST_DPL_HWI_DISABLED, HwiP_disableInt(HwiParams.intNum));

    /* Restoring interrupt with HwiP_disableInt returning 0U */
    HwiP_restoreInt(HwiParams.intNum, HwiP_disableInt(HwiParams.intNum));

    /* Restoring interrupt with old interrupt value */
    HwiP_restoreInt(HwiParams.intNum, oldIntState);

    HwiP_destruct(&HwiObject);

    /* Setup interrupt and enable it */
    HwiP_Params_init(&HwiParams);

    /* Passing valid parameters for FIQ interrupt to HwiP_construct */
    HwiParams.intNum = TEST_DPL_INT_NUM;
    HwiParams.callback = dpl_hwipCallback;
    HwiParams.isFIQ = TEST_DPL_ENABLE;
    HwiParams.isPulse = TEST_DPL_HWI_LEVEL;
    status = HwiP_construct(&HwiObject, &HwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    HwiP_destruct(&HwiObject);
}
#endif /* if defined (__ARM_ARCH_7R__) */

/**
 * \brief  Test function for DPL clock APIs.
 *
 * The test to get clock timer count value and compare
 * to value of timer get count.
 * Both values should be equal before starting the timer.
 */
#if defined (BUILD_C75X)
static void dpl_clockpC75(void *args)
{
    uint32_t timerBaseAddr = CSL_MCU_TIMER1_CFG_BASE;
    uint32_t timerCount;

    timerCount = ClockP_getTimerCount(timerBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(TimerP_getCount(timerBaseAddr), timerCount);

    ClockP_timerClearOverflowInt(timerBaseAddr);
}

/**
 * \brief  Test function for DPL hardware interrupt APIs.
 *
 * The test to create and delete HWI with provided parameters
 * for possible test cases.
 */
static void dpl_hwipC75(void *args)
{
    HwiP_Object hwiObj[TEST_DPL_LAST_HWI_OBJECT];
    HwiP_Params hwiParams;
    int32_t status;
    uintptr_t key;
    int8_t i;

    for(i = TEST_DPL_INIT_HWI_OBJECT; i < TEST_DPL_LAST_HWI_OBJECT; i++)
    {
        hwiParams.callback = dpl_hwipCallback;
        hwiParams.args = NULL;
        hwiParams.eventId = HWIP_INVALID_EVENT_ID;
        hwiParams.isPulse = TEST_DPL_HWI_LEVEL;
        hwiParams.intNum = i;
        hwiParams.priority = i;
        status = HwiP_construct(&hwiObj[i], &hwiParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        if(i == TEST_DPL_INIT_HWI_OBJECT)
        {
            /* Negtive testing of hwip construct, creating interrupt with same intNum to fail internally from creating an interrupt */
            hwiParams.callback = dpl_hwipCallback;
            hwiParams.args = NULL;
            hwiParams.eventId = HWIP_INVALID_EVENT_ID;
            hwiParams.isPulse = TEST_DPL_HWI_LEVEL;
            hwiParams.intNum = i;
            hwiParams.priority = i;
            status = HwiP_construct(&hwiObj[i], &hwiParams);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        }
    }

    /* Disable interrupt */
    key = HwiP_disable();

    /* Restore interrupt */
    HwiP_restore(key);

    /* Assert disable interrupt return outside critical section */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, key);

    status = HwiP_inISR();
    TEST_ASSERT_EQUAL_INT32(TEST_DPL_SYSTEM_MODE, status);

    /* Destructing Hwi objects */
    for(i = TEST_DPL_INIT_HWI_OBJECT; i < TEST_DPL_LAST_HWI_OBJECT; i++)
    {
        HwiP_destruct(&hwiObj[i]);
    }

    /* Negative testing of hwip construct with max event ID to fail internally from creating an interrupt */
    hwiParams.callback = dpl_hwipCallback;
    hwiParams.args = NULL;
    hwiParams.eventId = CSL_CLEC_MAX_EVT_IN;
    hwiParams.isPulse = TEST_DPL_HWI_PULSE;
    hwiParams.intNum = TEST_DPL_INT_NUM;
    hwiParams.priority = 1U;
    status = HwiP_construct(&hwiObj[TEST_DPL_INIT_HWI_OBJECT], &hwiParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}
#endif /* if defined (BUILD_C75X) */
#endif /* if defined (OS_SAFERTOS) */
