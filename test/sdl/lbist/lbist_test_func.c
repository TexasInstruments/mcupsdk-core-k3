/*
 *  Copyright (C) 2023-2025 Texas Instruments Incorporated
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
 *  \file     lbist_test_func.c
 *
 *  \brief    This file contains LBIST functional test code. .
 *
 *  \details  LBIST Functional tests
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_lbist.h>
#include <sdl/lbist/v0/sdl_ip_lbist.h>
#include <drivers/sciclient.h>
#include <drivers/device_manager/sciclient.h>
#include <drivers/soc.h>
#include <sdl/include/hw_types.h>

#if defined (SOC_AM62X)
#include <sdl/include/am62x/sdlr_mcu_ctrl_mmr.h>
#include <sdl/include/am62x/sdlr_soc_baseaddress.h>
#include <drivers/sciclient/include/tisci/am62x/tisci_clocks.h>
#endif

#if defined (SOC_AM62AX)
#include <sdl/include/am62ax/sdlr_mcu_ctrl_mmr.h>
#include <sdl/include/am62ax/sdlr_soc_baseaddress.h>
#include <drivers/sciclient/include/tisci/am62ax/tisci_clocks.h>
#endif

#if defined (SOC_AM62DX)
#include <sdl/include/am62dx/sdlr_mcu_ctrl_mmr.h>
#include <sdl/include/am62dx/sdlr_soc_baseaddress.h>
#include <drivers/sciclient/include/tisci/am62dx/tisci_clocks.h>
#endif

#if defined (SOC_J722S)
#include <sdl/include/j722s/sdlr_mcu_ctrl_mmr.h>
#include <sdl/include/j722s/sdlr_soc_baseaddress.h>
#include <drivers/sciclient/include/tisci/j722s/tisci_clocks.h>
#endif

#include <sdl/dpl/sdl_dpl.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/ClockP.h>
#include "lbist_test_cfg.h"

/* #define DEBUG */

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* HW POST run status definitions */
#define LBIST_POST_COMPLETED_SUCCESS      (0u)
#define LBIST_POST_COMPLETED_FAILURE      (1u)
#define LBIST_POST_ATTEMPTED_TIMEOUT      (2u)
#define LBIST_POST_NOT_RUN                (3u)
#define SCICLIENT_SERVICE_WAIT_FOREVER    (0xFFFFFFFFU)

#define LBIST_PSC_NEXT_MASK               (0x0000003F)
#define LBIST_PSC_FORCE_OFF               (0x80000000)
#define LBIST_PSC_FORCE_ON                (0x80000003)
#define LBIST_PSC_PTCMD_TIMEOUT           (1000000U)

#define DSB_ENABLE                        asm("dsb")
#define ISB_ENABLE                        asm("isb")

#define LBIST_WKUP_PSC_BASE     (0x04000000)
#define LBIST_MAIN_PSC_BASE     (0x00400000)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
int32_t LBIST_runTest(uint32_t coreIndex);
int32_t LBIST_funcTest(void);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static int32_t LBIST_PSCForceBit(uint32_t pscDomain, uint32_t pscPD, uint32_t pscID, bool powerOn)
{
    int32_t result = SDL_PASS;
    int32_t pscTimeout = LBIST_PSC_PTCMD_TIMEOUT;
    uint32_t pdShift = (1<<pscPD);
    uint32_t pscRdValue, pscAddr, ptcmdAddr, ptstatAddr;
    if (pscDomain == SOC_PSC_DOMAIN_ID_MCU)
    {
        pscAddr = LBIST_WKUP_PSC_BASE + CSL_PSC_MDCTL(pscID);
        ptcmdAddr = LBIST_WKUP_PSC_BASE + CSL_PSC_PTCMD(0);
        ptstatAddr = LBIST_WKUP_PSC_BASE + CSL_PSC_PTSTAT(0);
    }
    else
    {
        pscAddr = LBIST_MAIN_PSC_BASE + CSL_PSC_MDCTL(pscID);
        ptcmdAddr = LBIST_MAIN_PSC_BASE + CSL_PSC_PTCMD(0);
        ptstatAddr = LBIST_MAIN_PSC_BASE + CSL_PSC_PTSTAT(0);
    }

    /* Read current value of the register */
    pscRdValue = HW_RD_REG32(pscAddr);
    /* Delete bits corresponding to state */
    pscRdValue &= ~LBIST_PSC_NEXT_MASK;

    /* Bits to be set for SwRstDisable or On state and Force bit */
    if (powerOn == TRUE)
    {
        pscRdValue |= LBIST_PSC_FORCE_ON;
    }
    else
    {
        pscRdValue |= LBIST_PSC_FORCE_OFF;
    }

    /* Write back to the PSC register */
    HW_WR_REG32(pscAddr, pscRdValue);
    /* Write shift value to PSC_PTCMD to cause state change */
    HW_WR_REG32(ptcmdAddr, pdShift);
    DSB_ENABLE;
    ISB_ENABLE;

    /* Wait until state transition is completed */
    while (((HW_RD_REG32(ptstatAddr) & pdShift) != 0) && (pscTimeout > 0))
    {
        pscTimeout--;
    }

    /* If the transition wait timed out */
    if ((HW_RD_REG32(ptstatAddr) & pdShift) != 0)
    {
        result = SDL_EFAIL;
    }
    return result;
}

static int32_t LBIST_pscOp(uint32_t pscDomain, uint32_t pscPD, uint32_t pscID, bool powerOn)
{
    int32_t status = SystemP_SUCCESS;
    if(powerOn)
    {
        status = SOC_setPSCState(pscDomain, pscPD, pscID, SOC_PSC_ENABLE);
        if (status != SystemP_SUCCESS)
        {
            status = LBIST_PSCForceBit(pscDomain, pscPD, pscID, TRUE);
        }
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("\r\n Failure in enable of PSC %d in %s!", pscID, pscDomain==0? "Main PSC domain" : "WKUP PSC domain");
        }
    }
    else
    {
        status = SOC_setPSCState(pscDomain, pscPD, pscID, SOC_PSC_SYNCRESETDISABLE);
        if (status != SystemP_SUCCESS)
        {
            status = LBIST_PSCForceBit(pscDomain, pscPD, pscID, FALSE);
        }
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("\r\n Failure in disable of PSC %d in %s!", pscID, pscDomain==0? "Main PSC domain" : "WKUP PSC domain");
        }
    }
    return status;
}

static int32_t core_power_down()
{
    int32_t status = SystemP_SUCCESS;
    uint32_t corePD, corePSC;
    uint32_t core_PDCTL, core_PTCMD, core_PTSTAT;
#if defined(SOC_AM275X)
#if defined(R5FSS0)
    corePD = CSL_MAIN_R5SS_1;
    corePSC = CSL_MAIN_LPSC_MAIN_R5SS1_CORE0;
#else
    corePD = CSL_MAIN_R5SS_0;
    corePSC = CSL_MAIN_LPSC_MAIN_R5SS0_CORE0;
#endif
    status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MAIN, corePD, corePSC+2, SOC_PSC_SYNCRESETDISABLE);
    if (status == SystemP_SUCCESS)
    {
        status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MAIN, corePD, corePSC+1, SOC_PSC_SYNCRESETDISABLE);
    }
    if (status == SystemP_SUCCESS)
    {
        status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MAIN, corePD, corePSC, SOC_PSC_SYNCRESETDISABLE);
    }
#elif defined(SOC_AM62X) || defined(SOC_AM62PX) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_J722S)
#if !defined(SOC_AM62X)
    corePD = CSL_WKUP_PD_MCUSS;
    corePSC = CSL_WKUP_LPSC_MCU_R5;
#else
    corePD = CSL_WKUP_PD_M4F;
    corePSC = CSL_WKUP_LPSC_MCU_M4F;
#endif
    status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, corePD, corePSC, SOC_PSC_SYNCRESETDISABLE);
    if (status == SystemP_SUCCESS)
    {
        status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, corePD, CSL_WKUP_LPSC_MCU_MCANSS_0, SOC_PSC_SYNCRESETDISABLE);
    }
    if (status == SystemP_SUCCESS)
    {
        status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, corePD, CSL_WKUP_LPSC_MCU_MCANSS_1, SOC_PSC_SYNCRESETDISABLE);
    }
#if !defined(SOC_AM62X)
    if (status == SystemP_SUCCESS)
    {
        status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, corePD, CSL_WKUP_LPSC_MCU_PBIST, SOC_PSC_SYNCRESETDISABLE);
    }
#endif
    if (status == SystemP_SUCCESS)
    {
        status = SOC_setPSCState(SOC_PSC_DOMAIN_ID_MCU, corePD, CSL_WKUP_LPSC_MCU_COMMON, SOC_PSC_SYNCRESETDISABLE);
    }
#endif

    if (status != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Failure in PSC settings during core power down");
        return -1;
    }

#if defined(SOC_AM275X)
    core_PDCTL = CSL_PSCSS0_VBUS_BASE + CSL_PSC_PDCTL(corePD);
    core_PTCMD = CSL_PSCSS0_VBUS_BASE + CSL_PSC_PTCMD(0);
    core_PTSTAT = CSL_PSCSS0_VBUS_BASE + CSL_PSC_PTSTAT(0);
#elif defined(SOC_AM62X) || defined(SOC_AM62PX) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_J722S)
    core_PDCTL = CSL_WKUP_PSC0_BASE + CSL_PSC_PDCTL(corePD);
    core_PTCMD = CSL_WKUP_PSC0_BASE + CSL_PSC_PTCMD(0);
    core_PTSTAT = CSL_WKUP_PSC0_BASE + CSL_PSC_PTSTAT(0);
#endif
    int32_t pscTimeout = 1000000U;
    /* Write desired power state to the PSC register */
    HW_WR_REG32(core_PDCTL, SOC_PSC_DOMAIN_OFF);
    /* Write shift value to PSC_PTCMD to cause state change */
    HW_WR_REG32(core_PTCMD, (1 << corePD));
    DSB_ENABLE;
    ISB_ENABLE;
    /* Wait until state transition is completed */
    while (((HW_RD_REG32(core_PTSTAT) & (1 << corePD)) != 0) && (pscTimeout > 0))
    {
        pscTimeout--;
    }

    /* If the transition wait timed out */
    if ((HW_RD_REG32(core_PTSTAT) & (1 << corePD)) != 0)
    {
        status = SDL_EFAIL;
        DebugP_log("\r\n Failure in core power down");
    }
    return status;
}

int32_t LBIST_runTest(uint32_t coreIndex)
{
    int32_t testResult = 0;
    int32_t status = 0;
    uint64_t startTime , testStartTime,  testEndTime, endTime;
    uint64_t prepTime, diffTime, restoreTime;
    bool result = false;
    LBIST_PSC_t currPSC;

    DebugP_log("\r\n Starting LBIST test on %s, index %d...",
                LBIST_TestHandleArray[coreIndex].coreName,
                coreIndex);
#ifdef DEBUG
    char inputChar;

    DebugP_log("\r\n Press 'n' to skip..Press any key to continue...");
    inputChar = UART_getc();

    if (inputChar == 'n')
    {
        DebugP_log("   Skipping this test. on request \r\n");
        return 0;
    }
#endif

#ifdef DEBUG
    DebugP_log("\r\n  HwiP_Params_init complete \r\n");
#endif

    /* Get start time of test */
    startTime = ClockP_getTimeUsec();

    /* Request Primary core */
    if (testResult == 0)
    {
        if (LBIST_TestHandleArray[coreIndex].tisciProcId != 0u)
        {
#ifdef DEBUG
            DebugP_log("  Primary core: %s: Requesting processor \r\n",
                        LBIST_TestHandleArray[coreIndex].coreName);
#endif
            /* Request Primary core */
            status = Sciclient_procBootRequestProcessor(LBIST_TestHandleArray[coreIndex].tisciProcId,
                                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Primary core: Sciclient_procBootRequestProcessor, ProcId 0x%x...FAILED : Status %d\r\n",
                            LBIST_TestHandleArray[coreIndex].tisciProcId, status);
                testResult = -1;
            }
        }
    }

    /* Request Secondary core */
    if (testResult == 0)
    {
        if ((LBIST_TestHandleArray[coreIndex].secondaryCoreNeeded)
            && (LBIST_TestHandleArray[coreIndex].tisciSecProcId != 0u))
        {

#ifdef DEBUG
            DebugP_log("  Secondary core: %s: Requesting processor \r\n",
                        LBIST_TestHandleArray[coreIndex].secCoreName);
#endif
            /* Request secondary core */
            status = Sciclient_procBootRequestProcessor(LBIST_TestHandleArray[coreIndex].tisciSecProcId,
                                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Secondary core: Sciclient_procBootRequestProcessor, ProcId 0x%x...FAILED \r\n",
                            LBIST_TestHandleArray[coreIndex].tisciSecProcId);
                testResult = -1;
            }
        }
    }

    /* Pre-LBIST PSC power downs */
    for (int i=0; i<LBIST_NUM_DISABLES; i++)
    {
        currPSC = LBIST_pscDisableList[i];
        status = LBIST_pscOp(currPSC.pscDomainId, currPSC.pscPowerDomainId, currPSC.pscIndex, FALSE);
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("\r\n Failure in PSC settings before LBIST!");
            testResult = -1;
            break;
        }
    }

    /* Get start time for LBIST test */
    testStartTime = ClockP_getTimeUsec();
    uint32_t timeoutCount = 0;

    /* Run LBIST test */
    if (testResult == 0)
    {
        status = SDL_LBIST_selfTest(LBIST_TestHandleArray[coreIndex].instance, SDL_LBIST_TEST);
        if (status != SDL_PASS)
        {
            DebugP_log("    LBIST selfTest failed \r\n");
            testResult = -1;
        }
        while(timeoutCount < LBIST_MAX_TIMEOUT_VALUE)
        {
            if(LBIST_DONE == SDL_LBIST_checkDone(LBIST_TestHandleArray[coreIndex].instance))
            {
                break;
            }
            else
            {
                timeoutCount++;
            }
            if (timeoutCount > LBIST_MAX_TIMEOUT_VALUE)
            {
                DebugP_log("    LBIST selfTest failed with timeout \r\n");
                testResult = -1;
            }
        }
        status = SDL_LBIST_checkResult(LBIST_TestHandleArray[coreIndex].instance, &result);
        if (result != TRUE)
        {
            DebugP_log("    LBIST selfTest failed \r\n");
            testResult = -1;
        }
    }

    /* Here LBIST test is complete , get end time of test */
    testEndTime = ClockP_getTimeUsec();

    /* Switch off core PD */
    status = core_power_down();
    if (status != SystemP_SUCCESS)
    {
        DebugP_log("\r\n Failure in core power down after LBIST!");
        testResult = SDL_EFAIL;
    }
 
    /* Disable Isolation */
    if (testResult == 0)
    {
        status = SDL_LBIST_selfTest(LBIST_TestHandleArray[coreIndex].instance, SDL_LBIST_TEST_RELEASE);
    }

    /* Post-LBIST PSC power ups */
    for (int i=0; i<LBIST_NUM_ENABLES; i++)
    {
        currPSC = LBIST_pscEnableList[i];
        status = LBIST_pscOp(currPSC.pscDomainId, currPSC.pscPowerDomainId, currPSC.pscIndex, TRUE);
        if (status != SystemP_SUCCESS)
        {
            DebugP_log("\r\n Failure in PSC settings after LBIST!");
            testResult = -1;
            break;
        }
    }

    /* Release Primary core */
    if ((testResult == 0) && (LBIST_TestHandleArray[coreIndex].tisciProcId !=0))
    {
        /* release processor Primary core */
#ifdef DEBUG
        DebugP_log("  Primary core: Releasing %s \r\n",
                    LBIST_TestHandleArray[coreIndex].coreName);
#endif

        status = Sciclient_procBootReleaseProcessor(LBIST_TestHandleArray[coreIndex].tisciProcId,
                                                    TISCI_MSG_FLAG_AOP,
                                                    SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != SDL_PASS)
        {
            DebugP_log("   Primary core: Sciclient_procBootReleaseProcessor, ProcId 0x%x...FAILED \r\n",
                        LBIST_TestHandleArray[coreIndex].tisciProcId);
            testResult = -1;
        }
    }
    /* Release Secondary core */
    if (testResult == 0)
    {
        if ((LBIST_TestHandleArray[coreIndex].secondaryCoreNeeded)
            && (LBIST_TestHandleArray[coreIndex].tisciSecDeviceId != 0u))
        {
            /* release processor Secondary core */
#ifdef DEBUG
            DebugP_log("  Secondary core: Releasing %s \r\n",
                        LBIST_TestHandleArray[coreIndex].secCoreName);
#endif
            status = Sciclient_procBootReleaseProcessor(LBIST_TestHandleArray[coreIndex].tisciSecProcId,
                                                        TISCI_MSG_FLAG_AOP,
                                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status != SDL_PASS)
            {
                DebugP_log("   Secondary core: Sciclient_procBootReleaseProcessor, ProcId 0x%x...FAILED \r\n",
                            LBIST_TestHandleArray[coreIndex].tisciSecProcId);
                testResult = -1;
            }
        }
    }

    /* Here LBIST test is complete , get end time of test */
    endTime = ClockP_getTimeUsec();

    prepTime = testStartTime - startTime;
    diffTime = testEndTime - testStartTime;
    restoreTime = endTime - testEndTime;
    DebugP_log("\r\n  Delta Cores prep time in micro secs %d", (uint32_t)prepTime );
    DebugP_log("\r\n  Delta LBIST execution time in micro secs %d", (uint32_t)diffTime );
    DebugP_log("\r\n  Delta Cores restore time in micro secs %d", (uint32_t)restoreTime );
    if (testResult == 0)
    {
        DebugP_log("\r\n  Total LBIST time in micro secs %u", (uint32_t)(prepTime + diffTime + restoreTime) );
    }

    DebugP_log("\r\n  LBIST complete for %s \r\n",
                LBIST_TestHandleArray[coreIndex].coreName);

    return (testResult);
}

/* Run all APIs not exercised by functional test */
int32_t LBIST_apiTest(uint32_t coreIndex)
{
    int32_t testResult = 0;
    bool isRunning;
    SDL_lbistInstInfo *pInfo;
    pInfo = SDL_LBIST_getInstInfo(LBIST_TestHandleArray[coreIndex].instance);

    /* Call SDL APIs not used by functional test */

    /* This call is to test "false" isRunning value for SDL_LBIST_isRunning */
    testResult = SDL_LBIST_isRunning(pInfo->pLBISTRegs, &isRunning);

    /* LBIST is not expected to be running at this point in the program */
    if (isRunning)
    {
        testResult = SDL_EFAIL;
    }

    return (testResult);
}

/* LBIST Functional test */
int32_t LBIST_funcTest(void)
{
    int32_t    testResult = 0;

    if (testResult == 0)
    {
        for (int i = 0; i < SDL_LBIST_NUM_INSTANCES; i++)
        {
            uint32_t lbist_devId = Sciclient_getSelfDevIdCore();
            if(LBIST_TestHandleArray[i].tisciDeviceId == lbist_devId)
            {
                DebugP_log("\r\n Skipping LBIST test for %s\r\n", LBIST_TestHandleArray[i].coreName);
                continue;
            }
            testResult = LBIST_runTest(i);

            if (testResult != 0)
            {
                DebugP_log("\r\n LBIST functional test failed %d\r\n", i);
            }
        }
    }
    if (testResult == 0)
    {
        /* API test is enough to be run on one instance */
        testResult = LBIST_apiTest(0);
        if (testResult != 0)
        {
            DebugP_log("\r\n  LBIST API test failed\r\n");
        }
    }

    return (testResult);
}
/* Nothing past this point */
