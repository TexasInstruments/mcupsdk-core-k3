# DMA Utils autoincrement compression example {#EXAMPLES_DMAUTILS_AUTOINC_COMPRESSION}

[TOC]

# Introduction

Demostrates a simple example of auto increment DMA to allow DSP to operate a function on internal memory and transfer back the result with compression.

\if SOC_AM62AX
\code
The application runs on C7x core. UDMA is configured for UTC/DRU mode.
\endcode

# Supported Combinations

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/dmautils/dmautils_autoinc_compression/

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

# Sample Output

Shown below is a sample output when the benchmark application is run,
\if SOC_AM62AX

**c7x core:**
\code
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 0,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 1,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 2,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 3,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 4,        PASSED
width  : 1024
height : 128
Tensor Filled
Tensor Compressed
Tensor Un-compressed
DMAUtils Compression TestCase 0,        PASSED
All tests have passed!!
\endcode
\endif