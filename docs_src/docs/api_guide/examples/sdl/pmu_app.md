# SDL PMU Example {#EXAMPLES_SDL_PMU}

[TOC]

# Introduction

This example demonstrates the usage of PMU. The example shows how to configure PMU counters.

Use Cases
---------
* Configure three event counting registers, one cycle counting register and 12 CP15 registers for controlling and interrogating the counters.

# Supported Combinations {#EXAMPLES_SDL_PMU_COMBOS}

\cond SOC_J722S

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/pmu/

\endcond

# Steps to Run the Example

<!-- - **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). -->

# See Also

\ref SDL_PMU_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code

PMU Test Application
Number of PMU counters implemented is: 0x3 
 
  readStatic register successful

static config exportsEvents value is: 0x0 
 
 static config cycleCntDiv value is: 0x0 
 
 iCacheMissCnt is: 0x33 
 
 dCacheMissCnt is: 0x32 
 
 branchCnt is: 0x8ed 
 
 cycleCnt is: 0x0 
 
 Setting all PMU counters to new values:  
 New iCacheMissCnt is: 0x2 
 
 New dCacheMissCnt is: 0x2 
 
 New branchCnt is: 0x10 
 
 New cycleCnt is: 0x3000 
 
 Test Name: sdl_core_r5_pmuTest  PASSED 

 All tests have passed. 

\endcode

