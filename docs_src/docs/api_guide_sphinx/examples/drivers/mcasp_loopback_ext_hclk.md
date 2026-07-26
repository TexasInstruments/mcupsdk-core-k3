---
orphan: true
---

# MCASP Loopback External HCLK
## Introduction

This example demonstrates the McASP in loopback mode operation with an external
HCLK source

- Mcasp is configured in TDM mode
- Transfers data on single channel

## Supported Combinations
::::{only} SOC_AM62AX

    | Parameter      | Value |
    |---|---|
    | CPU + OS       | c75ss0-0 freertos |
    | Toolchain      | ti-c7000 |
    | Board          | {{ VAR_BOARD_NAME_LOWER }} |
    | Example folder | examples/drivers/mcasp/mcasp_loopback_ext_hclk |

::::


::::{only} SOC_AM62X

    | Parameter      | Value |
    |---|---|
    | CPU + OS       | a53ss0-0 freertos             |
    | Toolchain      | arm.gnu.aarch64-none |
    | Board          | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
    | Example folder | examples/drivers/mcasp/mcasp_loopback_ext_hclk |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

::::{only} SOC_AM62AX or SOC_AM62X
   - External HCLK source needs to be supplied to the pin 15 of J3 header. The frequency of
   the supplied source is specified in syscfg
::::

- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[MCASP](../../components/drivers/mcasp_v1.md)

## Sample Output

Shown below is a sample output when the application is run,

```
[MCASP] Loopback example started. Testing 2560 bytes ...
All bytes match!!
All tests have passed!!
```