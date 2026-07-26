# EEPROM Read Write
## Introduction

This example demonstrates write some values to the EEPROM device present in the board and
read those values.
Application write 20 samples to EEPROM and read those 20 samples from the EEPROM then exits.

## Supported Combinations
::::{only} SOC_AM62AX

    | Parameter      | Value |
    |---|---|
    | CPU + OS       | r5fss0-0 freertos |
    | Toolchain      | ti-arm-clang |
    | Board          | {{ VAR_BOARD_NAME_LOWER }} |
    | Example folder | examples/board/eeprom/eeprom_read_write |

::::


::::{only} SOC_AM62DX

    | Parameter      | Value |
    |---|---|
    | CPU + OS       | a53ss0-0 nortos |
    |  | a53ss0-0 freertos |
    | Toolchain      | arm.gnu.aarch64-none |
    | Board          | {{ VAR_BOARD_NAME_LOWER }} |
    | Example folder | examples/board/eeprom/eeprom_read_write |

::::


::::{only} SOC_AM275X

    | Parameter      | Value |
    |---|---|
    | CPU + OS       | r5fss0-0 freertos |
    | Toolchain      | ti-arm-clang |
    | Board          | {{ VAR_BOARD_NAME_LOWER }} |
    | Example folder | examples/board/eeprom/eeprom_read_write |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM275X
   :::{admonition} Attention
   As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.
   :::


   - Refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) for flashing the application.
::::

## See Also

[EEPROM](../../components/board/eeprom.md)

## Sample Output

Shown below is a sample output when the application is run,

```
Writing to the EEPROM Started ...
Writing to the EEPROM is SUCCESS...
Reading  the EEPROM Started ...
Reading  the EEPROM is SUCCESS ...
Read samples are 10
Read samples are 11
Read samples are 12
Read samples are 13
Read samples are 14
Read samples are 15
Read samples are 16
Read samples are 17
Read samples are 18
Read samples are 19
Read samples are 20
Read samples are 21
Read samples are 22
Read samples are 23
Read samples are 24
Read samples are 25
Read samples are 26
Read samples are 27
Read samples are 28
Read samples are 29
Reading  the EEPROM is Done...
All tests have passed!!
```