# LPM Suspend to IO Retention mode and Wakeup on UART pin activity

## Introduction

This example demonstrates the capability of SoC to enter IO Retention (also called partial IO) low power mode and then wakeup on detecting activity on UART pins.

::::{only} SOC_AM62DX
- This example provides support to trigger partial IO / IO Retention low power mode entry on pressing "P" on the application console
- This example provides support to wakeup the SoC using key press on MCU UART console
::::

The application configures the MCU UART to trigger wakeup. It then waits on UART to receive some character. On receiving "P" character on UART, it sends request to device manager to enter into partial IO / IO Retention low power mode.
In IO Retention low power mode, UART key press is used as an event to wake the SoC from low power mode. This is tested by pressing any key on MCU UART console.

During resume, the SBL will take the required actions to bring the SoC back to pre suspend state.
The application will be reloaded and hence will be ready to trigger partial IO entry again.

## Supported Combinations

::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/lpm/lpm_partial_io |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

:::{admonition} Attention
This example can only be tested in SD, EMMC or OSPI boot mode. It should be flashed and booted through SBL.
:::

## See Also

[Low Power Mode](../../components/drivers/lpm.md)

## Sample Output

Shown below is a sample output when the application is run,

```
[LPM Partial IO APP] Example Application Started...
[LPM PARTIAL IO APP] Press 'P' to enter partial I/O
[LPM PARTIAL IO APP] Entering partial I/O
```

Shown below is a sample output when the application resumes,

```
[LPM PARTIAL IO APP] Resume detected from pad_5...
[LPM Partial IO APP] Woken up from Partial IO...
[LPM PARTIAL IO APP] Press 'P' to enter partial I/O
```
