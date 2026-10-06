# MCU-Initiated Partial IO Mode {#EXAMPLES_LPM_PARTIAL_IO_RTOS_INITIATED}

[TOC]

# Introduction

This example shows RP Message APIs exchanging messages between linux on a cortex-A CPU and RTOS/NORTOS CPUs. This example also demonstrates the capability of RTOS running on the MCU core to initiate the Partial IO low power mode entry as well as demonstrates the SoC to receiving triggers on MCU MCAN IO to wake the entire SOC from Partial IO low power mode.

\attention Partial IO mode is supported only in the Linux SPL bootflow. SBL bootflow does not support any LPM.

In this example,
- We first confirm the functionality of IPC Message exchange between Linux and other cores. Refer \ref EXAMPLES_DRIVERS_IPC_RPMESSAGE_LINUX_ECHO. This is necessary to ensure that IPC is working correctly, which is a requirement for entering Partial IO mode.
- MCU MCAN IO is configured as a wakeup source.
- All cores on startup after driver initialization wait for linux to be ready.
- After the IPC channel is initialized, a suspend task is created for the remote cores to initiate Partial IO mode entry after receiving character "P" on application console.
- On receiving character, the remote core verifies if the linux has been powered off and sends message to device manager to enter Partial IO mode.

The software flow is illustrated below:

\imageStyle{lpm_partial_io_sw_flow.png,width:80%}
\image html lpm_partial_io_sw_flow.png Partial IO Mode Software Flow.

# Supported Combinations

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | m4fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_SK_LP_BOARD_NAME_LOWER
 Example folder | examples/lpm/lpm_partial_io

\endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/lpm/lpm_partial_io

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/lpm/lpm_partial_io

\endcond

# Steps to Run the Example

- **Hardware Connectivity**
  - Connect **MCU UART0** (MCU_UART0_RXD / MCU_UART0_TXD) to PC via USB-to-UART adapter
  - Used for user input character and logging output
  - Standard 115200 baud, 8N1 configuration

- Linux needs to run on the Cortex A-core. Refer to the **Processor SDK Linux** user guide on how to create an SD card for booting Linux.

\cond SOC_AM62X
- In order to enable this mode, 
    - Remove the **system-power-controller** property from k3-am62-lp-sk.dts device tree file. This property is used to indicate who is the power controller of system. As MCU is the controller now, this must not be set.
    - Ensure that MCU_MCAN is not claimed by linux. As MCU MCAN is a wakeup source, it should be owned only by MCU. To ensure this, check the k3-am62-lp-sk.dts file to confirm that mcu_mcan0 node has **status = "disabled"**.
\endcond

\cond SOC_AM62AX
- In order to enable this mode, 
    - Remove the **system-power-controller** property from k3-am62a7-sk.dts device tree file. This property is used to indicate who is the power controller of system. As MCU is the controller now, this must not be set.
    - Ensure that MCU_MCAN is not claimed by linux. As MCU MCAN is a wakeup source, it should be owned only by MCU. To ensure this, check the k3-am62a7-sk.dts file to confirm that mcu_mcan0 node has **status = "disabled"**.
\endcond

\cond SOC_AM62PX
- In order to enable this mode, 
    - Remove the **system-power-controller** property from k3-am62p5-sk.dts device tree file. This property is used to indicate who is the power controller of system. As MCU is the controller now, this must not be set.
    - Ensure that MCU_MCAN is not claimed by linux. As MCU MCAN is a wakeup source, it should be owned only by MCU. To ensure this, check the k3-am62p5-sk.dts file to confirm that mcu_mcan0 node has **status = "disabled"**.
\endcond

- Rebuild and flash the SD card after doing the above changes for device tree file.

- Once linux boots, the remoteproc driver will load the RTOS application on MCU core and request to release it from reset.

- Then, when MCU application boots, the initialization logs will be printed on MCU UART console(/dev/tty3)

- The application will be waiting to trigger Partial IO low power mode entry. Press "P" character in the application console to enter into Partial IO mode.

- Some LEDs on the board will turn off indicating that the SoC has entered low power mode.

- To resume the system, wakeup from MCAN pins can be triggered by grounding Pin 22 of J8 MCU header.

\cond SOC_AM62AX

\note In order to enter partial IO, J9 must not be connected on AM62A-SK EVM.

\endcond

\cond SOC_AM62PX

\note In order to enter partial IO, J12 must not be connected on AM62P-SK EVM.

\endcond

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). This will build all the dependant CPU projects as well
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_IPC_NOTIFY_PAGE
\ref EXAMPLES_LPM_MCU_UART_WAKEUP
\ref EXAMPLES_LPM_MCU_MCAN_WAKEUP
\ref EXAMPLES_LPM_IO_RETENTION_MCAN_WAKEUP

# Sample Output

Shown below is a sample output when the application is run,MCU UART output on MCU core:
\code
[LPM PARTIAL IO APP] Example Application Started...
[LPM PARTIAL IO APP] Press 'P' to enter partial I/O
[LPM PARTIAL IO APP] Remote Core waiting for messages at end point 13 ... !!!
[LPM PARTIAL IO APP] Remote Core waiting for messages at end point 14 ... !!!
[LPM PARTIAL IO APP] Remoteproc mailbox message sent successfully
[LPM PARTIAL IO APP] Sent poweroff req to Linux
[LPM PARTIAL IO APP] A53 powered off (took 3000 ms)
[LPM PARTIAL IO APP] Entering partial I�[LPM PARTIAL IO APP] Example Application Started...
[LPM PARTIAL IO APP] Press any character to enter partial I/O
[LPM PARTIAL IO APP] Remote Core waiting for messages at end point 13 ... !!!
\endcode

Linux console output shows graceful shutdown:

\code
Calling orderly_poweroff()
[  OK  ] Removed slice Slice /system/modprobe.
...
(shutdown sequence continues until power cut-off)
\endcode