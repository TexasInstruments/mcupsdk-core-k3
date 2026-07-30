# Watchdog interrupt mode
## Introduction

This example uses the WDT module in non reset mode to generate NMI Interrupt.
- The Watchdog interrupt is configured as a non-maskable interrupt and the user-defined callback function is registered.
- ESM module is configured with ESM Group 2 number and ESM NMI number to generate a non-maskable interrupt to the CPU.
- The callback function in the application handles the watchdog interrupt

## Supported Combinations
::::{only} SOC_AM273X or SOC_AWR294X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | c66ss0 nortos |
| Toolchain | ti-arm-clang, ti-c6000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/watchdog/watchdog_interrupt/ |

::::


::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | a53ss0-0 nortos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/watchdog/watchdog_interrupt/ |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/watchdog/watchdog_interrupt/ |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/watchdog/watchdog_interrupt/ |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/watchdog/watchdog_interrupt/ |

::::


::::{only} SOC_AM62LX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | a53ss0-0 nortos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/watchdog/watchdog_interrupt/ |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/watchdog/watchdog_interrupt/ |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/watchdog/watchdog_interrupt/ |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/watchdog/watchdog_interrupt/ |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM62LX
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM62X
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
   - Please select the UART port used for console as mentioned in [Setup UART Terminal](../../getting_started/am62x_evm_setup.md)
::::
::::{only} SOC_AM62AX
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
   - Please select the UART port used for console as mentioned in [Setup UART Terminal](../../getting_started/am62ax_evm_setup.md)
::::
::::{only} SOC_AM62DX
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
   - Please select the UART port used for console as mentioned in [Setup UART Terminal](../../getting_started/am62dx_evm_setup.md)
::::
::::{only} SOC_AM62PX
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
   - Please select the UART port used for console as mentioned in [Setup UART Terminal](../../getting_started/am62px_evm_setup.md)
::::
::::{only} SOC_AM275X
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
   - Please select the UART port used for console as mentioned in [Setup UART Terminal](../../getting_started/am275x_evm_setup.md)
::::
::::{only} SOC_AM62LX
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
   - Please select the UART port used for console as mentioned in [Setup UART Terminal](../../getting_started/am62lx_evm_setup.md)
::::
::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::


## See Also

[WATCHDOG](../../components/drivers/watchdog.md)

## Sample Output

Shown below is a sample output when the application is run,
Please note that application prints in both CCS and UART console.

::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM275X or SOC_AM62LX or SOC_AM62PX

   ```
   Watchdog interrupt Mode Test Started ...
   Watchdog Driver NMI received
   All tests have passed!!
   ```

::::


::::{only} SOC_AM273X or SOC_AWR294X or SOC_AM64X or SOC_AM243X or SOC_AM263X

   **CCS Console:**

   ```
   [Cortex_R5_0] Watchdog interrupt Mode Test Started ...
   Watchdog Driver NMI received
   All tests have passed!!
   ```

   **UART Console:**

   ```
   Watchdog interrupt Mode Test Started ...
   Watchdog Driver NMI received
   All tests have passed!!
   ```

::::
