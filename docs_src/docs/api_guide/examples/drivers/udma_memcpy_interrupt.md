# UDMA Memcpy Interrupt {#EXAMPLES_DRIVERS_UDMA_MEMCPY_INTERRUPT}

[TOC]

# Introduction

This example performs UDMA block copy transfer using Type 15 Transfer Record (TR15)
using Transfer Record Packet Descriptor (TRPD) in interrupt mode.

The application opens and configures a BCDMA channel using SysConfig.
It also configures the interrupt mode of operation through the SysConfig
which ensures that all required interrupt configuration are done.
The callback function App_udmaEventCb is registered via SysConfig.

Then the application prepares a TRPD for a 1D transfer from source to
destination buffer, submits the request to DMA, waits for the DMA to complete
by waiting on a semaphore which is posted in the callback function.

Once the transfer it completes, it does cache operation for data coherency
and compares the source and destination buffers for any data mismatch.

# Supported Combinations {#EXAMPLES_DRIVERS_UDMA_MEMCPY_INTERRUPT_COMBOS}

\cond SOC_AM64X
\attention A53 NORTOS, A53 FREERTOS and A53 FREERTOS SMP support is experimental and is NOT supported by TI. \n
\endcond

\cond SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 ^              | r5fss0-1 freertos
 ^              | r5fss1-0 freertos
 ^              | r5fss1-1 freertos
 ^              | a53ss0-0 nortos
 ^              | a53ss0-0 freertos
 ^              | a53ss0-0 freertos-smp
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/udma/udma_memcpy_interrupt

\endcond

\cond SOC_AM243X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 ^              | r5fss0-1 freertos
 ^              | r5fss1-0 freertos
 ^              | r5fss1-1 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/udma/udma_memcpy_interrupt

\endcond

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/drivers/udma/udma_memcpy_interrupt

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | a53ss0-0 nortos
 Toolchain      | ti-arm-clang
 ^              | arm.gnu.aarch64-none
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/udma/udma_memcpy_interrupt

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/udma/udma_chaining

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
\cond !SOC_AM62PX
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\endcond
\cond SOC_AM62X || SOC_AM62PX
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL.
 So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.
\endcond

# See Also

\ref DRIVERS_UDMA_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
[UDMA] Memcpy application started ...
All tests have passed!!
\endcode
