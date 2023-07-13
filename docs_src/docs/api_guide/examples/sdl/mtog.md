# SDL MTOG Example {#EXAMPLES_SDL_MTOG}

[TOC]

# Introduction

The following shows an example of SDL MTOG API usage by the application to set up the TOG module with the usage of the various APIs.
Events can be monitored by enabling the events in the associated ESM instance.

Use Cases
---------
\cond SOC_AM62X
 Use Case | Description
 ---------|------------
 UC-1     | MAIN INSTANCE
 UC-2     | WKUP INSTANCE
\endcond
\cond SOC_AM62AX
 Use Case | Description
 ---------|------------
 UC-1     | WKUP0 INSTANCE
 UC-2     | WKUP1 INSTANCE
\endcond

# Supported Combinations {#EXAMPLES_SDL_MTOG_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | m4fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/mtog/mtog_example/

\endcond
\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/mtog/mtog_example/am62ax-sk

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref SDL_MTOG_PAGE

# Sample Output

Shown below is a sample output when the application is run,
\cond SOC_AM62X
\code

TIMER_ESM_init: Init MCU ESM complete 

 Starting MTOG test on MCU MTOG0, index 1...
 MTOG Reset done

 Delta MTOG prep time in micro secs 17 
 
 Delta MTOG execution time in micro secs 1490 
 
  Delta MTOG restore time in micro secs 2 
  MTOG complete for MCU MTOG0 
 Use case 1 passed 
 
 Starting MTOG test on WKUP MTOG0, index 2...
 MTOG Reset done

 Delta MTOG prep time in micro secs 8 
 
 Delta MTOG execution time in micro secs 2521 
 
  Delta MTOG restore time in micro secs 1 
  MTOG complete for WKUP MTOG0 
 Use case 2 passed 

 MTOG Saftey Example passed. 

\endcode
\endcond
\cond SOC_AM62AX
\code

TIMER_ESM_init: Init MCU ESM complete 

 Starting MTOG test on MCU MTOG0, index 1...
 MTOG Status Register Value for the instance1 = 2 

 MTOG Reset done

 Delta MTOG prep time in micro secs 5 
 
 Delta MTOG execution time in micro secs 6740 
 
  Delta MTOG restore time in micro secs 1 
  MTOG complete for MCU MTOG0 
 Sdl mtog instance 1 passed 

 Starting MTOG test on MCU MTOG0, index 2...
 MTOG Status Register Value for the instance2 = 1 

 MTOG Reset done

 Delta MTOG prep time in micro secs 4 
 
 Delta MTOG execution time in micro secs 6442 
 
  Delta MTOG restore time in micro secs 0 
  MTOG complete for MCU MTOG0 
 Sdl mtog instance 2 passed 

 MTOG Saftey Example passed. 

\endcode
\endcond