# XIP Benchmark {#EXAMPLES_BENCHMARKS_XIP_BENCHMARK}

[TOC]

# Introduction

This example shows a application running in XIP (eXecute In Place) mode. This example can be used to check and evaluate the performance
of the SOC when running in XIP mode.

The example does the below
- SOC is booted to run applications for multiple CPUs
- The bootloader configures the flash at highest possible speed and highest throughput mode.
\cond SOC_AM275X
- On @VAR_SOC_NAME, this means, the flash is in
  - Direct access (DAC) mode for read
  - Dual data rate (DDR) mode
  - OSPI and flash at 166Mhz clock speed
  - OSPI Phy enable
  - OSPI Phy pipeline enabled.
\endcond
- All the CPUs are configured to run FreeRTOS with below functions being executed.
  - FIR function, here, code, input data and coeff data is kept in flash
  - memcpy function, here, code, input data is kept in flash
- The linker command file of the CPUs is setup so that code and rodata is execute and referenced from flash.
- An MPU entry is setup at each CPU, to enable execute from flahs region with cache enabled.
- Each function is run multiple times and the worst case, best case and average case performance is printed on the
  UART terminal in units of cycles.
- There is a compile time flag `ENABLE_CPU_SYNC` to "sync" all the CPUs such that all execute and access the code and data from flash
  at the approximately the same time. This allows to simulate the worst case simultaneous access to the flash device in multi CPU environment.
  **NOTE**, by default, `ENABLE_CPU_SYNC` is `0`, i.e the CPUs are not synced.

# Supported Combinations

\cond SOC_AM275X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/xip_benchmark/

\endcond

# Steps to Run the Example

\note This is a `system` or multi-core project, so refer to system project build instructions for CCS project or makefiles when building the example.

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). This will build all the dependant CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see \ref MAKEFILE_BUILD_PAGE). This will build all the dependant CPU makefiles as well.

- This program cannot be loaded and run from CCS since it expects some sections of code/data to reside in flash

- To flash this program use the sample config file located at below.

\cond SOC_AM275X
        examples/benchmarks/xip_benchmark/@VAR_BOARD_NAME_LOWER/r5fss0-0_freertos/xip_benchmark_sbl_ospi_hs_fs.cfg
\endcond

- This config file has the filenames listed assuming application is built using makefile's and release profile.
  If you are using CCS projects or debug profile, edit this file to point to appropriate files.

- Now flash to EVM using the steps mention here, only use the config file mentioned above, \ref GETTING_STARTED_FLASH

- This is a multi-core example. Above steps will flash applications for all the CPUs.

# Sample Output


Shown below is a sample output when the application is run on am275x,

\code
Starting OSPI Bootloader ... 

SYSFW Firmware Version 11.0.6--v11.00.06 (Fancy Rat)
SYSFW Firmware revision 0xb
SYSFW ABI revision 4.0

[KPI] Boot Media       : FLASH 
[KPI] Boot Media Clock : 166.667 MHz 
[KPI] Boot Image Size  : 417 KB 
[KPI] Cores present    : 
[KPI] TIFS init                        :        691us 
[KPI] System_init                      :       1879us 
[KPI] Board_init                       :          2us 
[KPI] FreeRtosTask Create              :        297us 
[KPI] Drivers_open                     :        103us 
[KPI] Board_driversOpen                :          0us 
[KPI] sciServer_init                   :      15073us 
[KPI] SBL Drivers_open                 :       3174us 
[KPI] SBL Board_driversOpen            :       2907us 
[KPI] Sciclient Get Version            :      10023us 
[KPI] R5FSS0_0 Image Load              :       1454us 
[KPI] R5FSS0_1 Image Load              :       1563us 
[KPI] R5FSS1_0 Image Load              :       1568us 
[KPI] R5FSS1_1 Image Load              :       1554us 
[KPI] DSP 0 Image Load                 :       6967us 
[KPI] DSP 1 Image Load                 :       6791us 
[KPI] SBL Total Time Taken             :      54054us 

Image loading done...
Starting RTOS/Baremetal applications


### XIP benchmark ###
FIR:
  24048 cycles (code/data fully cached) ,
  66113 cycles (code/data not cached) ,
  28256 cycles (code/data not-cached 1 of 10 iterations)
MEMCPY:
   1566 cycles (code/data fully cached) ,
   4497 cycles (code/data not cached) ,
   1864 cycles (code/data not-cached 1 of 10 iterations)
All tests have passed!!
\endcode
