# PM SAFETY CHECKERS WARM RESET

## Introduction

This example validates the warm reset API is indeed done. Below are the steps used for the validation of warm reset

1. Call warm reset function and wait for reset happen; failure if function returns without reset.
2. Check for the warm reset status in the second execution due to the successful reset. If the status is true return SUCCESS.

## Supported Combinations
::::{only} SOC_AM62X

    Parameter      | Value
    ---------------|-----------
    CPU + OS       | r5fss0-0 freertos
    Toolchain      | ti-arm-clang
    Board          | {{ VAR_BOARD_NAME_LOWER }} , {{ VAR_SK_LP_BOARD_NAME_LOWER }},
    Example folder | source/safety_checkers/examples/

::::


::::{only} SOC_AM62AX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Toolchain | arm.gnu.aarch64-none |
| Boards | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | source/safety_checkers/examples/ |

::::


::::{only} SOC_AM62PX

    Parameter      | Value
    ---------------|-----------
    CPU + OS       | mcu-r5fss0-0 freertos
    Toolchain      | ti-arm-clang
    ^              | arm.gnu.aarch64-none
    Board          | {{ VAR_BOARD_NAME_LOWER }}
    Example folder | source/safety_checkers/examples/

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[PM_SAFETY_CHECKERS](../../components/safety_checkers/safety_checkers_pm.md)

## Sample Output

Shown below is a sample output when the application is run,

```
Sciserver Testapp Built On: Feb  7 2024 10:19:18
Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
RM_PM_HAL Version: vMM.NN.PP
Starting Sciserver..... PASSED
PM Safety Checkers App for Warm Reset Started
Doing MCU warm reset resetSciserver Testapp Built On: Feb  7 2024 10:19:18
Sciserver Version: v2023.11.0.0REL.MCUSDK.MM.NN.PP.bb
RM_PM_HAL Version: vMM.NN.PP
Starting Sciserver..... PASSED
PM Safety Checkers App for Warm Reset Started
MCU reset occured due to warm reset

Warm Reset example Passed
```