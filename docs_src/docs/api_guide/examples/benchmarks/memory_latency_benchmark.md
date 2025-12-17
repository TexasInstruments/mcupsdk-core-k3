# Memory Access Latency Benchmark {#EXAMPLES_MEMORY_LATENCY_BENCHMARK}

[TOC]

# Supported Combinations {#EXAMPLES_MEMORY_LATENCY_BENCHMARK_COMBOS}
\cond SOC_AM275X
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/memory_latency_benchmark
\endcond

# Introduction

- This demo provides a rough measurement of the time taken for a Read or Write instruction to be executed at different memory regions (OCRAM, TCM).
- The demo uses simple assembly load and store commands to read the data at a specific memory location in different regions.
- The example does the following:
  1. Initializes the drivers and board
  2. Calls the Read functions at TCM, OCRAM, Non self TCM (peripheral address) for 32-bit and 64-bit access.
  3. The Read 32-bit functions consist of 32 commands for reading from 32-bit (4-byte) register.
  4. The Read 64-bit functions consist of 32 commands for reading from two 32-bit (4-byte) registers.
  5. Average cycles per byte is calculated in example.

# Performance statistics

\cond SOC_AM275X

## AM275x
Operation | Latency(ns)/byte |
----------------|-----------|
Read (32-bit access) - TCM          | 0.796875 |
Read (32-bit access) - OCRAM        | 9.234375 |
Read (32-bit access) - Non self TCM | 35.320312 |
Read (64-bit access) - TCM          | 0.300781 |
Read (64-bit access) - OCRAM        | 4.617188 |
Read (64-bit access) - Non self TCM | 17.660156 |

\endcond

# Steps to Run the Example

## Building Memory access latency application

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- When using makefiles to build, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Running the Memory access latency application

Flash the application binary to the device, follow the steps mentioned here
 (see \ref GETTING_STARTED_FLASH).

## Sample output for Memory access latency example

\cond SOC_AM275X
\code
BENCHMARK START - ARM R5F - Memory Access latency

[32-BIT READ] Self TCM Access Average Latency Per Byte: 0.796875 ns
[32-BIT READ] MSRAM Access Average Latency Per Byte: 9.234375 ns
[32-BIT READ] Non-Self TCM Access Average Latency Per Byte: 35.320312 ns

[64-BIT READ] Self TCM Access Average Latency Per Byte: 0.300781 ns
[64-BIT READ] MSRAM Access Read Average Latency Per Byte: 4.617188 ns
[64-BIT READ] Non-Self TCM Access Read Average Latency Per Byte: 17.660156 ns

BENCHMARK END
\endcode
\endcond

