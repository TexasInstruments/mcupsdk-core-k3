# IPC RP Message QNX Echo
## Introduction

This example shows usage of RP Message APIs to exchange messages between RTOS/NORTOS CPUs as
well as exchange message with QNX on Cortex-A CPU.

- One "main" CPU, sends multi-byte messages to other "remote" CPUs using the RP Message APIs
- The "remote" CPUs, then echo back the same message to the main CPUs
- Once all messages are echoed the main CPU exits. The remote CPUs remain waiting to receive new messages.


::::{only} SOC_AM62PX
   The example integrates bootloading funtionality with SBL on OSPI bootmedia. It
   also integrates Device manager functionality. The SBL stage 2 thread boots all
   the cores along with HLOS like Linux. Refer [SBL Booting Linux From OSPI](../../developer_guides/sbl_booting_linux_ospi.md) for boot
   flow sequence.
::::


## Supported Combinations


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | m4fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo_qnx |

::::


::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo_qnx |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/ipc/ipc_rpmsg_echo_qnx |

::::

## Steps to Run the Example


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX
   - **When using CCS projects to build**, import the system CCS project
     and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependant CPU projects as well
   - **When using makefiles to build**, build the system makefile using
     make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependant CPU makefiles as well.
   - To run this demo, QNX needs to run on the Cortex A-core. Refer to **Processor SDK QNX** user guide to load and run this example.
::::


::::{only} SOC_AM62PX
   - This example integrates SBL on OSPI bootmedia which needs to be flashed on the
   EVM flash, along with sample application images for MCU R5 CPUs, HSM M4F and
   Linux Appimage.

   - For HS-FS device, use **default_sbl_ospi_qnx_hs_fs.cfg** as the cfg file.

   - To flash to the EVM, refer to [Flash a Hello World example](../../getting_started/getting_started_flash.md) .

   - Example, assuming SDK is installed at `C:/ti/mcu_plus_sdk` and this example
   and IPC application is built using makefiles, and Linux Appimage is already
   created, in Windows,

           cd C:/ti/mcu_plus_sdk/tools/boot
           python uart_uniflash.py -p COM13 --cfg=C:/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_qnx_hs_fs.cfg

   - If Linux PC is used, assuming SDK is installed at `~/ti/mcu_plus_sdk`

           cd ~/ti/mcu_plus_sdk
           python uart_uniflash.py -p /dev/ttyUSB0 --cfg=~/ti/mcu_plus_sdk/tools/boot/sbl_prebuilt/{{ VAR_BOARD_NAME_LOWER }}/default_sbl_ospi_qnx_hs_fs.cfg

   - Switch to [OSPI NOR BOOT MODE](../../getting_started/am62px_evm_setup.md) and power on the EVM.

   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::
   :::


## See Also

[IPC RPMessage](../../components/drivers/ipc_rpmsg.md)

## Sample Output

There is no direct output from the RTOS/NORTOS CPUs on the UART or CCS console.
The output is seen on the QNX console on Cortex-A CPU.
