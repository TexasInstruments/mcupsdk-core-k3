# SDL MCRC Full CPU
## Introduction

This example demonstrates the usage of the MCRC module. The example shows how to setup and use the MCRC controller in the full mode of operation.
Shows the generation of matching CRC as well as non-matching signature due to insertion of error in the block of information on which the CRC
is being performed or in the signature provided to the PSA Signature Register (or both, depending on the mode).

Use Cases
---------

| Use Case | Description |
|---|---|
| UC-1 | Full CPU-mode signature compute for Channel 1 and comparison against known value. |
| UC-2 | Full CPU-mode signature compute for Channel 2 and comparison against known value. |


## Supported Combinations
::::{only} SOC_AM64X or SOC_AM62X

| Parameter | Value |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/mcrc/mcrc_full_cpu/ |


::::


::::{only} SOC_AM62AX or SOC_AM62DX

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/mcrc/mcrc_full_cpu/ |

::::


::::{only} SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/mcrc/mcrc_full_cpu/ |


::::


::::{only} SOC_AM275X

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/mcrc/mcrc_full_cpu/ |


::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

:::{admonition} Note
64 bit data writes during MCRC calculation will not be atomic due to limitations caused by the configuration of device memory - including the MCRC register space. If the user desires atomicity of register writes during CRC calculation, the recommended software workaround is to disable all interrupts before a write and re-enable them afterwards.
:::

## See Also

[MCRC](../../components/sdl/mcrc.md)

::::{only} SOC_AM64X

   **Sample Output SOC_AM64X**

   Shown below is a sample output when the application is run,

```
MCRC Application

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCRC_MCU_NAVSS

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCRC_MCU_NAVSS

Applications Name: MCRC_fullCPU_mode  PASSED

All applications have passed.

MCRC Application

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCRC_MCU_NAVSS

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCRC_MCU_NAVSS

Applications Name: MCRC_fullCPU_mode  PASSED

All tests have passed
```

::::


::::{only} SOC_AM62X

   **Sample Output SOC_AM62X**

::::


::::{only} SOC_AM62AX or SOC_AM62DX

   **Sample Output SOC_AM62AX || SOC_AM62DX**

```
MCRC Application

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

Applications Name: MCRC_fullCPU_mode  PASSED

All applications have passed.

MCRC Application

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

Applications Name: MCRC_fullCPU_mode  PASSED

All tests have passed
```

::::


::::{only} SOC_AM62PX

   **Sample Output SOC_AM62PX**

```
MCRC Application

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

Applications Name: MCRC_fullCPU_mode  PASSED

All applications have passed.

MCRC Application

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCU_MCRC64_0

Applications Name: MCRC_fullCPU_mode  PASSED

All tests have passed
```

::::


::::{only} SOC_AM275X

   **Sample Output SOC_AM275X**

```
MCRC Application

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCRC64_0

MCRC FULL CPU mode : starting
Full_CPU mode MCRC signature verification done successfully for the instance MCRC64_0

Applications Name: MCRC_fullCPU_mode  PASSED

All tests have passed
```

::::

