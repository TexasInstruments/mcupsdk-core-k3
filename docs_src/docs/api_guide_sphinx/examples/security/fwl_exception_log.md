# Firewall Exception Log Example

## Introduction

Firewall exceptions occur when an initiator tries to access memory locations which are firewalled against access from it.
Whenever firewall exceptions take place, corrsponding interrupt for various cores are asserted.
This example demonstrates how to handle firewall exceptions.

## Supported Combinations
::::{only} SOC_AM62X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/security/fwl_exception_log |


::::


::::{only} SOC_AM62AX

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/fwl_exception_trigger |

::::


::::{only} SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/fwl_exception_log |

::::


::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/fwl_exception_log |

::::


::::{only} SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/fwl_exception_trigger |


::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## Sample Output

Shown below is a sample output when the application is run,

```
FWL Exception logging example!
Registered handler for DMSC firewall exception interrupt!
Registered handler for CMBN firewall exception!
Waiting for DMSC firewall exceptions...
Waiting for CMBN firewall exceptions...
Combined Firewall Exception Occured!! Check TIFS logs for more details
Combined Firewall Exception Occured!! Check TIFS logs for more details
All tests have passed!!
```