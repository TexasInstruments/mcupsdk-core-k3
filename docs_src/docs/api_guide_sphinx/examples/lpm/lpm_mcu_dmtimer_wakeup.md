# LPM DMTimer Wakeup
## Introduction

This example shows usage of RP Message APIs to exchange messages between linux on cortex-A CPU and
RTOS/NORTOS CPUs. This example also demonstrates the capability of MCU DM-Timer timeout event to wake the
entire SOC in MCU Only low power mode.

:::{admonition} Attention
Low power mode is supported only on the Linux SPL boot flow. SBL bootflow does not support low power mode (LPM)
::::


In this example,

- We first confirm the functionality of IPC Message exchange between Linux and other cores. Refer [IPC RP Message Linux Echo](../drivers/ipc_rpmessage_linux_echo.md). This is necessary to ensure that IPC is working correctly, which is a requirement for entering low power mode.

::::{only} SOC_AM62X
   - This example provides support for graceful shutdown of the remote core (MCU M4F). Refer [Graceful shutdown of remote cores from Linux](../../developer_guides/graceful_remotecore_shutdown.md)
   - This example provides support for MCU only low power mode support on the MCU core (MCU M4F). To run MCU-only low power mode, refer [MCU only LPM](lpm_mcu_dmtimer_wakeup.md)
   - This example provides support for Deep Sleep low power mode (MCU M4F)
::::


::::{only} SOC_AM62AX
   - This example provides support for graceful shutdown of the remote core (MCU R5F). Refer [Graceful shutdown of remote cores from Linux](../../developer_guides/graceful_remotecore_shutdown.md)
   - This example provides support for MCU only low power mode support on the MCU core (MCU R5F). To run MCU-only low power mode, refer [MCU only LPM](lpm_mcu_dmtimer_wakeup.md)
   - This example provides support for Deep Sleep and IO Only plus DDR low power mode (MCU R5F).
::::


::::{only} SOC_AM62PX
   - This example provides support for graceful shutdown of the remote core (MCU R5F). Refer [Graceful shutdown of remote cores from Linux](../../developer_guides/graceful_remotecore_shutdown.md)
   - This example provides support for MCU only low power mode support on the MCU core (MCU R5F). To run MCU-only low power mode, refer [MCU only LPM](lpm_mcu_dmtimer_wakeup.md)
   - This example provides support for other low power modes on the remote core (MCU R5F)
::::

The example integrates bootloading functionality with SBL on OSPI bootmedia. It
also integrates Device manager functionality. The SBL stage 2 thread boots all
the cores along with HLOS like Linux. Refer [SBL Booting Linux From OSPI](../../developer_guides/sbl_booting_linux_ospi.md) for boot
flow sequence.

## Supported Combinations


::::{only} SOC_AM62X

| Parameter | Value |
|---|---|
| CPU + OS | m4fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/lpm/lpm_mcu_dmtimer_wakeup |


::::


::::{only} SOC_AM62AX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/lpm/lpm_mcu_dmtimer_wakeup |


::::


::::{only} SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/lpm/lpm_mcu_dmtimer_wakeup |


::::

## Steps to Run the Example

- **When using CCS projects to build**, import the system CCS project
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). This will build all the dependant CPU projects as well
- **When using makefiles to build**, build the system makefile using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md)). This will build all the dependant CPU makefiles as well.

- By default, a timeout of 10 seconds has been configured in the MCU DMTimer.

- We can modify the timeout value by modifying the `Tick Period` field in Timer Module in the example.syscfg for this example. Refer [Using SDK with SysConfig](../../developer_guides/syscfg_intro.md)

- To run this demo, Linux needs to run on the Cortex A-core. Refer to **Processor SDK Linux** user guide to load and run this example.

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

::::{only} SOC_AM62X
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62x_evm_setup.md) and power on the EVM.
::::

::::{only} SOC_AM62AX
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62ax_evm_setup.md) and power on the EVM.
::::

::::{only} SOC_AM62PX
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62px_evm_setup.md) and power on the EVM.
::::

:::{admonition} Attention
As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
::::


## MCU only LPM
- Set the wake up resume latency as 100ms for CPU0 on the linux kernel by running the following command. When the resume latency value is less, suspending the kernel will go to `MCU only sleep mode`.

```
$ echo 100000 > /sys/devices/system/cpu/cpu0/power/pm_qos_resume_latency_us
```
- Go to MCU only low power mode by running the following command on the linux.

```
$ echo mem > /sys/power/state
```
- After this, the following message will appear on the MCU UART.

```
[LPM DMTIMER WAKEUP] Next MCU mode is 1
[LPM DMTIMER WAKEUP] Suspend request to MCU-only mode received
[LPM DMTIMER WAKEUP] Starting the timer.
[LPM DMTIMER WAKEUP] Once it expires, will resume the kernel from MCU only mode
```
- Then the timer will run for the configured duration of time. Once the timer expires, it will resume the kernel from LPM. The following message will appear on the MCU UART

```
[LPM DMTIMER WAKEUP] Timer expired. Notifying DM to wakeup main domain
[LPM DMTIMER WAKEUP] Main domain resumed due to MCU DMTIMER
```
- For detailed implementation of low power modes, refer [Low power mode implementation of remote cores](../../developer_guides/low_power_mode_aware_remotecore.md)

## See Also

- [IPC RPMessage](../../components/drivers/ipc_rpmsg.md)
- [LPM MCU MCAN Wakeup](lpm_mcu_mcan_wakeup.md)
- [LPM UART Wakeup](lpm_mcu_uart_wakeup.md)

## Sample Output

There is no direct output from the RTOS/NORTOS CPUs on the UART or CCS console.
The output is seen on the Linux console on Cortex-A CPU.

