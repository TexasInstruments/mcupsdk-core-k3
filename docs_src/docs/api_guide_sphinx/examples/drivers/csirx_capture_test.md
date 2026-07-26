# CSIRX CAPTURE TEST
## Introduction


::::{only} SOC_J722S
   In this example, each CSIRX instance in the SOC is configured to receive RAW12 packets from 4 virtual channels
::::


::::{only} SOC_AM62AX
   In this example, CSIRX is configured to receive RAW12 packets from 1 virtual channel
::::


## Supported Combinations
::::{only} SOC_J722S

    | Parameter      | Value |
    |---|---|
    | CPU + OS       | main-r5fss0-0 freertos |
    | Toolchain      | ti-arm-clang |
    | Board          | {{ VAR_BOARD_NAME_LOWER }} |
    | Example folder | examples/drivers/csirx/csirx_capture_test/ |

::::


::::{only} SOC_AM62AX

    | Parameter      | Value |
    |---|---|
    | CPU + OS       | r5fss0-0 freertos |
    | Toolchain      | ti-arm-clang |
    | Board          | {{ VAR_BOARD_NAME_LOWER }} |
    | Example folder | examples/drivers/csirx/csirx_capture_test/ |

::::


## Steps to Run the Example

<!-- - **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)). -->
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Flash SBL NULL bootloader by following steps mentioned in [Flash SOC Initialization Binary](../../getting_started/am62px_evm_setup.md)
- Switch to [OSPI NOR BOOT MODE](../../getting_started/am62px_evm_setup.md) and power on the EVM.
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## Sample Output

