# SAFETY APP

## Introduction

The example demonstrates the usage of RM, PM and TIFS safety checker APIs.

* PM Safety Checker can be used to validate PSC/PLL configurations
* RM Safety Checkers can be used to validate RM module configurations
* TIFS Safety Checker can be used to verify the firewall configuration

Each of these configurations can be validated using the Golden Reference.

## Supported Combinations
::::{only} SOC_AM62X

    Parameter      | Value
    ---------------|-----------
    CPU + OS       | r5fss0-0 freertos
    Toolchain      | ti-arm-clang
    Board          | {{ VAR_BOARD_NAME_LOWER }}, {{ VAR_SK_LP_BOARD_NAME_LOWER }}
    Example folder | examples/safety/safety_app/

::::


::::{only} SOC_AM62AX or SOC_AM62PX

| Parameter | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/safety/safety_app/ |

::::


## Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[SAFETY_APP](../../components/safety_checkers/safety_app.md)

## Sample Output

Shown below is a sample output when the application is run

```
Get PSC configuration successful.
Get PLL configuration successful.
Get RM configuration successful.
Firewall open successful.
Get firewall configuration successful.
Verifying registers against golden reference...
No register mismatch with golden reference.
Firewall close successful.
```