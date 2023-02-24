# SDL PBIST {#EXAMPLES_SDL_PBIST}

[TOC]

# Introduction

This example demonstrates the usage of the PBIST module. The example shows how to setup and use the PBIST controller.
The example configures the algorithm and memory group. Example also prints the time taken for test execution.

Use Cases
---------

 Use Case | Description
 ---------|------------
 UC-1     | Configure wrong combination of algorithm and memory group.
 UC-2     | Configure correct combination of algorithm and memory group.

# Supported Combinations {#EXAMPLES_SDL_PBIST_COMBOS}


\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^				| m4fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/pbist/pbist_mpu/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref SDL_PBIST_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\cond SOC_AM62X
\code
[MAIN_Cortex_R5_0_0] Sciclient direct init..... SUCCESS

PBIST Test Application

 Starting PBIST failure insertion test on GPU PBIST, index 0...
  Delta Cores prep time in micro secs 1484 
  Delta PBIST execution time in micro secs 13 
  Delta Cores restore time in micro secs 54 
 PBIST complete GPU PBIST, test index 0

 Starting PBIST failure insertion test on MAIN, index 2...
  Delta Cores prep time in micro secs 339 
  Delta PBIST execution time in micro secs 9 
  Delta Cores restore time in micro secs 57476 
 PBIST complete MAIN, test index 2

 Starting PBIST test on GPU PBIST, index 0...
  Delta Cores prep time in micro secs 73 
  Delta PBIST execution time in micro secs 8 
  Delta Cores restore time in micro secs 42 
 PBIST complete GPU PBIST, test index 0

 Starting PBIST test on MAIN, index 2...
  Delta Cores prep time in micro secs 176490 
  Delta PBIST execution time in micro secs 7 
  Delta Cores restore time in micro secs 83887 
 PBIST complete MAIN, test index 2

 PBIST Functionality Test Passed.

All tests have passed.  

[BLAZAR_Cortex_M4F_1] 
PBIST Test Application

 Starting PBIST failure insertion test on GPU PBIST, index 0...
  Delta Cores prep time in micro secs 3416 
  Delta PBIST execution time in micro secs 6 
  Delta Cores restore time in micro secs 2244 
 PBIST complete GPU PBIST, test index 0

 Starting PBIST failure insertion test on MPU PBIST, index 1...
  Delta Cores prep time in micro secs 9180 
  Delta PBIST execution time in micro secs 8 
  Delta Cores restore time in micro secs 8591 
 PBIST complete MPU PBIST, test index 1

 Starting PBIST failure insertion test on MAIN, index 2...
  Delta Cores prep time in micro secs 16637 
  Delta PBIST execution time in micro secs 8 
  Delta Cores restore time in micro secs 12725 
 PBIST complete MAIN, test index 2

 Starting PBIST test on GPU PBIST, index 0...
  Delta Cores prep time in micro secs 3517 
  Delta PBIST execution time in micro secs 2752 
  Delta Cores restore time in micro secs 2289 
 PBIST complete GPU PBIST, test index 0

 Starting PBIST test on MPU PBIST, index 1...
  Delta Cores prep time in micro secs 10177 
  Delta PBIST execution time in micro secs 40602 
  Delta Cores restore time in micro secs 7929 
 PBIST complete MPU PBIST, test index 1

 PBIST Functionality Test Passed.

All tests have passed. 

\endcode
\endcond
