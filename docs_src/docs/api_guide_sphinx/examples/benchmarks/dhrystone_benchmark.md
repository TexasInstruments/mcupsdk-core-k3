# Dhrystone Benchmark 



## Introduction

Dhrystone is a synthetic benchmark that measures and compares processor performance.

The Dhrystone benchmark program contains 52 assignments, 33 control statements and 17 procedures/ function calls. Unlike Whetstone benchmarking, the program doesn't contain floating point operation and concentrates on string handling and standard code, heavily influenced by hardware and software design, compiler and linker options, code optimizing, cache memory, wait states and integer data types.
103 statements are dynamically executed.

## Supported Combinations 
::::{only} SOC_AM62X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Boards         | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}
 Example folder | examples/benchmarks/dhrystone_benchmark
::::

::::{only} SOC_AM62LX
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | a53ss0-0 freertos
 Toolchain      | arm.gnu.aarch64-none
 Boards         | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/benchmarks/dhrystone_benchmark
::::

::::{only} SOC_AM275X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | {{ VAR_BOARD_NAME_LOWER }}
 Example folder | examples/benchmarks/dhrystone_benchmark
::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [CCS_PROJECTS_PAGE](#ccs_projects_page)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [MAKEFILE_BUILD_PAGE](#makefile_build_page))
::::{only} SOC_AM62LX
- To Load and Run an example (see [DFU_LOAD_CCS_DEBUG](#dfu_load_ccs_debug))
::::
::::{only} not SOC_AM62LX
- Launch a CCS debug session and run the executable, see [CCS_LAUNCH_PAGE](#ccs_launch_page)
::::

### Sample output for Dhrystone benchmark example

::::{only} SOC_AM62X
\code
BENCHMARK START - DHRYSTONE

Dhrystone Benchmark, Version 2.1 (Language: C)

- BEGIN cycle count:                         14
- END Cycle count:                           99582466
- USER cycle count:                          99582452

BENCHMARK Using clock 1400000000
- Usertime in sec:                           0.071130
- Microseconds for one run through Dhrystone:   0.1
- Dhrystones per Second:                     7029351.2

Normalized MIPS/MHz:                         2.8577
BENCHMARK END

 All tests have passed.
\endcode
::::

::::{only} SOC_AM62LX
\code
 BENCHMARK START - DHRYSTONE

Dhrystone Benchmark, Version 2.1 (Language: C)

- BEGIN cycle count:                         15
- END Cycle count:                           99502570
- USER cycle count:                          99502555

BENCHMARK Using clock 1250000000
- Usertime in sec:                           0.079602
- Microseconds for one run through Dhrystone:   0.2
- Dhrystones per Second:                     6281246.0

Normalized MIPS/MHz:                         2.8600
BENCHMARK END

 All tests have passed.
\endcode
::::

::::{only} SOC_AM275X
\code

 BENCHMARK START - DHRYSTONE

Dhrystone Benchmark, Version 2.1 (Language: C)

- BEGIN cycle count:                         7
- END Cycle count:                           153441801
- USER cycle count:                          153441794

BENCHMARK Using clock 1000000000
- Usertime in sec:                           0.153442
- Microseconds for one run through Dhrystone:   0.3
- Dhrystones per Second:                     3258564.8

Normalized MIPS/MHz:                         1.8546
BENCHMARK END

 All tests have passed.
\endcode
::::