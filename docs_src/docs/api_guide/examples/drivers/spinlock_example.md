#  Spinlock Example {#EXAMPLE_SPINLOCK}

[TOC]

# Introduction

The Spinlock module provides hardware assistance for synchronizing the processes running on multiple processors in the device.
The following example shows the working of spinlock in synchronizing multiple cores.

In this example 2 cores work simultaneously. Synchronization is achieved with the help of spinlock,
where the core is only active when it has acquired the spinlock, while the other core waits till the lock if free.


# Supported Combinations {#EXAMPLE_SPINLOCK_COMBOS}


\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | c75ss0-0 freertos
 ^              | mcu-r5fss0-0 nortos
 ^              | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/spinlock/spinlock_example/

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 ^              |ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/spinlock/spinlock_example/

\endcond

\cond SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-1 nortos
 Toolchain      | ti-arm-clang
                | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/spinlock/spinlock_example/

\endcond
# Steps to Run the Example

\note This is a `system` or multi-core project, so refer to system project build instructions for CCS project or makefiles when building the example.

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). This will build all the dependant CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see \ref MAKEFILE_BUILD_PAGE). This will build all the dependant CPU makefiles as well.
- Launch a CCS debug session and run the executables, see \ref CCS_LAUNCH_PAGE
- This is a multi-core example. Hence the executables should be loaded and run for all the above mentioned cores
\cond SOC_AM62X || SOC_AM62DX
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL.
So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.
\endcond
\cond SOC_AM62X
- Both a53 core and r5f core output through the same UART console
\endcond
# Sample Output

Shown below is a sample output when the application is run,
\if SOC_AM62X
\code
hello core 1
hello core 0
hello core 1
hello core 0
hello core 1
hello core 0
hello core 1
hello core 0
hello core 1
hello core 0
All tests have passed!!

\endcode
\else
\code
[Cortex_R5_0] hello core 0
[Cortex_R5_1] hello core 1
[Cortex_R5_0] hello core 0
[Cortex_R5_1] hello core 1
[Cortex_R5_0] hello core 0
[Cortex_R5_1] hello core 1
'' ''
'' ''
'' ''
[Cortex_R5_0] hello core 0
[Cortex_R5_1] hello core 1
[Cortex_R5_0] All Test Cases passed!

\endcode
\endif