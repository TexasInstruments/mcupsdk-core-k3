# MCSPI Loopback
## Introduction

This example demonstrates the McSPI RX and TX operation configured
in blocking, interrupt mode of operation.

This example sends a known data in the TX mode of length APP_MCSPI_MSGSIZE
and then receives the same in RX mode. Internal pad level loopback mode
is enabled to receive data.
To enable internal pad level loopback mode, D0 pin is configured to both
TX Enable as well as RX input pin in the SYSCFG.

When transfer is completed, TX and RX buffer data are compared.
If data is matched, test result is passed otherwise failed.


::::{only} SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX
   To modify the example to use main domain SPI, refer [Accessing main and wakeup domain peripherals from MCU domain](../../developer_guides/main_domain_peripheral_access.md)
::::


## Supported Combinations
::::{only} SOC_AM64X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


::::{only} SOC_AM243X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | m4fss0-0 nortos(As am243x-lp has no MCU SPI, M4 core support excluded for am243x-lp) |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


::::{only} SOC_AM62AX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-c7000 |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


::::{only} SOC_AM263X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_LP_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | m4fss0-0 freertos |
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | arm.gnu.aarch64-none |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | r5fss0-0 nortos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


::::{only} SOC_AM62LX

| Parameter      | Value |
|---|---|
| CPU + OS | a53ss0-0 nortos |
| CPU + OS | a53ss0-0 freertos |
| Toolchain | arm.gnu.aarch64-none |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM62LX
   - To Load and Run an example (see `DFU_LOAD_CCS_DEBUG`)
::::


::::{only} SOC_AM64X or SOC_AM243X or SOC_AM263X or SOC_AM62X or SOC_AM62AX or SOC_AM62DX or SOC_AM62PX or SOC_AM275X or SOC_AM273X or SOC_AWR294X or SOC_J722S
   - Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)
::::


::::{only} SOC_AM62X or SOC_AM62PX
   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


   - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
::::


## See Also

[MCSPI](../../components/drivers/mcspi.md)

## Sample Output

Shown below is a sample output when the application is run,

```
[MCSPI] Loopback example started ...
All tests have passed!!
```