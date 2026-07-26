# SDL POK Example
## Introduction

This example demonstrates the usage of the POK modules. The example shows how to listen for POK error events using the ESM, and also forcing an error in order to demonstrate application notification of overvoltage and undervoltage events.

The example demonstrates:

    * Undervoltage event detection
    * Overvoltage event detection

Use Cases
---------
| Use Case | Description |
|---|---|
| UC-0 | An under-voltage POK instance is configured to a threshold value that will force the undervoltage |
| UC-0 | event.Error event is triggered and application is notified of the event. |
| UC-1 | An over-voltage POK instance is configured to a threshold value that will force the overvoltage event. Error event is triggered and application is notified of the event. |


## Supported Combinations
::::{only} (SOC_AM62X)

| Parameter | Value |
|---|---|
| CPU + OS | m4fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/pok/ |


::::


::::{only} (SOC_AM275X)

| Parameter | Value |
|---|---|
| CPU + OS | r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/pok/ |


::::


::::{only} (SOC_AM62PX) or (SOC_AM62AX) or (SOC_AM62DX)

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 nortos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/sdl/pok/ |


::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[POK](../../components/sdl/pok.md)

## Sample Output

Shown below is a sample output when the application is run,

```
 POK Test Application

sdlEsmSetupForPOK init: Init WKUP ESM complete


 POK ID = 2 , monitoring set to UV
Waiting for ESM to report the error
 Got the ESM Error Interrupt
Action taken
Safety software Example UC-1 pok for instance 2 PASSED


 POK ID = 2 , monitoring set to OV
Waiting for ESM to report the error
 Got the ESM Error Interrupt
Action taken
Safety software Example UC-2 pok for instance  2 PASSED
Test Name: POR EXAMPLE UC-2  PASSED

 All tests have passed.

```