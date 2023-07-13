# IPC RP Message Linux Echo {#EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO}

[TOC]

# Introduction

This example shows usage of RP Message APIs to exchange messages between RTOS/NORTOS CPUs as
well as exchange message with Linux on Cortex-A CPU.

In this example,
- We create two RP Message end points
  - One end point to exchange messages with Linux kernel
  - One end point to exchange messages with Linux user space and other RTOS/NORTOS CPUs
- All cores on startup after driver initialization first wait for Linux to be ready
- Then they `announce` the end points on which they are waiting for messages to Linux.
- This is needed to be done else Linux cannot initiate message exchange with RTOS/NORTOS CPUs.
- Two tasks are then created which listen for incoming messages and echo it back to the sender.
  The sender can be Linux CPU or other RTOS/NORTOS CPUs.
- Meanwhile Linux kernel and user space test applications initiate message exchange with RTOS/NORTOS CPUs
  and wait for the echoed message.
- The example also shows a "main" RTOS/NORTOS CPU exchanging message with other RTOS/NORTOS CPUs
  by sending messages to the same end point as that where LInux sends messages.
- This shows that all CPUs can exchange messages with each other, no matter which OS or RTOS or NORTOS
  is running on the sender or receiver CPUs.
\cond SOC_AM62X
- This example provides support for gracceful shutdown of the remote core (MCU M4F). Refer \ref GRACEFUL_REMOTECORE_SHUTDOWN
- This example provides support for MCU only low power mode support on the MCU core (MCU M4F)
\endcond
# Supported Combinations

\cond SOC_AM64X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-1 freertos
 ^              | r5fss1-0 freertos
 ^              | r5fss1-1 freertos
 ^              | m4fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | am64x-evm
 Example folder | examples/drivers/ipc/ipc_rpmsg_echo_linux

\endcond


\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | m4fss0-0 freertos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/ipc/ipc_rpmsg_echo_linux

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 ^              | r5fss0-0 freertos
 ^              | c75ss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/ipc/ipc_rpmsg_echo_linux

\endcond
# Steps to Run the Example

\note This is a `system` or multi-core project, so refer to system project build instructions for CCS project or makefiles when building the example.

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). This will build all the dependant CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see \ref MAKEFILE_BUILD_PAGE). This will build all the dependant CPU makefiles as well.
- To run this demo, Linux needs to run on the Cortex A-core. Refer to **Processor SDK Linux** user guide to load and run this example.
\cond SOC_AM62X
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.
\endcond

\cond SOC_AM62X
## MCU only LPM {#EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO_MCU_ONLY_LPM}
\attention Low power mode is supported only on the Linux SPL boot flow. SBL bootflow does not support low power mode (LPM)

The following steps shows how to run MCU-only low power mode.

- Set the MCU M4F as the wake-up source on the linux kernel by running the following command. When the MCU core is set as the wake-up source, suspending the kernel will go to `MCU only sleep mode`.

\code
$ echo enabled > /sys/bus/platform/devices/5000000.m4fss/power/wakeup
\endcode

 - Go to MCU only low power mode by running the following command on the linux.

\code
$ echo mem > /sys/power/state
\endcode

 - After this the following message will appear on the MCU UART.

\code
[IPC RPMSG ECHO] Suspend request to MCU-only mode received
[IPC RPMSG ECHO] Press any key on this terminal to resume the kernel from MCU only mode
\endcode

 - Then type any key on the MCU UART to resume the kernel from LPM.

 \code
[IPC RPMSG ECHO] Key pressed. Notifying DM to wakeup main domain.
[IPC RPMSG ECHO] Main domain resumed.
\endcode


\endcond
# See Also

\ref DRIVERS_IPC_RPMESSAGE_PAGE

# Sample Output

There is no direct output from the RTOS/NORTOS CPUs on the UART or CCS console.
The output is seen on the Linux console on Cortex-A CPU.