# Firewall Exception Trigger Example

## Introduction

This example can be used to trigger firewall exceptions.
The core running this example waits for the user to enter one of the following two characters:
* 'D' to trigger a DMSC firewall exception
* 'C' to trigger a Combined firewall exception

Consequently, a firewall exception takes place.
This example is used with the [Firewall Exception Log Example](fwl_exception_log.md) example to trigger firewall
exceptions, the latter one responds to exception events as and when they take place.

## Supported Combinations
::::{only} SOC_AM62X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}, {{ VAR_SIP_SK_BOARD_NAME_LOWER }} |
| Example folder | examples/security/fwl_exception_trigger |


::::


::::{only} SOC_AM62AX or SOC_AM62PX or SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/fwl_exception_trigger |

::::


::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-1 freertos |
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

::::{only} SOC_AM275X
- The example selects UART3 in the sysconfig for logging purposes so the logs should appear on UART3.
::::

## Sample Output

Shown below is a sample output when the application is run,

```
Enter 'D' to trigger DMSC firewall exception..
Enter 'C' to trigger CMBN firewall exception..
C
```