# PMIC user register configuration example
## Introduction

The example demonstrates the the configuration of user space registers for various features in the PMIC. The application
configures the ADC, thermal monitoring, voltage monitoring, GPIO pin and gets the status. Refer the PMIC datasheet
for more information on the parameters configured. The example passes if the configuration and get status is success.

## Supported Combinations
::::{only} SOC_AM62PX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmic/pmic_user_reg_cfg |

::::


::::{only} SOC_AM62DX

| Parameter      | Value |
|---|---|
| CPU + OS | mcu-r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmic/pmic_trigger_watchdog_interrupt |

::::


::::{only} SOC_AM275X

| Parameter      | Value |
|---|---|
| CPU + OS | r5fss0-0 freertos |
| Toolchain | ti-arm-clang |
| Board | {{ VAR_BOARD_NAME_LOWER }} |
| Example folder | examples/drivers/pmic/pmic_user_reg_cfg |

::::


## Steps

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see [Using SDK with CCS Projects](../../developer_guides/ccs_projects.md)).
- **When using makefiles to build**, note the required combination and build using
  make command (see [Using SDK with Makefiles](../../developer_guides/makefile_build.md))
- Launch a CCS debug session and run the executable, see [CCS Launch, Load and Run](../../getting_started/ccs_launch.md)

## See Also

[PMIC](../../components/board/pmic.md)

## Sample Output

Shown below is a sample output when the application is run,

```
Starting PMIC user space register configuration example !!

ADC result code: 0
PMIC ADC configuration and get conversion result... DONE

Thermal monitoring status:
Thermal warning bit: 0
Thermal orderly shutdown bit: 0
Thermal immediate shutdown bit: 0
PMIC thermal monitoring configuration and get status... DONE

BUCK3 over-voltage/under-voltage status: 0
LDO2 over-voltage/under-voltage status: 0
VMON1 over-voltage/under-voltage status: 0
VCCA VMON over-voltage/under-voltage status: 0
PMIC voltage monitoring configuration and get status... DONE

PMIC GPIO pin configuration... DONE

All tests have passed!!
```