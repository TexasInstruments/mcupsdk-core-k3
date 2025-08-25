/*
 * Copyright (C) 2025 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/soc.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Testcases */
static void test_soc_coverage(void *args);
void test_soc_main(void *);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define PSC_MODSTATE_ENABLE         (0x3U)
#define PSC_TIMEOUT                 (1000U)
#define MODULE_NUM                  (1U)
#define DOMAIN_NUM                  (1U)
#define INVALID_SOC_PSC_DOMAIN_ID   (2U)
#define CLK_RATE                    (0U)
#define EPWM_INSTNUM                (1U)
#define NUM_PARTITION               (1U)
#define RESETCAUSE_VALUE            (1U)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_soc_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(test_soc_coverage, 8034, NULL);

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

static void test_soc_coverage(void *args)
{
    uint32_t i;
    int32_t retValue;
    const char * coreName;
    uint32_t value = 1;
    uint32_t bootMode = 0x00DC;
    uint32_t enable = 0;

    DebugP_log("\r\n soc dynamic coverage test...\r\n");
    /* Getting core name from core ID */
    for(i = 0; i <= CSL_CORE_ID_MAX; i++)
    {
        coreName= SOC_getCoreName(i);
        DebugP_log("Core name: %s\r\n",coreName);
#if defined(SOC_AM62AX) || defined(SOC_AM62PX)
        retValue=SOC_getCoreId(coreName);
        if ( i < CSL_CORE_ID_MAX )
        {
            DebugP_log("Core ID: %d\r\n",retValue);
        }
        else
        {
            DebugP_log("Invalid coreID");
        }
#endif
    }

    /* Setting module frequency with a parent */
#if defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62X)
    retValue = SOC_moduleSetClockFrequencyWithParent(TISCI_DEV_WKUP_I2C0,TISCI_DEV_WKUP_I2C0_CLK,TISCI_DEV_WKUP_I2C0_CLK_PARENT_HSDIV4_16FFT_MCU_0_HSDIVOUT0_CLK,CLK_RATE);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retValue);
#endif

    /* Enabling epwm clock and lock the control module partition */
    SOC_setEpwmTbClk(EPWM_INSTNUM,TRUE);
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN,NUM_PARTITION);

    /* Disabling epwm clock and lock the control module NUM_PARTITION */
    SOC_setEpwmTbClk(EPWM_INSTNUM,FALSE);
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN,NUM_PARTITION);

    /* Reading module clock frequency */
#if defined(SOC_AM62AX) || defined(SOC_AM62X)
      retValue = SOC_moduleGetClockFrequency(TISCI_DEV_CMP_EVENT_INTROUTER0,TISCI_DEV_CMP_EVENT_INTROUTER0_INTR_CLK,NULL);
      TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retValue);
#elif defined(SOC_AM62PX)
      retValue = SOC_moduleGetClockFrequency(TISCI_DEV_DBGSUSPENDROUTER0,TISCI_DEV_DBGSUSPENDROUTER0_INTR_CLK,NULL);
      TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retValue);
#endif

    /* Changing to boot mode */
    SOC_setDevStat(bootMode);

    /* Generating the MCU IPC interrupt to DM R5 to wakeup the main domain from MCU */
    SOC_triggerMcuLpmWakeup();

    /* Resetting the Reason Source Mcu Domain */
    SOC_getWarmResetCauseMcuDomain();

    /* Clear the reset reason */
    SOC_clearResetCauseMainMcuDomain(RESETCAUSE_VALUE);

    /* Reading PSC state for main domain */
    retValue = SOC_getPSCState(SOC_PSC_DOMAIN_ID_MAIN,DOMAIN_NUM,MODULE_NUM,SOC_PSC_DOMAIN_OFF,SOC_PSC_SYNCRESETDISABLE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retValue);

    /* Reading PSC state for mcu domain */
    retValue = SOC_getPSCState(SOC_PSC_DOMAIN_ID_MCU,DOMAIN_NUM,MODULE_NUM,SOC_PSC_DOMAIN_OFF,SOC_PSC_SYNCRESETDISABLE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retValue);

    /* Reading PSC state by passing invalid instNum */
    retValue = SOC_getPSCState(INVALID_SOC_PSC_DOMAIN_ID,DOMAIN_NUM,MODULE_NUM,SOC_PSC_DOMAIN_OFF,SOC_PSC_SYNCRESETDISABLE);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retValue);

    /* Setting PSC state for main domain */
    retValue = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MAIN,DOMAIN_NUM,MODULE_NUM,PSC_MODSTATE_ENABLE);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retValue);

    /* Setting PSC state for mcu domain */
    retValue = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU,DOMAIN_NUM,MODULE_NUM,PSC_TIMEOUT);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retValue);

    /* Setting MCU reset isolation flag */
    SOC_setMCUResetIsolationDone(value);

    value = 0;
    SOC_setMCUResetIsolationDone(value);

    /* Unlocks the control MMRs */
    SOC_unlockAllMMR();

    /* Updating the boot block size for FSS subsystem */
    SOC_setFSSCtrlFlashBootSize();

    /* Getting Physical Address from virtual address */
    Soc_getPhyAddr(value);

    /* Disable clock to I2C module */
    retValue = SOC_moduleClockEnable(TISCI_DEV_I2C0,enable);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retValue);

    /* Enable clock to I2C module */
    enable = 1;
    retValue = SOC_moduleClockEnable(TISCI_DEV_I2C0,enable);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retValue);

    /* Setting module frequency */
    retValue = SOC_moduleSetClockFrequency(TISCI_DEV_WKUP_I2C0,TISCI_DEV_WKUP_I2C0_CLK,CLK_RATE);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, retValue);

    DebugP_log("\r\n soc dynamic coverage test: PASS \r\n");
}
