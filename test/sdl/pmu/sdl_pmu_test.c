/*
 * Copyright (C) 2024-2025 Texas Instruments Incorporated
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
 *  \file     sdl_pmu_test.c
 *
 *  \brief    This file contains PMU test code for R5 core.
 *
 *  \details  PMU register read/write and configuration tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/
#include "sdl_pmu_test.h"

/*===========================================================================*/
/*                         Declarations                                      */
/*===========================================================================*/


/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/
#define PMU_CNTR_NUM_BRANCH             (2u)
#define PMU_CNTR_NUM_ICACHE_MISS        (1u)
#define PMU_CNTR_NUM_DCAHCE_MISS        (0u)

/*===========================================================================*/
/*                         Internal function declarations                    */
/*===========================================================================*/
static uint32_t sdl_pmu_test_get_dCache_miss(void);
static uint32_t sdl_pmu_test_get_iCache_miss(void);
static uint32_t sdl_pmu_test_get_branch(void);
static uint32_t sdl_pmu_test_get_cycle(void);
static void sdlApp_printArg(uint32_t value);

/*===========================================================================*/
/*                         Global Variables                                  */
/*===========================================================================*/

/*===========================================================================*/
/*                   Local Function definitions                              */
/*===========================================================================*/


/*===========================================================================*/
/*                        Test Function definitions                          */
/*===========================================================================*/

static void sdlApp_printArg(uint32_t value)
{
    DebugP_log("0x%x \n", value);
}

static void sdl_pmu_test_init_pmu(void)
{
    uint32_t val;
	int32_t retValue;
	uint32_t cycleCntDiv = 0U,  exportEvents = 0U,  userEnable = 1U;

    SDL_R5PMU_cfg(cycleCntDiv, exportEvents, userEnable);
	retValue= SDL_R5PMU_verifyCfg(cycleCntDiv,exportEvents);
	if(retValue != SDL_PASS)
	{
		sdlApp_print(" verifyCfg failed\n");
	}
    /* Clear the overflow */
    val = SDL_R5PMU_readCntrOverflowStatus();
    val &= 0x80000007;
    SDL_R5PMU_clearCntrOverflowStatus (val);
    SDL_R5PMU_cfgCntr(SDL_ARM_R5_PMU_CYCLE_COUNTER_NUM, SDL_ARM_R5_PMU_EVENT_TYPE_CYCLE_CNT);
    /* I-Cache */
    SDL_R5PMU_cfgCntr(PMU_CNTR_NUM_ICACHE_MISS, SDL_ARM_R5_PMU_EVENT_TYPE_ICACHE_MISS);
    /* D-Cache */
    SDL_R5PMU_cfgCntr(PMU_CNTR_NUM_DCAHCE_MISS, SDL_ARM_R5_PMU_EVENT_TYPE_DCACHE_MISS);
    /* Branch */
    SDL_R5PMU_cfgCntr(PMU_CNTR_NUM_BRANCH, SDL_ARM_R5_PMU_EVENT_TYPE_B_IMMEDIATE);
    SDL_R5PMU_enableAllCntrs (0);
    SDL_R5PMU_resetCycleCnt ();      /* Set PMCR C-bit */
    SDL_R5PMU_resetCntrs();

    SDL_R5PMU_enableCntr (PMU_CNTR_NUM_BRANCH, 1);
    SDL_R5PMU_enableCntr (PMU_CNTR_NUM_ICACHE_MISS, 1);
    SDL_R5PMU_enableCntr (PMU_CNTR_NUM_DCAHCE_MISS, 1);
    SDL_R5PMU_enableAllCntrs (1);
    SDL_R5PMU_enableCntrOverflowIntr (PMU_CNTR_NUM_BRANCH, 1U);
    SDL_R5PMU_enableCntrOverflowIntr (PMU_CNTR_NUM_BRANCH, 0U);
}

static uint32_t sdl_pmu_test_get_iCache_miss(void)
{
    uint32_t    temp;
    temp = SDL_R5PMU_readCntr(PMU_CNTR_NUM_ICACHE_MISS);
    return temp;
}

static uint32_t sdl_pmu_test_get_dCache_miss(void)
{
    uint32_t    temp;
    temp = SDL_R5PMU_readCntr(PMU_CNTR_NUM_ICACHE_MISS);
    return temp;
}

static uint32_t sdl_pmu_test_get_branch(void)
{
    uint32_t    temp;
    temp = SDL_R5PMU_readCntr(PMU_CNTR_NUM_BRANCH);
    return temp;
}

unsigned int sdl_pmu_test_get_cycle(void) {
    uint32_t    temp;
    temp = SDL_R5PMU_readCntr(SDL_ARM_R5_PMU_CYCLE_COUNTER_NUM);
    return temp;
}

/*  This test demonstrates the APIs to enable the use of
 *             PMU counters
 */
int32_t sdl_core_r5_pmuTest(void)
{
    uint32_t   numCntrs, dCacheMissCnt, iCacheMissCnt, branchCnt, cycleCnt;
    /* Declarations of variables */
    int32_t    retValue, testResult = SDL_APP_TEST_PASS;
	SDL_PMU_staticRegs pStaticRegs;
	uint32_t cycleCntDiv = 0U,  exportEvents = 0U,  userEnable = 1U;

    /* Some negative tests for code coverage on PMU */
    SDL_R5PMU_cfg(1, 1, 0);
	retValue = SDL_R5PMU_verifyCfg(1,0);
	if(retValue != SDL_EFAIL)
	{
		sdlApp_print(" verifyCfg API test failed \n \n");
		testResult = SDL_APP_TEST_FAILED;
	}
	SDL_R5PMU_enableCntr (PMU_CNTR_NUM_BRANCH, 0);
    SDL_R5PMU_enableCntr (PMU_CNTR_NUM_ICACHE_MISS, 0);
    SDL_R5PMU_enableCntr (PMU_CNTR_NUM_DCAHCE_MISS, 0);
    SDL_R5PMU_enableAllCntrs (0);
	SDL_R5PMU_readStaticRegisters(&pStaticRegs);
    sdl_pmu_test_init_pmu();

   /* Report number of counters implemented */
    numCntrs = SDL_R5PMU_getNumCntrs();
    sdlApp_print("Number of PMU counters implemented is: ");
    sdlApp_printArg(numCntrs);
    sdlApp_print(" \n ");

	/* Report number of branch, icache miss and dcache miss */
	dCacheMissCnt = sdl_pmu_test_get_dCache_miss();
	iCacheMissCnt = sdl_pmu_test_get_iCache_miss();
	branchCnt     = sdl_pmu_test_get_branch();
	cycleCnt      = sdl_pmu_test_get_cycle();

	SDL_R5PMU_cfg(cycleCntDiv, exportEvents, userEnable);
	SDL_R5PMU_readStaticRegisters(&pStaticRegs);

	if(((uint8_t)pStaticRegs.cycleCntDiv == cycleCntDiv) &&
    ((uint8_t)pStaticRegs.exportEvents == exportEvents) &&
    ((uint8_t)pStaticRegs.userEnable == userEnable))
	{
		sdlApp_print(" readStatic register successful\n\n");

		sdlApp_print("static config exportsEvents value is: ");
		sdlApp_printArg(pStaticRegs.exportEvents);
		sdlApp_print(" \n ");

		sdlApp_print("static config cycleCntDiv value is: ");
		sdlApp_printArg(pStaticRegs.cycleCntDiv);
		sdlApp_print(" \n ");
	}
	else{
		sdlApp_print(" readStaticRegisters failed\n");
		 testResult = SDL_APP_TEST_FAILED;
	}

    sdlApp_print("iCacheMissCnt is: ");
    sdlApp_printArg(iCacheMissCnt);
    sdlApp_print(" \n ");

    sdlApp_print("dCacheMissCnt is: ");
    sdlApp_printArg(dCacheMissCnt);
    sdlApp_print(" \n ");

    sdlApp_print("branchCnt is: ");
    sdlApp_printArg(branchCnt);
    sdlApp_print(" \n ");

    sdlApp_print("cycleCnt is: ");
    sdlApp_printArg(cycleCnt);
    sdlApp_print(" \n ");


    sdlApp_print("Setting all PMU counters to new values: ");
    sdlApp_print(" \n ");

    /* Set and Read the Counter */
    SDL_R5PMU_setResetCntr(SDL_ARM_R5_PMU_CYCLE_COUNTER_NUM, 0x3000U );
    SDL_R5PMU_setResetCntr(PMU_CNTR_NUM_ICACHE_MISS, 1U );
    SDL_R5PMU_setResetCntr(PMU_CNTR_NUM_DCAHCE_MISS, 1U );
    SDL_R5PMU_setResetCntr(PMU_CNTR_NUM_BRANCH, 1U );

    dCacheMissCnt = sdl_pmu_test_get_dCache_miss();
    iCacheMissCnt = sdl_pmu_test_get_iCache_miss();
    branchCnt     = sdl_pmu_test_get_branch();
    cycleCnt      = sdl_pmu_test_get_cycle();

    sdlApp_print("New iCacheMissCnt is: ");
    sdlApp_printArg(iCacheMissCnt);
    sdlApp_print(" \n ");

    sdlApp_print("New dCacheMissCnt is: ");
    sdlApp_printArg(dCacheMissCnt);
    sdlApp_print(" \n ");

    sdlApp_print("New branchCnt is: ");
    sdlApp_printArg(branchCnt);
    sdlApp_print(" \n ");

    sdlApp_print("New cycleCnt is: ");
    sdlApp_printArg(cycleCnt);
    sdlApp_print(" \n ");

    return (testResult);
}


/* Nothing past this point */
