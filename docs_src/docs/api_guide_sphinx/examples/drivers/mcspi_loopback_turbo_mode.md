# MCSPI Loopback Turbo Mode

## Introduction

This example demonstrates the McSPI RX and TX operation configured in Turbo mode.

Turbo mode improves the throughput of the MCSPI interface when a single channel
is enabled by allowing transfers until the shift register and the MCSPI_RX register are full.
Turbo mode is time saving when a transfer exceeds two words. When several channels are enabled,
the TURBO bit has no effect.

This example sends a known data in TX mode and receives the same in RX mode. Internal pad level
loopback mode is enabled to receive data. When transfer is completed, TX and RX buffer data are
compared. If data is matched, test result is passed otherwise failed.

## Supported Combinations

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
| Example folder | examples/drivers/mcspi/mcspi_loopback_turbo_mode |

::::

::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| CPU + OS | c75ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | ti-c7000 |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/mcspi/mcspi_loopback_turbo_mode |

::::

## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[MCSPI](../../components/drivers/mcspi.md)

## Sample Output

Shown below is a sample output when the application is run,

```
[MCSPI] Loopback example started ...
----------------------------------------------------------
McSPI Clock 50000000 Hz
----------------------------------------------------------
Data Width 	Data Length 	Transfer Time (micro sec)
8		128		39.00
----------------------------------------------------------

All tests have passed!!
```
