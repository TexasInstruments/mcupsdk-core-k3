# RTC LED Blink
## Introduction

This example configures a GPIO pin connected to an LED on the EVM in output mode.
The application toggles the LED ON/OFF for 10 times using RTC Timer.

## Supported Combinations
::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/rtc/rtc_led_blink |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/rtc/rtc_led_blink |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/rtc/rtc_led_blink |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/rtc/rtc_led_blink |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/rtc/rtc_led_blink |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S or SOC_AM62LX and not SOC_AM62AX and not SOC_AM62DX and not SOC_AM62PX
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


   - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
::::

## See Also

[RTC](../../components/drivers/rtc.md)

## Sample Output

```
[RTC LED Blink Test] Starting ...
[RTC LED Blink Test] Started...
LED blinked successfully at time: 07/11/2024 14:45:12
LED blinked successfully at time: 07/11/2024 14:45:14
LED blinked successfully at time: 07/11/2024 14:45:16
LED blinked successfully at time: 07/11/2024 14:45:18
LED blinked successfully at time: 07/11/2024 14:45:20
LED blinked successfully at time: 07/11/2024 14:45:22
LED blinked successfully at time: 07/11/2024 14:45:24
LED blinked successfully at time: 07/11/2024 14:45:26
LED blinked successfully at time: 07/11/2024 14:45:28
LED blinked successfully at time: 07/11/2024 14:45:30
RTC LED blink test passed!!
```