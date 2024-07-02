# DDR PERF Test {#EXAMPLES_DRIVERS_DDR_PERF}

# Introduction

This example prints the read, write and total DDR bandwidth during memcpy operation. The memcpy operation is done on
source and destination buffers allocated from DDR scratch region. The cache is disabled for this memory region.
The values are calculated using the DDR performance counter registers available in DDR Subsystem. First performance counter
is configured to count write operations and second one is configured to count read operations. The idle thread updates the DDR
performance load stats.


# Supported Combinations {#EXAMPLES_DRIVERS_DDR_PERF_COMBOS}

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/ddr/ddr_perf/

\endcond

\cond SOC_AM62AX || SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/ddr/ddr_perf/

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/ddr/ddr_perf/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.

# See Also

\ref DRIVERS_DDR_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
DDR performance statistics
==========================
DDR: READ  BW: AVG =    285 MiB/s
DDR: WRITE BW: AVG =    323 MiB/s
DDR: TOTAL BW: AVG =    608 MiB/s
totalTime = 2354274
totalRead = 671249664
totalWrite = 761457664
\endcode
