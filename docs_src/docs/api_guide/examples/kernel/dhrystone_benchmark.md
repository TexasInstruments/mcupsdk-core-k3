# Dhrystone benchmarking demo {#EXAMPLES_KERNEL_FREERTOS_DHRYSTONE_BENCHMARK}

[TOC]

# Introduction

This example shows an application for benchmarking the FreeRTOS SMP kernel and single core FreeRTOS kernel using dhrystone benchmarking.

The application runs the the dhrystone benchmarking demo using the given number of threads and iterations and logs the results as the number of dhrystones run per second.

\if SOC_AM64X
\code
The application runs with thread number equal to 1, 2, 5 and 10, with iteration number 10000000.
\endcode

\elseif SOC_AM62AX
\code
The application runs with thread number equal to 1, 2, 5 and 10, with iteration number 30000000.
\endcode

\elseif SOC_AM62X
\code
The application runs with thread number equal to 1, 2, 5 and 10, with iteration number 30000000.
\endcode
\endif
# Supported Combinations

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 ^              | a53ss0-0 freertos-smp
 ^              | mcu-r5fss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 ^              | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/dhrystone_benchmark/

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/dhrystone_benchmark/

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/dhrystone_benchmark/

\endcond

\cond SOC_AM64X
\attention A53 NORTOS, A53 FREERTOS and A53 FREERTOS SMP support is experimental and is NOT supported by TI. \n
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 ^              | a53ss0-0 freertos-smp
 Toolchain      | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/dhrystone_benchmark/

\endcond



# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\if SOC_AM62PX
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\elseif SOC_AM62X
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\else
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE and \ref SMP_FREERTOS_GUIDE
\endif

# See Also

\ref KERNEL_DPL_PAGE

# Sample Output

Shown below is a sample output when the benchmark application is run,
\if SOC_AM64X
\code
[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 1
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 1299

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 2
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 1183

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 5
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 281

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 10
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 50

All tests have passed!!
\endcode

\elseif SOC_AM62AX

**a53 core:**
\code
[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 1
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 7602697.5

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 2
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 7623452.5

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 5
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 7652666.5

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 10
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 7656853.0

All tests have passed!!
\endcode

**mcu-r5f core:**
\code
[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 1
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 3123048.2

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 2
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 3110581.2

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 5
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 3110678.0

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 10
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 3110710.2

All tests have passed!!
\endcode

\elseif SOC_AM62PX

**mcu-r5f core:**
\code
[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 1
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 3123048.2

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 2
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 3114779.8

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 5
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 3113519.0

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 10
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 3114779.8

All tests have passed!!
\endcode

\elseif SOC_AM62X
**a53 core:**
\code

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 1
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 7603214.0

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 2
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 7624002.5

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 5
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 7653215.5

[DHRYSTONE BENCHMARKING] Iterations                       : 30000000
[DHRYSTONE BENCHMARKING] Threads                          : 10
[DHRYSTONE BENCHMARKING] Dhrystones per second            : 7657410.0

All tests have passed!!
\endcode
\endif