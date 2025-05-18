# PMU {#SDL_PMU_PAGE}

[TOC]

Performance Monitoring Unit (PMU) consists of three event counting registers, one cycle counting register and 12 CP15 registers for controlling and interrogating the counters.

The performance monitoring registers are always accessible in Privileged mode. Control registers can be used to enable or disable each of the event counters individually, and read and reset the overflow flag for each counter. All three event counters are read and written through the same CP15 register. The counters can be enabled to assert an interrupt request when the processor is in Debug halt state. 
PMU only counts events when non-invasive debug is enabled, that is, when either DBGEN or NIDEN inputs are asserted. The Cycle Count (CCNT) Register is always enabled regardless of whether non-invasive debug is enabled, unless the DP bit of the PMNC register is set.

## SysConfig Features

- None

## Features NOT Supported

- None

## Important Usage Guidelines

- None

## Example Usage

The following shows an example of SDL PMU API.

Include the below file to access the APIs

\code{.c}
#include <sdl/r5/v0/sdl_arm_r5_pmu.h>
\endcode

Configure the PMU
\code{.c}
SDL_R5PMU_cfg(cycleCntDiv, exportEvents, userEnable);
retValue= SDL_R5PMU_verifyCfg(cycleCntDiv,exportEvents);
\endcode

Configure PMU Counters
\code{.c}
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
\endcode

Get the number of PMU counters supported
\code{.c}
/* Report number of counters implemented */
numCntrs = SDL_R5PMU_getNumCntrs();
\endcode

Get the number of branch, icache misses and dcache misses
\code{.c}
/* Report number of branch, icache miss and dcache miss */
dCacheMissCnt = sdl_pmu_test_get_dCache_miss();
iCacheMissCnt = sdl_pmu_test_get_iCache_miss();
branchCnt     = sdl_pmu_test_get_branch();
cycleCnt      = sdl_pmu_test_get_cycle();
\endcode

Reconfigure PMU with new values
\code{.c}
SDL_R5PMU_cfg(cycleCntDiv, exportEvents, userEnable);
\endcode

Check if static registers values are as expected
\code{.c}
SDL_R5PMU_readStaticRegisters(&pStaticRegs);
\endcode

Set all PMU counters to new values
\code{.c}
/* Set and Read the Counter */
SDL_R5PMU_setResetCntr(SDL_ARM_R5_PMU_CYCLE_COUNTER_NUM, 0x3000U );
SDL_R5PMU_setResetCntr(PMU_CNTR_NUM_ICACHE_MISS, 1U );
SDL_R5PMU_setResetCntr(PMU_CNTR_NUM_DCAHCE_MISS, 1U );
SDL_R5PMU_setResetCntr(PMU_CNTR_NUM_BRANCH, 1U );

dCacheMissCnt = sdl_pmu_test_get_dCache_miss();
iCacheMissCnt = sdl_pmu_test_get_iCache_miss();
branchCnt     = sdl_pmu_test_get_branch();
cycleCnt      = sdl_pmu_test_get_cycle();
\endcode

## API

\ref SDL_ARM_R5_PMU_API







