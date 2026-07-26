# IPC RP Message Linux Echo
## Introduction

This example shows usage of RP Message APIs to exchange messages between RTOS/NORTOS CPUs as
well as exchange message with Linux on Cortex-A CPU.

In this example,
- We create two RP Message end points
  - One end point to exchange messages with Linux kernel
  - One end point to exchange messages with Linux user space and other RTOS/NORTOS CPUs
- All cores on startup after driver initialization first wait for Linux to be ready
- Then they `announce` the end points on which they are waiting for messages to Linux.
- This is needed to be done else Linux cannot initiate message exchange with RTOS/NORTOS CPUs.
- In case of remotecores, suspend task is created to enable graceful suspend in low power mode.
- Two tasks are then created which listen for incoming messages and echo it back to the sender.
  The sender can be Linux CPU or other RTOS/NORTOS CPUs.
- Meanwhile Linux kernel and user space test applications initiate message exchange with RTOS/NORTOS CPUs
  and wait for the echoed message.
- The example also shows a "main" RTOS/NORTOS CPU exchanging message with other RTOS/NORTOS CPUs
  by sending messages to the same end point as that where LInux sends messages.
- This shows that all CPUs can exchange messages with each other, no matter which OS or RTOS or NORTOS
  is running on the sender or receiver CPUs.

::::{only} SOC_AM62X
   - This example provides support for graceful shutdown of the remote core (MCU M4F). Refer [Graceful shutdown of remote cores from Linux](../../developer_guides/graceful_remotecore_shutdown.md)
   - This example provides support for MCU only low power mode support on the MCU core (MCU M4F)
   - This example provides support for Deep Sleep low power mode (MCU M4F)
::::


::::{only} SOC_AM62AX
   - This example provides support for graceful shutdown of the remote core (MCU R5F/ C7X). Refer [Graceful shutdown of remote cores from Linux](../../developer_guides/graceful_remotecore_shutdown.md)
   - This example provides support for MCU only low power mode support on the MCU core (MCU R5F)
   - This example provides support for Deep Sleep and IO Only plus DDR low power mode (MCU R5F/ C7X).
::::


::::{only} SOC_AM62DX
   - This example provides support for graceful shutdown of the remote core (MCU R5F/ C7X). Refer [Graceful shutdown of remote cores from Linux](../../developer_guides/graceful_remotecore_shutdown.md)
::::


::::{only} SOC_AM62PX
   - This example provides support for graceful shutdown of the remote core (MCU R5F). Refer [Graceful shutdown of remote cores from Linux](../../developer_guides/graceful_remotecore_shutdown.md)
   - This example provides support for MCU only low power mode support on the MCU core (MCU R5F)
   - This example provides support for other low power modes on the remote core (MCU R5F)

   The example integrates bootloading functionality with SBL on OSPI bootmedia. It
   also integrates Device manager functionality. The SBL stage 2 thread boots all
   the cores along with HLOS like Linux. Refer [SBL Booting Linux From OSPI](../../developer_guides/sbl_booting_linux_ospi.md) for boot
   flow sequence.
::::

## Supported Combinations


::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-1 freertos |
| CPU + OS | r5fss1-0 freertos |
| CPU + OS | r5fss1-1 freertos |
| CPU + OS | m4fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | am64x-evm |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo_linux |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | m4fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo_linux |

::::


::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo_linux |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo_linux |

::::

## Steps to Run the Example


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX
   - **When using CCS projects to build**, import the system CCS project
     and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependant CPU projects as well
   - **When using makefiles to build**, build the system makefile using
     make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependant CPU makefiles as well.
   - To run this demo, Linux needs to run on the Cortex A-core. Refer to **Processor SDK Linux** user guide to load and run this example.
::::


::::{only} SOC_AM62X
   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


   - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62PX
   **MCU only LPM**
   :::{admonition} Attention
   Low power mode is supported only on the Linux SPL boot flow. SBL bootflow does not support low power mode (LPM)
   :::


   The following steps shows how to run MCU-only low power mode.

   - Set the wake up resume latency as 100ms for CPU0 on the linux kernel by running the following command. When the resume latency value is less, suspending the kernel will go to `MCU only sleep mode`.

      $ echo 100000 > /sys/devices/system/cpu/cpu0/power/pm_qos_resume_latency_us
   
    - Go to MCU only low power mode by running the following command on the linux.

      $ echo mem > /sys/power/state
   
    - After this the following message will appear on the MCU UART.

      [IPC RPMSG ECHO] Next MCU mode is 1
   [IPC RPMSG ECHO] Suspend request to MCU-only mode received
   [IPC RPMSG ECHO] Press a single key on this terminal to resume the kernel from MCU only mode
   
    - Then type any key on the MCU UART to resume the kernel from LPM.

       [IPC RPMSG ECHO] Key pressed. Notifying DM to wakeup main domain
   [IPC RPMSG ECHO] Main domain resumed due to MCU UART
   
   - For detailed implementation of low power modes, refer [Low power mode implementation of remote cores](../../developer_guides/low_power_mode_aware_remotecore.md)

::::


::::{only} SOC_AM62PX
   - This example integrates SBL on OSPI bootmedia which needs to be flashed on the
   EVM flash, along with sample application images for MCU R5 CPUs, HSM M4F and
   Linux Appimage.

   - For HS-FS device, use **default_sbl_ospi_linux_hs_fs.cfg** as the cfg file.

   - To flash to the EVM, refer to [Flash a Hello World example](../../getting_started/getting_started_flash.md) .

   - Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example
   and IPC application is built using makefiles, and Linux Appimage is already
   created, in Windows,

           cd C:/ti/mcu_plus_sdk/tools/boot
           python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_linux_hs_fs.cfg

   - If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

           cd ~/ti/mcu_plus_sdk
           python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_linux_hs_fs.cfg

   - Switch to [OSPI NOR BOOT MODE](../../getting_started/am62px_evm_setup.md) and power on the EVM.

   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::
   :::


## See Also

[IPC RPMessage](../../components/drivers/ipc_rpmsg.md)

## Sample Output

There is no direct output from the RTOS/NORTOS CPUs on the UART or CCS console.
The output is seen on the Linux console on Cortex-A CPU.
