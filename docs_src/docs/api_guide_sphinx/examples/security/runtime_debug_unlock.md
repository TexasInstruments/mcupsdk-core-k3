# Runtime debug unlock Example

## Introduction

In HS-SE device, the JTAG debug port is closed by default. The user can do runtime debug unlock by sending a TISCI message with a signed debug certificate.
This example demonstrates how to do runtime JTAG port unlock. If the JTAG is unlocked, the example passes. The example is supported only on HS-SE device.

Refer [TISCI documentation](https://downloads.ti.com/tisci/esd/latest/2_tisci_msgs/security/runtime_debug.html) for more details about the API.

:::{admonition} Note
Only hosts allowed in security board configuration can send jtag unlock message via TISCI. Before running the example change the "allow_jtag_unlock", "allow_wildcard_unlock" and "jtag_unlock_hosts" parameters in the "source/drivers/sciclient/sciclient_default_boardcfg/{{ VAR_SOC_NAME_LOWER }}/sciclient_defaultBoardcfg_security.c" as follows,
:::


::::{only} SOC_AM62AX
              .allow_jtag_unlock = 0x5A,
           .allow_wildcard_unlock = 0x5A,
           .jtag_unlock_hosts = {TISCI_HOST_ID_A53_0, 0, 0, 0},
   ::::


::::{only} SOC_AM62PX
              .allow_jtag_unlock = 0x5A,
           .allow_wildcard_unlock = 0x5A,
           .jtag_unlock_hosts = {TISCI_HOST_ID_WKUP_0_R5_0, 0, 0, 0},
   ::::


::::{only} SOC_AM275X
              .allow_jtag_unlock = 0x5A,
           .allow_wildcard_unlock = 0x5A,
           .jtag_unlock_hosts = {TISCI_HOST_ID_MAIN_0_R5_0, 0, 0, 0},
   ::::


## Supported Combinations
::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | a53ss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/runtime_debug_unlock |

::::


::::{only} SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | wkup-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/runtime_debug_unlock |


::::


::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/security/runtime_debug_unlock |

::::


## Steps to Run the Example

### Generate debug certificate
- Generate the debug certificate for your HSSE device using [SYSFW Secure Debug Certificate Generation](../../components/tools/tools_sysfw.md) tool.

## Build the example
- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))

- As the JTAG is closed, the example can not be loaded through CCS. It can be flashed and booted through any [Secondary Bootloader (SBL)](../examples_drivers_sbl.rst).

- For example, refer [Flash a Hello World example](../../getting_started/getting_started_flash.md) to boot through SBL OSPI.


## Sample Output

Shown below is a sample output when the application is run,

```
Runtime debug unlock example!
Run time JTAG debug unlock... DONE !!!
All tests have passed!!
```