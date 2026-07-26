# MCU BIST Check Result
## Introduction

This example reads the MCU LBIST and MCU PBIST results and verifies it.
SBL OSPI example starts the MCU LBIST and MCU PBIST before loading the MCU core.
Once the MCU core is booted the results of the MCU PBIST and MCU LBIST can be verified by this example.


## Supported Combinations
::::{only} SOC_AM62X

| Parameter      | Value |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/safety/mcu_bist_result |

::::


::::{only} SOC_AM62AX or SOC_AM62DX or SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/safety/mcu_bist_result |

::::


## Steps

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)


## Sample Output

Shown below is a sample output when the application is run,

```
All tests have passed!!
```