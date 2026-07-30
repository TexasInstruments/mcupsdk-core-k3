# PMIC trigger watchdog reset example
## Introduction

The example demonstrates the PMIC watchdog in trigger mode which will generate a warm reset when the core fails to send the
trigger to the watchdog. The application configures the GPIO pin and the watchdog in the PMIC to receive the trigger signal.
It services the watchdog for few iterations and stops sending the trigger signal. Then, the core will wait for sometime
based on the reset threshold value configured in the watchdog for the warm reset to occur. If the warm reset occurs, the
test passes else fails.

:::{admonition} Note
This example won't work in the debug mode as the user must not service the watchdog while in debug mode. Flash the application to get the expected result.
:::


## Supported Combinations
::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmic/pmic_trigger_watchdog_reset |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmic/pmic_trigger_watchdog_reset |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmic/pmic_trigger_watchdog_reset |

::::


## Steps

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- As it is a watchdog example, it cannot be loaded through CCS as it may fail in debug mode. It should be flashed and booted
through SBL to get the expected results.
- Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
- Or use default_pmic_trigger_watchdog_reset_hs_fs.cfg for HS-FS device, default_pmic_trigger_watchdog_reset_hs.cfg for HS-SE
device.

::::{only} SOC_AM62X
- Refer to [EVM Setup](../../getting_started/am62x_evm_setup.md) for boot mode configuration and flashing procedures.
::::

::::{only} SOC_AM62AX
- Refer to [EVM Setup](../../getting_started/am62ax_evm_setup.md) for boot mode configuration and flashing procedures.
::::

::::{only} SOC_AM62PX
- Set bootmode to [UART BOOT MODE](../../getting_started/am62px_evm_setup.md) and flash the binary using the following command from {SDK_INSTALLTION_PATH}/tools/boot

           python uart_uniflash.py -p /dev/ttyUSB0 --cfg=../../examples/drivers/pmic/pmic_trigger_watchdog_reset/am62px-sk/default_pmic_trigger_watchdog_reset_hs_fs.cfg

- Power OFF and change the boot mode to [OSPI NOR BOOT MODE](../../getting_started/am62px_evm_setup.md)
::::

::::{only} SOC_AM62DX
- Set bootmode to [UART BOOT MODE](../../getting_started/am62dx_evm_setup.md) and flash the binary using the following command from {SDK_INSTALLTION_PATH}/tools/boot

           python uart_uniflash.py -p /dev/ttyUSB1 --cfg=../../examples/drivers/pmic/pmic_trigger_watchdog_reset/am62dx-evm/default_pmic_trigger_watchdog_reset_hs_fs.cfg

- Power OFF and change the boot mode to [OSPI NOR BOOT MODE](../../getting_started/am62dx_evm_setup.md)
::::

::::{only} SOC_AM275X
- Set bootmode to [UART BOOT MODE](../../getting_started/am275x_evm_setup.md) and flash the binary using the following command from {SDK_INSTALLTION_PATH}/tools/boot

           python uart_uniflash.py -p /dev/ttyACM0 --cfg=../../examples/drivers/pmic/pmic_trigger_watchdog_reset/am275x-evm/default_pmic_trigger_watchdog_reset_hs_fs.cfg

- Power OFF and change the boot mode to [OSPI NOR BOOT MODE](../../getting_started/am275x_evm_setup.md)
::::

::::{only} SOC_AM62LX
- Refer to [EVM Setup](../../getting_started/am62lx_evm_setup.md) for boot mode configuration and flashing procedures.
::::

::::{only} SOC_AM62PX or SOC_AM62DX or SOC_AM275X
- Logs should appear at the MCU_UART0
::::

## See Also

[PMIC](../../components/board/pmic.md)

## Sample Output

Shown below is a sample output when the application is run,

```
Starting trigger watchdog reset example !!
Configure GPIO trigger watchdog pin in the PMIC... DONE
Configure PMIC watchdog in Trigger mode... DONE
Started watchdog sequence... Sending watchdog trigger signal to the PMIC...
Stopped sending watchdog trigger signal... Waiting for the warm reset to occur...
Warm reset has occurred due to watchdog failure!!
All tests have passed!!
```