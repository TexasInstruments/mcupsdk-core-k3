/*
 *   Copyright (C) Texas Instruments Incorporated 2024-25
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
 *
 */

/**
 *  \file     ecc_func.c
 *
 *  \brief    This file contains ECC SDL Function test code for R5 core.
 *
 *  \details  ECC SDL API module tests
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <sdl/include/sdl_types.h>
#include <sdl/sdl_ecc.h>
#include <kernel/dpl/DebugP.h>
#include <sdl/sdl_esm.h>
#include <sdl/ecc/sdl_ecc_core.h>
#include "sdl_cache.h"
#include <sdl/sdl_exception.h>
#include <sdl/r5/v0/sdl_interrupt.h>
#include <sdl/r5/v0/sdl_interrupt_priv.h>
#include <sdl/r5/v0/sdl_vim.h>
#include <kernel/dpl/TimerP.h>
#include "ti_dpl_config.h"
#if defined(SOC_J722S)
#include <sdl/ecc/soc/j722s/sdl_ecc_soc.h>
#endif

#include "vim_test_main.h"
#include <sdl/dpl/sdl_dpl.h>
#include <drivers/soc.h>
#include <sdl/ecc/V0/sdlr_edc_ctl.h>
#include <dpl_interface.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/ClockP.h>

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Function prototypes */
void VIM_Test_copyResetVector(void);
int32_t VIM_Test_EsmInitHandlerInit(SDL_ESM_Inst esmInstType);
int32_t SDL_ECC_memoryRefresh(uint32_t *memAddr, size_t size);
__attribute__((interrupt,target("arm"), aligned(32))) void VIM_Test_VIMDEDInterruptHandler(void);
extern int32_t ECC_Test_UTILS_TCMEnable(void);
static void VIM_Test_startTimer(void);
void timerFxn(uintptr_t arg);
int32_t VIM_Memory_init (void);

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* delay for 1us*/
#define DELAY 1
#define DEBUG
#define ATCM_BASE_ADDR  (0x00000000U)
#define ATCM_SIZE       (0x00008000U)
#define TEST_AREA_SIZE  (0x00000400U)

#define ATCM_FILL_PATTERN (0xffffffffU)


#define MAIN_MSMC_AGGR0_MAX_MEM_SECTIONS (2u)
#define PIN_CLEAR_PERIOD_USEC    (10)
#define MODID_ESM	modId = TISCI_DEV_WKUP_ESM0;
#define CLKID_ESM   clkId = TISCI_DEV_WKUP_ESM0_CLK;
#define VECTOR_SIZE 0x100
#define APP_MAX_PROFILE_SIZE 16
#define MCU_R5F_MAX_MEM_SECTIONS   (1u)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern volatile bool esmError;
static uint32_t             gesmPinMinIntervalCycles;
static uint32_t             gesmPinMinIntervalUsec;
static uint32_t             gpinClearTimeCycles;
static bool VIM_Test_ECC_DEDTriggerFlag = false;
extern void *_vectors;
static uint32_t arg;

#if defined(SOC_J722S)
SDL_ESM_config ECC_Test_esmInitConfig_MAIN =
    {
        .esmErrorConfig = {1u, 8u}, /* Self test error config */
        .enableBitmap = {
            0x77f1bf6eu, 0xffc3e0fcu, 0xef066dfeu,
            0xcfc0bf00u, 0x034cf807u, 0xae343fffu,
            0x3C73f03u, 0xffffffffu,
        },
        /**< All events enable: except timer and self test  events, and Main ESM output */
        /* Temporarily disabling vim compare error as well*/
        .priorityBitmap = {
            0x77f1bf6eu, 0xffc3e0fcu, 0xef066dbeu,
            0xcfc0bf00u, 0x034cf807u, 0x94303fffu,
            0x3C73303u, 0xffffffffu,
        },
        /**< All events high priority: except timer, selftest error events, and Main ESM output */
        .errorpinBitmap = {
            0x77f1bf6eu, 0xffc3e0fcu, 0xef066dbeu,
            0xcfc0bf00u, 0x034cf807u, 0x94303fffu,
            0x3C73303u, 0xffffffffu,
        },
        /**< All events high priority: except timer, selftest error events, and Main ESM output */
};

SDL_ESM_config ECC_Test_esmInitConfig_MCU =
{
    .esmErrorConfig = {10u, 8u}, /* Self test error config */
    .enableBitmap = {
                        0x003fc030u, 0x0000033fu, 0x00000000u, 0x00000000u,
                        0x00000c00u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
					},
     /**< All events enable: except clkstop events for unused clocks
      *   and PCIE events */
    .priorityBitmap = {
                        0x003fc030u, 0x0000033fu, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                    },
    /**< All events high priority: except clkstop events for unused clocks
     *   and PCIE events */
    .errorpinBitmap = {
                        0x003fc030u, 0x0000033fu, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                        0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
                    },
    /**< All events high priority: except clkstop for unused clocks
     *   and PCIE events */
};
#endif

extern int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInstType,
                                                   SDL_ESM_IntType esmIntType,
                                                   uint32_t grpChannel,
                                                   uint32_t index,
                                                   uint32_t intSrc,
                                                   void *arg);
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


static SDL_ECC_MemSubType VIM_Test_R5FCoresubMemTypeList[MCU_R5F_MAX_MEM_SECTIONS] =
{
    SDL_ECC_R5F_MEM_SUBTYPE_KS_VIM_RAM_VECTOR_ID,

};

static SDL_ECC_InitConfig_t VIM_Test_R5FCoreECCInitConfig =
{
    .numRams = MCU_R5F_MAX_MEM_SECTIONS,
    /**< Number of Rams ECC is enabled  */
    .pMemSubTypeList = &(VIM_Test_R5FCoresubMemTypeList[0]),
    /**< Sub type list  */
};

void VIM_Test_cpuCacheInv(const void * addr, int32_t size)
{
    SDL_armR5CacheInv(addr, size);
}

void VIM_Test_cpuCacheWbInv(const void * addr, int32_t size)
{
    SDL_armR5CacheWbInv(addr, size);
}

void VIM_Test_copyResetVector(void)
{
    /* Invalidate cache */
    VIM_Test_cpuCacheInv(0, VECTOR_SIZE);

    /* copy the vectors into 0 location */
    /* Vectors are always assumed to be at 0 for R5 */
    memcpy(0, &_vectors, VECTOR_SIZE);

    /* Write back cache */
    VIM_Test_cpuCacheWbInv(0, VECTOR_SIZE);
}

/* This is the list of exception handle and the parameters */
const SDL_R5ExptnHandlers VIM_Test_R5ExptnHandlers =
{
    .udefExptnHandler = &SDL_EXCEPTION_undefInstructionExptnHandler,
    .swiExptnHandler = &SDL_EXCEPTION_swIntrExptnHandler,
    .pabtExptnHandler = &SDL_EXCEPTION_prefetchAbortExptnHandler,
    .dabtExptnHandler = &SDL_EXCEPTION_dataAbortExptnHandler,
    .irqExptnHandler = &SDL_EXCEPTION_irqExptnHandler,
    .fiqExptnHandler = &SDL_EXCEPTION_fiqExptnHandler,
    .udefExptnHandlerArgs = ((void *)0u),
    .swiExptnHandlerArgs = ((void *)0u),
    .pabtExptnHandlerArgs = ((void *)0u),
    .dabtExptnHandlerArgs = ((void *)0u),
    .irqExptnHandlerArgs = ((void *)0u),
};

void VIM_Test_undefInstructionExptnCallback(void)
{
    DebugP_log("\r\n  Undefined Instruction exception");
}

void VIM_Test_swIntrExptnCallback(void)
{
    DebugP_log("\r\n  Software interrupt exception");
}

void VIM_Test_prefetchAbortExptnCallback(void)
{
    DebugP_log("\r\n  Prefetch Abort exception");
}
void VIM_Test_dataAbortExptnCallback(void)
{
    DebugP_log("\r\n  Data Abort exception");
}
void VIM_Test_irqExptnCallback(void)
{
    DebugP_log("\r\n  Irq exception");
}

void VIM_Test_fiqExptnCallback(void)
{
    DebugP_log("\r\n  Fiq exception");
}

void VIM_Test_exceptionInit(void)
{

    SDL_EXCEPTION_CallbackFunctions_t exceptionCallbackFunctions =
            {
             .udefExptnCallback = VIM_Test_undefInstructionExptnCallback,
             .swiExptnCallback = VIM_Test_swIntrExptnCallback,
             .pabtExptnCallback = VIM_Test_prefetchAbortExptnCallback,
             .dabtExptnCallback = VIM_Test_dataAbortExptnCallback,
             .irqExptnCallback = VIM_Test_irqExptnCallback,
             .fiqExptnCallback = VIM_Test_fiqExptnCallback,
            };

    /* Initialize SDL exception handler */
    SDL_EXCEPTION_init(&exceptionCallbackFunctions);
    /* Register SDL exception handler */
    Intc_RegisterExptnHandlers(&VIM_Test_R5ExptnHandlers);

    return;
}


void VIM_Test_ECC_indicateDEDTrigger(void)
{
    VIM_Test_ECC_DEDTriggerFlag = true;
}

/*********************************************************************
* @fn      VIM_Test_VIMDEDInterruptHandler
*
* @brief   Sample DED Interrupt handler
*
* @param   None
*
* @return   None
*/
void VIM_Test_VIMDEDInterruptHandler(void)
{
    /* Action to be taken by customer */
    DebugP_log("\r\n   VIM DED error happened \r\n ");
    DebugP_log("  Take action \r\n ");

    /* clear appropriate interrupt events */

    VIM_Test_ECC_indicateDEDTrigger();
}

int32_t VIM_Test_ECC_waitDEDTrigger(uint64_t timeCount)
{
    int32_t retVal = 0;
    uint32_t startTimeStamp, curTimeStamp, lastTimeStamp, deltaTime;
    uint64_t elapsedTime = 0u;

    startTimeStamp = TimerP_getCount(gTimerBaseAddr[CONFIG_TIMER_VIM_TEST_Pin]);
    lastTimeStamp = startTimeStamp;
    while(VIM_Test_ECC_DEDTriggerFlag != true) {
        curTimeStamp = TimerP_getCount(gTimerBaseAddr[CONFIG_TIMER_VIM_TEST_Pin]);
        deltaTime = curTimeStamp-lastTimeStamp;
        lastTimeStamp = curTimeStamp;
        elapsedTime += deltaTime;
        if (elapsedTime > timeCount) {
            break;
        }
    }

    if (VIM_Test_ECC_DEDTriggerFlag == true )
    {
        VIM_Test_ECC_DEDTriggerFlag = false;
    }
    else
    {
        retVal = -1;
    }

    return retVal;
}

/*********************************************************************
 * @fn      VIM_Test_runECC2BitVIMRAMDEDvector
 *
 * @brief   Execute ECC 2 bit Inject test with VIM RAM,but expect to
 *          trigger VIM DED vector
 *
 * @param   None
 *
 * @return  0 : Success; < 0 for failures
 */
int32_t VIM_Test_runECC2BitVIMRAMDEDvector(void)
{
    SDL_ErrType_t result = 0;
    int32_t retVal=0;

    SDL_ECC_InjectErrorConfig_t injectErrorConfig;

    DebugP_log("\r\n  VIM RAM Double bit error inject: starting");

    /* Run one shot test for VIM RAM 2 bit error */
    /* Inject the error into the interrupt associated with MCU Timer 0 */
    /* Timer 0 interrupt needs to happen to get the VIM DED error to trigger */
    /* This is expected to trigger the DED vector */
    injectErrorConfig.pErrMem = (uint32_t *)(0x7FF2228u);
    injectErrorConfig.flipBitMask = 0x101;

    result = SDL_ECC_injectError(SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR,
                                 SDL_ECC_R5F_MEM_SUBTYPE_KS_VIM_RAM_VECTOR_ID,
                                 SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE,
                                 &injectErrorConfig);
    if (result != SDL_PASS ) {
        DebugP_log("\r\n  VIM RAM Double bit error inject: at pErrMem 0x%p: fixed location once test failed",
                    injectErrorConfig.pErrMem);
       retVal = -1;
    } else {
        DebugP_log("\r\n  VIM RAM Double bit error inject: pErrMem 0x%p fixed location once test complete",
                    injectErrorConfig.pErrMem);
    }
    if (retVal == 0) {
        DebugP_log("\r\n  Waiting for DED Vector Trigger.");
        retVal = VIM_Test_ECC_waitDEDTrigger(0x100000000ull);
    }
    if (retVal == 0) {
        DebugP_log("\r\n  DED Vector Trigger: Success");
    } else {
        DebugP_log("\r\n  DED Vector Trigger: Fail");
    }
    return retVal;
}


/** ============================================================================*
 *
 * \brief   Refresh memory to make sure ECC is generated
 *
 *
 * \param1  memAddr: Address to refresh ( Need to aligned to 32 bit)
 * \param2  size: Size of memory region to refresh
 *                Should be multiple of 4
 *
 * \return  SDL_PASS : Success; SDL_EFAIL for failures
 */
int32_t SDL_ECC_memoryRefresh(uint32_t *memAddr, size_t size)
{
    uint32_t i;
    int32_t result = SDL_PASS;
    volatile uint32_t tmpValue;

    /* Simply read and copy back data */
    for (i = ((uint32_t)0u); i < (size>>(uint32_t)2u); i++) {
        tmpValue = memAddr[i];
        memAddr[i] = tmpValue;
    }
    return result;
}

/*********************************************************************
* @fn      VIM_Memory_init
*
* @brief   Initializes Software Diagostics Test Framework
*
* @param   None
*
* @return    0 : Success; < 0 for failures
*/
int32_t VIM_Memory_init (void)
{
    int32_t retValue=0;
    void *ptr = (void *)&arg;
    SDL_ErrType_t result;
    SDL_ECC_staticRegs staticRegs;

    /* Enable ATCM and BTCM */
    ECC_Test_UTILS_TCMEnable();

     SDL_ECC_memoryRefresh(ATCM_BASE_ADDR,ATCM_SIZE-TEST_AREA_SIZE);

    DebugP_log("\r\n VIM_ECC_Test_init:  ready to print, proceeding with ECC_Test init \r\n ");

    DebugP_log("\r\n VIM_ECC_Test_init: Profile init complete \r\n ");

    /* Call Init for ECC_Test software structures */

    /* Copy reset vector to 0 location */
    VIM_Test_copyResetVector();

    DebugP_log("\r\n VIM_ECC_Test_init: Copy Reset vector complete \r\n ");

    /* Initialise exception handler */
    VIM_Test_exceptionInit();

    DebugP_log("\r\n VIM_ECC_Test_init: Exception init complete \r\n ");

    /* Register VIM DED interrupt handler */
    SDL_ECC_registerVIMDEDHandler(&VIM_Test_VIMDEDInterruptHandler);

    if (retValue == SDL_PASS) {
		/* Initialize MCU ESM module */
        result = SDL_ESM_init(SDL_ESM_INST_WKUP_ESM0, &ECC_Test_esmInitConfig_MCU, SDL_ESM_applicationCallbackFunction, ptr);
		if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("   \r\n  VIM_Memory_init: Error initializing MCU ESM: result = %d   \r\n  ", result);

            retValue = -1;
        } else {
            DebugP_log("   \r\n  ECC_Test_init: Init MCU ESM complete    \r\n  ");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize MAIN ESM module */
        result = SDL_ESM_init(SDL_ESM_INST_MAIN_ESM0, &ECC_Test_esmInitConfig_MAIN,SDL_ESM_applicationCallbackFunction,ptr);
        if (result != SDL_PASS) {
            /* print error and quit */
            DebugP_log("\r\n  VIM_Memory_init: Error initializing MAIN ESM: result = %d   \r\n  ", result);

            retValue = -1;
        } else {
            DebugP_log("   \r\n  ECC_Test_init: Init MAIN ESM complete    \r\n  ");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize ECC callbacks within the MCU ESM */
        result = SDL_ECC_initEsm(SDL_ESM_INST_WKUP_ESM0);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("   \r\n  VIM_Memory_init: Error initializing ECC callback for MCU ESM: result = %d   \r\n  ", result);

            retValue = -1;
        } else {
            DebugP_log("   \r\n  ECC_Test_init: ECC Callback Init complete for MCU ESM    \r\n  ");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize ECC callbacks within the Main ESM */
        result = SDL_ECC_initEsm(SDL_ESM_INST_MAIN_ESM0);
        if (result != SDL_PASS) {
            /* print error and quit */
             DebugP_log("   \r\n  VIM_Memory_init: Error initializing ECC callback for Main ESM: result = %d   \r\n  ", result);

            retValue = -1;
        } else {
            DebugP_log("   \r\n  ECC_Test_init: ECC Callback Init complete for Main ESM    \r\n  ");
        }
    }

    if (retValue == SDL_PASS) {
        /* Initialize ECC callbacks within the Main ESM */
        result = SDL_ECC_init(SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR, &VIM_Test_R5FCoreECCInitConfig);

        if (result != SDL_PASS) {
            /* print error and quit */
                DebugP_log("VIM_ECC_Test_init: Error initializing R5F core ECC: result = %d\r\n ", result);

            retValue = -1;
        } else {
            DebugP_log("\r\n VIM_ECC_Test_init: Init MAIN ESM complete \r\n ");
        }
    }
    if (retValue == 0) {
        /* Read back the static registers */
        result = SDL_ECC_getStaticRegisters(SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR, &staticRegs);
        if (result != SDL_PASS) {
            /* print error and quit */
            DebugP_log("VIM_ECC_Test_init: Error reading the static registers: result = %d\r\n ");

            retValue = -1;
        } else {
            DebugP_log("\r\n VIM_ECC_Test_init: R5F Memtype Register Readback successful \r\n ");
        }
    }
    if (retValue == 0) {
        /* Initialize VIM ECC memory ; This is specifically for VIM in lockstep*/
        /* All other memories are auto initialized by hardware */
        result = SDL_ECC_initMemory(SDL_MCU_R5FSS0_PULSAR_ULS_CPU0_ECC_AGGR, SDL_ECC_R5F_MEM_SUBTYPE_KS_VIM_RAM_VECTOR_ID);
        if (result != SDL_PASS) {
             /* print error and quit */
              DebugP_log("VIM_ECC_Test_init: Error initializing ECC memory: retValue = %d\r\n ", retValue);
             retValue = -1;
         } else {
             DebugP_log("\r\n VIM_ECC_Test_init: ECC Memory init complete \r\n ");
         }
    }



    return retValue;
}

static int32_t VIM_sdlFuncTest(void)
{
    int32_t result;
    int32_t retVal = 0;
    DebugP_log("\r\n  VIM SDL API tests: starting");

    /* Timer is used to trigger the interrupt vector used for VIM DED Handler error */
    VIM_Test_startTimer();

    /* This needs to be last as it is destructive */
    if (retVal == 0) {
        result = VIM_Test_runECC2BitVIMRAMDEDvector();
        if (result != SDL_PASS) {
            retVal = -1;
            DebugP_log("\r\n  VIM_Test_runECC2BitVIMRAMDEDvector has failed...");
        }
    }
    if ( retVal == 0) {
        DebugP_log("\r\n  VIM SDL API tests: success");
    } else {
        DebugP_log("\r\n  VIM SDL API tests: failed");
    }
    return retVal;
}

/*********************************************************************
* @fn      vimPinTimerInit
*
* @brief   This checks current timings for the minimum interval time
*          on the MCU_SAFETY_ERRORn pin for VIM module
* @param   pinClearTime: Amount of time in microseconds that the Pin control
*          timer waits before triggering clearing of the MCU_SAFETY_ERRORn pin
*
* @return    0 : Success; < 0 for failures
*/
int32_t vimPinTimerInit(uint32_t pinClearTime)
{
    int32_t retVal = SDL_PASS;
    uint32_t modId;
    uint32_t clkId;
    uint64_t esmInputClk;
    uint32_t vim_base_addr;
    vim_base_addr = (uint32_t) AddrTranslateP_getLocalAddr(SDL_MCU_R5FSS0_CORE0_ECC_AGGR_BASE);
    SDL_ESM_getErrPinLowTimePreload(vim_base_addr, &gesmPinMinIntervalCycles);

    if (retVal == SDL_PASS) {
        /* MCU ESM clock */
        MODID_ESM;
        CLKID_ESM;


        retVal = Sciclient_pmGetModuleClkFreq(modId,
                                              clkId,
                                              &esmInputClk,
                                              0xFFFFFFFFU);
    }

    if (retVal == SDL_PASS) {
        /* Translate Pin Timer Time (microseconds) into number of ESM cycles */
        gpinClearTimeCycles = (uint32_t)((float)pinClearTime /
                             1000000 * (float)esmInputClk);

        /* Translate Minimum Time Interval (cycles) into time (microseconds)*/
        gesmPinMinIntervalUsec = (uint32_t)((float)gesmPinMinIntervalCycles /
                                           (float)esmInputClk * 1000000);
        DebugP_log("\r\n   Minimum Time Interval is %d usecs", gesmPinMinIntervalUsec);
    }
    else {
        retVal = SDL_EFAIL;
    }

    /* If desired, ESMSetErrPinLowTimePreload can be used to change
     * minimum interval time here */

    return retVal;
}


void timerFxn(uintptr_t arg)
{
    return;
}

/* TIMER FUNCTIONS */

/*********************************************************************
* @fn      VIM_Test_startTimer
*
* @brief   This initializes all timers for the ESM Example Application.
*
* @param   None
*
* @return    0 : Success; < 0 for failures
*/

static void VIM_Test_startTimer(void)
{
    TimerP_Params   timerParams;

    /* Start Timer and register call back for periodic functions */
    /* Initialize timer parameters */
    TimerP_Params_init(&timerParams);
    timerParams.periodInUsec   = 1000000u;
    timerParams.oneshotMode    = 0;
    timerParams.enableOverflowInt = 1;
    TimerP_setup(gTimerBaseAddr[CONFIG_TIMER_VIM_TEST_Pin], &timerParams);
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER_VIM_TEST_Pin]);

    if (vimPinTimerInit(PIN_CLEAR_PERIOD_USEC) != 0) {
       DebugP_log("ERR: Pin Time Init failed\r\n ");
    }

    DebugP_log("\r\n ESM timer initialization complete\r\n ");

}


/* ECC Function module test */
int32_t VIM_funcTest(void)
{
    int32_t testResult;
    testResult = VIM_Memory_init();
    if (testResult != 0)
    {
        DebugP_log("   \r\n  ECC func tests: unsuccessful   \r\n  ");
        return SDL_EFAIL;
    }

    testResult = VIM_sdlFuncTest();


    return (testResult);
}

/* Nothing past this point */