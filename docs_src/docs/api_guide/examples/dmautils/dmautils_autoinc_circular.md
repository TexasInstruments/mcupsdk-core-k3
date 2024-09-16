# DMA Utils autoincrement circular example {#EXAMPLES_DMAUTILS_AUTOINC_CIRCULAR}

[TOC]

# Introduction

Demostrates a simple application demonstrating 2D auto increment feature with circularity enabled of dmautils

The application runs on C7x core. UDMA is configured for UTC/DRU mode.

# Supported Combinations

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/dmautils/dmautils_autoinc_circular/

\endcond

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/dmautils/dmautils_autoinc_circular/

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
DMAUtils TestCase 0,        PASSED
All tests have passed!!
\endcode
\endif

\if SOC_AM62DX

**c7x core:**
\code
DMAUtils TestCase 0,        PASSED
All tests have passed!!
\endcode
\endif