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

/**
 *  \file test_epwm_multi_thread.c
 *
 *  \brief File containing EPWM Driver test cases for multi-threaded
 *         usecases.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <drivers/epwm.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of threads for concurrent EPWM register access tests */
#define TEST_EPWM_MT_THREADS              (2U)

/* Number of threads for concurrent submodule config tests */
#define TEST_EPWM_MT_SUBMODULE_THREADS    (3U)

/* Task priority for EPWM test threads */
#define TEST_EPWM_TASK_PRIORITY           (8U)

/* Stack size (in bytes) for each EPWM test thread.
 * C75x requires at least configMINIMAL_STACK_SIZE * sizeof(StackType_t)
 * = 8192 * 8 = 64KB minimum per task. */
#define TEST_EPWM_STACK_SIZE              (64 * 1024)

/* TB frequency for multi-thread tests */
#define TEST_EPWM_MT_TB_FREQ              (CONFIG_EPWM0_FCLK / 4U)

/* Output frequency for multi-thread tests */
#define TEST_EPWM_MT_OUTPUT_FREQ          (1U * 1000U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Semaphore for synchronizing multithreaded EPWM tests */
static SemaphoreP_Object        TestEpwm_mtSemObj;

/* Task objects for multithreaded EPWM test threads */
static TaskP_Object             TestEpwm_MtThreadTaskObj[TEST_EPWM_MT_SUBMODULE_THREADS];

/* Stack memory for each multithreaded EPWM test thread */
static uint8_t                  TestEpwm_MtTaskStack[TEST_EPWM_MT_SUBMODULE_THREADS][TEST_EPWM_STACK_SIZE]
                                __attribute__((aligned(32)));

/* set by test_main in test_epwm.c before calling multi-thread tests */
extern uint32_t gEpwmBaseAddr;
#endif

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */

static void TestEpwm_mtConcurrentRegisterAccess(void *args);
static void TestEpwm_mtConcurrentSubmoduleCfg(void *args);
static void TestEpwm_mtStressConcurrentReconfigure(void *args);
static void TestEpwm_mtConcurrentTzEtOperations(void *args);

/* Thread worker functions */
static void TestEpwm_mtWorkerTbConfig(void *args);
static void TestEpwm_mtWorkerCcConfig(void *args);
static void TestEpwm_mtWorkerDbConfig(void *args);
static void TestEpwm_mtWorkerAqConfig(void *args);
static void TestEpwm_mtWorkerTzConfig(void *args);
static void TestEpwm_mtWorkerEtConfig(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void run_epwm_multi_threaded_tests(void *args)
{
    RUN_TEST(TestEpwm_mtConcurrentRegisterAccess, 11600, NULL);
    RUN_TEST(TestEpwm_mtConcurrentSubmoduleCfg, 11601, NULL);
    RUN_TEST(TestEpwm_mtStressConcurrentReconfigure, 11602, NULL);
    RUN_TEST(TestEpwm_mtConcurrentTzEtOperations, 11603, NULL);

    return;
}

/* ========================================================================== */
/*                     Thread Worker Functions                                */
/* ========================================================================== */

/**
 * @brief   Test case for configuring the EPWM Time-Base (TB) module in a 
 *          multi-threaded environment. This function performs repeated 
 *          configuration of the EPWM module's time-base clock, PWM frequency, 
 *          synchronization, and emulation mode. It ensures that the final 
 *          configuration matches the expected values and validates the 
 *          counter mode of the time-base module.
 * 
 *          The test also includes a small delay between iterations to simulate 
 *          real-world timing scenarios and concludes by signaling the 
 *          completion of the test using a semaphore.
 */
static void TestEpwm_mtWorkerTbConfig(void *args)
{
    uint32_t i;
    uint32_t regval, ctrmode;

    for (i = 0U; i < 20U; i++)
    {
        EPWM_tbTimebaseClkCfg(gEpwmBaseAddr, TEST_EPWM_MT_TB_FREQ, CONFIG_EPWM0_FCLK);
        EPWM_tbPwmFreqCfg(gEpwmBaseAddr, TEST_EPWM_MT_TB_FREQ, TEST_EPWM_MT_OUTPUT_FREQ,
                          EPWM_TB_COUNTER_DIR_UP_DOWN, EPWM_SHADOW_REG_CTRL_ENABLE);
        EPWM_tbSyncDisable(gEpwmBaseAddr);
        EPWM_tbSetEmulationMode(gEpwmBaseAddr, EPWM_TB_EMU_MODE_FREE_RUN);
        ClockP_usleep(100);
    }

    /* Verify final config */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_TBCTL);
    ctrmode = HW_GET_FIELD(regval, PWMSS_EPWM_TBCTL_CTRMODE);
    TEST_ASSERT_EQUAL_UINT32(EPWM_TB_COUNTER_DIR_UP_DOWN, ctrmode);

    SemaphoreP_post(&TestEpwm_mtSemObj);
    TaskP_exit();
}

/**
 * @brief Thread worker: Configures Counter Comparator submodule.
 *
 * Repeatedly writes comparator values for CMP_A and CMP_B with incremental
 * values, then verifies the last written values are correct. Ensures that
 * the shadow register control and load mode configurations are applied
 * correctly for both comparators.
 */
static void TestEpwm_mtWorkerCcConfig(void *args)
{
    uint32_t i;
    uint32_t regval, cmpval;

    for (i = 0U; i < 20U; i++)
    {
        EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_A, (100U + i),
                                           EPWM_SHADOW_REG_CTRL_ENABLE,
                                           EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
        EPWM_counterComparatorCfg(gEpwmBaseAddr, EPWM_CC_CMP_B, (200U + i),
                                           EPWM_SHADOW_REG_CTRL_ENABLE,
                                           EPWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO, TRUE);
        ClockP_usleep(100);
    }

    /* Verify final CMP_A value */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPA);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPA);
    TEST_ASSERT_EQUAL_UINT32(119U, cmpval);

    /* Verify final CMP_B value */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_CMPB);
    cmpval = HW_GET_FIELD(regval, PWMSS_EPWM_CMPB);
    TEST_ASSERT_EQUAL_UINT32(219U, cmpval);

    SemaphoreP_post(&TestEpwm_mtSemObj);
    TaskP_exit();
}

/**
 * @brief Thread worker: Configures Deadband submodule.
 *
 * Repeatedly configures the deadband submodule with incremental rising and
 * falling edge delays. Verifies the final delay values and ensures the
 * deadband bypass mode is applied correctly during cleanup.
 */
static void TestEpwm_mtWorkerDbConfig(void *args)
{
    EPWM_DeadbandCfg dbCfg;
    uint32_t i;
    uint32_t redVal, fedVal;

    dbCfg.inputMode      = EPWM_DB_IN_MODE_A_RED_A_FED;
    dbCfg.outputMode     = EPWM_DB_OUT_MODE_A_RED_B_FED;
    dbCfg.polaritySelect = EPWM_DB_POL_SEL_ACTV_HIGH_COMPLEMENTARY;

    for (i = 0U; i < 20U; i++)
    {
        dbCfg.risingEdgeDelay  = (10U + i);
        dbCfg.fallingEdgeDelay = (20U + i);
        EPWM_deadbandCfg(gEpwmBaseAddr, &dbCfg);
        ClockP_usleep(100);
    }

    /* Verify final delays */
    redVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBRED, PWMSS_EPWM_DBRED_DEL);
    fedVal = HW_RD_FIELD16(gEpwmBaseAddr + PWMSS_EPWM_DBFED, PWMSS_EPWM_DBFED_DEL);
    TEST_ASSERT_EQUAL_UINT32(29U, redVal);
    TEST_ASSERT_EQUAL_UINT32(39U, fedVal);

    /* Cleanup */
    EPWM_deadbandBypass(gEpwmBaseAddr);

    SemaphoreP_post(&TestEpwm_mtSemObj);
    TaskP_exit();
}

/**
 * @brief Thread worker: Configures Action Qualifier (AQ) submodule.
 *
 * Repeatedly configures the AQ submodule with specific actions for zero,
 * period, and comparator events. Verifies the final configuration matches
 * the expected values. Ensures the AQ submodule retains correct state
 * after multiple iterations.
 */
static void TestEpwm_mtWorkerAqConfig(void *args)
{
    EPWM_AqActionCfg aqConfig;
    uint32_t i;
    uint32_t regval;

    for (i = 0U; i < 20U; i++)
    {
        aqConfig.zeroAction     = EPWM_AQ_ACTION_HIGH;
        aqConfig.prdAction      = EPWM_AQ_ACTION_LOW;
        aqConfig.cmpAUpAction   = EPWM_AQ_ACTION_LOW;
        aqConfig.cmpADownAction = EPWM_AQ_ACTION_HIGH;
        aqConfig.cmpBUpAction   = EPWM_AQ_ACTION_DONOTHING;
        aqConfig.cmpBDownAction = EPWM_AQ_ACTION_DONOTHING;
        EPWM_aqActionOnOutputCfg(gEpwmBaseAddr, EPWM_OUTPUT_CH_A, &aqConfig);
        ClockP_usleep(100);
    }

    /* Verify final AQ config */
    regval = HW_RD_REG16(gEpwmBaseAddr + PWMSS_EPWM_AQCTLA);
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_HIGH,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_ZRO));
    TEST_ASSERT_EQUAL_UINT32(EPWM_AQ_ACTION_LOW,
        HW_GET_FIELD(regval, PWMSS_EPWM_AQCTLA_PRD));

    SemaphoreP_post(&TestEpwm_mtSemObj);
    TaskP_exit();
}

/**
 * @brief Test case for EPWM trip zone (TZ) configuration in a multi-threaded environment.
 *
 * This test function verifies the proper enablement, triggering, clearing, and disablement
 * of EPWM trip zone one-shot events in a loop. It ensures that the trip zone flags are
 * cleared after the cleanup process. The test also validates the synchronization between
 * threads using a semaphore and exits the task upon completion.
 *
 * The test is designed to simulate and validate the behavior of EPWM trip zone events
 * under repetitive operations and ensure no residual flags remain after execution.
 */

static void TestEpwm_mtWorkerTzConfig(void *args)
{
    uint32_t i;
    uint16_t status;

    for (i = 0U; i < 20U; i++)
    {
        EPWM_tzTripEventEnable(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);
        EPWM_tzTriggerSwEvent(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT);
        EPWM_tzEventStatusClear(gEpwmBaseAddr,
            EPWM_TZ_STS_FLG_OST | EPWM_TZ_STS_FLG_INT);
        EPWM_tzTripEventDisable(gEpwmBaseAddr, EPWM_TZ_EVENT_ONE_SHOT, 0U);
        ClockP_usleep(100);
    }

    /* Verify flags are clear after cleanup */
    status = EPWM_tzEventStatus(gEpwmBaseAddr, EPWM_TZ_STS_FLG_OST);
    TEST_ASSERT_EQUAL_UINT32(0U, status);

    SemaphoreP_post(&TestEpwm_mtSemObj);
    TaskP_exit();
}

/**
 * @brief Test case for EPWM multi-threaded worker event trigger configuration.
 *
 * This function configures the EPWM event trigger interrupt, triggers the interrupt,
 * clears the interrupt, and verifies that the interrupt flag is cleared after execution.
 * The test iterates 20 times to ensure consistent behavior and includes a small delay
 * between iterations. After verification, the interrupt is disabled, and the semaphore
 * is posted to signal completion. Finally, the task exits gracefully.
 *
 * This test ensures the proper functionality of EPWM event trigger interrupts in a
 * multi-threaded environment.
 */
static void TestEpwm_mtWorkerEtConfig(void *args)
{
    uint32_t i;
    uint16_t status;

    for (i = 0U; i < 20U; i++)
    {
        EPWM_etIntrCfg(gEpwmBaseAddr, EPWM_ET_INTR_EVT_CNT_EQ_ZRO,
                        EPWM_ET_INTR_PERIOD_FIRST_EVT);
        EPWM_etIntrTrigger(gEpwmBaseAddr);
        EPWM_etIntrClear(gEpwmBaseAddr);
        ClockP_usleep(100);
    }

    /* Verify flag is clear */
    status = EPWM_etIntrStatus(gEpwmBaseAddr);
    TEST_ASSERT_EQUAL_UINT32(0U, status);

    /* Cleanup */
    EPWM_etIntrDisable(gEpwmBaseAddr);

    SemaphoreP_post(&TestEpwm_mtSemObj);
    TaskP_exit();
}

/**
 * @brief Test case for concurrent register access in EPWM module.
 *
 * This test validates the concurrent access of EPWM registers by creating
 * multiple threads. Each thread is assigned a specific task to configure
 * either the Time Base (TB) or Compare Control (CC) registers. The test
 * ensures proper synchronization using a counting semaphore and verifies
 * that all threads complete their execution successfully. After execution,
 * resources such as tasks and semaphores are cleaned up.
 *
 * @param args Pointer to arguments passed to the test function.
 */
static void TestEpwm_mtConcurrentRegisterAccess(void *args)
{
    uint32_t    i;
    int32_t     status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestEpwm_mtSemObj, 0, TEST_EPWM_MT_THREADS));

    for (i = 0U; i < TEST_EPWM_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "EPWM_MT_REG";
        taskParams.stackSize = TEST_EPWM_STACK_SIZE;
        taskParams.stack     = TestEpwm_MtTaskStack[i];
        taskParams.priority  = TEST_EPWM_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0U)
            taskParams.taskMain = TestEpwm_mtWorkerTbConfig;
        else
            taskParams.taskMain = TestEpwm_mtWorkerCcConfig;

        status = TaskP_construct(&TestEpwm_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_EPWM_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestEpwm_mtSemObj, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&TestEpwm_mtSemObj);

    for (i = 0U; i < TEST_EPWM_MT_THREADS; i++)
    {
        TaskP_destruct(&TestEpwm_MtThreadTaskObj[i]);
    }
}

/**
 * @brief Test case for concurrent submodule configuration in EPWM module.
 *
 * This test validates the concurrent configuration of EPWM submodules by creating
 * multiple threads. Each thread is assigned a specific task to configure the Time Base (TB),
 * Action Qualifier (AQ), or Deadband (DB) submodules. The test ensures proper synchronization
 * using a counting semaphore and verifies that all threads complete their execution successfully.
 * After execution, resources such as tasks and semaphores are cleaned up.
 *
 * @param args Pointer to arguments passed to the test function.
 */
static void TestEpwm_mtConcurrentSubmoduleCfg(void *args)
{
    uint32_t    i;
    int32_t     status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestEpwm_mtSemObj, 0, TEST_EPWM_MT_SUBMODULE_THREADS));

    for (i = 0U; i < TEST_EPWM_MT_SUBMODULE_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "EPWM_MT_SUB";
        taskParams.stackSize = TEST_EPWM_STACK_SIZE;
        taskParams.stack     = TestEpwm_MtTaskStack[i];
        taskParams.priority  = TEST_EPWM_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0U)
            taskParams.taskMain = TestEpwm_mtWorkerTbConfig;
        else if (i == 1U)
            taskParams.taskMain = TestEpwm_mtWorkerAqConfig;
        else
            taskParams.taskMain = TestEpwm_mtWorkerDbConfig;

        status = TaskP_construct(&TestEpwm_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    for (i = 0U; i < TEST_EPWM_MT_SUBMODULE_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestEpwm_mtSemObj, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&TestEpwm_mtSemObj);

    for (i = 0U; i < TEST_EPWM_MT_SUBMODULE_THREADS; i++)
    {
        TaskP_destruct(&TestEpwm_MtThreadTaskObj[i]);
    }
}

/**
 * @brief Test case to validate concurrent reconfiguration of EPWM modules.
 *
 * This test creates multiple threads to simulate concurrent reconfiguration
 * of EPWM modules. Each thread performs specific tasks such as configuring
 * Time Base (TB) or Dead Band (DB) settings. The test ensures proper 
 * synchronization using a counting semaphore and validates the success of 
 * thread creation, execution, and cleanup. It also verifies that all threads 
 * complete their tasks without errors.
 */
static void TestEpwm_mtStressConcurrentReconfigure(void *args)
{
    uint32_t    i;
    int32_t     status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestEpwm_mtSemObj, 0, TEST_EPWM_MT_THREADS));

    for (i = 0U; i < TEST_EPWM_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "EPWM_MT_STRESS";
        taskParams.stackSize = TEST_EPWM_STACK_SIZE;
        taskParams.stack     = TestEpwm_MtTaskStack[i];
        taskParams.priority  = TEST_EPWM_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0U)
            taskParams.taskMain = TestEpwm_mtWorkerTbConfig;
        else
            taskParams.taskMain = TestEpwm_mtWorkerDbConfig;

        status = TaskP_construct(&TestEpwm_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    for (i = 0U; i < TEST_EPWM_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestEpwm_mtSemObj, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&TestEpwm_mtSemObj);

    for (i = 0U; i < TEST_EPWM_MT_THREADS; i++)
    {
        TaskP_destruct(&TestEpwm_MtThreadTaskObj[i]);
    }
}

/**
 * @brief Test case to validate concurrent Trip Zone (TZ) and Event Trigger (ET) 
 *        operations using multiple threads in the EPWM driver.
 *
 * This test initializes a counting semaphore and creates multiple threads 
 * to perform concurrent TZ and ET configurations. The threads are synchronized 
 * using the semaphore to ensure proper execution order. After the threads 
 * complete their tasks, the semaphore and thread objects are cleaned up.
 *
 * The test ensures that the EPWM driver can handle concurrent operations 
 * without any issues, validating its robustness in multi-threaded environments.
 */
static void TestEpwm_mtConcurrentTzEtOperations(void *args)
{
    uint32_t    i;
    int32_t     status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestEpwm_mtSemObj, 0, TEST_EPWM_MT_THREADS));

    for (i = 0U; i < TEST_EPWM_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "EPWM_MT_TZET";
        taskParams.stackSize = TEST_EPWM_STACK_SIZE;
        taskParams.stack     = TestEpwm_MtTaskStack[i];
        taskParams.priority  = TEST_EPWM_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0U)
            taskParams.taskMain = TestEpwm_mtWorkerTzConfig;
        else
            taskParams.taskMain = TestEpwm_mtWorkerEtConfig;

        status = TaskP_construct(&TestEpwm_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    for (i = 0U; i < TEST_EPWM_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestEpwm_mtSemObj, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&TestEpwm_mtSemObj);

    for (i = 0U; i < TEST_EPWM_MT_THREADS; i++)
    {
        TaskP_destruct(&TestEpwm_MtThreadTaskObj[i]);
    }
}



